#include "../../Core/Context.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API Context* Context_Context()
{
    return new Context();
}

}
