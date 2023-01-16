// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include <Urho3D/Urho3DAll.h>

namespace Urho3D
{

constexpr i32 CTRL_UP = 1;
constexpr i32 CTRL_DOWN = 2;
constexpr i32 CTRL_LEFT = 4;
constexpr i32 CTRL_RIGHT = 8;
constexpr i32 CTRL_FIRE = 16;
constexpr i32 CTRL_JUMP = 32;
constexpr i32 CTRL_ALL = 63;

constexpr i32 SIDE_NEUTRAL = 0;
constexpr i32 SIDE_PLAYER = 1;
constexpr i32 SIDE_ENEMY = 2;

class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:
    static void RegisterObject(Context* context);

    bool onGround;
    bool isSliding;
    float duration;
    i32 health;
    i32 maxHealth;
    i32 side; // Какой стороне принадлежит (игроки, враги или нейтралы)
    i32 lastDamageSide;
    i32 lastDamageCreatorID;
    i32 creatorID;

    GameObject(Context* context);

    void FixedUpdate(float timeStep) override;
    bool Damage(GameObject& origin, i32 amount);
    virtual bool Heal(i32 amount);
    void PlaySound(const String& soundName);
    void HandleSoundFinished(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    virtual void WorldCollision(VariantMap& eventData);
    virtual void ObjectCollision(GameObject& otherObject, VariantMap& eventData);
    void ResetWorldCollision();
};

} // namespace Urho3D
