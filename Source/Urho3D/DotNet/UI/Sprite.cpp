#include "../../UI/Sprite.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API void Sprite_SetTexture(Sprite* nativeInstance, Texture* texture)
{
    nativeInstance->SetTexture(texture);
}

URHO3D_API void Sprite_SetHotSpot(Sprite* nativeInstance, int x, int y)
{
    nativeInstance->SetHotSpot(x, y);
}

URHO3D_API void Sprite_SetScale(Sprite* nativeInstance, float scale)
{
    nativeInstance->SetScale(scale);
}

}
