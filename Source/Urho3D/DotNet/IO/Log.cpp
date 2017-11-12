#include "../../IO/Log.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API void Log_Write(int level, const char* message)
{
    Log::Write(level, String(message));
}

URHO3D_API void Log_WriteRaw(const char* message, bool error)
{
    Log::WriteRaw(String(message), error);
}

}
