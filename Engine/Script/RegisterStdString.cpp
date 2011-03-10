//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Exception.h"
#include "StringUtils.h"

#include <angelscript.h>

// Adapted from AngelScript's scriptstdstring add-on

static std::string StringFactory(asUINT length, const char* s)
{
    return std::string(s, length);
}

static void ConstructString(std::string* ptr)
{
    new(ptr) std::string();
}

static void ConstructStringCopy(const std::string& str, std::string* ptr)
{
    new(ptr) std::string(str);
}

static void DestructString(std::string* ptr)
{
    using namespace std;
    ptr->~string();
}

static char* StringCharAt(unsigned int i, std::string& str)
{
    if (i >= str.size())
        SAFE_EXCEPTION_RET("Index out of bounds", 0);
    return &str[i];
}

static int StringCmp(const std::string& lhs, const std::string& rhs)
{
    int cmp = 0;
    if (lhs < rhs)
        cmp = -1;
    else if (lhs > rhs)
        cmp = 1;
    return cmp;
}

static int StringFind(const std::string& rhs, const std::string& str)
{
    return str.find(rhs);
}

void StringResize(unsigned newSize, std::string& str)
{
    unsigned oldSize = str.length();
    str.resize(newSize);
    for (unsigned i = oldSize; i < newSize; ++i)
        str[i] = ' ';
}


std::string StringSubString1Param(unsigned start, const std::string& str)
{
    try
    {
        return str.substr(start);
    }
    catch (...)
    {
        return std::string();
    }
}

std::string StringSubString2Params(unsigned start, unsigned length, const std::string& str)
{
    try
    {
        return str.substr(start, length);
    }
    catch (...)
    {
        return std::string();
    }
}

static void ConstructStringInt(int value, std::string* ptr)
{
    new(ptr) std::string();
    *ptr = toString(value);
}

static void ConstructStringUInt(unsigned value, std::string* ptr)
{
    new(ptr) std::string();
    *ptr = toString(value);
}

static void ConstructStringFloat(float value, std::string* ptr)
{
    new(ptr) std::string();
    *ptr = toString(value);
}

static void ConstructStringBool(bool value, std::string* ptr)
{
    new(ptr) std::string();
    *ptr = toString(value);
}

static std::string& StringAssignInt(int value, std::string& str)
{
    str = toString(value);
    return str;
}

static std::string& StringAddAssignInt(int value, std::string& str)
{
    str += toString(value);
    return str;
}

static std::string StringAddInt(int value, const std::string& str)
{
    return str + toString(value);
}

static std::string StringAddIntReverse(int value, const std::string& str)
{
    return toString(value) + str;
}

static std::string& StringAssignUInt(unsigned value, std::string& str)
{
    str = toString(value);
    return str;
}

static std::string& StringAddAssignUInt(unsigned value, std::string& str)
{
    str += toString(value);
    return str;
}

static std::string StringAddUInt(unsigned value, const std::string& str)
{
    return str + toString(value);
}

static std::string StringAddUIntReverse(unsigned value, const std::string& str)
{
    return toString(value) + str;
}

static std::string& StringAssignFloat(float value, std::string& str)
{
    str = toString(value);
    return str;
}

static std::string& StringAddAssignFloat(float value, std::string& str)
{
    str += toString(value);
    return str;
}

static std::string StringAddFloat(float value, const std::string& str)
{
    return str + toString(value);
}

static std::string StringAddFloatReverse(float value, const std::string& str)
{
    return toString(value) + str;
}

static std::string& StringAssignBool(bool value, std::string& str)
{
    str = toString(value);
    return str;
}

static std::string& StringAddAssignBool(bool value, std::string& str)
{
    str += toString(value);
    return str;
}

static std::string StringAddBool(bool value, const std::string& str)
{
    return str + toString(value);
}

static std::string StringAddBoolReverse(bool value, const std::string& str)
{
    return toString(value) + str;
}

void registerStdString(asIScriptEngine *engine)
{
    engine->RegisterObjectType("string", sizeof(std::string), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterStringFactory("string", asFUNCTION(StringFactory), asCALL_CDECL);
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(ConstructStringCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("string", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAssign(const string& in)", asMETHODPR(std::string, operator =, (const std::string&), std::string&), asCALL_THISCALL);
    engine->RegisterObjectMethod("string", "string &opAddAssign(const string& in)", asMETHODPR(std::string, operator+=, (const std::string&), std::string&), asCALL_THISCALL);
    engine->RegisterObjectMethod("string", "bool opEquals(const string& in) const", asFUNCTIONPR(std::operator ==, (const std::string&, const std::string&), bool), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("string", "int opCmp(const string& in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("string", "string opAdd(const string& in) const", asFUNCTIONPR(std::operator +, (const std::string&, const std::string&), std::string), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("string", "uint length() const", asMETHOD(std::string, length), asCALL_THISCALL);
    engine->RegisterObjectMethod("string", "uint size() const", asMETHOD(std::string, size), asCALL_THISCALL);
    engine->RegisterObjectMethod("string", "bool empty() const", asMETHOD(std::string, empty), asCALL_THISCALL);
    engine->RegisterObjectMethod("string", "void resize(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "uint8 &opIndex(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "const uint8 &opIndex(uint) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "int find(const string& in) const", asFUNCTION(StringFind), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string substr(uint) const", asFUNCTION(StringSubString1Param), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string substr(uint, uint) const", asFUNCTION(StringSubString2Params), asCALL_CDECL_OBJLAST);
    
    // Register automatic conversion functions for convenience
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructStringInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructStringUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructStringFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructStringBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAssign(int)", asFUNCTION(StringAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAddAssign(int)", asFUNCTION(StringAddAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd(int) const", asFUNCTION(StringAddInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd_r(int) const", asFUNCTION(StringAddIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAssign(uint)", asFUNCTION(StringAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAddAssign(uint)", asFUNCTION(StringAddAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd(uint) const", asFUNCTION(StringAddUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd_r(uint) const", asFUNCTION(StringAddUIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAssign(float)", asFUNCTION(StringAssignFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAddAssign(float)", asFUNCTION(StringAddAssignFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd(float) const", asFUNCTION(StringAddFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd_r(float) const", asFUNCTION(StringAddFloatReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAssign(bool)", asFUNCTION(StringAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string &opAddAssign(bool)", asFUNCTION(StringAddAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd(bool) const", asFUNCTION(StringAddBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("string", "string opAdd_r(bool) const", asFUNCTION(StringAddBoolReverse), asCALL_CDECL_OBJLAST);
}
