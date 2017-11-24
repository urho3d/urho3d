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

URHO3D_API void UIElement_SetHorizontalAlignment(UIElement* nativeInstance, HorizontalAlignment align)
{
    nativeInstance->SetHorizontalAlignment(align);
}

URHO3D_API void UIElement_SetVerticalAlignment(UIElement* nativeInstance, VerticalAlignment align)
{
    nativeInstance->SetVerticalAlignment(align);
}

URHO3D_API void UIElement_SetSize(UIElement* nativeInstance, int width, int height)
{
    nativeInstance->SetSize(width, height);
}

URHO3D_API void UIElement_SetColor(UIElement* nativeInstance, Color& color)
{
    nativeInstance->SetColor(color);
}

URHO3D_API void UIElement_AddChild(UIElement* nativeInstance, UIElement* element)
{
    nativeInstance->AddChild(element);
}

URHO3D_API void UIElement_SetPosition(UIElement* nativeInstance, int x, int y)
{
    nativeInstance->SetPosition(x, y);
}

URHO3D_API int UIElement_GetWidth(UIElement* nativeInstance)
{
    return nativeInstance->GetWidth();
}

URHO3D_API int UIElement_GetHeight(UIElement* nativeInstance)
{
    return nativeInstance->GetHeight();
}

}
