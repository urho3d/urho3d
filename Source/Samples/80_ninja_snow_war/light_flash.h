// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "game_object.h"

namespace Urho3D
{

class LightFlash : public GameObject
{
    URHO3D_OBJECT(LightFlash, GameObject);

public:
    static void RegisterObject(Context* context);

    LightFlash(Context* context);
    void FixedUpdate(float timeStep) override;
};

} // namespace Urho3D
