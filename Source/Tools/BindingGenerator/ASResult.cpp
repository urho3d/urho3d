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
#include "Tuning.h"
#include "Utils.h"

#include <fstream>
#include <cassert>
#include <unordered_map>
#include <memory>

extern string _sourceDir;

namespace ASBindingGenerator
{

ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction(const string& outputFilePath, const string& functionName)
{
    outputFilePath_ = outputFilePath;
    functionName_ = functionName;
}

// ============================================================================

void ASGeneratedFile_Members::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "\n"
        "#include \"../AngelScript/Generated_Includes.h\"\n"
        "#include \"../AngelScript/Manual.h\"\n"
        "\n"
        "namespace Urho3D\n"
        "{\n"
        "\n"
        "void FakeAddRef(void* ptr);\n"
        "void FakeReleaseRef(void* ptr);\n"
        "\n"
        << glue_.str() <<
        "void " << functionName_ << "(asIScriptEngine* engine)\n"
        "{\n"
        << reg_.str() <<
        "}\n"
        "\n"
        "}\n";
}

// ============================================================================

ASGeneratedFile_Templates::ASGeneratedFile_Templates(const string& outputFilePath)
{
    outputFilePath_ = outputFilePath;
}

void ASGeneratedFile_Templates::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "#pragma once\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "\n"
        "#include \"../AngelScript/Generated_Includes.h\"\n"
        "\n"
        "#include \"../AngelScript/Manual.h\"\n"
        "\n"
        "namespace Urho3D\n"
        "{\n"
        "\n"
        "void FakeAddRef(void* ptr);\n"
        "void FakeReleaseRef(void* ptr);\n"
        "\n"
        << glue_.str()
        << reg_.str() <<
        "}\n";
}

bool ProcessedEnum::operator <(const ProcessedEnum& rhs) const
{
    if (insideDefine_ != rhs.insideDefine_)
        return insideDefine_ < rhs.insideDefine_;

    return name_ < rhs.name_;
}

bool ProcessedGlobalFunction::operator <(const ProcessedGlobalFunction& rhs) const
{
    if (insideDefine_ != rhs.insideDefine_)
        return insideDefine_ < rhs.insideDefine_;

    if (name_ != rhs.name_)
        return name_ < rhs.name_;

    // Overloads with the same name may exist
    if (comment_ != rhs.comment_)
        return comment_ < rhs.comment_;

    // Different specializations of the same template and aliases have the same comment
    return registration_ < rhs.registration_;
}

bool ProcessedGlobalVariable::operator <(const ProcessedGlobalVariable& rhs) const
{
    if (insideDefine_ != rhs.insideDefine_)
        return insideDefine_ < rhs.insideDefine_;

    return name_ < rhs.name_;
}

bool ProcessedClass::operator <(const ProcessedClass& rhs) const
{
    if (inherianceDeep_ != rhs.inherianceDeep_)
        return inherianceDeep_ < rhs.inherianceDeep_;

    if (insideDefine_ != rhs.insideDefine_)
        return insideDefine_ < rhs.insideDefine_;

    return name_ < rhs.name_;
}

bool MemberRegistrationError::operator <(const MemberRegistrationError& rhs) const
{
    if (name_ != rhs.name_)
        return name_ < rhs.name_;

    return comment_ < rhs.comment_;
}

namespace Result
{
    vector<ProcessedEnum> enums_;

