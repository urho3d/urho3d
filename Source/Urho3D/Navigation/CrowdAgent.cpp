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
static const float DEFAULT_AGENT_MAX_SPEED = 5.0f;
static const float DEFAULT_AGENT_MAX_ACCEL = 3.6f;
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
    navPushiness_(DEFAULT_AGENT_NAVIGATION_PUSHINESS)
{
}

CrowdAgent::~CrowdAgent()
{
}

void CrowdAgent::RegisterObject(Context* context)
{
    context->RegisterFactory<CrowdAgent>(NAVIGATION_CATEGORY);

    ACCESSOR_ATTRIBUTE("Max Accel", GetMaxAccel, SetMaxAccel, float, DEFAULT_AGENT_MAX_ACCEL, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Max Speed", GetMaxSpeed, SetMaxSpeed, float, DEFAULT_AGENT_MAX_SPEED, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Radius", GetRadius, SetRadius, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Height", GetHeight, SetHeight, float, 0.0f, AM_DEFAULT);
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
        const Vector3 agentHeightVec(0, height_ * 0.5f, 0);

        debug->AddLine(pos, pos + vel, Color::GREEN, depthTest);
        debug->AddLine(pos + agentHeightVec, pos + desiredVel + agentHeightVec, Color::RED, depthTest);
        debug->AddCylinder(pos, radius_, height_, Color::GREEN, depthTest);
    }
}

void CrowdAgent::AddAgentToCrowd()
{
    if (!crowdManager_ || !crowdManager_->crowd_)
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
        dtCrowdAgentParams& params = crowdManager_->GetCrowd()->getEditableAgent(agentCrowdId_)->params;
        params.userData = this;
        crowdManager_->UpdateAgentNavigationQuality(this, navQuality_);
        crowdManager_->UpdateAgentPushiness(this, navPushiness_);
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

bool CrowdAgent::SetMoveTarget(const Vector3& position)
{
    if (crowdManager_ && !inCrowd_)
        AddAgentToCrowd();
    if (crowdManager_ && inCrowd_)
    {
        targetPosition_ = position;
        if (crowdManager_->SetAgentTarget(this, position, targetRef_))
        {
            MarkNetworkUpdate();
            return true;
        }
    }
    return false;
}

bool CrowdAgent::SetMoveVelocity(const Vector3& velocity)
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (agent && agent->active)
        {
            crowdManager_->GetCrowd()->requestMoveVelocity(agentCrowdId_, velocity.Data());
            MarkNetworkUpdate();
        }
    }
    return false;
}

