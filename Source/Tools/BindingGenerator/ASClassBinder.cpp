// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "ASResult.h"
#include "ASUtils.h"
#include "Tuning.h"
#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace pugi;

namespace ASBindingGenerator
{

static void RegisterObjectType(const ClassAnalyzer& classAnalyzer, ProcessedClass& inoutProcessedClass)
{
    string className = classAnalyzer.GetClassName();
    bool isNoCount = classAnalyzer.IsNoCount();
    if (classAnalyzer.IsRefCounted() || isNoCount)
    {
        inoutProcessedClass.objectTypeRegistration_ = "engine->RegisterObjectType(\"" + className + "\", 0, asOBJ_REF" +
            (isNoCount ? " | asOBJ_NOCOUNT" : "") + ");";
    }
    else // Value type
    {
        string flags = "asOBJ_VALUE | asGetTypeTraits<" + className + ">()";

        if (classAnalyzer.IsPod())
        {
            flags += " | asOBJ_POD";

            if (classAnalyzer.AllFloats())
                flags += " | asOBJ_APP_CLASS_ALLFLOATS";
            else if (classAnalyzer.AllInts())
                flags += " | asOBJ_APP_CLASS_ALLINTS";
        }

        inoutProcessedClass.objectTypeRegistration_ = "engine->RegisterObjectType(\"" + className + "\", sizeof(" + className + "), " + flags + ");";
    }
}

static bool IsConstructorRequired(const ClassAnalyzer& classAnalyzer)
{
    if (classAnalyzer.IsRefCounted())
        return false;

    if (classAnalyzer.IsNoCount())
        return false;

    if (classAnalyzer.IsPod())
        return false;

    return true;
}

static bool IsDestructorRequired(const ClassAnalyzer& classAnalyzer)
{
    if (classAnalyzer.IsRefCounted())
        return false;

    if (classAnalyzer.IsNoCount())
        return false;

    if (classAnalyzer.IsPod())
        return false;

    return true;
}

// Iterate over overrided funcions
static bool HaveMark(const MethodAnalyzer& methodAnalyzer, const string& mark)
{
    if (Contains(methodAnalyzer.GetComment(), mark))
        return true;

    shared_ptr<MethodAnalyzer> reimplements = methodAnalyzer.Reimplements();

    if (!reimplements)
        return false;

    return HaveMark(*reimplements, mark);
}

static void RegisterConstructor(const MethodAnalyzer& methodAnalyzer, ProcessedClass& processedClass)
{
    ClassAnalyzer classAnalyzer = methodAnalyzer.GetClass();

    if (classAnalyzer.IsAbstract())
        return;

    if (methodAnalyzer.IsDeleted())
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because deleted";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    if (HaveMark(methodAnalyzer, "NO_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @nobind mark";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    if (HaveMark(methodAnalyzer, "MANUAL_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @manualbind mark";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    if (classAnalyzer.IsNoCount())
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetLocation();
        regError.message_ = "Factory not registered since the @nocount object created in a script through the factory will never be deleted";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    SpecialMethodRegistration result;
    //result.name_ = methodAnalyzer.GetName();
    result.comment_ = methodAnalyzer.GetDeclaration();
    
    string asClassName = classAnalyzer.GetClassName();
    string cppClassName = classAnalyzer.GetClassName();
    vector<ParamAnalyzer> params = methodAnalyzer.GetParams();

    if (params.empty()) // Default constructor
    {
        if (classAnalyzer.IsRefCounted())
            result.registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_FACTORY, \"" +
                                   asClassName + "@+ f()\", asFUNCTION(ASCompatibleFactory<" + cppClassName + ">), AS_CALL_CDECL);";
        else
            result.registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_CONSTRUCT, \"void f()\", asFUNCTION(ASCompatibleConstructor<" + cppClassName + ">), AS_CALL_CDECL_OBJFIRST);";

        result.comment_ = methodAnalyzer.GetLocation(); // Rewrite comment
        processedClass.defaultConstructor_ = make_shared<SpecialMethodRegistration>(result);
        return;
    }

    vector<ConvertedVariable> convertedParams;
    for (const ParamAnalyzer& param : params)
    {
        ConvertedVariable convertedParam;

        try
        {
            convertedParam = CppVariableToAS(param.GetType(), VariableUsage::FunctionParameter, param.GetDeclname(), param.GetDefval());
        }
        catch (const Exception& e)
        {
            MemberRegistrationError regError;
            regError.name_ = methodAnalyzer.GetName();
            regError.comment_ = methodAnalyzer.GetDeclaration();
            regError.message_ = e.what();
            processedClass.unregisteredSpecialMethods_.push_back(regError);
            return;
        }

        convertedParams.push_back(convertedParam);
    }

    bool needWrapper = false;
    for (const ConvertedVariable& convertedParam : convertedParams)
    {
        if (convertedParam.NeedWrapper())
            needWrapper = true;
    }

    if (classAnalyzer.IsRefCounted())
    {
        string asDeclaration = asClassName + "@+ f(" + JoinASDeclarations(convertedParams) + ")";
        result.registration_ = result.registration_ =
            "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_FACTORY, \"" + asDeclaration + "\", AS_FUNCTION("
            + GenerateWrapperName(methodAnalyzer) + ") , AS_CALL_CDECL);";

        result.glue_ = GenerateFactoryWrapper(methodAnalyzer, convertedParams);
    }
    else
    {
        string asDeclaration = "void f(" + JoinASDeclarations(convertedParams) + ")";
        result.registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_CONSTRUCT, \"" + asDeclaration +
            "\", AS_FUNCTION_OBJFIRST(" + GenerateWrapperName(methodAnalyzer) + "), AS_CALL_CDECL_OBJFIRST);";

        result.glue_ = GenerateConstructorWrapper(methodAnalyzer, convertedParams);
    }

    processedClass.nonDefaultConstructors_.push_back(result);
}

static void RegisterDestructor(const ClassAnalyzer& classAnalyzer, ProcessedClass& processedClass)
{
    if (classAnalyzer.IsRefCounted())
        return;

    if (classAnalyzer.IsNoCount())
        return;

    string className = classAnalyzer.GetClassName();
    string wrapperName = className + "_Destructor";

    shared_ptr<SpecialMethodRegistration> result = make_shared<SpecialMethodRegistration>();

    //result->name_ = "~" + className;

    result->registration_ = "engine->RegisterObjectBehaviour(\"" + className + "\", asBEHAVE_DESTRUCT, \"void f()\", AS_DESTRUCTOR(" + className + "), AS_CALL_CDECL_OBJFIRST);";

    shared_ptr<MethodAnalyzer> thisDestructor = classAnalyzer.GetDefinedThisDestructor();

    if (thisDestructor)
    {
        result->comment_ = thisDestructor->GetDeclaration();
        processedClass.destructor_ = result;
    }
    else if (!classAnalyzer.HasThisDestructor() && IsDestructorRequired(classAnalyzer))
    {
        result->comment_ = className + "::~" + className + "() | Implicitly-declared";
        processedClass.destructor_ = result;
    }
}

// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_script_class_ops.html
static string CppMethodNameToAS(const MethodAnalyzer& methodAnalyzer)
{
    string name = methodAnalyzer.GetName();

    if (name == "operator=")
        return "opAssign";

    if (name == "operator+")
        return "opAdd";

    if (name == "operator-")
    {
        if (!methodAnalyzer.GetParams().size()) // If no params
            return "opNeg";               // then unary minus
        else
            return "opSub";
    }

    if (name == "operator*")
        return "opMul";

    if (name == "operator/")
        return "opDiv";

    if (name == "operator%")
        return "opMod";

    if (name == "operator+=")
        return "opAddAssign";

    if (name == "operator-=")
        return "opSubAssign";

    if (name == "operator*=")
        return "opMulAssign";

    if (name == "operator/=")
        return "opDivAssign";

    if (name == "operator%=")
        return "opModAssign";

    if (name == "operator==")
        return "opEquals";

    if (name == "operator[]")
        return "opIndex";

    // Conversion to another type operator
    if (StartsWith(name, "operator "))
    {
        if (methodAnalyzer.IsExplicit())
            return "opConv";
        else
            return "opImplConv";
    }

    if (name == "operator!=")
        throw Exception("Only operator == is needed");

    if (name == "operator<")
        throw Exception("Registerd as opCmp separately");

    if (name == "operator>")
        throw Exception("Registerd as opCmp separately");

    if (name == "operator<=")
        throw Exception("Registerd as opCmp separately");

    if (name == "operator>=")
        throw Exception("Registerd as opCmp separately");

    if (methodAnalyzer.IsPrefixIncrementOperator())
        return "opPreInc";

    if (methodAnalyzer.IsPostfixIncrementOperator())
        return "opPostInc";

    if (methodAnalyzer.IsPrefixDecrementOperator())
        return "opPreDec";

    if (methodAnalyzer.IsPostfixDecrementOperator())
        return "opPostDec";

    return name;
}

// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_reg_objprop.html
static string CppMethodNameToASProperty(const MethodAnalyzer& methodAnalyzer)
{
    string name = methodAnalyzer.GetName();

    if (StartsWith(name, "Is") || StartsWith(name, "Get"))
    {
        string result = CutStart(name, "Is");
        result = CutStart(result, "Get");
        result = "get_" + FirstCharToLower(result);
        return result;
    }

    if (StartsWith(name, "Set"))
    {
        string result = CutStart(name, "Set");
        result = "set_" + FirstCharToLower(result);
        return result;
    }

    if (methodAnalyzer.CanBeGetProperty())
    {
        string result = name;
        result = "get_" + FirstCharToLower(result);
        return result;
    }

    if (methodAnalyzer.CanBeSetProperty())
    {
        string result = name;
        result = "set_" + FirstCharToLower(result);
        return result;
    }

    throw Exception("Can not be property");
}

// Can return BIND_AS_ALIAS_xxxx or BIND_AS_PROPERTY
// Return "" if no this marks
static string GetPropertyMark(const MethodAnalyzer& methodAnalyzer)
{
    string comment = methodAnalyzer.GetComment();

    smatch match;
    regex_match(comment, match, regex(".*\\b(BIND_AS_ALIAS_.+?)\\b.*"));
    if (match.size() == 2)
        return match[1].str();

    regex_match(comment, match, regex(".*\\bBIND_AS_PROPERTY\\b.*"));
    if (match.size() == 1)
        return "BIND_AS_PROPERTY";

    shared_ptr<MethodAnalyzer> reimplements = methodAnalyzer.Reimplements();

    if (!reimplements)
        return "";

    return GetPropertyMark(*reimplements);
}

static string GetSignature(const MethodAnalyzer& method)
{
    xml_node memberdef = method.GetMemberdef();

    string result = string(memberdef.child_value("name")) + '|';
    result += RemoveRefs(memberdef.child("type")) + '|';

    for (xml_node param : memberdef.children("param"))
        result += RemoveRefs(param.child("type")) + '|';

    if (method.IsStatic())
        result += "static" + result;

    return result;
}

struct ClassMemberSignatures
{
    unordered_set<string> methods_; // Signatures of all nonstatic public methods (including inherited)
    unordered_map<string, vector<string>> hiddenInAnyDerivedClassesMethods_; // method signature -> derived class names
    unordered_map<string, vector<string>> existsInBaseClassesMethods_; // method signature -> base class names
};

static unordered_map<string, shared_ptr<ClassMemberSignatures>> _cachedMemberSignatures; // className -> signatures

static bool ContainsSameSignature(const string& className, const string& methodSignature)
{
    shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[className];
    return classData->methods_.find(methodSignature) != classData->methods_.end();
}

static void InitCachedMemberSignatures()
{ 
    // Fill signatures
    for (pair<const string, xml_node>& element : SourceData::classesByID_)
    {
        xml_node compounddef = element.second;
        ClassAnalyzer classAnalyzer(compounddef);
        shared_ptr<ClassMemberSignatures> classData = make_shared<ClassMemberSignatures>();
        vector<MethodAnalyzer> methods = classAnalyzer.GetAllPublicMethods();
        for (const MethodAnalyzer& method : methods)
            classData->methods_.insert(GetSignature(method));
        _cachedMemberSignatures[classAnalyzer.GetClassName()] = classData;
    }

    // Fill hidden in any derived classes members
    for (pair<const string, xml_node>& element : SourceData::classesByID_)
    {
        xml_node compounddef = element.second;
        ClassAnalyzer classAnalyzer(compounddef);
        string className = classAnalyzer.GetClassName();
        shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[classAnalyzer.GetClassName()];
        vector<MethodAnalyzer> methods = classAnalyzer.GetAllPublicMethods();
        vector<ClassAnalyzer> allDerivedClasses = classAnalyzer.GetAllDerivedClasses();
        vector<ClassAnalyzer> baseClasses = classAnalyzer.GetBaseClasses();
        for (const MethodAnalyzer& method : methods)
        {
            string methodSignature = GetSignature(method);

            vector<string> hiddenInderivedClasses;
            
            for (const ClassAnalyzer& derivedClass : allDerivedClasses)
            {
                string derivedClassName = derivedClass.GetClassName();
                if (!ContainsSameSignature(derivedClassName, methodSignature))
                    hiddenInderivedClasses.push_back(derivedClassName);
            }

            if (hiddenInderivedClasses.size())
                classData->hiddenInAnyDerivedClassesMethods_[methodSignature] = hiddenInderivedClasses;

            vector<string> existInBaseClasses;

            for (const ClassAnalyzer& baseClass : baseClasses)
            {
                string baseClassName = baseClass.GetClassName();
                if (ContainsSameSignature(baseClassName, methodSignature))
                    existInBaseClasses.push_back(baseClassName);
            }

            if (existInBaseClasses.size())
                classData->existsInBaseClassesMethods_[methodSignature] = existInBaseClasses;
        }
    }


}

/*static bool ContainsSameSignature(const ClassAnalyzer& classAnalyzer, const MethodAnalyzer& method)
{
    vector<MethodAnalyzer> methods = classAnalyzer.GetAllPublicMethods();
    
    for (const MethodAnalyzer& m : methods)
    {
        if (GetSignature(m) == GetSignature(method))
            return true;
    }

    return false;
}*/



static vector<string> HiddenInAnyDerivedClasses(const MethodAnalyzer& method)
{
    /*vector<string> result;

    vector<ClassAnalyzer> derivedClasses = method.GetClass().GetAllDerivedClasses();
    for (const ClassAnalyzer& derivedClass : derivedClasses)
    {
        //if (!ContainsSameSignature(derivedClass, method))
        //    result.push_back(derivedClass.GetClassName());

        if (!ContainsSameSignature(derivedClass.GetClassName(), GetSignature(method)))
            result.push_back(derivedClass.GetClassName());
    }

    return result;*/
    string classname = method.GetClassName();
    string methodSignature = GetSignature(method);
    shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[classname];

    auto it = classData->hiddenInAnyDerivedClassesMethods_.find(methodSignature);
    if (it == classData->hiddenInAnyDerivedClassesMethods_.end())
        return vector<string>();
    else
        return it->second;
}

static vector<string> HiddenInAnyDerivedClasses(const MethodAnalyzer& method, const ClassAnalyzer& classAnalyzer)
{
    /*vector<string> result;

    vector<ClassAnalyzer> derivedClasses = classAnalyzer.GetAllDerivedClasses();
    for (const ClassAnalyzer& derivedClass : derivedClasses)
    {
        //if (!ContainsSameSignature(derivedClass, method))
        //    result.push_back(derivedClass.GetClassName());
        if (!ContainsSameSignature(derivedClass.GetClassName(), GetSignature(method)))
            result.push_back(derivedClass.GetClassName());
    }

    return result;*/

    string classname = classAnalyzer.GetClassName();
    string methodSignature = GetSignature(method);
    shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[classname];

    auto it = classData->hiddenInAnyDerivedClassesMethods_.find(methodSignature);
    if (it == classData->hiddenInAnyDerivedClassesMethods_.end())
        return vector<string>();
    else
        return it->second;
}

static vector<string> ExistsInBaseClasses(const MethodAnalyzer& method)
{
    /*vector<string> result;

    vector<ClassAnalyzer> baseClasses = method.GetClass().GetBaseClasses();
    string methodSignature = GetSignature(method);
    for (const ClassAnalyzer& baseClass : baseClasses)
    {
        //if (ContainsSameSignature(baseClass, method))
        //    result.push_back(baseClass.GetClassName());
        if (ContainsSameSignature(baseClass.GetClassName(), methodSignature))
            result.push_back(baseClass.GetClassName());
    }

    return result;*/

    string classname = method.GetClassName();
    string methodSignature = GetSignature(method);
    shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[classname];
    
    auto it = classData->existsInBaseClassesMethods_.find(methodSignature);
    if (it == classData->existsInBaseClassesMethods_.end())
        return vector<string>();
    else
        return it->second;
}

static vector<string> ExistsInBaseClasses(const MethodAnalyzer& method, const ClassAnalyzer& classAnalyzer)
{
    /*vector<string> result;

    vector<ClassAnalyzer> baseClasses = classAnalyzer.GetBaseClasses();
    string methodSignature = GetSignature(method);
    for (const ClassAnalyzer& baseClass : baseClasses)
    {
        //if (ContainsSameSignature(baseClass, method))
        //    result.push_back(baseClass.GetClassName());
        if (ContainsSameSignature(baseClass.GetClassName(), methodSignature))
            result.push_back(baseClass.GetClassName());
    }

    return result;*/

    string className = classAnalyzer.GetClassName();
    string methodSignature = GetSignature(method);
    shared_ptr<ClassMemberSignatures> classData = _cachedMemberSignatures[className];

    auto it = classData->existsInBaseClassesMethods_.find(methodSignature);
    if (it == classData->existsInBaseClassesMethods_.end())
        return vector<string>();
    else
        return it->second;
}

// Returns names of derived class that has base classes with the same method signature
// (multiple inheriance methods with same signature - we can not register this in template because this cause multiple registration same signature)
static string FindConflicts(const MethodAnalyzer& method)
{
    vector<ClassAnalyzer> derivedClasses = method.GetClass().GetAllDerivedClasses();
    for (const ClassAnalyzer& derivedClass : derivedClasses)
    {
        vector<string> existsInBaseClasses = ExistsInBaseClasses(method, derivedClass);

        if (existsInBaseClasses.size() > 1)
            return derivedClass.GetClassName(); // Conflict found
    }

    return string(); // No conflicts
}

static string FindConflicts(const MethodAnalyzer& method, const ClassAnalyzer& classAnalyzer)
{
    vector<ClassAnalyzer> derivedClasses = classAnalyzer.GetAllDerivedClasses();
    for (const ClassAnalyzer& derivedClass : derivedClasses)
    {
        vector<string> existsInBaseClasses = ExistsInBaseClasses(method, derivedClass);

        if (existsInBaseClasses.size() > 1)
            return derivedClass.GetClassName(); // Conflict found
    }

    return string(); // No conflicts
}


static void RegisterMethod(const MethodAnalyzer& methodAnalyzer, ProcessedClass& processedClass)
{
    if (methodAnalyzer.IsDefine())
        return;

    // TEST

    //if (/*methodAnalyzer.GetClassName() == "OcclusionBuffer" && */methodAnalyzer.GetName() == "AddRef")
    //    string className = methodAnalyzer.GetClassName(); // Breakpoint here

    // TEST END

    // TODO: This functions take 99% of generation time. Need some cache?
    // ===============================================

    vector<string> existsInBaseClasses = ExistsInBaseClasses(methodAnalyzer);


    if (existsInBaseClasses.size() == 1)
    {
        shared_ptr<ClassAnalyzer> baseClass = FindClassByName(existsInBaseClasses[0]);
        if (HiddenInAnyDerivedClasses(methodAnalyzer, *baseClass).empty() && FindConflicts(methodAnalyzer, *baseClass).empty())
            return; // Already registered in template of base class
    }

    bool regInTemplate = true;

    vector<string> hiddenInDerivedClasses = HiddenInAnyDerivedClasses(methodAnalyzer);

    if (!hiddenInDerivedClasses.empty())
    {
        if (methodAnalyzer.IsThisMethod())
        {
            MemberRegistrationError msg;
            msg.name_ = methodAnalyzer.GetName();
            msg.comment_ = methodAnalyzer.GetDeclaration();
            msg.message_ = "Can not be registered here bacause hidden in derived classes: " + Join(hiddenInDerivedClasses, ", ");
            processedClass.unregisteredTemplateMethods_.push_back(msg);
        }

        regInTemplate = false; // Impossible register in template
    }

    if (regInTemplate) // Additional check
    {

        string conflict = FindConflicts(methodAnalyzer);

        if (!conflict.empty())
            regInTemplate = false; // Impossible register in tempalte
    }

    // ====================================================
    // END

    if (methodAnalyzer.IsTemplate())
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because template";

        if (regInTemplate)
            processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalStaticMethods_.push_back(regError);
        return;
    }

