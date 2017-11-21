#include "../../UI/Sprite.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API void Sprite_SetTexture(Sprite* nativeInstance, Texture* texture)
{
    nativeInstance->SetTexture(texture);
}

}
