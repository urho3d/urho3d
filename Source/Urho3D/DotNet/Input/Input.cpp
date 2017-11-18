#include "../../Input/Input.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void Input_SetMouseMode(Input* nativeInstance, MouseMode mode, bool suppressEvent = false)
{
    nativeInstance->SetMouseMode(mode, suppressEvent);
}

URHO3D_API void Input_SetMouseVisible(Input* nativeInstance, bool enable, bool suppressEvent = false)
{
    nativeInstance->SetMouseVisible(enable, suppressEvent);
}

}
