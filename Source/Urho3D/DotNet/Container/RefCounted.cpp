#include "../../Container/RefCounted.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void RefCounted_AddRef(RefCounted* nativeInstance)
{
    nativeInstance->AddRef();
}

URHO3D_API void RefCounted_ReleaseRef(RefCounted* nativeInstance)
{
    nativeInstance->ReleaseRef();
}

}
