#include "../DotNet/Defines.h"

char* DuplicateCString(const char *str)
{
    char* result = (char*)malloc(strlen(str) + 1);
    strcpy(result, str);
    return result;
}

void FreeCString(char* str)
{
    free(str);
}

extern "C"
{

URHO3D_API void Utils_FreeCString(char* str)
{
    FreeCString(str);
}

}