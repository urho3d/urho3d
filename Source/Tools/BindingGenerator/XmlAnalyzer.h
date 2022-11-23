// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <PugiXml/pugixml.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>

#include "XmlSourceData.h"
#include "Utils.h"

using TemplateSpecialization = std::map<std::string, std::string>;

// <type>...</type> | <defval>...</defval> | <para>...</para>
std::string RemoveRefs(pugi::xml_node node);

// <type>...</type>
class TypeAnalyzer
{
private:
    std::string fullType_;
    std::string name_;
    bool isConst_;
    bool isConstexpr_;
    bool isPointer_; // *
    bool isReference_; // &
    bool isRvalueReference_; // &&
    bool isDoublePointer_; // **
    bool isRefToPoiner_; // *&
    std::string templateParams_;

public:
    TypeAnalyzer(pugi::xml_node type, const TemplateSpecialization& specialization = {});

    // Used for doxygen bug workaround https://github.com/doxygen/doxygen/issues/7732
    TypeAnalyzer(const std::string& typeName);

    std::string ToString() const { return fullType_; }
    std::string GetName() const { return name_; }
    bool IsConst() const { return isConst_; }
    bool IsConstexpr() const { return isConstexpr_; }
    bool IsPointer() const { return isPointer_; }
    bool IsReference() const { return isReference_; }
    bool IsRvalueReference() const { return isRvalueReference_; }
    bool IsDoublePointer() const { return isDoublePointer_; }
    bool IsRefToPointer() const { return isRefToPoiner_; }
    bool IsTemplate() const { return templateParams_.length() > 0; }
    std::string GetTemplateParams() { return templateParams_; }
    std::string GetNameWithTemplateParams() const { return IsTemplate() ? name_ + "<" + templateParams_ + ">" : name_; }
};

// <memberdef kind="function">
//     <param>...</param>
class ParamAnalyzer
{
private:
    pugi::xml_node node_;
    TemplateSpecialization specialization_; 

public:
    ParamAnalyzer(pugi::xml_node param, const TemplateSpecialization& specialization = {});

    pugi::xml_node GetNode() const { return node_; }

    std::string ToString() const;

    // <param>
    //     <type>....</type>
    TypeAnalyzer GetType() const;

    // <param>
    //     <declname>....</declname>
    std::string GetDeclname() const;

    // <param>
    //     <defval>....</defval>
    std::string GetDefval() const; // Default value
};

// <memberdef>
inline bool IsMemberdef(pugi::xml_node node) { return node.name() == std::string("memberdef"); }

// <compounddef>
inline bool IsCompounddef(pugi::xml_node node) { return node.name() == std::string("compounddef"); }

// <member>
inline bool IsMember(pugi::xml_node node) { return node.name() == std::string("member"); }

// <sectiondef>
inline bool IsSectiondef(pugi::xml_node node) { return node.name() == std::string("sectiondef"); }

// <enumvalue>
inline bool IsEnumvalue(pugi::xml_node node) { return node.name() == std::string("enumvalue"); }

// <compounddef>
//     <compoundname>...</compoundname>
std::string ExtractCompoundname(pugi::xml_node compounddef);

// <compounddef>
//     <sectiondef kind="xxx">...</sectiondef>
pugi::xml_node FindSectiondef(pugi::xml_node compounddef, const std::string& kind);

// <memberdef static="yes">
bool IsStatic(pugi::xml_node memberdef);

// <memberdef kind="function" explicit="yes">
bool IsExplicit(pugi::xml_node memberdef);

// <memberdef>
//     <definition>...</definition>
std::string ExtractDefinition(pugi::xml_node memberdef);

// <memberdef>
//     <argsstring>...</argsstring>
std::string ExtractArgsstring(pugi::xml_node memberdef);

// <memberdef kind="function">
//     <argsstring>(...)</argsstring>
//     <argsstring>(...) xxx</argsstring>
//         where xxx can be of const, override, =default, =delete, =0 or their combination
std::string ExtractCleanedFunctionArgsstring(pugi::xml_node memberdef);

// <memberdef prot="...">
std::string ExtractProt(pugi::xml_node memberdef);

// <memberdef>
//     <type>...</type>
TypeAnalyzer ExtractType(pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});

// <memberdef kind="function">
//     <param>...</param>
//     <param>...</param>
std::vector<ParamAnalyzer> ExtractParams(pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});

// <memberdef kind="function">
//     <param>...</param>
//     <param>...</param>
std::string JoinParamsTypes(pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});
std::string JoinParamsNames(pugi::xml_node memberdef, bool skipContext = false);

// <memberdef kind="function">
//     ...
std::string GetFunctionDeclaration(pugi::xml_node memberdef);

