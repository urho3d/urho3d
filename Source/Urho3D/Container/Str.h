// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Vector.h"

#include <cstdarg>
#include <cstring>
#include <cctype>

namespace Urho3D
{

static const int CONVERSION_BUFFER_LENGTH = 128;
static const int MATRIX_CONVERSION_BUFFER_LENGTH = 256;

class WString;

class StringHash;
template <class T, class U> class HashMap;

/// Map of strings.
using StringMap = HashMap<StringHash, String>;

/// %String class.
class URHO3D_API String
{
public:
    using Iterator = RandomAccessIterator<char>;
    using ConstIterator = RandomAccessConstIterator<char>;

    /// Construct empty.
    String() noexcept
    {
        SetShortStringLength(0);
        data_.shortString_.buffer_[0] = '\0';
    }

    /// Construct from another string.
    String(const String& str)
        : String()
    {
        *this = str;
    }

    /// Move-construct from another string.
    String(String && str) noexcept
        : String()
    {
        Swap(str);
    }

    /// Construct from a C string.
    String(const char* str)   // NOLINT(google-explicit-constructor)
        : String()
    {
        *this = str;
    }

    /// Construct from a C string.
    String(char* str)         // NOLINT(google-explicit-constructor)
        : String()
    {
        *this = (const char*)str;
    }

    /// Construct from a char array and length.
    String(const char* str, unsigned length)
        : String()
    {
        Resize(length);
        CopyChars(GetBuffer(), str, length);
    }

    /// Construct from a null-terminated wide character array.
    explicit String(const wchar_t* str)
        : String()
    {
        SetUTF8FromWChar(str);
    }

    /// Construct from a null-terminated wide character array.
    explicit String(wchar_t* str)
        : String()
    {
        SetUTF8FromWChar(str);
    }

    /// Construct from a wide character string.
    explicit String(const WString& str);

    /// Construct from an integer.
    explicit String(int value);
    /// Construct from a short integer.
    explicit String(short value);
    /// Construct from a long integer.
    /// @nobind
    explicit String(long value);
    /// Construct from a long long integer.
    explicit String(long long value);
    /// Construct from an unsigned integer.
    explicit String(unsigned value);
    /// Construct from an unsigned short integer.
    explicit String(unsigned short value);
    /// Construct from an unsigned long integer.
    /// @nobind
    explicit String(unsigned long value);
    /// Construct from an unsigned long long integer.
    explicit String(unsigned long long value);
    /// Construct from a float.
    explicit String(float value);
    /// Construct from a double.
    explicit String(double value);
    /// Construct from a bool.
    explicit String(bool value);
    /// Construct from a character.
    explicit String(char value);
    /// Construct from a character and fill length.
    explicit String(char value, unsigned length);

    /// Construct from a convertible value.
    template <class T> explicit String(const T& value)
        : String()
    {
        *this = value.ToString();
    }

    /// Destruct.
    ~String()
    {
        if (!IsShort())
            delete[] data_.longString_.buffer_;
    }

    /// Assign a string.
    String& operator =(const String& rhs)
    {
        if (&rhs != this)
        {
            Resize(rhs.Length());
            CopyChars(GetBuffer(), rhs.GetBuffer(), rhs.Length());
        }

        return *this;
    }

    /// Move-assign a string.
    String& operator =(String && rhs) noexcept
    {
        Swap(rhs);
        return *this;
    }

    /// Assign a C string.
    String& operator =(const char* rhs)
    {
        unsigned rhsLength = CStringLength(rhs);
        Resize(rhsLength);
        CopyChars(GetBuffer(), rhs, rhsLength);

        return *this;
    }

    /// Add-assign a string.
    String& operator +=(const String& rhs)
    {
        unsigned oldLength = Length();
        unsigned rhsLength = rhs.Length();
        Resize(oldLength + rhsLength);
        CopyChars(GetBuffer() + oldLength, rhs.GetBuffer(), rhsLength);

        return *this;
    }

