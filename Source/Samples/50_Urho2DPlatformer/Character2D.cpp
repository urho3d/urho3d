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
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include <Urho3D/DebugNew.h>

#include "Character2D.h"

// Character2D logic component
Character2D::Character2D(Context* context) :
    LogicComponent(context),
    wounded_(false),
    killed_(false),
    timer_(0.0f),
    maxCoins_(0),
    remainingCoins_(0),
    remainingLifes_(3),
    isClimbing_(false),
    climb2_(false),
    aboveClimbable_(false),
    onSlope_(false)
{
}

void Character2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Character2D>();

    // These macros register the class attributes to the Context for automatic load / save handling.
    // We specify the 'Default' attribute mode which means it will be used both for saving into file, and network replication.
    URHO3D_ATTRIBUTE("Wounded", bool, wounded_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Killed", bool, killed_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Timer", float, timer_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Coins In Level", int, maxCoins_, 0, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Remaining Coins", int, remainingCoins_, 0, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Remaining Lifes", int, remainingLifes_, 3, AM_DEFAULT);
    // Note that we don't load/save isClimbing_ as the contact listener already sets this bool.
    URHO3D_ATTRIBUTE("Is Climbing Rope", bool, climb2_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Above Climbable", bool, aboveClimbable_, false, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is On Slope", bool, onSlope_, false, AM_DEFAULT);
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

    // Set temporary variables
    auto* input = GetSubsystem<Input>();
    auto* body = GetComponent<RigidBody2D>();
    auto* animatedSprite = GetComponent<AnimatedSprite2D>();
    bool onGround = false;
    bool jump = false;

    // Collision detection (AABB query)
    Vector2 characterHalfSize = Vector2(0.16f, 0.16f);
    auto* physicsWorld = GetScene()->GetComponent<PhysicsWorld2D>();
    PODVector<RigidBody2D*> collidingBodies;
    physicsWorld->GetRigidBodies(collidingBodies, Rect(node_->GetWorldPosition2D() - characterHalfSize - Vector2(0.0f, 0.1f), node_->GetWorldPosition2D() + characterHalfSize));

    if (collidingBodies.Size() > 1 && !isClimbing_)
        onGround = true;

    // Set direction
    Vector2 moveDir = Vector2::ZERO; // Reset

    if (input->GetKeyDown(KEY_A) || input->GetKeyDown(KEY_LEFT))
    {
        moveDir = moveDir + Vector2::LEFT;
        animatedSprite->SetFlipX(false); // Flip sprite (reset to default play on the X axis)
    }
    if (input->GetKeyDown(KEY_D) || input->GetKeyDown(KEY_RIGHT))
    {
        moveDir = moveDir + Vector2::RIGHT;
        animatedSprite->SetFlipX(true); // Flip sprite (flip animation on the X axis)
    }

    // Jump
    if ((onGround || aboveClimbable_) && (input->GetKeyPress(KEY_W) || input->GetKeyPress(KEY_UP)))
        jump = true;

    // Climb
    if (isClimbing_)
    {
        if (!aboveClimbable_ && (input->GetKeyDown(KEY_UP) || input->GetKeyDown(KEY_W)))
            moveDir = moveDir + Vector2(0.0f, 1.0f);

        if (input->GetKeyDown(KEY_DOWN) || input->GetKeyDown(KEY_S))
            moveDir = moveDir + Vector2(0.0f, -1.0f);
    }

    // Move
    if (!moveDir.Equals(Vector2::ZERO) || jump)
    {
        if (onSlope_)
            body->ApplyForceToCenter(moveDir * MOVE_SPEED / 2, true); // When climbing a slope, apply force (todo: replace by setting linear velocity to zero when will work)
        else
            node_->Translate(Vector3(moveDir.x_, moveDir.y_, 0) * timeStep * 1.8f);
        if (jump)
            body->ApplyLinearImpulse(Vector2(0.0f, 0.17f) * MOVE_SPEED, body->GetMassCenter(), true);
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
            node_->SetPosition(Vector3(1.0f, 8.0f, 0.0f));
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
    if (animatedSprite->GetAnimation() != "dead2")
        animatedSprite->SetAnimation("dead2");
}
