//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "DebugNew.h"

namespace Urho3D
{

unsigned CountElements(const char* buffer, char separator)
{
    if (!buffer)
        return 0;
    
    const char* endPos = buffer + String::CStringLength(buffer);
    const char* pos = buffer;
    unsigned ret = 0;
    
    while (pos < endPos)
    {
        if (*pos != separator)
            break;
        ++pos;
    }
    
    while (pos < endPos)
    {
        const char* start = pos;
        
        while (start < endPos)
        {
            if (*start == separator)
                break;
            
            ++start;
        }
        
        if (start == endPos)
        {
            ++ret;
            break;
        }
        
        const char* end = start;
        
        while (end < endPos)
        {
            if (*end != separator)
                break;
            
            ++end;
        }
        
        ++ret;
        pos = end;
    }
    
    return ret;
}

bool ToBool(const String& source)
{
    return ToBool(source.CString());
}

bool ToBool(const char* source)
{
    unsigned length = String::CStringLength(source);
    
    for (unsigned i = 0; i < length; ++i)
    {
        char c = tolower(source[i]);
        if (c == 't' || c == 'y' || c == '1')
            return true;
        else if (c != ' ' && c != '\t')
            break;
    }
    
    return false;
}

int ToInt(const String& source)
{
    return ToInt(source.CString());
}

int ToInt(const char* source)
{
    if (!source)
        return 0;
    
    // Explicitly ask for base 10 to prevent source starts with '0' or '0x' from being converted to base 8 or base 16, respectively
    return strtol(source, 0, 10);
}

unsigned ToUInt(const String& source)
{
    return ToUInt(source.CString());
}

unsigned ToUInt(const char* source)
{
    if (!source)
        return 0;
    
    return strtoul(source, 0, 10);
}

float ToFloat(const String& source)
{
    return ToFloat(source.CString());
}

float ToFloat(const char* source)
{
    if (!source)
        return 0;
    
    return (float)strtod(source, 0);
}

Color ToColor(const String& source)
{
    return ToColor(source.CString());
}

Color ToColor(const char* source)
{
    Color ret;
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 3)
        return ret;
    
    char* ptr = (char*)source;
    ret.r_ = (float)strtod(ptr, &ptr);
    ret.g_ = (float)strtod(ptr, &ptr);
    ret.b_ = (float)strtod(ptr, &ptr);
    if (elements > 3)
        ret.a_ = (float)strtod(ptr, &ptr);
    
    return ret;
}

IntRect ToIntRect(const String& source)
{
    return ToIntRect(source.CString());
}

IntRect ToIntRect(const char* source)
{
    IntRect ret(IntRect::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 4)
        return ret;
    
    char* ptr = (char*)source;
    ret.left_ = strtol(ptr, &ptr, 10);
    ret.top_ = strtol(ptr, &ptr, 10);
    ret.right_ = strtol(ptr, &ptr, 10);
    ret.bottom_ = strtol(ptr, &ptr, 10);
    
    return ret;
}

IntVector2 ToIntVector2(const String& source)
{
    return ToIntVector2(source.CString());
}

IntVector2 ToIntVector2(const char* source)
{
    IntVector2 ret(IntVector2::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 2)
        return ret;
    
    char* ptr = (char*)source;
    ret.x_ = strtol(ptr, &ptr, 10);
    ret.y_ = strtol(ptr, &ptr, 10);
    
    return ret;
}

Rect ToRect(const String& source)
{
    return ToRect(source.CString());
}

Rect ToRect(const char* source)
{
    Rect ret(Rect::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 4)
        return ret;
    
    char* ptr = (char*)source;
    ret.min_.x_ = (float)strtod(ptr, &ptr);
    ret.min_.y_ = (float)strtod(ptr, &ptr);
    ret.max_.x_ = (float)strtod(ptr, &ptr);
    ret.max_.y_ = (float)strtod(ptr, &ptr);
    
    return ret;
}

Quaternion ToQuaternion(const String& source)
{
    return ToQuaternion(source.CString());
}

