// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Input/Input.h>

#include "Character.h"
#include "Touch.h"

const float GYROSCOPE_THRESHOLD = 0.1f;

Touch::Touch(Context* context, float touchSensitivity) :
    Object(context),
    touchSensitivity_(touchSensitivity),
    cameraDistance_(CAMERA_INITIAL_DIST),
    zoom_(false),
    useGyroscope_(false)
{
}

Touch::~Touch() = default;

void Touch::UpdateTouches(Controls& controls) // Called from HandleUpdate
{
    zoom_ = false; // reset bool

    auto* input = GetSubsystem<Input>();

    // Zoom in/out
    if (input->GetNumTouches() == 2)
    {
        TouchState* touch1 = input->GetTouch(0);
        TouchState* touch2 = input->GetTouch(1);

        // Check for zoom pattern (touches moving in opposite directions and on empty space)
        if (!touch1->touchedElement_ && !touch2->touchedElement_ && ((touch1->delta_.y_ > 0 && touch2->delta_.y_ < 0) || (touch1->delta_.y_ < 0 && touch2->delta_.y_ > 0)))
            zoom_ = true;
        else
            zoom_ = false;

        if (zoom_)
        {
            int sens = 0;
            // Check for zoom direction (in/out)
            if (Abs(touch1->position_.y_ - touch2->position_.y_) > Abs(touch1->lastPosition_.y_ - touch2->lastPosition_.y_))
                sens = -1;
            else
                sens = 1;
            cameraDistance_ += Abs(touch1->delta_.y_ - touch2->delta_.y_) * sens * touchSensitivity_ / 50.0f;
            cameraDistance_ = Clamp(cameraDistance_, CAMERA_MIN_DIST, CAMERA_MAX_DIST); // Restrict zoom range to [1;20]
        }
    }

    // Gyroscope (emulated by SDL through a virtual joystick)
    if (useGyroscope_ && input->GetNumJoysticks() > 0)  // numJoysticks = 1 on iOS & Android
    {
        JoystickState* joystick = input->GetJoystickByIndex(0);
        if (joystick->GetNumAxes() >= 2)
        {
            if (joystick->GetAxisPosition(0) < -GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_LEFT, true);
            if (joystick->GetAxisPosition(0) > GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_RIGHT, true);
            if (joystick->GetAxisPosition(1) < -GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_FORWARD, true);
            if (joystick->GetAxisPosition(1) > GYROSCOPE_THRESHOLD)
                controls.Set(CTRL_BACK, true);
        }
    }
}
