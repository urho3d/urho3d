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

#include "ASUtils.h"
#include "Utils.h"
#include "XmlAnalyzer.h"

#include <cassert>

string SimpleCppTypeToAS(const string& cppType)
{
    if (cppType == "char")
        return "int8";

    if (cppType == "unsigned char")
        return "uint8";

    if (cppType == "short")
        return "int16";

    if (cppType == "unsigned short")
        return "uint16";

    if (cppType == "unsigned")
        return "uint";

    if (cppType == "SDL_JoystickID")
        return "int";

    if (EndsWith(cppType, "Flags"))
        return "uint";

    return cppType;
}

string CppTypeToAS(TypeAnalyzer type, bool returnType)
{
    if (type.IsConst() && type.IsReference() && !returnType)
        return "const " + SimpleCppTypeToAS(type.GetName()) + "&in";

    string result = SimpleCppTypeToAS(type.GetName());

    if (type.IsReference())
        result += "&";
    else if (type.IsPointer())
        result += "@+";

    if (returnType && type.IsConst())
        result = "const " + result;

    return result;
}
