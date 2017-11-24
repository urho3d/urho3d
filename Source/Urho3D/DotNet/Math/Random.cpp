#include "../../Math/Random.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API int Rand()
{
    return Urho3D::Rand();
}

}
