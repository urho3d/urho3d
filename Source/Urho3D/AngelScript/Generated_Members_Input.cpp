// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// class Controls | File: ../Input/Controls.h
void CollectMembers_Controls(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned Controls::buttons_", "uint buttons", offsetof(Controls, buttons_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Controls::yaw_", "float yaw", offsetof(Controls, yaw_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float Controls::pitch_", "float pitch", offsetof(Controls, pitch_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap Controls::extraData_", "VariantMap extraData", offsetof(Controls, extraData_)));

}

// struct JoystickState | File: ../Input/Input.h
void CollectMembers_JoystickState(MemberCollection& members)
{
    // SDL_Joystick* JoystickState::joystick_
    // Not registered because pointer
    // SDL_GameController* JoystickState::controller_
    // Not registered because pointer
    // UIElement* JoystickState::screenJoystick_
    // Not registered because pointer
    // PODVector<bool> JoystickState::buttons_
    // Error: type "PODVector<bool>" can not automatically bind
    // PODVector<bool> JoystickState::buttonPress_
    // Error: type "PODVector<bool>" can not automatically bind
    // PODVector<float> JoystickState::axes_
    // Error: type "PODVector<float>" can not automatically bind
    // PODVector<int> JoystickState::hats_
    // Error: type "PODVector<int>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("SDL_JoystickID JoystickState::joystickID_", "SDL_JoystickID joystickID", offsetof(JoystickState, joystickID_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String JoystickState::name_", "String name", offsetof(JoystickState, name_)));

}

// struct TouchState | File: ../Input/Input.h
void CollectMembers_TouchState(MemberCollection& members)
{
    // WeakPtr<UIElement> TouchState::touchedElement_
    // Error: type "WeakPtr<UIElement>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("int TouchState::touchID_", "int touchID", offsetof(TouchState, touchID_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 TouchState::position_", "IntVector2 position", offsetof(TouchState, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 TouchState::lastPosition_", "IntVector2 lastPosition", offsetof(TouchState, lastPosition_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 TouchState::delta_", "IntVector2 delta", offsetof(TouchState, delta_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float TouchState::pressure_", "float pressure", offsetof(TouchState, pressure_)));

}

// class Input | File: ../Input/Input.h
void CollectMembers_Input(MemberCollection& members)
{
    CollectMembers_Object(members);

}

} // namespace Urho3D