    /// Add-assign a C string.
    String& operator +=(const char* rhs)
    {
        unsigned rhsLength = CStringLength(rhs);
        unsigned oldLength = Length();
        Resize(oldLength + rhsLength);
        CopyChars(GetBuffer() + oldLength, rhs, rhsLength);

        return *this;
    }

    /// Add-assign a character.
    String& operator +=(char rhs)
    {
        unsigned oldLength = Length();
        Resize(oldLength + 1);
        GetBuffer()[oldLength] = rhs;

        return *this;
    }

    /// Add-assign (concatenate as string) an integer.
    String& operator +=(int rhs);
    /// Add-assign (concatenate as string) a short integer.
    String& operator +=(short rhs);
    /// Add-assign (concatenate as string) a long integer.
    /// @nobind
    String& operator +=(long rhs);
    /// Add-assign (concatenate as string) a long long integer.
    String& operator +=(long long rhs);
    /// Add-assign (concatenate as string) an unsigned integer.
    String& operator +=(unsigned rhs);
    /// Add-assign (concatenate as string) a short unsigned integer.
    String& operator +=(unsigned short rhs);
    /// Add-assign (concatenate as string) a long unsigned integer.
    /// @nobind
    String& operator +=(unsigned long rhs);
    /// Add-assign (concatenate as string) a long long unsigned integer.
    String& operator +=(unsigned long long rhs);
    /// Add-assign (concatenate as string) a float.
    String& operator +=(float rhs);
    /// Add-assign (concatenate as string) a bool.
    String& operator +=(bool rhs);

    /// Add-assign (concatenate as string) an arbitrary type.
    template <class T> String& operator +=(const T& rhs) { return *this += rhs.ToString(); }

    /// Add a string.
    String operator +(const String& rhs) const
    {
        String ret;
        unsigned length = Length();
        unsigned rhsLength = rhs.Length();
        ret.Resize(length + rhsLength);
        char* retBuffer = ret.GetBuffer();
        CopyChars(retBuffer, GetBuffer(), length);
        CopyChars(retBuffer + length, rhs.GetBuffer(), rhsLength);

        return ret;
    }

    /// Add a C string.
    String operator +(const char* rhs) const
    {
        unsigned length = Length();
        unsigned rhsLength = CStringLength(rhs);
        String ret;
        ret.Resize(length + rhsLength);
        char* retBuffer = ret.GetBuffer();
        CopyChars(retBuffer, GetBuffer(), length);
        CopyChars(retBuffer + length, rhs, rhsLength);

        return ret;
    }

    /// Test for equality with another string.
    bool operator ==(const String& rhs) const { return strcmp(CString(), rhs.CString()) == 0; }

    /// Test for inequality with another string.
    bool operator !=(const String& rhs) const { return strcmp(CString(), rhs.CString()) != 0; }

    /// Test if string is less than another string.
    bool operator <(const String& rhs) const { return strcmp(CString(), rhs.CString()) < 0; }

    /// Test if string is greater than another string.
    bool operator >(const String& rhs) const { return strcmp(CString(), rhs.CString()) > 0; }

    /// Test for equality with a C string.
    bool operator ==(const char* rhs) const { return strcmp(CString(), rhs) == 0; }

    /// Test for inequality with a C string.
    bool operator !=(const char* rhs) const { return strcmp(CString(), rhs) != 0; }

    /// Test if string is less than a C string.
    bool operator <(const char* rhs) const { return strcmp(CString(), rhs) < 0; }

    /// Test if string is greater than a C string.
    bool operator >(const char* rhs) const { return strcmp(CString(), rhs) > 0; }

    /// Return char at index.
    char& operator [](unsigned index)
    {
        assert(index < Length());
        return GetBuffer()[index];
    }

    /// Return const char at index.
    const char& operator [](unsigned index) const
    {
        assert(index < Length());
        return GetBuffer()[index];
    }

    /// Return char at index.
    char& At(unsigned index)
    {
        assert(index < Length());
        return GetBuffer()[index];
    }

    /// Return const char at index.
    const char& At(unsigned index) const
    {
        assert(index < Length());
        return GetBuffer()[index];
    }

