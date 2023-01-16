// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "potion.h"

namespace Urho3D
{

static constexpr int POTION_HEAL_AMOUNT = 5;

void Potion::RegisterObject(Context* context)
{
    context->RegisterFactory<Potion>();
}

Potion::Potion(Context* context)
    : GameObject(context)
{
    healAmount = POTION_HEAL_AMOUNT;
}

void Potion::Start()
{
    SubscribeToEvent(node_, E_NODECOLLISION, URHO3D_HANDLER(Potion, HandleNodeCollision));
}

void Potion::ObjectCollision(GameObject& otherObject, VariantMap& eventData)
{
    if (healAmount > 0)
    {
        if (otherObject.Heal(healAmount))
        {
            // Could also remove the potion directly, but this way it gets removed on next update
            healAmount = 0;
            duration = 0;
        }
    }
}

} // namespace Urho3D
