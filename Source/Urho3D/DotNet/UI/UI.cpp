#include "../../UI/UI.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API UIElement* UI_GetRoot(UI* nativeInstance)
{
    return nativeInstance->GetRoot();
}

}