void CrowdAgent::SetMaxSpeed(float speed)
{
    maxSpeed_ = speed;
    if(crowdManager_ && inCrowd_)
    {
        dtCrowdAgentParams params = crowdManager_->GetCrowdAgent(agentCrowdId_)->params;
        params.maxSpeed = speed;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMaxAccel(float accel)
{
    maxAccel_ = accel;
    if(crowdManager_ && inCrowd_)
    {
        dtCrowdAgentParams params = crowdManager_->GetCrowdAgent(agentCrowdId_)->params;
        params.maxAcceleration = accel;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetRadius(float radius)
{
    radius_ = radius;
    if (crowdManager_ && inCrowd_)
    {
        dtCrowdAgentParams params = crowdManager_->GetCrowdAgent(agentCrowdId_)->params;
        params.radius = radius;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetHeight(float height)
{
    height_ = height;
    if (crowdManager_ && inCrowd_)
    {
        dtCrowdAgentParams params = crowdManager_->GetCrowdAgent(agentCrowdId_)->params;
        params.height = height;
        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationQuality(NavigationQuality val)
{
    navQuality_=val;
    if(crowdManager_ && inCrowd_)
    {
        crowdManager_->UpdateAgentNavigationQuality(this, navQuality_);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationPushiness(NavigationPushiness val)
{
    navPushiness_=val;
    if(crowdManager_ && inCrowd_)
    {
        crowdManager_->UpdateAgentPushiness(this, navPushiness_);
        MarkNetworkUpdate();
    }
}

Vector3 CrowdAgent::GetPosition() const
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (agent && agent->active)
            return Vector3(agent->npos);
    }
    return node_->GetPosition();
}

Vector3 CrowdAgent::GetDesiredVelocity() const
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (agent && agent->active)
            return Vector3(agent->dvel);
    }
    return Vector3::ZERO;
}

Vector3 CrowdAgent::GetActualVelocity() const
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (agent && agent->active)
            return Vector3(agent->vel);
    }
    return Vector3::ZERO;
}

const Vector3& CrowdAgent::GetTargetPosition() const
{
    return targetPosition_;
}

Urho3D::CrowdAgentState CrowdAgent::GetAgentState() const
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (!agent || !agent->active)
            return CROWD_AGENT_INVALID;
        return (CrowdAgentState)agent->state;
    }
    return CROWD_AGENT_INVALID;
}

Urho3D::CrowdTargetState CrowdAgent::GetTargetState() const
{
    if (crowdManager_ && inCrowd_)
    {
        const dtCrowdAgent* agent = crowdManager_->GetCrowdAgent(agentCrowdId_);
        if (!agent || !agent->active)
            return CROWD_AGENT_TARGET_NONE;

        // Determine if we've arrived at the target
        if (agent->targetState == DT_CROWDAGENT_TARGET_VALID)
        {
            if (agent->ncorners)
            {
                // Is the agent at the end of its path?
                const bool endOfPath = (agent->cornerFlags[agent->ncorners - 1] & DT_STRAIGHTPATH_END) ? true : false;
                if (endOfPath)
                {
                    // Within its own radius of the goal?
                    if (dtVdist2D(agent->npos, &agent->cornerVerts[(agent->ncorners - 1) * 3]) <= agent->params.radius)
                        return CROWD_AGENT_TARGET_ARRIVED;

                }
            }
        }
        return (CrowdTargetState)agent->targetState;
    }
    return CROWD_AGENT_TARGET_NONE;
}

void CrowdAgent::SetUpdateNodePosition(bool unodepos)
{
    updateNodePosition_ = unodepos;
    MarkNetworkUpdate();
}

bool CrowdAgent::GetUpdateNodePosition()
{
    return updateNodePosition_;
}

void CrowdAgent::OnCrowdAgentReposition(const Vector3& newPos, const Vector3& newDirection)
{
    if(node_)
    {
        // Notify parent node of the reposition
        VariantMap& map = GetContext()->GetEventDataMap();
        map[CrowdAgentReposition::P_POSITION] = newPos;
        map[CrowdAgentReposition::P_VELOCITY] = GetActualVelocity();
        SendEvent(E_CROWD_AGENT_REPOSITION, map);
        
        ignoreTransformChanges_ = true;
        if (updateNodePosition_)
            node_->SetPosition(newPos);
        ignoreTransformChanges_ = false;

        // Send a notification event if we've reached the destination
        CrowdTargetState targetState = GetTargetState();
        switch (targetState)
        {
        case CROWD_AGENT_TARGET_ARRIVED:
            VariantMap& map = GetContext()->GetEventDataMap();
            map[CrowdAgentStateChanged::P_STATE] = targetState;
            map[CrowdAgentStateChanged::P_POSITION] = newPos;
            map[CrowdAgentStateChanged::P_VELOCITY] = GetActualVelocity();
            SendEvent(E_CROWD_AGENT_STATE_CHANGED, map);
            break;
        }
    }
}


PODVector<unsigned char> CrowdAgent::GetAgentDataAttr() const
{
    if (!inCrowd_ || !crowdManager_ || !IsEnabled())
        return Variant::emptyBuffer;
    dtCrowd* crowd = crowdManager_->GetCrowd();
    const dtCrowdAgent* agent = crowd->getAgent(agentCrowdId_);
    
    // Reading it back in isn't this simple, see SetAgentDataAttr
    VectorBuffer ret;
    ret.Write(agent, sizeof(dtCrowdAgent));

    return ret.GetBuffer();
}

void CrowdAgent::SetAgentDataAttr(const PODVector<unsigned char>& value)
{
    if (value.Empty() || !inCrowd_ || !crowdManager_ || !IsEnabled())
        return;

    MemoryBuffer buffer(value);
    dtCrowd* crowd = crowdManager_->GetCrowd();
    dtCrowdAgent* agent = crowd->getEditableAgent(agentCrowdId_);

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
    if (inCrowd_ && crowdManager_ && !ignoreTransformChanges_) {
        dtCrowdAgent* agt = crowdManager_->GetCrowd()->getEditableAgent(agentCrowdId_);
        memcpy(agt->npos, node->GetPosition().Data(), sizeof(float) * 3);
    }
}


}
