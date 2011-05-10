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

std::vector<std::string> Split(const std::string& source, char separator)
{
    std::vector<std::string> ret;
    unsigned pos = 0;
    
    while (pos < source.length())
    {
        unsigned start = pos;
        
        while (start < source.length())
        {
            if (source[start] == separator)
                break;
            
            start++;
        }
        
        if (start == source.length())
        {
            ret.push_back(source.substr(pos));
            break;
        }
        
        unsigned end = start;
        
        while (end < source.length())
        {
            if (source[end] != separator)
                break;
            
            end++;
        }
        
        ret.push_back(source.substr(pos, start - pos));
        pos = end;
    }
    
    return ret;
}

std::string Replace(const std::string& source, char replaceThis, char replaceWith)
{
    std::string ret;
    ret.resize(source.length());
    
    for (unsigned i = 0; i < ret.length(); ++i)
    {
        if (source[i] == replaceThis)
            ret[i] = replaceWith;
        else
            ret[i] = source[i];
    }
    
    return ret;
}

std::string Replace(const std::string& source, const std::string& replaceThis, const std::string& replaceWith)
{
    std::string ret = source;
    ReplaceInPlace(ret, replaceThis, replaceWith);
    return ret;
}

std::string ToLower(const std::string& source)
{
    std::string ret;
    ret.resize(source.length());
    
    for (unsigned i = 0; i < ret.length(); ++i)
        ret[i] = tolower(source[i]);
    
    return ret;
}

std::string ToUpper(const std::string& source)
{
    std::string ret;
    ret.resize(source.length());
    
    for (unsigned i = 0; i < ret.length(); ++i)
        ret[i] = toupper(source[i]);
    
    return ret;
}

void ReplaceInPlace(std::string& str, char replaceThis, char replaceWith)
{
    for (unsigned i = 0; i < str.length(); ++i)
    {
        if (str[i] == replaceThis)
            str[i] = replaceWith;
    }
}

void ReplaceInPlace(std::string& str, const std::string& replaceThis, const std::string& replaceWith)
{
    size_t nextIndex = 0;
    
    while (nextIndex < str.length())
    {
        size_t index = str.find(replaceThis, nextIndex);
        if (index == std::string::npos)
            break;
        
        str.replace(index, replaceThis.length(), replaceWith);
        nextIndex = index + replaceWith.length();
    }
}

void ToLowerInPlace(std::string& str)
{
    for (unsigned i = 0; i < str.length(); ++i)
        str[i] = tolower(str[i]);
}

void ToUpperInPlace(std::string& str)
{
    for (unsigned i = 0; i < str.length(); ++i)
        str[i] = toupper(str[i]);
}

bool ToBool(const std::string& source)
{
    std::string temp = ToLower(source);
    if (temp.find("true") != std::string::npos)
        return true;
    else
        return false;
}

int ToInt(const std::string& source)
{
    if (!source.length())
        return 0;
    return atoi(source.c_str());
}

unsigned ToUInt(const std::string& source)
{
    if (!source.length())
        return 0;
    return (unsigned)atoi(source.c_str());
}

float ToFloat(const std::string& source)
{
    if (!source.length())
        return 0.0f;
    return (float)atof(source.c_str());
}

Color ToColor(const std::string& source)
{
    std::vector<std::string> colors = Split(source, ' ');
    if (colors.size() < 3)
        return Color();
    
    Color ret(ToFloat(colors[0]), ToFloat(colors[1]), ToFloat(colors[2]));
    if (colors.size() > 3)
        ret.a_ = ToFloat(colors[3]);
    
    return ret;
}

IntRect ToIntRect(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 4)
        return IntRect::ZERO;
    else
        return IntRect(ToInt(coords[0]), ToInt(coords[1]), ToInt(coords[2]), ToInt(coords[3]));
}

IntVector2 ToIntVector2(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 2)
        return IntVector2::ZERO;
    else
        return IntVector2(ToInt(coords[0]), ToInt(coords[1]));
}

Rect ToRect(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 4)
        return Rect::ZERO;
    else
        return Rect(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3]));
}

Quaternion ToQuaternion(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 3)
        return Quaternion::IDENTITY;
    else if (coords.size() < 4)
        // 3 coords specified: conversion from Euler angles
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
    else
        // 4 coords specified: full quaternion
        return Quaternion(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3])).GetNormalized();
}

Vector2 ToVector2(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 2)
        return Vector2::ZERO;
    else
        return Vector2(ToFloat(coords[0]), ToFloat(coords[1]));
}

Vector3 ToVector3(const std::string& source)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (coords.size() < 3)
        return Vector3::ZERO;
    else
        return Vector3(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]));
}

Vector4 ToVector4(const std::string& source, bool allowMissingCoords)
{
    std::vector<std::string> coords = Split(source, ' ');
    if (!allowMissingCoords)
    {
        if (coords.size() < 4)
            return Vector4::ZERO;
        
        return Vector4(ToFloat(coords[0]), ToFloat(coords[1]), ToFloat(coords[2]), ToFloat(coords[3]));
    }
    else
    {
        unsigned num = coords.size();
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

std::string ToString(bool value)
{
    if (value)
        return "true";
    else
        return "false";
}

std::string ToString(float value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g", value);
    return std::string(tempBuffer);
}

std::string ToString(int value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    return std::string(tempBuffer);
}

std::string ToString(unsigned value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    return std::string(tempBuffer);
}

std::string ToString(const Color& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.r_, value.g_, value.b_, value.a_);
    return std::string(tempBuffer);
}

std::string ToString(const IntRect& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d %d &d", value.left_, value.top_, value.right_, value.bottom_);
    return std::string(tempBuffer);
}

std::string ToString(const IntVector2& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d", value.x_, value.y_);
    return std::string(tempBuffer);
}

std::string ToString(const Rect& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.min_.x_, value.min_.y_, value.max_.x_, value.max_.y_);
    return std::string(tempBuffer);
}

std::string ToString(const Quaternion& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.w_, value.x_, value.y_, value.z_);
    return std::string(tempBuffer);
}

std::string ToString(const StringHash& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08X", value.GetValue());
    return std::string(tempBuffer);
}

std::string ToString(const ShortStringHash& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%04X", value.GetValue());
    return std::string(tempBuffer);
}

std::string ToString(const Vector2& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g", value.x_, value.y_);
    return std::string(tempBuffer);
}

std::string ToString(const Vector3& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g", value.x_, value.y_, value.z_);
    return std::string(tempBuffer);
}

std::string ToString(const Vector4& value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g %g %g %g", value.x_, value.y_, value.z_, value.w_);
    return std::string(tempBuffer);
}

std::string ToString(void* value)
{
    return ToStringHex((int)value);
}

std::string ToStringHex(unsigned value)
{
    char tempBuffer[TEMP_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08x", value);
    return std::string(tempBuffer);
}

unsigned GetStringListIndex(const std::string& value, const std::string* strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive)
{
    for (unsigned i = 0; i < count; ++i)
    {
        if (caseSensitive)
        {
            if (value == strings[i])
                return i;
        }
        else
        {
            if (ToLower(value) == ToLower(strings[i]))
                return i;
        }
    }
    
    return defaultIndex;
}
