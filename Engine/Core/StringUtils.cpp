//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "StringUtils.h"

#include <cstdio>
#include <ctype.h>

#include "DebugNew.h"

bool ToBool(const String& source)
{
    String temp = source.ToLower();
    if (temp.Find("true") != String::NPOS)
        return true;
    else
        return false;
}

int ToInt(const String& source)
{
    if (!source.Length())
        return 0;
    return atoi(source.CString());
}

unsigned ToUInt(const String& source)
{
    if (!source.Length())
        return 0;
    return (unsigned)atoi(source.CString());
}

float ToFloat(const String& source)
{
    if (!source.Length())
        return 0.0f;
    return (float)atof(source.CString());
}

Color ToColor(const String& source)
{
    Vector<String> colors = source.Split(' ');
    if (colors.Size() < 3)
        return Color();
    
    Color ret(ToFloat(colors[0]), ToFloat(colors[1]), ToFloat(colors[2]));
    if (colors.Size() > 3)
        ret.a_ = ToFloat(colors[3]);
    
    return ret;
}

IntRect ToIntRect(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 4)
        return IntRect::ZERO;
    else
        return IntRect(ToInt(coords[0]), ToInt(coords[1]), ToInt(coords[2]), ToInt(coords[3]));
}

IntVector2 ToIntVector2(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 2)
        return IntVector2::ZERO;
    else
        return IntVector2(ToInt(coords[0]), ToInt(coords[1]));
}

Rect ToRect(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 4)
        return Rect::ZERO;
    else
        return Rect(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3]));
}

Quaternion ToQuaternion(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 3)
        return Quaternion::IDENTITY;
    else if (coords.Size() < 4)
        // 3 coords specified: conversion from Euler angles
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
    else
        // 4 coords specified: full quaternion
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3])).Normalized();
}

Vector2 ToVector2(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 2)
        return Vector2::ZERO;
    else
        return Vector2(ToFloat(coords[0]), ToFloat(coords[1]));
}

Vector3 ToVector3(const String& source)
{
    Vector<String> coords = source.Split(' ');
    if (coords.Size() < 3)
        return Vector3::ZERO;
    else
        return Vector3(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
}

Vector4 ToVector4(const String& source, bool allowMissingCoords)
{
    Vector<String> coords = source.Split(' ');
    if (!allowMissingCoords)
    {
        if (coords.Size() < 4)
            return Vector4::ZERO;
        
        return Vector4(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3]));
    }
    else
    {
        unsigned num = coords.Size();
        Vector4 ret(Vector4::ZERO);
        if (num > 0)
            ret.x_ = ToFloat(coords[0]);
        if (num > 1)
            ret.y_ = ToFloat(coords[1]);
        if (num > 2)
            ret.z_ = ToFloat(coords[2]);
        if (num > 3)
            ret.w_ = ToFloat(coords[3]);
        return ret;
    }
}

String ToString(void* value)
{
    return ToStringHex((int)value);
}

String ToStringHex(unsigned value)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08x", value);
    return String(tempBuffer);
}

unsigned GetStringListIndex(const String& value, const String* strings, unsigned defaultIndex, bool caseSensitive)
{
    unsigned i = 0;
    
    if (caseSensitive)
    {
        while (!strings[i].Empty())
        {
            if (value == strings[i])
                return i;
            ++i;
        }
    }
    else
    {
        String valueLower = value.ToLower();
        while (!strings[i].Empty())
        {
            /// \todo Write an insensitive compare function instead of creating new strings
            if (valueLower == strings[i].ToLower())
                return i;
            ++i;
        }
    }
    
    return defaultIndex;
}
