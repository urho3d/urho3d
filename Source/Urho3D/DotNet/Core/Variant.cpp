#include "../../Core/Variant.h"
#include "../Defines.h"
#include "../Utils.h"

extern "C"
{

URHO3D_API char* Variant_GetCString(Variant& variant)
{
    String urhoString = variant.GetString();
    return DuplicateCString(urhoString.CString());
}

URHO3D_API void Variant_SetCString(Variant& variant, const char* value)
{
    variant = value;
}

URHO3D_API void VariantMap_GetValue(VariantMap& nativeInstance, StringHash key, Variant& value)
{
    value = nativeInstance[key];
}

URHO3D_API void VariantMap_SetValue(VariantMap& nativeInstance, StringHash key, Variant& value)
{
    nativeInstance[key] = value;
}

}