    if (methodAnalyzer.IsDeleted())
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because deleted";
        if (regInTemplate)
            processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalStaticMethods_.push_back(regError);

        return;
    }

    if (methodAnalyzer.IsStatic())
    {
        if (HaveMark(methodAnalyzer, "NO_BIND"))
        {
            MemberRegistrationError regError;
            regError.name_ = methodAnalyzer.GetName();
            regError.comment_ = methodAnalyzer.GetDeclaration();
            regError.message_ = "Not registered because have @nobind mark";
            if (regInTemplate)
                processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
            else
                processedClass.unregisteredPersonalStaticMethods_.push_back(regError);

            return;
        }

        if (HaveMark(methodAnalyzer, "MANUAL_BIND"))
        {
            MemberRegistrationError regError;
            regError.name_ = methodAnalyzer.GetName();
            regError.comment_ = methodAnalyzer.GetDeclaration();
            regError.message_ = "Not registered because have @manualbind mark";
            if (regInTemplate)
                processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
            else
                processedClass.unregisteredPersonalStaticMethods_.push_back(regError);

            return;
        }

        ClassStaticFunctionAnalyzer staticMethodAnalyzer(methodAnalyzer.GetClass(), methodAnalyzer.GetMemberdef());

        vector<ParamAnalyzer> params = staticMethodAnalyzer.GetParams();
        vector<ConvertedVariable> convertedParams;
        string outGlue;
        bool needWrapper = false;

        for (const ParamAnalyzer& param : params)
        {
            ConvertedVariable conv;
            try
            {
                conv = CppVariableToAS(param.GetType(), VariableUsage::FunctionParameter, param.GetDeclname(), param.GetDefval());
            }
            catch (const Exception& e)
            {
                MemberRegistrationError regError;
                regError.name_ = staticMethodAnalyzer.GetName();
                regError.comment_ = methodAnalyzer.GetDeclaration();
                regError.message_ = e.what();
                if (regInTemplate)
                    processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
                else
                    processedClass.unregisteredPersonalStaticMethods_.push_back(regError);

                return;
            }

            if (conv.NeedWrapper())
                needWrapper = true;

            convertedParams.push_back(conv);
        }

        ConvertedVariable convertedReturn;

        try
        {
            convertedReturn = CppVariableToAS(staticMethodAnalyzer.GetReturnType(), VariableUsage::FunctionReturn);
        }
        catch (const Exception& e)
        {
            MemberRegistrationError regError;
            regError.name_ = staticMethodAnalyzer.GetName();
            regError.comment_ = methodAnalyzer.GetDeclaration();
            regError.message_ = e.what();
            if (regInTemplate)
                processedClass.unregisteredTemplateStaticMethods_.push_back(regError);
            else
                processedClass.unregisteredPersonalStaticMethods_.push_back(regError);

            return;
        }

        if (convertedReturn.NeedWrapper())
            needWrapper = true;


        Registration result;
        result.comment_ = methodAnalyzer.GetDeclaration();

        string funcPointer;
        string callConv = "AS_CALL_CDECL";

        string asFunctionName = staticMethodAnalyzer.GetName();
        string cppClassName = methodAnalyzer.GetClass().GetClassName();
        string className = staticMethodAnalyzer.GetClassName();

        if (needWrapper)
        {
            /*result.glue_ = GenerateWrapper(methodAnalyzer, false, convertedParams, retConv);
            result.registration_.funcPointer_ = "AS_FUNCTION_OBJFIRST(" + GenerateWrapperName(methodAnalyzer) + ")";
            result.registration_.callConv_ = "AS_CALL_CDECL_OBJFIRST";*/

            result.glue_ = GenerateWrapper(staticMethodAnalyzer, regInTemplate, convertedParams, convertedReturn);
            funcPointer = "AS_FUNCTION(" + GenerateWrapperName(staticMethodAnalyzer);
            if (regInTemplate)
                funcPointer += "<" + cppClassName + ">";
            funcPointer += ")";
        }
        else
        {
            /*result.registration_.funcPointer_ = Generate_asMETHODPR(methodAnalyzer, regInTemplate);
            result.registration_.callConv_ = "AS_CALL_THISCALL";*/

            funcPointer = Generate_asFUNCTIONPR(staticMethodAnalyzer, regInTemplate);
        }

        string asClassName = cppClassName;

        string decl = convertedReturn.asDeclaration_ + " " + asFunctionName + "(" + JoinASDeclarations(convertedParams) + ")";

        if (regInTemplate)
        {
            result.registration_.push_back(
                "engine->SetDefaultNamespace(className);"
                "engine->RegisterGlobalFunction(\"" + decl + "\", " + funcPointer + ", " + callConv + ");"
                "engine->SetDefaultNamespace(\"\");"
            );
        }
        else
        {
            result.registration_.push_back(
                "engine->SetDefaultNamespace(\"" + asClassName + "\");"
                "engine->RegisterGlobalFunction(\"" + decl + "\", " + funcPointer + ", " + callConv + ");"
                "engine->SetDefaultNamespace(\"\");"
            );
        }
/*

        StaticMethodRegistration result;
        result.cppDeclaration_ = methodAnalyzer.GetDeclaration();
        result.name_ = staticMethodAnalyzer.GetName();
        result.registration_.asDeclarations_.push_back(decl);
        result.registration_.callConv_ = "AS_CALL_CDECL";
        
        if (needWrapper)
            result.registration_.funcPointer_ = "AS_FUNCTION(" + GenerateWrapperName(staticMethodAnalyzer) + ")";
        else
            result.registration_.funcPointer_ = Generate_asFUNCTIONPR(staticMethodAnalyzer);

        if (needWrapper)
            result.glue_ = GenerateWrapper(staticMethodAnalyzer, convertedParams, convertedReturn);

        processedClass.staticMethods_.push_back(result);

        */


        if (regInTemplate)
            processedClass.templateStaticMethods_.push_back(result);
        else
            processedClass.personalStaticMethods_.push_back(result);

        return;
    }

    if (HaveMark(methodAnalyzer, "NO_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @nobind mark";
        if (regInTemplate)
            processedClass.unregisteredTemplateMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalMethods_.push_back(regError);
        return;
    }

    if (HaveMark(methodAnalyzer, "MANUAL_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @manualbind mark";
        if (regInTemplate)
            processedClass.unregisteredTemplateMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalMethods_.push_back(regError);
        return;
    }

    vector<ParamAnalyzer> params = methodAnalyzer.GetParams();
    vector<ConvertedVariable> convertedParams;
    bool needWrapper = false;

    for (const ParamAnalyzer& param : params)
    {
        ConvertedVariable conv;

        try
        {
            VariableUsage varUsage = VariableUsage::FunctionParameter;
            if (methodAnalyzer.IsPostfixIncrementOperator() || methodAnalyzer.IsPostfixDecrementOperator())
                varUsage = VariableUsage::PostfixIncDecParameter;

            conv = CppVariableToAS(param.GetType(), varUsage, param.GetDeclname(), param.GetDefval());
        }
        catch (const Exception& e)
        {
            MemberRegistrationError regError;
            regError.name_ = methodAnalyzer.GetName();
            regError.comment_ = methodAnalyzer.GetDeclaration();
            regError.message_ = e.what();
            if (regInTemplate)
                processedClass.unregisteredTemplateMethods_.push_back(regError);
            else
                processedClass.unregisteredPersonalMethods_.push_back(regError);

            return;
        }

        convertedParams.push_back(conv);

        if (conv.NeedWrapper())
            needWrapper = true;
    }

    ConvertedVariable retConv;

    try
    {
        retConv = CppVariableToAS(methodAnalyzer.GetReturnType(), VariableUsage::FunctionReturn);
    }
    catch (const Exception& e)
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = e.what();
        if (regInTemplate)
            processedClass.unregisteredTemplateMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalMethods_.push_back(regError);

        return;
    }

    if (retConv.NeedWrapper())
        needWrapper = true;

    string asReturnType = retConv.asDeclaration_;

    string asFunctionName = methodAnalyzer.GetName();
    if (methodAnalyzer.IsConsversionOperator())
        asReturnType = CutStart(asFunctionName, "operator ");
    
    try
    {
        asFunctionName = CppMethodNameToAS(methodAnalyzer);
    }
    catch (const Exception& e)
    {
        MemberRegistrationError regError;
        regError.name_ = methodAnalyzer.GetName();
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = e.what();
        if (regInTemplate)
            processedClass.unregisteredTemplateMethods_.push_back(regError);
        else
            processedClass.unregisteredPersonalMethods_.push_back(regError);

        return;
    }

    string cppClassName = methodAnalyzer.GetClass().GetClassName();

    /*MethodRegistration result;
    result.name_ = methodAnalyzer.GetName();
    result.cppDeclaration_ = ReplaceAll(methodAnalyzer.GetDeclaration(), "\"", "\\\"");*/

    Registration result;
    result.comment_ = methodAnalyzer.GetDeclaration();

    string funcPointer;
    string callConv;

    //bool templateVersion = true;

    if (needWrapper)
    {
        /*result.glue_ = GenerateWrapper(methodAnalyzer, false, convertedParams, retConv);
        result.registration_.funcPointer_ = "AS_FUNCTION_OBJFIRST(" + GenerateWrapperName(methodAnalyzer) + ")";
        result.registration_.callConv_ = "AS_CALL_CDECL_OBJFIRST";*/

        result.glue_ = GenerateWrapper(methodAnalyzer, regInTemplate, convertedParams, retConv);
        funcPointer = "AS_FUNCTION_OBJFIRST(" + GenerateWrapperName(methodAnalyzer, regInTemplate);
        if (regInTemplate)
            funcPointer += "<" + cppClassName + ">";
        funcPointer += ")";

        callConv = "AS_CALL_CDECL_OBJFIRST";
    }
    else
    {
        /*result.registration_.funcPointer_ = Generate_asMETHODPR(methodAnalyzer, regInTemplate);
        result.registration_.callConv_ = "AS_CALL_THISCALL";*/

        funcPointer = Generate_asMETHODPR(methodAnalyzer, regInTemplate);
        callConv = "AS_CALL_THISCALL";
    }

    string decl = asReturnType + " " + asFunctionName + "(" + JoinASDeclarations(convertedParams) + ")";

    if (methodAnalyzer.IsConst())
        decl += " const";

    string asClassName = cppClassName;

    //result.registration_.asDeclarations_.push_back(decl);

  if (regInTemplate)
      result.registration_.push_back("engine->RegisterObjectMethod(className, \"" + decl + "\", " + funcPointer + ", " + callConv + ");");
  else
      result.registration_.push_back("engine->RegisterObjectMethod(\"" + asClassName + "\", \"" + decl + "\", " + funcPointer + ", " + callConv + ");");

    // Also register as property if needed
    string propertyMark = GetPropertyMark(methodAnalyzer);
    if (!propertyMark.empty())
    {
        if (StartsWith(propertyMark, "BIND_AS_ALIAS_"))
        {
            asFunctionName = CutStart(propertyMark, "BIND_AS_ALIAS_");
        }
        else
        {
            try
            {
                asFunctionName = CppMethodNameToASProperty(methodAnalyzer);
            }
            catch (const Exception& e)
            {
                MemberRegistrationError regError;
                regError.name_ = methodAnalyzer.GetName();
                regError.comment_ = methodAnalyzer.GetDeclaration();
                regError.message_ = e.what();
                if (regInTemplate)
                    processedClass.unregisteredTemplateMethods_.push_back(regError);
                else
                    processedClass.unregisteredPersonalMethods_.push_back(regError);

                return;
            }
        }

        decl = asReturnType + " " + asFunctionName + "(" + JoinASDeclarations(convertedParams) + ")";

        if (methodAnalyzer.IsConst())
            decl += " const";

        //result.registration_.asDeclarations_.push_back(decl);

        if (regInTemplate)
            result.registration_.push_back("engine->RegisterObjectMethod(className, \"" + decl + "\", " + funcPointer + ", " + callConv + ");");
        else
            result.registration_.push_back("engine->RegisterObjectMethod(\"" + asClassName + "\", \"" + decl + "\", " + funcPointer + ", " + callConv + ");");

        //result.registration_.push_back("engine->RegisterObjectMethod(className, \"" + decl + "\", " + funcPointer + ", " + callConv + ");");
    }

    //processedClass.methods_.push_back(result);

    if (regInTemplate)
        processedClass.templateMethods_.push_back(result);
    else
        processedClass.personalMethods_.push_back(result);
}

