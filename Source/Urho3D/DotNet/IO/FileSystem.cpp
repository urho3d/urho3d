#include "../../IO/FileSystem.h"
#include "../../DotNet/Defines.h"
#include "../../DotNet/Utils.h"

extern "C"
{

URHO3D_API char* FileSystem_GetAppPreferencesDir(FileSystem* nativeInstance, const char* org, const char* app)
{
    String urhoString = nativeInstance->GetAppPreferencesDir(org, app);
    return DuplicateCString(urhoString.CString());
}

}
