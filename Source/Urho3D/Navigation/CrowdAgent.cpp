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

#include "../Scene/Component.h"
#include "../Core/Context.h"
#include "../Navigation/CrowdAgent.h"
#include "../Graphics/DebugRenderer.h"
#include "../Navigation/DetourCrowdManager.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Navigation/NavigationEvents.h"
#include "../Scene/Node.h"
#include "../Core/Profiler.h"
#include "../Scene/Scene.h"
#include "../Scene/Serializable.h"
#include "../Core/Variant.h"

#include <Detour/DetourCommon.h>
#include <DetourCrowd/DetourCrowd.h>

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

static const unsigned DEFAULT_AGENT_NAVIGATION_FILTER_TYPE = 0;
static const float DEFAULT_AGENT_MAX_SPEED = 0.f;
static const float DEFAULT_AGENT_MAX_ACCEL = 0.f;
static const NavigationQuality DEFAULT_AGENT_AVOIDANCE_QUALITY = NAVIGATIONQUALITY_HIGH;
static const NavigationPushiness DEFAULT_AGENT_NAVIGATION_PUSHINESS = PUSHINESS_MEDIUM;

const char* crowdAgentAvoidanceQualityNames[] = {
    "low",
    "medium",
    "high",
    0
};

const char* crowdAgentPushinessNames[] = {
    "low",
    "medium",
    "high",
    0
};


CrowdAgent::CrowdAgent(Context* context) :
    Component(context),
    inCrowd_(false),
    agentCrowdId_(-1),
    targetRef_(-1),
    updateNodePosition_(true),
    maxAccel_(DEFAULT_AGENT_MAX_ACCEL),
    maxSpeed_(DEFAULT_AGENT_MAX_SPEED),
    radius_(0.0f),
    height_(0.0f),
    filterType_(DEFAULT_AGENT_NAVIGATION_FILTER_TYPE),
    navQuality_(DEFAULT_AGENT_AVOIDANCE_QUALITY),
    navPushiness_(DEFAULT_AGENT_NAVIGATION_PUSHINESS),
    previousTargetState_(CROWD_AGENT_TARGET_NONE),
    previousAgentState_(CROWD_AGENT_READY),
    ignoreTransformChanges_(false)
{
}

CrowdAgent::~CrowdAgent()
{
    RemoveAgentFromCrowd();
}

void CrowdAgent::RegisterObject(Context* context)
{
    context->RegisterFactory<CrowdAgent>(NAVIGATION_CATEGORY);

    ACCESSOR_ATTRIBUTE("Max Accel", GetMaxAccel, SetMaxAccel, float, DEFAULT_AGENT_MAX_ACCEL, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Max Speed", GetMaxSpeed, SetMaxSpeed, float, DEFAULT_AGENT_MAX_SPEED, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Radius", GetRadius, SetRadius, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Height", GetHeight, SetHeight, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Target Position", GetTargetPosition, SetMoveTarget, Vector3, Vector3::ZERO, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Navigation Filter", GetNavigationFilterType, SetNavigationFilterType, unsigned, DEFAULT_AGENT_NAVIGATION_FILTER_TYPE, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Navigation Pushiness", GetNavigationPushiness, SetNavigationPushiness, NavigationPushiness, crowdAgentPushinessNames, PUSHINESS_LOW, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Navigation Quality", GetNavigationQuality, SetNavigationQuality, NavigationQuality, crowdAgentAvoidanceQualityNames, NAVIGATIONQUALITY_LOW, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Agent Data", GetAgentDataAttr, SetAgentDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
}

void CrowdAgent::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            if (scene == node)
                LOGERROR(GetTypeName() + " should not be created to the root scene node");
            crowdManager_ = scene->GetOrCreateComponent<DetourCrowdManager>();
            AddAgentToCrowd();
        }

        node->AddListener(this);
    }
    else
        RemoveAgentFromCrowd();
}

void CrowdAgent::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (enabled && !inCrowd_)
        AddAgentToCrowd();
    else if (!enabled && inCrowd_)
        RemoveAgentFromCrowd();
}

void CrowdAgent::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
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

const dtCrowdAgent* CrowdAgent::GetDetourCrowdAgent() const
{
    return crowdManager_ && inCrowd_ ? crowdManager_->GetCrowdAgent(agentCrowdId_) : 0;
}

