// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

const String String::EMPTY;

String::String(const WString& str)
    : String()
{
    SetUTF8FromWChar(str.CString());
}

String::String(int value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    *this = tempBuffer;
}

String::String(short value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    *this = tempBuffer;
}

String::String(long value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%ld", value);
    *this = tempBuffer;
}

String::String(long long value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%lld", value);
    *this = tempBuffer;
}

String::String(unsigned value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    *this = tempBuffer;
}

String::String(unsigned short value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    *this = tempBuffer;
}

String::String(unsigned long value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%lu", value);
    *this = tempBuffer;
}

String::String(unsigned long long value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%llu", value);
    *this = tempBuffer;
}

String::String(float value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g", value);
    *this = tempBuffer;
}

String::String(double value)
    : String()
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%.15g", value);
    *this = tempBuffer;
}

String::String(bool value)
    : String()
{
    if (value)
        *this = "true";
    else
        *this = "false";
}

String::String(char value)
    : String()
{
    Resize(1);
    GetBuffer()[0] = value;
}

String::String(char value, i32 length)
    : String()
{
    Resize(length);
    char* buffer = GetBuffer();
    for (i32 i = 0; i < length; ++i)
        buffer[i] = value;
}

String& String::operator +=(int rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(short rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(long rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(long long rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(unsigned rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(unsigned short rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(unsigned long rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(unsigned long long rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(float rhs)
{
    return *this += String(rhs);
}

String& String::operator +=(bool rhs)
{
    return *this += String(rhs);
}

void String::Replace(char replaceThis, char replaceWith, bool caseSensitive)
{
    i32 length = Length();
    char* buffer = GetBuffer();

    if (caseSensitive)
    {
        for (i32 i = 0; i < length; ++i)
        {
            if (buffer[i] == replaceThis)
                buffer[i] = replaceWith;
        }
    }
    else
    {
        replaceThis = (char)tolower(replaceThis);
        for (i32 i = 0; i < length; ++i)
        {
            if (tolower(buffer[i]) == replaceThis)
                buffer[i] = replaceWith;
        }
    }
}

void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive)
{
    i32 nextPos = 0;

    i32 length = Length();
    i32 replaceThisLength = replaceThis.Length();
    i32 replaceWithLength = replaceWith.Length();

    while (nextPos < length)
    {
        i32 pos = Find(replaceThis, nextPos, caseSensitive);
        if (pos == NPOS)
            break;
        Replace(pos, replaceThisLength, replaceWith);
        nextPos = pos + replaceWithLength;
    }
}

void String::Replace(i32 pos, i32 length, const String& replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > Length())
        return;

    Replace(pos, length, replaceWith.GetBuffer(), replaceWith.Length());
}

void String::Replace(i32 pos, i32 length, const char* replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > Length())
        return;

    Replace(pos, length, replaceWith, CStringLength(replaceWith));
}

String::Iterator String::Replace(const String::Iterator& start, const String::Iterator& end, const String& replaceWith)
{
    i32 pos = (i32)(start - Begin());
    if (pos >= Length())
        return End();
    i32 length = (i32)(end - start);
    Replace(pos, length, replaceWith);

    return Begin() + pos;
}

String String::Replaced(char replaceThis, char replaceWith, bool caseSensitive) const
{
    String ret(*this);
    ret.Replace(replaceThis, replaceWith, caseSensitive);
    return ret;
}

String String::Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive) const
{
    String ret(*this);
    ret.Replace(replaceThis, replaceWith, caseSensitive);
    return ret;
}

String& String::Append(const String& str)
{
    return *this += str;
}

String& String::Append(const char* str)
{
    return *this += str;
}

String& String::Append(char c)
{
    return *this += c;
}

String& String::Append(const char* str, i32 length)
{
    if (str)
    {
        i32 oldLength = Length();
        Resize(oldLength + length);
        CopyChars(&GetBuffer()[oldLength], str, length);
    }
    return *this;
}

void String::Insert(i32 pos, const String& str)
{
    assert(pos >= 0);

    i32 length = Length();

    if (pos > length)
        pos = length;

    if (pos == length)
        (*this) += str;
    else
        Replace(pos, 0, str);
}

void String::Insert(i32 pos, char c)
{
    assert(pos >= 0);

    i32 length = Length();

    if (pos > length)
        pos = length;

    if (pos == length)
    {
        (*this) += c;
    }
    else
    {
        i32 oldLength = length;
        Resize(length + 1);
        MoveRange(pos + 1, pos, oldLength - pos);
        GetBuffer()[pos] = c;
    }
}

String::Iterator String::Insert(const String::Iterator& dest, const String& str)
{
    i32 length = Length();

    i32 pos = (i32)(dest - Begin());
    if (pos > length)
        pos = length;
    Insert(pos, str);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, const String::Iterator& start, const String::Iterator& end)
{
    i32 pos = (i32)(dest - Begin());
    if (pos > Length())
        pos = Length();
    i32 length = (i32)(end - start);
    Replace(pos, 0, &(*start), length);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, char c)
{
    i32 length = Length();

    i32 pos = (i32)(dest - Begin());
    if (pos > length)
        pos = length;
    Insert(pos, c);

    return Begin() + pos;
}

void String::Erase(i32 pos, i32 length)
{
    Replace(pos, length, String::EMPTY);
}

String::Iterator String::Erase(const String::Iterator& it)
{
    i32 pos = (i32)(it - Begin());
    if (pos >= Length())
        return End();
    Erase(pos);

    return Begin() + pos;
}

String::Iterator String::Erase(const String::Iterator& start, const String::Iterator& end)
{
    i32 pos = (i32)(start - Begin());
    if (pos >= Length())
        return End();
    i32 length = (i32)(end - start);
    Erase(pos, length);

    return Begin() + pos;
}

void String::Resize(i32 newLength)
{
    assert(newLength >= 0);

    i32 capacity = Capacity();

    if (newLength && capacity < newLength + 1) // Need to increase capacity
    {
        // Increase the capacity with half each time it is exceeded
        while (capacity < newLength + 1)
            capacity += (capacity + 1) >> 1u;

        // SHORT_STRING_CAPACITY is minimal possible capacity
        assert(capacity > SHORT_STRING_CAPACITY);

        char* newBuffer = new char[capacity];

        // Move the existing data to the new buffer
        i32 oldLength = Length();
        if (oldLength)
            CopyChars(newBuffer, GetBuffer(), oldLength);

        // Delete the old buffer if in heap
        if (!IsShort())
            delete[] data_.longString_.buffer_;

        newBuffer[newLength] = '\0';
        data_.longString_.buffer_ = newBuffer;
        data_.longString_.capacity_ = capacity;
        data_.longString_.length_ = newLength;
    }
    else // Old buffer is used
    {
        if (IsShort())
        {
            data_.shortString_.buffer_[newLength] = '\0';
            SetShortStringLength((u8)newLength);
        }
        else
        {
            data_.longString_.buffer_[newLength] = '\0';
            data_.longString_.length_ = newLength;
        }
    }
}

void String::Reserve(i32 newCapacity)
{
    assert(newCapacity >= 0);

    i32 length = Length();

    if (newCapacity < length + 1)
        newCapacity = length + 1;

    if (newCapacity < SHORT_STRING_CAPACITY)
        newCapacity = SHORT_STRING_CAPACITY;

    if (newCapacity == Capacity())
        return;

    if (newCapacity > SHORT_STRING_CAPACITY) // New buffer in heap
    {
        char* newBuffer = new char[newCapacity];

        // Move the existing data to the new buffer
        CopyChars(newBuffer, GetBuffer(), length + 1);

        // Delete the old buffer if in heap
        if (!IsShort())
            delete[] data_.longString_.buffer_;

        data_.longString_.buffer_ = newBuffer;
        data_.longString_.capacity_ = newCapacity;
        data_.longString_.length_ = length;
    }
    else // New buffer in stack
    {
        if (!IsShort()) // Old buffer in heap
        {
            // Pointer will be will be overwritten in CopyChars()
            char* oldBuffer = data_.longString_.buffer_;

            // Move the existing data from heap to stack
            CopyChars(data_.shortString_.buffer_, oldBuffer, length + 1);

            // Delete the old buffer if in heap
            delete[] oldBuffer;
        }

        SetShortStringLength((u8)length);
    }
}

void String::Compact()
{
    Reserve(Length() + 1);
}

void String::Clear()
{
    Resize(0);
}

void String::Swap(String& str)
{
    std::swap(data_, str.data_);
}

String String::Substring(i32 pos) const
{
    i32 length = Length();

    if (pos < length)
    {
        String ret;
        ret.Resize(length - pos);
        CopyChars(ret.GetBuffer(), GetBuffer() + pos, ret.Length());

        return ret;
    }
    else
        return String();
}

String String::Substring(i32 pos, i32 length) const
{
    i32 thisLength = Length();

    if (pos < thisLength)
    {
        String ret;
        if (pos + length > thisLength)
            length = thisLength - pos;
        ret.Resize(length);
        CopyChars(ret.GetBuffer(), GetBuffer() + pos, ret.Length());

        return ret;
    }
    else
        return String();
}

String String::Trimmed() const
{
    i32 trimStart = 0;
    i32 trimEnd = Length();

    const char* buffer = GetBuffer();

    while (trimStart < trimEnd)
    {
        char c = buffer[trimStart];
        if (c != ' ' && c != 9)
            break;
        ++trimStart;
    }
    while (trimEnd > trimStart)
    {
        char c = buffer[trimEnd - 1];
        if (c != ' ' && c != 9)
            break;
        --trimEnd;
    }

    return Substring(trimStart, trimEnd - trimStart);
}

String String::ToLower() const
{
    String ret(*this);
    const char* buffer = GetBuffer();
    i32 retLength = ret.Length();
    char* retBuffer = ret.GetBuffer();
    for (i32 i = 0; i < retLength; ++i)
        retBuffer[i] = (char)tolower(buffer[i]);

    return ret;
}

String String::ToUpper() const
{
    String ret(*this);
    const char* buffer = GetBuffer();
    i32 retLength = ret.Length();
    char* retBuffer = ret.GetBuffer();
    for (i32 i = 0; i < retLength; ++i)
        retBuffer[i] = (char)toupper(buffer[i]);

    return ret;
}

Vector<String> String::Split(char separator, bool keepEmptyStrings) const
{
    return Split(CString(), separator, keepEmptyStrings);
}

void String::Join(const Vector<String>& subStrings, const String& glue)
{
    *this = Joined(subStrings, glue);
}

i32 String::Find(char c, i32 startPos, bool caseSensitive) const
{
    assert(startPos >= 0);

    const char* buffer = GetBuffer();
    i32 length = Length();

    if (caseSensitive)
    {
        for (i32 i = startPos; i < length; ++i)
        {
            if (buffer[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (i32 i = startPos; i < length; ++i)
        {
            if (tolower(buffer[i]) == c)
                return i;
        }
    }

    return NPOS;
}

i32 String::Find(const String& str, i32 startPos, bool caseSensitive) const
{
    assert(startPos >= 0);

    i32 length = Length();
    i32 strLength = str.Length();

    if (!strLength || strLength > length)
        return NPOS;

    const char* buffer = GetBuffer();
    const char* strBuffer = str.GetBuffer();

    char first = strBuffer[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (i32 i = startPos; i <= length - strLength; ++i)
    {
        char c = buffer[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            i32 skip = NPOS;
            bool found = true;
            for (i32 j = 1; j < strLength; ++j)
            {
                c = buffer[i + j];
                char d = strBuffer[j];
                if (!caseSensitive)
                {
                    c = (char)tolower(c);
                    d = (char)tolower(d);
                }

                if (skip == NPOS && c == first)
                    skip = i + j - 1;

                if (c != d)
                {
                    found = false;
                    if (skip != NPOS)
                        i = skip;
                    break;
                }
            }
            if (found)
                return i;
        }
    }

    return NPOS;
}

i32 String::FindLast(char c, i32 startPos, bool caseSensitive) const
{
    i32 length = Length();
    const char* buffer = GetBuffer();

    if (startPos == NPOS || startPos >= length)
        startPos = length - 1;

    if (caseSensitive)
    {
        for (i32 i = startPos; i >= 0; --i)
        {
            if (buffer[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (i32 i = startPos; i >= 0; --i)
        {
            if (tolower(buffer[i]) == c)
                return i;
        }
    }

    return NPOS;
}

i32 String::FindLast(const String& str, i32 startPos, bool caseSensitive) const
{
    i32 length = Length();
    i32 strLength = str.Length();

    if (!strLength || strLength > length)
        return NPOS;

    if (startPos == NPOS || startPos > length - strLength)
        startPos = length - strLength;

    const char* buffer = GetBuffer();
    const char* strBuffer = str.GetBuffer();

    char first = strBuffer[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (i32 i = startPos; i >= 0; --i)
    {
        char c = buffer[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            bool found = true;
            for (i32 j = 1; j < strLength; ++j)
            {
                c = buffer[i + j];
                char d = strBuffer[j];
                if (!caseSensitive)
                {
                    c = (char)tolower(c);
                    d = (char)tolower(d);
                }

                if (c != d)
                {
                    found = false;
                    break;
                }
            }
            if (found)
                return i;
        }
    }

    return NPOS;
}

bool String::StartsWith(const String& str, bool caseSensitive) const
{
    return Find(str, 0, caseSensitive) == 0;
}

bool String::EndsWith(const String& str, bool caseSensitive) const
{
    i32 pos = FindLast(str, Length() - 1, caseSensitive);
    return pos != NPOS && pos == Length() - str.Length();
}

int String::Compare(const String& str, bool caseSensitive) const
{
    return Compare(CString(), str.CString(), caseSensitive);
}

int String::Compare(const char* str, bool caseSensitive) const
{
    return Compare(CString(), str, caseSensitive);
}

void String::SetUTF8FromLatin1(const char* str)
{
    char temp[7];

    Clear();

    if (!str)
        return;

    while (*str)
    {
        char* dest = temp;
        EncodeUTF8(dest, (c32)*str++);
        *dest = 0;
        Append(temp);
    }
}

void String::SetUTF8FromWChar(const wchar_t* str)
{
    char temp[7];

    Clear();

    if (!str)
        return;

#ifdef _WIN32
    while (*str)
    {
        c32 unicodeChar = DecodeUTF16(str);
        char* dest = temp;
        EncodeUTF8(dest, unicodeChar);
        *dest = 0;
        Append(temp);
    }
#else
    while (*str)
    {
        char* dest = temp;
        EncodeUTF8(dest, (c32)*str++);
        *dest = 0;
        Append(temp);
    }
#endif
}

i32 String::LengthUTF8() const
{
    i32 ret = 0;

    const char* buffer = GetBuffer();

    const char* src = buffer;
    if (!src)
        return ret;
    const char* end = buffer + Length();

    while (src < end)
    {
        DecodeUTF8(src);
        ++ret;
    }

    return ret;
}

i32 String::ByteOffsetUTF8(i32 index) const
{
    i32 byteOffset = 0;
    i32 utfPos = 0;

    i32 length = Length();

    while (utfPos < index && byteOffset < length)
    {
        NextUTF8Char(byteOffset);
        ++utfPos;
    }

    return byteOffset;
}

c32 String::NextUTF8Char(i32& byteOffset) const
{
    const char* buffer = GetBuffer();

    const char* src = buffer + byteOffset;
    c32 ret = DecodeUTF8(src);
    byteOffset = (i32)(src - buffer);

    return ret;
}

c32 String::AtUTF8(i32 index) const
{
    i32 byteOffset = ByteOffsetUTF8(index);
    return NextUTF8Char(byteOffset);
}

void String::ReplaceUTF8(i32 index, c32 unicodeChar)
{
    i32 utfPos = 0;
    i32 byteOffset = 0;
    i32 length = Length();

    while (utfPos < index && byteOffset < length)
    {
        NextUTF8Char(byteOffset);
        ++utfPos;
    }

    if (utfPos < index)
        return;

    i32 beginCharPos = byteOffset;
    NextUTF8Char(byteOffset);

    char temp[7];
    char* dest = temp;
    EncodeUTF8(dest, unicodeChar);
    *dest = 0;

    Replace(beginCharPos, byteOffset - beginCharPos, temp, (i32)(dest - temp));
}

String& String::AppendUTF8(c32 unicodeChar)
{
    char temp[7];
    char* dest = temp;
    EncodeUTF8(dest, unicodeChar);
    *dest = 0;
    return Append(temp);
}

String String::SubstringUTF8(i32 pos) const
{
    i32 utf8Length = LengthUTF8();
    i32 byteOffset = ByteOffsetUTF8(pos);
    String ret;

    while (pos < utf8Length)
    {
        ret.AppendUTF8(NextUTF8Char(byteOffset));
        ++pos;
    }

    return ret;
}

String String::SubstringUTF8(i32 pos, i32 length) const
{
    i32 utf8Length = LengthUTF8();
    i32 byteOffset = ByteOffsetUTF8(pos);
    i32 endPos = pos + length;
    String ret;

    while (pos < endPos && pos < utf8Length)
    {
        ret.AppendUTF8(NextUTF8Char(byteOffset));
        ++pos;
    }

    return ret;
}

void String::EncodeUTF8(char*& dest, c32 unicodeChar)
{
    if (unicodeChar < 0x80)
        *dest++ = (char)unicodeChar;
    else if (unicodeChar < 0x800)
    {
        dest[0] = (char)(0xc0u | ((unicodeChar >> 6u) & 0x1fu));
        dest[1] = (char)(0x80u | (unicodeChar & 0x3fu));
        dest += 2;
    }
    else if (unicodeChar < 0x10000)
    {
        dest[0] = (char)(0xe0u | ((unicodeChar >> 12u) & 0xfu));
        dest[1] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
        dest[2] = (char)(0x80u | (unicodeChar & 0x3fu));
        dest += 3;
    }
    else if (unicodeChar < 0x200000)
    {
        dest[0] = (char)(0xf0u | ((unicodeChar >> 18u) & 0x7u));
        dest[1] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
        dest[2] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
        dest[3] = (char)(0x80u | (unicodeChar & 0x3fu));
        dest += 4;
    }
    else if (unicodeChar < 0x4000000)
    {
        dest[0] = (char)(0xf8u | ((unicodeChar >> 24u) & 0x3u));
        dest[1] = (char)(0x80u | ((unicodeChar >> 18u) & 0x3fu));
        dest[2] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
        dest[3] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
        dest[4] = (char)(0x80u | (unicodeChar & 0x3fu));
        dest += 5;
    }
    else
    {
        dest[0] = (char)(0xfcu | ((unicodeChar >> 30u) & 0x1u));
        dest[1] = (char)(0x80u | ((unicodeChar >> 24u) & 0x3fu));
        dest[2] = (char)(0x80u | ((unicodeChar >> 18u) & 0x3fu));
        dest[3] = (char)(0x80u | ((unicodeChar >> 12u) & 0x3fu));
        dest[4] = (char)(0x80u | ((unicodeChar >> 6u) & 0x3fu));
        dest[5] = (char)(0x80u | (unicodeChar & 0x3fu));
        dest += 6;
    }
}

#define GET_NEXT_CONTINUATION_BYTE(ptr) *(ptr); if ((u8)*(ptr) < 0x80 || (u8)*(ptr) >= 0xc0) return '?'; else ++(ptr);

c32 String::DecodeUTF8(const char*& src)
{
    if (src == nullptr)
        return 0;

    u8 char1 = *src++;

    // Check if we are in the middle of a UTF8 character
    if (char1 >= 0x80 && char1 < 0xc0)
    {
        while ((u8)*src >= 0x80 && (u8)*src < 0xc0)
            ++src;
        return '?';
    }

    if (char1 < 0x80)
        return char1;
    else if (char1 < 0xe0)
    {
        u8 char2 = GET_NEXT_CONTINUATION_BYTE(src);
        return (c32)((char2 & 0x3fu) | ((char1 & 0x1fu) << 6u));
    }
    else if (char1 < 0xf0)
    {
        u8 char2 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char3 = GET_NEXT_CONTINUATION_BYTE(src);
        return (c32)((char3 & 0x3fu) | ((char2 & 0x3fu) << 6u) | ((char1 & 0xfu) << 12u));
    }
    else if (char1 < 0xf8)
    {
        u8 char2 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char3 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char4 = GET_NEXT_CONTINUATION_BYTE(src);
        return (c32)((char4 & 0x3fu) | ((char3 & 0x3fu) << 6u) | ((char2 & 0x3fu) << 12u) | ((char1 & 0x7u) << 18u));
    }
    else if (char1 < 0xfc)
    {
        u8 char2 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char3 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char4 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char5 = GET_NEXT_CONTINUATION_BYTE(src);
        return (c32)((char5 & 0x3fu) | ((char4 & 0x3fu) << 6u) | ((char3 & 0x3fu) << 12u) | ((char2 & 0x3fu) << 18u) |
                          ((char1 & 0x3u) << 24u));
    }
    else
    {
        u8 char2 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char3 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char4 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char5 = GET_NEXT_CONTINUATION_BYTE(src);
        u8 char6 = GET_NEXT_CONTINUATION_BYTE(src);
        return (c32)((char6 & 0x3fu) | ((char5 & 0x3fu) << 6u) | ((char4 & 0x3fu) << 12u) | ((char3 & 0x3fu) << 18u) |
                          ((char2 & 0x3fu) << 24u) | ((char1 & 0x1u) << 30u));
    }
}

#ifdef _WIN32
void String::EncodeUTF16(wchar_t*& dest, c32 unicodeChar)
{
    if (unicodeChar < 0x10000)
        *dest++ = (wchar_t)unicodeChar;
    else
    {
        unicodeChar -= 0x10000;
        *dest++ = 0xd800 | ((unicodeChar >> 10) & 0x3ff);
        *dest++ = 0xdc00 | (unicodeChar & 0x3ff);
    }
}

c32 String::DecodeUTF16(const wchar_t*& src)
{
    if (src == nullptr)
        return 0;

    u16 word1 = *src++;

    // Check if we are at a low surrogate
    if (word1 >= 0xdc00 && word1 < 0xe000)
    {
        while (*src >= 0xdc00 && *src < 0xe000)
            ++src;
        return '?';
    }

    if (word1 < 0xd800 || word1 >= 0xe000)
        return word1;
    else
    {
        u16 word2 = *src++;
        if (word2 < 0xdc00 || word2 >= 0xe000)
        {
            --src;
            return '?';
        }
        else
            return (((word1 & 0x3ff) << 10) | (word2 & 0x3ff)) + 0x10000;
    }
}
#endif

Vector<String> String::Split(const char* str, char separator, bool keepEmptyStrings)
{
    Vector<String> ret;
    const char* strEnd = str + String::CStringLength(str);

    for (const char* splitEnd = str; splitEnd != strEnd; ++splitEnd)
    {
        if (*splitEnd == separator)
        {
            const ptrdiff_t splitLen = splitEnd - str;
            if (splitLen > 0 || keepEmptyStrings)
                ret.Push(String(str, (i32)splitLen));
            str = splitEnd + 1;
        }
    }

    const ptrdiff_t splitLen = strEnd - str;
    if (splitLen > 0 || keepEmptyStrings)
        ret.Push(String(str, (i32)splitLen));

    return ret;
}

String String::Joined(const Vector<String>& subStrings, const String& glue)
{
    if (subStrings.Empty())
        return String();

    String joinedString(subStrings[0]);
    for (i32 i = 1; i < subStrings.Size(); ++i)
        joinedString.Append(glue).Append(subStrings[i]);

    return joinedString;
}

String& String::AppendWithFormat(const char* formatString, ...)
{
    va_list args;
    va_start(args, formatString);
    AppendWithFormatArgs(formatString, args);
    va_end(args);
    return *this;
}

String& String::AppendWithFormatArgs(const char* formatString, va_list args)
{
    int pos = 0, lastPos = 0;
    i32 length = (i32)strlen(formatString);

    while (true)
    {
        // Scan the format string and find %a argument where a is one of d, f, s ...
        while (pos < length && formatString[pos] != '%') pos++;
        Append(formatString + lastPos, (i32)(pos - lastPos));
        if (pos >= length)
            return *this;

        char format = formatString[pos + 1];
        pos += 2;
        lastPos = pos;

        switch (format)
        {
        // Integer
        case 'd':
        case 'i':
            {
                int arg = va_arg(args, int);
                Append(String(arg));
                break;
            }

        // Unsigned
        case 'u':
            {
                unsigned arg = va_arg(args, unsigned);
                Append(String(arg));
                break;
            }

        // Unsigned long
        case 'l':
            {
                unsigned long arg = va_arg(args, unsigned long);
                Append(String(arg));
                break;
            }

        // Real
        case 'f':
            {
                double arg = va_arg(args, double);
                Append(String(arg));
                break;
            }

        // Character
        case 'c':
            {
                int arg = va_arg(args, int);
                Append((char)arg);
                break;
            }

        // C string
        case 's':
            {
                char* arg = va_arg(args, char*);
                Append(arg);
                break;
            }

        // Hex
        case 'x':
            {
                char buf[CONVERSION_BUFFER_LENGTH];
                int arg = va_arg(args, int);
                int arglen = ::sprintf(buf, "%x", arg);
                Append(buf, arglen);
                break;
            }

        // Pointer
        case 'p':
            {
                char buf[CONVERSION_BUFFER_LENGTH];
                int arg = va_arg(args, int);
                int arglen = ::sprintf(buf, "%p", reinterpret_cast<void*>(arg));
                Append(buf, arglen);
                break;
            }

        case '%':
            {
                Append("%", 1);
                break;
            }

        default:
            URHO3D_LOGWARNINGF("Unsupported format specifier: '%c'", format);
            break;
        }
    }
}

int String::Compare(const char* lhs, const char* rhs, bool caseSensitive)
{
    if (!lhs || !rhs)
        return lhs ? 1 : (rhs ? -1 : 0);

    if (caseSensitive)
        return strcmp(lhs, rhs);
    else
    {
        for (;;)
        {
            auto l = (char)tolower(*lhs);
            auto r = (char)tolower(*rhs);
            if (!l || !r)
                return l ? 1 : (r ? -1 : 0);
            if (l < r)
                return -1;
            if (l > r)
                return 1;

            ++lhs;
            ++rhs;
        }
    }
}

void String::Replace(i32 pos, i32 length, const char* srcStart, i32 srcLength)
{
    i32 delta = srcLength - length;
    i32 thisLength = Length();

    if (pos + length < thisLength)
    {
        if (delta < 0)
        {
            MoveRange(pos + srcLength, pos + length, thisLength - pos - length);
            Resize(thisLength + delta);
        }
        if (delta > 0)
        {
            Resize(thisLength + delta);
            thisLength = Length();
            MoveRange(pos + srcLength, pos + length, thisLength - pos - length - delta);
        }
    }
    else
    {
        Resize(thisLength + delta);
    }

    CopyChars(GetBuffer() + pos, srcStart, srcLength);
}

WString::WString() :
    length_(0),
    buffer_(nullptr)
{
}

WString::WString(const String& str) :
    length_(0),
    buffer_(nullptr)
{
#ifdef _WIN32
    i32 neededSize = 0;
    wchar_t temp[3];

    i32 byteOffset = 0;
    while (byteOffset < str.Length())
    {
        wchar_t* dest = temp;
        String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
        neededSize += (i32)(dest - temp);
    }

    Resize(neededSize);

    byteOffset = 0;
    wchar_t* dest = buffer_;
    while (byteOffset < str.Length())
        String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
#else
    Resize(str.LengthUTF8());

    i32 byteOffset = 0;
    wchar_t* dest = buffer_;
    while (byteOffset < str.Length())
        *dest++ = (wchar_t)str.NextUTF8Char(byteOffset);
#endif
}

WString::~WString()
{
    delete[] buffer_;
}

void WString::Resize(i32 newLength)
{
    if (!newLength)
    {
        delete[] buffer_;
        buffer_ = nullptr;
        length_ = 0;
    }
    else
    {
        auto* newBuffer = new wchar_t[newLength + 1];
        if (buffer_)
        {
            i32 copyLength = length_ < newLength ? length_ : newLength;
            memcpy(newBuffer, buffer_, copyLength * sizeof(wchar_t));
            delete[] buffer_;
        }
        newBuffer[newLength] = 0;
        buffer_ = newBuffer;
        length_ = newLength;
    }
}

}
