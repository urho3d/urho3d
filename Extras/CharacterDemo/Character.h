#pragma once

#include "Component.h"
#include "Controls.h"

using namespace Urho3D;

const int CTRL_UP = 1;
const int CTRL_DOWN = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_FIRE = 16;
const int CTRL_JUMP = 32;
const int CTRL_ALL = 63;

const float MOVE_FORCE = 0.8f;
const float INAIR_MOVE_FORCE = 0.02f;
const float BRAKE_FORCE = 0.2f;
const float JUMP_FORCE = 7.0f;
const float YAW_SENSITIVITY = 0.1f;
const float INAIR_THRESHOLD_TIME = 0.1f;

class Character : public Component
{
    OBJECT(Character)

public:
    /// Construct.
    Character(Context* context);
    
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    
    /// Handle physics collision event.
    void HandleNodeCollision(StringHash eventType, VariantMap& eventData);
    /// Handle physics world update event.
    void HandleFixedUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Movement controls.
    Controls controls_;
    /// Grounded flag for movement.
    bool onGround_;
    /// Jump flag.
    bool okToJump_;
    /// In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
    float inAirTimer_;
};
