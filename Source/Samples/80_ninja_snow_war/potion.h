// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "game_object.h"

namespace Urho3D
{

class Potion : public GameObject
{
    URHO3D_OBJECT(Potion, GameObject);

private:
    i32 healAmount;

public:
    static void RegisterObject(Context* context);

    Potion(Context* context);
    void Start() override;
    void ObjectCollision(GameObject& otherObject, VariantMap& eventData) override;
};

} // namespace Urho3D
