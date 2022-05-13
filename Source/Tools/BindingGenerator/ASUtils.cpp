// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "ASUtils.h"
#include "Tuning.h"
#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <cassert>
#include <regex>

using namespace std;
using namespace pugi;

namespace ASBindingGenerator
{

// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_datatypes_primitives.html
// https://en.cppreference.com/w/cpp/language/types
string CppPrimitiveTypeToAS(const string& cppType)
{
    if (cppType == "bool")
        return "bool";

    if (cppType == "char" || cppType == "signed char" || cppType == "i8")
        return "int8";

    if (cppType == "unsigned char" || cppType == "u8")
        return "uint8";

    if (cppType == "short" || cppType == "i16")
        return "int16";

    if (cppType == "unsigned short" || cppType == "u16")
        return "uint16";

    if (cppType == "int" || cppType == "i32")
        return "int";

    if (cppType == "unsigned" || cppType == "unsigned int" || cppType == "u32")
        return "uint";

    if (cppType == "long long" || cppType == "i64")
        return "int64";

    if (cppType == "unsigned long long" || cppType == "u64")
        return "uint64";

    if (cppType == "float")
        return "float";

    if (cppType == "double")
        return "double";

    // Types below are registered in Manual.cpp
    
    if (cppType == "long")
        return "long";

    if (cppType == "unsigned long")
        return "ulong";

    if (cppType == "size_t")
        return "size_t";

    if (cppType == "SDL_JoystickID")
        return "SDL_JoystickID";

    throw Exception(cppType + " not a primitive type");
}

string JoinASDeclarations(const vector<ConvertedVariable>& vars)
{
    string result;

    for (const ConvertedVariable& var : vars)
    {
        if (!var.asDeclaration_.empty())
        {
            if (!result.empty())
                result += ", ";

            result += var.asDeclaration_;
        }
    }

    return result;
}

string JoinCppDeclarations(const string& firstCppDeclaration, const vector<ConvertedVariable>& vars)
{
    string result = firstCppDeclaration;

    for (const ConvertedVariable& var : vars)
    {
        if (!var.cppDeclaration_.empty())
        {
            if (!result.empty())
                result += ", ";

            result += var.cppDeclaration_;
        }
    }

    return result;
}

string JoinCppDeclarations(const vector<ConvertedVariable>& vars)
{
    return JoinCppDeclarations("", vars);
}

shared_ptr<EnumAnalyzer> FindEnum(const string& name)
{
    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<EnumAnalyzer> enumAnalyzers = namespaceAnalyzer.GetEnums();

    for (const EnumAnalyzer& enumAnalyzer : enumAnalyzers)
    {
        if (enumAnalyzer.GetTypeName() == name)
            return make_shared<EnumAnalyzer>(enumAnalyzer);
    }

    return shared_ptr<EnumAnalyzer>();
}

static bool IsUsing(const string& identifier)
{
    for (xml_node memberdef : SourceData::usings_)
    {
        UsingAnalyzer usingAnalyzer(memberdef);
        
        if (usingAnalyzer.GetName() == identifier)
            return true;
    }

    return false;
}

bool IsKnownCppType(const string& name)
{
    static vector<string> _knownTypes = {
        "void",
        "bool",
        "size_t",
        "char",
        "signed char",
        "i8",
        "unsigned char",
        "u8",
        "short",
        "i16",
        "unsigned short",
        "u16",
        "int",
        "i32",
        "long", // Size is compiler-dependent
        "unsigned",
        "unsigned int",
        "u32",
        "unsigned long", // Size is compiler-dependent
        "long long",
        "i64",
        "unsigned long long",
        "u64",
        "float",
        "double",
        "SDL_JoystickID",

        // TODO: Remove
        "VariantMap",
    };

    if (CONTAINS(_knownTypes, name))
        return true;

    if (SourceData::classesByName_.find(name) != SourceData::classesByName_.end())
        return true;

    if (SourceData::enums_.find(name) != SourceData::enums_.end())
        return true;

    if (EndsWith(name, "Flags"))
        return true;

    return false;
}

shared_ptr<ClassAnalyzer> FindClassByName(const string& name)
{
    auto it = SourceData::classesByName_.find(name);
    if (it != SourceData::classesByName_.end())
    {
        xml_node compounddef = it->second;
        return make_shared<ClassAnalyzer>(compounddef);
    }

    // using VariantVector = Vector<Variant>

    return shared_ptr<ClassAnalyzer>();
}

shared_ptr<ClassAnalyzer> FindClassByID(const string& id)
{
    auto it = SourceData::classesByID_.find(id);
    if (it != SourceData::classesByID_.end())
    {
        xml_node compounddef = it->second;
        return make_shared<ClassAnalyzer>(compounddef);
    }

    // using VariantVector = Vector<Variant>

    return shared_ptr<ClassAnalyzer>();
}

// Variable name can be empty for function return type
ConvertedVariable CppVariableToAS(const TypeAnalyzer& type, VariableUsage usage, const string& name, const string& defaultValue)
{
    ConvertedVariable result;

    if (usage == VariableUsage::PostfixIncDecParameter)
    {
        result.glue_ = "    " + type.ToString() + " " + name + "{};\n";
        return result;
    }

    if (type.IsRvalueReference() || type.IsDoublePointer() || type.IsRefToPointer())
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    string cppTypeName = type.GetNameWithTemplateParams();

    if (cppTypeName == "void")
    {
        if (usage == VariableUsage::FunctionReturn && !type.IsPointer())
        {
            result.asDeclaration_ = "void";
            result.cppDeclaration_ = "void";
            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    if (cppTypeName == "Context")
    {
        if (usage == VariableUsage::FunctionParameter && type.IsPointer())
        {
            result.glue_ = "    " + type.ToString() + " " + name + " = GetScriptContext();\n";
            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can used only as function parameter");
    }

    // Works with both Vector<String> and Vector<String>&
    if (cppTypeName == "Vector<String>" || cppTypeName == "StringVector")
    {
        // Works with both Vector<String> and Vector<String>&
        if (usage == VariableUsage::FunctionReturn && !type.IsPointer())
        {
            result.asDeclaration_ = "Array<String>@";
            result.cppDeclaration_ = "CScriptArray*";
            result.glue_ = "return VectorToArray<String>(result, \"Array<String>\");\n";
            return result;
        }

        if (usage == VariableUsage::FunctionParameter && type.IsConst() && type.IsReference())
        {
            string newCppVarName = name + "_conv";

            //result->asDecl_ = "String[]&";
            result.asDeclaration_ = "Array<String>@+";
            result.cppDeclaration_ = "CScriptArray* " + newCppVarName;
            result.glue_ = "    " + cppTypeName + " " + name + " = ArrayToVector<String>(" + newCppVarName + ");\n";

            if (!defaultValue.empty())
            {
                assert(defaultValue == "Vector< String >()");
                //result->asDecl_ += " = Array<String>()";
                result.asDeclaration_ += " = null";
            }

            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    smatch match;

    regex_match(cppTypeName, match, regex("SharedPtr<(\\w+)>"));
    if (!match.empty())
    {
        string cppSubtypeName = match[1].str();

        string asSubtypeName;

        try
        {
            asSubtypeName = CppPrimitiveTypeToAS(cppSubtypeName);
        }
        catch (...)
        {
            asSubtypeName = cppSubtypeName;
        }

        if (cppSubtypeName == "WorkItem") // TODO autodetect
            throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

        if (usage == VariableUsage::FunctionReturn)
        {
            result.asDeclaration_ = asSubtypeName + "@+";
            result.cppDeclaration_ = cppSubtypeName + "*";
            result.glue_ = "return result.Detach();\n";
            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    regex_match(cppTypeName, match, regex("Vector<SharedPtr<(\\w+)>>"));
    if (!match.empty())
    {
        string cppSubtypeName = match[1].str();

        string asSubtypeName;

        try
        {
            asSubtypeName = CppPrimitiveTypeToAS(cppSubtypeName);
        }
        catch (...)
        {
            asSubtypeName = cppSubtypeName;
        }

        if (cppSubtypeName == "WorkItem") // TODO autodetect
            throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

        if (usage == VariableUsage::FunctionReturn)
        {
            result.asDeclaration_ = "Array<" + asSubtypeName + "@>@";
            result.cppDeclaration_ = "CScriptArray*";

            // Which variant is correct/better?
#if 0
            result->glueResult_ = "return VectorToArray<SharedPtr<" + cppTypeName + ">>(result, \"Array<" + asTypeName + "@>@\");\n";
#else
            result.glue_ = "return VectorToHandleArray(result, \"Array<" + asSubtypeName + "@>\");\n";
#endif
            return result;
        }

        if (usage == VariableUsage::FunctionParameter && type.IsConst() && type.IsReference())
        {
            string newCppVarName = name + "_conv";
            result.asDeclaration_ = "Array<" + asSubtypeName + "@>@+";
            result.cppDeclaration_ = "CScriptArray* " + newCppVarName;
            result.glue_ = "    " + cppTypeName + " " + name + " = HandleArrayToVector<" + cppSubtypeName + ">(" + newCppVarName + ");\n";

            assert(defaultValue.empty()); // TODO: make

            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    regex_match(cppTypeName, match, regex("PODVector<(\\w+)\\*>"));
    if (!match.empty())
    {
        string cppSubtypeName = match[1].str();

        string asSubtypeName;

        try
        {
            asSubtypeName = CppPrimitiveTypeToAS(cppSubtypeName);
        }
        catch (...)
        {
            asSubtypeName = cppSubtypeName;
        }

        if (usage == VariableUsage::FunctionReturn)
        {
            result.asDeclaration_ = "Array<" + asSubtypeName + "@>@";
            result.cppDeclaration_ = "CScriptArray*";
            result.glue_ = "return VectorToHandleArray(result, \"Array<" + asSubtypeName + "@>\");\n";
            return result;
        }

        if (usage == VariableUsage::FunctionParameter && type.IsConst() && type.IsReference())
        {
            string newCppVarName = name + "_conv";
            result.asDeclaration_ = "Array<" + asSubtypeName + "@>@";
            result.cppDeclaration_ = "CScriptArray* " + newCppVarName;
            result.glue_ = "    " + cppTypeName + " " + name + " = ArrayToVector<" + cppSubtypeName + "*>(" + newCppVarName + ");\n";

            assert(defaultValue.empty()); // TODO: make

            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    regex_match(cppTypeName, match, regex("PODVector<(\\w+)>"));
    if (!match.empty())
    {
        string cppSubtypeName = match[1].str();

        string asSubtypeName;

        try
        {
            asSubtypeName = CppPrimitiveTypeToAS(cppSubtypeName);
        }
        catch (...)
        {
            asSubtypeName = cppSubtypeName;
        }

        if (usage == VariableUsage::FunctionReturn && type.IsConst() == type.IsReference())
        {
            result.asDeclaration_ = "Array<" + asSubtypeName + ">@";
            result.cppDeclaration_ = "CScriptArray*";
            result.glue_ = "return VectorToArray(result, \"Array<" + asSubtypeName + ">\");\n";
            return result;
        }

        if (usage == VariableUsage::FunctionParameter && type.IsConst() && type.IsReference())
        {
            string newCppVarName = name + "_conv";
            result.asDeclaration_ = "Array<" + asSubtypeName + ">@+";
            result.cppDeclaration_ = "CScriptArray* " + newCppVarName;
            result.glue_ = "    " + cppTypeName + " " + name + " = ArrayToVector<" + cppSubtypeName + ">(" + newCppVarName + ");\n";

            assert(defaultValue.empty()); // TODO: make

            return result;
        }

        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    if (!IsKnownCppType(cppTypeName))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    shared_ptr<ClassAnalyzer> analyzer = FindClassByName(cppTypeName);
    if (analyzer && analyzer->IsInternal())
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind bacause internal");

    if (analyzer && Contains(analyzer->GetComment(), "NO_BIND"))
        throw Exception("Error: type \"" + cppTypeName + "\" can not automatically bind bacause have @nobind mark");

    if (analyzer && analyzer->IsAbstract() && !(analyzer->IsRefCounted() || analyzer->IsNoCount()))
        throw Exception("Error: type \"" + cppTypeName + "\" can not bind bacause abstract value");

    // analyzer can be null for simple types (int, float) or if type "using VariantVector = Vector<Variant>"
    // TODO add to type info "IsUsing"
    // TODO add description to TypeAnalyzer::GetClass()

    if (IsUsing(cppTypeName) && cppTypeName != "VariantMap")
        throw Exception("Using \"" + cppTypeName + "\" can not automatically bind");

    string asTypeName;

    try
    {
        asTypeName = CppPrimitiveTypeToAS(cppTypeName);
    }
    catch (...)
    {
        asTypeName = cppTypeName;
    }

    if (Contains(asTypeName, '<'))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    if (Contains(type.ToString(), "::"))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind bacause internal");

    if (usage == VariableUsage::FunctionParameter && type.IsConst() && type.IsReference())
    {
        result.asDeclaration_ = "const " + asTypeName + "&in";
        result.cppDeclaration_ = type.ToString();

        if (!name.empty())
            result.cppDeclaration_ += " " + name;

        if (!defaultValue.empty())
        {
            string asDefaultValue = CppValueToAS(defaultValue);
            asDefaultValue = ReplaceAll(asDefaultValue, "\"", "\\\"");
            result.asDeclaration_ += " = " + asDefaultValue;
        }

        return result;
    }

    result.asDeclaration_ = asTypeName;

    if (type.IsReference())
    {
        result.asDeclaration_ += "&";
    }
    else if (type.IsPointer())
    {
        shared_ptr<ClassAnalyzer> analyzer = FindClassByName(cppTypeName);

        if (analyzer && (analyzer->IsRefCounted() || analyzer->IsNoCount()))
            result.asDeclaration_ = result.asDeclaration_  + "@" + (analyzer->IsNoCount() ? "" : "+");
        else
            throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    result.cppDeclaration_ = type.ToString();

    if (!name.empty())
        result.cppDeclaration_ += " " + name;

    if (usage == VariableUsage::FunctionReturn && type.IsConst() && !type.IsPointer())
        result.asDeclaration_ = "const " + result.asDeclaration_;

    if (!defaultValue.empty())
    {
        string asDefaultValue = CppValueToAS(defaultValue);
        asDefaultValue = ReplaceAll(asDefaultValue, "\"", "\\\"");
        result.asDeclaration_ += " = " + asDefaultValue;
    }

    return result;
}

string HideUnnamedType(const string& name)
{
    regex rgx("@\\d+");
    return regex_replace(name, rgx, "@?");
}

string CppTypeToAS(const TypeAnalyzer& type, TypeUsage typeUsage)
{
    if (Contains(type.GetName(), "@")) // Unnamed union inside class
        throw Exception("Error: type \"" + HideUnnamedType(type.ToString()) + "\" can not automatically bind");

    if (type.IsRvalueReference() || type.IsDoublePointer() || type.IsRefToPointer())
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    string cppTypeName = type.GetNameWithTemplateParams();

    if (cppTypeName == "Context" && typeUsage == TypeUsage::FunctionReturn)
        throw Exception("Error: type \"" + type.ToString() + "\" can not be returned");

    if (!IsKnownCppType(type.GetNameWithTemplateParams()))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    shared_ptr<ClassAnalyzer> analyzer = FindClassByName(type.GetNameWithTemplateParams());
    if (analyzer && analyzer->IsInternal())
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind bacause internal");

    if (analyzer && Contains(analyzer->GetComment(), "NO_BIND"))
        throw Exception("Error: type \"" + cppTypeName + "\" can not automatically bind bacause have @nobind mark");

    // analyzer can be null for simple types (int, float) or if type "using VariantVector = Vector<Variant>"
    // TODO add to type info "IsUsing"
    // TODO add description to TypeAnalyzer::GetClass()

    if (IsUsing(cppTypeName) && cppTypeName != "VariantMap")
        throw Exception("Using \"" + cppTypeName + "\" can not automatically bind");

    string asTypeName;
    
    try
    {
        asTypeName = CppPrimitiveTypeToAS(cppTypeName);
    }
    catch (...)
    {
        asTypeName = cppTypeName;
    }

    if (asTypeName == "void" && type.IsPointer())
        throw Exception("Error: type \"void*\" can not automatically bind");

    if (Contains(asTypeName, '<'))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");

    if (Contains(type.ToString(), "::"))
        throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind bacause internal");

    if (type.IsConst() && type.IsReference() && typeUsage == TypeUsage::FunctionParameter)
        return "const " + asTypeName + "&in";

    string result = asTypeName;

    if (type.IsReference())
    {
        result += "&";
    }
    else if (type.IsPointer())
    {
        shared_ptr<ClassAnalyzer> analyzer = FindClassByName(type.GetNameWithTemplateParams());

        if (analyzer && (analyzer->IsRefCounted() || analyzer->IsNoCount()))
            result = result + "@" + (analyzer->IsNoCount() ? "" : "+");
        else
            throw Exception("Error: type \"" + type.ToString() + "\" can not automatically bind");
    }

    if (typeUsage == TypeUsage::FunctionReturn && type.IsConst() && !type.IsPointer())
        result = "const " + result;

    return result;
}

string CppValueToAS(const string& cppValue)
{
    if (cppValue == "nullptr")
        return "null";

    if (cppValue == "Variant::emptyVariantMap")
        return "VariantMap()";

    if (cppValue == "NPOS")
        return "String::NPOS";

    return cppValue;
}

// =================================================================================

static string GenerateFunctionWrapperName(xml_node memberdef)
{
    TypeAnalyzer returnType = ExtractType(memberdef);
    string result = ExtractType(memberdef).ToString() + "_" + ExtractName(memberdef);
    vector<ParamAnalyzer> params = ExtractParams(memberdef);

    if (params.size() == 0)
    {
        result += "_void";
    }
    else
    {
        for (ParamAnalyzer param : params)
        {
            result += "_" + param.GetType().ToString();
        }
    }

    result = ReplaceAll(result, "=", "eq");
    result = ReplaceAll(result, "<", "les");
    result = ReplaceAll(result, ">", "gre");
    result = ReplaceAll(result, "*", "star");
    result = ReplaceAll(result, "/", "div");
    result = ReplaceAll(result, "+", "plus");
    result = ReplaceAll(result, "-", "min");
    result = ReplaceAll(result, "[", "lbr");
    result = ReplaceAll(result, "]", "rbr");
    result = ReplaceAll(result, ":", "col");
    result = ReplaceAll(result, " ", "sp");
    result = ReplaceAll(result, "&", "amp");

    return result;
}

string GenerateWrapperName(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    return GenerateFunctionWrapperName(functionAnalyzer.GetMemberdef());
}

string GenerateWrapperName(const ClassStaticFunctionAnalyzer& functionAnalyzer)
{
    return functionAnalyzer.GetClassName() + "_" + GenerateFunctionWrapperName(functionAnalyzer.GetMemberdef());
}

string GenerateWrapperName(const MethodAnalyzer& methodAnalyzer, bool templateVersion)
{
    if (templateVersion)
        return methodAnalyzer.GetClassName() + "_" + GenerateFunctionWrapperName(methodAnalyzer.GetMemberdef()) + "_template";
    else
        return methodAnalyzer.GetClassName() + "_" + GenerateFunctionWrapperName(methodAnalyzer.GetMemberdef());
}

// =================================================================================

string GenerateWrapper(const GlobalFunctionAnalyzer& functionAnalyzer, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn)
{
    string result;

    string glueReturnType = convertedReturn.cppDeclaration_;

    result =
        "static " + glueReturnType + " " + GenerateWrapperName(functionAnalyzer) + "(" + JoinCppDeclarations(convertedParams) + ")\n"
        "{\n";

    for (size_t i = 0; i < convertedParams.size(); i++)
        result += convertedParams[i].glue_;

    if (glueReturnType != "void")
        result += "    " + functionAnalyzer.GetReturnType().ToString() + " result = ";
    else
        result += "    ";

    result += functionAnalyzer.GetName() + "(" + functionAnalyzer.JoinParamsNames() + ");\n";

    if (!convertedReturn.glue_.empty())
        result += "    " + convertedReturn.glue_;
    else if (glueReturnType != "void")
        result += "    return result;\n";

    result += "}";

    return result;
}

string GenerateWrapper(const ClassStaticFunctionAnalyzer& functionAnalyzer, bool templateVersion, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn)
{
    string result = templateVersion ? "template <class T> " : "static ";
    string className = templateVersion ? "T" : functionAnalyzer.GetClassName();

    string glueReturnType = convertedReturn.cppDeclaration_;

    result +=
        glueReturnType + " " + GenerateWrapperName(functionAnalyzer) + "(" + JoinCppDeclarations(convertedParams) + ")\n"
        "{\n";

    for (size_t i = 0; i < convertedParams.size(); i++)
        result += convertedParams[i].glue_;

    if (glueReturnType != "void")
        result += "    " + functionAnalyzer.GetReturnType().ToString() + " result = ";
    else
        result += "    ";

    result += className + "::" + functionAnalyzer.GetName() + "(" + functionAnalyzer.JoinParamsNames() + ");\n";

    if (!convertedReturn.glue_.empty())
        result += "    " + convertedReturn.glue_;
    else if (glueReturnType != "void")
        result += "    return result;\n";

    result += "}\n";

    return result;
}

string GenerateWrapper(const MethodAnalyzer& methodAnalyzer, bool templateVersion, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn)
{
    string result = templateVersion ? "template <class T> " : "static ";
    string className = templateVersion ? "T" : methodAnalyzer.GetClassName();

    string glueReturnType = convertedReturn.cppDeclaration_;

    result +=
        glueReturnType + " " + GenerateWrapperName(methodAnalyzer, templateVersion) + "(" + JoinCppDeclarations(className + "* _ptr", convertedParams) + ")\n"
        "{\n";

    for (size_t i = 0; i < convertedParams.size(); i++)
        result += convertedParams[i].glue_;

    if (glueReturnType != "void")
        result += "    " + methodAnalyzer.GetReturnType().ToString() + " result = ";
    else
        result += "    ";

    result += "_ptr->" + methodAnalyzer.GetName() + "(" + methodAnalyzer.JoinParamsNames() + ");\n";

    if (!convertedReturn.glue_.empty())
        result += "    " + convertedReturn.glue_;
    else if (glueReturnType != "void")
        result += "    return result;\n";

    result += "}\n";

    return result;
}

string GenerateConstructorWrapper(const MethodAnalyzer& methodAnalyzer, const vector<ConvertedVariable>& convertedParams)
{
    string className = methodAnalyzer.GetClassName();

    string result =
        "static void " + GenerateWrapperName(methodAnalyzer) + "(" + JoinCppDeclarations(className + "* _ptr", convertedParams) + ")\n"
        "{\n";

    for (size_t i = 0; i < convertedParams.size(); i++)
        result += convertedParams[i].glue_;

    result +=
        "    new(_ptr) " + className + "(" + methodAnalyzer.JoinParamsNames() + ");\n"
        "}\n";

    return result;
}

string GenerateFactoryWrapper(const MethodAnalyzer& methodAnalyzer, const vector<ConvertedVariable>& convertedParams)
{
    string className = methodAnalyzer.GetClassName();

    string result =
        "static " + className + "* " + GenerateWrapperName(methodAnalyzer) + "(" + JoinCppDeclarations(convertedParams) + ")\n"
        "{\n";

    for (size_t i = 0; i < convertedParams.size(); i++)
        result += convertedParams[i].glue_;

    result +=
        "    return new " + className + "(" + methodAnalyzer.JoinParamsNames() + ");\n"
        "}\n";

    return result;
}

// =================================================================================

string Generate_asFUNCTIONPR(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    string functionName = functionAnalyzer.GetName();
    string cppParams = "(" + JoinParamsTypes(functionAnalyzer.GetMemberdef(), functionAnalyzer.GetSpecialization()) + ")";
    string returnType = functionAnalyzer.GetReturnType().ToString();
    return "AS_FUNCTIONPR(" + functionName + ", " + cppParams + ", " + returnType + ")";
}

string Generate_asFUNCTIONPR(const ClassStaticFunctionAnalyzer& functionAnalyzer, bool templateVersion)
{
    string className = functionAnalyzer.GetClassName();
    string functionName = functionAnalyzer.GetName();
    string cppParams = "(" + JoinParamsTypes(functionAnalyzer.GetMemberdef(), functionAnalyzer.GetSpecialization()) + ")";
    string returnType = functionAnalyzer.GetReturnType().ToString();
    
    if (templateVersion)
        return "AS_FUNCTIONPR(T::" + functionName + ", " + cppParams + ", " + returnType + ")";
    else
        return "AS_FUNCTIONPR(" + className + "::" + functionName + ", " + cppParams + ", " + returnType + ")";
}

string Generate_asMETHODPR(const MethodAnalyzer& methodAnalyzer, bool templateVersion)
{
    string className = methodAnalyzer.GetClassName();
    string functionName = methodAnalyzer.GetName();

    string cppParams = "(" + JoinParamsTypes(methodAnalyzer.GetMemberdef(), methodAnalyzer.GetSpecialization()) + ")";

    if (methodAnalyzer.IsConst())
        cppParams += " const";

    string returnType = methodAnalyzer.GetReturnType().ToString();
    
    if (templateVersion)
        return "AS_METHODPR(T, " + functionName + ", " + cppParams + ", " + returnType + ")";
    else
        return "AS_METHODPR(" + className + ", " + functionName + ", " + cppParams + ", " + returnType + ")";
}

} // namespace ASBindingGenerator
