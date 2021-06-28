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

    if (cppEnumBaseType == "int") // Enums in AngelScript can be only int
    {
        processedEnum.registration_.push_back("engine->RegisterEnum(\"" + enumTypeName + "\");");

        for (const string& value : analyzer.GetEnumerators())
            processedEnum.registration_.push_back("engine->RegisterEnumValue(\"" + enumTypeName + "\", \"" + value + "\", " + value + ");");
    }
    else // If enum is not int then register as typedef. But this type can not be used in switch
    {
        string asEnumBaseType = CppPrimitiveTypeToAS(cppEnumBaseType);

        processedEnum.registration_.push_back("engine->RegisterTypedef(\"" + enumTypeName + "\", \"" + asEnumBaseType + "\");");

        for (const string& enumerator : analyzer.GetEnumerators())
        {
            string constName = enumTypeName + "_" + enumerator;
            processedEnum.glue_.push_back("static const " + cppEnumBaseType + " " + constName + " = " + enumerator + ";");
            processedEnum.registration_.push_back("engine->RegisterGlobalProperty(\"const " + asEnumBaseType + " " + enumerator + "\", (void*)&" + constName + ");");
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
