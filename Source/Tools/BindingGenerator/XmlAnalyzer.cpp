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

string RemoveRefs(xml_node node)
{
    assert(node.name() == string("type") || node.name() == string("defval") || node.name() == string("para"));

    string result;

    for (xml_node part : node.children())
    {
        if (part.name() == string("ref"))
            result += part.child_value();
        else
            result += part.value();
    }

    return result;
}

TypeAnalyzer::TypeAnalyzer(xml_node type, const TemplateSpecialization& specialization)
{
    assert(type.name() == string("type"));

    fullType_ = RemoveRefs(type);
    fullType_ = RemoveFirst(fullType_, "URHO3D_API ");
    fullType_ = CutStart(fullType_, "constexpr ");
    fullType_ = ReplaceAll(fullType_, " *", "*");
    fullType_ = ReplaceAll(fullType_, " &", "&");
    fullType_ = ReplaceAll(fullType_, "< ", "<");
    fullType_ = ReplaceAll(fullType_, " >", ">");

    for (pair<const string, string> it : specialization)
    {
        regex rgx("\\b" + it.first + "\\b");
        fullType_ = regex_replace(fullType_, rgx, it.second);
    }

    isConst_ = StartsWith(fullType_, "const ");
    name_ = CutStart(fullType_, "const ");

    isRvalueReference_ = EndsWith(name_, "&&");
    name_ = CutEnd(name_, "&&");

    isRefToPoiner_ = EndsWith(name_, "*&");
    name_ = CutEnd(name_, "*&");

    isDoublePointer_ = EndsWith(name_, "**");
    name_ = CutEnd(name_, "**");

    isPointer_ = EndsWith(name_, "*");
    name_ = CutEnd(name_, "*");

    isReference_ = EndsWith(name_, "&");
    name_ = CutEnd(name_, "&");

    smatch match;
    if (regex_match(name_, match, regex("(.+?)<(.+)>")))
    {
        templateParams_ = match[2].str();
        name_ = match[1].str();
    }
}

TypeAnalyzer::TypeAnalyzer(const string& typeName)
{
    fullType_ = typeName;
    name_ = typeName;
    isConst_ = false;
    isPointer_ = false;
    isReference_ = false;
    isRvalueReference_ = false;
    isDoublePointer_ = false;
    isRefToPoiner_ = false;
}

// ============================================================================

ParamAnalyzer::ParamAnalyzer(xml_node param, const TemplateSpecialization& specialization)
    : node_(param)
    , specialization_(specialization)
{
    assert(node_.name() == string("param"));
}

string ParamAnalyzer::ToString() const
{
    string type = GetType().ToString();
    assert(!type.empty());

    string name = GetDeclname();
    assert(!name.empty());

    return type + " " + name;
}

TypeAnalyzer ParamAnalyzer::GetType() const
{
    xml_node type = node_.child("type");
    assert(type);

    return TypeAnalyzer(type, specialization_);
}

string ParamAnalyzer::GetDeclname() const
{
    string result = node_.child("declname").child_value();
    assert(!result.empty());

    return result;
}

string ParamAnalyzer::GetDefval() const
{
    xml_node defval = node_.child("defval");

    if (defval)
        return RemoveRefs(defval);

    return "";
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
    assert(IsCompounddef(compounddef));
    assert(!kind.empty());

    for (xml_node sectiondef : compounddef.children("sectiondef"))
    {
        if (ExtractKind(sectiondef) == kind)
            return sectiondef;
    }

    return xml_node();
}

bool IsStatic(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string staticAttr = memberdef.attribute("static").value();
    assert(!staticAttr.empty());

    return staticAttr == "yes";
}

bool IsExplicit(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");

    string explicitAttr = memberdef.attribute("explicit").value();
    assert(!explicitAttr.empty());

    return explicitAttr == "yes";
}

string ExtractDefinition(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string result = memberdef.child("definition").child_value();
    assert(!result.empty());

    return result;
}

string ExtractArgsstring(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    xml_node argsstring = memberdef.child("argsstring");
    assert(argsstring);

    return argsstring.child_value();
}

string ExtractCleanedFunctionArgsstring(xml_node memberdef)
{
    assert(ExtractKind(memberdef) == "function");

    string argsstring = ExtractArgsstring(memberdef);
    assert(StartsWith(argsstring, "("));

    size_t endPos = argsstring.find_last_of(')');
    assert(endPos != string::npos);

    return argsstring.substr(1, endPos - 1);
}

string ExtractProt(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));

    string result = memberdef.attribute("prot").value();
    assert(!result.empty());

    return result;
}

