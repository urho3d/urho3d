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

#include "ASResult.h"
#include "ASUtils.h"
#include "Tuning.h"
#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <cassert>

// Temporary bind only classes from list
static vector<string> onlyClasses
{
    "Vector3",
    "Vector2",
    "IntVector3",
    "IntVector2",
    "Vector4",
    "Matrix2",
    "Matrix3",
    "Matrix3x4",
    "Matrix4",
    "Quaternion",
    "IntRect",
    "Rect",
    "Plane",
    "Color",
    "Ray",
    "BoundingBox",
    "Frustum",
    "Polyhedron",
    "Sphere",
    "StringHash",
    //"Controls",
};

static string GenerateWrapperName(ClassFunctionAnalyzer& function)
{
    string functionName = function.GetName();
    functionName = ReplaceFirst(functionName, "~", "Destructor_");

    return function.GetClassName() + "_" + functionName
        + "_" + function.GetLine() + "_" + function.GetColumn();
}

static void RegisterValueConstructor(ClassFunctionAnalyzer& function)
{
    string className = function.GetClassName();
    string wrapperName = GenerateWrapperName(function);
    
    string args = function.GetMemberdef().child("argsstring").child_value();
    assert(!args.empty());
    assert(StartsWith(args, "("));
    size_t endPos = args.find_last_of(')'); // After ')' can be " override"
    assert(endPos != string::npos);
    args = args.substr(1, endPos - 1);

    ASResult::glue_ <<
        "// " << function.GetLocation() << "\n"
        "static void " << wrapperName << "(" << className << "* ptr";
    
    if (args.length() > 0)
        ASResult::glue_ << ", " << args;

    ASResult::glue_ << ")\n"
        "{\n"
        "    new(ptr) " << className << "(" << function.JoinParamsNames() << ");\n"
        "}\n\n";

    string decl = "";
    vector<ParamAnalyzer> params = function.GetParams();
    for (ParamAnalyzer param : params)
    {
        if (decl.length() > 0)
            decl += ", ";

        decl += CppTypeToAS(param.GetType(), false);
    }
    decl = "void f(" + decl + ")";

    ASResult::reg_ <<
        "    engine->RegisterObjectBehaviour("
        "\"" << className << "\", "
        "asBEHAVE_CONSTRUCT, "
        "\"" << decl << "\", "
        "asFUNCTION(" << wrapperName << "), "
        "asCALL_CDECL_OBJFIRST);\n";
}

static void RegisterValueDestructor(ClassFunctionAnalyzer& function)
{
    string className = function.GetClassName();
    string wrapperName = GenerateWrapperName(function);

    ASResult::glue_ <<
        "// " << function.GetLocation() << "\n"
        "static void " << wrapperName << "(" << className << "* ptr)\n"
        "{\n"
        "    ptr->~" << className << "();\n"
        "}\n\n";

    ASResult::reg_ <<
        "    engine->RegisterObjectBehaviour("
        "\"" << className << "\", "
        "asBEHAVE_DESTRUCT, "
        "\"void f()\", "
        "asFUNCTION(" << wrapperName << "), "
        "asCALL_CDECL_OBJFIRST);\n";
}

static void RegisterDefaultValueDestructor(const string& className)
{
    string wrapperName = className + "_Destructor";

    ASResult::glue_ <<
        "// " << className << "::~" << className << "()\n"
        "static void " << wrapperName << "(" << className << "* ptr)\n"
        "{\n"
        "    ptr->~" << className << "();\n"
        "}\n\n";

    ASResult::reg_ <<
        "    // " << className << "::~" << className << "()\n"
        "    engine->RegisterObjectBehaviour("
        "\"" << className << "\", "
        "asBEHAVE_DESTRUCT, "
        "\"void f()\", "
        "asFUNCTION(" << wrapperName << "), "
        "asCALL_CDECL_OBJFIRST);\n";
}

static void RegisterComparisonOperator(ClassAnalyzer analyzer)
{
    string className = analyzer.GetClassName();
    string wrapperName = className + "_Comparison";

    ClassFunctionAnalyzer operatorLess = analyzer.GetFunction("operator<");
    ClassFunctionAnalyzer operatorGreater = analyzer.GetFunction("operator>");

    ASResult::glue_ <<
        "// " << operatorLess.GetLocation() << "\n"
        "// " << operatorGreater.GetLocation() << "\n"
        "static int " << wrapperName << "(const " << className << "& lhs, const " << className << "& rhs)\n"
        "{\n"
        "    if (lhs < rhs)\n"
        "        return -1;\n"
        "    if (lhs > rhs)\n"
        "        return 1;\n"
        "    return 0;\n"
        "}\n\n";

    ASResult::reg_ <<
        "    // " << operatorLess.GetLocation() << "\n"
        "    // " << operatorGreater.GetLocation() << "\n"
        "    engine->RegisterObjectMethod("
        "\"" << className << "\", "
        "\"int opCmp(const " << className << "&in) const\", "
        "asFUNCTION(" << wrapperName << "), "
        "asCALL_CDECL_OBJFIRST);\n";
}

