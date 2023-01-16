// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "snow_crate.h"
#include "utilities/spawn.h"

namespace Urho3D
{

static constexpr i32 SNOWCRATE_HEALTH = 5;
static constexpr i32 SNOWCRATE_POINTS = 250;

void SnowCrate::RegisterObject(Context* context)
{
    context->RegisterFactory<SnowCrate>();
}

SnowCrate::SnowCrate(Context* context)
    : GameObject(context)
{
    health = maxHealth = SNOWCRATE_HEALTH;
}

void SnowCrate::Start()
{
    SubscribeToEvent(node_, E_NODECOLLISION, URHO3D_HANDLER(SnowCrate, HandleNodeCollision));
}

void SnowCrate::FixedUpdate(float timeStep)
{
    if (health <= 0)
    {
        SpawnParticleEffect(node_->GetScene(), node_->GetPosition(), "Particle/SnowExplosionBig.xml", 2);
        SpawnObject(node_->GetScene(), node_->GetPosition(), Quaternion(), "potion");

        VariantMap eventData;
        eventData["Points"] = SNOWCRATE_POINTS;
        eventData["Receiver"] = lastDamageCreatorID;
        eventData["DamageSide"] = lastDamageSide;
        SendEvent("Points", eventData);

        node_->Remove();
    }
}

} // namespace Urho3D