    // Write result to Generated_Enums.cpp
    static void SaveEnums()
    {
        sort(enums_.begin(), enums_.end());

        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_Enums.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register all enums before registration of any functions because functions can use any enums\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n";

        for (const ProcessedEnum& processedEnum : enums_)
        {
            if (!processedEnum.glue_.size())
                continue;

            if (!processedEnum.insideDefine_.empty())
                ofs << "#ifdef " << processedEnum.insideDefine_ << "\n";

            ofs << "// " << processedEnum.comment_ << "\n";

            for (const string& glue : processedEnum.glue_)
                ofs << glue << "\n";

            if (!processedEnum.insideDefine_.empty())
                ofs << "#endif\n";

            ofs << "\n";
        }

        ofs <<
            "void ASRegisterGeneratedEnums(asIScriptEngine* engine)\n"
            "{\n";

        bool isFirst = true;
        string openedDefine;

        for (const ProcessedEnum& processedEnum : enums_)
        {
            if (processedEnum.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (!isFirst)
                ofs << "\n";

            if (processedEnum.insideDefine_ != openedDefine && !processedEnum.insideDefine_.empty())
            {
                ofs << "#ifdef " << processedEnum.insideDefine_ << "\n";
                openedDefine = processedEnum.insideDefine_;
            }

            ofs << "    // " << processedEnum.comment_ << "\n";

            for (const string& registration : processedEnum.registration_)
                ofs << "    " << registration << "\n";

            isFirst = false;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }

    // ============================================================================

    vector<ProcessedGlobalFunction> globalFunctions_;

    // Write result to Generated_GlobalFunctions.cpp
    static void SaveGlobalFunctions()
    {
        sort(globalFunctions_.begin(), globalFunctions_.end());

        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_GlobalFunctions.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n";

        for (const ProcessedGlobalFunction& globalFunction : globalFunctions_)
        {
            if (globalFunction.glue_.empty())
                continue;

            if (!globalFunction.insideDefine_.empty())
                ofs << "#ifdef " << globalFunction.insideDefine_ << "\n";

            ofs << "// " << globalFunction.comment_ << "\n";
            ofs << globalFunction.glue_ << "\n";

            if (!globalFunction.insideDefine_.empty())
                ofs << "#endif\n";

            ofs << "\n";
        }

        ofs <<
            "void ASRegisterGeneratedGlobalFunctions(asIScriptEngine* engine)\n"
            "{\n";

        bool isFirst = true;
        string openedDefine;
        string lastComment;

        for (const ProcessedGlobalFunction& globalFunction : globalFunctions_)
        {
            if (globalFunction.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (!isFirst && lastComment != globalFunction.comment_)
                ofs << "\n";

            if (globalFunction.insideDefine_ != openedDefine && !globalFunction.insideDefine_.empty())
            {
                ofs << "#ifdef " << globalFunction.insideDefine_ << "\n";
                openedDefine = globalFunction.insideDefine_;
            }

            if (lastComment != globalFunction.comment_)
                ofs << "    // " << globalFunction.comment_ << "\n";

            ofs << "    " << globalFunction.registration_ << "\n";

            isFirst = false;
            lastComment = globalFunction.comment_;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }

    // ============================================================================

    vector<ProcessedGlobalVariable> globalVariables_;

    // Write result to Generated_GlobalVariables.cpp
    static void SaveGlobalVariables()
    {
        sort(globalVariables_.begin(), globalVariables_.end());

        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_GlobalVariables.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "\n"
            "// Some headers could re-define M_PI, ensure that it's undefined\n"
            "#undef M_PI\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void ASRegisterGeneratedGlobalVariables(asIScriptEngine* engine)\n"
            "{\n";

        bool isFirst = true;
        string openedDefine;
        string lastComment;

        for (const ProcessedGlobalVariable& globalVariable : globalVariables_)
        {
            if (globalVariable.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (!isFirst && lastComment != globalVariable.comment_)
                ofs << "\n";

            if (globalVariable.insideDefine_ != openedDefine && !globalVariable.insideDefine_.empty())
            {
                ofs << "#ifdef " << globalVariable.insideDefine_ << "\n";
                openedDefine = globalVariable.insideDefine_;
            }

            if (lastComment != globalVariable.comment_)
                ofs << "    // " << globalVariable.comment_ << "\n";

            ofs << "    " << globalVariable.registration_ << "\n";

            isFirst = false;
            lastComment = globalVariable.comment_;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }
    // ============================================================================

    vector<ProcessedClass> classes_;

    // Write result to Generated_ObjectTypes.cpp
    static void SaveObjectTypes()
    {
        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_ObjectTypes.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register all types before registration of any functions because functions can use any types\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void ASRegisterGeneratedObjectTypes(asIScriptEngine* engine)\n"
            "{\n";

        string openedDefine;
        bool isFirst = true;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (!isFirst)
                ofs << "\n";

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofs << "#ifdef " << processedClass.insideDefine_ << "\n";
                openedDefine = processedClass.insideDefine_;
            }

            ofs
                << "    // " << processedClass.comment_ << "\n"
                << "    " << processedClass.objectTypeRegistration_ << "\n";

            isFirst = false;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }

    // Write result to Generated_DefaultConstructors.cpp
    static void SaveDefaultConstructors()
    {
        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_DefaultConstructors.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register default constructors before any members to allow using in Array<type>\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n";

        string openedDefine;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (!processedClass.defaultConstructor_)
                continue;

            if (processedClass.defaultConstructor_->glue_.empty())
                continue;

            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "\n#endif\n";
                openedDefine.clear();
            }

            ofs << "\n";

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofs << "#ifdef " << processedClass.insideDefine_ << "\n\n";
                openedDefine = processedClass.insideDefine_;
            }

             ofs <<
                 "// " << processedClass.defaultConstructor_->comment_ << "\n" <<
                 processedClass.defaultConstructor_->glue_;
        }

        if (!openedDefine.empty())
        {
            ofs << "\n#endif\n";
            openedDefine.clear();
        }

        ofs <<
            "\n"
            "void ASRegisterGeneratedDefaultConstructors(asIScriptEngine* engine)\n"
            "{\n";

        bool isFirst = true;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (!processedClass.defaultConstructor_)
                continue;

            if (processedClass.noBind_)
                continue;

            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (!isFirst)
                ofs << "\n";

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofs << "#ifdef " << processedClass.insideDefine_ << "\n";
                openedDefine = processedClass.insideDefine_;
            }

            ofs <<
                "    // " << processedClass.defaultConstructor_->comment_ << "\n" <<
                "    " << processedClass.defaultConstructor_->registration_ << "\n";

            isFirst = false;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }

    // Write result to Generated_Classes.cpp
    static void SaveGeneratedClasses()
    {
        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_Classes.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "#include \"../AngelScript/Generated_Members.h\"\n"
            "#include \"../AngelScript/Manual.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void FakeAddRef(void* ptr);\n"
            "void FakeReleaseRef(void* ptr);\n";

        string openedDefine;
        
        for (ProcessedClass& processedClass : classes_)
        {
            if (processedClass.noBind_)
                continue;

            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "\n#endif // def " << openedDefine << "\n";
                openedDefine.clear();
            }

            ofs << "\n";

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofs << "#ifdef " << processedClass.insideDefine_ << "\n\n";
                openedDefine = processedClass.insideDefine_;
            }

            if (processedClass.destructor_ && !processedClass.destructor_->glue_.empty())
            {
                ofs <<
                    "// " << processedClass.destructor_->comment_ << "\n"
                    << processedClass.destructor_->glue_ <<
                    "\n";
            }

            for (const SpecialMethodRegistration& nonDefaultConstructor : processedClass.nonDefaultConstructors_)
            {
                ofs <<
                    "// " << nonDefaultConstructor.comment_ << "\n"
                    << nonDefaultConstructor.glue_ <<
                    "\n";
            }

            for (const Registration& personalMethod : processedClass.personalMethods_)
            {
                if (personalMethod.glue_.size())
                {
                    ofs <<
                        "// " << personalMethod.comment_ << "\n"
                        << personalMethod.glue_ <<
                        "\n";
                }
            }

            for (const Registration& personalStaticMethod : processedClass.personalStaticMethods_)
            {
                if (personalStaticMethod.glue_.size())
                {
                    ofs <<
                        "// " << personalStaticMethod.comment_ << "\n"
                        << personalStaticMethod.glue_ <<
                        "\n";
                }
            }

            ofs <<
                "// " << processedClass.comment_ << "\n"
                "static void Register_" << processedClass.name_ << "(asIScriptEngine* engine)\n"
                "{\n";

            bool needGap = false;

            sort(processedClass.unregisteredSpecialMethods_.begin(), processedClass.unregisteredSpecialMethods_.end());

            for (const MemberRegistrationError& regError : processedClass.unregisteredSpecialMethods_)
            {
                ofs <<
                    "    // " << regError.comment_ << "\n"
                    "    // " << regError.message_ << "\n";

                needGap = true;
            }

            if (needGap && processedClass.nonDefaultConstructors_.size())
                ofs << '\n';

            for (const SpecialMethodRegistration& nonDefaultConstructor : processedClass.nonDefaultConstructors_)
            {
                ofs <<
                    "    // " << nonDefaultConstructor.comment_ << "\n"
                    "    " << nonDefaultConstructor.registration_ << "\n";

                needGap = true;
            }

            if (processedClass.destructor_)
            {
                if (needGap)
                    ofs << '\n';

                ofs <<
                    "    // " << processedClass.destructor_->comment_ << "\n"
                    "    " << processedClass.destructor_->registration_ << "\n";
                
                needGap = true;
            }

            if (needGap && processedClass.fakeRefBehaviors_.size())
                ofs << '\n';

            for (const SpecialMethodRegistration& fakeRefBehavior : processedClass.fakeRefBehaviors_)
            {
                if (fakeRefBehavior.comment_.size())
                    ofs << "    // " << fakeRefBehavior.comment_ << '\n';

                ofs << "    " + fakeRefBehavior.registration_ << '\n';

                needGap = true;
            }


            if (needGap && processedClass.subclassRegistrations_.size())
                ofs << '\n';

            for (const string& subclassRegistration : processedClass.subclassRegistrations_)
            {
                ofs << "    " << subclassRegistration << '\n';

                needGap = true;
            }

            if (needGap)
                ofs << '\n';

            ofs <<
                "    RegisterMembers_" << processedClass.name_ << "<" << processedClass.name_ << ">(engine, \"" << processedClass.name_ << "\");\n"
                "\n"
                "    #ifdef REGISTER_CLASS_MANUAL_PART_" << processedClass.name_ << "\n"
                "        REGISTER_CLASS_MANUAL_PART_" << processedClass.name_ << "();\n"
                "    #endif\n";

            for (const MemberRegistrationError& unregisteredPersonalMethod : processedClass.unregisteredPersonalMethods_)
            {
                ofs <<
                    "\n"
                    "    // " << unregisteredPersonalMethod.comment_ << "\n"
                    "    // " << unregisteredPersonalMethod.message_ << "\n";

                needGap = true;
            }

            for (const Registration& perosnalMethod : processedClass.personalMethods_)
            {
                ofs <<
                    "\n"
                    "    // " << perosnalMethod.comment_ << "\n";

                for (const string& reg : perosnalMethod.registration_)
                    ofs << "    " << reg << '\n';
            }

            for (const MemberRegistrationError& unregisteredPersonalStaticMethod : processedClass.unregisteredPersonalStaticMethods_)
            {
                ofs <<
                    "\n"
                    "    // " << unregisteredPersonalStaticMethod.comment_ << "\n"
                    "    // " << unregisteredPersonalStaticMethod.message_ << "\n";

                needGap = true;
            }

            for (const Registration& perosnalStaticMethod : processedClass.personalStaticMethods_)
            {
                ofs <<
                    "\n"
                    "    // " << perosnalStaticMethod.comment_ << "\n";

                for (const string& reg : perosnalStaticMethod.registration_)
                    ofs << "    " << reg << '\n';
            }

            if (processedClass.additionalLines_.size())
                ofs << '\n';

            for (string str : processedClass.additionalLines_)
                ofs << str << '\n';

            ofs << "}\n";
        }

