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

#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace ASBindingGenerator
{

class ASGeneratedFile_Base
{
protected:
    // Result file path
    string outputFilePath_;

public:
    // Wrappers
    stringstream glue_;

    // Registration function body
    stringstream reg_;

    // Write result to file
    virtual void Save() {};
};

class ASGeneratedFile_WithRegistrationFunction : public ASGeneratedFile_Base
{
protected:
    // Registration function name
    string functionName_;

public:
    ASGeneratedFile_WithRegistrationFunction(const string& outputFilePath, const string& functionName);
};

class ASGeneratedFile_Members : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_Templates : public ASGeneratedFile_Base
{

public:
    ASGeneratedFile_Templates(const string& outputFilePath);

    // Write result to file
    void Save() override;
};

struct ProcessedEnum
{
    string name_; // Used for sorting
    string comment_; // Location
    vector<string> glue_; // Can be empty
    string insideDefine_; // Can be empty
    vector<string> registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedEnum& rhs) const;
};

struct ProcessedGlobalFunction
{
    string name_; // Used for sorting
    string comment_; // Location
    string glue_; // Can be empty
    string insideDefine_; // Can be empty
    string registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedGlobalFunction& rhs) const;
};

struct ProcessedGlobalVariable
{
    string name_; // Used for sorting
    string comment_; // Location
    string insideDefine_; // Can be empty
    string registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedGlobalVariable& rhs) const;
};

struct Registration
{
    string comment_;
    string glue_;
    vector<string> registration_;
};

struct SpecialMethodRegistration
{
    string comment_; // C++ declaration / location for default constructor
    string glue_;
    string registration_; // Or warning message
};

struct RegisterObjectMethodArgs
{
    vector<string> asDeclarations_; // String
    string funcPointer_;            // asSFuncPtr
    string callConv_;               // asDWORD
};

struct MethodRegistration
{
    string name_; // Used for sorting
    string cppDeclaration_;
    string glue_;
    RegisterObjectMethodArgs registration_;
};

struct RegisterGlobalFunctionArgs
{
    vector<string> asDeclarations_; // String
    string funcPointer_;            // asSFuncPtr
    string callConv_;               // asDWORD
};

struct StaticMethodRegistration
{
    string name_; // Used for sorting
    string cppDeclaration_;
    string glue_;
    RegisterGlobalFunctionArgs registration_;
};

struct RegisterObjectPropertyArgs
{
    vector<string> asDeclarations_; // String
    string byteOffset_;             // int
};

struct FieldRegistration
{
    string name_; // Used for sorting
    string cppDeclaration_;
    RegisterObjectPropertyArgs registration_;
};

struct RegisterGlobalPropertyArgs
{
    vector<string> asDeclarations_; // String
    string pointer_;                // void*
};

struct StaticFieldRegistration
{
    string name_; // Used for sorting
    string cppDeclaration_;
    RegisterGlobalPropertyArgs registration_;
};

/*
struct RegisterObjectBehaviourArgs
{
    string behaviour_;              // asEBehaviours
    vector<string> asDeclarations_; // String
    string funcPointer_;            // asSFuncPtr
    string callConv_;               // asDWORD
};

struct BehaviorRegistration
{
    string name_; // Used for sorting
    string cppDeclaration_;
    //string glue_;
    RegisterObjectBehaviourArgs registration_;
};
*/

struct MemberRegistrationError
{
    string name_; // Used for sorting
    string comment_; // C++ declaration / location
    string message_;

    // Used for sorting
    bool operator <(const MemberRegistrationError& rhs) const;
};

struct ProcessedClass
{
    string name_;
    string dirName_;
    string insideDefine_; // Can be empty
    string comment_; // Class location
    string objectTypeRegistration_; // engine->RegisterObjectType(...); or warning message
    int inherianceDeep_ = 0; // Used for sorting

    // Used for sorting
    bool operator <(const ProcessedClass& rhs) const;

    shared_ptr<SpecialMethodRegistration> defaultConstructor_;
    vector<SpecialMethodRegistration> nonDefaultConstructors_;

    shared_ptr<SpecialMethodRegistration> destructor_;

    vector<SpecialMethodRegistration> fakeRefBehaviors_;

    vector<MemberRegistrationError> unregisteredSpecialMethods_;

    //vector<MethodRegistration> methods_;


    //vector<StaticMethodRegistration> staticMethods_;
    //vector<MemberRegistrationError> unregisteredStaticMethods_;

    //vector<FieldRegistration> fields_;
    //vector<MemberRegistrationError> unregisteredFields_;

    //vector<MethodRegistration> wrappedFields_;

    //vector<StaticFieldRegistration> staticFields_;
    //vector<MemberRegistrationError> unregisteredStaticFields_;

    vector<string> additionalLines_;

    bool noBind_ = false;

    vector<string> baseClassNames_;
    vector<string> subclassRegistrations_;

    // Base class members that were hidden in this class (c++ declarations)
    /*vector<string> hiddenMethods_;
    vector<string> hiddenStaticMethods_;
    vector<string> hiddenFields_;
    vector<string> hiddenStaticFields_;*/

    vector<Registration> templateMethods_;
    vector<MemberRegistrationError> unregisteredTemplateMethods_;
    vector<Registration> personalMethods_;
    vector<MemberRegistrationError> unregisteredPersonalMethods_;

    vector<Registration> templateStaticMethods_;
    vector<MemberRegistrationError> unregisteredTemplateStaticMethods_;
    vector<Registration> personalStaticMethods_;
    vector<MemberRegistrationError> unregisteredPersonalStaticMethods_;
    
    vector<Registration> personalFields_;
    vector<MemberRegistrationError> unregisteredPersonalFields_;
    vector<Registration> templateFields_;
    vector<MemberRegistrationError> unregisteredTemplateFields_;

    vector<Registration> personalStaticFields_;
    vector<MemberRegistrationError> unregisteredPersonalStaticFields_;
    vector<Registration> templateStaticFields_;
    vector<MemberRegistrationError> unregisteredTemplateStaticFields_;
};

namespace Result
{
    extern vector<ProcessedEnum> enums_;
    extern vector<ProcessedGlobalFunction> globalFunctions_;
    extern vector<ProcessedGlobalVariable> globalVariables_;
    extern vector<ProcessedClass> classes_;

    // Add header to lists if not added yet
    void AddHeader(const string& headerFile);
}

} // namespace ASBindingGenerator
