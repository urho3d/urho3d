// Copyright (c) 2008-2023 the Urho3D project
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

struct as_unkn_arg
{
    void* val;
    int typeId;
};

static bool isFirstNameSymbol(char s) { return (s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') || s == '_'; }
static bool isNameSymbol(char s) { return isFirstNameSymbol(s) || (s >= '0' && s <= '9'); }
static String strFromSprintf(const char* buffer, int len) { return {buffer, len > 0 ? len : 0}; }

static void findVariable(asIScriptContext* context, const String& varName, void*& var, int& typeId)
{
    int thisTypeId = context->GetThisTypeId();

    if (varName == "this")
    {
        if (thisTypeId > 0)
        {
            typeId = thisTypeId;
            var = context->GetThisPointer();
        }
        return;
    }
    // Search in local vars
    for (int idx = 0, varCount = context->GetVarCount(); idx < varCount; idx++)
    {
        const char* contextVarName = nullptr;
        context->GetVar(idx, 0, &contextVarName, &typeId);
        if (varName == contextVarName && context->IsVarInScope(idx, 0))
        {
            var = context->GetAddressOfVar(idx);
            return;
        }
    }
    // Try in member vars
    if (thisTypeId > 0)
    {
        asITypeInfo* typeInfo = context->GetEngine()->GetTypeInfoById(thisTypeId);
        for (int idx = 0, propCount = typeInfo->GetPropertyCount(); idx < propCount; idx++)
        {
            const char* name;
            typeInfo->GetProperty(idx, &name, &typeId);
            if (varName == name)
            {
                var = reinterpret_cast<asIScriptObject*>(context->GetThisPointer())->GetAddressOfProperty(idx);
                return;
            }
        }
    }
    // Try global vars
    asIScriptModule* mod = context->GetFunction(0)->GetModule();
    int varIdx = mod->GetGlobalVarIndexByName(varName.CString());
    if (varIdx >= 0)
    {
        mod->GetGlobalVar(varIdx, nullptr, nullptr, &typeId);
        var = mod->GetAddressOfGlobalVar(varIdx);
        return;
    }
}

static void convertToString(void* object, asIScriptContext* context, int typeId, String& result)
{
    asITypeInfo* typeInfo = context->GetEngine()->GetTypeInfoById(typeId);
    if (!typeInfo)
    {
        result = "[error]";
        return;
    }

    bool isMemberFunc = true;
    asIScriptFunction* pFunc = typeInfo->GetMethodByDecl("String ToString()const");
    if (!pFunc)
        pFunc = typeInfo->GetMethodByDecl("String opImplConv()const");
    if (!pFunc)
        pFunc = typeInfo->GetMethodByDecl("String toString()const");
    if (!pFunc)
    {
        isMemberFunc = false;
        const char* ns = typeInfo->GetNamespace();
        String nameOfType = (ns ? String(ns) + "::" : String()) + typeInfo->GetName();
        String nameOfFunc = String("String ToString(const ") + nameOfType + "&in)";
        pFunc = context->GetFunction()->GetModule()->GetFunctionByDecl(nameOfFunc.CString());
    }
    if (pFunc)
    {
        context->PushState();
        context->Prepare(pFunc);
        if (isMemberFunc)
            context->SetObject(object);
        else
            context->SetArgObject(0, object);

        bool success = context->Execute() == asEXECUTION_FINISHED;
        if (success)
            result = *(String*)context->GetAddressOfReturnValue();
        context->PopState();
        if (success)
            return;
    }
    char buf[256];
    result = strFromSprintf(buf, snprintf(buf, sizeof(buf), "[object %s, %p]", typeInfo->GetName(), object));
}

static String formatVariable(asIScriptContext* context, int stringTypeID, as_unkn_arg* args,
                             const String& fmtStr, const String& varName, i32 argIdx)
{
    void* val = nullptr;
    int valTypeId;
    if (!varName.Empty())
        findVariable(context, varName, val, valTypeId);
    else
    {
        val = args[argIdx].val;
        valTypeId = args[argIdx].typeId;
    }
    if (!val || !valTypeId)
        return {};

    const char* fmt = fmtStr.Empty() ? nullptr : fmtStr.CString();

    if (valTypeId & asTYPEID_MASK_OBJECT)
    {
        if (valTypeId & asTYPEID_OBJHANDLE)
        {
            val = *(void**)val;
            valTypeId &= ~asTYPEID_OBJHANDLE;
        }
        String tmp;
        if (valTypeId != stringTypeID)
        {
            convertToString(val, context, valTypeId, tmp);
            val = &tmp;
        }
        if (!fmt || fmtStr == "%s")
            return *(String*)val;
        char buf[1024];
        return strFromSprintf(buf, snprintf(buf, sizeof(buf), fmt, reinterpret_cast<String*>(val)->CString()));
    }

    if (valTypeId > asTYPEID_DOUBLE) // For enums
        valTypeId = asTYPEID_INT32;

    char buffer[256];

    switch (valTypeId)
    {
    case asTYPEID_BOOL:
        if (!fmt)
            return String{*(bool*)val};
        else
            return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt, *(bool*)val));
    case asTYPEID_INT8:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%hhd", *(i8*)val));
    case asTYPEID_INT16:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%hd", *(i16*)val));
    case asTYPEID_INT32:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%d", *(i32*)val));
    case asTYPEID_INT64:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%lld", *(i64*)val));
    case asTYPEID_UINT8:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%hhx", *(u8*)val));
    case asTYPEID_UINT16:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%hx", *(u16*)val));
    case asTYPEID_UINT32:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%x", *(u32*)val));
    case asTYPEID_UINT64:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%llx", *(u64*)val));
    case asTYPEID_FLOAT:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%g", (double)*(float*)val));
    case asTYPEID_DOUBLE:
    default:
        return strFromSprintf(buffer, snprintf(buffer, sizeof(buffer), fmt ? fmt : "%g", *(double*)val));
    }
}

