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

#pragma once

#include "../Core/Variant.h"

namespace Urho3D
{

/// Parse a bool from a string. Check for the first non-empty character (converted to lowercase) being either 't', 'y' or '1'.
URHO3D_API bool ToBool(const String& source);
/// Parse a bool from a C string. Check for the first non-empty character (converted to lowercase) being either 't', 'y' or '1'.
URHO3D_API bool ToBool(const char* source);
/// Parse a float from a string.
URHO3D_API float ToFloat(const String& source);
/// Parse a float from a C string.
URHO3D_API float ToFloat(const char* source);
/// Parse a double from a string.
URHO3D_API double ToDouble(const String& source);
/// Parse a double from a C string.
URHO3D_API double ToDouble(const char* source);
/// Parse an integer from a string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API int ToInt(const String& source, int base = 10);
/// Parse an integer from a C string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API int ToInt(const char* source, int base = 10);
/// Parse an unsigned integer from a string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API unsigned ToUInt(const String& source, int base = 10);
/// Parse an unsigned integer from a C string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API unsigned ToUInt(const char* source, int base = 10);
/// Parse an 64 bit integer from a string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API long long ToInt64(const String& source, int base = 10);
/// Parse an 64 bit integer from a C string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API long long ToInt64(const char* source, int base = 10);
/// Parse an unsigned 64 bit integer from a string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API unsigned long long ToUInt64(const String& source, int base = 10);
/// Parse an unsigned 64 bit integer from a C string. Assumed to be decimal by default (base 10). Use base 0 to autodetect from string.
URHO3D_API unsigned long long ToUInt64(const char* source, int base = 10);
/// Parse a Color from a string.
URHO3D_API Color ToColor(const String& source);
/// Parse a Color from a C string.
URHO3D_API Color ToColor(const char* source);
/// Parse an IntRect from a string.
URHO3D_API IntRect ToIntRect(const String& source);
/// Parse an IntRect from a C string.
URHO3D_API IntRect ToIntRect(const char* source);
/// Parse an IntVector2 from a string.
URHO3D_API IntVector2 ToIntVector2(const String& source);
/// Parse an IntVector2 from a C string.
URHO3D_API IntVector2 ToIntVector2(const char* source);
/// Parse an IntVector3 from a string.
URHO3D_API IntVector3 ToIntVector3(const String& source);
/// Parse an IntVector3 from a C string.
URHO3D_API IntVector3 ToIntVector3(const char* source);
/// Parse a Quaternion from a string. If only 3 components specified, convert Euler angles (degrees) to quaternion.
URHO3D_API Quaternion ToQuaternion(const String& source);
/// Parse a Quaternion from a C string. If only 3 components specified, convert Euler angles (degrees) to quaternion.
URHO3D_API Quaternion ToQuaternion(const char* source);
/// Parse a Rect from a string.
URHO3D_API Rect ToRect(const String& source);
/// Parse a Rect from a C string.
URHO3D_API Rect ToRect(const char* source);
/// Parse a Vector2 from a string.
URHO3D_API Vector2 ToVector2(const String& source);
/// Parse a Vector2 from a C string.
URHO3D_API Vector2 ToVector2(const char* source);
/// Parse a Vector3 from a string.
URHO3D_API Vector3 ToVector3(const String& source);
/// Parse a Vector3 from a C string.
URHO3D_API Vector3 ToVector3(const char* source);
/// Parse a Vector4 from a string.
URHO3D_API Vector4 ToVector4(const String& source, bool allowMissingCoords = false);
/// Parse a Vector4 from a C string.
URHO3D_API Vector4 ToVector4(const char* source, bool allowMissingCoords = false);
/// Parse a float, Vector or Matrix variant from a string. Return empty variant on illegal input.
URHO3D_API Variant ToVectorVariant(const String& source);
/// Parse a float, Vector or Matrix variant from a C string. Return empty variant on illegal input.
URHO3D_API Variant ToVectorVariant(const char* source);
/// Parse a Matrix3 from a string.
URHO3D_API Matrix3 ToMatrix3(const String& source);
/// Parse a Matrix3 from a C string.
URHO3D_API Matrix3 ToMatrix3(const char* source);
/// Parse a Matrix3x4 from a string.
URHO3D_API Matrix3x4 ToMatrix3x4(const String& source);
/// Parse a Matrix3x4 from a C string.
URHO3D_API Matrix3x4 ToMatrix3x4(const char* source);
/// Parse a Matrix4 from a string.
URHO3D_API Matrix4 ToMatrix4(const String& source);
/// Parse a Matrix4 from a C string.
URHO3D_API Matrix4 ToMatrix4(const char* source);
/// Convert a pointer to string (returns hexadecimal).
URHO3D_API String ToString(void* value);
/// Convert an unsigned integer to string as hexadecimal.
URHO3D_API String ToStringHex(unsigned value);
/// Convert a byte buffer to a string.
URHO3D_API void BufferToString(String& dest, const void* data, unsigned size);
/// Convert a string to a byte buffer.
URHO3D_API void StringToBuffer(PODVector<unsigned char>& dest, const String& source);
/// Convert a C string to a byte buffer.
URHO3D_API void StringToBuffer(PODVector<unsigned char>& dest, const char* source);
/// Return an index to a string list corresponding to the given string, or a default value if not found. The string list must be empty-terminated.
URHO3D_API unsigned GetStringListIndex(const String& value, const String* strings, unsigned defaultIndex, bool caseSensitive = false);
/// Return an index to a string list corresponding to the given C string, or a default value if not found. The string list must be empty-terminated.
URHO3D_API unsigned GetStringListIndex(const char* value, const String* strings, unsigned defaultIndex, bool caseSensitive = false);
/// Return an index to a C string list corresponding to the given C string, or a default value if not found. The string list must be empty-terminated.
URHO3D_API unsigned GetStringListIndex(const char* value, const char** strings, unsigned defaultIndex, bool caseSensitive = false);
/// Return a formatted string.
URHO3D_API String ToString(const char* formatString, ...);
/// Return whether a char is an alphabet letter.
URHO3D_API bool IsAlpha(unsigned ch);
/// Return whether a char is a digit.
URHO3D_API bool IsDigit(unsigned ch);
/// Return char in uppercase.
URHO3D_API unsigned ToUpper(unsigned ch);
/// Return char in lowercase.
URHO3D_API unsigned ToLower(unsigned ch);
/// Convert a memory size into a formatted size string, of the style "1.5 Mb".
URHO3D_API String GetFileSizeString(unsigned long long memorySize);
/// Decode a base64-encoded string into buffer.
URHO3D_API PODVector<unsigned char> DecodeBase64(String encodedString);
/// Parse type from a C string.
template <class T> T FromString(const char* source);

template <> inline const char* FromString<const char*>(const char* source) { return source; }
template <> inline String FromString<String>(const char* source) { return source; }
template <> inline bool FromString<bool>(const char* source) { return ToBool(source); }
template <> inline float FromString<float>(const char* source) { return ToFloat(source); }
template <> inline double FromString<double>(const char* source) { return ToDouble(source); }
template <> inline int FromString<int>(const char* source) { return ToInt(source); }
template <> inline unsigned FromString<unsigned>(const char* source) { return ToUInt(source); }
template <> inline Color FromString<Color>(const char* source) { return ToColor(source); }
template <> inline IntRect FromString<IntRect>(const char* source) { return ToIntRect(source); }
template <> inline IntVector2 FromString<IntVector2>(const char* source) { return ToIntVector2(source); }
template <> inline IntVector3 FromString<IntVector3>(const char* source) { return ToIntVector3(source); }
template <> inline Quaternion FromString<Quaternion>(const char* source) { return ToQuaternion(source); }
template <> inline Rect FromString<Rect>(const char* source) { return ToRect(source); }
template <> inline Vector2 FromString<Vector2>(const char* source) { return ToVector2(source); }
template <> inline Vector3 FromString<Vector3>(const char* source) { return ToVector3(source); }
template <> inline Vector4 FromString<Vector4>(const char* source) { return ToVector4(source); }
template <> inline Variant FromString<Variant>(const char* source) { return ToVectorVariant(source); }
template <> inline Matrix3 FromString<Matrix3>(const char* source) { return ToMatrix3(source); }
template <> inline Matrix3x4 FromString<Matrix3x4>(const char* source) { return ToMatrix3x4(source); }
template <> inline Matrix4 FromString<Matrix4>(const char* source) { return ToMatrix4(source); }

/// Parse type from a string.
template <class T> T FromString(const String& source) { return FromString<T>(source.CString()); }

}
