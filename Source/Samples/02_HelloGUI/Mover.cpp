//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/UIElement.h>

#include "Mover.h"

#include <Urho3D/DebugNew.h>

Mover::Mover(Context* context) :
    UIComponent(context),
    position_(Vector2::ZERO),
    moveSpeed_(Vector2::ZERO)
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Mover, HandleUpdate));
}

void Mover::Init(const Vector2& position, const Vector2& speed)
{
    position_ = position;
    moveSpeed_ = speed;
}

void Mover::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    if (position_.x_ > 200.0f)
        moveSpeed_.x_ = -abs(moveSpeed_.x_);
    else if (position_.x_ < -200.0f)
        moveSpeed_.x_ = abs(moveSpeed_.x_);

    if (position_.y_ > 100.0f)
        moveSpeed_.y_ = -abs(moveSpeed_.y_);
    else if (position_.y_ < -100.0f)
        moveSpeed_.y_ = abs(moveSpeed_.y_);

    position_ += moveSpeed_ * timeStep;
    element_->SetPosition((int)position_.x_, (int)position_.y_);
}
