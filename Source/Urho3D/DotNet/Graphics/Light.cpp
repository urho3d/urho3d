#include "../../Graphics/Light.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API void Light_SetLightType(Light* nativeInstance, LightType type)
{
    nativeInstance->SetLightType(type);
}

}