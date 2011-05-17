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
std::vector<String> Split(const String& source, char separator);
/// Parse a bool from a string. Check for the substring "true" case-insensitively
bool ToBool(const String& source);
/// Parse a float from a string
float ToFloat(const String& source);
/// Parse an integer from a string
int ToInt(const String& source);
/// Parse an unsigned integer from a string
unsigned ToUInt(const String& source);
/// Parse a Color from a string
Color ToColor(const String& source);
/// Parse an IntRect from a string
IntRect ToIntRect(const String& source);
/// Parse an IntVector2 from a string
IntVector2 ToIntVector2(const String& source);
/// Parse a Quaternion from a string. If only 3 components specified, convert Euler angles (degrees) to quaternion
Quaternion ToQuaternion(const String& source);
/// Parse a Rect from a string
Rect ToRect(const String& source);
/// Parse a Vector2 from a string
Vector2 ToVector2(const String& source);
/// Parse a Vector3 from a string
Vector3 ToVector3(const String& source);
/// Parse a Vector4 from a string
Vector4 ToVector4(const String& source, bool allowMissingCoords = false);
/// Convert a bool to string
String ToString(bool value);
/// Convert a float to string
String ToString(float value);
/// Convert an integer to string
String ToString(int value);
/// Convert an unsigned integer to string
String ToString(unsigned value);
/// Convert a Color to string
String ToString(const Color& value);
/// Convert an IntRect to string
String ToString(const IntRect& value);
/// Convert an IntVector2 to string
String ToString(const IntVector2& value);
/// Convert a Quaternion to string
String ToString(const Quaternion& value);
/// Convert a Rect to string
String ToString(const Rect& value);
/// Convert a StringHash to string. Return the reverse mapping if found
String ToString(const StringHash& value);
/// Convert a ShortStringHash to string. Return the reverse mapping if found
String ToString(const ShortStringHash& value);
/// Convert a Vector2 to string
String ToString(const Vector2& value);
/// Convert a Vector3 to string
String ToString(const Vector3& value);
/// Convert a Vector4 to string
String ToString(const Vector4& value);
/// Convert a pointer to string (returns hexadecimal)
String ToString(void* value);
/// Convert an unsigned integer to string as hexadecimal
String ToStringHex(unsigned value);

/// Return an index to a string list corresponding to the given string, or a default value if not found
unsigned GetStringListIndex(const String& value, const String* strings, unsigned count, unsigned defaultIndex,
    bool caseSensitive = false);
