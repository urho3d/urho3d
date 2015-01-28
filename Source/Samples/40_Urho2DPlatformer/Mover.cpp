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

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Container/DebugNew.h>

#include "Mover.h"

Mover::Mover(Context* context) :
    LogicComponent(context),
    speed_(0.5f),
    currentPathID_(1)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(USE_UPDATE);
}

void Mover::Update(float timeStep)
{
    // Set direction and move to target
    Vector2 dir = path_[currentPathID_] - node_->GetPosition2D();
    Vector2 dirNormal = dir.Normalized();
    node_->Translate(Vector3(dirNormal.x_, dirNormal.y_, 0.0f) * Abs(speed_) * timeStep);

    // Check for new target to reach
    if (Abs(dir.Length()) < 0.1f)
    {
        if (speed_ > 0.0f)
        {
            if (currentPathID_ + 1 < path_.Size())
                currentPathID_ = currentPathID_ + 1;
            else
            {
                currentPathID_ = currentPathID_ - 1;
                speed_ = -speed_;
            }
        }
        else
        {
            if (currentPathID_ - 1 >= 0)
                currentPathID_ = currentPathID_ - 1;
            else
            {
                currentPathID_ = 1;
                speed_ = -speed_;
            }
        }
    }
}