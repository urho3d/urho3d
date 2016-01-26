//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../IO/Log.h"

#include <cstdio>

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:6293)
#endif

namespace Urho3D
{

char String::endZero = 0;

const String String::EMPTY;

String::String(const WString& str) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    SetUTF8FromWChar(str.CString());
}

String::String(int value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    *this = tempBuffer;
}

String::String(short value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d", value);
    *this = tempBuffer;
}

String::String(long value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%ld", value);
    *this = tempBuffer;
}

String::String(long long value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%lld", value);
    *this = tempBuffer;
}

String::String(unsigned value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    *this = tempBuffer;
}

String::String(unsigned short value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%u", value);
    *this = tempBuffer;
}

String::String(unsigned long value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%lu", value);
    *this = tempBuffer;
}

String::String(unsigned long long value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%llu", value);
    *this = tempBuffer;
}

String::String(float value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%g", value);
    *this = tempBuffer;
}

String::String(double value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%.15g", value);
    *this = tempBuffer;
}

String::String(bool value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    if (value)
        *this = "true";
    else
        *this = "false";
}

String::String(char value) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    Resize(1);
    buffer_[0] = value;
}

String::String(char value, unsigned length) :
    length_(0),
    capacity_(0),
    buffer_(&endZero)
{
    Resize(length);
    for (unsigned i = 0; i < length; ++i)
        buffer_[i] = value;
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
    if (caseSensitive)
    {
        for (unsigned i = 0; i < length_; ++i)
        {
            if (buffer_[i] == replaceThis)
                buffer_[i] = replaceWith;
        }
    }
    else
    {
        replaceThis = (char)tolower(replaceThis);
        for (unsigned i = 0; i < length_; ++i)
        {
            if (tolower(buffer_[i]) == replaceThis)
                buffer_[i] = replaceWith;
        }
    }
}

void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive)
{
    unsigned nextPos = 0;

    while (nextPos < length_)
    {
        unsigned pos = Find(replaceThis, nextPos, caseSensitive);
        if (pos == NPOS)
            break;
        Replace(pos, replaceThis.length_, replaceWith);
        nextPos = pos + replaceWith.length_;
    }
}

void String::Replace(unsigned pos, unsigned length, const String& replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > length_)
        return;

    Replace(pos, length, replaceWith.buffer_, replaceWith.length_);
}

void String::Replace(unsigned pos, unsigned length, const char* replaceWith)
{
    // If substring is illegal, do nothing
    if (pos + length > length_)
        return;

    Replace(pos, length, replaceWith, CStringLength(replaceWith));
}

String::Iterator String::Replace(const String::Iterator& start, const String::Iterator& end, const String& replaceWith)
{
    unsigned pos = (unsigned)(start - Begin());
    if (pos >= length_)
        return End();
    unsigned length = (unsigned)(end - start);
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
        unsigned oldLength = length_;
        Resize(oldLength + length);
        CopyChars(&buffer_[oldLength], str, length);
    }
    return *this;
}

void String::Insert(unsigned pos, const String& str)
{
    if (pos > length_)
        pos = length_;

    if (pos == length_)
        (*this) += str;
    else
        Replace(pos, 0, str);
}

void String::Insert(unsigned pos, char c)
{
    if (pos > length_)
        pos = length_;

    if (pos == length_)
        (*this) += c;
    else
    {
        unsigned oldLength = length_;
        Resize(length_ + 1);
        MoveRange(pos + 1, pos, oldLength - pos);
        buffer_[pos] = c;
    }
}

String::Iterator String::Insert(const String::Iterator& dest, const String& str)
{
    unsigned pos = (unsigned)(dest - Begin());
    if (pos > length_)
        pos = length_;
    Insert(pos, str);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, const String::Iterator& start, const String::Iterator& end)
{
    unsigned pos = (unsigned)(dest - Begin());
    if (pos > length_)
        pos = length_;
    unsigned length = (unsigned)(end - start);
    Replace(pos, 0, &(*start), length);

    return Begin() + pos;
}

String::Iterator String::Insert(const String::Iterator& dest, char c)
{
    unsigned pos = (unsigned)(dest - Begin());
    if (pos > length_)
        pos = length_;
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
    if (pos >= length_)
        return End();
    Erase(pos);

    return Begin() + pos;
}

String::Iterator String::Erase(const String::Iterator& start, const String::Iterator& end)
{
    unsigned pos = (unsigned)(start - Begin());
    if (pos >= length_)
        return End();
    unsigned length = (unsigned)(end - start);
    Erase(pos, length);

    return Begin() + pos;
}

