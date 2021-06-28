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

    if (typeAnalyzer.IsConst())
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
