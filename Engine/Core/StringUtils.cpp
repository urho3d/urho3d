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

static const int TEMP_BUFFER_LENGTH = 128;

Vector<String> Split(const String& source, char separator)
{
    Vector<String> ret;
    unsigned pos = 0;
    
    while (pos < source.Length())
    {
        unsigned start = pos;
        
        while (start < source.Length())
        {
            if (source[start] == separator)
                break;
            
            start++;
        }
        
        if (start == source.Length())
        {
            ret.Push(source.Substring(pos));
            break;
        }
        
        unsigned end = start;
        
        while (end < source.Length())
        {
            if (source[end] != separator)
                break;
            
            end++;
        }
        
        ret.Push(source.Substring(pos, start - pos));
        pos = end;
    }
    
    return ret;
}

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
    Vector<String> colors = Split(source, ' ');
    if (colors.Size() < 3)
        return Color();
    
    Color ret(ToFloat(colors[0]), ToFloat(colors[1]), ToFloat(colors[2]));
    if (colors.Size() > 3)
        ret.a_ = ToFloat(colors[3]);
    
    return ret;
}

IntRect ToIntRect(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 4)
        return IntRect::ZERO;
    else
        return IntRect(ToInt(coords[0]), ToInt(coords[1]), ToInt(coords[2]), ToInt(coords[3]));
}

IntVector2 ToIntVector2(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 2)
        return IntVector2::ZERO;
    else
        return IntVector2(ToInt(coords[0]), ToInt(coords[1]));
}

Rect ToRect(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 4)
        return Rect::ZERO;
    else
        return Rect(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3]));
}

Quaternion ToQuaternion(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 3)
        return Quaternion::IDENTITY;
    else if (coords.Size() < 4)
        // 3 coords specified: conversion from Euler angles
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
    else
        // 4 coords specified: full quaternion
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3])).GetNormalized();
}

Vector2 ToVector2(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 2)
        return Vector2::ZERO;
    else
        return Vector2(ToFloat(coords[0]), ToFloat(coords[1]));
}

Vector3 ToVector3(const String& source)
{
    Vector<String> coords = Split(source, ' ');
    if (coords.Size() < 3)
        return Vector3::ZERO;
    else
        return Vector3(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
}

Vector4 ToVector4(const String& source, bool allowMissingCoords)
{
    Vector<String> coords = Split(source, ' ');
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

String ToString(bool value)
{
    if (value)
        return "true";
    else
        return "false";
}

String ToString(float value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g", value);
    return String(tempBuffer);
}

String ToString(int value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    return String(tempBuffer);
}

String ToString(unsigned value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    return String(tempBuffer);
}

String ToString(const Color& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.r_, value.g_, value.b_, value.a_);
    return String(tempBuffer);
}

String ToString(const IntRect& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d %d &d", value.left_, value.top_, value.right_, value.bottom_);
    return String(tempBuffer);
}

String ToString(const IntVector2& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d", value.x_, value.y_);
    return String(tempBuffer);
}

String ToString(const Rect& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.min_.x_, value.min_.y_, value.max_.x_, value.max_.y_);
    return String(tempBuffer);
}

String ToString(const Quaternion& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.w_, value.x_, value.y_, value.z_);
    return String(tempBuffer);
}

String ToString(const StringHash& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08X", value.GetValue());
    return String(tempBuffer);
}

String ToString(const ShortStringHash& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%04X", value.GetValue());
    return String(tempBuffer);
}

String ToString(const Vector2& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g", value.x_, value.y_);
    return String(tempBuffer);
}

String ToString(const Vector3& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g", value.x_, value.y_, value.z_);
    return String(tempBuffer);
}

String ToString(const Vector4& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.x_, value.y_, value.z_, value.w_);
    return String(tempBuffer);
}

String ToString(void* value)
{
    return ToStringHex((int)value);
}

String ToStringHex(unsigned value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08x", value);
    return String(tempBuffer);
}

unsigned GetStringListIndex(const String& value, const String* strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive)
{
    if (caseSensitive)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            if (value == strings[i])
                return i;
        }
    }
    else
    {
        String valueLower = value.ToLower();
        for (unsigned i = 0; i < count; ++i)
        {
            /// \todo Write an insensitive compare function instead of creating new strings
            if (valueLower == strings[i].ToLower())
                return i;
        }
    }
    
    return defaultIndex;
}
