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

#include <PugiXml/pugixml.hpp>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace pugi;

namespace SourceData
{
    // All classes and structs
    extern map<string, xml_node> classes_; // id -> compounddef

    // Huge table with all members of all classes and structs
    extern map<string, xml_node> members_; // id -> memberdef

    // List of all defines. Used to detect that some function is a define
    extern vector<string> defines_;

    // Namespace Urho3D contains all needed enums and global functions
    extern xml_node namespaceUrho3D_; // compounddef from namespace_urho3_d.xml

    // Header files with @nobindfile mark at the beginning
    extern vector<string> ignoredHeaders_;

    // Init classes_, members_, defines_, namespaceUrho3D_
    void LoadAllXmls(const string& dir);
}
