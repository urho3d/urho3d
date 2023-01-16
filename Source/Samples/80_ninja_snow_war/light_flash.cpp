// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "light_flash.h"

namespace Urho3D
{

void LightFlash::RegisterObject(Context* context)
{
    context->RegisterFactory<LightFlash>();
}

LightFlash::LightFlash(Context* context)
    : GameObject(context)
{
    duration = 2.0f;
}

void LightFlash::FixedUpdate(float timeStep)
{
    Light* light = node_->GetComponent<Light>();
    light->SetBrightness(light->GetBrightness() * Max(1.0f - timeStep * 10.0f, 0.0f));

    // Call superclass to handle lifetime
    GameObject::FixedUpdate(timeStep);
}

} // namespace Urho3D