void CrowdAgent::AddAgentToCrowd()
{
    if (!crowdManager_ || !crowdManager_->crowd_ || !node_)
        return;

    PROFILE(AddAgentToCrowd);

    if (!inCrowd_)
    {
        inCrowd_ = true;
        agentCrowdId_ = crowdManager_->AddAgent(this, node_->GetPosition());
        if (agentCrowdId_ == -1)
        {
            inCrowd_ = false;
            LOGERROR("AddAgentToCrowd: Could not add agent to crowd");
            return;
        }
        crowdManager_->UpdateAgentNavigationQuality(this, navQuality_);
        crowdManager_->UpdateAgentPushiness(this, navPushiness_);
        previousAgentState_ = GetAgentState();
        previousTargetState_ = GetTargetState();

        // Agent created, but initial state is invalid and needs to be addressed
        if (previousAgentState_ == CROWD_AGENT_INVALID)
        {
            VariantMap& map = GetContext()->GetEventDataMap();
            map[CrowdAgentFailure::P_NODE] = GetNode();
            map[CrowdAgentFailure::P_CROWD_AGENT] = this;
            map[CrowdAgentFailure::P_CROWD_TARGET_STATE] = previousTargetState_;
            map[CrowdAgentFailure::P_CROWD_AGENT_STATE] = previousAgentState_;
            map[CrowdAgentFailure::P_POSITION] = GetPosition();
            map[CrowdAgentFailure::P_VELOCITY] = GetActualVelocity();
            SendEvent(E_CROWD_AGENT_FAILURE, map);

            // Reevaluate states as handling of event may have resulted in changes
            previousAgentState_ = GetAgentState();
            previousTargetState_ = GetTargetState();
        }

        // Save the initial position to prevent CrowdAgentReposition event being triggered unnecessarily
        previousPosition_ = GetPosition();
    }
}

void CrowdAgent::RemoveAgentFromCrowd()
{
    if (crowdManager_ && agentCrowdId_ != -1 && inCrowd_)
    {
        crowdManager_->RemoveAgent(this);
        inCrowd_ = false;
        agentCrowdId_ = -1;
    }
}

void CrowdAgent::SetNavigationFilterType(unsigned filterType)
{
    filterType_ = filterType;
    if (crowdManager_ && inCrowd_)
    {
        // If in the crowd it's necessary to force the update of the query filter
        dtCrowdAgentParams params = crowdManager_->GetCrowdAgent(agentCrowdId_)->params;
        params.queryFilterType = (unsigned char)filterType;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMoveTarget(const Vector3& position)
{
    if (crowdManager_) {
        if (!inCrowd_)
            AddAgentToCrowd();
        targetPosition_ = position;
        if (crowdManager_->SetAgentTarget(this, position, targetRef_))
            MarkNetworkUpdate();
    }
}

void CrowdAgent::ResetMoveTarget()
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent && agent->active)
    {
        targetPosition_ = Vector3::ZERO;
        crowdManager_->GetCrowd()->resetMoveTarget(agentCrowdId_);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMoveVelocity(const Vector3& velocity)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent && agent->active)
    {
        crowdManager_->GetCrowd()->requestMoveVelocity(agentCrowdId_, velocity.Data());
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMaxSpeed(float speed)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        maxSpeed_ = speed;
        dtCrowdAgentParams params = agent->params;
        params.maxSpeed = speed;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMaxAccel(float accel)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        maxAccel_ = accel;
        dtCrowdAgentParams params = agent->params;
        params.maxAcceleration = accel;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetRadius(float radius)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        radius_ = radius;
        dtCrowdAgentParams params = agent->params;
        params.radius = radius;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetHeight(float height)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        height_ = height;
        dtCrowdAgentParams params = agent->params;
        params.height = height;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationQuality(NavigationQuality val)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        navQuality_ = val;
        crowdManager_->UpdateAgentNavigationQuality(this, navQuality_);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationPushiness(NavigationPushiness val)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        navPushiness_ = val;
        crowdManager_->UpdateAgentPushiness(this, navPushiness_);
        MarkNetworkUpdate();
    }
}

Vector3 CrowdAgent::GetPosition() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active ? Vector3(agent->npos) : node_->GetPosition();
}

Vector3 CrowdAgent::GetDesiredVelocity() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active ? Vector3(agent->dvel) : Vector3::ZERO;
}

Vector3 CrowdAgent::GetActualVelocity() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active ? Vector3(agent->vel) : Vector3::ZERO;
}

Urho3D::CrowdAgentState CrowdAgent::GetAgentState() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active ? (CrowdAgentState)agent->state : CROWD_AGENT_INVALID;
}

Urho3D::CrowdTargetState CrowdAgent::GetTargetState() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active ? (CrowdTargetState)agent->targetState : CROWD_AGENT_TARGET_NONE;
}

bool CrowdAgent::HasArrived() const
{
    // Is the agent at or near the end of its path?
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && agent->active && (!agent->ncorners ||
        (agent->cornerFlags[agent->ncorners - 1] & DT_STRAIGHTPATH_END &&
            Equals(dtVdist2D(agent->npos, &agent->cornerVerts[(agent->ncorners - 1) * 3]), 0.f)));
}

