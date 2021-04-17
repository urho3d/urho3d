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

#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

extern string _sourceDir;

namespace ASBindingGenerator
{

// Generate templates for up to this number of function parameters
const int MAX_PARAMS = 8;

void WriteConstructors(ofstream& ofs)
{
    ofs <<
        "// Constructors that don't require parameter conversion between C++ and AngelScript\n"
        "\n"
        "#ifdef AS_MAX_PORTABILITY\n"
        "\n";

    for (int numParams = 0; numParams <= MAX_PARAMS; numParams++)
    {
        ofs << "template <class C";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
            ofs << ", typename P" << paramIndex;

        ofs <<
            ">\n"
            "void ASCompatibleConstructor(asIScriptGeneric* gen)\n"
            "{\n"
            "    new (gen->GetObject()) C("; // Placement new

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
        {
            if (paramIndex != 0)
                ofs << ",\n                             ";

            ofs << "*reinterpret_cast<P" << paramIndex << "*>(gen->GetAddressOfArg(" << paramIndex << "))";
        }

        ofs <<
            ");\n"
            "}\n"
            "\n";
    }

    ofs <<
        "#else\n"
        "\n";

    for (int numParams = 0; numParams <= MAX_PARAMS; numParams++)
    {
        ofs << "template <class C";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
            ofs << ", typename P" << paramIndex;

        ofs <<
            ">\n"
            "void ASCompatibleConstructor(C* ptr";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
            ofs << ", P" << paramIndex << " p" << paramIndex;

        ofs <<
            ")\n"
            "{\n"
            "    new (ptr) C("; // Placement new

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
        {
            if (paramIndex != 0)
                ofs << ", ";

            ofs << "p" << paramIndex;
        }

        ofs <<
            ");\n"
            "}\n"
            "\n";
    }

    ofs <<
        "#endif\n"
        "\n";
}

void WriteFactories(ofstream& ofs)
{
    ofs <<
        "// Factories that don't require parameter conversion between C++ and AngelScript\n"
        "\n"
        "#ifdef AS_MAX_PORTABILITY\n"
        "\n";

    for (int numParams = 0; numParams <= MAX_PARAMS; numParams++)
    {
        ofs << "template <class C";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
            ofs << ", typename P" << paramIndex;

        ofs <<
            ">\n"
            "void ASCompatibleFactory(asIScriptGeneric* gen)\n"
            "{\n"
            "    gen->SetReturnAddress(new C(";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
        {
            if (paramIndex != 0)
                ofs << ",\n                                ";

            ofs << "*reinterpret_cast<P" << paramIndex << "*>(gen->GetAddressOfArg(" << paramIndex << "))";
        }

        ofs <<
            "));\n"
            "}\n"
            "\n";
    }

    ofs <<
        "#else\n"
        "\n";

    for (int numParams = 0; numParams <= MAX_PARAMS; numParams++)
    {
        ofs << "template <class C";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
            ofs << ", typename P" << paramIndex;

        ofs <<
            ">\n"
            "C* ASCompatibleFactory(";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
        {
            if (paramIndex != 0)
                ofs << ", ";

            ofs << "P" << paramIndex << " p" << paramIndex;
        }

        ofs <<
            ")\n"
            "{\n"
            "    return new C(";

        for (int paramIndex = 0; paramIndex < numParams; paramIndex++)
        {
            if (paramIndex != 0)
                ofs << ", ";

            ofs << "p" << paramIndex;
        }

        ofs <<
            ");\n"
            "}\n"
            "\n";
    }

    ofs <<
        "#endif\n"
        "\n";
}

void GenerateTemplates()
{
    ofstream ofs(_sourceDir + "/Source/Urho3D/AngelScript/Generated_Templates.h");

    ofs <<
        "// DO NOT EDIT. This file is generated\n"
        "\n"
        "#pragma once\n"
        "\n"
        "#include <AngelScript/angelscript.h>\n"
        "\n"
        "#include <new>\n"
        "\n"
        "namespace Urho3D\n"
        "{\n"
        "\n";
 
    WriteConstructors(ofs);
    WriteFactories(ofs);

    ofs << "} // namespace Urho3D\n";
}

} // ASBindingGenerator
