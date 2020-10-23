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

void ASGeneratedFile_Classes::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "// We need register all types before registration of any members because members can use any types\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
        "\n";

    out <<
        "namespace Urho3D\n"
        "{\n"
        "\n"
        "void " << functionName_ << "(asIScriptEngine* engine)\n"
        "{\n"
        << reg_.str() <<
        "}\n"
        "\n"
        "}\n";
}

// ============================================================================

void ASGeneratedFile_Members_HighPriority::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "// We need register default constructors before any members to allow using in Array<type>\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
        "\n";

    out <<
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

void ASGeneratedFile_GlobalVariables::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
        "\n"
        "// Some headers could re-define M_PI, ensure that it's undefined\n"
        "#undef M_PI\n"
        "\n"
        "namespace Urho3D\n"
        "{\n"
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

void ASGeneratedFile_GlobalFunctions::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "#include \"../AngelScript/GeneratedIncludes.h\"\n"
        "#include \"../AngelScript/GeneratedGlue.h\"\n"
        "\n";

    out <<
        "namespace Urho3D\n"
        "{\n"
        "\n"
        //<< glue_.str() <<
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

// ============================================================================

namespace ResultIncludes
{
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

    // Write result to file
    void Save(const string& outputBasePath)
    {
        ofstream ofsIncludes(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedIncludes.h");
        sort(headers_.begin(), headers_.end());
        sort(ignoredHeaders_.begin(), ignoredHeaders_.end());

        ofsIncludes <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#pragma once\n"
            "\n";

        for (const string& header : headers_)
        {
            string insideDefine = InsideDefine(header);
            if (!insideDefine.empty())
                ofsIncludes << "#ifdef " << insideDefine << "\n";

            ofsIncludes << "#include \"" << header << "\"\n";

            if (!insideDefine.empty())
                ofsIncludes << "#endif\n";
        }

        if (headers_.size() > 0)
            ofsIncludes << "\n";

        if (ignoredHeaders_.size() > 0)
            ofsIncludes << "// Ignored headers\n";

        for (string header : ignoredHeaders_)
        {
            string insideDefine = InsideDefine(header);
            if (!insideDefine.empty())
                ofsIncludes << "//#ifdef " << insideDefine << "\n";

            ofsIncludes << "//#include \"" << header << "\"\n";

            if (!insideDefine.empty())
                ofsIncludes << "//#endif\n";
        }
    }
}

namespace ResultEnums
{
    // List of all required header files
    static vector<string> headers_;

    // Consts
    stringstream glue_;

    // Registration function body
    stringstream reg_;

    // Add header to list if not added yet
    void AddHeader(const string& headerFile)
    {
        if (!CONTAINS(headers_, headerFile))
            headers_.push_back(headerFile);
    }

    // Write result to file
    void Save(const string& outputBasePath)
    {
        ofstream ofs(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedEnums.cpp");
        sort(headers_.begin(), headers_.end());

        ofs <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "// We need register all enums before registration of any members because members can use any enums\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "\n";

        for (const string& header : headers_)
        {
            string insideDefine = InsideDefine(header);

            if (!insideDefine.empty())
                ofs << "#ifdef " << insideDefine << "\n";

            ofs << "#include \"" << header << "\"\n";

            if (!insideDefine.empty())
                ofs << "#endif\n";
        }

        if (headers_.size() > 0)
            ofs << "\n";

        ofs <<
            "namespace Urho3D\n"
            "{\n"
            "\n"
            << glue_.str() <<
            "void ASRegisterGenerated_Enums(asIScriptEngine* engine)\n"
            "{\n"
            << reg_.str() <<
            "}\n"
            "\n"
            "}\n";
    }
}

namespace Result
{
    // GeneratedGlue.h
    stringstream glueH_;

    // GeneratedGlue.cpp
    stringstream glueCpp_;

    // Write result to files
    void Save(const string& outputBasePath)
    {
        ofstream ofsGlueH(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedGlue.h");

        ofsGlueH <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#pragma once\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            << glueH_.str() <<
            "\n"
            "}\n";

        ofstream ofsGlueCpp(outputBasePath + "/Source/Urho3D/AngelScript/GeneratedGlue.cpp");

        ofsGlueCpp <<
            "// DO NOT EDIT. This file is generated\n"
            "\n"
            "#include \"../Precompiled.h\"\n"
            "\n"
            "#include \"../AngelScript/APITemplates.h\"\n"
            "#include \"../AngelScript/GeneratedIncludes.h\"\n"
            "\n"
            "namespace Urho3D\n"
            "{\n"
            "\n"
            "void FakeAddRef(void* ptr);\n"
            "void FakeReleaseRef(void* ptr);\n"
            "\n"
            << glueCpp_.str() <<
            "}\n";
    }
}

void SaveResult(const string& outputBasePath)
{
    ResultIncludes::Save(outputBasePath);
    ResultEnums::Save(outputBasePath);
    Result::Save(outputBasePath);
}

}
