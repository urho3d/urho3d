#include "../../Graphics/Zone.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API void Zone_SetFogColor(Zone* nativeInstance, Color& color)
{
    nativeInstance->SetFogColor(color);
}

}