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

#pragma once

#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace ASBindingGenerator
{

class ASGeneratedFile_Base
{
protected:
    // Result file path
    string outputFilePath_;

public:
    // Wrappers
    stringstream glue_;

    // Registration function body
    stringstream reg_;

    // Write result to file
    virtual void Save() {};
};

class ASGeneratedFile_WithRegistrationFunction : public ASGeneratedFile_Base
{
protected:
    // Registration function name
    string functionName_;

public:
    ASGeneratedFile_WithRegistrationFunction(const string& outputFilePath, const string& functionName);
};

class ASGeneratedFile_Classes : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_Members_HighPriority : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_Members : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_GlobalVariables : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_GlobalFunctions : public ASGeneratedFile_WithRegistrationFunction
{
public:
    using ASGeneratedFile_WithRegistrationFunction::ASGeneratedFile_WithRegistrationFunction;

    void Save() override;
};

class ASGeneratedFile_Templates : public ASGeneratedFile_Base
{

public:
    ASGeneratedFile_Templates(const string& outputFilePath);

    // Write result to file
    void Save() override;
};

struct ProcessedEnum
{
    // Used for alphabetical sorting
    string name_;

    string comment_;
    vector<string> glue_; // Can be empty
    string insideDefine_; // Can be empty
    vector<string> registration_;

    // Used for alphabetical sorting
    bool operator <(const ProcessedEnum& rhs) const;
};

namespace Result
{
    extern vector<ProcessedEnum> enums_;

    // Add header to lists if not added yet
    void AddHeader(const string& headerFile);
}

} // namespace ASBindingGenerator