void String::Resize(unsigned newLength)
{
    if (!capacity_)
    {
        // If zero length requested, do not allocate buffer yet
        if (!newLength)
            return;

        // Calculate initial capacity
        capacity_ = newLength + 1;
        if (capacity_ < MIN_CAPACITY)
            capacity_ = MIN_CAPACITY;

        buffer_ = new char[capacity_];
    }
    else
    {
        if (newLength && capacity_ < newLength + 1)
        {
            // Increase the capacity with half each time it is exceeded
            while (capacity_ < newLength + 1)
                capacity_ += (capacity_ + 1) >> 1;

            char* newBuffer = new char[capacity_];
            // Move the existing data to the new buffer, then delete the old buffer
            if (length_)
                CopyChars(newBuffer, buffer_, length_);
            delete[] buffer_;

            buffer_ = newBuffer;
        }
    }

    buffer_[newLength] = 0;
    length_ = newLength;
}

void String::Reserve(unsigned newCapacity)
{
    if (newCapacity < length_ + 1)
        newCapacity = length_ + 1;
    if (newCapacity == capacity_)
        return;

    char* newBuffer = new char[newCapacity];
    // Move the existing data to the new buffer, then delete the old buffer
    CopyChars(newBuffer, buffer_, length_ + 1);
    if (capacity_)
        delete[] buffer_;

    capacity_ = newCapacity;
    buffer_ = newBuffer;
}

void String::Compact()
{
    if (capacity_)
        Reserve(length_ + 1);
}

void String::Clear()
{
    Resize(0);
}

void String::Swap(String& str)
{
    Urho3D::Swap(length_, str.length_);
    Urho3D::Swap(capacity_, str.capacity_);
    Urho3D::Swap(buffer_, str.buffer_);
}

String String::Substring(unsigned pos) const
{
    if (pos < length_)
    {
        String ret;
        ret.Resize(length_ - pos);
        CopyChars(ret.buffer_, buffer_ + pos, ret.length_);

        return ret;
    }
    else
        return String();
}

String String::Substring(unsigned pos, unsigned length) const
{
    if (pos < length_)
    {
        String ret;
        if (pos + length > length_)
            length = length_ - pos;
        ret.Resize(length);
        CopyChars(ret.buffer_, buffer_ + pos, ret.length_);

        return ret;
    }
    else
        return String();
}

String String::Trimmed() const
{
    unsigned trimStart = 0;
    unsigned trimEnd = length_;

    while (trimStart < trimEnd)
    {
        char c = buffer_[trimStart];
        if (c != ' ' && c != 9)
            break;
        ++trimStart;
    }
    while (trimEnd > trimStart)
    {
        char c = buffer_[trimEnd - 1];
        if (c != ' ' && c != 9)
            break;
        --trimEnd;
    }

    return Substring(trimStart, trimEnd - trimStart);
}

String String::ToLower() const
{
    String ret(*this);
    for (unsigned i = 0; i < ret.length_; ++i)
        ret[i] = (char)tolower(buffer_[i]);

    return ret;
}

