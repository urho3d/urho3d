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

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "Character2D.h"

#include <Urho3D/DebugNew.h>

// Character2D logic component
Character2D::Character2D(Context* context) :
    LogicComponent(context),
    wounded_(false),
    killed_(false),
    timer_(0.0f),
    maxCoins_(0),
    remainingCoins_(0),
    remainingLifes_(3),
    moveSpeedScale_(1.0f),
    zoom_(0.0f)
{
}

void Character2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Character2D>();

    // These macros register the class attributes to the Context for automatic load / save handling.
    // We specify the 'Default' attribute mode which means it will be used both for saving into file, and network replication.
    URHO3D_ATTRIBUTE("Move Speed Scale", float, moveSpeedScale_, 1.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Camera Zoom", float, zoom_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Coins In Level", int, maxCoins_, 0, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Remaining Coins", int, remainingCoins_, 0, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Remaining Lifes", int, remainingLifes_, 3, AM_DEFAULT);
}

void Character2D::Update(float timeStep)
{
    // Handle wounded/killed states
    if (killed_)
        return;

    if (wounded_)
    {
        HandleWoundedState(timeStep);
        return;
    }

    auto* animatedSprite = GetComponent<AnimatedSprite2D>();
    auto* input = GetSubsystem<Input>();

    // Set direction
    Vector3 moveDir = Vector3::ZERO; // Reset
    float speedX = Clamp(MOVE_SPEED_X / zoom_, 0.4f, 1.0f);
    float speedY = speedX;

    if (input->GetKeyDown(KEY_A) || input->GetKeyDown(KEY_LEFT))
    {
        moveDir = moveDir + Vector3::LEFT * speedX;
        animatedSprite->SetFlipX(false); // Flip sprite (reset to default play on the X axis)
    }
    if (input->GetKeyDown(KEY_D) || input->GetKeyDown(KEY_RIGHT))
    {
        moveDir = moveDir + Vector3::RIGHT * speedX;
        animatedSprite->SetFlipX(true); // Flip sprite (flip animation on the X axis)
    }

    if (!moveDir.Equals(Vector3::ZERO))
        speedY = speedX * moveSpeedScale_;

    if (input->GetKeyDown(KEY_W) || input->GetKeyDown(KEY_UP))
        moveDir = moveDir + Vector3::UP * speedY;
    if (input->GetKeyDown(KEY_S) || input->GetKeyDown(KEY_DOWN))
        moveDir = moveDir + Vector3::DOWN * speedY;

    // Move
    if (!moveDir.Equals(Vector3::ZERO))
        node_->Translate(moveDir * timeStep);

    // Animate
    if (input->GetKeyDown(KEY_SPACE))
    {
        if (animatedSprite->GetAnimation() != "attack")
            animatedSprite->SetAnimation("attack", LM_FORCE_LOOPED);
    }
    else if (!moveDir.Equals(Vector3::ZERO))
    {
        if (animatedSprite->GetAnimation() != "run")
            animatedSprite->SetAnimation("run");
    }
    else if (animatedSprite->GetAnimation() != "idle")
    {
        animatedSprite->SetAnimation("idle");
    }
}

void Character2D::HandleWoundedState(float timeStep)
{
    auto* body = GetComponent<RigidBody2D>();
    auto* animatedSprite = GetComponent<AnimatedSprite2D>();

    // Play "hit" animation in loop
    if (animatedSprite->GetAnimation() != "hit")
        animatedSprite->SetAnimation("hit", LM_FORCE_LOOPED);

    // Update timer
    timer_ += timeStep;

    if (timer_ > 2.0f)
    {
        // Reset timer
        timer_ = 0.0f;

        // Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        body->SetLinearVelocity(Vector2::ZERO);
        body->SetAwake(false);
        body->SetAwake(true);

        // Remove particle emitter
        node_->GetChild("Emitter", true)->Remove();

        // Update lifes UI and counter
        remainingLifes_ -= 1;
        auto* ui = GetSubsystem<UI>();
        Text* lifeText = static_cast<Text*>(ui->GetRoot()->GetChild("LifeText", true));
        lifeText->SetText(String(remainingLifes_)); // Update lifes UI counter

        // Reset wounded state
        wounded_ = false;

        // Handle death
        if (remainingLifes_ == 0)
        {
            HandleDeath();
            return;
        }

        // Re-position the character to the nearest point
        if (node_->GetPosition().x_ < 15.0f)
            node_->SetPosition(Vector3(-5.0f, 11.0f, 0.0f));
        else
            node_->SetPosition(Vector3(18.8f, 9.2f, 0.0f));
    }
}

void Character2D::HandleDeath()
{
    auto* body = GetComponent<RigidBody2D>();
    auto* animatedSprite = GetComponent<AnimatedSprite2D>();

    // Set state to 'killed'
    killed_ = true;

    // Update UI elements
    auto* ui = GetSubsystem<UI>();
    Text* instructions = static_cast<Text*>(ui->GetRoot()->GetChild("Instructions", true));
    instructions->SetText("!!! GAME OVER !!!");
    static_cast<Text*>(ui->GetRoot()->GetChild("ExitButton", true))->SetVisible(true);
    static_cast<Text*>(ui->GetRoot()->GetChild("PlayButton", true))->SetVisible(true);

    // Show mouse cursor so that we can click
    auto* input = GetSubsystem<Input>();
    input->SetMouseVisible(true);

    // Put character outside of the scene and magnify him
    node_->SetPosition(Vector3(-20.0f, 0.0f, 0.0f));
    node_->SetScale(1.2f);

    // Play death animation once
    if (animatedSprite->GetAnimation() != "dead")
        animatedSprite->SetAnimation("dead");
}
