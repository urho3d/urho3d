#include "../../Math/Quaternion.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API void Quaternion_FromEulerAngles(float x, float y, float z, Quaternion& result)
{
    result = Quaternion(x, y, z);
}

}