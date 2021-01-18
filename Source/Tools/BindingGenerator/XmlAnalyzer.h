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

#include <PugiXml/pugixml.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "XmlSourceData.h"
#include "Utils.h"

using namespace pugi;
using namespace std;

using TemplateSpecialization = map<string, string>;

// <type>...</type> | <defval>...</defval> | <para>...</para>
string RemoveRefs(xml_node node);

// <type>...</type>
class TypeAnalyzer
{
private:
    string fullType_;
    string name_;
    bool isConst_;
    bool isPointer_; // *
    bool isReference_; // &
    bool isRvalueReference_; // &&
    bool isDoublePointer_; // **
    bool isRefToPoiner_; // *&
    string templateParams_;

public:
    TypeAnalyzer(xml_node type, const TemplateSpecialization& specialization = {});

    // Used for doxygen bug workaround https://github.com/doxygen/doxygen/issues/7732
    TypeAnalyzer(const string& typeName);

    string ToString() const { return fullType_; }
    string GetName() const { return name_; }
    bool IsConst() const { return isConst_; }
    bool IsPointer() const { return isPointer_; }
    bool IsReference() const { return isReference_; }
    bool IsRvalueReference() const { return isRvalueReference_; }
    bool IsDoublePointer() const { return isDoublePointer_; }
    bool IsRefToPointer() const { return isRefToPoiner_; }
    bool IsTemplate() const { return templateParams_.length() > 0; }
    string GetTemplateParams() { return templateParams_; }
    string GetNameWithTemplateParams() const { return IsTemplate() ? name_ + "<" + templateParams_ + ">" : name_; }
};

// <memberdef kind="function">
//     <param>...</param>
class ParamAnalyzer
{
private:
    xml_node node_;
    TemplateSpecialization specialization_; 

public:
    ParamAnalyzer(xml_node param, const TemplateSpecialization& specialization = {});

    xml_node GetNode() const { return node_; }

    string ToString() const;

    // <param>
    //     <type>....</type>
    TypeAnalyzer GetType() const;

    // <param>
    //     <declname>....</declname>
    string GetDeclname() const;

    // <param>
    //     <defval>....</defval>
    string GetDefval() const; // Default value
};

// <memberdef>
inline bool IsMemberdef(xml_node node) { return node.name() == string("memberdef"); }

// <compounddef>
inline bool IsCompounddef(xml_node node) { return node.name() == string("compounddef"); }

// <member>
inline bool IsMember(xml_node node) { return node.name() == string("member"); }

// <sectiondef>
inline bool IsSectiondef(xml_node node) { return node.name() == string("sectiondef"); }

// <enumvalue>
inline bool IsEnumvalue(xml_node node) { return node.name() == string("enumvalue"); }

// <compounddef>
//     <compoundname>...</compoundname>
string ExtractCompoundname(xml_node compounddef);

// <compounddef>
//     <sectiondef kind="xxx">...</sectiondef>
xml_node FindSectiondef(xml_node compounddef, const string& kind);

// <memberdef static="yes">
bool IsStatic(xml_node memberdef);

// <memberdef kind="function" explicit="yes">
bool IsExplicit(xml_node memberdef);

// <memberdef>
//     <definition>...</definition>
string ExtractDefinition(xml_node memberdef);

// <memberdef>
//     <argsstring>...</argsstring>
string ExtractArgsstring(xml_node memberdef);

// <memberdef kind="function">
//     <argsstring>(...)</argsstring>
//     <argsstring>(...) xxx</argsstring>
//         where xxx can be of const, override, =default, =delete, =0 or their combination
string ExtractCleanedFunctionArgsstring(xml_node memberdef);

// <memberdef prot="...">
string ExtractProt(xml_node memberdef);

// <memberdef>
//     <type>...</type>
TypeAnalyzer ExtractType(xml_node memberdef, const TemplateSpecialization& specialization = {});

// <memberdef kind="function">
//     <param>...</param>
//     <param>...</param>
vector<ParamAnalyzer> ExtractParams(xml_node memberdef, const TemplateSpecialization& specialization = {});

// <memberdef kind="function">
//     <param>...</param>
//     <param>...</param>
string JoinParamsTypes(xml_node memberdef, const TemplateSpecialization& specialization = {});
string JoinParamsNames(xml_node memberdef, bool skipContext = false);

// <memberdef kind="function">
//     ...
string GetFunctionLocation(xml_node memberdef);

// <compounddef|memberdef id="...">
string ExtractID(xml_node node);

// <compounddef|memberdef|member|sectiondef kind="...">
string ExtractKind(xml_node node);

// <memberdef|enumvalue>
//     <name>...</name>
string ExtractName(xml_node node);

// <compounddef|memberdef>
//     <location line="...">
string ExtractLine(xml_node node);

// <compounddef|memberdef>
//     <location column="...">
string ExtractColumn(xml_node node);

// <compounddef|memberdef>
//     <briefdescription>...</briefdescription>
//     <detaileddescription>...</detaileddescription>
string ExtractComment(xml_node node);

