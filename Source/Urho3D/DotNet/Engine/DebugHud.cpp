#include "../../Engine/DebugHud.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void DebugHud_ToggleAll(DebugHud* nativeInstance)
{
    nativeInstance->ToggleAll();
}

}
