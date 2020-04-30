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

#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <cassert>
#include <regex>


TypeAnalyzer::TypeAnalyzer(xml_node type)
    : node_(type)
{
    assert(!node_.empty() && node_.name() == string("type"));
}

string TypeAnalyzer::ToString() const
{
    string result;

    for (xml_node part : node_.children())
    {
        if (part.name() == string("ref"))
            result += part.child_value();
        else
            result += part.value();
    }

    return result;
}

bool TypeAnalyzer::IsPointer() const
{
    return EndsWith(ToString(), " *");
}

bool TypeAnalyzer::IsReference() const
{
    return EndsWith(ToString(), " &");
}

bool TypeAnalyzer::IsConst() const
{
    return StartsWith(ToString(), "const ");
}

string TypeAnalyzer::GetName() const
{
    string result = ToString();
    result = CutStart(result, "const ");
    result = CutEnd(result, " *");
    result = CutEnd(result, " &");
    return result;
}

// ============================================================================

ParamAnalyzer::ParamAnalyzer(xml_node param)
    : node_(param)
{
    assert(!node_.empty() && node_.name() == string("param"));
}

string ParamAnalyzer::GetDeclname() const
{
    string result = node_.child("declname").child_value();
    assert(!result.empty());

    return result;
}

TypeAnalyzer ParamAnalyzer::GetType() const
{
    xml_node type = node_.child("type");
    assert(!type.empty());

    return TypeAnalyzer(type);
}

string ParamAnalyzer::ToString() const
{
    string type = GetType().ToString();
    assert(!type.empty());

    string name = GetDeclname();
    assert(!name.empty());

    return type + " " + name;
}

// ============================================================================

bool IsMemberdef(xml_node node)
{
    return node.name() == string("memberdef");
}

bool IsCompounddef(xml_node node)
{
    return node.name() == string("compounddef");
}

string ExtractID(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    string result = node.attribute("id").value();
    assert(!result.empty());

    return result;
}

string ExtractKind(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    string result = node.attribute("kind").value();
    assert(!result.empty());

    return result;
}

string ExtractLine(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    string result = node.child("location").attribute("line").value();
    assert(!result.empty());

    return result;
}

string ExtractColumn(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    string result = node.child("location").attribute("column").value();
    assert(!result.empty());

    return result;
}

static string DescriptionToString(xml_node description)
{
    string result;

    for (xml_node para : description.children("para"))
    {
        for (xml_node part : para.children())
        {
            if (part.name() == string("ref"))
                result += part.child_value();
            else
                result += part.value();
        }
    }

    return result;
}

string ExtractComment(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    xml_node brief = node.child("briefdescription");
    assert(brief);

    xml_node detailed = node.child("detaileddescription");
    assert(detailed);

    return DescriptionToString(brief) + DescriptionToString(detailed);
}

static string HeaderFullPathToRelative(const string& fullPath)
{
    size_t pos = fullPath.rfind("Source/Urho3D");
    assert(pos != string::npos);

    return ".." + fullPath.substr(pos + strlen("Source/Urho3D"));
}

string ExtractHeaderFile(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    xml_node location = node.child("location");
    assert(!location.empty());

    string declfile = location.attribute("declfile").value();
    if (EndsWith(declfile, ".h"))
        return HeaderFullPathToRelative(declfile);

    string file = location.attribute("file").value();
    if (EndsWith(file, ".h"))
        return HeaderFullPathToRelative(file);

    return string();
}

// ============================================================================

string ExtractCompoundname(xml_node compounddef)
{
    assert(IsCompounddef(compounddef));

    string result = compounddef.child("compoundname").child_value();
    assert(!result.empty());

    return result;
}

xml_node FindSectiondef(xml_node compounddef, const string& kind)
{
    assert(IsCompounddef(compounddef) && !kind.empty());

    for (xml_node sectiondef : compounddef.children("sectiondef"))
    {
        string kindAttr = sectiondef.attribute("kind").value();
        if (kindAttr == kind)
            return sectiondef;
    }

    return xml_node();
}

// ============================================================================

string ExtractName(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string result = memberdef.child("name").child_value();
    assert(!result.empty());

    return result;
}

bool IsStatic(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string staticAttr = memberdef.attribute("static").value();
    assert(!staticAttr.empty());

    return staticAttr == "yes";
}

TypeAnalyzer ExtractType(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    xml_node type = memberdef.child("type");
    assert(type);

    return TypeAnalyzer(type);
}

string ExtractProt(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string result = memberdef.attribute("prot").value();
    assert(!result.empty());
    
    return result;
}

