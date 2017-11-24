#include "../../Core/ProcessUtils.h"
#include "../../DotNet/Defines.h"

extern "C"
{

// TODO: should return
URHO3D_API void ProcessUtils_ParseArguments(const char* cmdLine)
{
    ParseArguments(cmdLine);
}

}
