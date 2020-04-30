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

#include "Utils.h"
#include "XmlAnalyzer.h"
#include "XmlSourceData.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>

// For GetXmlFiles()
#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

static void LoadXml(const string& fullPath)
{
    // All loaded XMLs. Not used directly, just prevents destruction
    static vector<shared_ptr<xml_document> > xmlStorage;

    // Load and store XML file
    shared_ptr<xml_document> xmlDocument = make_shared<xml_document>();
    xml_parse_result parseResult = xmlDocument->load_file(fullPath.c_str());
    assert(parseResult);
    xmlStorage.push_back(xmlDocument);

    xml_node doxygenindex = xmlDocument->child("doxygenindex");
    
    if (doxygenindex) // index.xml
    {
        // Fill defines_
        for (xml_node compound : doxygenindex.children("compound"))
        {
            for (xml_node member : compound.children("member"))
            {
                string kind = member.attribute("kind").value();

                if (kind == "define")
                {
                    string name = member.child("name").child_value();
                    SourceData::defines_.push_back(name);
                }
            }
        }

        return;
    }
    
    xml_node compounddef = xmlDocument->child("doxygen").child("compounddef");
    
    if (!compounddef)
        return;

    string kind = compounddef.attribute("kind").value();

    if (kind == "struct" || kind == "class")
    {
        // Fill classes_
        string id = compounddef.attribute("id").value();
        assert(!id.empty());
        SourceData::classes_.insert({ id, compounddef });

        // Fill members_
        for (xml_node sectiondef : compounddef.children("sectiondef"))
        {
            for (xml_node memberdef : sectiondef.children("memberdef"))
            {
                string memberKind = memberdef.attribute("kind").value();
                if (memberKind != "variable" && memberKind != "function")
                    continue;

                string memberID = memberdef.attribute("id").value();
                SourceData::members_.insert({ memberID, memberdef });
            }
        }
    }
    else if (kind == "namespace")
    {
        string compoundname = compounddef.child("compoundname").child_value();

        if (compoundname != "Urho3D")
            return;

        // Init namespaceUrho3D_
        SourceData::namespaceUrho3D_ = compounddef;
    }
    else if (kind == "file")
    {
        // Fill ignoredHeaders_
        string comment = ExtractComment(compounddef);
        if (Contains(comment, "BIND_IGNORE"))
            SourceData::ignoredHeaders_.push_back(ExtractHeaderFile(compounddef));
    }
}

static string AddTrailingSlash(const string& pathName)
{
    string ret = pathName;
    replace(ret.begin(), ret.end(), '\\', '/');
    if (!ret.empty() && ret.back() != '/')
        ret += '/';
    return ret;
}

static void GetXmlFiles(string dirPath, vector<string>& result)
{
    result.clear();
    dirPath = AddTrailingSlash(dirPath);

#ifdef _WIN32
    WIN32_FIND_DATAA findData;
    HANDLE handle = FindFirstFileA((dirPath + "*.xml").c_str(), &findData);
    if (handle == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            result.push_back(dirPath + findData.cFileName);
    } while (FindNextFileA(handle, &findData));

    FindClose(handle);
#else
    DIR* dir = opendir(dirPath.c_str());
    if (!dir)
        return;

    struct stat st;
    while (dirent* de = readdir(dir))
    {
        string filePath = dirPath + de->d_name;

        if (stat(filePath.c_str(), &st) != 0)
            continue;

        if (st.st_mode & S_IFDIR)
            continue;

        if (EndsWith(filePath, ".xml"))
            result.push_back(filePath);
    }

    closedir(dir);
#endif
}

namespace SourceData
{
    map<string, xml_node> classes_;
    xml_node namespaceUrho3D_;
    map<string, xml_node> members_;
    vector<string> defines_;
    vector<string> ignoredHeaders_;

    void LoadAllXmls(const string& dir)
    {
        cout << "Loading XMLs from " << dir << "\n";
        vector<string> fullPaths;
        GetXmlFiles(dir, fullPaths);
        cout << "Found " << fullPaths.size() << " xml files\n";

        for (string fullPath : fullPaths)
            LoadXml(fullPath);
    }
}
