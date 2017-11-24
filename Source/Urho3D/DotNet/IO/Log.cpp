#include "../../IO/Log.h"
#include "../../DotNet/Defines.h"

extern "C"
{

URHO3D_API void Log_Write(int level, const char* message)
{
    Log::Write(level, message);
}

URHO3D_API void Log_WriteRaw(const char* message, bool error = false)
{
    Log::WriteRaw(message, error);
}

}