// <memberdef kind="variable">
//     ...
std::string GetVariableDeclaration(pugi::xml_node memberdef);

// <memberdef kind="function">
//     ...
std::string GetFunctionLocation(pugi::xml_node memberdef);

// <compounddef|memberdef id="...">
std::string ExtractID(pugi::xml_node node);

// <compounddef|memberdef|member|sectiondef kind="...">
std::string ExtractKind(pugi::xml_node node);

// <memberdef|enumvalue>
//     <name>...</name>
std::string ExtractName(pugi::xml_node node);

// <compounddef|memberdef>
//     <location line="...">
std::string ExtractLine(pugi::xml_node node);

// <compounddef|memberdef>
//     <location column="...">
std::string ExtractColumn(pugi::xml_node node);

// <compounddef|memberdef>
//     <briefdescription>...</briefdescription>
//     <detaileddescription>...</detaileddescription>
std::string ExtractComment(pugi::xml_node node);

// <compounddef|memberdef>
//     <location ...>
// Extract header file path and convert to relative.
// Return empty std::string when declared in *.cpp
std::string ExtractHeaderFile(pugi::xml_node node);

// <compounddef|memberdef>
//     <templateparamlist>
bool IsTemplate(pugi::xml_node node);

// <compounddef|memberdef>
//     <templateparamlist>
//         <param>...</param>
//         <param>...</param>
std::vector<std::string> ExtractTemplateParams(pugi::xml_node node);

// <compounddef kind="namespace">
//     <sectiondef kind="enum">
//         <memberdef kind="enum">...</memberdef>
class EnumAnalyzer
{
    pugi::xml_node memberdef_;

public:
    EnumAnalyzer(pugi::xml_node memberdef);

    std::string GetTypeName() const { return ExtractName(memberdef_); }
    std::string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    std::string GetComment() const { return ExtractComment(memberdef_); }
    bool IsInternal() const { return GetHeaderFile().empty(); } // true if declared in .cpp file
    std::string GetBaseType() const;
    std::string GetLocation() const;

    // <memberdef kind="enum">
    //     <enumvalue><name>...</name></enumvalue>
    //     <enumvalue><name>...</name></enumvalue>
    std::vector<std::string> GetEnumerators() const;

};

// <compounddef kind="namespace">
//     <sectiondef kind="var">
//         <memberdef kind="variable">...</memberdef>
class GlobalVariableAnalyzer
{
    pugi::xml_node memberdef_;

public:
    GlobalVariableAnalyzer(pugi::xml_node memberdef);

