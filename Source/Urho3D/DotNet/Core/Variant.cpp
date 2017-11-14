#include "../../Core/Variant.h"

using namespace Urho3D;

extern "C"
{

// Warning when "Variant VariantMap_GetValue(const VariantMap& nativeInstance, StringHash key)
URHO3D_API void VariantMap_GetValue(const VariantMap& nativeInstance, StringHash key, Variant* value)
{
    (*value) = nativeInstance[key];
}

URHO3D_API void VariantMap_SetValue(VariantMap* nativeInstance, StringHash key, Variant* value)
{
    printf("VariantMap_SetValue key=%u value.type=%i value.value=%i\n", key, value->GetType(), value->GetInt());

//    Variant testValue = 17;

    unsigned char bytes[sizeof(Variant)];
    memcpy(bytes, value, sizeof(Variant));
    for (int i = 0; i < sizeof(Variant); i++)
        printf("%i = %i\n", i, bytes[i]);

    (*nativeInstance)[key] = (*value);
}

}
