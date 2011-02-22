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
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <cstdio>
#include <cstdlib>
#include <ctype.h>

#include "DebugNew.h"

static const int TEMP_BUFFER_LENGTH = 128;
char tempBuffer[TEMP_BUFFER_LENGTH];

std::vector<std::string> split(const std::string& source, char separator)
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

std::string replace(const std::string& source, char replaceThis, char replaceWith)
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

std::string replace(const std::string& source, const std::string& replaceThis, const std::string& replaceWith)
{
    std::string ret = source;
    replaceInPlace(ret, replaceThis, replaceWith);
    return ret;
}

std::string toLower(const std::string& source)
{
    std::string ret;
    ret.resize(source.length());
    
    for (unsigned i = 0; i < ret.length(); ++i)
        ret[i] = tolower(source[i]);
    
    return ret;
}

std::string toUpper(const std::string& source)
{
    std::string ret;
    ret.resize(source.length());
    
    for (unsigned i = 0; i < ret.length(); ++i)
        ret[i] = toupper(source[i]);
    
    return ret;
}

void replaceInPlace(std::string& str, char replaceThis, char replaceWith)
{
    for (unsigned i = 0; i < str.length(); ++i)
    {
        if (str[i] == replaceThis)
            str[i] = replaceWith;
    }
}

void replaceInPlace(std::string& str, const std::string& replaceThis, const std::string& replaceWith)
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

void toLowerInPlace(std::string& str)
{
    for (unsigned i = 0; i < str.length(); ++i)
        str[i] = tolower(str[i]);
}

void toUpperInPlace(std::string& str)
{
    for (unsigned i = 0; i < str.length(); ++i)
        str[i] = toupper(str[i]);
}

bool toBool(const std::string& source)
{
    std::string temp = toLower(source);
    if (temp.find("true") != std::string::npos)
        return true;
    else
        return false;
}

int toInt(const std::string& source)
{
    if (!source.length())
        return 0;
    return atoi(source.c_str());
}

unsigned toUInt(const std::string& source)
{
    if (!source.length())
        return 0;
    return (unsigned)atoi(source.c_str());
}

float toFloat(const std::string& source)
{
    if (!source.length())
        return 0.0f;
    return (float)atof(source.c_str());
}

Color toColor(const std::string& source)
{
    std::vector<std::string> colors = split(source, ' ');
    if (colors.size() < 3)
        return Color();
    
    Color ret(toFloat(colors[0]), toFloat(colors[1]), toFloat(colors[2]));
    if (colors.size() > 3)
        ret.mA = toFloat(colors[3]);
    
    return ret;
}

IntRect toIntRect(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 4)
        return IntRect::sZero;
    else
        return IntRect(toInt(coords[0]), toInt(coords[1]), toInt(coords[2]), toInt(coords[3]));
}

IntVector2 toIntVector2(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 2)
        return IntVector2::sZero;
    else
        return IntVector2(toInt(coords[0]), toInt(coords[1]));
}

Rect toRect(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 4)
        return Rect::sZero;
    else
        return Rect(toFloat(coords[0]), toFloat(coords[1]), toFloat(coords[2]), toFloat(coords[3]));
}

Quaternion toQuaternion(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 3)
        return Quaternion::sIdentity;
    else if (coords.size() < 4)
        // 3 coords specified: conversion from Euler angles
        return Quaternion(toFloat(coords[0]), toFloat(coords[1]), toFloat(coords[2]));
    else
        // 4 coords specified: full quaternion
        return Quaternion(toFloat(coords[0]), toFloat(coords[1]), toFloat(coords[2]), toFloat(coords[3])).getNormalized();
}

Vector2 toVector2(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 2)
        return Vector2::sZero;
    else
        return Vector2(toFloat(coords[0]), toFloat(coords[1]));
}

Vector3 toVector3(const std::string& source)
{
    std::vector<std::string> coords = split(source, ' ');
    if (coords.size() < 3)
        return Vector3::sZero;
    else
        return Vector3(toFloat(coords[0]), toFloat(coords[1]), toFloat(coords[2]));
}

