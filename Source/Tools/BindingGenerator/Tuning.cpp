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

// Functions that users can change to affect the work BindingGenerator

#include "XmlSourceData.h"
#include "Tuning.h"
#include "Utils.h"

// Some parts of the engine are compiled only if there are defines
string InsideDefine(const string& headerFile)
{
    string dir = WithoutFileName(headerFile);

    if (dir == "../Network")
        return "URHO3D_NETWORK";

    if (dir == "../Database")
        return "URHO3D_DATABASE";

    if (dir == "../IK")
        return "URHO3D_IK";

    if (dir == "../Physics")
        return "URHO3D_PHYSICS";

    if (dir == "../Navigation")
        return "URHO3D_NAVIGATION";

    if (dir == "../Urho2D")
        return "URHO3D_URHO2D";

    return string();
}

// Users can prevent the automatic creation of bindings for certain files and dirs
bool IsIgnoredHeader(const string& headerFile)
{
    static vector<string> ignoredDirs = {
        "../AngelScript",
        //"../Container",
        "../LuaScript",
        "../Graphics/Direct3D11",
        "../Graphics/Direct3D9",
        "../Graphics/OpenGL",
        "../Database/ODBC",
        "../Database/SQLite",
    };

    static vector<string> ignoredHeaders = {
        //"../Graphics/Drawable.h",
    };

    if (CONTAINS(SourceData::ignoredHeaders_, headerFile))
        return true;

    if (CONTAINS(ignoredHeaders, headerFile))
        return true;

    string dir = WithoutFileName(headerFile);
    if (CONTAINS(ignoredDirs, dir))
        return true;

    return false;
}
