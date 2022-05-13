// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "XmlAnalyzer.h"

#include <map>
#include <stdexcept>
#include <string>

namespace ASBindingGenerator
{

enum class TypeUsage
{
    FunctionParameter = 0,
    FunctionReturn,
    StaticField,
    Field,
};

struct ConvertedVariable
{
    std::string asDeclaration_;
    std::string cppDeclaration_;
    std::string glue_;

    bool NeedWrapper() const { return !glue_.empty(); }
};

std::string JoinASDeclarations(const std::vector<ConvertedVariable>& vars);

enum class VariableUsage
{
    FunctionParameter = 0,
    FunctionReturn,
    StaticField,
    Field,
    PostfixIncDecParameter
};

ConvertedVariable CppVariableToAS(const TypeAnalyzer& type, VariableUsage usage, const std::string& name = "", const std::string& defaultValue = "");

std::string CppTypeToAS(const TypeAnalyzer& type, TypeUsage typeUsage);

std::shared_ptr<EnumAnalyzer> FindEnum(const std::string& name);
std::string CppPrimitiveTypeToAS(const std::string& cppType);
std::string CppValueToAS(const std::string& cppValue);

class Exception : public std::runtime_error
{
    using runtime_error::runtime_error;
};

bool IsKnownCppType(const std::string& name);

// A union within a class may not have a type name. For such types, Doxygen generates identifiers like @123.
// These identifiers can change and produce redundant changes in commits.
std::string HideUnnamedType(const std::string& name);

std::shared_ptr<ClassAnalyzer> FindClassByName(const std::string& name);
std::shared_ptr<ClassAnalyzer> FindClassByID(const std::string& name);

std::string GenerateWrapperName(const GlobalFunctionAnalyzer& functionAnalyzer);
std::string GenerateWrapperName(const ClassStaticFunctionAnalyzer& functionAnalyzer);
std::string GenerateWrapperName(const MethodAnalyzer& methodAnalyzer, bool templateVersion = false);

std::string GenerateWrapper(const GlobalFunctionAnalyzer& functionAnalyzer, const std::vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);
std::string GenerateWrapper(const ClassStaticFunctionAnalyzer& functionAnalyzer, bool templateVersion, const std::vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);
std::string GenerateWrapper(const MethodAnalyzer& methodAnalyzer, bool templateVersion, const std::vector<ConvertedVariable>& convertedParams, const ConvertedVariable& convertedReturn);

std::string GenerateConstructorWrapper(const MethodAnalyzer& methodAnalyzer, const std::vector<ConvertedVariable>& convertedParams);
std::string GenerateFactoryWrapper(const MethodAnalyzer& methodAnalyzer, const std::vector<ConvertedVariable>& convertedParams);


std::string Generate_asFUNCTIONPR(const GlobalFunctionAnalyzer& functionAnalyzer);
std::string Generate_asFUNCTIONPR(const ClassStaticFunctionAnalyzer& functionAnalyzer, bool templateVersion);
std::string Generate_asMETHODPR(const MethodAnalyzer& methodAnalyzer, bool templateVersion);

}
