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
#include <map>
#include <regex>

namespace ASBindingGenerator
{

static string GetAliasMark(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    string comment = functionAnalyzer.GetComment();

    smatch match;
    regex_match(comment, match, regex(".*\\b(BIND_AS_ALIAS_.+?)\\b.*"));
    if (match.size() == 2)
        return match[1].str();

    return "";
}

static vector<map<string, string>> GetSpecializations(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    vector<string> templateParams = functionAnalyzer.GetTemplateParams();

    vector<map<string, string>> result;
    string comment = functionAnalyzer.GetComment();
    smatch match;

    if (templateParams.size() == 1)
    {
        regex rgx("\\bSPECIALIZATION_([^_]+?)\\b");

        string::const_iterator searchStart(comment.cbegin());
        while (regex_search(searchStart, comment.cend(), match, rgx))
        {
            map<string, string> specialization;
            specialization[templateParams[0]] = match[1].str();
            searchStart = match.suffix().first;
            result.push_back(specialization);
        }
    }

    else if (templateParams.size() == 2)
    {
        regex rgx("\\bSPECIALIZATION_([^_]+?)_([^_]+?)\\b");

        string::const_iterator searchStart(comment.cbegin());
        while (regex_search(searchStart, comment.cend(), match, rgx))
        {
            map<string, string> specialization;
            specialization[templateParams[0]] = match[1].str();
            specialization[templateParams[1]] = match[2].str();
            searchStart = match.suffix().first;
            result.push_back(specialization);
        }
    }

    else if (templateParams.size() == 3)
    {
        regex rgx("\\bSPECIALIZATION_([^_]+?)_([^_]+?)_([^_]+?)\\b");

        string::const_iterator searchStart(comment.cbegin());
        while (regex_search(searchStart, comment.cend(), match, rgx))
        {
            map<string, string> specialization;
            specialization[templateParams[0]] = match[1].str();
            specialization[templateParams[1]] = match[2].str();
            specialization[templateParams[2]] = match[3].str();
            searchStart = match.suffix().first;
            result.push_back(specialization);
        }
    }

    return result;
}

static void BindGlobalFunction(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    vector<ParamAnalyzer> params = functionAnalyzer.GetParams();
    string outGlue;

    bool needWrapper = false;

    vector<ConvertedVariable> convertedParams;

    ProcessedGlobalFunction processedGlobalFunction;
    processedGlobalFunction.name_ = functionAnalyzer.GetName();
    processedGlobalFunction.comment_ = functionAnalyzer.GetLocation();
    processedGlobalFunction.insideDefine_ = InsideDefine(functionAnalyzer.GetHeaderFile());

    for (const ParamAnalyzer& param : params)
    {
        ConvertedVariable conv;
        
        try
        {
            conv = CppVariableToAS(param.GetType(), VariableUsage::FunctionParameter, param.GetDeclname(), param.GetDefval());
        }
        catch (const Exception& e)
        {
            processedGlobalFunction.registration_ = "// " + string(e.what());
            Result::globalFunctions_.push_back(processedGlobalFunction);
            return;
        }

        if (conv.NeedWrapper())
            needWrapper = true;

        convertedParams.push_back(conv);
    }

    ConvertedVariable retConv;

    try
    {
        retConv = CppVariableToAS(functionAnalyzer.GetReturnType(), VariableUsage::FunctionReturn);
    }
    catch (const Exception& e)
    {
        processedGlobalFunction.registration_ = "// " + string(e.what());
        Result::globalFunctions_.push_back(processedGlobalFunction);
        return;
    }

    if (retConv.NeedWrapper())
        needWrapper = true;

    if (needWrapper)
        processedGlobalFunction.glue_ = GenerateWrapper(functionAnalyzer, convertedParams, retConv);

    string asReturnType = retConv.asDeclaration_;

    string asFunctionName = functionAnalyzer.GetName();

    string decl = asReturnType + " " + asFunctionName + "(" + JoinASDeclarations(convertedParams) + ")";

    processedGlobalFunction.registration_ = "engine->RegisterGlobalFunction(\"" + decl + "\", ";

    if (needWrapper)
        processedGlobalFunction.registration_ += "AS_FUNCTION(" + GenerateWrapperName(functionAnalyzer) + "), AS_CALL_CDECL);";
    else
        processedGlobalFunction.registration_ += Generate_asFUNCTIONPR(functionAnalyzer) + ", AS_CALL_CDECL);";

    Result::globalFunctions_.push_back(processedGlobalFunction);

    // Also register alias if needed
    string aliasMark = GetAliasMark(functionAnalyzer);

    if (!aliasMark.empty())
    {
        asFunctionName = CutStart(aliasMark, "BIND_AS_ALIAS_");

        decl = asReturnType + " " + asFunctionName + "(" + JoinASDeclarations(convertedParams) + ")";

        processedGlobalFunction.registration_ = "engine->RegisterGlobalFunction(\"" + decl + "\", ";

        if (needWrapper)
            processedGlobalFunction.registration_ += "AS_FUNCTION(" + GenerateWrapperName(functionAnalyzer) + "), AS_CALL_CDECL);";
        else
            processedGlobalFunction.registration_ += Generate_asFUNCTIONPR(functionAnalyzer) + ", AS_CALL_CDECL);";

        Result::globalFunctions_.push_back(processedGlobalFunction);
    }
}

static void ProcessGlobalFunction(const GlobalFunctionAnalyzer& globalFunctionAnalyzer)
{
    if (globalFunctionAnalyzer.IsDefine())
        return;

    vector<map<string, string>> specializations;

    if (globalFunctionAnalyzer.IsTemplate())
    {
        specializations = GetSpecializations(globalFunctionAnalyzer);

        if (!specializations.size())
            return;
    }

    if (Contains(globalFunctionAnalyzer.GetName(), "operator"))
        return;

    string header = globalFunctionAnalyzer.GetHeaderFile();
    Result::AddHeader(header);

    if (IsIgnoredHeader(header))
        return;

    if (Contains(globalFunctionAnalyzer.GetComment(), "NO_BIND"))
    {
        ProcessedGlobalFunction processedGlobalFunction;
        processedGlobalFunction.name_ = globalFunctionAnalyzer.GetName();
        processedGlobalFunction.insideDefine_ = InsideDefine(header);
        processedGlobalFunction.comment_ = globalFunctionAnalyzer.GetLocation();
        processedGlobalFunction.registration_ = "// Not registered because have @nobind mark";
        Result::globalFunctions_.push_back(processedGlobalFunction);
        return;
    }

    if (globalFunctionAnalyzer.IsTemplate())
    {
        for (const TemplateSpecialization& specialization : specializations)
        {
            GlobalFunctionAnalyzer specializedAnalyzer(globalFunctionAnalyzer.GetMemberdef(), specialization);
            BindGlobalFunction(specializedAnalyzer);
        }
    }
    else
    {
        BindGlobalFunction(globalFunctionAnalyzer);
    }
}

void ProcessAllGlobalFunctions()
{
    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<GlobalFunctionAnalyzer> globalFunctionAnalyzers = namespaceAnalyzer.GetFunctions();

    for (const GlobalFunctionAnalyzer& globalFunctionAnalyzer : globalFunctionAnalyzers)
        ProcessGlobalFunction(globalFunctionAnalyzer);
}

}
