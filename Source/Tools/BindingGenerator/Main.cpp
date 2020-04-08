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

#include "XmlSourceData.h"

//#define DEVELOP

void GenerateASBindings(const string& outputPath);
//GenerateLuaBindings(const string& outputPath);
//GenerateJSBindings(const string& outputPath);
//GenerateCSBindings(const string& outputPath);

int main(int argc, char* argv[])
{
#ifdef DEVELOP
    string inputDir = R"(D:/MyGames/Urho3DFork/Build/Source/Tools/BindingGenerator/generated/xml)";
    string outputBasePath = R"(D:/MyGames/Urho3DFork/Urho3D)";
#else
    if (argc != 3)
        return -1;

    string inputDir = argv[1];
    string outputBasePath = argv[2];
#endif

    SourceData::LoadAllXmls(inputDir);

    GenerateASBindings(outputBasePath + "/Source/Urho3D/AngelScript/Generated.cpp");
    //GenerateLuaBindings(outputBasePath + "/Source/Urho3D/Lua/Generated.cpp");
    //GenerateJSBindings(outputBasePath + "/Source/Urho3D/JavaScript/Generated.cpp");
    //GenerateCSBindings(outputBasePath + "/Source/Urho3D/CSharp/Generated.cpp");
    
    return 0;
}