static String formatString(const String& pattern, int argsCount, as_unkn_arg* args)
{
    asIScriptContext* context = asGetActiveContext();
    if (!context)
        return pattern;
    int stringTypeId = context->GetEngine()->GetStringFactoryReturnTypeId();

    Vector<String> parts;
    int curArgIdx = 0, argIdx = 0, state = 0;
    const char *ptr = pattern.CString(), *start = ptr, *end = ptr + pattern.Length(), *fmt = nullptr,
               *openCurl = nullptr, *varName = nullptr;
    i32 varNameLen = 0;

    enum states
    {
        stNone,
        stReadOpenCurl,
        stBeginIdxNum,
        stBeginVarName,
        stBeginFormat,
        stReadCloseCurl,
    };

    for (; ptr < end; ptr++)
    {
        char s = *ptr;
        switch (state)
        {
        case stNone:
            if (s == '{')
            {
                state = stReadOpenCurl;
                openCurl = ptr;
            }
            break;
        case stReadOpenCurl:
            argIdx = -1;
            varNameLen = 0;
            fmt = nullptr;
            if (s == '{')
            {
                parts.EmplaceBack(start, i32(ptr - start));
                start = ptr + 1;
                state = stNone;
            }
            else if (s >= '0' && s <= '9')
            {
                argIdx = s - '0';
                state = stBeginIdxNum;
            }
            else if (isFirstNameSymbol(s))
            {
                varName = ptr;
                state = stBeginVarName;
            }
            else if (s == '%')
            {
                fmt = ptr;
                state = stBeginFormat;
            }
            else if (s == '}')
                state = stReadCloseCurl;
            else
                state = stNone;
            break;
        case stBeginIdxNum:
            if (s >= '0' && s <= '9')
                argIdx = argIdx * 10 + s - '0';
            else if (s == '%')
            {
                fmt = ptr;
                state = stBeginFormat;
            }
            else if (s == '}')
                state = stReadCloseCurl;
            else
                state = stNone;
            break;
        case stBeginVarName:
            if (!isNameSymbol(s))
            {
                if (s == '%')
                {
                    varNameLen = i32(ptr - varName);
                    fmt = ptr;
                    state = stBeginFormat;
                }
                else if (s == '}')
                {
                    varNameLen = i32(ptr - varName);
                    state = stReadCloseCurl;
                }
                else
                    state = stNone;
            }
            break;
        case stBeginFormat:
            if (s == '}')
                state = stReadCloseCurl;
            break;
        }
        if (state == stReadCloseCurl)
        {
            state = stNone;
            if (!varNameLen)
            {
                if (argIdx < 0)
                    argIdx = curArgIdx++;
                if (argIdx >= argsCount)
                    continue;
            }
            if (openCurl > start)
                parts.EmplaceBack(start, i32(openCurl - start));
            start = ptr + 1;
            parts.EmplaceBack(formatVariable(context, stringTypeId, args, {fmt, fmt ? int(ptr - fmt) : 0},
                                             {varName, varNameLen}, argIdx));
        }
    }
    if (start < end)
        parts.EmplaceBack(start, i32(end - start));
    return String::Joined(parts, {});
}

static String format_args0(const String& pattern) { return formatString(pattern, 0, nullptr); }

static String format_args1(const String& pattern, void* a1, int i1)
{
    as_unkn_arg ua[] = {{a1, i1}};
    return formatString(pattern, 1, ua);
}

static String format_args2(const String& pattern, void* a1, int i1, void* a2, int i2)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}};
    return formatString(pattern, 2, ua);
}

static String format_args3(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}};
    return formatString(pattern, 3, ua);
}

