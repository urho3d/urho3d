#include "../../Core/Variant.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void VariantMap_GetValue(VariantMap& nativeInstance, StringHash key, Variant& value)
{
    value = nativeInstance[key];
}

URHO3D_API void VariantMap_SetValue(VariantMap& nativeInstance, StringHash key, Variant& value)
{
    nativeInstance[key] = value;
}

}
