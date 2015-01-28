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

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/Container/DebugNew.h>

#include "Character2D.h"

// Character2D logic component
Character2D::Character2D(Context* context) :
    LogicComponent(context)
{
}

void Character2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Character2D>();
}

void Character2D::Update(float timeStep)
{
    AnimatedSprite2D* animatedSprite = GetComponent<AnimatedSprite2D>();
    RigidBody2D* body = GetComponent<RigidBody2D>();
    Input* input = GetSubsystem<Input>();

    // Set direction
    Vector2 moveDir = Vector2::ZERO; // Reset

    if (input->GetKeyDown('A') || input->GetKeyDown(KEY_LEFT))
    {
        moveDir = moveDir + Vector2::LEFT;
        animatedSprite->SetFlipX(false); // Flip sprite (reset to default play on the X axis)
    }
    if (input->GetKeyDown('D') || input->GetKeyDown(KEY_RIGHT))
    {
        moveDir = moveDir + Vector2::RIGHT;
        animatedSprite->SetFlipX(true); // Flip sprite (flip animation on the X axis)
    }

    if (input->GetKeyPress('W') || input->GetKeyPress(KEY_UP)) // Jump
    {
            float jumpForce = 15.0f;
            if (moveDir.Equals(Vector2::ZERO))
                jumpForce = 10.0f;
            moveDir = moveDir + Vector2(0.0f, jumpForce);
    }

    // Move
    if (!moveDir.Equals(Vector2::ZERO))
        {
            body->ApplyForceToCenter(moveDir * MOVE_SPEED, true);
            body->ApplyForceToCenter(body->GetLinearVelocity() * -10.0f, true); // Limit max speed and facilitate return to rest
        }

    // Animate
    if (input->GetKeyDown(KEY_SPACE))
    {
        if (animatedSprite->GetAnimation() != "attack")
        {
            animatedSprite->SetAnimation("attack", LM_FORCE_LOOPED);
            animatedSprite->SetSpeed(1.5f);
        }
    }
    else if (!moveDir.Equals(Vector2::ZERO))
    {
        if (animatedSprite->GetAnimation() != "run")
            animatedSprite->SetAnimation("run", LM_FORCE_LOOPED);
    }
    else if (animatedSprite->GetAnimation() != "idle")
    {
        animatedSprite->SetAnimation("idle", LM_FORCE_LOOPED);
    }
}