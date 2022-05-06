// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Network/NetworkPriority.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* NETWORK_CATEGORY = "Network";

static const float DEFAULT_BASE_PRIORITY = 100.0f;
static const float DEFAULT_DISTANCE_FACTOR = 0.0f;
static const float DEFAULT_MIN_PRIORITY = 0.0f;
static const float UPDATE_THRESHOLD = 100.0f;

NetworkPriority::NetworkPriority(Context* context) :
    Component(context),
    basePriority_(DEFAULT_BASE_PRIORITY),
    distanceFactor_(DEFAULT_DISTANCE_FACTOR),
    minPriority_(DEFAULT_MIN_PRIORITY),
    alwaysUpdateOwner_(true)
{
}

NetworkPriority::~NetworkPriority() = default;

void NetworkPriority::RegisterObject(Context* context)
{
    context->RegisterFactory<NetworkPriority>(NETWORK_CATEGORY);

    URHO3D_ATTRIBUTE("Base Priority", float, basePriority_, DEFAULT_BASE_PRIORITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Distance Factor", float, distanceFactor_, DEFAULT_DISTANCE_FACTOR, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Minimum Priority", float, minPriority_, DEFAULT_MIN_PRIORITY, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Always Update Owner", bool, alwaysUpdateOwner_, true, AM_DEFAULT);
}

void NetworkPriority::SetBasePriority(float priority)
{
    basePriority_ = Max(priority, 0.0f);
    MarkNetworkUpdate();
}

void NetworkPriority::SetDistanceFactor(float factor)
{
    distanceFactor_ = Max(factor, 0.0f);
    MarkNetworkUpdate();
}

void NetworkPriority::SetMinPriority(float priority)
{
    minPriority_ = Max(priority, 0.0f);
    MarkNetworkUpdate();
}

void NetworkPriority::SetAlwaysUpdateOwner(bool enable)
{
    alwaysUpdateOwner_ = enable;
    MarkNetworkUpdate();
}

bool NetworkPriority::CheckUpdate(float distance, float& accumulator)
{
    float currentPriority = Max(basePriority_ - distanceFactor_ * distance, minPriority_);
    accumulator += currentPriority;
    if (accumulator >= UPDATE_THRESHOLD)
    {
        accumulator = fmodf(accumulator, UPDATE_THRESHOLD);
        return true;
    }
    else
        return false;
}

}
