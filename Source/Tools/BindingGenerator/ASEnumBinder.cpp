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
#include <memory>

namespace ASBindingGenerator
{

static void ProcessEnum(class EnumAnalyzer& analyzer)
{
    if (analyzer.IsInternal())
        return;

    string header = analyzer.GetHeaderFile();
    
    if (IsIgnoredHeader(header))
    {
        ResultIncludes::AddHeader(header);
        return;
    }

    string insideDefine = InsideDefine(header);
    string comment = analyzer.GetComment();
    string location = analyzer.GetLocation();

    if (Contains(comment, "NO_BIND"))
    {
        if (!insideDefine.empty())
            ResultEnums::reg_ << "#ifdef " << insideDefine << "\n";

        ResultEnums::reg_ <<
            "    // " << location << "\n"
            "    // Not registered because have @nobind mark\n";

        if (!insideDefine.empty())
            ResultEnums::reg_ << "#endif\n";

        ResultEnums::reg_ << "\n";
        
        return;
    }

    if (Contains(comment, "MANUAL_BIND"))
    {
        if (!insideDefine.empty())
            ResultEnums::reg_ << "#ifdef " << insideDefine << "\n";

        ResultEnums::reg_ <<
            "    // " << location << "\n"
            "    // Not registered because have @manualbind mark\n";

        if (!insideDefine.empty())
            ResultEnums::reg_ << "#endif\n";

        ResultEnums::reg_ << "\n";

        return;
    }

    ResultIncludes::AddHeader(header);
    ResultEnums::AddHeader(header);

    string enumTypeName = analyzer.GetTypeName();
    string cppEnumBaseType = analyzer.GetBaseType();

    if (cppEnumBaseType == "int") // Enums in AngelScript can be only int
    {
        if (!insideDefine.empty())
            ResultEnums::reg_ << "#ifdef " << insideDefine << "\n";

        ResultEnums::reg_ <<
            "    // " << location << "\n"
            "    engine->RegisterEnum(\"" << enumTypeName << "\");\n";

        for (string value : analyzer.GetEnumerators())
            ResultEnums::reg_ << "    engine->RegisterEnumValue(\"" << enumTypeName << "\", \"" << value << "\", " << value << ");\n";

        if (!insideDefine.empty())
            ResultEnums::reg_ << "#endif\n";

        ResultEnums::reg_ << "\n";

        return;
    }

    // If enum is not int then register as typedef. But this type can not be used in switch

    if (!insideDefine.empty())
        ResultEnums::reg_ << "#ifdef " << insideDefine << "\n";

    string asEnumBaseType = CppFundamentalTypeToAS(cppEnumBaseType);

    ResultEnums::reg_ <<
        "    // " << location << "\n"
        "    engine->RegisterTypedef(\"" << enumTypeName << "\", \"" << asEnumBaseType << "\");\n";

    ResultEnums::glue_ << "// " << location << "\n";

    vector<string> enumerators = analyzer.GetEnumerators();

    for (string enumerator : enumerators)
    {
        string constName = enumTypeName + "_" + enumerator;

        ResultEnums::glue_ << "static const " << cppEnumBaseType << " " << constName << " = " << enumerator << ";\n";

        ResultEnums::reg_ << "    engine->RegisterGlobalProperty(\"const " << asEnumBaseType << " " << enumerator << "\", (void*)&" << constName << ");\n";
    }

    if (!insideDefine.empty())
        ResultEnums::glue_ << "#endif\n";

    ResultEnums::glue_ << "\n";

    if (!insideDefine.empty())
        ResultEnums::reg_ << "#endif\n";

    ResultEnums::reg_ << "\n";
}

static void ProcessFlagset(const GlobalFunctionAnalyzer& analyzer)
{
    string header = analyzer.GetHeaderFile();

    if (IsIgnoredHeader(header))
    {
        ResultIncludes::AddHeader(header);
        return;
    }

    ResultIncludes::AddHeader(header);
    ResultEnums::AddHeader(header);

    vector<ParamAnalyzer> params = analyzer.GetParams();
    assert(params.size() == 2);
    string enumTypeName = params[0].GetType().GetName();
    string flagsetName = params[1].GetType().GetName();
    shared_ptr<EnumAnalyzer> enumAnalyzer = FindEnum(enumTypeName);
    assert(enumAnalyzer);
    string cppEnumBaseType = enumAnalyzer->GetBaseType();
    string asEnumBaseType = CppFundamentalTypeToAS(cppEnumBaseType);
    string insideDefine = InsideDefine(header);
    string location = analyzer.GetLocation();

    if (!insideDefine.empty())
        ResultEnums::reg_ << "#ifdef " << insideDefine << "\n";

    ResultEnums::reg_ <<
        "    // " << location << "\n"
        "    engine->RegisterTypedef(\"" << flagsetName << "\", \"" << asEnumBaseType << "\");\n";

    if (!insideDefine.empty())
        ResultEnums::reg_ << "#endif\n";
}

void ProcessAllEnums()
{
    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<EnumAnalyzer> enumAnalyzers = namespaceAnalyzer.GetEnums();

    for (EnumAnalyzer enumAnalyzer : enumAnalyzers)
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