vector<ParamAnalyzer> ExtractParams(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    vector<ParamAnalyzer> result;

    for (xml_node param : memberdef.children("param"))
        result.push_back(ParamAnalyzer(param));

    return result;
}

// ============================================================================

EnumAnalyzer::EnumAnalyzer(xml_node memberdef)
    : memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "enum");
}

vector<string> EnumAnalyzer::GetEnumerators() const
{
    vector<string> result;

    for (xml_node enumvalue : memberdef_.children("enumvalue"))
    {
        string name = enumvalue.child("name").child_value();
        assert(!name.empty());

        result.push_back(name);
    }

    return result;
}

string EnumAnalyzer::GetLocation() const
{
    return "enum " + GetTypeName() + " | File: " + GetHeaderFile() + " | Line: " + ExtractLine(memberdef_);
}

// ============================================================================

ClassAnalyzer::ClassAnalyzer(xml_node compounddef)
    : compounddef_(compounddef)
{
    assert(IsCompounddef(compounddef));
}

string ClassAnalyzer::GetClassName() const
{
    string compoundname = ExtractCompoundname(compounddef_);
    assert(StartsWith(compoundname, "Urho3D::"));
    return CutStart(compoundname, "Urho3D::");
}

bool ClassAnalyzer::IsInternal() const
{
    if (GetHeaderFile().empty()) // Defined in *.cpp
        return true;

    if (Contains(GetClassName(), "::")) // Defined inside another class
        return true;

    return false;
}

vector<xml_node> ClassAnalyzer::GetMemberdefs() const
{
    vector<xml_node> result;

    xml_node listofallmembers = compounddef_.child("listofallmembers");
    assert(listofallmembers);

    for (xml_node member : listofallmembers.children("member"))
    {
        xml_attribute ambiguityscope = member.attribute("ambiguityscope");
        if (!ambiguityscope.empty()) // Overridden method from parent class
            continue;

        string refid = member.attribute("refid").value();
        assert(!refid.empty());
        xml_node memberdef = SourceData::members_[refid];
        if (memberdef)
            result.push_back(memberdef);
    }

    return result;
}

vector<ClassFunctionAnalyzer> ClassAnalyzer::GetFunctions() const
{
    vector<ClassFunctionAnalyzer> result;
   
    vector<xml_node> memberdefs = GetMemberdefs();

    for (xml_node memberdef : memberdefs)
    {
        if (ExtractKind(memberdef) == "function")
            result.push_back(ClassFunctionAnalyzer(*this, memberdef));
    }

    return result;
}

vector<ClassVariableAnalyzer> ClassAnalyzer::GetVariables() const
{
    vector<ClassVariableAnalyzer> result;

    vector<xml_node> memberdefs = GetMemberdefs();

    for (xml_node memberdef : memberdefs)
    {
        if (ExtractKind(memberdef) == "variable")
            result.push_back(ClassVariableAnalyzer(*this, memberdef));
    }

    return result;
}

bool ClassAnalyzer::ContainsFunction(const string& name) const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (ClassFunctionAnalyzer function : functions)
    {
        if (function.GetName() == name)
            return true;
    }

    return false;
}

bool ClassAnalyzer::IsAbstract() const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (ClassFunctionAnalyzer function : functions)
    {
        if (function.IsPureVirtual())
        {
            if (!IsRefCounted())
                return true;

            // Some pure virtual functions is implemented by URHO3D_OBJECT
            string name = function.GetName();
            if (name == "GetType" || name == "GetTypeInfo" || name == "GetTypeName")
            {
                if (ContainsFunction("URHO3D_OBJECT"))
                    continue;
            }

            return true;
        }
    }

    return false;
}

bool ClassAnalyzer::AllFloats() const
{
    if (Contains(GetComment(), "ALL_FLOATS")) // TODO: remove
        return true;

    vector<ClassVariableAnalyzer> variables = GetVariables();

    for (ClassVariableAnalyzer variable : variables)
    {
        if (variable.IsStatic())
            continue;

        string type = variable.GetType().ToString();
        if (type != "float" && type != "double")
            return false;
    }

    return true;
}

bool ClassAnalyzer::AllInts() const
{
    if (Contains(GetComment(), "ALL_INTS")) // TODO: remove
        return true;

    vector<ClassVariableAnalyzer> variables = GetVariables();

    for (ClassVariableAnalyzer variable : variables)
    {
        if (variable.IsStatic())
            continue;

        string type = variable.GetType().ToString();
        if (type != "int" && type != "unsigned")
            return false;
    }

    return true;
}

