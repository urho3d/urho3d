// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <chrono>
#include <iostream>
#include <string>

using namespace std;

//#define DEVELOP

// Path to Urho3D's root folder (CMAKE_SOURCE_DIR). There must be no slash at the end
string _sourceDir;

namespace SourceData
{
    void LoadAllXmls(const string& dir);
}

namespace ASBindingGenerator
{
    void ProcessAllEnums();
    void ProcessAllClasses();
    void ProcessAllGlobalVariables();
    void ProcessAllGlobalFunctions();
    void SaveResult();

    void GenerateTemplates();

    void GenerateBindings()
    {
        ProcessAllEnums();
        ProcessAllClasses();
        ProcessAllGlobalVariables();
        ProcessAllGlobalFunctions();
        SaveResult();

        GenerateTemplates();
    }
}

namespace LuaBindingGenerator
{
    void GenerateBindings()
    {
    }
}

namespace JSBindingGenerator
{
    void GenerateBindings()
    {
    }
}

namespace CSBindingGenerator
{
    void GenerateBindings()
    {
    }
}

int main(int argc, char* argv[])
{
#ifdef DEVELOP
    string inputDir = R"(G:/MyGames/Urho3DFork/Build/Source/Tools/BindingGenerator/generated/xml)";
    _sourceDir = R"(G:/MyGames/Urho3DFork/Urho3D)";
#else
    if (argc != 3)
        return -1;

    string inputDir = argv[1];
    _sourceDir = argv[2];
#endif

    auto start = chrono::high_resolution_clock::now();
    SourceData::LoadAllXmls(inputDir);
    auto end = chrono::high_resolution_clock::now();
    cout << "Loaded in " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    start = chrono::high_resolution_clock::now();
    ASBindingGenerator::GenerateBindings();
    end = chrono::high_resolution_clock::now();
    cout << "Generated in " << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    LuaBindingGenerator::GenerateBindings();
    JSBindingGenerator::GenerateBindings();
    CSBindingGenerator::GenerateBindings();
    
    return 0;
}