static void RegisterField(const FieldAnalyzer& fieldAnalyzer, ProcessedClass& processedClass)
{
    if (Contains(fieldAnalyzer.GetComment(), "NO_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = fieldAnalyzer.GetName();
        regError.comment_ = fieldAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @nobind mark";
        processedClass.unregisteredTemplateFields_.push_back(regError);
        return;
    }

    if (Contains(fieldAnalyzer.GetComment(), "MANUAL_BIND"))
    {
        MemberRegistrationError regError;
        regError.name_ = fieldAnalyzer.GetName();
        regError.comment_ = fieldAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @manualbind mark";
        processedClass.unregisteredTemplateFields_.push_back(regError);
        return;
    }

    if (fieldAnalyzer.IsStatic())
    {
        string asType;

        try
        {
            asType = CppTypeToAS(fieldAnalyzer.GetType(), TypeUsage::StaticField);
        }
        catch (const Exception& e)
        {
            MemberRegistrationError regError;
            regError.name_ = fieldAnalyzer.GetName();
            regError.comment_ = fieldAnalyzer.GetDeclaration();
            regError.message_ = e.what();
            processedClass.unregisteredTemplateStaticFields_.push_back(regError);
            return;
        }

        if (fieldAnalyzer.GetType().IsConst() || fieldAnalyzer.GetType().IsConstexpr())
            asType = "const " + asType;

        asType = ReplaceAll(asType, "struct ", "");

        string cppClassName = fieldAnalyzer.GetClassName();
        string asPropertyName = fieldAnalyzer.GetName();

        /*StaticFieldRegistration result;
        result.cppDeclaration_ = fieldAnalyzer.GetDeclaration();
        result.name_ = fieldAnalyzer.GetName();
        result.registration_.asDeclarations_.push_back(asType + " " + asPropertyName);
        result.registration_.pointer_ = "(void*)&" + cppClassName + "::" + fieldAnalyzer.GetName();

        processedClass.staticFields_.push_back(result);
        */

        Registration reg;
        reg.comment_ = fieldAnalyzer.GetDeclaration();
        reg.registration_.push_back(
            "engine->SetDefaultNamespace(className);"
            "engine->RegisterGlobalProperty(\"" + asType + " " + asPropertyName + "\", " + "(void*)&T::" + fieldAnalyzer.GetName() + ");"
            "engine->SetDefaultNamespace(\"\");");

        processedClass.templateStaticFields_.push_back(reg);
    }
    else
    {
        if (fieldAnalyzer.IsArray())
        {
            MemberRegistrationError regError;
            regError.name_ = fieldAnalyzer.GetName();
            regError.comment_ = fieldAnalyzer.GetDeclaration();
            regError.message_ = "Not registered because array";
            processedClass.unregisteredTemplateFields_.push_back(regError);
            return;
        }

        if (fieldAnalyzer.GetType().IsPointer())
        {
            MemberRegistrationError regError;
            regError.name_ = fieldAnalyzer.GetName();
            regError.comment_ = fieldAnalyzer.GetDeclaration();
            regError.message_ = "Not registered because pointer";
            processedClass.unregisteredTemplateFields_.push_back(regError);
            return;
        }

        string asPropertyType;

        try
        {
            asPropertyType = CppTypeToAS(fieldAnalyzer.GetType(), TypeUsage::Field);
        }
        catch (const Exception& e)
        {
            MemberRegistrationError regError;
            regError.name_ = HideUnnamedType(fieldAnalyzer.GetName());
            regError.comment_ = HideUnnamedType(fieldAnalyzer.GetDeclaration());
            regError.message_ = e.what();
            processedClass.unregisteredTemplateFields_.push_back(regError);
            return;
        }

        string cppFieldName = fieldAnalyzer.GetName();
        assert(!cppFieldName.empty());
        string asPropertyName = CutEnd(cppFieldName, "_");

        string cppClassName = fieldAnalyzer.GetClassName();

        /*FieldRegistration result;
        result.name_ = cppFieldName;
        result.cppDeclaration_ = fieldAnalyzer.GetDeclaration();
        result.registration_.asDeclarations_.push_back(asPropertyType + " " + asPropertyName);
        result.registration_.byteOffset_ = "offsetof(" + cppClassName + ", " + cppFieldName + ")";*/

        Registration reg;
        reg.comment_ = fieldAnalyzer.GetDeclaration();
        reg.registration_.push_back("engine->RegisterObjectProperty(className, \"" + asPropertyType + " " + asPropertyName + "\", "
            "offsetof(T, " + cppFieldName + "));");

        processedClass.templateFields_.push_back(reg);

        //processedClass.fields_.push_back(result);
    }
}

static void RegisterComparisonOperator(const ClassAnalyzer& classAnalyzer, ProcessedClass& processedClass)
{
    string className = classAnalyzer.GetClassName();
    shared_ptr<MethodAnalyzer> methodAnalyzer = classAnalyzer.GetMethod("operator<");
    assert(methodAnalyzer);
    string wrapperName = GenerateWrapperName(*methodAnalyzer);

    Registration result;
    result.comment_ = methodAnalyzer->GetDeclaration();
    
    result.glue_ =
        "template <class T> int " + wrapperName + "(const T& lhs, const T& rhs)\n"
        "{\n"
        "    if (lhs < rhs)\n"
        "        return -1;\n\n"
        "    if (lhs > rhs)\n"
        "        return 1;\n\n"
        "    return 0;\n"
        "}\n";

    //result.name_ = methodAnalyzer->GetName();
    result.registration_.push_back(
        "engine->RegisterObjectMethod(className, \"int opCmp(const " + className + "& in) const\", "
        "AS_FUNCTION_OBJFIRST(" + wrapperName + "<T>), AS_CALL_CDECL_OBJFIRST);");

    processedClass.templateMethods_.push_back(result);
}

static void TryRegisterImplicitlyDeclaredAssignOperator(const ClassAnalyzer& classAnalyzer, ProcessedClass& processedClass)
{
    string className = classAnalyzer.GetClassName();

    processedClass.additionalLines_.push_back("    // " + className + "& " + className + "::operator =(const " + className + "&) | Possible implicitly-declared");
    processedClass.additionalLines_.push_back("    RegisterImplicitlyDeclaredAssignOperatorIfPossible<" + className + ">(engine, \"" + className + "\");");
}

static void ProcessClass(const ClassAnalyzer& classAnalyzer)
{
    if (classAnalyzer.IsInternal())
        return;

    // TODO: Remove
    if (classAnalyzer.IsTemplate())
        return;

    string header = classAnalyzer.GetHeaderFile();
    Result::AddHeader(header);

    if (IsIgnoredHeader(header))
        return;

    ProcessedClass processedClass;
    processedClass.name_ = classAnalyzer.GetClassName();
    processedClass.dirName_ = classAnalyzer.GetDirName();
    processedClass.comment_ = classAnalyzer.GetLocation();
    processedClass.insideDefine_ = InsideDefine(header);
    processedClass.inherianceDeep_ = classAnalyzer.GetInherianceDeep();

    //cout << processedClass.name_ << " DEEP: " << processedClass.inherianceDeep_;
    cout << processedClass.name_ << "\n";

    vector<MethodAnalyzer> methods = classAnalyzer.GetAllPublicMethods();
    for (const MethodAnalyzer& method : methods)
    {
        if (method.IsStatic())
            continue; // TODO remove hack

        if (method.IsThisConstructor())
            RegisterConstructor(method, processedClass);
        else if (method.IsDestructor())
            continue;
        else if (method.IsConstructor())
            continue;
        else
            RegisterMethod(method, processedClass);
    }

    // TODO отдельный класс для статических методов?
    vector<MethodAnalyzer> staticMethods = classAnalyzer.GetThisPublicStaticMethods();
    for (const MethodAnalyzer& staticMethod : staticMethods)
    {
        RegisterMethod(staticMethod, processedClass);
    }

    vector<FieldAnalyzer> fields = classAnalyzer.GetThisPublicFields();
    for (const FieldAnalyzer& field : fields)
        RegisterField(field, processedClass);

    vector<FieldAnalyzer> staticFields = classAnalyzer.GetThisPublicStaticFields();
    for (const FieldAnalyzer& staticField : staticFields)
        RegisterField(staticField, processedClass);

    vector<ClassAnalyzer> baseClasses = classAnalyzer.GetBaseClasses();
    for (const ClassAnalyzer& baseClass : baseClasses)
        processedClass.baseClassNames_.push_back(baseClass.GetClassName());

    //processedClass.hiddenMethods_ = classAnalyzer.GetHiddenMethods();
    /*processedClass.hiddenStaticMethods_ = classAnalyzer.GetHiddenStaticMethods();
    processedClass.hiddenFields_ = classAnalyzer.GetHiddenFields();
    processedClass.hiddenStaticFields_ = classAnalyzer.GetHiddenStaticFields();*/

    bool isNoCount = classAnalyzer.IsNoCount();

    if (classAnalyzer.IsAbstract() && !(classAnalyzer.IsRefCounted() || isNoCount))
    {
        processedClass.objectTypeRegistration_ = "// Not registered because value types can not be abstract";
        processedClass.noBind_ = true;
        Result::classes_.push_back(processedClass);
        return;
    }

    string classComment = classAnalyzer.GetComment();

    if (Contains(classComment, "NO_BIND"))
    {
        processedClass.objectTypeRegistration_ = "// Not registered because have @nobind mark";
        processedClass.noBind_ = true;
        Result::classes_.push_back(processedClass);
        return;
    }

    if (Contains(classComment, "MANUAL_BIND"))
    {
        processedClass.objectTypeRegistration_ = "// Not registered because have @manualbind mark";
        processedClass.noBind_ = true;
        Result::classes_.push_back(processedClass);
        return;
    }

    RegisterObjectType(classAnalyzer, processedClass);

    if (classAnalyzer.IsRefCounted() || isNoCount)
    {
        vector<ClassAnalyzer> baseClasses = classAnalyzer.GetAllBaseClasses();
        for (ClassAnalyzer baseClass : baseClasses)
        {
            if (baseClass.IsRefCounted() || baseClass.IsNoCount())
            {
                string cppBaseClassName = baseClass.GetClassName();
                string asBaseClassName = cppBaseClassName;

                string cppClassName = classAnalyzer.GetClassName();
                string asClassName = classAnalyzer.GetClassName();

                string reg = "RegisterSubclass<" + cppBaseClassName + ", " + cppClassName + ">(engine, \"" + asBaseClassName + "\", \"" + asClassName + "\");";
                processedClass.subclassRegistrations_.push_back(reg);
            }
        }
    }

    // 2 operators is replaced by single function opCmp
    if (classAnalyzer.ContainsMethod("operator>") || classAnalyzer.ContainsMethod("operator<"))
        RegisterComparisonOperator(classAnalyzer, processedClass);

    if (!classAnalyzer.ContainsMethod("operator="))
        TryRegisterImplicitlyDeclaredAssignOperator(classAnalyzer, processedClass);

    if (classAnalyzer.IsAbstract()) // Abstract refcounted type
    {
        Result::classes_.push_back(processedClass);
        return;
    }

    if (!classAnalyzer.HasThisConstructor() && IsConstructorRequired(classAnalyzer))
    {
        shared_ptr<SpecialMethodRegistration> result = make_shared<SpecialMethodRegistration>();
        string cppClassName = classAnalyzer.GetClassName();
        string asClassName = classAnalyzer.GetClassName();

        if (classAnalyzer.IsRefCounted() || isNoCount)
            result->registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_FACTORY, \"" +
                                    asClassName + "@" + (isNoCount ? "" : "+") + " f()\", asFUNCTION(ASCompatibleFactory<" + cppClassName + ">), AS_CALL_CDECL);";
        else
            result->registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_CONSTRUCT, \"void f()\", asFUNCTION(ASCompatibleConstructor<" + cppClassName + ">), AS_CALL_CDECL_OBJFIRST);";

        result->comment_ = cppClassName + "::" + cppClassName + "() | Implicitly-declared";
        processedClass.defaultConstructor_ = result;
    }

    RegisterDestructor(classAnalyzer, processedClass);

    Result::classes_.push_back(processedClass);
}

void ProcessAllClasses()
{
    InitCachedMemberSignatures();

    for (pair<const string, xml_node>& element : SourceData::classesByID_)
    {
        xml_node compounddef = element.second;
        ClassAnalyzer analyzer(compounddef);
        ProcessClass(analyzer);
    }
}

} // namespace ASBindingGenerator
