// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/DebugNew.h>

#include "Mover.h"

Mover::Mover(Context* context) :
    LogicComponent(context),
    speed_(0.8f),
    currentPathID_(1),
    emitTime_(0.0f),
    fightTimer_(0.0f),
    flip_(0.0f)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(LogicComponentEvents::Update);
}

void Mover::RegisterObject(Context* context)
{
    context->RegisterFactory<Mover>();

    // These macros register the class attribute to the Context for automatic load / save handling.
    // We specify the Default attribute mode which means it will be used both for saving into file, and network replication.
    URHO3D_ACCESSOR_ATTRIBUTE("Path", GetPathAttr, SetPathAttr, Variant::emptyBuffer, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Speed", speed_, 0.8f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Current Path ID", currentPathID_, 1, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Emit Time", emitTime_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Fight Timer", fightTimer_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Flip Animation", flip_, 0.0f, AM_DEFAULT);
}

void Mover::SetPathAttr(const Vector<byte>& value)
{
    if (value.Empty())
        return;

    MemoryBuffer buffer(value);
    while (!buffer.IsEof())
        path_.Push(buffer.ReadVector2());
}

Vector<byte> Mover::GetPathAttr() const
{
    VectorBuffer buffer;

    for (const Vector2& point : path_)
        buffer.WriteVector2(point);

    return buffer.GetBuffer();
}

void Mover::Update(float timeStep)
{
    if (path_.Size() < 2)
        return;

    // Handle Orc states (idle/wounded/fighting)
    if (node_->GetName() == "Orc")
    {
        auto* animatedSprite = node_->GetComponent<AnimatedSprite2D>();
        String anim = "run";

        // Handle wounded state
        if (emitTime_ > 0.0f)
        {
            emitTime_ += timeStep;
            anim = "dead";

            // Handle dead
            if (emitTime_ >= 3.0f)
            {
                node_->Remove();
                return;
            }
        }
        else
        {
            // Handle fighting state
            if (fightTimer_ > 0.0f)
            {
                anim = "attack";
                flip_ = GetScene()->GetChild("Imp", true)->GetPosition().x_ - node_->GetPosition().x_;
                fightTimer_ += timeStep;
                if (fightTimer_ >= 3.0f)
                    fightTimer_ = 0.0f; // Reset
            }
            // Flip Orc animation according to speed, or player position when fighting
            animatedSprite->SetFlipX(flip_ >= 0.0f);
        }
        // Animate
        if (animatedSprite->GetAnimation() != anim)
            animatedSprite->SetAnimation(anim);
    }

    // Don't move if fighting or wounded
    if (fightTimer_ > 0.0f || emitTime_ > 0.0f)
        return;

    // Set direction and move to target
    Vector2 dir = path_[currentPathID_] - node_->GetPosition2D();
    Vector2 dirNormal = dir.Normalized();
    node_->Translate(Vector3(dirNormal.x_, dirNormal.y_, 0.0f) * Abs(speed_) * timeStep);
    flip_ = dir.x_;

    // Check for new target to reach
    if (Abs(dir.Length()) < 0.1f)
    {
        if (speed_ > 0.0f)
        {
            if (currentPathID_ + 1 < path_.Size())
                currentPathID_ = currentPathID_ + 1;
            else
            {
                // If loop, go to first waypoint, which equates to last one (and never reverse)
                if (path_[currentPathID_] == path_[0])
                {
                    currentPathID_ = 1;
                    return;
                }
                // Reverse path if not looping
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
