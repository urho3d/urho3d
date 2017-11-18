#include "../../Resource/ResourceCache.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API Resource* ResourceCache_GetResource(ResourceCache* nativeInstance, StringHash type, const char* name, bool sendEventOnFailure = true)
{
    return nativeInstance->GetResource(type, name, sendEventOnFailure);
}

}