String String::ToUpper() const
{
    String ret(*this);
    for (unsigned i = 0; i < ret.length_; ++i)
        ret[i] = (char)toupper(buffer_[i]);

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
    if (caseSensitive)
    {
        for (unsigned i = startPos; i < length_; ++i)
        {
            if (buffer_[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (unsigned i = startPos; i < length_; ++i)
        {
            if (tolower(buffer_[i]) == c)
                return i;
        }
    }

    return NPOS;
}

unsigned String::Find(const String& str, unsigned startPos, bool caseSensitive) const
{
    if (!str.length_ || str.length_ > length_)
        return NPOS;

    char first = str.buffer_[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (unsigned i = startPos; i <= length_ - str.length_; ++i)
    {
        char c = buffer_[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            unsigned skip = NPOS;
            bool found = true;
            for (unsigned j = 1; j < str.length_; ++j)
            {
                c = buffer_[i + j];
                char d = str.buffer_[j];
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
    if (startPos >= length_)
        startPos = length_ - 1;

    if (caseSensitive)
    {
        for (unsigned i = startPos; i < length_; --i)
        {
            if (buffer_[i] == c)
                return i;
        }
    }
    else
    {
        c = (char)tolower(c);
        for (unsigned i = startPos; i < length_; --i)
        {
            if (tolower(buffer_[i]) == c)
                return i;
        }
    }

    return NPOS;
}

unsigned String::FindLast(const String& str, unsigned startPos, bool caseSensitive) const
{
    if (!str.length_ || str.length_ > length_)
        return NPOS;
    if (startPos > length_ - str.length_)
        startPos = length_ - str.length_;

    char first = str.buffer_[0];
    if (!caseSensitive)
        first = (char)tolower(first);

    for (unsigned i = startPos; i < length_; --i)
    {
        char c = buffer_[i];
        if (!caseSensitive)
            c = (char)tolower(c);

        if (c == first)
        {
            bool found = true;
            for (unsigned j = 1; j < str.length_; ++j)
            {
                c = buffer_[i + j];
                char d = str.buffer_[j];
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

    const char* src = buffer_;
    if (!src)
        return ret;
    const char* end = buffer_ + length_;

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

    while (utfPos < index && byteOffset < length_)
    {
        NextUTF8Char(byteOffset);
        ++utfPos;
    }

    return byteOffset;
}

unsigned String::NextUTF8Char(unsigned& byteOffset) const
{
    if (!buffer_)
        return 0;

    const char* src = buffer_ + byteOffset;
    unsigned ret = DecodeUTF8(src);
    byteOffset = (unsigned)(src - buffer_);

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

    while (utfPos < index && byteOffset < length_)
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
        dest[0] = (char)(0xc0 | ((unicodeChar >> 6) & 0x1f));
        dest[1] = (char)(0x80 | (unicodeChar & 0x3f));
        dest += 2;
    }
    else if (unicodeChar < 0x10000)
    {
        dest[0] = (char)(0xe0 | ((unicodeChar >> 12) & 0xf));
        dest[1] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
        dest[2] = (char)(0x80 | (unicodeChar & 0x3f));
        dest += 3;
    }
    else if (unicodeChar < 0x200000)
    {
        dest[0] = (char)(0xf0 | ((unicodeChar >> 18) & 0x7));
        dest[1] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
        dest[2] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
        dest[3] = (char)(0x80 | (unicodeChar & 0x3f));
        dest += 4;
    }
    else if (unicodeChar < 0x4000000)
    {
        dest[0] = (char)(0xf8 | ((unicodeChar >> 24) & 0x3));
        dest[1] = (char)(0x80 | ((unicodeChar >> 18) & 0x3f));
        dest[2] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
        dest[3] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
        dest[4] = (char)(0x80 | (unicodeChar & 0x3f));
        dest += 5;
    }
    else
    {
        dest[0] = (char)(0xfc | ((unicodeChar >> 30) & 0x1));
        dest[1] = (char)(0x80 | ((unicodeChar >> 24) & 0x3f));
        dest[2] = (char)(0x80 | ((unicodeChar >> 18) & 0x3f));
        dest[3] = (char)(0x80 | ((unicodeChar >> 12) & 0x3f));
        dest[4] = (char)(0x80 | ((unicodeChar >> 6) & 0x3f));
        dest[5] = (char)(0x80 | (unicodeChar & 0x3f));
        dest += 6;
    }
}

#define GET_NEXT_CONTINUATION_BYTE(ptr) *ptr; if ((unsigned char)*ptr < 0x80 || (unsigned char)*ptr >= 0xc0) return '?'; else ++ptr;

unsigned String::DecodeUTF8(const char*& src)
{
    if (src == 0)
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
        return (unsigned)((char2 & 0x3f) | ((char1 & 0x1f) << 6));
    }
    else if (char1 < 0xf0)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char3 & 0x3f) | ((char2 & 0x3f) << 6) | ((char1 & 0xf) << 12));
    }
    else if (char1 < 0xf8)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char4 & 0x3f) | ((char3 & 0x3f) << 6) | ((char2 & 0x3f) << 12) | ((char1 & 0x7) << 18));
    }
    else if (char1 < 0xfc)
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char5 & 0x3f) | ((char4 & 0x3f) << 6) | ((char3 & 0x3f) << 12) | ((char2 & 0x3f) << 18) |
                          ((char1 & 0x3) << 24));
    }
    else
    {
        unsigned char char2 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char3 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char4 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char5 = GET_NEXT_CONTINUATION_BYTE(src);
        unsigned char char6 = GET_NEXT_CONTINUATION_BYTE(src);
        return (unsigned)((char6 & 0x3f) | ((char5 & 0x3f) << 6) | ((char4 & 0x3f) << 12) | ((char3 & 0x3f) << 18) |
                          ((char2 & 0x3f) << 24) | ((char1 & 0x1) << 30));
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
    if (src == 0)
        return 0;
    
    unsigned short word1 = *src;
    
    // Check if we are at a low surrogate
    word1 = *src++;
    if (word1 >= 0xdc00 && word1 < 0xe000)
    {
        while (*src >= 0xdc00 && *src < 0xe000)
            ++src;
        return '?';
    }
    
    if (word1 < 0xd800 || word1 >= 0xe00)
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
    int length = (int)strlen(formatString);

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
            char l = (char)tolower(*lhs);
            char r = (char)tolower(*rhs);
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

    if (pos + length < length_)
    {
        if (delta < 0)
        {
            MoveRange(pos + srcLength, pos + length, length_ - pos - length);
            Resize(length_ + delta);
        }
        if (delta > 0)
        {
            Resize(length_ + delta);
            MoveRange(pos + srcLength, pos + length, length_ - pos - length - delta);
        }
    }
    else
        Resize(length_ + delta);

    CopyChars(buffer_ + pos, srcStart, srcLength);
}

WString::WString() :
    length_(0),
    buffer_(0)
{
}

WString::WString(const String& str) :
    length_(0),
    buffer_(0)
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
        buffer_ = 0;
        length_ = 0;
    }
    else
    {
        wchar_t* newBuffer = new wchar_t[newLength + 1];
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
