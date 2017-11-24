#include "../../Graphics/Texture.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API int Texture_GetWidth(Texture* nativeInstance)
{
    return nativeInstance->GetWidth();
}

URHO3D_API int Texture_GetHeight(Texture* nativeInstance)
{
    return nativeInstance->GetHeight();
}

}