string CppMethodNameToAS(ClassFunctionAnalyzer& function)
{
    string name = function.GetName();

    if (name == "operator=")
        return "opAssign";

    if (name == "operator+")
        return "opAdd";

    if (name == "operator-")
    {
        if (!function.GetParams().size()) // If no params
            return "opNeg"; // then unary minus

        return "opSub";
    }

    if (name == "operator*")
        return "opMul";
    
    if (name == "operator/")
        return "opDiv";
    
    if (name == "operator+=")
        return "opAddAssign";
    
    if (name == "operator-=")
        return "opSubAssign";
    
    if (name == "operator*=")
        return "opMulAssign";
    
    if (name == "operator/=")
        return "opDivAssign";
    
    if (name == "operator==")
        return "opEquals";

    if (name == "operator[]")
        return "opIndex";
    
    if (name == "operator!=")
        return "IGNORED";

    if (name == "operator<")
        return "IGNORED";

    if (name == "operator>")
        return "IGNORED";

    return name;
}

string Generate_asMETHODPR(ClassFunctionAnalyzer& function)
{
    string cppParams = function.JoinParamsTypes();
    cppParams = "(" + cppParams + ")";
    if (function.IsConst())
        cppParams += " const";

    string returnType = function.GetReturnType().ToString();
    
    // https://github.com/doxygen/doxygen/issues/7732
    if (function.IsConsversionOperator())
        returnType = CutStart(function.GetName(), "operator ");

    return "asMETHODPR(" + function.GetClassName() + ", "
        + function.GetName() + ", " + cppParams + ", " + returnType + ")";
}

static void RegisterMethod(ClassFunctionAnalyzer& function)
{
    if (Contains(function.GetComment(), "BIND_IGNORE"))
        return;

    if (!function.IsPublic())
        return;

    if (function.IsStatic())
        return;

    if (function.GetName() == "operator!=")
        return;

    // Already registered as sigle function opCmp
    if (function.GetName() == "operator<" || function.GetName() == "operator>")
        return;

    if (function.GetClassName() == "Vector4") // TODO Remove test
    {
        string func = function.GetName();
    }

    ASResult::reg_ << "    // " << function.GetLocation() << "\n";

    if (function.IsConstrunctor())
    {
        if (function.GetClass().IsRefCounted()
            || Contains(function.GetClass().GetComment(), "FAKE_REF"))
        {
            
        }
        else
        {
            RegisterValueConstructor(function);
        }
    }
    else if (function.IsDestructor())
    {
        if (!function.GetClass().IsRefCounted())
            RegisterValueDestructor(function);
    }
    else
    {
        string decl = "";
        vector<ParamAnalyzer> params = function.GetParams();
        for (ParamAnalyzer param : params)
        {
            if (decl.length() > 0)
                decl += ", ";

            decl += CppTypeToAS(param.GetType(), false);
        }

        string returnType = CppTypeToAS(function.GetReturnType(), true);

        string functionName = function.GetName();
        if (function.IsConsversionOperator())
        {
            returnType = CutStart(functionName, "operator ");

            if (function.IsExplicit())
                functionName = "opConv";
            else
                functionName = "opImplConv";
        }
        else if (Contains(function.GetComment(), "BIND_AS_PROPERTY"))
        {
            if (function.CanBeGetProperty())
            {
                functionName = CutStart(functionName, "Get");
                functionName = "get_" + FirstCharToLower(functionName);
            }
            else if (function.CanBeSetProperty())
            {
                functionName = CutStart(functionName, "Set");
                functionName = "set_" + FirstCharToLower(functionName);
            }
            else
            {
                assert(false);
            }
        }
        else
        {
            functionName = CppMethodNameToAS(function);
        }

        decl = returnType + " " + functionName + "(" + decl + ")";

        if (function.IsConst())
            decl += " const";

        ASResult::reg_ <<
            "    engine->RegisterObjectMethod("
            "\"" << function.GetClassName() << "\", "
            "\"" << decl << "\", "
            << Generate_asMETHODPR(function) << ", "
            "asCALL_THISCALL);\n";
    }
}