TypeAnalyzer ExtractType(xml_node memberdef, const TemplateSpecialization& specialization)
{
    assert(IsMemberdef(memberdef));

    xml_node type = memberdef.child("type");
    assert(type);

    // Doxygen bug workaround https://github.com/doxygen/doxygen/issues/7732
    // For user-defined conversion operator exract return type from function name
    if (RemoveRefs(type).empty() && ExtractKind(memberdef) == "function")
    {
        string functionName = ExtractName(memberdef);
        if (StartsWith(functionName, "operator "))
            return TypeAnalyzer(CutStart(functionName, "operator "));
    }

    return TypeAnalyzer(type, specialization);
}

vector<ParamAnalyzer> ExtractParams(xml_node memberdef, const TemplateSpecialization& specialization)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");

    vector<ParamAnalyzer> result;

    for (xml_node param : memberdef.children("param"))
        result.push_back(ParamAnalyzer(param, specialization));

    return result;
}

string JoinParamsTypes(xml_node memberdef, const TemplateSpecialization& specialization)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");

    string result;

    vector<ParamAnalyzer> params = ExtractParams(memberdef, specialization);
    for (const ParamAnalyzer& param : params)
    {
        if (!result.empty())
            result += ", ";

        result += param.GetType().ToString();
    }

    return result;
}

string JoinParamsNames(xml_node memberdef, bool skipContext)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");

    string result;

    vector<ParamAnalyzer> params = ExtractParams(memberdef);
    for (size_t i = 0; i < params.size(); i++)
    {
        ParamAnalyzer param = params[i];

        if (skipContext && i == 0)
        {
            assert(param.GetType().ToString() == "Context*");
            continue;
        }

        if (!result.empty())
            result += ", ";

        result += param.GetDeclname();
    }

    return result;
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
    assert(IsMemberdef(node) || IsCompounddef(node) || IsMember(node) || IsSectiondef(node));

    string result = node.attribute("kind").value();
    assert(!result.empty());

    return result;
}

string ExtractName(xml_node node)
{
    assert(IsMemberdef(node) || IsEnumvalue(node));

    string result = node.child("name").child_value();
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
        result += RemoveRefs(para);
        result += " "; // To avoid gluing words from different paragraphs
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

bool IsTemplate(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    return node.child("templateparamlist");
}

vector<string> ExtractTemplateParams(xml_node node)
{
    assert(IsMemberdef(node) || IsCompounddef(node));

    vector<string> result;

    xml_node templateparamlist = node.child("templateparamlist");
    for (xml_node param : templateparamlist.children("param"))
    {
        string type = param.child_value("type");
        type = CutStart(type, "class ");
        type = CutStart(type, "typename ");

        result.push_back(type);
    }

    return result;
}

// ============================================================================

EnumAnalyzer::EnumAnalyzer(xml_node memberdef)
    : memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "enum");
}

string EnumAnalyzer::GetBaseType() const
{
    string result = memberdef_.child("type").child_value();

    if (result.empty())
        return "int";

    return result;
}

string EnumAnalyzer::GetLocation() const
{
    string baseType = GetBaseType();

    if (baseType == "int")
        return "enum " + GetTypeName() + " | File: " + GetHeaderFile();

    return "enum " + GetTypeName() + " : " + baseType + " | File: " + GetHeaderFile();
}

vector<string> EnumAnalyzer::GetEnumerators() const
{
    vector<string> result;

    for (xml_node enumvalue : memberdef_.children("enumvalue"))
        result.push_back(ExtractName(enumvalue));

    return result;
}

// ============================================================================

GlobalVariableAnalyzer::GlobalVariableAnalyzer(xml_node memberdef)
    : memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "variable");
}

string GlobalVariableAnalyzer::GetLocation() const
{
    string result = ExtractDefinition(memberdef_);

    result = RemoveFirst(result, "URHO3D_API ");

    assert(Contains(result, " Urho3D::"));
    result = ReplaceFirst(result, " Urho3D::", " ");

    if (IsStatic())
        result = "static " + result;

    result += " | File: " + GetHeaderFile();

    return result;
}

// ============================================================================

ClassAnalyzer::ClassAnalyzer(xml_node compounddef, const TemplateSpecialization& specialization)
    : compounddef_(compounddef)
    , specialization_(specialization)
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

        auto it = SourceData::members_.find(refid);
        if (it == SourceData::members_.end())
            continue;

        xml_node memberdef = it->second;
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

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.GetName() == name)
            return true;
    }

    return false;
}

shared_ptr<ClassFunctionAnalyzer> ClassAnalyzer::GetFunction(const string& name) const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.GetName() == name)
            return make_shared<ClassFunctionAnalyzer>(function);
    }

    return nullptr;
}

int ClassAnalyzer::NumFunctions(const string& name) const
{
    int result = 0;

    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.GetName() == name)
            result++;
    }

    return result;
}

bool ClassAnalyzer::IsAbstract() const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
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

    for (const ClassVariableAnalyzer& variable : variables)
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

    for (const ClassVariableAnalyzer& variable : variables)
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

