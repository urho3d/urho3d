// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "game_object.h"

namespace Urho3D
{

class SnowCrate : public GameObject
{
    URHO3D_OBJECT(SnowCrate, GameObject);

public:
    static void RegisterObject(Context* context);

    SnowCrate(Context* context);

    void Start() override;
    void FixedUpdate(float timeStep) override;
};

} // namespace Urho3D