    /// Replace all occurrences of a character.
    void Replace(char replaceThis, char replaceWith, bool caseSensitive = true);
    /// Replace all occurrences of a string.
    void Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive = true);
    /// Replace a substring.
    void Replace(unsigned pos, unsigned length, const String& replaceWith);
    /// Replace a substring with a C string.
    void Replace(unsigned pos, unsigned length, const char* replaceWith);
    /// Replace a substring by iterators.
    Iterator Replace(const Iterator& start, const Iterator& end, const String& replaceWith);
    /// Return a string with all occurrences of a character replaced.
    String Replaced(char replaceThis, char replaceWith, bool caseSensitive = true) const;
    /// Return a string with all occurrences of a string replaced.
    String Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive = true) const;
    /// Append a string.
    String& Append(const String& str);
    /// Append a C string.
    String& Append(const char* str);
    /// Append a character.
    String& Append(char c);
    /// Append characters.
    String& Append(const char* str, unsigned length);
    /// Insert a string.
    void Insert(unsigned pos, const String& str);
    /// Insert a character.
    void Insert(unsigned pos, char c);
    /// Insert a string by iterator.
    Iterator Insert(const Iterator& dest, const String& str);
    /// Insert a string partially by iterators.
    Iterator Insert(const Iterator& dest, const Iterator& start, const Iterator& end);
    /// Insert a character by iterator.
    Iterator Insert(const Iterator& dest, char c);
    /// Erase a substring.
    void Erase(unsigned pos, unsigned length = 1);
    /// Erase a character by iterator.
    Iterator Erase(const Iterator& it);
    /// Erase a substring by iterators.
    Iterator Erase(const Iterator& start, const Iterator& end);
    
    /// Resize the string. Can increase capacity, but never decrease.
    void Resize(unsigned newLength);
    
    /// Set new capacity. New capacity may differ from requested.
    void Reserve(unsigned newCapacity);

    /// Reallocate so that no extra memory is used.
    void Compact();
    /// Clear the string.
    void Clear();
    /// Swap with another string.
    void Swap(String& str);

    /// Return iterator to the beginning.
    Iterator Begin() { return Iterator(GetBuffer()); }

    /// Return const iterator to the beginning.
    ConstIterator Begin() const { return ConstIterator(GetBuffer()); }

    /// Return iterator to the end.
    Iterator End() { return Iterator(GetBuffer() + Length()); }

    /// Return const iterator to the end.
    ConstIterator End() const { return ConstIterator(GetBuffer() + Length()); }

    /// Return first char, or 0 if empty.
    char Front() const { return GetBuffer()[0]; }

    /// Return last char, or 0 if empty.
    char Back() const
    {
        unsigned length = Length();
        return length ? GetBuffer()[length - 1] : GetBuffer()[0];
    }

    /// Return a substring from position to end.
    String Substring(unsigned pos) const;
    /// Return a substring with length from position.
    String Substring(unsigned pos, unsigned length) const;
    /// Return string with whitespace trimmed from the beginning and the end.
    String Trimmed() const;
    /// Return string in uppercase.
    String ToUpper() const;
    /// Return string in lowercase.
    String ToLower() const;
    /// Return substrings split by a separator char. By default don't return empty strings.
    Vector<String> Split(char separator, bool keepEmptyStrings = false) const;
    /// Join substrings with a 'glue' string.
    void Join(const Vector<String>& subStrings, const String& glue);
    /// Return index to the first occurrence of a string, or NPOS if not found.
    unsigned Find(const String& str, unsigned startPos = 0, bool caseSensitive = true) const;
    /// Return index to the first occurrence of a character, or NPOS if not found.
    unsigned Find(char c, unsigned startPos = 0, bool caseSensitive = true) const;
    /// Return index to the last occurrence of a string, or NPOS if not found.
    unsigned FindLast(const String& str, unsigned startPos = NPOS, bool caseSensitive = true) const;
    /// Return index to the last occurrence of a character, or NPOS if not found.
    unsigned FindLast(char c, unsigned startPos = NPOS, bool caseSensitive = true) const;
    /// Return whether starts with a string.
    bool StartsWith(const String& str, bool caseSensitive = true) const;
    /// Return whether ends with a string.
    bool EndsWith(const String& str, bool caseSensitive = true) const;

    /// Return pointer to buffer.
    char* GetBuffer() { return IsShort() ? data_.shortString_.buffer_ : data_.longString_.buffer_; }

    /// Return pointer to buffer.
    const char* GetBuffer() const { return IsShort() ? data_.shortString_.buffer_ : data_.longString_.buffer_; }

    /// Return the C string.
    const char* CString() const { return GetBuffer(); }

    /// Return length.
    /// @property
    unsigned Length() const { return IsShort() ? GetShortStringLength() : data_.longString_.length_; }

    /// Return buffer capacity.
    unsigned Capacity() const { return IsShort() ? SHORT_STRING_CAPACITY : data_.longString_.capacity_; }

    /// Return whether the string is empty.
    /// @property
    bool Empty() const { return Length() == 0; }

    /// Return comparison result with a string.
    int Compare(const String& str, bool caseSensitive = true) const;
    /// Return comparison result with a C string.
    int Compare(const char* str, bool caseSensitive = true) const;

    /// Return whether contains a specific occurrence of a string.
    bool Contains(const String& str, bool caseSensitive = true) const { return Find(str, 0, caseSensitive) != NPOS; }

    /// Return whether contains a specific character.
    bool Contains(char c, bool caseSensitive = true) const { return Find(c, 0, caseSensitive) != NPOS; }

    /// Construct UTF8 content from Latin1.
    void SetUTF8FromLatin1(const char* str);
    /// Construct UTF8 content from wide characters.
    void SetUTF8FromWChar(const wchar_t* str);
    /// Calculate number of characters in UTF8 content.
    /// @property{get_utf8Length}
    unsigned LengthUTF8() const;
    /// Return byte offset to char in UTF8 content.
    unsigned ByteOffsetUTF8(unsigned index) const;
    /// Return next Unicode character from UTF8 content and increase byte offset.
    unsigned NextUTF8Char(unsigned& byteOffset) const;
    /// Return Unicode character at index from UTF8 content.
    unsigned AtUTF8(unsigned index) const;
    /// Replace Unicode character at index from UTF8 content.
    void ReplaceUTF8(unsigned index, unsigned unicodeChar);
    /// Append Unicode character at the end as UTF8.
    String& AppendUTF8(unsigned unicodeChar);
    /// Return a UTF8 substring from position to end.
    String SubstringUTF8(unsigned pos) const;
    /// Return a UTF8 substring with length from position.
    String SubstringUTF8(unsigned pos, unsigned length) const;

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const
    {
        unsigned hash = 0;
        const char* ptr = GetBuffer();
        while (*ptr)
        {
            hash = *ptr + (hash << 6u) + (hash << 16u) - hash;
            ++ptr;
        }

        return hash;
    }

    /// Return substrings split by a separator char. By default don't return empty strings.
    static Vector<String> Split(const char* str, char separator, bool keepEmptyStrings = false);
    /// Return a string by joining substrings with a 'glue' string.
    /// @manualbind
    static String Joined(const Vector<String>& subStrings, const String& glue);
    /// Encode Unicode character to UTF8. Pointer will be incremented.
    static void EncodeUTF8(char*& dest, unsigned unicodeChar);
    /// Decode Unicode character from UTF8. Pointer will be incremented.
    static unsigned DecodeUTF8(const char*& src);