shared_ptr<ClassAnalyzer> ClassAnalyzer::GetBaseClass() const
{
    xml_node basecompoundref = compounddef_.child("basecompoundref");

    if (!basecompoundref)
        return shared_ptr<ClassAnalyzer>();

    string refid = basecompoundref.attribute("refid").value();
    assert(!refid.empty());

    auto it = SourceData::classesByID_.find(refid);
    if (it == SourceData::classesByID_.end())
        return shared_ptr<ClassAnalyzer>();

    xml_node compounddef = it->second;
    return make_shared<ClassAnalyzer>(compounddef);
}

vector<ClassAnalyzer> ClassAnalyzer::GetBaseClasses() const
{
    vector<ClassAnalyzer> result;

    for (xml_node basecompoundref : compounddef_.children("basecompoundref"))
    {
        string refid = basecompoundref.attribute("refid").value();
        if (refid.empty()) // Type from ThirdParty lib
            continue;

        auto it = SourceData::classesByID_.find(refid);
        if (it == SourceData::classesByID_.end())
            continue;

        xml_node compounddef = it->second;
        result.push_back(ClassAnalyzer(compounddef));
    }

    return result;
}

static void RecursivelyGetBaseClasses(const ClassAnalyzer& analyzer, vector<ClassAnalyzer>& outResult)
{
    for (const ClassAnalyzer& baseClass : analyzer.GetBaseClasses())
    {
        outResult.push_back(baseClass);
        RecursivelyGetBaseClasses(baseClass, outResult);
    }
}

vector<ClassAnalyzer> ClassAnalyzer::GetAllBaseClasses() const
{
    vector<ClassAnalyzer> result;

    RecursivelyGetBaseClasses(*this, result);

    return result;
}

bool ClassAnalyzer::HasThisConstructor() const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.IsThisConstructor())
            return true;
    }

    return false;
}

bool ClassAnalyzer::IsRefCounted() const
{
    if (GetClassName() == "RefCounted")
        return true;

    vector<ClassAnalyzer> baseClasses = GetAllBaseClasses();

    for (const ClassAnalyzer& classAnalyzer : baseClasses)
    {
        if (classAnalyzer.GetClassName() == "RefCounted")
            return true;
    }

    return false;
}

shared_ptr<ClassFunctionAnalyzer> ClassAnalyzer::GetDefinedThisDefaultConstructor() const
{
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.IsThisDefaultConstructor())
            return make_shared<ClassFunctionAnalyzer>(function);
    }

    return nullptr;
}

vector<ClassFunctionAnalyzer> ClassAnalyzer::GetThisNonDefaultConstructors() const
{
    vector<ClassFunctionAnalyzer> result;
    vector<ClassFunctionAnalyzer> functions = GetFunctions();

    for (const ClassFunctionAnalyzer& function : functions)
    {
        if (function.IsThisNonDefaultConstructor())
            result.push_back(function);
    }

    return result;
}

// ============================================================================

FunctionAnalyzer::FunctionAnalyzer(xml_node memberdef, const TemplateSpecialization& specialization)
    : memberdef_(memberdef)
    , specialization_(specialization)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");
}

// ============================================================================

ClassFunctionAnalyzer::ClassFunctionAnalyzer(const ClassAnalyzer& classAnalyzer, xml_node memberdef, const TemplateSpecialization& specialization)
    : FunctionAnalyzer(memberdef, specialization)
    , classAnalyzer_(classAnalyzer)
{
    // Append template specialization from class
    specialization_.insert(classAnalyzer.GetSpecialization().begin(), classAnalyzer.GetSpecialization().end());
}

string ClassFunctionAnalyzer::GetVirt() const
{
    string result = memberdef_.attribute("virt").value();
    assert(!result.empty());

    return result;
}

string ClassFunctionAnalyzer::GetContainsClassName() const
{
    string argsstring = ExtractArgsstring(memberdef_);
    assert(!argsstring.empty());

    string prototype = ExtractDefinition(memberdef_) + argsstring;

    smatch match;
    regex_match(prototype, match, regex(".*Urho3D::(.+?)::.*"));
    assert(match.size());
    string result = match[1].str();

    return result;
}

