#include "../../UI/Sprite.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void Sprite_SetTexture(Sprite* nativeInstance, Texture* texture)
{
    nativeInstance->SetTexture(texture);
}

}