Vector4 toVector4(const std::string& source, bool allowMissingCoords)
{
    std::vector<std::string> coords = split(source, ' ');
    if (!allowMissingCoords)
    {
        if (coords.size() < 4)
            return Vector4::sZero;
        
        return Vector4(toFloat(coords[0]), toFloat(coords[1]), toFloat(coords[2]), toFloat(coords[3]));
    }
    else
    {
        unsigned num = coords.size();
        Vector4 ret(Vector4::sZero);
        if (num > 0)
            ret.mX = toFloat(coords[0]);
        if (num > 1)
            ret.mY = toFloat(coords[1]);
        if (num > 2)
            ret.mZ = toFloat(coords[2]);
        if (num > 3)
            ret.mW = toFloat(coords[3]);
        return ret;
    }
}

std::string toString(bool value)
{
    if (value)
        return "true";
    else
        return "false";
}

std::string toString(float value)
{
    sprintf(tempBuffer, "%g", value);
    
    return std::string(tempBuffer);
}

std::string toString(int value)
{
    sprintf(tempBuffer, "%d", value);
    
    return std::string(tempBuffer);
}

std::string toString(unsigned value)
{
    sprintf(tempBuffer, "%u", value);
    
    return std::string(tempBuffer);
}

std::string toString(const Color& value)
{
    sprintf(tempBuffer, "%g %g %g %g", value.mR, value.mG, value.mB, value.mA);
    
    return std::string(tempBuffer);
}

std::string toString(const IntRect& value)
{
    sprintf(tempBuffer, "%d %d %d &d", value.mLeft, value.mTop, value.mRight, value.mBottom);
    
    return std::string(tempBuffer);
}

std::string toString(const IntVector2& value)
{
    sprintf(tempBuffer, "%d %d", value.mX, value.mY);
    
    return std::string(tempBuffer);
}

std::string toString(const Rect& value)
{
    sprintf(tempBuffer, "%g %g %g %g", value.mMin.mX, value.mMin.mY, value.mMax.mX, value.mMax.mY);
    
    return std::string(tempBuffer);
}

std::string toString(const Quaternion& value)
{
    sprintf(tempBuffer, "%g %g %g %g", value.mW, value.mX, value.mY, value.mZ);
    
    return std::string(tempBuffer);
}

std::string toString(const StringHash& value)
{
    const std::string& str = hashToString(value);
    
    // Return reverse-mapped string if possible
    if (str.empty())
    {
        sprintf(tempBuffer, "%08X", value.mData);
        return std::string(tempBuffer);
    }
    else
        return str;
}

std::string toString(const ShortStringHash& value)
{
    const std::string& str = shortHashToString(value);
    
    // Return reverse-mapped string if possible
    if (str.empty())
    {
        sprintf(tempBuffer, "%04X", value.mData);
        return std::string(tempBuffer);
    }
    else
        return str;
}

std::string toString(const Vector2& value)
{
    sprintf(tempBuffer, "%g %g", value.mX, value.mY);
    
    return std::string(tempBuffer);
}

std::string toString(const Vector3& value)
{
    sprintf(tempBuffer, "%g %g %g", value.mX, value.mY, value.mZ);
    
    return std::string(tempBuffer);
}

std::string toString(const Vector4& value)
{
    sprintf(tempBuffer, "%g %g %g %g", value.mX, value.mY, value.mZ, value.mW);
    
    return std::string(tempBuffer);
}

std::string toStringHex(int value)
{
    sprintf(tempBuffer, "%08x", value);
    
    return std::string(tempBuffer);
}

unsigned getIndexFromStringList(const std::string& value, const std::string* strings, unsigned count, unsigned defaultIndex,
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
            if (toLower(value) == toLower(strings[i]))
                return i;
        }
    }
    
    return defaultIndex;
}
