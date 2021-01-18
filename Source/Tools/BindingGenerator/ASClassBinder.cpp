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
#include <iostream>
#include <regex>
#include <fstream>
#include <vector>

namespace ASBindingGenerator
{

static string _outputBasePath;

static shared_ptr<ASGeneratedFile_Members> _result_Members_A;
static shared_ptr<ASGeneratedFile_Members> _result_Members_B;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Constraint;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Ca_Cm;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Cn_Cz;
static shared_ptr<ASGeneratedFile_Members> _result_Members_D;
static shared_ptr<ASGeneratedFile_Members> _result_Members_E;
static shared_ptr<ASGeneratedFile_Members> _result_Members_F;
static shared_ptr<ASGeneratedFile_Members> _result_Members_G;
static shared_ptr<ASGeneratedFile_Members> _result_Members_H;
static shared_ptr<ASGeneratedFile_Members> _result_Members_I;
static shared_ptr<ASGeneratedFile_Members> _result_Members_J;
static shared_ptr<ASGeneratedFile_Members> _result_Members_K;
static shared_ptr<ASGeneratedFile_Members> _result_Members_L;
static shared_ptr<ASGeneratedFile_Members> _result_Members_M;
static shared_ptr<ASGeneratedFile_Members> _result_Members_N;
static shared_ptr<ASGeneratedFile_Members> _result_Members_O;
static shared_ptr<ASGeneratedFile_Members> _result_Members_P;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Q;
static shared_ptr<ASGeneratedFile_Members> _result_Members_R;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Sa_Sm;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Sn_Sz;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Ta_Tm;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Tn_Tz;
static shared_ptr<ASGeneratedFile_Members> _result_Members_U;
static shared_ptr<ASGeneratedFile_Members> _result_Members_V;
static shared_ptr<ASGeneratedFile_Members> _result_Members_W;
static shared_ptr<ASGeneratedFile_Members> _result_Members_X;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Y;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Z;
static shared_ptr<ASGeneratedFile_Members> _result_Members_Other;

static shared_ptr<ASGeneratedFile_Templates> _result_Templates;

static shared_ptr<ASGeneratedFile_Members> GetGeneratedFile(const string& className)
{
    if (StartsWith(className, "A"))
        return _result_Members_A;
 
    if (StartsWith(className, "B"))
        return _result_Members_B;
    
    if (StartsWith(className, "Constraint"))
        return _result_Members_Constraint;
    
    if (StartsWith(className, "C"))
    {
        if (className.length() < 2)
            return _result_Members_Ca_Cm;

        char secondChar = className[1];

        if (secondChar >= 'n')
            return _result_Members_Cn_Cz;

        return _result_Members_Ca_Cm;
    }
    
    if (StartsWith(className, "D"))
        return _result_Members_D;
    
    if (StartsWith(className, "E"))
        return _result_Members_E;
    
    if (StartsWith(className, "F"))
        return _result_Members_F;
    
    if (StartsWith(className, "G"))
        return _result_Members_G;
    
    if (StartsWith(className, "H"))
        return _result_Members_H;
    
    if (StartsWith(className, "I"))
        return _result_Members_I;
    
    if (StartsWith(className, "J"))
        return _result_Members_J;
    
    if (StartsWith(className, "K"))
        return _result_Members_K;
    
    if (StartsWith(className, "L"))
        return _result_Members_L;
    
    if (StartsWith(className, "M"))
        return _result_Members_M;
    
    if (StartsWith(className, "N"))
        return _result_Members_N;
    
    if (StartsWith(className, "O"))
        return _result_Members_O;

    if (StartsWith(className, "P"))
        return _result_Members_P;

    if (StartsWith(className, "Q"))
        return _result_Members_Q;

    if (StartsWith(className, "R"))
        return _result_Members_R;

    if (StartsWith(className, "S"))
    {
        if (className.length() < 2)
            return _result_Members_Sa_Sm;

        char secondChar = className[1];
        
        if (secondChar >= 'n')
            return _result_Members_Sn_Sz;
        
        return _result_Members_Sa_Sm;
    }

    if (StartsWith(className, "T"))
    {
        if (className.length() < 2)
            return _result_Members_Ta_Tm;

        char secondChar = className[1];
        
        if (secondChar >= 'n')
            return _result_Members_Tn_Tz;
        
        return _result_Members_Ta_Tm;
    }

    if (StartsWith(className, "U"))
        return _result_Members_U;

    if (StartsWith(className, "V"))
        return _result_Members_V;

    if (StartsWith(className, "W"))
        return _result_Members_W;

    if (StartsWith(className, "X"))
        return _result_Members_X;

    if (StartsWith(className, "Y"))
        return _result_Members_Y;

    if (StartsWith(className, "Z"))
        return _result_Members_Z;

    if (StartsWith(className, "W"))
        return _result_Members_W;

    return _result_Members_Other;
}

//static void RegisterStaticFunction(const ClassStaticFunctionAnalyzer& functionAnalyzer, shared_ptr<ASGeneratedFile_Members> result)
static void RegisterStaticFunction(const ClassStaticFunctionAnalyzer& functionAnalyzer, ASGeneratedFile_Base* result)
{
    result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";

    vector<ParamAnalyzer> params = functionAnalyzer.GetParams();
    vector<shared_ptr<FuncParamConv> > convertedParams;
    string outGlue;
    bool needWrapper = false;

    for (size_t i = 0; i < params.size(); i++)
    {
        ParamAnalyzer param = params[i];
        shared_ptr<FuncParamConv> conv = CppFunctionParamToAS(i, param);
        if (!conv->success_)
        {
            result->reg_ << "    // " << conv->errorMessage_ << "\n";
            return;
        }

        if (conv->NeedWrapper())
            needWrapper = true;

        convertedParams.push_back(conv);
    }

    shared_ptr<FuncReturnTypeConv> convertedReturn = CppFunctionReturnTypeToAS(functionAnalyzer.GetReturnType());
    if (!convertedReturn->success_)
    {
        result->reg_ << "    // " << GetLastErrorMessage() << "\n";
        return;
    }

    if (convertedReturn->needWrapper_)
        needWrapper = true;

    string declParams;

    for (shared_ptr<FuncParamConv> conv : convertedParams)
    {
        if (declParams.length() > 0)
            declParams += ", ";

        declParams += conv->asDecl_;
    }

    string asFunctionName = functionAnalyzer.GetName();
    string className = functionAnalyzer.GetClassName();

    if (needWrapper)
        result->glue_ << GenerateWrapper(functionAnalyzer, convertedParams, convertedReturn);

    string decl = convertedReturn->asReturnType_ + " " + asFunctionName + "(" + declParams + ")";

    result->reg_ << "    engine->SetDefaultNamespace(\"" << className << "\");\n";

    result->reg_ << "    engine->RegisterGlobalFunction(\"" << decl << "\", ";

    if (needWrapper)
        result->reg_ << "asFUNCTION(" << GenerateWrapperName(functionAnalyzer) << "), asCALL_CDECL);\n";
    else
        result->reg_ << Generate_asFUNCTIONPR(functionAnalyzer) << ", asCALL_CDECL);\n";

    result->reg_ << "    engine->SetDefaultNamespace(\"\");\n";
}

static void RegisterRefCountedConstructor(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion)
{
    string className = functionAnalyzer.GetClassName();
    string wrapperName = GenerateWrapperName(functionAnalyzer, templateVersion);
    string header = functionAnalyzer.GetClass().GetHeaderFile();
    string insideDefine = InsideDefine(header);

    string args = ExtractCleanedFunctionArgsstring(functionAnalyzer.GetMemberdef());

    //shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(functionAnalyzer.GetClass().GetClassName());
    ASGeneratedFile_Base* result = templateVersion ? (ASGeneratedFile_Base*)_result_Templates.get() : (ASGeneratedFile_Base*)GetGeneratedFile(functionAnalyzer.GetClass().GetClassName()).get();

    bool firstContext = StartsWith(args, "Context *context");
    if (firstContext)
    {
        args = CutStart(args, "Context *context");
        args = CutStart(args, ", ");
    }
    else if (args.find("Context") != string::npos)
    {
        result->reg_ <<
            "    // " << functionAnalyzer.GetLocation() << "\n"
            "    // Error: context can be only first\n";
        return;
    }

    string cppParamsNames = functionAnalyzer.JoinParamsNames(firstContext);

    if (firstContext)
    {
        if (cppParamsNames.length() > 0)
            cppParamsNames = ", " + cppParamsNames;
        cppParamsNames = "GetScriptContext()" + cppParamsNames;
    }

    string decl = "";
    vector<ParamAnalyzer> params = functionAnalyzer.GetParams();
    for (unsigned i = 0; i < params.size(); i++)
    {
        ParamAnalyzer param = params[i];

        if (i == 0 && firstContext)
        {
            assert(param.GetType().ToString() == "Context*");
            continue;
        }

        if (decl.length() > 0)
            decl += ", ";

        bool outSuccess;
        decl += CppTypeToAS(param.GetType(), false, outSuccess);

        string defval = param.GetDefval();
        if (!defval.empty())
        {
            defval = CppValueToAS(defval);
            defval = ReplaceAll(defval, "\"", "\\\"");
            decl += /*" " + param.GetDeclname() +*/ " = " + defval;
        }

        if (!outSuccess)
        {
            result->reg_ <<
                "    // " << functionAnalyzer.GetLocation() << "\n"
                "    // " << GetLastErrorMessage() << "\n";
            return;
        }
    }

    decl = className + "@+ f(" + decl + ")";

    if (templateVersion)
    {
        result->reg_ <<
            "    // " << functionAnalyzer.GetLocation() << "\n"
            "    {\n"
            "        String declFactory(String(className) + \"@ f()\");\n"
            "        engine->RegisterObjectBehaviour(className, "
            "asBEHAVE_FACTORY, "
            "declFactory.CString(), "
            "asFUNCTION(" << wrapperName << "), "
            "asCALL_CDECL);\n"
            "    }\n";
    }
    else
    {
        result->reg_ <<
            "    // " << functionAnalyzer.GetLocation() << "\n"
            "    engine->RegisterObjectBehaviour("
            "\"" << className << "\", "
            "asBEHAVE_FACTORY, "
            "\"" << decl << "\", "
            "asFUNCTION(" << wrapperName << "), "
            "asCALL_CDECL);\n";
    }

    if (!insideDefine.empty())
        result->glue_ << "#ifdef " << insideDefine << "\n";

    result->glue_ <<
        "// " << functionAnalyzer.GetLocation() << "\n"
        "static " << className << "* " << wrapperName << "(" << args << ")\n"
        "{\n"
        "    return new " << className << "(" << cppParamsNames << ");\n"
        "}\n";

    if (!insideDefine.empty())
        result->glue_ << "#endif\n";

    result->glue_ << "\n";
}

static void RegisterValueConstructor(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion)
{
    string header = functionAnalyzer.GetClass().GetHeaderFile();
    string insideDefine = InsideDefine(header);
    string className = functionAnalyzer.GetClassName();
    string wrapperName = GenerateWrapperName(functionAnalyzer, templateVersion);
    
    string args = ExtractCleanedFunctionArgsstring(functionAnalyzer.GetMemberdef());

    shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(className);

    bool isDefaultConstructor = args.empty();

    if (isDefaultConstructor)
        return;

    stringstream& reg = result->reg_;
    stringstream& glue = result->glue_;

    string decl = "";
    vector<ParamAnalyzer> params = functionAnalyzer.GetParams();
    for (ParamAnalyzer param : params)
    {
        if (decl.length() > 0)
            decl += ", ";

        bool outSuccess;
        decl += CppTypeToAS(param.GetType(), false, outSuccess);

        string defval = param.GetDefval();
        if (!defval.empty())
        {
            defval = CppValueToAS(defval);
            defval = ReplaceAll(defval, "\"", "\\\"");
            decl += /*" " + param.GetDeclname() +*/ " = " + defval;
        }

        if (!outSuccess)
        {
            if (isDefaultConstructor && !insideDefine.empty())
                reg << "#ifdef " << insideDefine << "\n";
            
            reg <<
                "    // " << functionAnalyzer.GetLocation() << "\n"
                "    // " << GetLastErrorMessage() << "\n";
            
            if (isDefaultConstructor && !insideDefine.empty())
                reg << "#endif\n";
            
            return;
        }
    }
    decl = "void f(" + decl + ")";

    if (isDefaultConstructor && !insideDefine.empty())
        reg << "#ifdef " << insideDefine << "\n";

    reg <<
        "    // " << functionAnalyzer.GetLocation() << "\n"
        "    engine->RegisterObjectBehaviour("
        "\"" << className << "\", "
        "asBEHAVE_CONSTRUCT, "
        "\"" << decl << "\", "
        "asFUNCTION(" << wrapperName << "), "
        "asCALL_CDECL_OBJFIRST);\n";

    if (isDefaultConstructor && !insideDefine.empty())
        reg << "#endif\n";

    if (isDefaultConstructor && !insideDefine.empty())
        glue << "#ifdef " << insideDefine << "\n";

    glue <<
        "// " << functionAnalyzer.GetLocation() << "\n"
        "static void " << wrapperName << "(" << className << "* ptr";

    if (args.length() > 0)
        glue << ", " << args;

    glue << ")\n"
        "{\n"
        "    new(ptr) " << className << "(" << functionAnalyzer.JoinParamsNames() << ");\n"
        "}\n";

    if (isDefaultConstructor && !insideDefine.empty())
        glue << "#endif\n";

    glue << "\n";

    if (isDefaultConstructor)
        Result::AddHeader(header);
}

static void TryRegisterImplicitlyDeclaredAssignOperator(const ClassAnalyzer& classAnalyzer)
{
    string className = classAnalyzer.GetClassName();
    shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(className);
    
    result->reg_ <<
        "    // " << className << "& " << className << "::operator=(const " << className << "&) | Possible implicitly-declared\n"
        "    RegisterImplicitlyDeclaredAssignOperatorIfPossible<" << className << ">(engine, \"" << className << "\");\n";
}

// Some required methods can not be bound automatically when processing class because implicitly-declared
static void RegisterImplicitlyDeclaredMethods(const ClassAnalyzer& classAnalyzer)
{
    if (!classAnalyzer.ContainsFunction("operator="))
        TryRegisterImplicitlyDeclaredAssignOperator(classAnalyzer);

    // No need register impicitly declared copy constructor when registered opAssign operator
}

static void RegisterComparisonOperator(const ClassAnalyzer& classAnalyzer)
{
    string className = classAnalyzer.GetClassName();
    string wrapperName = className + "_Comparison";
    string operatorLessLocation = classAnalyzer.GetFunction("operator<")->GetLocation();
    string operatorGreaterLocation = classAnalyzer.GetFunction("operator>")->GetLocation();
    shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(className);

    result->glue_ <<
        "// " << operatorLessLocation << "\n"
        "// " << operatorGreaterLocation << "\n"
        "static int " << wrapperName << "(const " << className << "& lhs, const " << className << "& rhs)\n"
        "{\n"
        "    if (lhs < rhs)\n"
        "        return -1;\n\n"
        "    if (lhs > rhs)\n"
        "        return 1;\n\n"
        "    return 0;\n"
        "}\n\n";

    result->reg_ <<
        "    // " << operatorLessLocation << "\n"
        "    // " << operatorGreaterLocation << "\n"
        "    engine->RegisterObjectMethod(\"" << className << "\", \"int opCmp(const " << className << "&in) const\", asFUNCTION(" << wrapperName << "), asCALL_CDECL_OBJFIRST);\n";
}

static void RegisterAddReleaseRef(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion)
{
    string className = functionAnalyzer.GetClassName();
    //shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(className);
    ASGeneratedFile_Base* result = templateVersion ? (ASGeneratedFile_Base*)_result_Templates.get() : (ASGeneratedFile_Base*)GetGeneratedFile(functionAnalyzer.GetClass().GetClassName()).get();
    string functionName = functionAnalyzer.GetName();
    string behaviour = (functionName == "AddRef") ? "asBEHAVE_ADDREF" : "asBEHAVE_RELEASE";
    string methodpr = Generate_asMETHODPR(functionAnalyzer, templateVersion);

    result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";

    if (templateVersion)
        result->reg_ << "    engine->RegisterObjectBehaviour(className, " << behaviour << ", \"void f()\", "  << methodpr << ", asCALL_THISCALL);\n";
    else
        result->reg_ << "    engine->RegisterObjectBehaviour(\"" << className << "\", " << behaviour << ", \"void f()\", " << methodpr << ", asCALL_THISCALL);\n";
}

static void RegisterFakeAddReleaseRef(const ClassAnalyzer& classAnalyzer)
{
    string className = classAnalyzer.GetClassName();
    shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(className);

    result->reg_ <<
        "    engine->RegisterObjectBehaviour(\"" << className << "\", asBEHAVE_ADDREF, \"void f()\", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);\n"
        "    engine->RegisterObjectBehaviour(\"" << className << "\", asBEHAVE_RELEASE, \"void f()\", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);\n";
}

// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_script_class_ops.html
string CppMethodNameToAS(const ClassFunctionAnalyzer& functionAnalyzer, bool& outSuccess)
{
    string name = functionAnalyzer.GetName();

    if (name == "operator=")
    {
        outSuccess = true;
        return "opAssign";
    }

    if (name == "operator+")
    {
        outSuccess = true;
        return "opAdd";
    }

    if (name == "operator-")
    {
        outSuccess = true;

        if (!functionAnalyzer.GetParams().size()) // If no params
            return "opNeg";               // then unary minus
        else
            return "opSub";
    }

    if (name == "operator*")
    {
        outSuccess = true;
        return "opMul";
    }
    
    if (name == "operator/")
    {
        outSuccess = true;
        return "opDiv";
    }
    
    if (name == "operator+=")
    {
        outSuccess = true;
        return "opAddAssign";
    }
    
    if (name == "operator-=")
    {
        outSuccess = true;
        return "opSubAssign";
    }
    
    if (name == "operator*=")
    {
        outSuccess = true;
        return "opMulAssign";
    }
    
    if (name == "operator/=")
    {
        outSuccess = true;
        return "opDivAssign";
    }
    
    if (name == "operator==")
    {
        outSuccess = true;
        return "opEquals";
    }

    if (name == "operator[]")
    {
        outSuccess = true;
        return "opIndex";
    }

    // Conversion to another type operator
    if (StartsWith(name, "operator "))
    {
        outSuccess = true;

        if (functionAnalyzer.IsExplicit())
            return "opConv";
        else
            return "opImplConv";
    }

    if (name == "operator!=")
    {
        outSuccess = false;
        SetLastErrorMessage("Only operator== is needed");
        return "IGNORED";
    }

    if (name == "operator<")
    {
        outSuccess = false;
        SetLastErrorMessage("Registerd as opCmp separately");
        return "IGNORED";
    }

    if (name == "operator>")
    {
        outSuccess = false;
        SetLastErrorMessage("Registerd as opCmp separately");
        return "IGNORED";
    }

    outSuccess = true;
    return name;
}

// Iterate over overrided funcions
static bool HaveMark(const ClassFunctionAnalyzer& functionAnalyzer, const string& mark)
{
    if (Contains(functionAnalyzer.GetComment(), mark))
        return true;

    shared_ptr<ClassFunctionAnalyzer> reimplements = functionAnalyzer.Reimplements();

    if (!reimplements)
        return false;

    return HaveMark(*reimplements, mark);
}

// Can return BIND_AS_ALIAS_xxxx or BIND_AS_PROPERTY
// Return "" if no this marks
static string GetPropertyMark(ClassFunctionAnalyzer function)
{
    string comment = function.GetComment();

    smatch match;
    regex_match(comment, match, regex(".*\\b(BIND_AS_ALIAS_.+?)\\b.*"));
    if (match.size() == 2)
        return match[1].str();

    regex_match(comment, match, regex(".*\\bBIND_AS_PROPERTY\\b.*"));
    if (match.size() == 1)
        return "BIND_AS_PROPERTY";

    shared_ptr<ClassFunctionAnalyzer> reimplements = function.Reimplements();

    if (!reimplements)
        return "";

    return GetPropertyMark(*reimplements);
}

// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_reg_objprop.html
static string CppMethodNameToASProperty(const ClassFunctionAnalyzer& functionAnalyzer, bool& outSuccess)
{
    string name = functionAnalyzer.GetName();

    if (StartsWith(name, "Is") || StartsWith(name, "Get"))
    {
        outSuccess = true;
        string result = CutStart(name, "Is");
        result = CutStart(result, "Get");
        result = "get_" + FirstCharToLower(result);
        return result;
    }

    if (StartsWith(name, "Set"))
    {
        outSuccess = true;
        string result = CutStart(name, "Set");
        result = "set_" + FirstCharToLower(result);
        return result;
    }

    if (functionAnalyzer.CanBeGetProperty())
    {
        outSuccess = true;
        string result = name;
        result = "get_" + FirstCharToLower(result);
        return result;
    }

    if (functionAnalyzer.CanBeSetProperty())
    {
        outSuccess = true;
        string result = name;
        result = "set_" + FirstCharToLower(result);
        return result;
    }

    outSuccess = false;
    SetLastErrorMessage("ERROR: Can not be property");
    return "ERROR";
}

static void RegisterMethod(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion)
{
    if (functionAnalyzer.IsDefine()) // URHO3D_OBJECT
        return; 
    
    if (!functionAnalyzer.IsPublic())
        return;

    if (functionAnalyzer.IsParentDestructor())
        return;

    if (functionAnalyzer.IsParentConstructor())
        return;

    //shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(functionAnalyzer.GetClass().GetClassName());
    ASGeneratedFile_Base* result = templateVersion ? (ASGeneratedFile_Base*)_result_Templates.get() : (ASGeneratedFile_Base*)GetGeneratedFile(functionAnalyzer.GetClass().GetClassName()).get();

    if (HaveMark(functionAnalyzer, "NO_BIND"))
    {
        result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";
        result->reg_ << "    // Not registered because have @nobind mark\n";
        return;
    }

    if (HaveMark(functionAnalyzer, "MANUAL_BIND"))
    {
        result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";
        result->reg_ << "    // Not registered because have @manualbind mark\n";
        return;
    }

    if (functionAnalyzer.IsTemplate())
    {
        result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";
        result->reg_ << "    // Not registered because template\n";
        return;
    }

    if (functionAnalyzer.IsStatic())
    {
        ClassStaticFunctionAnalyzer classStaticFunctionAnalyzer(functionAnalyzer.GetClass(), functionAnalyzer.GetMemberdef());
        RegisterStaticFunction(classStaticFunctionAnalyzer, result);
        return;
    }

    if (functionAnalyzer.IsDeleted())
        return;

    /*if (function.IsPureVirtual()) // Register pure virtual function but not register constructor for this class
        return;*/

    // Do not register destructor for refcounted because object is deleted by himself
    if (functionAnalyzer.IsThisDestructor()
        && (functionAnalyzer.GetClass().IsRefCounted() || Contains(functionAnalyzer.GetClass().GetComment(), "FAKE_REF")))
    {
        return;
    }

    string functionName = functionAnalyzer.GetName();

    if (functionName == "operator!=")
        return;

    // Already registered as sigle function opCmp
    if (functionName == "operator<" || functionName == "operator>")
        return;

    if (functionName == "AddRef" || functionName == "ReleaseRef")
    {
        RegisterAddReleaseRef(functionAnalyzer, templateVersion);
        return;
    }

    if (functionAnalyzer.IsThisConstructor())
    {
        if (functionAnalyzer.GetClass().IsRefCounted() || Contains(functionAnalyzer.GetClass().GetComment(), "FAKE_REF"))
        {
            // Do not register construnctor for abstract class
            if (functionAnalyzer.GetClass().IsAbstract())
                return;

            RegisterRefCountedConstructor(functionAnalyzer, templateVersion);
        }
        else
        {
            RegisterValueConstructor(functionAnalyzer, templateVersion);
        }
        
        return;
    }

    if (functionAnalyzer.IsThisDestructor())
        return;

    result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";

    vector<ParamAnalyzer> params = functionAnalyzer.GetParams();
    vector<shared_ptr<FuncParamConv> > convertedParams;
    bool needWrapper = false;

    for (size_t i = 0; i < params.size(); i++)
    {
        ParamAnalyzer param = params[i];
        shared_ptr<FuncParamConv> conv = CppFunctionParamToAS(i, param);
        if (!conv->success_)
        {
            result->reg_ << "    // " << conv->errorMessage_ << "\n";
            return;
        }

        if (conv->NeedWrapper())
            needWrapper = true;

        convertedParams.push_back(conv);
    }

    shared_ptr<FuncReturnTypeConv> retConv = CppFunctionReturnTypeToAS(functionAnalyzer.GetReturnType());
    if (!retConv->success_)
    {
        result->reg_ << "    // " << retConv->errorMessage_ << "\n";
        return;
    }

    if (retConv->needWrapper_)
        needWrapper = true;

    string declParams = "";

    for (shared_ptr<FuncParamConv> conv : convertedParams)
    {
        if (declParams.length() > 0)
            declParams += ", ";

        declParams += conv->asDecl_;
    }

    string asReturnType = retConv->asReturnType_;

    string asFunctionName = functionAnalyzer.GetName();
    if (functionAnalyzer.IsConsversionOperator())
        asReturnType = CutStart(asFunctionName, "operator ");

    bool outSuccess;
    asFunctionName = CppMethodNameToAS(functionAnalyzer, outSuccess);

    if (!outSuccess)
    {
        result->reg_ << "    // " << GetLastErrorMessage() << "\n";
        return;
    }

    if (needWrapper)
        result->glue_ << GenerateWrapper(functionAnalyzer, templateVersion, convertedParams, retConv);

    string decl = asReturnType + " " + asFunctionName + "(" + declParams + ")";

    if (functionAnalyzer.IsConst())
        decl += " const";

    if (templateVersion)
        result->reg_ << "    engine->RegisterObjectMethod(className, \"" << decl << "\", ";
    else
        result->reg_ << "    engine->RegisterObjectMethod(\"" << functionAnalyzer.GetClassName() << "\", \"" << decl << "\", ";

    if (needWrapper)
        result->reg_ << "asFUNCTION(" << GenerateWrapperName(functionAnalyzer, templateVersion) << "), asCALL_CDECL_OBJFIRST);\n";
    else
        result->reg_ << Generate_asMETHODPR(functionAnalyzer, templateVersion) << ", asCALL_THISCALL);\n";

    // Also register as property if needed
    string propertyMark = GetPropertyMark(functionAnalyzer);
    if (!propertyMark.empty())
    {
        if (StartsWith(propertyMark, "BIND_AS_ALIAS_"))
        {
            asFunctionName = CutStart(propertyMark, "BIND_AS_ALIAS_");
        }
        else
        {
            asFunctionName = CppMethodNameToASProperty(functionAnalyzer, outSuccess);
            if (!outSuccess)
            {
                result->reg_ << "    // " << GetLastErrorMessage() << "\n";
                return;
            }
        }
        
        decl = asReturnType + " " + asFunctionName + "(" + declParams + ")";

        if (functionAnalyzer.IsConst())
            decl += " const";

        if (templateVersion)
            result->reg_ << "    engine->RegisterObjectMethod(className, \"" << decl << "\", ";
        else
            result->reg_ << "    engine->RegisterObjectMethod(\"" << functionAnalyzer.GetClassName() << "\", \"" << decl << "\", ";

        if (needWrapper)
            result->reg_ << "asFUNCTION(" << GenerateWrapperName(functionAnalyzer, templateVersion) << "), asCALL_CDECL_OBJFIRST);\n";
        else
            result->reg_ << Generate_asMETHODPR(functionAnalyzer, templateVersion) << ", asCALL_THISCALL);\n";
    }
}

static void RegisterClassVarAsProperty(ClassVariableAnalyzer& variable)
{
    if (!variable.IsPublic())
        return;

    shared_ptr<ASGeneratedFile_Members> result = GetGeneratedFile(variable.GetClassName());

    if (Contains(variable.GetComment(), "NO_BIND"))
    {
        result->reg_ << "    // " << variable.GetLocation() << "\n";
        result->reg_ << "    // Not registered because have @nobind mark\n";
        return;
    }

    if (Contains(variable.GetComment(), "MANUAL_BIND"))
    {
        result->reg_ << "    // " << variable.GetLocation() << "\n";
        result->reg_ << "    // Not registered because have @manualbind mark\n";
        return;
    }

    if (variable.IsStatic())
    {
        result->reg_ << "    // " << variable.GetLocation() << "\n";

        bool outSuccess;
        string asType = CppTypeToAS(variable.GetType(), false, outSuccess);
        if (variable.GetType().IsConst())
            asType = "const " + asType;

        asType = ReplaceAll(asType, "struct ", "");

        if (!outSuccess)
        {
            result->reg_ << "    // " << GetLastErrorMessage() << "\n";
            return;
        }

        string className = variable.GetClassName();

        result->reg_ <<
            "    engine->SetDefaultNamespace(\"" << className << "\");\n";

        result->reg_ <<
            "    engine->RegisterGlobalProperty("
            "\"" << asType << " " << variable.GetName() << "\", "
            "(void*)&" << className << "::" << variable.GetName() << ");\n";

        result->reg_ << "    engine->SetDefaultNamespace(\"\");\n";
    }
    else
    {

        result->reg_ << "    // " << variable.GetLocation() << "\n";

        if (variable.IsArray())
        {
            result->reg_ << "    // Not registered because array\n";
            return;
        }

        if (variable.GetType().IsPointer())
        {
            result->reg_ << "    // " << variable.GetType().ToString() << " can not be registered\n";
            return;
        }

        bool outSuccess;
        string propType = CppTypeToAS(variable.GetType(), false, outSuccess);

        if (!outSuccess)
        {
            result->reg_ << "    // " << GetLastErrorMessage() << "\n";
            return;
        }

        string varName = variable.GetName();
        assert(!varName.empty());
        string propName = CutEnd(varName, "_");

        string className = variable.GetClassName();

        result->reg_ <<
            "    engine->RegisterObjectProperty("
            "\"" << className << "\", "
            "\"" << propType << " " << propName << "\", "
            "offsetof(" << className << ", " << varName << "));\n";
    }
}

static void RegisterObjectMembers(const ClassAnalyzer& classAnalyzer, bool templateVersion)
{
    string header = classAnalyzer.GetHeaderFile();
    
    ASGeneratedFile_Base* result = templateVersion ? (ASGeneratedFile_Base*)_result_Templates.get() : (ASGeneratedFile_Base*)GetGeneratedFile(classAnalyzer.GetClassName()).get();

    Result::AddHeader(header);

    string insideDefine = InsideDefine(header);
    if (!insideDefine.empty())
        result->reg_ << "#ifdef " << insideDefine << "\n";

    vector<ClassVariableAnalyzer> variables = classAnalyzer.GetVariables();
    for (ClassVariableAnalyzer variable : variables)
        RegisterClassVarAsProperty(variable);

    vector<ClassFunctionAnalyzer> functions = classAnalyzer.GetFunctions();
    for (ClassFunctionAnalyzer function : functions)
        RegisterMethod(function, templateVersion);

    RegisterImplicitlyDeclaredMethods(classAnalyzer);

    // 2 operators is replaced by single function opCmp
    if (classAnalyzer.ContainsFunction("operator>") || classAnalyzer.ContainsFunction("operator>"))
        RegisterComparisonOperator(classAnalyzer);

    if (Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        RegisterFakeAddReleaseRef(classAnalyzer);

    vector<ClassAnalyzer> classList = classAnalyzer.GetAllBaseClasses();
    classList.push_back(classAnalyzer); // Also add current class to list

    string className = classAnalyzer.GetClassName();

    for (ClassAnalyzer& cl : classList)
    {
        string clName = cl.GetClassName();

        result->reg_ << "#ifdef REGISTER_MANUAL_PART_" << clName << "\n";

        if (templateVersion)
            result->reg_ << "    REGISTER_MANUAL_PART_" << clName << "(T, className)\n";
        else
            result->reg_ << "    REGISTER_MANUAL_PART_" << clName << "(" << className << ", \"" << className << "\")\n";

        result->reg_ << "#endif\n";
    }

    if (classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF"))
    {
        vector<ClassAnalyzer> baseClasses = classAnalyzer.GetAllBaseClasses();
        for (ClassAnalyzer baseClass : baseClasses)
        {
            if (baseClass.IsRefCounted() || Contains(baseClass.GetComment(), "FAKE_REF"))
            {
                string baseClassName = baseClass.GetClassName();

                if (templateVersion)
                    result->reg_ << "    RegisterSubclass<" << baseClassName << ", T>(engine, \"" << baseClassName << "\", className);\n";
                else
                    result->reg_ << "    RegisterSubclass<" << baseClassName << ", " << className << ">(engine, \"" << baseClassName << "\", \"" << className << "\");\n";
            }
        }

        // In template also add current class
        if (templateVersion)
            result->reg_ << "    RegisterSubclass<" << className << ", T>(engine, \"" << className << "\", className);\n";
    }

    /*if (!analyzer.IsRefCounted()) // Executed also for FAKE_REF
    // TODO refcounted <=> value conversion if refcounted is chield value
    {
        vector<ClassAnalyzer> baseClasses = analyzer.GetAllBaseClasses();
        for (ClassAnalyzer baseClass : baseClasses)
        {
            if (!baseClass.IsRefCounted()) // Executed also for FAKE_REF
            {
                ASResult::reg_ << "    RegisterSubclassValue<" << baseClass.GetClassName()
                    << ", " << analyzer.GetClassName() << ">(engine, "
                    << "\"" << baseClass.GetClassName() << "\", "
                    << "\"" << analyzer.GetClassName() << "\");\n";
            }
        }
    }
    */

    if (!insideDefine.empty())
        result->reg_ << "#endif\n";

    if (!templateVersion)
        result->reg_ << "\n";
}

// Only template version
static void RegisterObjectType(const ClassAnalyzer& classAnalyzer/*, bool templateVersion*/)
{
    string header = classAnalyzer.GetHeaderFile();

    ASGeneratedFile_Base* result = (ASGeneratedFile_Base*)_result_Templates.get();

    Result::AddHeader(header);

    string insideDefine = InsideDefine(header);
    if (!insideDefine.empty())
        result->reg_ << "#ifdef " << insideDefine << "\n";

    result->reg_ << "    // " + classAnalyzer.GetLocation() + "\n";

    string className = classAnalyzer.GetClassName();

    if (classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF"))
    {
        //if (templateVersion)
            result->reg_ << "    engine->RegisterObjectType(className, 0, asOBJ_REF);\n";
        //else
          //  result->reg_ << "    engine->RegisterObjectType(\"" << className << "\", 0, asOBJ_REF);\n";
    }
    else // Value type
    {
        // TODO templateversion

       /* string flags = "asOBJ_VALUE | asGetTypeTraits<" + className + ">()";

        if (classAnalyzer.IsPod())
        {
            flags += " | asOBJ_POD";

            if (classAnalyzer.AllFloats())
                flags += " | asOBJ_APP_CLASS_ALLFLOATS";
            else if (classAnalyzer.AllInts())
                flags += " | asOBJ_APP_CLASS_ALLINTS";
        }

        result->reg_ << "    engine->RegisterObjectType(\"" << className << "\", sizeof(" << className << "), " << flags << ");\n";*/
    }

    if (!insideDefine.empty())
        result->reg_ << "#endif\n";
}

static void ProcessClass(const ClassAnalyzer& classAnalyzer, bool templateVersion)
{
    if (classAnalyzer.IsInternal())
        return;

    if (classAnalyzer.IsAbstract() && !(classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF")))
        return;
    
    if (Contains(classAnalyzer.GetComment(), "NO_BIND"))
    {
        //_result_Classes->reg_ << "    // " << classAnalyzer.GetLocation() << "\n";
        //_result_Classes->reg_ << "    // Not registered because have @nobind mark\n";
        return;
    }

    if (Contains(classAnalyzer.GetComment(), "MANUAL_BIND"))
    {
        //_result_Classes->reg_ << "    // " << classAnalyzer.GetLocation() << "\n";
        //_result_Classes->reg_ << "    // Not registered because have @manualbind mark\n";
        return;
    }

    string header = classAnalyzer.GetHeaderFile();
    if (IsIgnoredHeader(header))
    {
        Result::AddHeader(header);
        return;
    }

    if (classAnalyzer.IsTemplate())
        return;

    if (templateVersion)
        _result_Templates->reg_ << "template <class T> void Register" << classAnalyzer.GetClassName() << "(asIScriptEngine* engine, const char* className)\n{\n";

    if (templateVersion)
        RegisterObjectType(classAnalyzer);

    RegisterObjectMembers(classAnalyzer, templateVersion);

    if (templateVersion)
        _result_Templates->reg_ << "}\n\n";
}

void ProcessAllClasses(const string& outputBasePath)
{
    _outputBasePath = outputBasePath;

    _result_Members_A = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_A.cpp", "ASRegisterGenerated_Members_A");
    _result_Members_B = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_B.cpp", "ASRegisterGenerated_Members_B");
    _result_Members_Constraint = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Constraint.cpp", "ASRegisterGenerated_Members_Constraint");
    _result_Members_Ca_Cm = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Ca_Cm.cpp", "ASRegisterGenerated_Members_Ca_Cm");
    _result_Members_Cn_Cz = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Cn_Cz.cpp", "ASRegisterGenerated_Members_Cn_Cz");
    _result_Members_D = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_D.cpp", "ASRegisterGenerated_Members_D");
    _result_Members_E = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_E.cpp", "ASRegisterGenerated_Members_E");
    _result_Members_F = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_F.cpp", "ASRegisterGenerated_Members_F");
    _result_Members_G = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_G.cpp", "ASRegisterGenerated_Members_G");
    _result_Members_H = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_H.cpp", "ASRegisterGenerated_Members_H");
    _result_Members_I = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_I.cpp", "ASRegisterGenerated_Members_I");
    _result_Members_J = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_J.cpp", "ASRegisterGenerated_Members_J");
    _result_Members_K = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_K.cpp", "ASRegisterGenerated_Members_K");
    _result_Members_L = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_L.cpp", "ASRegisterGenerated_Members_L");
    _result_Members_M = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_M.cpp", "ASRegisterGenerated_Members_M");
    _result_Members_N = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_N.cpp", "ASRegisterGenerated_Members_N");
    _result_Members_O = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_O.cpp", "ASRegisterGenerated_Members_O");
    _result_Members_P = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_P.cpp", "ASRegisterGenerated_Members_P");
    _result_Members_Q = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Q.cpp", "ASRegisterGenerated_Members_Q");
    _result_Members_R = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_R.cpp", "ASRegisterGenerated_Members_R");
    _result_Members_Sa_Sm = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Sa_Sm.cpp", "ASRegisterGenerated_Members_Sa_Sm");
    _result_Members_Sn_Sz = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Sn_Sz.cpp", "ASRegisterGenerated_Members_Sn_Sz");
    _result_Members_Ta_Tm = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Ta_Tm.cpp", "ASRegisterGenerated_Members_Ta_Tm");
    _result_Members_Tn_Tz = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Tn_Tz.cpp", "ASRegisterGenerated_Members_Tn_Tz");
    _result_Members_U = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_U.cpp", "ASRegisterGenerated_Members_U");
    _result_Members_V = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_V.cpp", "ASRegisterGenerated_Members_V");
    _result_Members_W = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_W.cpp", "ASRegisterGenerated_Members_W");
    _result_Members_X = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_X.cpp", "ASRegisterGenerated_Members_X");
    _result_Members_Y = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Y.cpp", "ASRegisterGenerated_Members_Y");
    _result_Members_Z = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Z.cpp", "ASRegisterGenerated_Members_Z");
    _result_Members_Other = make_shared<ASGeneratedFile_Members>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Members_Other.cpp", "ASRegisterGenerated_Members_Other");
    _result_Templates = make_shared<ASGeneratedFile_Templates>(_outputBasePath + "/Source/Urho3D/AngelScript/Generated_Templates.h");

    // Sorting keys to make class order compiler independent
    vector<string> classIDs;
    classIDs.reserve(SourceData::classesByID_.size());
    for (pair<const string, xml_node>& it : SourceData::classesByID_)
        classIDs.push_back(it.first);
    sort(classIDs.begin(), classIDs.end());

    for (string classID : classIDs)
    {
        xml_node compounddef = SourceData::classesByID_[classID];
        ClassAnalyzer analyzer(compounddef);
        ProcessClass(analyzer, false);

        // Generate also template version of bindings
        if (Contains(analyzer.GetComment(), "TEMPLATE_VERSION"))
            ProcessClass(analyzer, true);
    }

    _result_Members_A->Save();
    _result_Members_B->Save();
    _result_Members_Constraint->Save();
    _result_Members_Ca_Cm->Save();
    _result_Members_Cn_Cz->Save();
    _result_Members_D->Save();
    _result_Members_E->Save();
    _result_Members_F->Save();
    _result_Members_G->Save();
    _result_Members_H->Save();
    _result_Members_I->Save();
    _result_Members_J->Save();
    _result_Members_K->Save();
    _result_Members_L->Save();
    _result_Members_M->Save();
    _result_Members_N->Save();
    _result_Members_O->Save();
    _result_Members_P->Save();
    _result_Members_Q->Save();
    _result_Members_R->Save();
    _result_Members_Sa_Sm->Save();
    _result_Members_Sn_Sz->Save();
    _result_Members_Ta_Tm->Save();
    _result_Members_Tn_Tz->Save();
    _result_Members_U->Save();
    _result_Members_V->Save();
    _result_Members_W->Save();
    _result_Members_X->Save();
    _result_Members_Y->Save();
    _result_Members_Z->Save();
    _result_Members_Other->Save();
    _result_Templates->Save();
}

}