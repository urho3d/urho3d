#include "../../Math/StringHash.h"
#include "../Defines.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API unsigned StringHash_Calculate(const char* str)
{
    return StringHash::Calculate(str);
}

}
