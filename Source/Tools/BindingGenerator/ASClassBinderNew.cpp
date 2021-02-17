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

static void RegisterDefaultConstructor(const ClassAnalyzer& classAnalyzer, ProcessedClass& processedClass)
{
    if (classAnalyzer.IsRefCounted())
        return;

    if (Contains(classAnalyzer.GetComment(), "FAKE_REF"))
        return;

    string className = classAnalyzer.GetClassName();
    string wrapperName = className + "_Constructor";

    shared_ptr<ClassMemberRegistration> result = make_shared<ClassMemberRegistration>();

    result->name_ = className;

    result->glue_ =
        "static void " + wrapperName + "(" + className + "* ptr)\n"
        "{\n"
        "    new(ptr) " + className + "();\n"
        "}\n";

    result->registration_ = "engine->RegisterObjectBehaviour(\"" + className + "\", asBEHAVE_CONSTRUCT, \"void f()\", asFUNCTION(" + wrapperName + "), asCALL_CDECL_OBJFIRST);";

    shared_ptr<ClassFunctionAnalyzer> defaultConstructor = classAnalyzer.GetDefinedThisDefaultConstructor();

    if (defaultConstructor)
    {
        result->comment_ = defaultConstructor->GetLocation();
        processedClass.defaultConstructor_ = result;
    }
    else if (!classAnalyzer.HasThisConstructor() && IsConstructorRequired(classAnalyzer))
    {
        result->comment_ = className + "::" + className + "() | Implicitly-declared";
        processedClass.defaultConstructor_ = result;
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

    shared_ptr<ClassMemberRegistration> result = make_shared<ClassMemberRegistration>();

    result->name_ = "~" + className;

    result->glue_ =
        "static void " + wrapperName + "(" + className + "* ptr)\n"
        "{\n"
        "    ptr->~" + className + "();\n"
        "}\n";

    result->registration_ = "engine->RegisterObjectBehaviour(\"" + className + "\", asBEHAVE_DESTRUCT, \"void f()\", asFUNCTION(" + wrapperName + "), asCALL_CDECL_OBJFIRST);";

    shared_ptr<ClassFunctionAnalyzer> thisDestructor = classAnalyzer.GetDefinedThisDestructor();

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

static void RegisterNonDefaultConstructor(const ClassFunctionAnalyzer& classFunctionAnalyzer, ProcessedClass& processedClass)
{
    processedClass.nonDefaultConstructors_.push_back(classFunctionAnalyzer.GetLocation());
}

static void ProcessClass(const ClassAnalyzer& classAnalyzer)
{
    if (classAnalyzer.IsInternal())
        return;

    // TODO: Remove
    if (classAnalyzer.IsTemplate())
        return;

    // TODO: Remove
    if (classAnalyzer.IsAbstract() && !(classAnalyzer.IsRefCounted() || Contains(classAnalyzer.GetComment(), "FAKE_REF")))
        return;

    string header = classAnalyzer.GetHeaderFile();
    Result::AddHeader(header);

    if (IsIgnoredHeader(header))
        return;

    ProcessedClass processedClass;
    processedClass.name_ = classAnalyzer.GetClassName();
    processedClass.comment_ = classAnalyzer.GetLocation();
    processedClass.insideDefine_ = InsideDefine(header);

    string classComment = classAnalyzer.GetComment();

    if (Contains(classComment, "NO_BIND"))
    {
        processedClass.objectTypeRegistration_ = "// Not registered because have @nobind mark";
        Result::classes_.push_back(processedClass);
        return;
    }

    if (Contains(classComment, "MANUAL_BIND"))
    {
        processedClass.objectTypeRegistration_ = "// Not registered because have @manualbind mark";
        Result::classes_.push_back(processedClass);
        return;
    }

    RegisterObjectType(classAnalyzer, processedClass);
    RegisterDefaultConstructor(classAnalyzer, processedClass);

    vector<ClassFunctionAnalyzer> nonDefaultConstructors = classAnalyzer.GetThisNonDefaultConstructors();
    for (const ClassFunctionAnalyzer& classFunctionAnalyzer : nonDefaultConstructors)
        RegisterNonDefaultConstructor(classFunctionAnalyzer, processedClass);

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
