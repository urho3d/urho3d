#include "../../Graphics/Viewport.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Viewport* Viewport_Viewport(Context* nativeContext, Scene* scene, Camera* camera, RenderPath* renderPath = nullptr)
{
    return new Viewport(nativeContext, scene, camera, renderPath);
}

}
