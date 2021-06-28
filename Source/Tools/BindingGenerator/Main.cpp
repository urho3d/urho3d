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
