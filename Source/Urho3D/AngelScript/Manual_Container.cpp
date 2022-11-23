// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Container(asIScriptEngine* engine)
{
}

// ========================================================================================

static String& StringAssignInt(int value, String& str)
{
    str = String(value);
    return str;
}

static String StringAddInt(int value, const String& str)
{
    return str + String(value);
}

static String StringAddIntReverse(int value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignUInt(unsigned value, String& str)
{
    str = String(value);
    return str;
}

static String StringAddUInt(unsigned value, const String& str)
{
    return str + String(value);
}

static String StringAddUIntReverse(unsigned value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignFloat(float value, String& str)
{
    str = String(value);
    return str;
}

static String StringAddFloat(float value, const String& str)
{
    return str + String(value);
}

static String StringAddFloatReverse(float value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignDouble(double value, String& str)
{
    str = String(value);
    return str;
}

static String& StringAddAssignDouble(double value, String& str)
{
    str += String(value);
    return str;
}

static String StringAddDouble(double value, const String& str)
{
    return str + String(value);
}

static String StringAddDoubleReverse(double value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignBool(bool value, String& str)
{
    str = String(value);
    return str;
}

static String StringAddBool(bool value, const String& str)
{
    return str + String(value);
}

static String StringAddBoolReverse(bool value, const String& str)
{
    return String(value) + str;
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Container(asIScriptEngine* engine)
{
    static StringFactory stringFactory;
    engine->RegisterStringFactory("String", &stringFactory);

    engine->RegisterObjectMethod("String", "String& opAssign(int)", AS_FUNCTION_OBJLAST(StringAssignInt), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(int) const", AS_FUNCTION_OBJLAST(StringAddInt), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(int) const", AS_FUNCTION_OBJLAST(StringAddIntReverse), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(uint)", AS_FUNCTION_OBJLAST(StringAssignUInt), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(uint) const", AS_FUNCTION_OBJLAST(StringAddUInt), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(uint) const", AS_FUNCTION_OBJLAST(StringAddUIntReverse), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(float)", AS_FUNCTION_OBJLAST(StringAssignFloat), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(float) const", AS_FUNCTION_OBJLAST(StringAddFloat), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(float) const", AS_FUNCTION_OBJLAST(StringAddFloatReverse), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(double)", AS_FUNCTION_OBJLAST(StringAssignDouble), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(double)", AS_FUNCTION_OBJLAST(StringAddAssignDouble), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(double) const", AS_FUNCTION_OBJLAST(StringAddDouble), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(double) const", AS_FUNCTION_OBJLAST(StringAddDoubleReverse), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(bool)", AS_FUNCTION_OBJLAST(StringAssignBool), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(bool) const", AS_FUNCTION_OBJLAST(StringAddBool), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(bool) const", AS_FUNCTION_OBJLAST(StringAddBoolReverse), AS_CALL_CDECL_OBJLAST);
}

}
