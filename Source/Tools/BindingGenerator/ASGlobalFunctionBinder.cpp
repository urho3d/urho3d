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

#include <regex>
#include <cassert>
#include <map>

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

static vector<map<string, string> > GetSpecializations(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    vector<string> templateParams = functionAnalyzer.GetTemplateParams();

    vector<map<string, string> > result;
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

static shared_ptr<ASGeneratedFile_GlobalFunctions> _result;

static void BindGlobalFunction(const GlobalFunctionAnalyzer& functionAnalyzer, const map<string, string>& templateSpecialization = map<string, string>())
{
    string declParams = "";
    vector<ParamAnalyzer> params = functionAnalyzer.GetParams(templateSpecialization);
    string outGlue;

    bool needWrapper = false;

    vector<shared_ptr<FuncParamConv> > convertedParams;

    for (size_t i = 0; i < params.size(); i++)
    {
        ParamAnalyzer param = params[i];
        shared_ptr<FuncParamConv> conv = CppFunctionParamToAS(i, param);
        if (!conv->success_)
        {
            _result->reg_ << "    // " << conv->errorMessage_ << "\n";
            return;
        }

        if (declParams.length() > 0)
            declParams += ", ";

        declParams += conv->asDecl_;

        if (conv->NeedWrapper())
            needWrapper = true;

        convertedParams.push_back(conv);
    }

    shared_ptr<FuncReturnTypeConv> retConv = CppFunctionReturnTypeToAS(functionAnalyzer.GetReturnType(templateSpecialization));
    if (!retConv->success_)
    {
        _result->reg_ << "    // " << GetLastErrorMessage() << "\n";
        return;
    }
    
    if (retConv->needWrapper_)
        needWrapper = true;

    if (needWrapper)
        _result->glue_ << GenerateWrapper(functionAnalyzer, convertedParams, retConv);

    string asReturnType = retConv->asReturnType_;

    string asFunctionName = functionAnalyzer.GetName();

    string decl = asReturnType + " " + asFunctionName + "(" + declParams + ")";

    _result->reg_ << "    engine->RegisterGlobalFunction(\"" << decl << "\", ";

    if (needWrapper)
        _result->reg_ << "asFUNCTION(" << GenerateWrapperName(functionAnalyzer) << "), asCALL_CDECL);\n";
    else
        _result->reg_ << Generate_asFUNCTIONPR(functionAnalyzer, templateSpecialization) << ", asCALL_CDECL);\n";

    // Also register alias if needed
    string aliasMark = GetAliasMark(functionAnalyzer);

    if (!aliasMark.empty())
    {
        asFunctionName = CutStart(aliasMark, "BIND_AS_ALIAS_");

        decl = asReturnType + " " + asFunctionName + "(" + declParams + ")";

        _result->reg_ << "    engine->RegisterGlobalFunction(\"" << decl << "\", ";

        if (needWrapper)
            _result->reg_ << "asFUNCTION(" << GenerateWrapperName(functionAnalyzer) << "), asCALL_CDECL);\n";
        else
            _result->reg_ << Generate_asFUNCTIONPR(functionAnalyzer, templateSpecialization) << ", asCALL_CDECL);\n";
    }
}

static void ProcessGlobalFunction(const GlobalFunctionAnalyzer& functionAnalyzer)
{
    if (functionAnalyzer.IsDefine())
        return;

    vector<map<string, string> > specializations;

    if (functionAnalyzer.IsTemplate())
    {
        specializations = GetSpecializations(functionAnalyzer);

        if (!specializations.size())
            return;
    }

    if (Contains(functionAnalyzer.GetName(), "operator"))
        return;

    string header = functionAnalyzer.GetHeaderFile();
    if (IsIgnoredHeader(header))
    {
        _result->AddIgnoredHeader(header);
        return;
    }

    _result->AddHeader(header);

    string insideDefine = InsideDefine(header);
    if (!insideDefine.empty())
        _result->reg_ << "#ifdef " << insideDefine << "\n";

    _result->reg_ << "    // " << functionAnalyzer.GetLocation() << "\n";

    if (Contains(functionAnalyzer.GetComment(), "NO_BIND"))
    {
        _result->reg_ << "    // Not registered because have @nobind mark\n";
        if (!insideDefine.empty())
            _result->reg_ << "#endif\n";
        return;
    }

    if (functionAnalyzer.IsTemplate())
    {
        for (map<string, string> specialization : specializations)
            BindGlobalFunction(functionAnalyzer, specialization);
    }
    else
    {
        BindGlobalFunction(functionAnalyzer);
    }

    if (!insideDefine.empty())
        _result->reg_ << "#endif\n";
}

void ProcessAllGlobalFunctions(const string& outputBasePath)
{
    string outputPath = outputBasePath + "/Source/Urho3D/AngelScript/Generated_GlobalFunctions.cpp";

    NamespaceAnalyzer namespaceAnalyzer(SourceData::namespaceUrho3D_);
    vector<GlobalFunctionAnalyzer> globalFunctionAnalyzers = namespaceAnalyzer.GetFunctions();

    _result = make_shared<ASGeneratedFile_GlobalFunctions>(outputPath, "ASRegisterGenerated_GlobalFunctions");

    for (GlobalFunctionAnalyzer globalFunctionAnalyzer : globalFunctionAnalyzers)
        ProcessGlobalFunction(globalFunctionAnalyzer);

    _result->Save();
}

}
