// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "ASResult.h"
#include "ASUtils.h"
#include "Tuning.h"
#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <cassert>

using namespace std;

namespace ASBindingGenerator
{

static void ProcessEnum(const EnumAnalyzer& analyzer)
{
    if (analyzer.IsInternal())
        return;

    string header = analyzer.GetHeaderFile();
    Result::AddHeader(header);
    
    if (IsIgnoredHeader(header))
        return;

    ProcessedEnum processedEnum;
    processedEnum.name_ = analyzer.GetTypeName();
    processedEnum.insideDefine_ = InsideDefine(header);
    processedEnum.comment_ = analyzer.GetLocation();

    string comment = analyzer.GetComment();

    if (Contains(comment, "NO_BIND"))
    {
        processedEnum.registration_.push_back("// Not registered because have @nobind mark");
        Result::enums_.push_back(processedEnum);
        return;
    }

    if (Contains(comment, "MANUAL_BIND"))
    {
        processedEnum.registration_.push_back("// Not registered because have @manualbind mark");
        Result::enums_.push_back(processedEnum);
        return;
    }

    string enumTypeName = analyzer.GetTypeName();
    string cppEnumBaseType = analyzer.GetBaseType();
    string asEnumBaseType = CppPrimitiveTypeToAS(cppEnumBaseType);

    if (analyzer.IsClass()) // Scoped enumerations
    {
        processedEnum.registration_.push_back("engine->RegisterTypedef(\"" + enumTypeName + "\", \"" + asEnumBaseType + "\");");
        processedEnum.registration_.push_back("engine->SetDefaultNamespace(\"" + enumTypeName + "\");");

        for (const string& value : analyzer.GetEnumerators())
        {
            string constName = enumTypeName + "_" + value;
            processedEnum.glue_.push_back("static const " + cppEnumBaseType + " " + constName + " = static_cast<" + cppEnumBaseType + ">(" + enumTypeName + "::" + value + ");");
            processedEnum.registration_.push_back("engine->RegisterGlobalProperty(\"const " + asEnumBaseType + " " + value + "\", (void*)&" + constName + ");");
        }

        processedEnum.registration_.push_back("engine->SetDefaultNamespace(\"\");");
    }
    else // Unscoped enumerations
    {
        if (cppEnumBaseType == "int") // Enums in AngelScript can be only int
        {
            processedEnum.registration_.push_back("engine->RegisterEnum(\"" + enumTypeName + "\");");

            for (const string& value : analyzer.GetEnumerators())
                processedEnum.registration_.push_back("engine->RegisterEnumValue(\"" + enumTypeName + "\", \"" + value + "\", " + value + ");");
        }
        else // If enum is not int then register as typedef. But this type can not be used in switch
        {
            processedEnum.registration_.push_back("engine->RegisterTypedef(\"" + enumTypeName + "\", \"" + asEnumBaseType + "\");");

            for (const string& enumerator : analyzer.GetEnumerators())
            {
                string constName = enumTypeName + "_" + enumerator;
                processedEnum.glue_.push_back("static const " + cppEnumBaseType + " " + constName + " = " + enumerator + ";");
                processedEnum.registration_.push_back("engine->RegisterGlobalProperty(\"const " + asEnumBaseType + " " + enumerator + "\", (void*)&" + constName + ");");
            }
        }
    }

    Result::enums_.push_back(processedEnum);
}

static void ProcessFlagset(const GlobalFunctionAnalyzer& analyzer)
{
    string header = analyzer.GetHeaderFile();
    Result::AddHeader(header);

    if (IsIgnoredHeader(header))
        return;

    vector<ParamAnalyzer> params = analyzer.GetParams();
    assert(params.size() == 2);
    string enumTypeName = params[0].GetType().GetName();
    string flagsetName = params[1].GetType().GetName();

    shared_ptr<EnumAnalyzer> enumAnalyzer = FindEnum(enumTypeName);
    assert(enumAnalyzer);
    string cppEnumBaseType = enumAnalyzer->GetBaseType();
    string asEnumBaseType = CppPrimitiveTypeToAS(cppEnumBaseType);

    ProcessedEnum processedEnum;
    processedEnum.name_ = flagsetName;
    processedEnum.insideDefine_ = InsideDefine(header);
    processedEnum.comment_ = analyzer.GetLocation();
    processedEnum.registration_.push_back("engine->RegisterTypedef(\"" + flagsetName + "\", \"" + asEnumBaseType + "\");");

    Result::enums_.push_back(processedEnum);
}

void ProcessAllEnums()
{
    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<EnumAnalyzer> enumAnalyzers = namespaceAnalyzer.GetEnums();

    for (const EnumAnalyzer& enumAnalyzer : enumAnalyzers)
        ProcessEnum(enumAnalyzer);

    vector<GlobalFunctionAnalyzer> globalFunctionAnalyzers = namespaceAnalyzer.GetFunctions();

    for (const GlobalFunctionAnalyzer& globalFunctionAnalyzer : globalFunctionAnalyzers)
    {
        string functionName = globalFunctionAnalyzer.GetName();

        if (functionName == "URHO3D_FLAGSET")
            ProcessFlagset(globalFunctionAnalyzer);
    }
}

} // namespace ASBindingGenerator