#ifdef _WIN32
    /// Encode Unicode character to UTF16. Pointer will be incremented.
    static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
    /// Decode Unicode character from UTF16. Pointer will be incremented.
    static unsigned DecodeUTF16(const wchar_t*& src);
#endif

    /// Return length of a C string.
    static unsigned CStringLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }

    /// Append to string using formatting.
    String& AppendWithFormat(const char* formatString, ...);
    /// Append to string using variable arguments.
    String& AppendWithFormatArgs(const char* formatString, va_list args);

    /// Compare two C strings.
    static int Compare(const char* lhs, const char* rhs, bool caseSensitive);

    /// Position for "not found".
    static inline constexpr unsigned NPOS = 0xffffffff;

    /// Empty string.
    static const String EMPTY;

    /// Is the string stored on the stack?
    bool IsShort() const
    {
        u8 lastByte = data_.shortString_.length_;
        return !!(lastByte & SSO_MASK);
    }

private:
    struct LongString
    {
        /// Data.
        char* buffer_;

        /// Number of bytes without null terminator.
        u32 length_;
        
        /// Size of buffer_.
        u32 capacity_;
    };

    /// 11 bytes on 32-bit platform, 15 bytes on 64-bit platform
    inline static constexpr unsigned SHORT_STRING_CAPACITY = sizeof(LongString) - 1;

    struct ShortString
    {
        /// Data.
        char buffer_[SHORT_STRING_CAPACITY];

        /// Number of bytes without null terminator.
        u8 length_;
    };

    static_assert(sizeof(LongString) == sizeof(ShortString));

    // https://github.com/doxygen/doxygen/issues/7623
    union
    {
        /// @nobind
        LongString longString_;
        
        /// @nobind
        ShortString shortString_;
    } data_;

    /// MSB of the last byte is used as a flag.
    inline static constexpr u8 SSO_MASK = 0b10000000u;
    
    inline static constexpr u8 INVERTED_SSO_MASK = static_cast<u8>(~SSO_MASK);

    unsigned GetShortStringLength() const
    {
        return data_.shortString_.length_ & INVERTED_SSO_MASK;
    }

    void SetShortStringLength(u8 value)
    {
        data_.shortString_.length_ = value | SSO_MASK;
    }

    /// Move a range of characters within the string.
    void MoveRange(unsigned dest, unsigned src, unsigned count)
    {
        if (count)
        {
            char* buffer = GetBuffer();
            memmove(buffer + dest, buffer + src, count);
        }
    }

    /// Copy chars from one buffer to another.
    static void CopyChars(char* dest, const char* src, unsigned count)
    {
#ifdef _MSC_VER
        if (count)
            memcpy(dest, src, count);
#else
        char* end = dest + count;
        while (dest != end)
        {
            *dest = *src;
            ++dest;
            ++src;
        }
#endif
    }

    /// Replace a substring with another substring.
    void Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength);
};

