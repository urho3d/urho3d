#include "../../Core/Context.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Context* Context_Context()
{
    return new Context();
}

URHO3D_API Object* Context_GetSubsystem(Context* nativeInstance, StringHash type)
{
    return nativeInstance->GetSubsystem(type);
}

}
