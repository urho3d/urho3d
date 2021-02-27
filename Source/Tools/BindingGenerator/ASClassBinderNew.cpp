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

#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

namespace ASBindingGenerator
{

static void RegisterObjectType(const ClassAnalyzer& classAnalyzer, ProcessedClass& inoutProcessedClass)
{
    string className = classAnalyzer.GetClassName();

    if (classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF"))
    {
        inoutProcessedClass.objectTypeRegistration_ = "engine->RegisterObjectType(\"" + className + "\", 0, asOBJ_REF);";
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

    if (Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        return false;

    if (classAnalyzer.IsPod())
        return false;

    return true;
}

static bool IsDestructorRequired(const ClassAnalyzer& classAnalyzer)
{
    if (classAnalyzer.IsRefCounted())
        return false;

    if (Contains(classAnalyzer.GetComment(), "FAKE_REF"))
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

    if (HaveMark(methodAnalyzer, "NO_BIND"))
    {
        RegistrationError regError;
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @nobind mark";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    if (HaveMark(methodAnalyzer, "MANUAL_BIND"))
    {
        RegistrationError regError;
        regError.comment_ = methodAnalyzer.GetDeclaration();
        regError.message_ = "Not registered because have @manualbind mark";
        processedClass.unregisteredSpecialMethods_.push_back(regError);
        return;
    }

    MemberRegistration result;
    result.name_ = methodAnalyzer.GetName();
    result.comment_ = methodAnalyzer.GetDeclaration();
    
    string asClassName = classAnalyzer.GetClassName();
    string cppClassName = classAnalyzer.GetClassName();
    vector<ParamAnalyzer> params = methodAnalyzer.GetParams();

    if (params.empty()) // Default constructor
    {
        if (classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        {
        }
        else
        {
            result.comment_ = methodAnalyzer.GetLocation(); // Rewrite comment
            result.registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_CONSTRUCT, \"void f()\", asFUNCTION(ASCompatibleConstructor<" + cppClassName + ">), AS_CALL_CDECL_OBJFIRST);";
            processedClass.defaultConstructor_ = make_shared<MemberRegistration>(result);
            return;
        }
    }
}

static void RegisterDestructor(const ClassAnalyzer& classAnalyzer, ProcessedClass& processedClass)
{
    if (classAnalyzer.IsRefCounted())
        return;

    if (Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        return;

    string className = classAnalyzer.GetClassName();
    string wrapperName = className + "_Destructor";

    shared_ptr<MemberRegistration> result = make_shared<MemberRegistration>();

    result->name_ = "~" + className;

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
    processedClass.comment_ = classAnalyzer.GetLocation();
    processedClass.insideDefine_ = InsideDefine(header);

    vector<MethodAnalyzer> methods = classAnalyzer.GetThisPublicMethods();
    for (const MethodAnalyzer& method : methods)
    {
        if (method.IsThisConstructor())
            RegisterConstructor(method, processedClass);
    }

    // CollectMembers()

    if (classAnalyzer.IsAbstract() && !(classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF")))
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

    vector<ClassAnalyzer> baseClasses = classAnalyzer.GetBaseClasses();
    for (const ClassAnalyzer& baseClass : baseClasses)
        processedClass.baseClassNames_.push_back(baseClass.GetClassName());

    if (classAnalyzer.IsAbstract()) // Abstract refcounted type
    {
        Result::classes_.push_back(processedClass);
        return;
    }

    if (!classAnalyzer.HasThisConstructor() && IsConstructorRequired(classAnalyzer))
    {
        if (classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        {
        }
        else
        {
            shared_ptr<MemberRegistration> result = make_shared<MemberRegistration>();
            string cppClassName = classAnalyzer.GetClassName();
            string asClassName = classAnalyzer.GetClassName();
            result->comment_ = cppClassName + "::" + cppClassName + "() | Implicitly-declared";
            result->registration_ = "engine->RegisterObjectBehaviour(\"" + asClassName + "\", asBEHAVE_CONSTRUCT, \"void f()\", asFUNCTION(ASCompatibleConstructor<" + cppClassName + ">), AS_CALL_CDECL_OBJFIRST);";
            processedClass.defaultConstructor_ = result;
        }
    }

    RegisterDestructor(classAnalyzer, processedClass);

    Result::classes_.push_back(processedClass);
}

void ProcessAllClassesNew()
{
#if 0
    // Old order of classes for tests
    vector<string> classIDs;
    classIDs.reserve(SourceData::classesByID_.size());
    for (pair<const string, xml_node>& it : SourceData::classesByID_)
        classIDs.push_back(it.first);
    sort(classIDs.begin(), classIDs.end());

    for (string classID : classIDs)
    {
        xml_node compounddef = SourceData::classesByID_[classID];
        ClassAnalyzer analyzer(compounddef);
        ProcessClass(analyzer);
    }
#else
    for (auto element : SourceData::classesByID_)
    {
        xml_node compounddef = element.second;
        ClassAnalyzer analyzer(compounddef);
        ProcessClass(analyzer);
    }
#endif
}

} // namespace ASBindingGenerator
