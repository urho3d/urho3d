#include "../../Input/Input.h"
#include "../Defines.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void Input_SetMouseMode(Input* nativeInstance, MouseMode mode, bool suppressEvent = false)
{
    nativeInstance->SetMouseMode(mode, suppressEvent);
}

URHO3D_API bool Input_IsMouseVisible(Input* nativeInstance)
{
    return nativeInstance->IsMouseVisible();
}

URHO3D_API void Input_SetMouseVisible(Input* nativeInstance, bool enable, bool suppressEvent = false)
{
    nativeInstance->SetMouseVisible(enable, suppressEvent);
}

URHO3D_API bool Input_GetKeyDown(Input* nativeInstance, int key)
{
    return nativeInstance->GetKeyDown(key);
}

URHO3D_API bool Input_GetKeyPress(Input* nativeInstance, int key)
{
    return nativeInstance->GetKeyPress(key);
}

}