bool ClassAnalyzer::IsPod() const
{
    bool result = Contains(GetComment(), "IS_POD");

    if (AllFloats() || AllInts())
        result = true;

    return result;
}

string ClassAnalyzer::GetLocation() const
{
    return GetKind() + " " + GetClassName()
        + " | File: " + GetHeaderFile() + " | Line: " + ExtractLine(compounddef_);
}

// ============================================================================

ClassFunctionAnalyzer::ClassFunctionAnalyzer(ClassAnalyzer classAnalyzer, xml_node memberdef)
    : classAnalyzer_(classAnalyzer)
    , memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");
}

string ClassFunctionAnalyzer::GetVirt() const
{
    string result = memberdef_.attribute("virt").value();
    assert(!result.empty());

    return result;
}

string ClassFunctionAnalyzer::GetLocation() const
{
    string definition = memberdef_.child("definition").child_value();
    assert(!definition.empty());

    string argsstring = memberdef_.child("argsstring").child_value();
    assert(!argsstring.empty());

    string prototype = definition + argsstring;

    // Remove Urho3D::
    smatch match;
    regex_match(prototype, match, regex("(.*)Urho3D::(.+)"));
    assert(match.size() == 3);
    string result = match[1].str() + match[2].str();

    result += " | File: " + GetHeaderFile() + " | Line: " + ExtractLine(memberdef_);

    return result;
}

string ClassFunctionAnalyzer::JoinParamsNames() const
{
    string result;

    vector<ParamAnalyzer> params = GetParams();
    for (ParamAnalyzer param : params)
    {
        if (result.length() > 0)
            result += ", ";

        result += param.GetDeclname();
    }

    return result;
}

string ClassFunctionAnalyzer::JoinParamsTypes() const
{
    string result;

    vector<ParamAnalyzer> params = GetParams();
    for (ParamAnalyzer param : params)
    {
        if (result.length() > 0)
            result += ", ";

        result += param.GetType().ToString();
    }

    return result;
}

bool ClassFunctionAnalyzer::IsConst() const
{
    string constAttr = memberdef_.attribute("const").value();
    assert(!constAttr.empty());

    return constAttr == "yes";
}

bool ClassFunctionAnalyzer::CanBeGetProperty() const
{
    string returnType = GetReturnType().ToString();

    if (returnType == "void" || returnType.empty())
        return false;

    if (GetParams().size() != 0)
        return false;

    return true;
}

bool ClassFunctionAnalyzer::CanBeSetProperty() const
{
    string returnType = GetReturnType().ToString();

    if (returnType != "void")
        return false;

    if (GetParams().size() != 1)
        return false;

    return true;
}

bool ClassFunctionAnalyzer::IsConsversionOperator() const
{
    return StartsWith(GetName(), "operator ");
}

bool ClassFunctionAnalyzer::IsExplicit() const
{
    string explicitAttr = memberdef_.attribute("explicit").value();
    assert(!explicitAttr.empty());

    return explicitAttr == "yes";
}

// ============================================================================

ClassVariableAnalyzer::ClassVariableAnalyzer(ClassAnalyzer classAnalyzer, xml_node memberdef)
    : classAnalyzer_(classAnalyzer)
    , memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "variable");
}

TypeAnalyzer ClassVariableAnalyzer::GetType() const
{
    TypeAnalyzer result = ExtractType(memberdef_);
    assert(!result.IsEmpty());
    return result;
}

string ClassVariableAnalyzer::GetLocation() const
{
    string definition = memberdef_.child("definition").child_value();
    assert(!definition.empty());
    
    // Remove Urho3D::
    smatch match;
    regex_match(definition, match, regex("(.*)Urho3D::(.+)"));
    assert(match.size() == 3);
    string result =  match[1].str() + match[2].str();

    result += " | File: " + GetHeaderFile() + " | Line: " + ExtractLine(memberdef_);

    return result;
}

// ============================================================================

NamespaceAnalyzer::NamespaceAnalyzer(xml_node compounddef)
    : compounddef_(compounddef)
{
    assert(IsCompounddef(compounddef));
    assert(ExtractKind(compounddef) == "namespace");
}

vector<EnumAnalyzer> NamespaceAnalyzer::GetEnums()
{
    xml_node sectiondef = FindSectiondef(compounddef_, "enum");
    assert(sectiondef);

    vector<EnumAnalyzer> result;

    for (xml_node memberdef : sectiondef.children("memberdef"))
    {
        EnumAnalyzer analyzer(memberdef);
        result.push_back(analyzer);
    }

    return result;
}