/// Add a string to a C string.
inline String operator +(const char* lhs, const String& rhs)
{
    String ret(lhs);
    ret += rhs;
    return ret;
}

/// Add a string to a wide char C string.
inline String operator +(const wchar_t* lhs, const String& rhs)
{
    String ret(lhs);
    ret += rhs;
    return ret;
}

/// Wide character string. Only meant for converting from String and passing to the operating system where necessary.
/// @nobind
class URHO3D_API WString
{
public:
    /// Construct empty.
    WString();
    /// Construct from a string.
    explicit WString(const String& str);
    /// Destruct.
    ~WString();

    /// Return char at index.
    wchar_t& operator [](unsigned index)
    {
        assert(index < length_);
        return buffer_[index];
    }

    /// Return const char at index.
    const wchar_t& operator [](unsigned index) const
    {
        assert(index < length_);
        return buffer_[index];
    }

    /// Return char at index.
    wchar_t& At(unsigned index)
    {
        assert(index < length_);
        return buffer_[index];
    }

    /// Return const char at index.
    const wchar_t& At(unsigned index) const
    {
        assert(index < length_);
        return buffer_[index];
    }

    /// Resize the string.
    void Resize(unsigned newLength);

    /// Return whether the string is empty.
    bool Empty() const { return length_ == 0; }

    /// Return length.
    unsigned Length() const { return length_; }

    /// Return character data.
    const wchar_t* CString() const { return buffer_; }

private:
    /// String length.
    unsigned length_;
    /// String buffer, null if not allocated.
    wchar_t* buffer_;
};

}
