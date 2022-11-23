// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace ASBindingGenerator
{

class ASGeneratedFile_Base
{
protected:
    // Result file path
    std::string outputFilePath_;

public:
    // Wrappers
    std::stringstream glue_;

    // Registration function body
    std::stringstream reg_;

    // Write result to file
    virtual void Save() {};
};

class ASGeneratedFile_WithRegistrationFunction : public ASGeneratedFile_Base
{
protected:
    // Registration function name
    std::string functionName_;

public:
    ASGeneratedFile_WithRegistrationFunction(const std::string& outputFilePath, const std::string& functionName);
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
    ASGeneratedFile_Templates(const std::string& outputFilePath);

    // Write result to file
    void Save() override;
};

struct ProcessedEnum
{
    std::string name_; // Used for sorting
    std::string comment_; // Location
    std::vector<std::string> glue_; // Can be empty
    std::string insideDefine_; // Can be empty
    std::vector<std::string> registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedEnum& rhs) const;
};

struct ProcessedGlobalFunction
{
    std::string name_; // Used for sorting
    std::string comment_; // Location
    std::string glue_; // Can be empty
    std::string insideDefine_; // Can be empty
    std::string registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedGlobalFunction& rhs) const;
};

struct ProcessedGlobalVariable
{
    std::string name_; // Used for sorting
    std::string comment_; // Location
    std::string insideDefine_; // Can be empty
    std::string registration_; // Or warning message

    // Used for sorting
    bool operator <(const ProcessedGlobalVariable& rhs) const;
};

struct Registration
{
    std::string comment_;
    std::string glue_;
    std::vector<std::string> registration_;
};

struct SpecialMethodRegistration
{
    std::string comment_; // C++ declaration / location for default constructor
    std::string glue_;
    std::string registration_; // Or warning message
};

struct RegisterObjectMethodArgs
{
    std::vector<std::string> asDeclarations_; // String
    std::string funcPointer_;            // asSFuncPtr
    std::string callConv_;               // asDWORD
};

struct MethodRegistration
{
    std::string name_; // Used for sorting
    std::string cppDeclaration_;
    std::string glue_;
    RegisterObjectMethodArgs registration_;
};

struct RegisterGlobalFunctionArgs
{
    std::vector<std::string> asDeclarations_; // String
    std::string funcPointer_;            // asSFuncPtr
    std::string callConv_;               // asDWORD
};

struct StaticMethodRegistration
{
    std::string name_; // Used for sorting
    std::string cppDeclaration_;
    std::string glue_;
    RegisterGlobalFunctionArgs registration_;
};

struct RegisterObjectPropertyArgs
{
    std::vector<std::string> asDeclarations_; // String
    std::string byteOffset_;             // int
};

struct FieldRegistration
{
    std::string name_; // Used for sorting
    std::string cppDeclaration_;
    RegisterObjectPropertyArgs registration_;
};

struct RegisterGlobalPropertyArgs
{
    std::vector<std::string> asDeclarations_; // String
    std::string pointer_;                // void*
};

struct StaticFieldRegistration
{
    std::string name_; // Used for sorting
    std::string cppDeclaration_;
    RegisterGlobalPropertyArgs registration_;
};

/*
struct RegisterObjectBehaviourArgs
{
    std::string behaviour_;              // asEBehaviours
    std::vector<std::string> asDeclarations_; // String
    std::string funcPointer_;            // asSFuncPtr
    std::string callConv_;               // asDWORD
};

struct BehaviorRegistration
{
    std::string name_; // Used for sorting
    std::string cppDeclaration_;
    //std::string glue_;
    RegisterObjectBehaviourArgs registration_;
};
*/

struct MemberRegistrationError
{
    std::string name_; // Used for sorting
    std::string comment_; // C++ declaration / location
    std::string message_;

    // Used for sorting
    bool operator <(const MemberRegistrationError& rhs) const;
};

struct ProcessedClass
{
    std::string name_;
    std::string dirName_;
    std::string insideDefine_; // Can be empty
    std::string comment_; // Class location
    std::string objectTypeRegistration_; // engine->RegisterObjectType(...); or warning message
    int inherianceDeep_ = 0; // Used for sorting

    // Used for sorting
    bool operator <(const ProcessedClass& rhs) const;

    std::shared_ptr<SpecialMethodRegistration> defaultConstructor_;
    std::vector<SpecialMethodRegistration> nonDefaultConstructors_;

    std::shared_ptr<SpecialMethodRegistration> destructor_;

    std::vector<MemberRegistrationError> unregisteredSpecialMethods_;

    //std::vector<MethodRegistration> methods_;


    //std::vector<StaticMethodRegistration> staticMethods_;
    //std::vector<MemberRegistrationError> unregisteredStaticMethods_;

    //std::vector<FieldRegistration> fields_;
    //std::vector<MemberRegistrationError> unregisteredFields_;

    //std::vector<MethodRegistration> wrappedFields_;

    //std::vector<StaticFieldRegistration> staticFields_;
    //std::vector<MemberRegistrationError> unregisteredStaticFields_;

    std::vector<std::string> additionalLines_;

    bool noBind_ = false;

    std::vector<std::string> baseClassNames_;
    std::vector<std::string> subclassRegistrations_;

    // Base class members that were hidden in this class (c++ declarations)
    /*std::vector<std::string> hiddenMethods_;
    std::vector<std::string> hiddenStaticMethods_;
    std::vector<std::string> hiddenFields_;
    std::vector<std::string> hiddenStaticFields_;*/

    std::vector<Registration> templateMethods_;
    std::vector<MemberRegistrationError> unregisteredTemplateMethods_;
    std::vector<Registration> personalMethods_;
    std::vector<MemberRegistrationError> unregisteredPersonalMethods_;

    std::vector<Registration> templateStaticMethods_;
    std::vector<MemberRegistrationError> unregisteredTemplateStaticMethods_;
    std::vector<Registration> personalStaticMethods_;
    std::vector<MemberRegistrationError> unregisteredPersonalStaticMethods_;
    
    std::vector<Registration> personalFields_;
    std::vector<MemberRegistrationError> unregisteredPersonalFields_;
    std::vector<Registration> templateFields_;
    std::vector<MemberRegistrationError> unregisteredTemplateFields_;

    std::vector<Registration> personalStaticFields_;
    std::vector<MemberRegistrationError> unregisteredPersonalStaticFields_;
    std::vector<Registration> templateStaticFields_;
    std::vector<MemberRegistrationError> unregisteredTemplateStaticFields_;
};

namespace Result
{
    extern std::vector<ProcessedEnum> enums_;
    extern std::vector<ProcessedGlobalFunction> globalFunctions_;
    extern std::vector<ProcessedGlobalVariable> globalVariables_;
    extern std::vector<ProcessedClass> classes_;

    // Add header to lists if not added yet
    void AddHeader(const std::string& headerFile);
}

} // namespace ASBindingGenerator
