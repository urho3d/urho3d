#include "../../UI/UIElement.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API UIElement* UIElement_CreateChild(UIElement* nativeInstance, StringHash type, const char* name = "", unsigned index = M_MAX_UNSIGNED)
{
    return nativeInstance->CreateChild(type, name, index);
}

URHO3D_API UIElement* UIElement_SetPriority(UIElement* nativeInstance, int priority)
{
    return nativeInstance->SetPriority(priority);
}

URHO3D_API UIElement* UIElement_SetOpacity(UIElement* nativeInstance, float opacity)
{
    return nativeInstance->SetOpacity(opacity);
}

URHO3D_API UIElement* UIElement_SetAlignment(UIElement* nativeInstance, HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    return nativeInstance->SetAlignment(hAlign, vAlign);
}

URHO3D_API UIElement* UIElement_SetSize(UIElement* nativeInstance, int width, int height)
{
    return nativeInstance->SetSize(width, height);
}

}
