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

void ASGeneratedFile_Base::AddHeader(const string& headerFile)
{
    if (!CONTAINS(headers_, headerFile))
        headers_.push_back(headerFile);
}

void ASGeneratedFile_Base::AddIgnoredHeader(const string& headerFile)
{
    if (!CONTAINS(ignoredHeaders_, headerFile))
        ignoredHeaders_.push_back(headerFile);
}

void ASGeneratedFile_Base::WriteHeaders(ofstream& out)
{
    sort(ignoredHeaders_.begin(), ignoredHeaders_.end());
    sort(headers_.begin(), headers_.end());

    if (ignoredHeaders_.size() > 0)
    {
        out << "// Ignored headers\n";

        for (string header : ignoredHeaders_)
        {
            string insideDefine = InsideDefine(header);
            if (!insideDefine.empty())
                out << "//#ifdef " << insideDefine << "\n";

            out << "//#include \"" << header << "\"\n";

            if (!insideDefine.empty())
                out << "//#endif\n";
        }

        out << "\n";
    }

    for (string header : headers_)
    {
        string insideDefine = InsideDefine(header);
        if (!insideDefine.empty())
            out << "#ifdef " << insideDefine << "\n";

        out << "#include \"" << header << "\"\n";

        if (!insideDefine.empty())
            out << "#endif\n";
    }

    if (headers_.size() > 0)
        out << "\n";
}

// ============================================================================

ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction(const string& outputFilePath, const string& functionName)
{
    outputFilePath_ = outputFilePath;
    functionName_ = functionName;
}

// ============================================================================

void ASGeneratedFile_Enums::Save()
{
    ofstream out(outputFilePath_);

    out <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "// We need register all enums before registration of any members because members can use any enums\n"
        "\n"
        "#include \"../Precompiled.h\"\n"
        "#include \"../AngelScript/APITemplates.h\"\n"
        "\n";

    WriteHeaders(out);

    out <<
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
        "\n";

    WriteHeaders(out);

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
        "\n";

    WriteHeaders(out);

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
        "\n";

    WriteHeaders(out);

    out <<
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
        "\n";

    WriteHeaders(out);

    out <<
        "// Some headers could re-define M_PI, ensure that it's undefined\n"
        "#undef M_PI\n"
        "\n";

    out <<
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
        "\n";

    WriteHeaders(out);

    out <<
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
        "\n";

    WriteHeaders(out);

    out <<
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

}
