// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:6293)
#endif

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

String::String(char value, unsigned length)
    : String()
{
    Resize(length);
    char* buffer = GetBuffer();
    for (unsigned i = 0; i < length; ++i)
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
    unsigned length = Length();
    char* buffer = GetBuffer();

    if (caseSensitive)
    {
        for (unsigned i = 0; i < length; ++i)
        {
            if (buffer[i] == replaceThis)
                buffer[i] = replaceWith;
        }
    }
    else
    {
        replaceThis = (char)tolower(replaceThis);
        for (unsigned i = 0; i < length; ++i)
        {
            if (tolower(buffer[i]) == replaceThis)
                buffer[i] = replaceWith;
        }
    }
}

void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive)
{
    unsigned nextPos = 0;

    unsigned length = Length();
    unsigned replaceThisLength = replaceThis.Length();
    unsigned replaceWithLength = replaceWith.Length();

    while (nextPos < length)
    {
        unsigned pos = Find(replaceThis, nextPos, caseSensitive);
        if (pos == NPOS)
            break;
        Replace(pos, replaceThisLength, replaceWith);
        nextPos = pos + replaceWithLength;
    }
}

void String::Replace(unsigned pos, unsigned length, const String& replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > Length())
        return;

    Replace(pos, length, replaceWith.GetBuffer(), replaceWith.Length());
}

void String::Replace(unsigned pos, unsigned length, const char* replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > Length())
        return;

    Replace(pos, length, replaceWith, CStringLength(replaceWith));
}

