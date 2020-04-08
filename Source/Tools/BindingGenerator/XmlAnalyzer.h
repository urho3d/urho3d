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
#include <vector>

using namespace pugi;
using namespace std;


// <type>...</type>
class TypeAnalyzer
{
private:
    xml_node node_;

public:
    TypeAnalyzer(xml_node type);
    xml_node GetNode() const { return node_; }
    bool IsEmpty() const { return node_.empty(); }
    string ToString() const;
    string GetName() const;

    // type*
    bool IsPointer() const;

    // type&
    bool IsReference() const;

    // const type
    bool IsConst() const;
};

// ============================================================================

// <memberdef kind="function">
//     <param>...</param>
class ParamAnalyzer
{
private:
    xml_node node_;

public:
    ParamAnalyzer(xml_node param);
    xml_node GetNode() const { return node_; }

    // <param>
    //     <type>....</type>
    TypeAnalyzer GetType() const;

    // <param>
    //     <declname>....</declname>
    string GetDeclname() const;

    // "type name"
    string ToString() const;
};

// ============================================================================

// <memberdef>
bool IsMemberdef(xml_node node);

// <compounddef>
bool IsCompounddef(xml_node node);

// <compounddef|memberdef id="...">
string ExtractID(xml_node node);

// <compounddef|memberdef kind="...">
string ExtractKind(xml_node node);

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

// ============================================================================

// <compounddef>
//     <compoundname>...</compoundname>
string ExtractCompoundname(xml_node compounddef);

// <compounddef>
//     <sectiondef kind="xxx">...</sectiondef>
xml_node FindSectiondef(xml_node compounddef, const string& kind);

// ============================================================================

// <memberdef>
//     <name>...</name>
string ExtractName(xml_node memberdef);

// <memberdef static="yes">
bool IsStatic(xml_node memberdef);

// <memberdef>
//     <type>...</type>
TypeAnalyzer ExtractType(xml_node memberdef);

// <memberdef prot="...">
string ExtractProt(xml_node memberdef);

// <memberdef kind="function">
//     <param>...</param>
//     <param>...</param>
vector<ParamAnalyzer> ExtractParams(xml_node memberdef);

// ============================================================================

// <compounddef kind="namespace">
//     <sectiondef kind="enum">
//         <memberdef kind="enum">...</memberdef>
class EnumAnalyzer
{
    xml_node memberdef_;

public:
    EnumAnalyzer(xml_node memberdef);
    string GetTypeName() const { return ExtractName(memberdef_); }

    // <memberdef kind="enum">
    //     <enumvalue><name>...</name></enumvalue>
    //     <enumvalue><name>...</name></enumvalue>
    vector<string> GetEnumerators() const;

    string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    string GetComment() const { return ExtractComment(memberdef_); }
    string GetLocation() const;

    // true if declared in .cpp file
    bool IsInternal() const { return GetHeaderFile().empty(); }
};

// ============================================================================

class ClassFunctionAnalyzer;
class ClassVariableAnalyzer;

// <compounddef kind="class|struct">...</compounddef>
class ClassAnalyzer
{
private:
    xml_node compounddef_;
    
    vector<xml_node> GetMemberdefs() const;
    bool ContainsFunction(const string& name) const;

public:
    ClassAnalyzer(xml_node compounddef);

    string GetClassName() const;
    string GetComment() const { return ExtractComment(compounddef_); }
    string GetHeaderFile() const { return ExtractHeaderFile(compounddef_); }
    string GetKind() const { return ExtractKind(compounddef_); }
    bool IsInternal() const;
    bool IsTemplate() const { return !compounddef_.child("templateparamlist").empty(); }
    vector<ClassFunctionAnalyzer> GetFunctions() const;
    vector<ClassVariableAnalyzer> GetVariables() const;
    bool IsRefCounted() const { return ContainsFunction("AddRef") && ContainsFunction("ReleaseRef"); }
    bool IsAbstract() const;
    string GetLocation() const;
    bool AllFloats() const;
    bool AllInts() const;
    bool IsPod() const;
};

// ============================================================================

// <compounddef kind="class|struct">
//     <sectiondef>
//         <memberdef kind="function">...</memberdef>
class ClassFunctionAnalyzer
{
    ClassAnalyzer classAnalyzer_;
    xml_node memberdef_;

public:
    ClassFunctionAnalyzer(ClassAnalyzer classAnalyzer, xml_node memberdef);
    ClassAnalyzer GetClass() const { return classAnalyzer_; }
    xml_node GetMemberdef() const { return memberdef_; }

    // <memberdef kind="function" virt="...">
    string GetVirt() const;
    bool IsPureVirtual() const { return GetVirt() == "pure-virtual"; }

    // <memberdef kind="function" const="yes">
    bool IsConst() const;

    string GetName() const { return ExtractName(memberdef_); }
    string GetClassName() const { return classAnalyzer_.GetClassName(); }
    string GetLine() const { return ExtractLine(memberdef_); }
    string GetColumn() const { return ExtractColumn(memberdef_); }
    string GetComment() const { return ExtractComment(memberdef_); }
    bool IsStatic() const { return ::IsStatic(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }
    bool IsConstrunctor() const { return GetName() == GetClassName(); }
    string GetLocation(bool detailed) const;
    string GetHeaderFile() const { return classAnalyzer_.GetHeaderFile(); }
    TypeAnalyzer GetReturnType() const { return ExtractType(memberdef_); }
    bool CanBeGetProperty() const;
    bool CanBeSetProperty() const;
    
    // <memberdef kind="function">
    //     <name>operator xxx</name>
    bool IsConsversionOperator() const;
    
    // <memberdef kind="function" explicit="yes">
    bool IsExplicit() const;

    vector<ParamAnalyzer> GetParams() const { return ExtractParams(memberdef_); }
    string JoinParamsNames() const;
    string JoinParamsTypes() const;
};

// ============================================================================

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
    TypeAnalyzer GetType() const;
    string GetName() const { return ExtractName(memberdef_); }
    string GetComment() const { return ExtractComment(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }
    string GetHeaderFile() const { return classAnalyzer_.GetHeaderFile(); }
    string GetLocation() const;
    string GetClassName() const { return classAnalyzer_.GetClassName(); }
};

// ============================================================================

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
};
