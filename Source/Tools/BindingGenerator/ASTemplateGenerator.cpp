// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