static String format_args4(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}};
    return formatString(pattern, 4, ua);
}

static String format_args5(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}};
    return formatString(pattern, 5, ua);
}

static String format_args6(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5, void* a6, int i6)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}, {a6, i6}};
    return formatString(pattern, 6, ua);
}

static String format_args7(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5, void* a6, int i6, void* a7, int i7)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}, {a6, i6}, {a7, i7}};
    return formatString(pattern, 7, ua);
}

static String format_args8(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5, void* a6, int i6, void* a7, int i7, void* a8, int i8)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}, {a6, i6}, {a7, i7}, {a8, i8}};
    return formatString(pattern, 8, ua);
}

static String format_args9(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5, void* a6, int i6, void* a7, int i7, void* a8, int i8, void* a9, int i9)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}, {a6, i6}, {a7, i7}, {a8, i8}, {a9, i9}};
    return formatString(pattern, 9, ua);
}

static String format_argsA(const String& pattern, void* a1, int i1, void* a2, int i2, void* a3, int i3, void* a4, int i4, void* a5, int i5, void* a6, int i6, void* a7, int i7, void* a8, int i8, void* a9, int i9, void* aA, int iA)
{
    as_unkn_arg ua[] = {{a1, i1}, {a2, i2}, {a3, i3}, {a4, i4}, {a5, i5}, {a6, i6}, {a7, i7}, {a8, i8}, {a9, i9}, {aA, iA}};
    return formatString(pattern, 10, ua);
}

#ifdef AS_MAX_PORTABILITY
static void String_Format_gen(asIScriptGeneric* gen)
{
    int argsCount = gen->GetArgCount();
    Vector<as_unkn_arg> args(argsCount);
    for (int i = 0; i < argsCount; i++)
    {
        args[i].typeId = gen->GetArgTypeId(i);
        args[i].val = gen->GetArgAddress(i);
    }
    *static_cast<String*>(gen->GetAddressOfReturnLocation()) = formatString(*static_cast<String*>(gen->GetObject()), argsCount, args.Buffer());
}
static void Format_String_gen(asIScriptGeneric* gen)
{
    int argsCount = gen->GetArgCount();
    Vector<as_unkn_arg> args(argsCount - 1);
    for (int i = 1; i < argsCount; i++)
    {
        args[i - 1].typeId = gen->GetArgTypeId(i);
        args[i - 1].val = gen->GetArgAddress(i);
    }
    *static_cast<String*>(gen->GetAddressOfReturnLocation()) = formatString(*static_cast<String*>(gen->GetArgAddress(0)), argsCount - 1, args.Buffer());
}
#endif

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
#ifndef AS_MAX_PORTABILITY
    engine->RegisterObjectMethod("String", "String f()const", AS_FUNCTION_OBJFIRST(format_args0), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0)const", AS_FUNCTION_OBJFIRST(format_args1), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1)const", AS_FUNCTION_OBJFIRST(format_args2), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2)const", AS_FUNCTION_OBJFIRST(format_args3), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3)const", AS_FUNCTION_OBJFIRST(format_args4), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4)const", AS_FUNCTION_OBJFIRST(format_args5), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5)const",AS_FUNCTION_OBJFIRST(format_args6), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6)const", AS_FUNCTION_OBJFIRST(format_args7), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7)const", AS_FUNCTION_OBJFIRST(format_args8), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8)const", AS_FUNCTION_OBJFIRST(format_args9), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8,?&in a9)const",AS_FUNCTION_OBJFIRST(format_argsA), AS_CALL_CDECL_OBJFIRST);

    engine->RegisterGlobalFunction("String format(const String&in pattern)", AS_FUNCTION(format_args0), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0)", AS_FUNCTION(format_args1), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1)", AS_FUNCTION(format_args2), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2)", AS_FUNCTION(format_args3), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3)", AS_FUNCTION(format_args4), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4)", AS_FUNCTION(format_args5), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5)", AS_FUNCTION(format_args6), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6)", AS_FUNCTION(format_args7), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7)", AS_FUNCTION(format_args8), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8)", AS_FUNCTION(format_args9), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8,?&in a9)", AS_FUNCTION(format_argsA), AS_CALL_CDECL);
#else
    engine->RegisterObjectMethod("String", "String f()const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);
    engine->RegisterObjectMethod("String", "String f(?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8,?&in a9)const", asFUNCTION(String_Format_gen), asCALL_GENERIC);

    engine->RegisterGlobalFunction("String format(const String&in pattern)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
    engine->RegisterGlobalFunction("String format(const String&in pattern,?&in a0,?&in a1,?&in a2,?&in a3,?&in a4,?&in a5,?&in a6,?&in a7,?&in a8,?&in a9)", asFUNCTION(Format_String_gen), asCALL_GENERIC);
#endif
}

}
