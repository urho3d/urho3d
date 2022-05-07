// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "ASResult.h"
#include "ASUtils.h"
#include "Tuning.h"
#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

using namespace std;

namespace ASBindingGenerator
{

static void ProcessGlobalVariable(GlobalVariableAnalyzer varAnalyzer)
{
    string header = varAnalyzer.GetHeaderFile();

    Result::AddHeader(header);
   
    if (IsIgnoredHeader(header))
        return;

    ProcessedGlobalVariable processedGlobalVariable;
    processedGlobalVariable.name_ = varAnalyzer.GetName();
    processedGlobalVariable.insideDefine_ = InsideDefine(header);
    processedGlobalVariable.comment_ = varAnalyzer.GetLocation();

    if (varAnalyzer.IsArray())
    {
        processedGlobalVariable.registration_ = "// Not registered because array";
        Result::globalVariables_.push_back(processedGlobalVariable);
        return;
    }

    TypeAnalyzer typeAnalyzer = varAnalyzer.GetType();

    string asType;

    try
    {
        asType = CppPrimitiveTypeToAS(typeAnalyzer.GetName());
    }
    catch (...)
    {
        asType = typeAnalyzer.GetName();
    }

    if (typeAnalyzer.IsConst() || typeAnalyzer.IsConstexpr())
        asType = "const " + asType;

    string varName = varAnalyzer.GetName();

    processedGlobalVariable.registration_ = "engine->RegisterGlobalProperty(\"" + asType + " " + varName + "\", (void*)&" + varName + ");";
    Result::globalVariables_.push_back(processedGlobalVariable);
}

void ProcessAllGlobalVariables()
{
    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<GlobalVariableAnalyzer> globalVariableAnalyzers = namespaceAnalyzer.GetVariables();

    for (GlobalVariableAnalyzer globalVariableAnalyzer : globalVariableAnalyzers)
        ProcessGlobalVariable(globalVariableAnalyzer);
}

} // namespace ASBindingGenerator
