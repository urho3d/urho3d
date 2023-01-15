// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "game_object.h"

namespace Urho3D
{

class Snowball : public GameObject
{
    URHO3D_OBJECT(Snowball, GameObject);

private:
    int hitDamage;

public:
    static void RegisterObject(Context* context);

    Snowball(Context* context);

    void Start() override;
    void FixedUpdate(float timeStep) override;
    void WorldCollision(VariantMap& eventData) override;
    void ObjectCollision(GameObject& otherObject, VariantMap& eventData) override;
};

} // namespace Urho3D
