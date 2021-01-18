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

#pragma once

#include "XmlAnalyzer.h"

#include <string>
#include <map>

using namespace std;

namespace ASBindingGenerator
{

shared_ptr<EnumAnalyzer> FindEnum(const string& name);
string CppFundamentalTypeToAS(const string& cppType);
string CppTypeToAS(const TypeAnalyzer& type, bool returnType, bool& outSuccess);
string CppValueToAS(const string& cppValue);

struct FuncParamConv
{
    bool success_ = false;
    string errorMessage_ = "TODO";
    string asDecl_ = "TODO";
    string cppType_ = "TODO";
    string inputVarName_ = "TODO";
    string convertedVarName_ = "TODO";
    string glue_ = "";

    bool NeedWrapper() const { return !glue_.empty(); }
};

shared_ptr<FuncParamConv> CppFunctionParamToAS(int paramIndex, ParamAnalyzer& paramAnalyzer);

struct FuncReturnTypeConv
{
    bool success_ = false;
    bool needWrapper_ = false;
    string errorMessage_ = "TODO";
    string asReturnType_ = "TODO";
    string glueReturnType_ = "TODO";
    string glueReturn_ = "TODO";
};

bool IsKnownType(const string& name);

shared_ptr<ClassAnalyzer> FindClassByName(const string& name);
shared_ptr<ClassAnalyzer> FindClassByID(const string& name);

shared_ptr<FuncReturnTypeConv> CppFunctionReturnTypeToAS(const TypeAnalyzer& typeAnalyzer);

string GenerateWrapperName(const GlobalFunctionAnalyzer& functionAnalyzer);
string GenerateWrapperName(const ClassStaticFunctionAnalyzer& functionAnalyzer);
string GenerateWrapperName(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion);

string GenerateWrapper(const GlobalFunctionAnalyzer& functionAnalyzer, vector<shared_ptr<FuncParamConv> >& convertedParams, shared_ptr<FuncReturnTypeConv> convertedReturn);
string GenerateWrapper(const ClassStaticFunctionAnalyzer& functionAnalyzer, vector<shared_ptr<FuncParamConv> >& convertedParams, shared_ptr<FuncReturnTypeConv> convertedReturn);
string GenerateWrapper(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion, vector<shared_ptr<FuncParamConv> >& convertedParams, shared_ptr<FuncReturnTypeConv> convertedReturn);

string Generate_asFUNCTIONPR(const GlobalFunctionAnalyzer& functionAnalyzer);
string Generate_asFUNCTIONPR(const ClassStaticFunctionAnalyzer& functionAnalyzer);
string Generate_asMETHODPR(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion);

}
