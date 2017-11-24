#include "../../Math/MathDefs.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API float Random_void()
{
    return Urho3D::Random();
}

URHO3D_API float Random_float(float range)
{
    return Urho3D::Random(range);
}

}