    std::string GetName() const { return ExtractName(memberdef_); }
    std::string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    bool IsStatic() const { return ::IsStatic(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
    bool IsArray() const { return StartsWith(ExtractArgsstring(memberdef_), "["); }
    std::string GetLocation() const { return GetVariableDeclaration(memberdef_) + " | File: " + GetHeaderFile(); }
};

class MethodAnalyzer;
class FieldAnalyzer;

// <compounddef kind="class|struct">...</compounddef>
class ClassAnalyzer
{
private:
    pugi::xml_node compounddef_;
    TemplateSpecialization specialization_;
    
    std::vector<pugi::xml_node> GetMemberdefs() const;

public:
    std::string usingLocation_;

    pugi::xml_node GetCompounddef() const { return compounddef_; }

    ClassAnalyzer(pugi::xml_node compounddef, const TemplateSpecialization& specialization = {});

    const TemplateSpecialization& GetSpecialization() const { return specialization_; }

    std::string GetClassName() const;
    std::string GetComment() const { return ExtractComment(compounddef_); }
    std::string GetHeaderFile() const { return ExtractHeaderFile(compounddef_); }
    std::string GetDirName() const;
    std::string GetKind() const { return ExtractKind(compounddef_); }
    bool IsInternal() const;
    bool IsTemplate() const { return ::IsTemplate(compounddef_); }
    std::vector<MethodAnalyzer> GetAllMethods() const;
    std::vector<MethodAnalyzer> GetAllPublicMethods() const;
    std::vector<MethodAnalyzer> GetThisPublicMethods() const;
    std::vector<MethodAnalyzer> GetThisPublicStaticMethods() const;
    std::vector<FieldAnalyzer> GetAllFields() const;
    std::vector<FieldAnalyzer> GetThisPublicFields() const;
    std::vector<FieldAnalyzer> GetThisPublicStaticFields() const;
    bool ContainsMethod(const std::string& name) const;
    std::shared_ptr<MethodAnalyzer> GetMethod(const std::string& name) const;
    int NumMethods(const std::string& name) const;
    bool IsRefCounted() const;
    bool HasThisDestructor() const { return ContainsMethod("~" + GetClassName()); }
    bool HasThisConstructor() const;
    bool IsAbstract() const;
    std::string GetLocation() const { return GetKind() + " " + GetClassName() + " | File: " + GetHeaderFile(); }
    bool AllFloats() const;
    bool AllInts() const;
    bool IsPod() const;
    bool IsNoCount() const { return Contains(GetComment(), "NO_COUNT"); } // Have @nocount in comment -> asOBJ_NOCOUNT
    std::shared_ptr<ClassAnalyzer> GetBaseClass() const;
    std::vector<ClassAnalyzer> GetBaseClasses() const;
    std::vector<ClassAnalyzer> GetAllBaseClasses() const;

    std::vector<ClassAnalyzer> GetDerivedClasses() const;
    std::vector<ClassAnalyzer> GetAllDerivedClasses() const;
    
    // Return null if default constructor is implicitly-declared.
    // Return pointer if default constructor is deleted
    std::shared_ptr<MethodAnalyzer> GetDefinedThisDefaultConstructor() const;

    std::vector<MethodAnalyzer> GetThisNonDefaultConstructors() const;

    // Return null if destructor is implicitly-declared.
    // Return pointer if destructor is deleted
    std::shared_ptr<MethodAnalyzer> GetDefinedThisDestructor() const { return GetMethod("~" + GetClassName()); }

    int GetInherianceDeep(int counter = 0) const;
    
    std::vector<std::string> GetAllPublicMembersRefids() const;

    // Base class members that were hidden in this class (c++ declarations)
    std::vector<std::string> GetHiddenMethods() const;
    std::vector<std::string> GetHiddenStaticMethods() const;
    std::vector<std::string> GetHiddenFields() const;
    std::vector<std::string> GetHiddenStaticFields() const;
};

// <memberdef kind="function">...</memberdef>
class FunctionAnalyzer
{
protected:
    pugi::xml_node memberdef_;
    TemplateSpecialization specialization_;

public:
    FunctionAnalyzer(pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});
    
    pugi::xml_node GetMemberdef() const { return memberdef_; }
    const TemplateSpecialization& GetSpecialization() const { return specialization_; }

    std::string GetComment() const { return ExtractComment(memberdef_); }
    std::string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    std::string GetName() const { return ExtractName(memberdef_); }
    std::vector<ParamAnalyzer> GetParams() const { return ExtractParams(memberdef_, specialization_); }
    TypeAnalyzer GetReturnType() const { return ExtractType(memberdef_, specialization_); }
    std::vector<std::string> GetTemplateParams() const { return ExtractTemplateParams(memberdef_); }
    bool IsDefine() const { return CONTAINS(SourceData::defines_, GetName()); }
    bool IsTemplate() const { return ::IsTemplate(memberdef_); }
    std::string JoinParamsNames(bool skipContext = false) const { return ::JoinParamsNames(memberdef_, skipContext); } // TODO убрать skipContext, он больше не нужен
    std::string JoinParamsTypes() const { return ::JoinParamsTypes(memberdef_, specialization_); }

    virtual std::string GetLocation() const { return GetFunctionLocation(memberdef_); }
};

// <compounddef kind="class|struct">
//     <sectiondef>
//         <memberdef kind="function">...</memberdef>
class MethodAnalyzer : public FunctionAnalyzer
{
    ClassAnalyzer classAnalyzer_;

public:
    MethodAnalyzer(const ClassAnalyzer& classAnalyzer, pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});

    ClassAnalyzer GetClass() const { return classAnalyzer_; }

    // <memberdef kind="function" virt="...">
    std::string GetVirt() const;
    bool IsPureVirtual() const { return GetVirt() == "pure-virtual"; }

    // <memberdef kind="function" const="yes">
    bool IsConst() const;

    // <memberdef>
    // <reimplements refid="..."></reimplements>
    std::shared_ptr<MethodAnalyzer> Reimplements() const;

