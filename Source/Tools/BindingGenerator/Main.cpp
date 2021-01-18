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

#include <string>

using namespace std;

//#define DEVELOP

namespace SourceData
{
    void LoadAllXmls(const string& dir);
}

namespace ASBindingGenerator
{
    void ProcessAllEnums();
    void ProcessAllClasses(const string& outputBasePath);
    void ProcessAllClassesNew();
    void ProcessAllGlobalVariables();
    void ProcessAllGlobalFunctions();
    void SaveResult(const string& outputBasePath);

    void GenerateBindings(const string& outputBasePath)
    {
        ProcessAllEnums();
        ProcessAllClasses(outputBasePath);
        ProcessAllClassesNew();
        ProcessAllGlobalVariables();
        ProcessAllGlobalFunctions();
        SaveResult(outputBasePath);
    }
}

namespace LuaBindingGenerator
{
    void GenerateBindings(const string& outputBasePath)
    {
    }
}

namespace JSBindingGenerator
{
    void GenerateBindings(const string& outputBasePath)
    {
    }
}

namespace CSBindingGenerator
{
    void GenerateBindings(const string& outputBasePath)
    {
    }
}

int main(int argc, char* argv[])
{
#ifdef DEVELOP
    string inputDir = R"(G:/MyGames/Urho3DFork2_TestOrg/Build/Source/Tools/BindingGenerator/generated/xml)";
    string outputBasePath = R"(G:/MyGames/Urho3DFork2_TestOrg/Urho3D)";
#else
    if (argc != 3)
        return -1;

    string inputDir = argv[1];
    string outputBasePath = argv[2];
#endif

    SourceData::LoadAllXmls(inputDir);

    ASBindingGenerator::GenerateBindings(outputBasePath);
    LuaBindingGenerator::GenerateBindings(outputBasePath);
    JSBindingGenerator::GenerateBindings(outputBasePath);
    CSBindingGenerator::GenerateBindings(outputBasePath);
    
    return 0;
}