static void RegisterProperty(ClassVariableAnalyzer& variable)
{
    if (Contains(variable.GetComment(), "BIND_IGNORE"))
        return;

    if (!variable.IsPublic())
        return;

    if (variable.IsStatic())
        return;

    ASResult::reg_ << "    // " << variable.GetLocation() << "\n";

    string propType = CppTypeToAS(variable.GetType(), false);
        
    string varName = variable.GetName();
    assert(!varName.empty());
    string propName = CutEnd(varName, "_");

    string className = variable.GetClassName();

    ASResult::reg_ <<
        "    engine->RegisterObjectProperty("
        "\"" << className << "\", "
        "\"" << propType << " " << propName << "\", "
        "offsetof(" << className << ", " << varName << "));\n";
}

static void RegisterObjectMembers(ClassAnalyzer& analyzer)
{
    string header = analyzer.GetHeaderFile();

    string insideDefine = InsideDefine(header);
    if (!insideDefine.empty())
        ASResult::reg_ << "#ifdef " << insideDefine << "\n";

    vector<ClassVariableAnalyzer> variables = analyzer.GetVariables();
    for (ClassVariableAnalyzer variable : variables)
        RegisterProperty(variable);

    vector<ClassFunctionAnalyzer> functions = analyzer.GetFunctions();
    for (ClassFunctionAnalyzer function : functions)
        RegisterMethod(function);

    if (!insideDefine.empty())
        ASResult::reg_ << "#endif\n";

    ASResult::reg_ << "\n";
}

static void RegisterObjectType(ClassAnalyzer analyzer)
{
    string header = analyzer.GetHeaderFile();

    string insideDefine = InsideDefine(header);
    if (!insideDefine.empty())
        ASResult::regFirst_ << "#ifdef " << insideDefine << "\n";

    ASResult::regFirst_ << "    // " + analyzer.GetLocation() + "\n";

    string className = analyzer.GetClassName();

    if (analyzer.IsRefCounted() || Contains(analyzer.GetComment(), "FAKE_REF"))
    {
        ASResult::regFirst_ <<
            "    engine->RegisterObjectType("
            "\"" << className << "\", "
            "0, "
            "asOBJ_REF"
            ");\n";
    }
    else // Value type
    {
        string flags = "asOBJ_VALUE | asGetTypeTraits<" + className + ">()";

        if (analyzer.IsPod())
        {
            flags += " | asOBJ_POD";

            if (analyzer.AllFloats())
                flags += " | asOBJ_APP_CLASS_ALLFLOATS";
            else if (analyzer.AllInts())
                flags += " | asOBJ_APP_CLASS_ALLINTS";
        }

        ASResult::regFirst_ <<
            "    engine->RegisterObjectType("
            "\"" << className << "\", "
            "sizeof(" << className << "), " <<
            flags <<
            ");\n";

        // Non-pod value classes required destructor
        // If destructor exists, it will be registered later when processing functions,
        // if not exists - registered here
        if (!analyzer.HasDestructor() && !analyzer.IsPod())
            RegisterDefaultValueDestructor(className);

        // 2 operators is replaced by single function opCmp
        if (analyzer.ContainsFunction("operator>") || analyzer.ContainsFunction("operator>"))
            RegisterComparisonOperator(analyzer);
    }

    if (!insideDefine.empty())
        ASResult::regFirst_ << "#endif\n";
}

static void ProcessClass(ClassAnalyzer analyzer)
{
    if (analyzer.IsInternal() || analyzer.IsAbstract() || analyzer.IsTemplate())
        return;

    if (Contains(analyzer.GetComment(), "BIND_IGNORE"))
        return;

    string header = analyzer.GetHeaderFile();
    if (IsIgnoredHeader(header))
    {
        ASResult::AddIgnoredHeader(header);
        return;
    }

    ASResult::AddHeader(header);

    RegisterObjectType(analyzer);
    RegisterObjectMembers(analyzer);
}

void ASProcessAllClasses()
{
    ASResult::regFirst_ << "    // Classes and structs\n";

    for (auto element : SourceData::classes_)
    {
        xml_node compounddef = element.second;
        ClassAnalyzer analyzer(compounddef);
        if (CONTAINS(onlyClasses, analyzer.GetClassName()))
            ProcessClass(analyzer);
    }

    // Space between regFirst_ and reg_
    ASResult::regFirst_ << "\n";
}
