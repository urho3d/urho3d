#include "../../Core/ProcessUtils.h"
#include "../Defines.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void ProcessUtils_ParseArguments(const char* cmdLine)
{
    ParseArguments(cmdLine);
}

}