Quaternion ToQuaternion(const char* source)
{
    unsigned elements = CountElements(source, ' ');
    char* ptr = (char*)source;
    
    if (elements < 3)
        return Quaternion::IDENTITY;
    else if (elements < 4)
    {
        // 3 coords specified: conversion from Euler angles
        float x, y, z;
        x = (float)strtod(ptr, &ptr);
        y = (float)strtod(ptr, &ptr);
        z = (float)strtod(ptr, &ptr);
        
        return Quaternion(x, y, z);
    }
    else
    {
        // 4 coords specified: full quaternion
        Quaternion ret;
        ret.w_ = (float)strtod(ptr, &ptr);
        ret.x_ = (float)strtod(ptr, &ptr);
        ret.y_ = (float)strtod(ptr, &ptr);
        ret.z_ = (float)strtod(ptr, &ptr);
        
        return ret;
    }
}

Vector2 ToVector2(const String& source)
{
    return ToVector2(source.CString());
}

Vector2 ToVector2(const char* source)
{
    Vector2 ret(Vector2::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 2)
        return ret;
    
    char* ptr = (char*)source;
    ret.x_ = (float)strtod(ptr, &ptr);
    ret.y_ = (float)strtod(ptr, &ptr);
    
    return ret;
}

Vector3 ToVector3(const String& source)
{
    return ToVector3(source.CString());
}

Vector3 ToVector3(const char* source)
{
    Vector3 ret(Vector3::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 3)
        return ret;
    
    char* ptr = (char*)source;
    ret.x_ = (float)strtod(ptr, &ptr);
    ret.y_ = (float)strtod(ptr, &ptr);
    ret.z_ = (float)strtod(ptr, &ptr);
    
    return ret;
}

Vector4 ToVector4(const String& source, bool allowMissingCoords)
{
    return ToVector4(source.CString(), allowMissingCoords);
}

Vector4 ToVector4(const char* source, bool allowMissingCoords)
{
    Vector4 ret(Vector4::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    char* ptr = (char*)source;
    
    if (!allowMissingCoords)
    {
        if (elements < 4)
            return ret;
        
        ret.x_ = (float)strtod(ptr, &ptr);
        ret.y_ = (float)strtod(ptr, &ptr);
        ret.z_ = (float)strtod(ptr, &ptr);
        ret.w_ = (float)strtod(ptr, &ptr);
        
        return ret;
    }
    else
    {
        if (elements > 0)
            ret.x_ = (float)strtod(ptr, &ptr);
        if (elements > 1)
            ret.y_ = (float)strtod(ptr, &ptr);
        if (elements > 2)
            ret.z_ = (float)strtod(ptr, &ptr);
        if (elements > 3)
            ret.w_ = (float)strtod(ptr, &ptr);
        
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
    return GetStringListIndex(value.CString(), strings, defaultIndex, caseSensitive);
}

unsigned GetStringListIndex(const char* value, const String* strings, unsigned defaultIndex, bool caseSensitive)
{
    unsigned i = 0;
    
    while (!strings[i].Empty())
    {
        if (!strings[i].Compare(value, caseSensitive))
            return i;
        ++i;
    }
    
    return defaultIndex;
}

unsigned GetStringListIndex(const char* value, const char** strings, unsigned defaultIndex, bool caseSensitive)
{
    unsigned i = 0;
    
    while (strings[i])
    {
        if (!String::Compare(value, strings[i], caseSensitive))
            return i;
        ++i;
    }
    
    return defaultIndex;
}

String ToString(const char* formatString, ...)
{
    String ret;
    va_list args;
    va_start(args, formatString);
    ret.AppendWithFormatArgs(formatString, args);
    va_end(args);
    return ret;
}

bool IsAlpha(unsigned ch)
{
    return ch < 255 ? isalpha(ch) : false;
}

bool IsDigit(unsigned ch)
{
    return ch < 255 ? isdigit(ch) : false;
}

}