string GetFunctionLocation(xml_node memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "function");

    string argsstring = ExtractArgsstring(memberdef);
    assert(!argsstring.empty());

    string prototype = ExtractDefinition(memberdef) + argsstring;

    smatch match;
    regex_match(prototype, match, regex("([^(]*)Urho3D::(.+?)"));
    assert(match.size());
    string result = match[1].str() + match[2].str();

    if (IsExplicit(memberdef))
        result = "explicit " + result;

    result += " | File: " + ExtractHeaderFile(memberdef);

    if (IsTemplate(memberdef))
    {
        string t = "";

        xml_node templateparamlist = memberdef.child("templateparamlist");
        for (xml_node param : templateparamlist.children("param"))
        {
            if (t.length() > 0)
                t += ", ";

            xml_node type = param.child("type");
            assert(type);
            t += type.child_value();

            xml_node declname = param.child("declname");
            if (!declname.empty())
                t += " " + string(declname.child_value());
        }

        result = "template<" + t + "> " + result;
    }
    
    result = RemoveFirst(result, "URHO3D_API ");

    result = ReplaceAll(result, " **", "** ");
    result = ReplaceAll(result, " &&", "&& ");
    result = ReplaceAll(result, " *&", "*& ");
    result = ReplaceAll(result, " *", "* ");
    result = ReplaceAll(result, " &", "& ");
    result = ReplaceAll(result, " )", ")");
    result = ReplaceAll(result, "< ", "<");
    
    while (Contains(result, " >"))
        result = ReplaceAll(result, " >", ">");

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

    if (GetParams().size() != 0 && GetParams().size() != 1)
        return false;

    return true;
}

bool ClassFunctionAnalyzer::CanBeSetProperty() const
{
    string returnType = GetReturnType().ToString();

    if (returnType != "void")
        return false;

    if (GetParams().size() != 1 && GetParams().size() != 2)
        return false;

    return true;
}

bool ClassFunctionAnalyzer::IsParentDestructor() const
{
    string functionName = GetName();
    if (!StartsWith(functionName, "~"))
        return false;
    
    return !IsThisDestructor();
}

bool ClassFunctionAnalyzer::IsParentConstructor() const
{
    if (IsThisConstructor())
        return false;

    string name = GetName();

    return ExtractDefinition(memberdef_) == "Urho3D::" + name + "::" + name;
}

shared_ptr<ClassFunctionAnalyzer> ClassFunctionAnalyzer::Reimplements() const
{
    xml_node reimplements = memberdef_.child("reimplements");

    if (!reimplements)
        return shared_ptr<ClassFunctionAnalyzer>();

    string refid = reimplements.attribute("refid").value();
    assert(!refid.empty());

    auto it = SourceData::members_.find(refid);
    if (it == SourceData::members_.end())
        return shared_ptr<ClassFunctionAnalyzer>();

    xml_node memberdef = it->second;
    return make_shared<ClassFunctionAnalyzer>(classAnalyzer_, memberdef);
}

// ============================================================================

ClassVariableAnalyzer::ClassVariableAnalyzer(ClassAnalyzer classAnalyzer, xml_node memberdef)
    : classAnalyzer_(classAnalyzer)
    , memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "variable");
}

string ClassVariableAnalyzer::GetLocation() const
{
    string definition = ExtractDefinition(memberdef_);
    assert(!definition.empty());
    
    // Remove Urho3D::
    smatch match;
    regex_match(definition, match, regex("(.*)Urho3D::(.+)"));
    assert(match.size() == 3);
    string result =  match[1].str() + match[2].str();

    result += " | File: " + GetHeaderFile();

    if (!classAnalyzer_.usingLocation_.empty())
        result = classAnalyzer_.usingLocation_ + " | " + result;

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

vector<GlobalVariableAnalyzer> NamespaceAnalyzer::GetVariables()
{
    xml_node sectiondef = FindSectiondef(compounddef_, "var");
    assert(sectiondef);

    vector<GlobalVariableAnalyzer> result;

    for (xml_node memberdef : sectiondef.children("memberdef"))
        result.push_back(GlobalVariableAnalyzer(memberdef));

    return result;
}

vector<GlobalFunctionAnalyzer> NamespaceAnalyzer::GetFunctions()
{
    xml_node sectiondef = FindSectiondef(compounddef_, "func");
    assert(sectiondef);

    vector<GlobalFunctionAnalyzer> result;

    for (xml_node memberdef : sectiondef.children("memberdef"))
        result.push_back(GlobalFunctionAnalyzer(memberdef));

    return result;
}

// ============================================================================

UsingAnalyzer::UsingAnalyzer(xml_node memberdef)
    : memberdef_(memberdef)
{
    assert(IsMemberdef(memberdef));
    assert(ExtractKind(memberdef) == "typedef");
}

// ============================================================================

GlobalFunctionAnalyzer::GlobalFunctionAnalyzer(xml_node memberdef, const TemplateSpecialization& specialization)
    : FunctionAnalyzer(memberdef, specialization)
{
}

// ============================================================================

ClassStaticFunctionAnalyzer::ClassStaticFunctionAnalyzer(const ClassAnalyzer& classAnalyzer, xml_node memberdef, const TemplateSpecialization& specialization)
    : FunctionAnalyzer(memberdef, specialization)
    , classAnalyzer_(classAnalyzer)
{
    assert(IsStatic(memberdef));
}
