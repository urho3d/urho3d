// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Urho3DAll.h>

namespace Urho3D
{

// Перенесено сюда из NinjaSnowWar.as
Node* SpawnObject(Scene* scene, const Vector3& position, const Quaternion& rotation, const String& className);
Node* SpawnParticleEffect(Scene* scene, const Vector3& position, const String& effectName, float duration, CreateMode mode = REPLICATED);
Node* SpawnSound(Scene* scene, const Vector3& position, const String& soundName, float duration);

} // namespace Urho3D
