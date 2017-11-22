#include "../../UI/Text.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Text* Text_Text(Context* nativeContext)
{
    return new Text(nativeContext);
}

URHO3D_API void Text_SetText(Text* nativeInstance, const char* text)
{
    nativeInstance->SetText(text);
}

URHO3D_API bool Text_SetFont(Text* nativeInstance, Font* font, float size = DEFAULT_FONT_SIZE)
{
    return nativeInstance->SetFont(font, size);
}

}