void CrowdAgent::SetUpdateNodePosition(bool unodepos)
{
    updateNodePosition_ = unodepos;
    MarkNetworkUpdate();
}

void CrowdAgent::OnCrowdAgentReposition(const Vector3& newPos, const Vector3& newVel)
{
    if (node_)
    {
        // Notify parent node of the reposition
        if (newPos != previousPosition_)
        {
            previousPosition_ = newPos;

            VariantMap& map = GetContext()->GetEventDataMap();
            map[CrowdAgentReposition::P_NODE] = GetNode();
            map[CrowdAgentReposition::P_CROWD_AGENT] = this;
            map[CrowdAgentReposition::P_POSITION] = newPos;
            map[CrowdAgentReposition::P_VELOCITY] = newVel;
            map[CrowdAgentReposition::P_ARRIVED] = HasArrived();
            SendEvent(E_CROWD_AGENT_REPOSITION, map);

            if (updateNodePosition_)
            {
                ignoreTransformChanges_ = true;
                node_->SetPosition(newPos);
                ignoreTransformChanges_ = false;
            }
        }

        // Send a notification event if we've reached the destination
        CrowdTargetState newTargetState = GetTargetState();
        CrowdAgentState newAgentState = GetAgentState();
        if (newAgentState != previousAgentState_ || newTargetState != previousTargetState_)
        {
            VariantMap& map = GetContext()->GetEventDataMap();
            map[CrowdAgentStateChanged::P_NODE] = GetNode();
            map[CrowdAgentStateChanged::P_CROWD_AGENT] = this;
            map[CrowdAgentStateChanged::P_CROWD_TARGET_STATE] = newTargetState;
            map[CrowdAgentStateChanged::P_CROWD_AGENT_STATE] = newAgentState;
            map[CrowdAgentStateChanged::P_POSITION] = newPos;
            map[CrowdAgentStateChanged::P_VELOCITY] = newVel;
            SendEvent(E_CROWD_AGENT_STATE_CHANGED, map);

            // Send a failure event if either state is a failed status
            if (newAgentState == CROWD_AGENT_INVALID || newTargetState == CROWD_AGENT_TARGET_FAILED)
            {
                VariantMap& map = GetContext()->GetEventDataMap();
                map[CrowdAgentFailure::P_NODE] = GetNode();
                map[CrowdAgentFailure::P_CROWD_AGENT] = this;
                map[CrowdAgentFailure::P_CROWD_TARGET_STATE] = newTargetState;
                map[CrowdAgentFailure::P_CROWD_AGENT_STATE] = newAgentState;
                map[CrowdAgentFailure::P_POSITION] = newPos;
                map[CrowdAgentFailure::P_VELOCITY] = newVel;
                SendEvent(E_CROWD_AGENT_FAILURE, map);
            }

            // State may have been altered during the handling of the event
            previousAgentState_ = GetAgentState();
            previousTargetState_ = GetTargetState();
        }
    }
}

PODVector<unsigned char> CrowdAgent::GetAgentDataAttr() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (!agent)
        return Variant::emptyBuffer;

    // Reading it back in isn't this simple, see SetAgentDataAttr
    VectorBuffer ret;
    ret.Write(agent, sizeof(dtCrowdAgent));

    return ret.GetBuffer();
}

void CrowdAgent::SetAgentDataAttr(const PODVector<unsigned char>& value)
{
    if (value.Empty())
        return;

    dtCrowdAgent* agent = const_cast<dtCrowdAgent*>(GetDetourCrowdAgent());
    if (!agent)
        return;

    MemoryBuffer buffer(value);

    // Path corridor is tricky
    char corridorData[sizeof(dtPathCorridor)];
    // Duplicate the existing path corridor into a block
    memcpy(corridorData, &agent->corridor, sizeof(dtPathCorridor));

    // Read the entire block of the crowd agent
    buffer.Read(agent, sizeof(dtCrowdAgent));
    // Restore the values of the original path corridor
    memcpy(&agent->corridor, corridorData, sizeof(dtPathCorridor));
    // Tell the path corridor to rebuild the path, it will reevaluate the path, existing velocities maintained
    agent->corridor.reset(agent->targetRef, agent->targetPos);

    agent->params.userData = this;
}

void CrowdAgent::OnMarkedDirty(Node* node)
{
    if (!ignoreTransformChanges_ && IsEnabledEffective())
    {
        dtCrowdAgent* agent = const_cast<dtCrowdAgent*>(GetDetourCrowdAgent());
        if (agent)
        {
            memcpy(agent->npos, node->GetWorldPosition().Data(), sizeof(float) * 3);

            // If the node has been externally altered, provide the opportunity for DetourCrowd to reevaluate the crowd agent
            if (agent->state == CROWD_AGENT_INVALID)
                agent->state = CROWD_AGENT_READY;
        }
    }
}

}
