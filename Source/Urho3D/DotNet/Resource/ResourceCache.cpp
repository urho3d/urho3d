#include "../../Resource/ResourceCache.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Resource* ResourceCache_GetResource(ResourceCache* nativeInstance, StringHash type, const char* name, bool sendEventOnFailure = true)
{
    return nativeInstance->GetResource(type, name, sendEventOnFailure);
}

}
