#include "../../Graphics/StaticModel.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API void StaticModel_SetModel(StaticModel* nativeInstance, Model* model)
{
    nativeInstance->SetModel(model);
}

URHO3D_API void StaticModel_SetMaterial(StaticModel* nativeInstance, Material* material)
{
    nativeInstance->SetMaterial(material);
}

}