String::Iterator String::Replace(const String::Iterator& start, const String::Iterator& end, const String& replaceWith)
{
    unsigned pos = (unsigned)(start - Begin());
    if (pos >= Length())
        return End();
    auto length = (unsigned)(end - start);
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

String& String::Append(const char* str, unsigned length)
{
    if (str)
    {
        unsigned oldLength = Length();
        Resize(oldLength + length);
        CopyChars(&GetBuffer()[oldLength], str, length);
    }
    return *this;
}

void String::Insert(unsigned pos, const String& str)
{
    unsigned length = Length();

    if (pos > length)
        pos = length;

    if (pos == length)
        (*this) += str;
    else
        Replace(pos, 0, str);
}

void String::Insert(unsigned pos, char c)
{
    unsigned length = Length();

    if (pos > length)
        pos = length;

    if (pos == length)
    {
        (*this) += c;
    }
    else
    {
        unsigned oldLength = length;
        Resize(length + 1);
        MoveRange(pos + 1, pos, oldLength - pos);
        GetBuffer()[pos] = c;
    }
}

String::Iterator String::Insert(const String::Iterator& dest, const String& str)
{
    unsigned length = Length();

    unsigned pos = (unsigned)(dest - Begin());
    if (pos > length)
        pos = length;
    Insert(pos, str);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, const String::Iterator& start, const String::Iterator& end)
{
    unsigned pos = (unsigned)(dest - Begin());
    if (pos > Length())
        pos = Length();
    unsigned length = (unsigned)(end - start);
    Replace(pos, 0, &(*start), length);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, char c)
{
    unsigned length = Length();

    unsigned pos = (unsigned)(dest - Begin());
    if (pos > length)
        pos = length;
    Insert(pos, c);

    return Begin() + pos;
}

void String::Erase(unsigned pos, unsigned length)
{
    Replace(pos, length, String::EMPTY);
}

String::Iterator String::Erase(const String::Iterator& it)
{
    unsigned pos = (unsigned)(it - Begin());
    if (pos >= Length())
        return End();
    Erase(pos);

    return Begin() + pos;
}

String::Iterator String::Erase(const String::Iterator& start, const String::Iterator& end)
{
    unsigned pos = (unsigned)(start - Begin());
    if (pos >= Length())
        return End();
    unsigned length = (unsigned)(end - start);
    Erase(pos, length);

    return Begin() + pos;
}

void String::Resize(unsigned newLength)
{
    unsigned capacity = Capacity();

    if (newLength && capacity < newLength + 1) // Need to increase capacity
    {
        // Increase the capacity with half each time it is exceeded
        while (capacity < newLength + 1)
            capacity += (capacity + 1) >> 1u;

        // SHORT_STRING_CAPACITY is minimal possible capacity
        assert(capacity > SHORT_STRING_CAPACITY);

        char* newBuffer = new char[capacity];

        // Move the existing data to the new buffer
        unsigned oldLength = Length();
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

void String::Reserve(unsigned newCapacity)
{
    unsigned length = Length();

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

String String::Substring(unsigned pos) const
{
    unsigned length = Length();

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

String String::Substring(unsigned pos, unsigned length) const
{
    unsigned thisLength = Length();

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
    unsigned trimStart = 0;
    unsigned trimEnd = Length();

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
    unsigned retLength = ret.Length();
    char* retBuffer = ret.GetBuffer();
    for (unsigned i = 0; i < retLength; ++i)
        retBuffer[i] = (char)tolower(buffer[i]);

    return ret;
}

String String::ToUpper() const
{
    String ret(*this);
    const char* buffer = GetBuffer();
    unsigned retLength = ret.Length();
    char* retBuffer = ret.GetBuffer();
    for (unsigned i = 0; i < retLength; ++i)
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

unsigned String::Find(char c, unsigned startPos, bool caseSensitive) const
{
    const char* buffer = GetBuffer();
    unsigned length = Length();

    if (caseSensitive)
    {
        for (unsigned i = startPos; i < length; ++i)
        {
            if (buffer[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (unsigned i = startPos; i < length; ++i)
        {
            if (tolower(buffer[i]) == c)
                return i;
        }
    }

    return NPOS;
}

unsigned String::Find(const String& str, unsigned startPos, bool caseSensitive) const
{
    unsigned length = Length();
    unsigned strLength = str.Length();

    if (!strLength || strLength > length)
        return NPOS;

    const char* buffer = GetBuffer();
    const char* strBuffer = str.GetBuffer();

    char first = strBuffer[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (unsigned i = startPos; i <= length - strLength; ++i)
    {
        char c = buffer[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            unsigned skip = NPOS;
            bool found = true;
            for (unsigned j = 1; j < strLength; ++j)
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

unsigned String::FindLast(char c, unsigned startPos, bool caseSensitive) const
{
    unsigned length = Length();
    const char* buffer = GetBuffer();

    if (startPos >= length)
        startPos = length - 1;

    if (caseSensitive)
    {
        for (unsigned i = startPos; i < length; --i)
        {
            if (buffer[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (unsigned i = startPos; i < length; --i)
        {
            if (tolower(buffer[i]) == c)
                return i;
        }
    }

    return NPOS;
}

unsigned String::FindLast(const String& str, unsigned startPos, bool caseSensitive) const
{
    unsigned length = Length();
    unsigned strLength = str.Length();

    if (!strLength || strLength > length)
        return NPOS;

    if (startPos > length - strLength)
        startPos = length - strLength;

    const char* buffer = GetBuffer();
    const char* strBuffer = str.GetBuffer();

    char first = strBuffer[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (unsigned i = startPos; i < length; --i)
    {
        char c = buffer[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            bool found = true;
            for (unsigned j = 1; j < strLength; ++j)
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
    unsigned pos = FindLast(str, Length() - 1, caseSensitive);
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
        EncodeUTF8(dest, (unsigned)*str++);
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
        unsigned unicodeChar = DecodeUTF16(str);
        char* dest = temp;
        EncodeUTF8(dest, unicodeChar);
        *dest = 0;
        Append(temp);
    }
#else
    while (*str)
    {
        char* dest = temp;
        EncodeUTF8(dest, (unsigned)*str++);
        *dest = 0;
        Append(temp);
    }
#endif
}

unsigned String::LengthUTF8() const
{
    unsigned ret = 0;

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

unsigned String::ByteOffsetUTF8(unsigned index) const
{
    unsigned byteOffset = 0;
    unsigned utfPos = 0;

    unsigned length = Length();

    while (utfPos < index && byteOffset < length)
    {
        NextUTF8Char(byteOffset);
        ++utfPos;
    }

    return byteOffset;
}

unsigned String::NextUTF8Char(unsigned& byteOffset) const
{
    const char* buffer = GetBuffer();

    const char* src = buffer + byteOffset;
    unsigned ret = DecodeUTF8(src);
    byteOffset = (unsigned)(src - buffer);

    return ret;
}

unsigned String::AtUTF8(unsigned index) const
{
    unsigned byteOffset = ByteOffsetUTF8(index);
    return NextUTF8Char(byteOffset);
}

void String::ReplaceUTF8(unsigned index, unsigned unicodeChar)
{
    unsigned utfPos = 0;
    unsigned byteOffset = 0;
    unsigned length = Length();

    while (utfPos < index && byteOffset < length)
    {
        NextUTF8Char(byteOffset);
        ++utfPos;
    }

    if (utfPos < index)
        return;

    unsigned beginCharPos = byteOffset;
    NextUTF8Char(byteOffset);

    char temp[7];
    char* dest = temp;
    EncodeUTF8(dest, unicodeChar);
    *dest = 0;

    Replace(beginCharPos, byteOffset - beginCharPos, temp, (unsigned)(dest - temp));
}

String& String::AppendUTF8(unsigned unicodeChar)
{
    char temp[7];
    char* dest = temp;
    EncodeUTF8(dest, unicodeChar);
    *dest = 0;
    return Append(temp);
}

String String::SubstringUTF8(unsigned pos) const
{
    unsigned utf8Length = LengthUTF8();
    unsigned byteOffset = ByteOffsetUTF8(pos);
    String ret;

    while (pos < utf8Length)
    {
        ret.AppendUTF8(NextUTF8Char(byteOffset));
        ++pos;
    }

    return ret;
}

String String::SubstringUTF8(unsigned pos, unsigned length) const
{
    unsigned utf8Length = LengthUTF8();
    unsigned byteOffset = ByteOffsetUTF8(pos);
    unsigned endPos = pos + length;
    String ret;

    while (pos < endPos && pos < utf8Length)
    {
        ret.AppendUTF8(NextUTF8Char(byteOffset));
        ++pos;
    }

    return ret;
}

void String::EncodeUTF8(char*& dest, unsigned unicodeChar)
{
    if (unicodeChar < 0x80)
        *dest++ = unicodeChar;
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

#define GET_NEXT_CONTINUATION_BYTE(ptr) *(ptr); if ((unsigned char)*(ptr) < 0x80 || (unsigned char)*(ptr) >= 0xc0) return '?'; else ++(ptr);

unsigned String::DecodeUTF8(const char*& src)
{
    if (src == nullptr)
        return 0;

    unsigned char char1 = *src++;

    // Check if we are in the middle of a UTF8 character
    if (char1 >= 0x80 && char1 < 0xc0)
    {
        while ((unsigned char)*src >= 0x80 && (unsigned char)*src < 0xc0)
            ++src;
        return '?';
    }

    if (char1 < 0x80)
        return char1;
    else if (char1 < 0xe0)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char2 & 0x3fu) | ((char1 & 0x1fu) << 6u));
    }
    else if (char1 < 0xf0)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char3 & 0x3fu) | ((char2 & 0x3fu) << 6u) | ((char1 & 0xfu) << 12u));
    }
    else if (char1 < 0xf8)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char4 & 0x3fu) | ((char3 & 0x3fu) << 6u) | ((char2 & 0x3fu) << 12u) | ((char1 & 0x7u) << 18u));
    }
    else if (char1 < 0xfc)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char5 & 0x3fu) | ((char4 & 0x3fu) << 6u) | ((char3 & 0x3fu) << 12u) | ((char2 & 0x3fu) << 18u) |
                          ((char1 & 0x3u) << 24u));
    }
    else
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char6 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char6 & 0x3fu) | ((char5 & 0x3fu) << 6u) | ((char4 & 0x3fu) << 12u) | ((char3 & 0x3fu) << 18u) |
                          ((char2 & 0x3fu) << 24u) | ((char1 & 0x1u) << 30u));
    }
}

#ifdef _WIN32
void String::EncodeUTF16(wchar_t*& dest, unsigned unicodeChar)
{
    if (unicodeChar < 0x10000)
        *dest++ = unicodeChar;
    else
    {
        unicodeChar -= 0x10000;
        *dest++ = 0xd800 | ((unicodeChar >> 10) & 0x3ff);
        *dest++ = 0xdc00 | (unicodeChar & 0x3ff);
    }
}

unsigned String::DecodeUTF16(const wchar_t*& src)
{
    if (src == nullptr)
        return 0;

    unsigned short word1 = *src++;

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
        unsigned short word2 = *src++;
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
                ret.Push(String(str, splitLen));
            str = splitEnd + 1;
        }
    }

    const ptrdiff_t splitLen = strEnd - str;
    if (splitLen > 0 || keepEmptyStrings)
        ret.Push(String(str, splitLen));

    return ret;
}

String String::Joined(const Vector<String>& subStrings, const String& glue)
{
    if (subStrings.Empty())
        return String();

    String joinedString(subStrings[0]);
    for (unsigned i = 1; i < subStrings.Size(); ++i)
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
    auto length = (int)strlen(formatString);

    while (true)
    {
        // Scan the format string and find %a argument where a is one of d, f, s ...
        while (pos < length && formatString[pos] != '%') pos++;
        Append(formatString + lastPos, (unsigned)(pos - lastPos));
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
                Append(buf, (unsigned)arglen);
                break;
            }

        // Pointer
        case 'p':
            {
                char buf[CONVERSION_BUFFER_LENGTH];
                int arg = va_arg(args, int);
                int arglen = ::sprintf(buf, "%p", reinterpret_cast<void*>(arg));
                Append(buf, (unsigned)arglen);
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

void String::Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength)
{
    int delta = (int)srcLength - (int)length;
    unsigned thisLength = Length();

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
    unsigned neededSize = 0;
    wchar_t temp[3];

    unsigned byteOffset = 0;
    while (byteOffset < str.Length())
    {
        wchar_t* dest = temp;
        String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
        neededSize += dest - temp;
    }

    Resize(neededSize);

    byteOffset = 0;
    wchar_t* dest = buffer_;
    while (byteOffset < str.Length())
        String::EncodeUTF16(dest, str.NextUTF8Char(byteOffset));
#else
    Resize(str.LengthUTF8());

    unsigned byteOffset = 0;
    wchar_t* dest = buffer_;
    while (byteOffset < str.Length())
        *dest++ = (wchar_t)str.NextUTF8Char(byteOffset);
#endif
}

WString::~WString()
{
    delete[] buffer_;
}

void WString::Resize(unsigned newLength)
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
            unsigned copyLength = length_ < newLength ? length_ : newLength;
            memcpy(newBuffer, buffer_, copyLength * sizeof(wchar_t));
            delete[] buffer_;
        }
        newBuffer[newLength] = 0;
        buffer_ = newBuffer;
        length_ = newLength;
    }
}

}
