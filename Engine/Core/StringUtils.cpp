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
#include "../../ThirdParty/Assimp/code/pstdint.h"
#include "../../ThirdParty/Assimp/code/fast_atof.h"

#include <cstdio>
#include <ctype.h>

#include "DebugNew.h"

unsigned CountElements(const String& str, char separator)
{
    const char* buffer = str.CString();
    unsigned length = str.Length();
    unsigned pos = 0;
    unsigned ret = 0;
    
    while (pos < length)
    {
        unsigned start = pos;
        
        while (start < length)
        {
            if (buffer[start] == separator)
                break;
            
            ++start;
        }
        
        if (start == length)
        {
            ++ret;
            break;
        }
        
        unsigned end = start;
        
        while (end < length)
        {
            if (buffer[end] != separator)
                break;
            
            ++end;
        }
        
        ++ret;
        pos = end;
    }
    
    return ret;
}

void SkipSeparator(const char** str, char separator)
{
    const char*& ptr = *str;
    
    while (ptr && *ptr && *ptr == separator)
        ++ptr;
}

bool ToBool(const String& source)
{
    for (unsigned i = 0; i < source.Length(); ++i)
    {
        char c = tolower(source[0]);
        if (c == 't' || c == 'y' || c == '1')
            return true;
        else if (c != ' ' && c != '\t')
            break;
    }
    
    return false;
}

int ToInt(const String& source)
{
    if (!source.Length())
        return 0;
    return Assimp::strtol10(source.CString(), 0);
}

unsigned ToUInt(const String& source)
{
    if (!source.Length())
        return 0;
    return Assimp::strtoul10(source.CString(), 0);
}

float ToFloat(const String& source)
{
    if (!source.Length())
        return 0.0f;
    return Assimp::fast_atof(source.CString());
}

Color ToColor(const String& source)
{
    Color ret;
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 3)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.r_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.g_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.b_ = Assimp::fast_atof(&ptr);
    if (elements > 3)
    {
        SkipSeparator(&ptr, ' ');
        ret.a_ = Assimp::fast_atof(&ptr);
    }
    
    return ret;
}

IntRect ToIntRect(const String& source)
{
    IntRect ret(IntRect::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 4)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.left_ = Assimp::strtol10(ptr, &ptr);
    SkipSeparator(&ptr, ' ');
    ret.top_ = Assimp::strtol10(ptr, &ptr);
    SkipSeparator(&ptr, ' ');
    ret.right_ = Assimp::strtol10(ptr, &ptr);
    SkipSeparator(&ptr, ' ');
    ret.bottom_ = Assimp::strtol10(ptr, &ptr);
    
    return ret;
}

IntVector2 ToIntVector2(const String& source)
{
    IntVector2 ret(IntVector2::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 2)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.x_ = Assimp::strtol10(ptr, &ptr);
    SkipSeparator(&ptr, ' ');
    ret.y_ = Assimp::strtol10(ptr, &ptr);
    
    return ret;
}

Rect ToRect(const String& source)
{
    Rect ret(Rect::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 4)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.min_.x_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.min_.y_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.max_.x_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.max_.y_ = Assimp::fast_atof(&ptr);
    
    return ret;
}

Quaternion ToQuaternion(const String& source)
{
    unsigned elements = CountElements(source, ' ');
    const char* ptr = source.CString();
    const char* end = ptr + source.Length();
    
    if (elements < 3)
        return Quaternion::IDENTITY;
    else if (elements < 4)
    {
        // 3 coords specified: conversion from Euler angles
        float x, y, z;
        SkipSeparator(&ptr, ' ');
        x = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        y = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        z = Assimp::fast_atof(&ptr);
        
        return Quaternion(x, y, z);
    }
    else
    {
        // 4 coords specified: full quaternion
        Quaternion ret;
        
        SkipSeparator(&ptr, ' ');
        ret.w_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.x_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.y_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.z_ = Assimp::fast_atof(&ptr);
        
        return ret;
    }
}

Vector2 ToVector2(const String& source)
{
    Vector2 ret(Vector2::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 2)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.x_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.y_ = Assimp::fast_atof(&ptr);
    
    return ret;
}

Vector3 ToVector3(const String& source)
{
    Vector3 ret(Vector3::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    if (elements < 3)
        return ret;
    
    const char* ptr = source.CString();
    
    SkipSeparator(&ptr, ' ');
    ret.x_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.y_ = Assimp::fast_atof(&ptr);
    SkipSeparator(&ptr, ' ');
    ret.z_ = Assimp::fast_atof(&ptr);
    
    return ret;
}

Vector4 ToVector4(const String& source, bool allowMissingCoords)
{
    Vector4 ret(Vector4::ZERO);
    
    unsigned elements = CountElements(source, ' ');
    const char* ptr = source.CString();
    
    if (!allowMissingCoords)
    {
        if (elements < 4)
            return ret;
        
        SkipSeparator(&ptr, ' ');
        ret.x_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.y_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.z_ = Assimp::fast_atof(&ptr);
        SkipSeparator(&ptr, ' ');
        ret.w_ = Assimp::fast_atof(&ptr);
        
        return ret;
    }
    else
    {
        if (elements > 0)
        {
            SkipSeparator(&ptr, ' ');
            ret.x_ = Assimp::fast_atof(&ptr);
        }
        if (elements > 1)
        {
            SkipSeparator(&ptr, ' ');
            ret.y_ = Assimp::fast_atof(&ptr);
        }
        if (elements > 2)
        {
            SkipSeparator(&ptr, ' ');
            ret.z_ = Assimp::fast_atof(&ptr);
        }
        if (elements > 3)
        {
            SkipSeparator(&ptr, ' ');
            ret.w_ = Assimp::fast_atof(&ptr);
        }
        
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
    
    while (!strings[i].Empty())
    {
        if (!value.Compare(strings[i], caseSensitive))
            return i;
        ++i;
    }
    
    return defaultIndex;
}