        if (!openedDefine.empty())
        {
            ofs << "\n#endif // def " << openedDefine << "\n";
            openedDefine.clear();
        }

        ofs <<
            "\n"
            "void ASRegisterGeneratedClasses(asIScriptEngine* engine)\n"
            "{\n";

        bool isFirst = true;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (processedClass.noBind_)
                continue;

            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofs << "#endif\n";
                openedDefine.clear();
            }

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                if (!isFirst)
                    ofs << "\n";

                ofs << "#ifdef " << processedClass.insideDefine_ << "\n";
                openedDefine = processedClass.insideDefine_;
            }

            ofs << "    Register_" << processedClass.name_ << "(engine);\n";

            isFirst = false;
        }

        if (!openedDefine.empty())
            ofs << "#endif\n";

        ofs <<
            "}\n"
            "\n"
            "}\n";
    }

    struct MemberCppFile
    {
        ofstream ofs_;
        string openedDefine_;
        bool needGap_ = false;

        MemberCppFile(const string& dirName)
        {
            string fileName = _sourceDir + "/Source/Urho3D/AngelScript/Generated_Members_" + dirName + ".cpp";
            ofs_ = ofstream(fileName);

            ofs_ <<
                "// DO NOT EDIT. This file is generated\n"
                "\n"
                "#include \"../Precompiled.h\"\n"
                "#include \"../AngelScript/APITemplates.h\"\n"
                "\n"
                "#include \"../AngelScript/Generated_Includes.h\"\n"
                "#include \"../AngelScript/Generated_ClassMembers.h\"\n"
                "#include \"../AngelScript/Manual.h\"\n"
                "\n"
                "namespace Urho3D\n"
                "{\n";
        }
    };

    unordered_map<string, shared_ptr<MemberCppFile>> memberCppFiles_;

    shared_ptr<MemberCppFile> GetMemberCppFile(const string& dirName)
    {
        auto it = memberCppFiles_.find(dirName);

        if (it == memberCppFiles_.end())
        {
            auto newElement = memberCppFiles_.emplace(dirName, make_shared<MemberCppFile>(dirName));
            it = newElement.first;
        }

        return (*it).second;
    }

    // Write result to GeneratedClassMembers.cpp and GeneratedClassMembers.h // TODO change comment
    static void SaveClassMembers()
    {
        ofstream ofsH = ofstream(_sourceDir + "/Source/Urho3D/AngelScript/Generated_Members.h");

        ofsH <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#pragma once\n"
            "\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/Generated_Includes.h\"\n"
            "#include \"../AngelScript/Manual.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n";

        string openedDefine;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofsH <<
                    "\n"
                    "#endif // def " << openedDefine << "\n";

                openedDefine.clear();
            }

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofsH <<
                    "\n"
                    "#ifdef " << processedClass.insideDefine_ << "\n";

                openedDefine = processedClass.insideDefine_;
            }

            for (const Registration& method : processedClass.templateMethods_)
            {
                if (method.glue_.size())
                {
                    ofsH <<
                        "\n"
                        "// " << method.comment_ << "\n"
                        << method.glue_;
                }
            }

            for (const Registration& staticMethod : processedClass.templateStaticMethods_)
            {
                if (staticMethod.glue_.size())
                {
                    ofsH <<
                        "\n"
                        "// " << staticMethod.comment_ << "\n"
                        << staticMethod.glue_;
                }
            }

            ofsH <<
                "\n"
                "// " << processedClass.comment_ << "\n"
                "template <class T> void RegisterMembers_" << processedClass.name_ << "(asIScriptEngine* engine, const char* className)\n"
                "{\n";

            bool needGap = false;

            if (processedClass.baseClassNames_.size())
            {
                for (const string& baseClassName : processedClass.baseClassNames_)
                    ofsH << "    RegisterMembers_" << baseClassName << "<T>(engine, className);\n";

                needGap = true;
            }

            if (needGap && processedClass.unregisteredTemplateMethods_.size())
                ofsH << '\n';

            for (const MemberRegistrationError& unregisteredTemplateMethod : processedClass.unregisteredTemplateMethods_)
            {
                ofsH <<
                    "    // " << unregisteredTemplateMethod.comment_ << "\n"
                    "    // " << unregisteredTemplateMethod.message_ << "\n";

                needGap = true;
            }

            for (const Registration& method : processedClass.templateMethods_)
            {
                if (needGap)
                    ofsH << '\n';

                ofsH << "    // " << method.comment_ << '\n';

                for (const string& registration : method.registration_)
                    ofsH << "    " << registration << '\n';

                needGap = true;
            }

            if (needGap && processedClass.unregisteredTemplateStaticMethods_.size())
                ofsH << '\n';

            for (const MemberRegistrationError& unregisteredTemplateStaticMethod : processedClass.unregisteredTemplateStaticMethods_)
            {
                ofsH <<
                    "    // " << unregisteredTemplateStaticMethod.comment_ << "\n"
                    "    // " << unregisteredTemplateStaticMethod.message_ << "\n";

                needGap = true;
            }

            for (const Registration& staticMethod : processedClass.templateStaticMethods_)
            {
                if (needGap)
                    ofsH << '\n';

                ofsH << "    // " << staticMethod.comment_ << '\n';

                for (const string& registration : staticMethod.registration_)
                    ofsH << "    " << registration << '\n';

                needGap = true;
            }

            if (needGap && processedClass.unregisteredTemplateFields_.size())
                ofsH << '\n';

            for (const MemberRegistrationError& unregisteredTemplateField : processedClass.unregisteredTemplateFields_)
            {
                ofsH <<
                    "    // " << unregisteredTemplateField.comment_ << "\n"
                    "    // " << unregisteredTemplateField.message_ << "\n";

                needGap = true;
            }

            for (const Registration& field : processedClass.templateFields_)
            {
                if (needGap)
                    ofsH << '\n';

                ofsH << "    // " << field.comment_ << '\n';

                for (const string& registration : field.registration_)
                    ofsH << "    " << registration << '\n';

                needGap = true;
            }

            if (needGap && processedClass.unregisteredTemplateStaticFields_.size())
                ofsH << '\n';

            for (const MemberRegistrationError& unregisteredTemplateStaticField : processedClass.unregisteredTemplateStaticFields_)
            {
                ofsH <<
                    "    // " << unregisteredTemplateStaticField.comment_ << "\n"
                    "    // " << unregisteredTemplateStaticField.message_ << "\n";

                needGap = true;
            }

            for (const Registration& field : processedClass.templateStaticFields_)
            {
                if (needGap)
                    ofsH << '\n';

                ofsH << "    // " << field.comment_ << '\n';

                for (const string& registration : field.registration_)
                    ofsH << "    " << registration << '\n';

                needGap = true;
            }

            if (needGap)
                ofsH << '\n';

            ofsH <<
                "    #ifdef REGISTER_MEMBERS_MANUAL_PART_" << processedClass.name_ << "\n"
                "        REGISTER_MEMBERS_MANUAL_PART_" << processedClass.name_ << "();\n"
                "    #endif\n";

            ofsH << "}\n";
        }

        if (!openedDefine.empty())
        {
            ofsH <<
                "\n"
                "#endif // def " << openedDefine << "\n";

            openedDefine.clear();
        }

        ofsH <<
            "\n"
            "} // namespace Urho3D\n";
    }

    static void SaveClasses()
    {
        sort(classes_.begin(), classes_.end());
        SaveObjectTypes();
        SaveDefaultConstructors();
        SaveGeneratedClasses();
        SaveClassMembers();
    }

    // ============================================================================

    // List of all required header files
    static vector<string> headers_;

    // Discarded header files for statistic
    static vector<string> ignoredHeaders_;

    // Add header to lists if not added yet
    void AddHeader(const string& headerFile)
    {
        if (IsIgnoredHeader(headerFile))
        {
            if (!CONTAINS(ignoredHeaders_, headerFile))
                ignoredHeaders_.push_back(headerFile);
        }
        else
        {
            if (!CONTAINS(headers_, headerFile))
                headers_.push_back(headerFile);
        }
    }

    // Write result to Generated_Includes.h
    static void SaveIncludes()
    {
        sort(headers_.begin(), headers_.end());
        sort(ignoredHeaders_.begin(), ignoredHeaders_.end());

        ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_Includes.h");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#pragma once\n"
            "\n";

        string openedDefine;
        bool isFirst = true;

        for (const string& header : headers_)
        {
            string insideDefine = InsideDefine(header);

            if (insideDefine != openedDefine)
            {
                if (!openedDefine.empty())
                {
                    ofs << "#endif\n";
                    openedDefine.clear();
                }

                if (!isFirst) // First include can be guarded. Avoid print \n before it
                    ofs << "\n";

                if (!insideDefine.empty())
                {
                    ofs << "#ifdef " << insideDefine << "\n";
                    openedDefine = insideDefine;
                }
            }

            ofs << "#include \"" << header << "\"\n";
            isFirst = false;
        }

        if (!openedDefine.empty())
        {
            ofs << "#endif\n";
            openedDefine.clear();
        }

        if (headers_.size() > 0)
            ofs << "\n";

        if (ignoredHeaders_.size() > 0)
            ofs << "// Ignored headers\n\n";

        isFirst = true;

        for (const string& header : ignoredHeaders_)
        {
            string insideDefine = InsideDefine(header);

            if (insideDefine != openedDefine)
            {
                if (!openedDefine.empty())
                {
                    ofs << "//#endif\n";
                    openedDefine.clear();
                }

                if (!isFirst) // First include can be guarded. Avoid print \n before it
                    ofs << "\n";

                if (!insideDefine.empty())
                {
                    ofs << "//#ifdef " << insideDefine << "\n";
                    openedDefine = insideDefine;
                }
            }

            ofs << "//#include \"" << header << "\"\n";
            isFirst = false;
        }

        if (!openedDefine.empty())
            ofs << "//#endif\n";
    }
}

void SaveResult()
{
    Result::SaveEnums();
    Result::SaveGlobalFunctions();
    Result::SaveGlobalVariables();
    Result::SaveClasses();
    Result::SaveIncludes();
}

}
