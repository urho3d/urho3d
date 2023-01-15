// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "game_object.h"

namespace Urho3D
{

void GameObject::RegisterObject(Context* context)
{
    context->RegisterFactory<GameObject>();
}

GameObject::GameObject(Context* context)
    : LogicComponent(context)
    , onGround(false)
    , isSliding(false)
    , duration(-1) // Бесконечно
    , health(0)
    , maxHealth(0)
    , side(SIDE_NEUTRAL)
    , lastDamageSide(SIDE_NEUTRAL)
    , lastDamageCreatorID(0)
    , creatorID(0)
{
    SetUpdateEventMask(LogicComponentEvents::FixedUpdate);

    // if (runClient)
    //     Print("Warning! Logic object created on client!");
}

void GameObject::FixedUpdate(float timeStep)
{
    // Disappear when duration expired
    if (duration >= 0)
    {
        duration -= timeStep;
        if (duration <= 0)
            node_->Remove();
    }
}

bool GameObject::Damage(GameObject& origin, i32 amount)
{
    if (origin.side == side || health == 0)
        return false;

    lastDamageSide = origin.side;
    lastDamageCreatorID = origin.creatorID;
    health -= amount;
    if (health < 0)
        health = 0;
    return true;
}

bool GameObject::Heal(i32 amount)
{
    // By default do not heal
    return false;
}

void GameObject::PlaySound(const String& soundName)
{
    SoundSource3D* source = node_->CreateComponent<SoundSource3D>();
    Sound* sound = GetSubsystem<ResourceCache>()->GetResource<Sound>(soundName);
    // Subscribe to sound finished for cleaning up the source
    SubscribeToEvent(node_, E_SOUNDFINISHED, URHO3D_HANDLER(GameObject, HandleSoundFinished));

    source->SetDistanceAttenuation(2, 50, 1);
    source->Play(sound);
}

void GameObject::HandleSoundFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace SoundFinished;
    SoundSource3D* source = static_cast<SoundSource3D*>(eventData[P_SOUNDSOURCE].GetPtr());
    source->Remove();
}

void GameObject::HandleNodeCollision(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
    RigidBody* otherBody = static_cast<RigidBody*>(eventData[P_OTHERBODY].GetPtr());

    // If the other collision shape belongs to static geometry, perform world collision
    if (otherBody->GetCollisionLayer() == 2)
        WorldCollision(eventData);

    // If the other node is scripted, perform object-to-object collision
    GameObject* otherObject = otherNode->GetDerivedComponent<GameObject>();
    if (otherObject)
        ObjectCollision(*otherObject, eventData);
}

void GameObject::WorldCollision(VariantMap& eventData)
{
    using namespace NodeCollision;
    MemoryBuffer contacts(eventData[P_CONTACTS].GetBuffer());

    while (!contacts.IsEof())
    {
        Vector3 contactPosition = contacts.ReadVector3();
        Vector3 contactNormal = contacts.ReadVector3();
        float contactDistance = contacts.ReadFloat();
        float contactImpulse = contacts.ReadFloat();

        // If contact is below node center and pointing up, assume it's ground contact
        if (contactPosition.y_ < node_->GetPosition().y_)
        {
            float level = contactNormal.y_;

            if (level > 0.75)
            {
                onGround = true;
            }
            else
            {
                // If contact is somewhere between vertical/horizontal, is sliding a slope
                if (level > 0.1)
                    isSliding = true;
            }
        }
    }

    // Ground contact has priority over sliding contact
    if (onGround == true)
        isSliding = false;
}

void GameObject::ObjectCollision(GameObject& otherObject, VariantMap& eventData)
{
}

void GameObject::ResetWorldCollision()
{
    RigidBody* body = node_->GetComponent<RigidBody>();
 
    if (body->IsActive())
    {
        onGround = false;
        isSliding = false;
    }
    else
    {
        // If body is not active, assume it rests on the ground
        onGround = true;
        isSliding = false;
    }
}

} // namespace Urho3D