    std::string GetClassName() const { return classAnalyzer_.GetClassName(); }
    std::string GetContainsClassName() const; // May this function defined in parent class, so return name oа class, real define this function
    bool IsStatic() const { return ::IsStatic(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }

    // Constructor can have different name https://github.com/doxygen/doxygen/issues/8402
    bool IsThisConstructor() const { return GetName() == GetClassName(); }
    
    bool IsThisDefaultConstructor() const { return IsThisConstructor() && ExtractCleanedFunctionArgsstring(memberdef_).empty(); }
    bool IsThisNonDefaultConstructor() const { return IsThisConstructor() && !ExtractCleanedFunctionArgsstring(memberdef_).empty(); }
    bool IsConstructor() const;
    bool IsDestructor() const;
    bool IsParentConstructor() const;
    bool IsThisDestructor() const { return GetName() == "~" + GetClassName(); }
    bool IsParentDestructor() const;
    bool CanBeGetProperty() const;
    bool CanBeSetProperty() const;
    bool IsExplicit() const { return ::IsExplicit(memberdef_); }
    bool IsDeleted() const { return EndsWith(ExtractArgsstring(memberdef_), "=delete"); }
    bool IsConsversionOperator() const { return StartsWith(GetName(), "operator "); }

    bool IsThisMethod() const { return GetContainsClassName() == GetClassName(); } // Defined in this class

    bool IsPrefixIncrementOperator() const { return GetName() == "operator++" && GetParams().size() == 0; }
    bool IsPostfixIncrementOperator() const { return GetName() == "operator++" && GetParams().size() != 0; }
    bool IsPrefixDecrementOperator() const { return GetName() == "operator--" && GetParams().size() == 0; }
    bool IsPostfixDecrementOperator() const { return GetName() == "operator--" && GetParams().size() != 0; }

    std::string GetDeclaration() const { return JoinNonEmpty({ classAnalyzer_.usingLocation_, GetFunctionDeclaration(memberdef_) }, " | "); }
    std::string GetLocation() const override { return JoinNonEmpty({ classAnalyzer_.usingLocation_, GetFunctionLocation(memberdef_) }, " | "); }
};

// <compounddef kind="class|struct">
//     <sectiondef>
//         <memberdef kind="variable">...</memberdef>
class FieldAnalyzer
{
    ClassAnalyzer classAnalyzer_;
    pugi::xml_node memberdef_;

public:
    FieldAnalyzer(ClassAnalyzer classAnalyzer, pugi::xml_node memberdef);

    bool IsStatic() const { return ::IsStatic(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
    std::string GetName() const { return ExtractName(memberdef_); }
    std::string GetComment() const { return ExtractComment(memberdef_); }
    bool IsPublic() const { return ExtractProt(memberdef_) == "public"; }
    std::string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    std::string GetDeclaration() const { return GetVariableDeclaration(memberdef_); }
    std::string GetLocation() const;
    std::string GetClassName() const { return classAnalyzer_.GetClassName(); }
    bool IsArray() const { return StartsWith(ExtractArgsstring(memberdef_), "["); };
};

// <compounddef kind="namespace">
//     <sectiondef kind="func">
//         <memberdef kind="function">...</memberdef>
class GlobalFunctionAnalyzer : public FunctionAnalyzer
{
public:
    GlobalFunctionAnalyzer(pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});
};

// <compounddef kind="class|struct">
//     <sectiondef kind="public-static-func">
//         <memberdef kind="function" prot="public" static="yes">...</memberdef>
class ClassStaticFunctionAnalyzer : public FunctionAnalyzer
{
    ClassAnalyzer classAnalyzer_;

public:
    ClassStaticFunctionAnalyzer(const ClassAnalyzer& classAnalyzer, pugi::xml_node memberdef, const TemplateSpecialization& specialization = {});

    std::string GetClassName() const { return classAnalyzer_.GetClassName(); }
};

// <memberdef kind="typedef">
//     <definition>using ...</definition>
class UsingAnalyzer
{
private:
    pugi::xml_node memberdef_;

public:
    UsingAnalyzer(pugi::xml_node memberdef);

    std::string GetComment() const { return ExtractComment(memberdef_); }
    std::string GetHeaderFile() const { return ExtractHeaderFile(memberdef_); }
    std::string GetLocation() const { return "using " + GetName() + " = " + GetType().ToString() + " | File: " + GetHeaderFile(); }
    std::string GetName() const { return ExtractName(memberdef_); }
    TypeAnalyzer GetType() const { return ExtractType(memberdef_); }
};

// <compounddef kind = "namespace">...</compounddef>
class NamespaceAnalyzer
{
private:
    pugi::xml_node compounddef_;

public:
    NamespaceAnalyzer(pugi::xml_node compounddef);

    // <compounddef kind="namespace">
    //     <sectiondef kind="enum">
    //         <memberdef kind="enum">...</memberdef>
    //         <memberdef kind="enum">...</memberdef>
    std::vector<EnumAnalyzer> GetEnums();

    // <compounddef kind="namespace">
    //     <sectiondef kind="var">
    //         <memberdef kind="variable">...</memberdef>
    //         <memberdef kind="variable">...</memberdef>
    std::vector<GlobalVariableAnalyzer> GetVariables();

    // <compounddef kind="namespace">
    //     <sectiondef kind="func">
    //         <memberdef kind="function">...</memberdef>
    //         <memberdef kind="function">...</memberdef>
    std::vector<GlobalFunctionAnalyzer> GetFunctions();
};

