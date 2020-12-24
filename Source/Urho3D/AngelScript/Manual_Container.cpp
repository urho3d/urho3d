//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Container(asIScriptEngine* engine)
{
}

// ========================================================================================

// Workaround for GCC to allow get addresses
const unsigned String::NPOS;
const unsigned String::MIN_CAPACITY;
const unsigned HashBase::MIN_BUCKETS;
const unsigned HashBase::MAX_LOAD_FACTOR;

// ========================================================================================


void FakeAddRef(void* ptr)
{
}

void FakeReleaseRef(void* ptr)
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

    engine->RegisterObjectMethod("String", "String& opAssign(int)", asFUNCTION(StringAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(int) const", asFUNCTION(StringAddInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(int) const", asFUNCTION(StringAddIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(uint)", asFUNCTION(StringAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(uint) const", asFUNCTION(StringAddUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(uint) const", asFUNCTION(StringAddUIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(float)", asFUNCTION(StringAssignFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(float) const", asFUNCTION(StringAddFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(float) const", asFUNCTION(StringAddFloatReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(double)", asFUNCTION(StringAssignDouble), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(double)", asFUNCTION(StringAddAssignDouble), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(double) const", asFUNCTION(StringAddDouble), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(double) const", asFUNCTION(StringAddDoubleReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(bool)", asFUNCTION(StringAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(bool) const", asFUNCTION(StringAddBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(bool) const", asFUNCTION(StringAddBoolReverse), asCALL_CDECL_OBJLAST);
}

}
