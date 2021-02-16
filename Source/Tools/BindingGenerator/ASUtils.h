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

#include <map>
#include <stdexcept>
#include <string>

using namespace std;

namespace ASBindingGenerator
{

enum class TypeUsage
{
    FunctionParameter = 0,
    FunctionReturn,
    ClassStaticVariable,
    ClassVariable,
};

struct ConvertedVariable
{
    string asDeclaration_;
    string cppDeclaration_;
    string glue_;

    bool NeedWrapper() const { return !glue_.empty(); }
};

string JoinASDeclarations(const vector<ConvertedVariable>& vars);

enum class VariableUsage
{
    FunctionParameter = 0,
    FunctionReturn,
    ClassStaticVariable,
    ClassVariable,
};

ConvertedVariable CppVariableToAS(const TypeAnalyzer& type, VariableUsage usage, const string& name = "", const string& defaultValue = "");

string CppTypeToAS(const TypeAnalyzer& type, TypeUsage typeUsage);

shared_ptr<EnumAnalyzer> FindEnum(const string& name);
string CppPrimitiveTypeToAS(const string& cppType);
string CppValueToAS(const string& cppValue);

class Exception : public runtime_error
{
    using runtime_error::runtime_error;
};

bool IsKnownCppType(const string& name);

shared_ptr<ClassAnalyzer> FindClassByName(const string& name);
shared_ptr<ClassAnalyzer> FindClassByID(const string& name);

string GenerateWrapperName(const GlobalFunctionAnalyzer& functionAnalyzer);
string GenerateWrapperName(const ClassStaticFunctionAnalyzer& functionAnalyzer);
string GenerateWrapperName(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion = false);

string GenerateWrapper(const GlobalFunctionAnalyzer& functionAnalyzer, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);
string GenerateWrapper(const ClassStaticFunctionAnalyzer& functionAnalyzer, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);
string GenerateWrapper(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion, const vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);

string Generate_asFUNCTIONPR(const GlobalFunctionAnalyzer& functionAnalyzer);
string Generate_asFUNCTIONPR(const ClassStaticFunctionAnalyzer& functionAnalyzer);
string Generate_asMETHODPR(const ClassFunctionAnalyzer& functionAnalyzer, bool templateVersion);

}
