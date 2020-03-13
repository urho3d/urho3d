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

#include "../Precompiled.h"

#include "../Core/StringUtils.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

static const String base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

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
        auto c = (char)tolower(source[i]);
        if (c == 't' || c == 'y' || c == '1')
            return true;
        else if (c != ' ' && c != '\t')
            break;
    }

    return false;
}

int ToInt(const String& source, int base)
{
    return ToInt(source.CString(), base);
}

int ToInt(const char* source, int base)
{
    if (!source)
        return 0;

    // Shield against runtime library assert by converting illegal base values to 0 (autodetect)
    if (base < 2 || base > 36)
        base = 0;

    return (int)strtol(source, nullptr, base);
}

long long ToInt64(const char* source, int base)
{
    if (!source)
        return 0;

    // Shield against runtime library assert by converting illegal base values to 0 (autodetect)
    if (base < 2 || base > 36)
        base = 0;

    return strtoll(source, nullptr, base);
}

long long ToInt64(const String& source, int base)
{
    return ToInt64(source.CString(), base);
}

unsigned ToUInt(const String& source, int base)
{
    return ToUInt(source.CString(), base);
}

unsigned long long ToUInt64(const char* source, int base)
{
    if (!source)
        return 0;

    // Shield against runtime library assert by converting illegal base values to 0 (autodetect)
    if (base < 2 || base > 36)
        base = 0;

    return strtoull(source, nullptr, base);
}

unsigned long long ToUInt64(const String& source, int base)
{
    return ToUInt64(source.CString(), base);
}

unsigned ToUInt(const char* source, int base)
{
    if (!source)
        return 0;

    if (base < 2 || base > 36)
        base = 0;

    return (unsigned)strtoul(source, nullptr, base);
}

float ToFloat(const String& source)
{
    return ToFloat(source.CString());
}

float ToFloat(const char* source)
{
    if (!source)
        return 0;

    return (float)strtod(source, nullptr);
}

double ToDouble(const String& source)
{
    return ToDouble(source.CString());
}

double ToDouble(const char* source)
{
    if (!source)
        return 0;

    return strtod(source, nullptr);
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

    auto* ptr = (char*)source;
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

    auto* ptr = (char*)source;
    ret.left_ = (int)strtol(ptr, &ptr, 10);
    ret.top_ = (int)strtol(ptr, &ptr, 10);
    ret.right_ = (int)strtol(ptr, &ptr, 10);
    ret.bottom_ = (int)strtol(ptr, &ptr, 10);

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

    auto* ptr = (char*)source;
    ret.x_ = (int)strtol(ptr, &ptr, 10);
    ret.y_ = (int)strtol(ptr, &ptr, 10);

    return ret;
}

IntVector3 ToIntVector3(const String& source)
{
    return ToIntVector3(source.CString());
}

