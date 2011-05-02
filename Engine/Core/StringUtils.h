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

#pragma once

#include "Color.h"
#include "Quaternion.h"
#include "Rect.h"
#include "StringHash.h"
#include "Vector4.h"

#include <vector>

/// Split string with a separator char
std::vector<std::string> Split(const std::string& source, char separator);
/// Replace characters in a string
std::string Replace(const std::string& source, char replaceThis, char replaceWith);
/// Replace substrings in a string
std::string Replace(const std::string& source, const std::string& replaceThis, const std::string& replaceWith);
/// Convert a string to uppercase
std::string ToUpper(const std::string& source);
/// Convert a string to lowercase
std::string ToLower(const std::string& source);
/// Replace characters in a string by modifying the original string
void ReplaceInPlace(std::string& str, char replaceThis, char replaceWith);
/// Replace substrings in a string by modifying the original string
void ReplaceInPlace(std::string& str, const std::string& replaceThis, const std::string& replaceWith);
/// Convert a string to uppercase by modifying the original string
void ToUpperInPlace(std::string& str);
/// Convert a string to lowercase by modifying the original string
void ToLowerInPlace(std::string& str);
/// Parse a bool from a string. Check for the substring "true" case-insensitively
bool ToBool(const std::string& source);
/// Parse a float from a string
float ToFloat(const std::string& source);
/// Parse an integer from a string
int ToInt(const std::string& source);
/// Parse an unsigned integer from a string
unsigned ToUInt(const std::string& source);
/// Parse a Color from a string
Color ToColor(const std::string& source);
/// Parse an IntRect from a string
IntRect ToIntRect(const std::string& source);
/// Parse an IntVector2 from a string
IntVector2 ToIntVector2(const std::string& source);
/// Parse a Quaternion from a string. If only 3 components specified, convert Euler angles (degrees) to quaternion
Quaternion ToQuaternion(const std::string& source);
/// Parse a Rect from a string
Rect ToRect(const std::string& source);
/// Parse a Vector2 from a string
Vector2 ToVector2(const std::string& source);
/// Parse a Vector3 from a string
Vector3 ToVector3(const std::string& source);
/// Parse a Vector4 from a string
Vector4 ToVector4(const std::string& source, bool allowMissingCoords = false);
/// Convert a bool to string
std::string ToString(bool value);
/// Convert a float to string
std::string ToString(float value);
/// Convert an integer to string
std::string ToString(int value);
/// Convert an unsigned integer to string
std::string ToString(unsigned value);
/// Convert a Color to string
std::string ToString(const Color& value);
/// Convert an IntRect to string
std::string ToString(const IntRect& value);
/// Convert an IntVector2 to string
std::string ToString(const IntVector2& value);
/// Convert a Quaternion to string
std::string ToString(const Quaternion& value);
/// Convert a Rect to string
std::string ToString(const Rect& value);
/// Convert a StringHash to string. Return the reverse mapping if found
std::string ToString(const StringHash& value);
/// Convert a ShortStringHash to string. Return the reverse mapping if found
std::string ToString(const ShortStringHash& value);
/// Convert a Vector2 to string
std::string ToString(const Vector2& value);
/// Convert a Vector3 to string
std::string ToString(const Vector3& value);
/// Convert a Vector4 to string
std::string ToString(const Vector4& value);
/// Convert a pointer to string (returns hexadecimal)
std::string ToString(void* value);
/// Convert an unsigned integer to string as hexadecimal
std::string ToStringHex(unsigned value);

/// Return an index to a string list corresponding to the given string, or a default value if not found
unsigned GetStringListIndex(const std::string& value, const std::string* strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive = false);
/// Return an index to a string list (C string version)
unsigned GetStringListIndex(const char* value, const char** strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive = false);
