#include "../../Scene/Scene.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Scene* Scene_Scene(Context* nativeContext)
{
    return new Scene(nativeContext);
}

}