IntVector3 ToIntVector3(const char* source)
{
    IntVector3 ret(IntVector3::ZERO);

    unsigned elements = CountElements(source, ' ');
    if (elements < 3)
        return ret;

    auto* ptr = (char*)source;
    ret.x_ = (int)strtol(ptr, &ptr, 10);
    ret.y_ = (int)strtol(ptr, &ptr, 10);
    ret.z_ = (int)strtol(ptr, &ptr, 10);

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

    auto* ptr = (char*)source;
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
    auto* ptr = (char*)source;

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

    auto* ptr = (char*)source;
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

    auto* ptr = (char*)source;
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
    auto* ptr = (char*)source;

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

Variant ToVectorVariant(const String& source)
{
    return ToVectorVariant(source.CString());
}

Variant ToVectorVariant(const char* source)
{
    Variant ret;
    unsigned elements = CountElements(source, ' ');

    switch (elements)
    {
    case 1:
        ret.FromString(VAR_FLOAT, source);
        break;

    case 2:
        ret.FromString(VAR_VECTOR2, source);
        break;

    case 3:
        ret.FromString(VAR_VECTOR3, source);
        break;

    case 4:
        ret.FromString(VAR_VECTOR4, source);
        break;

    case 9:
        ret.FromString(VAR_MATRIX3, source);
        break;

    case 12:
        ret.FromString(VAR_MATRIX3X4, source);
        break;

    case 16:
        ret.FromString(VAR_MATRIX4, source);
        break;

    default:
        // Illegal input. Return variant remains empty
        break;
    }

    return ret;
}

Matrix3 ToMatrix3(const String& source)
{
    return ToMatrix3(source.CString());
}

Matrix3 ToMatrix3(const char* source)
{
    Matrix3 ret(Matrix3::ZERO);

    unsigned elements = CountElements(source, ' ');
    if (elements < 9)
        return ret;

    auto* ptr = (char*)source;
    ret.m00_ = (float)strtod(ptr, &ptr);
    ret.m01_ = (float)strtod(ptr, &ptr);
    ret.m02_ = (float)strtod(ptr, &ptr);
    ret.m10_ = (float)strtod(ptr, &ptr);
    ret.m11_ = (float)strtod(ptr, &ptr);
    ret.m12_ = (float)strtod(ptr, &ptr);
    ret.m20_ = (float)strtod(ptr, &ptr);
    ret.m21_ = (float)strtod(ptr, &ptr);
    ret.m22_ = (float)strtod(ptr, &ptr);

    return ret;
}

Matrix3x4 ToMatrix3x4(const String& source)
{
    return ToMatrix3x4(source.CString());
}

Matrix3x4 ToMatrix3x4(const char* source)
{
    Matrix3x4 ret(Matrix3x4::ZERO);

    unsigned elements = CountElements(source, ' ');
    if (elements < 12)
        return ret;

    auto* ptr = (char*)source;
    ret.m00_ = (float)strtod(ptr, &ptr);
    ret.m01_ = (float)strtod(ptr, &ptr);
    ret.m02_ = (float)strtod(ptr, &ptr);
    ret.m03_ = (float)strtod(ptr, &ptr);
    ret.m10_ = (float)strtod(ptr, &ptr);
    ret.m11_ = (float)strtod(ptr, &ptr);
    ret.m12_ = (float)strtod(ptr, &ptr);
    ret.m13_ = (float)strtod(ptr, &ptr);
    ret.m20_ = (float)strtod(ptr, &ptr);
    ret.m21_ = (float)strtod(ptr, &ptr);
    ret.m22_ = (float)strtod(ptr, &ptr);
    ret.m23_ = (float)strtod(ptr, &ptr);

    return ret;
}

Matrix4 ToMatrix4(const String& source)
{
    return ToMatrix4(source.CString());
}

Matrix4 ToMatrix4(const char* source)
{
    Matrix4 ret(Matrix4::ZERO);

    unsigned elements = CountElements(source, ' ');
    if (elements < 16)
        return ret;

    auto* ptr = (char*)source;
    ret.m00_ = (float)strtod(ptr, &ptr);
    ret.m01_ = (float)strtod(ptr, &ptr);
    ret.m02_ = (float)strtod(ptr, &ptr);
    ret.m03_ = (float)strtod(ptr, &ptr);
    ret.m10_ = (float)strtod(ptr, &ptr);
    ret.m11_ = (float)strtod(ptr, &ptr);
    ret.m12_ = (float)strtod(ptr, &ptr);
    ret.m13_ = (float)strtod(ptr, &ptr);
    ret.m20_ = (float)strtod(ptr, &ptr);
    ret.m21_ = (float)strtod(ptr, &ptr);
    ret.m22_ = (float)strtod(ptr, &ptr);
    ret.m23_ = (float)strtod(ptr, &ptr);
    ret.m30_ = (float)strtod(ptr, &ptr);
    ret.m31_ = (float)strtod(ptr, &ptr);
    ret.m32_ = (float)strtod(ptr, &ptr);
    ret.m33_ = (float)strtod(ptr, &ptr);

    return ret;
}

String ToString(void* value)
{
    return ToStringHex((unsigned)(size_t)value);
}

String ToStringHex(unsigned value)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08x", value);
    return String(tempBuffer);
}

void BufferToString(String& dest, const void* data, unsigned size)
{
    // Precalculate needed string size
    const auto* bytes = (const unsigned char*)data;
    unsigned length = 0;
    for (unsigned i = 0; i < size; ++i)
    {
        // Room for separator
        if (i)
            ++length;

        // Room for the value
        if (bytes[i] < 10)
            ++length;
        else if (bytes[i] < 100)
            length += 2;
        else
            length += 3;
    }

    dest.Resize(length);
    unsigned index = 0;

    // Convert values
    for (unsigned i = 0; i < size; ++i)
    {
        if (i)
            dest[index++] = ' ';

        if (bytes[i] < 10)
        {
            dest[index++] = '0' + bytes[i];
        }
        else if (bytes[i] < 100)
        {
            dest[index++] = (char)('0' + bytes[i] / 10);
            dest[index++] = (char)('0' + bytes[i] % 10);
        }
        else
        {
            dest[index++] = (char)('0' + bytes[i] / 100);
            dest[index++] = (char)('0' + bytes[i] % 100 / 10);
            dest[index++] = (char)('0' + bytes[i] % 10);
        }
    }
}

