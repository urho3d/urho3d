//
// Copyright (c) 2008-2014 the Urho3D project.
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

NetworkPriority::~NetworkPriority()
{
}

void NetworkPriority::RegisterObject(Context* context)
{
    context->RegisterFactory<NetworkPriority>(NETWORK_CATEGORY);
    
    ATTRIBUTE("Base Priority", float, basePriority_, DEFAULT_BASE_PRIORITY, AM_DEFAULT);
    ATTRIBUTE("Distance Factor", float, distanceFactor_, DEFAULT_DISTANCE_FACTOR, AM_DEFAULT);
    ATTRIBUTE("Minimum Priority", float, minPriority_, DEFAULT_MIN_PRIORITY, AM_DEFAULT);
    ATTRIBUTE("Always Update Owner", bool, alwaysUpdateOwner_, true, AM_DEFAULT);
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
