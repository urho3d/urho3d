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

#ifndef COMMON_STRINGUTILS_H
#define COMMON_STRINGUTILS_H

#include "Color.h"
#include "Quaternion.h"
#include "Rect.h"
#include "StringHash.h"
#include "Vector4.h"

#include <string>
#include <vector>

//! Split string with a separator char
std::vector<std::string> split(const std::string& source, char separator);
//! Replace characters in a string
std::string replace(const std::string& source, char replaceThis, char replaceWith);
//! Replace substrings in a string
std::string replace(const std::string& source, const std::string& replaceThis, const std::string& replaceWith);
//! Convert a string to uppercase
std::string toUpper(const std::string& source);
//! Convert a string to lowercase
std::string toLower(const std::string& source);
//! Replace characters in a string by modifying the original string
void replaceInPlace(std::string& str, char replaceThis, char replaceWith);
//! Replace substrings in a string by modifying the original string
void replaceInPlace(std::string& str, const std::string& replaceThis, const std::string& replaceWith);
//! Convert a string to uppercase by modifying the original string
void toUpperInPlace(std::string& str);
//! Convert a string to lowercase by modifying the original string
void toLowerInPlace(std::string& str);
//! Parse a bool from a string. Check for the substring "true" case-insensitively
bool toBool(const std::string& source);
//! Parse a float from a string
float toFloat(const std::string& source);
//! Parse an integer from a string
int toInt(const std::string& source);
//! Parse an unsigned integer from a string
unsigned toUInt(const std::string& source);
//! Parse a Color from a string
Color toColor(const std::string& source);
//! Parse an IntRect from a string
IntRect toIntRect(const std::string& source);
//! Parse an IntVector2 from a string
IntVector2 toIntVector2(const std::string& source);
//! Parse a Quaternion from a string. If only 3 components specified, convert Euler angles (degrees) to quaternion
Quaternion toQuaternion(const std::string& source);
//! Parse a Rect from a string
Rect toRect(const std::string& source);
//! Parse a Vector2 from a string
Vector2 toVector2(const std::string& source);
//! Parse a Vector3 from a string
Vector3 toVector3(const std::string& source);
//! Parse a Vector4 from a string
Vector4 toVector4(const std::string& source, bool allowMissingCoords = false);
//! Convert a bool to string
std::string toString(bool value);
//! Convert a float to string
std::string toString(float value);
//! Convert an integer to string
std::string toString(int value);
//! Convert an unsigned integer to string
std::string toString(unsigned value);
//! Convert a Color to string
std::string toString(const Color& value);
//! Convert an IntRect to string
std::string toString(const IntRect& value);
//! Convert an IntVector2 to string
std::string toString(const IntVector2& value);
//! Convert a Quaternion to string
std::string toString(const Quaternion& value);
//! Convert a Rect to string
std::string toString(const Rect& value);
//! Convert a StringHash to string. Return the reverse mapping if found
std::string toString(const StringHash& value);
//! Convert a ShortStringHash to string. Return the reverse mapping if found
std::string toString(const ShortStringHash& value);
//! Convert a Vector2 to string
std::string toString(const Vector2& value);
//! Convert a Vector3 to string
std::string toString(const Vector3& value);
//! Convert a Vector4 to string
std::string toString(const Vector4& value);
//! Convert an integer to string as hexadecimal
std::string toStringHex(int value);
//! Return an index to a string list corresponding to the given string, or a default value if not found
unsigned getIndexFromStringList(const std::string& value, const std::string* strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive = false);

#endif // COMMON_STRINGUTILS_H