void StringToBuffer(PODVector<unsigned char>& dest, const String& source)
{
    StringToBuffer(dest, source.CString());
}

void StringToBuffer(PODVector<unsigned char>& dest, const char* source)
{
    if (!source)
    {
        dest.Clear();
        return;
    }

    unsigned size = CountElements(source, ' ');
    dest.Resize(size);

    bool inSpace = true;
    unsigned index = 0;
    unsigned value = 0;

    // Parse values
    const char* ptr = source;
    while (*ptr)
    {
        if (inSpace && *ptr != ' ')
        {
            inSpace = false;
            value = (unsigned)(*ptr - '0');
        }
        else if (!inSpace && *ptr != ' ')
        {
            value *= 10;
            value += *ptr - '0';
        }
        else if (!inSpace && *ptr == ' ')
        {
            dest[index++] = (unsigned char)value;
            inSpace = true;
        }

        ++ptr;
    }

    // Write the final value
    if (!inSpace && index < size)
        dest[index] = (unsigned char)value;
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
    return ch < 256 ? isalpha(ch) != 0 : false;
}

bool IsDigit(unsigned ch)
{
    return ch < 256 ? isdigit(ch) != 0 : false;
}

unsigned ToUpper(unsigned ch)
{
    return (unsigned)toupper(ch);
}

unsigned ToLower(unsigned ch)
{
    return (unsigned)tolower(ch);
}

String GetFileSizeString(unsigned long long memorySize)
{
    static const char* memorySizeStrings = "kMGTPE";

    String output;

    if (memorySize < 1024)
    {
        output = String(memorySize) + " b";
    }
    else
    {
        const auto exponent = (int)(log((double)memorySize) / log(1024.0));
        const double majorValue = ((double)memorySize) / pow(1024.0, exponent);
        char buffer[64];
        memset(buffer, 0, 64);
        sprintf(buffer, "%.1f", majorValue);
        output = buffer;
        output += " ";
        output += memorySizeStrings[exponent - 1];
    }

    return output;
}

// Implementation of base64 decoding originally by Ren� Nyffenegger.
// Modified by Konstantin Guschin and Lasse Oorni

/*
base64.cpp and base64.h

Copyright (C) 2004-2017 Ren� Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

Ren� Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static inline bool IsBase64(char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

PODVector<unsigned char> DecodeBase64(String encodedString)
{
    int inLen = encodedString.Length();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char charArray4[4], charArray3[3];
    PODVector<unsigned char> ret;

    while (inLen-- && (encodedString[in_] != '=') && IsBase64(encodedString[in_]))
    {
        charArray4[i++] = encodedString[in_];
        in_++;

        if (i == 4)
        {
            for (i = 0; i < 4; i++)
                charArray4[i] = base64_chars.Find(charArray4[i]);

            charArray3[0] = (charArray4[0] << 2u) + ((charArray4[1] & 0x30u) >> 4u);
            charArray3[1] = ((charArray4[1] & 0xfu) << 4u) + ((charArray4[2] & 0x3cu) >> 2u);
            charArray3[2] = ((charArray4[2] & 0x3u) << 6u) + charArray4[3];

            for (i = 0; (i < 3); i++)
                ret.Push(charArray3[i]);

            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j <4; j++)
            charArray4[j] = 0;

        for (j = 0; j <4; j++)
            charArray4[j] = base64_chars.Find(charArray4[j]);

        charArray3[0] = (charArray4[0] << 2u) + ((charArray4[1] & 0x30u) >> 4u);
        charArray3[1] = ((charArray4[1] & 0xfu) << 4u) + ((charArray4[2] & 0x3cu) >> 2u);
        charArray3[2] = ((charArray4[2] & 0x3u) << 6u) + charArray4[3];

        for (j = 0; (j < i - 1); j++)
            ret.Push(charArray3[j]);
    }

    return ret;
}

}
