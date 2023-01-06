// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "../Base/PrimitiveTypes.h"

#include <cstddef>

namespace Urho3D
{

/// Combine hash into result value.
inline void CombineHash(hash32& result, hash32 hash)
{
    result ^= hash + 0x9e3779b9 + (result << 6) + (result >> 2);
}

/// Pointer hash function.
template <class T> hash32 MakeHash(T* value)
{
    return (hash32)((size_t)value / sizeof(T));
}

/// Const pointer hash function.
template <class T> hash32 MakeHash(const T* value)
{
    return (hash32)((size_t)value / sizeof(T));
}

/// Generic hash function.
template <class T> hash32 MakeHash(const T& value)
{
    return value.ToHash();
}

/// Void pointer hash function.
template <> inline hash32 MakeHash(void* value)
{
    return (hash32)(size_t)value;
}

/// Const void pointer hash function.
template <> inline hash32 MakeHash(const void* value)
{
    return (hash32)(size_t)value;
}

/// Long long hash function.
template <> inline hash32 MakeHash(const i64& value)
{
    return (hash32)((value >> 32u) | (value & 0xffffffffu));
}

/// Unsigned long long hash function.
template <> inline hash32 MakeHash(const u64& value)
{
    return (hash32)((value >> 32u) | (value & 0xffffffffu));
}

/// Int hash function.
template <> inline hash32 MakeHash(const i32& value)
{
    return (hash32)value;
}

/// Unsigned hash function.
template <> inline hash32 MakeHash(const u32& value)
{
    return value;
}

/// Short hash function.
template <> inline hash32 MakeHash(const i16& value)
{
    return (hash32)value;
}

/// Unsigned short hash function.
template <> inline hash32 MakeHash(const u16& value)
{
    return value;
}

/// Char hash function.
template <> inline hash32 MakeHash(const char& value)
{
    return (hash32)value;
}

/// Unicode code point hash function.
template <> inline hash32 MakeHash(const c32& value)
{
    return (hash32)value;
}

/// Unsigned char hash function.
template <> inline hash32 MakeHash(const u8& value)
{
    return value;
}

/// Signed char hash function.
template <> inline hash32 MakeHash(const i8& value)
{
    return value;
}

}
