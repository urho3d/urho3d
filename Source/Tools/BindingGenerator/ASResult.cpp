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
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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
    if (insideDefine_ != rhs.insideDefine_)
        return insideDefine_ < rhs.insideDefine_;

    return name_ < rhs.name_;
}

namespace Result
{
    vector<ProcessedEnum> enums_;

    // Write result to GeneratedEnums.cpp
    static void SaveEnums(const string& outputBasePath)
    {
        sort(enums_.begin(), enums_.end());

        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedEnums.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register all enums before registration of any functions because functions can use any enums\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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

    // Write result to GlobalFunctions.cpp
    static void SaveGlobalFunctions(const string& outputBasePath)
    {
        sort(globalFunctions_.begin(), globalFunctions_.end());

        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedGlobalFunctions.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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

    // Write result to GlobalVariables.cpp
    static void SaveGlobalVariables(const string& outputBasePath)
    {
        sort(globalVariables_.begin(), globalVariables_.end());

        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedGlobalVariables.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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

    // Write result to GeneratedObjectTypes.cpp
    static void SaveObjectTypes(const string& outputBasePath)
    {
        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedObjectTypes.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register all types before registration of any functions because functions can use any types\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
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

    // Write result to GeneratedDefaultConstructors.cpp
    static void SaveDefaultConstructors(const string& outputBasePath)
    {
        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedDefaultConstructors.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register default constructors before any members to allow using in Array<type>\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n";

        string openedDefine;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (!processedClass.defaultConstructor_)
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

    // Write result to GeneratedClasses.cpp
    static void SaveGeneratedClasses(const string& outputBasePath)
    {
        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedClasses.cpp");

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
            "#include \"../AngelScript/GeneratedClassMembers.h\"\n"
            "#include \"../AngelScript/Manual.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void FakeAddRef(void* ptr);\n"
            "void FakeReleaseRef(void* ptr);\n";

        string openedDefine;
        
        for (const ProcessedClass& processedClass : classes_)
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

            if (processedClass.destructor_)
            {
                ofs <<
                    "// " << processedClass.destructor_->comment_ << "\n"
                    << processedClass.destructor_->glue_ <<
                    "\n";
            }

            ofs <<
                "// " << processedClass.comment_ << "\n"
                "static void Register_" << processedClass.name_ << "(asIScriptEngine* engine)\n"
                "{\n";

            bool needGap = false;

            /*
            for (string nonDefaultConstructor : processedClass.nonDefaultConstructors_)
                ofs << "    // " << nonDefaultConstructor << "\n";
                */

            if (processedClass.destructor_)
            {
                ofs <<
                    "    // " << processedClass.destructor_->comment_ << "\n"
                    "    " << processedClass.destructor_->registration_ << "\n";
                
                needGap = true;
            }

            if (needGap)
                ofs << '\n';

            ofs <<
                "    Vector<RegisterObjectMethodArgs> methods;\n"
                "    CollectMembers_" << processedClass.name_ << "(methods);\n"
                "    const char* asClassName = \"" << processedClass.name_ << "\";\n"
                "    //for (const RegisterObjectMethodArgs& method : methods)\n"
                "    //    engine->RegisterObjectMethod(asClassName, method.declaration_.CString(), method.funcPointer_, method.callConv_);\n";

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

    // Write result to GeneratedClassMembers.cpp and GeneratedClassMembers.h
    static void SaveClassMembers(const string& outputBasePath)
    {
        ofstream ofsCpp(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedClassMembers.cpp");

        ofsCpp <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
            "#include \"../AngelScript/GeneratedClassMembers.h\"\n"
            "#include \"../AngelScript/Manual.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void FakeAddRef(void* ptr);\n"
            "void FakeReleaseRef(void* ptr);\n";

        string openedDefine;

        for (const ProcessedClass& processedClass : classes_)
        {
            if (processedClass.insideDefine_ != openedDefine && !openedDefine.empty())
            {
                ofsCpp <<
                    "\n"
                    "#endif // def " << openedDefine << "\n";

                openedDefine.clear();
            }

            if (processedClass.insideDefine_ != openedDefine && !processedClass.insideDefine_.empty())
            {
                ofsCpp <<
                    "\n"
                    "#ifdef " << processedClass.insideDefine_ << "\n";

                openedDefine = processedClass.insideDefine_;
            }

            /*for (const ClassMethodRegistration& method : processedClass.methods_)
            {
                if (!method.glue_.empty())
                {
                    ofsCpp <<
                        "\n"
                        "// " << method.cppDeclaration_ << "\n"
                        << method.glue_;
                }
            }*/

            ofsCpp <<
                "\n"
                "// " << processedClass.comment_ << "\n"
                "void CollectMembers_" << processedClass.name_ << "(Vector<RegisterObjectMethodArgs>& methods)\n"
                "{\n";

            bool needGap = false;

            /*for (const RegistrationError& unregisteredMethod : processedClass.unregisteredMethods_)
            {
                if (needGap)
                    ofsCpp << '\n';

                ofsCpp <<
                    "    // " << unregisteredMethod.cppDeclaration_ << "\n"
                    "    // " << unregisteredMethod.message_ << "\n";

                needGap = true;
            }*/

            if (processedClass.baseClassNames_.size())
            {
                if (needGap)
                    ofsCpp << '\n';

                for (const string& baseClassName : processedClass.baseClassNames_)
                    ofsCpp << "    CollectMembers_" << baseClassName << "(methods);\n";

                needGap = true;
            }

            /*for (const ClassMethodRegistration& method : processedClass.methods_)
            {
                if (needGap)
                    ofsCpp << '\n';

                const RegisterObjectMethodArgs& args = method.registration_;

                ofsCpp <<
                    "    // " << method.cppDeclaration_ << "\n"
                    "    methods.Push(RegisterObjectMethodArgs(\"" << args.declaration_ << "\", " << args.funcPointer_ << ", " << args.callConv_ << "));\n";

                needGap = true;
            }*/

            ofsCpp << "}\n";
        }

        if (!openedDefine.empty())
        {
            ofsCpp <<
                "\n"
                "#endif // def " << openedDefine << "\n";

            openedDefine.clear();
        }

        ofsCpp <<
            "\n"
            "} // namespace Urho3D\n";

        ofstream ofsH(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedClassMembers.h");

        ofsH <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#pragma once\n"
            "\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n";

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

            ofsH <<
                "\n"
                "// " << processedClass.comment_ << "\n"
                "void CollectMembers_" << processedClass.name_ << "(Vector<RegisterObjectMethodArgs>& methods);\n";
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

    static void SaveClasses(const string& outputBasePath)
    {
        sort(classes_.begin(), classes_.end());
        SaveObjectTypes(outputBasePath);
        SaveDefaultConstructors(outputBasePath);
        SaveGeneratedClasses(outputBasePath);
        SaveClassMembers(outputBasePath);
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

    // Write result to GeneratedIncludes.h
    static void SaveIncludes(const string& outputBasePath)
    {
        sort(headers_.begin(), headers_.end());
        sort(ignoredHeaders_.begin(), ignoredHeaders_.end());

        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedIncludes.h");

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

void SaveResult(const string& outputBasePath)
{
    Result::SaveEnums(outputBasePath);
    Result::SaveGlobalFunctions(outputBasePath);
    Result::SaveGlobalVariables(outputBasePath);
    Result::SaveClasses(outputBasePath);
    Result::SaveIncludes(outputBasePath);
}

}
