#include "../../UI/UIElement.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API UIElement* UIElement_CreateChild(UIElement* nativeInstance, StringHash type, const char* name = "", unsigned index = M_MAX_UNSIGNED)
{
    return nativeInstance->CreateChild(type, name, index);
}

URHO3D_API void UIElement_SetPriority(UIElement* nativeInstance, int priority)
{
    nativeInstance->SetPriority(priority);
}

URHO3D_API void UIElement_SetOpacity(UIElement* nativeInstance, float opacity)
{
    nativeInstance->SetOpacity(opacity);
}

URHO3D_API void UIElement_SetAlignment(UIElement* nativeInstance, HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    nativeInstance->SetAlignment(hAlign, vAlign);
}

URHO3D_API void UIElement_SetSize(UIElement* nativeInstance, int width, int height)
{
    nativeInstance->SetSize(width, height);
}

}