// <compounddef|memberdef>
//     <location ...>
// Extract header file path and convert to relative.
// Return empty string when declared in *.cpp
string ExtractHeaderFile(xml_node node);

// <compounddef|memberdef>
//     <templateparamlist>
bool IsTemplate(xml_node node);

// <compounddef|memberdef>
//     <templateparamlist>
//         <param>...</param>
//         <param>...</param>
vector<string> ExtractTemplateParams(xml_node node);

// <compounddef kind="namespace">
//     <sectiondef kind="enum">
//         <memberdef kind="enum">...</memberdef>
class EnumAnalyzer
{
    xml_node memberdef_;

public:
    EnumAnalyzer(xml_node memberdef);

    string GetTypeName() const { return ExtractName(memberdef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    string GetComment() const { return ExtractComment(memberdef_); }
    bool IsInternal() const { return GetHeaderFile().empty(); } // true if declared in .cpp file
    string GetBaseType() const;
    string GetLocation() const;

    // <memberdef kind="enum">
    //     <enumvalue><name>...</name></enumvalue>
    //     <enumvalue><name>...</name></enumvalue>
    vector<string> GetEnumerators() const;

};

// <compounddef kind="namespace">
//     <sectiondef kind="var">
//         <memberdef kind="variable">...</memberdef>
class GlobalVariableAnalyzer
{
    xml_node memberdef_;

public:
    GlobalVariableAnalyzer(xml_node memberdef);

    string GetName() const { return ExtractName(memberdef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    bool IsStatic() const { return ::IsStatic(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
    bool IsArray() const { return StartsWith(ExtractArgsstring(memberdef_), "["); }
    string GetLocation() const;
};

class ClassFunctionAnalyzer;
class ClassVariableAnalyzer;

// <compounddef kind="class|struct">...</compounddef>
class ClassAnalyzer
{
private:
    xml_node compounddef_;
    TemplateSpecialization specialization_;
    
    vector<xml_node> GetMemberdefs() const;

public:
    string usingLocation_;

    ClassAnalyzer(xml_node compounddef, const TemplateSpecialization& specialization = {});

    const TemplateSpecialization& GetSpecialization() const { return specialization_; }

    string GetClassName() const;
    string GetComment() const { return ExtractComment(compounddef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(compounddef_); }
    string GetKind() const { return ExtractKind(compounddef_); }
    bool IsInternal() const;
    bool IsTemplate() const { return ::IsTemplate(compounddef_); }
    vector<ClassFunctionAnalyzer> GetFunctions() const;
    vector<ClassVariableAnalyzer> GetVariables() const;
    bool ContainsFunction(const string& name) const;
    shared_ptr<ClassFunctionAnalyzer> GetFunction(const string& name) const;
    int NumFunctions(const string& name) const;
    bool IsRefCounted() const;
    bool HasThisDestructor() const { return ContainsFunction("~" + GetClassName()); }
    bool HasThisConstructor() const;
    bool IsAbstract() const;
    string GetLocation() const { return GetKind() + " " + GetClassName() + " | File: " + GetHeaderFile(); }
    bool AllFloats() const;
    bool AllInts() const;
    bool IsPod() const;
    shared_ptr<ClassAnalyzer> GetBaseClass() const;
    vector<ClassAnalyzer> GetBaseClasses() const;
    vector<ClassAnalyzer> GetAllBaseClasses() const;
    
    // Return null if default constructor is implicitly-declared.
    // Return pointer if default constructor is deleted
    shared_ptr<ClassFunctionAnalyzer> GetDefinedThisDefaultConstructor() const;

    vector<ClassFunctionAnalyzer> GetThisNonDefaultConstructors() const;

    // Return null if destructor is implicitly-declared.
    // Return pointer if destructor is deleted
    shared_ptr<ClassFunctionAnalyzer> GetDefinedThisDestructor() const { return GetFunction("~" + GetClassName()); }
};

// <memberdef kind="function">...</memberdef>
class FunctionAnalyzer
{
protected:
    xml_node memberdef_;
    TemplateSpecialization specialization_;

public:
    FunctionAnalyzer(xml_node memberdef, const TemplateSpecialization& specialization = {});
    
    xml_node GetMemberdef() const { return memberdef_; }
    const TemplateSpecialization& GetSpecialization() const { return specialization_; }

    string GetComment() const { return ExtractComment(memberdef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    string GetName() const { return ExtractName(memberdef_); }
    vector<ParamAnalyzer> GetParams() const { return ExtractParams(memberdef_, specialization_); }
    TypeAnalyzer GetReturnType() const { return ExtractType(memberdef_, specialization_); }
    vector<string> GetTemplateParams() const { return ExtractTemplateParams(memberdef_); }
    bool IsDefine() const { return CONTAINS(SourceData::defines_, GetName()); }
    bool IsTemplate() const { return ::IsTemplate(memberdef_); }
    string JoinParamsNames(bool skipContext = false) const { return ::JoinParamsNames(memberdef_, skipContext); }
    string JoinParamsTypes() const { return ::JoinParamsTypes(memberdef_, specialization_); }

    virtual string GetLocation() const { return GetFunctionLocation(memberdef_); }
};

// <compounddef kind="class|struct">
//     <sectiondef>
//         <memberdef kind="function">...</memberdef>
class ClassFunctionAnalyzer : public FunctionAnalyzer
{
    ClassAnalyzer classAnalyzer_;

public:
    ClassFunctionAnalyzer(const ClassAnalyzer& classAnalyzer, xml_node memberdef, const TemplateSpecialization& specialization = {});

    ClassAnalyzer GetClass() const { return classAnalyzer_; }

    // <memberdef kind="function" virt="...">
    string GetVirt() const;
    bool IsPureVirtual() const { return GetVirt() == "pure-virtual"; }

    // <memberdef kind="function" const="yes">
    bool IsConst() const;

    // <memberdef>
    // <reimplements refid="..."></reimplements>
    shared_ptr<ClassFunctionAnalyzer> Reimplements() const;

    string GetClassName() const { return classAnalyzer_.GetClassName(); }
    string GetContainsClassName() const; // May this function defined in parent class, so return name o class, real define this function
    bool IsStatic() const { return ::IsStatic(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }
    bool IsThisConstructor() const { return GetName() == GetClassName(); }
    bool IsThisDefaultConstructor() const { return IsThisConstructor() && ExtractCleanedFunctionArgsstring(memberdef_).empty(); }
    bool IsThisNonDefaultConstructor() const { return IsThisConstructor() && !ExtractCleanedFunctionArgsstring(memberdef_).empty(); }
    bool IsParentConstructor() const;
    bool IsThisDestructor() const { return GetName() == "~" + GetClassName(); }
    bool IsParentDestructor() const;
    bool CanBeGetProperty() const;
    bool CanBeSetProperty() const;
    bool IsExplicit() const { return ::IsExplicit(memberdef_); }
    bool IsDeleted() const { return EndsWith(ExtractArgsstring(memberdef_), "=delete"); }
    bool IsConsversionOperator() const { return StartsWith(GetName(), "operator "); }

    string GetLocation() const override { return JoinNonEmpty({ classAnalyzer_.usingLocation_, GetFunctionLocation(memberdef_) }, " | "); }
};

// <compounddef kind="class|struct">
//     <sectiondef>
//         <memberdef kind="variable">...</memberdef>
class ClassVariableAnalyzer
{
    ClassAnalyzer classAnalyzer_;
    xml_node memberdef_;

public:
    ClassVariableAnalyzer(ClassAnalyzer classAnalyzer, xml_node memberdef);

    bool IsStatic() const { return ::IsStatic(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
    string GetName() const { return ExtractName(memberdef_); }
    string GetComment() const { return ExtractComment(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }
    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    string GetLocation() const;
    string GetClassName() const { return classAnalyzer_.GetClassName(); }
    bool IsArray() const { return StartsWith(ExtractArgsstring(memberdef_), "["); };
};

// <compounddef kind="namespace">
//     <sectiondef kind="func">
//         <memberdef kind="function">...</memberdef>
class GlobalFunctionAnalyzer : public FunctionAnalyzer
{
public:
    GlobalFunctionAnalyzer(xml_node memberdef, const TemplateSpecialization& specialization = {});
};

// <compounddef kind="class|struct">
//     <sectiondef kind="public-static-func">
//         <memberdef kind="function" prot="public" static="yes">...</memberdef>
class ClassStaticFunctionAnalyzer : public FunctionAnalyzer
{
    ClassAnalyzer classAnalyzer_;

public:
    ClassStaticFunctionAnalyzer(const ClassAnalyzer& classAnalyzer, xml_node memberdef, const TemplateSpecialization& specialization = {});

    string GetClassName() const { return classAnalyzer_.GetClassName(); }
};

// <memberdef kind="typedef">
//     <definition>using ...</definition>
class UsingAnalyzer
{
private:
    xml_node memberdef_;

public:
    UsingAnalyzer(xml_node memberdef);

    string GetComment() const { return ExtractComment(memberdef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    string GetLocation() const { return "using " + GetName() + " = " + GetType().ToString() + " | File: " + GetHeaderFile(); }
    string GetName() const { return ExtractName(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
};

// <compounddef kind = "namespace">...</compounddef>
class NamespaceAnalyzer
{
private:
    xml_node compounddef_;

public:
    NamespaceAnalyzer(xml_node compounddef);

    // <compounddef kind="namespace">
    //     <sectiondef kind="enum">
    //         <memberdef kind="enum">...</memberdef>
    //         <memberdef kind="enum">...</memberdef>
    vector<EnumAnalyzer> GetEnums();

    // <compounddef kind="namespace">
    //     <sectiondef kind="var">
    //         <memberdef kind="variable">...</memberdef>
    //         <memberdef kind="variable">...</memberdef>
    vector<GlobalVariableAnalyzer> GetVariables();

    // <compounddef kind="namespace">
    //     <sectiondef kind="func">
    //         <memberdef kind="function">...</memberdef>
    //         <memberdef kind="function">...</memberdef>
    vector<GlobalFunctionAnalyzer> GetFunctions();
};

