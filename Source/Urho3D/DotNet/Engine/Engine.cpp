#include "../../Engine/Engine.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API DebugHud* Engine_CreateDebugHud(Engine* nativeInstance)
{
    return nativeInstance->CreateDebugHud();
}

}
