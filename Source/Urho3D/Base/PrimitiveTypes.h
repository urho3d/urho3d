// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <cstddef> // std::byte, std::ptrdiff_t
#include <cstdint> // std::intptr_t, std::int8_t, ...
#include <limits> // std::numeric_limits


// https://en.cppreference.com/w/cpp/language/types
static_assert(std::numeric_limits<unsigned char>::digits == 8);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 4);
static_assert(sizeof(long) == 4 || sizeof(long) == 8); // (Win32, Win64, Unix32) || Unix64
static_assert(sizeof(long long) == 8);
static_assert(sizeof(char32_t) == 4);

// Pointer arithmetics
static_assert(sizeof(void*) == sizeof(std::ptrdiff_t));
static_assert(sizeof(void*) == sizeof(std::intptr_t));


// User can inject Urho3D::PrimitiveTypes into other namespace
namespace Urho3D::PrimitiveTypes
{

// https://en.cppreference.com/w/cpp/types/integer
using i8 = std::int8_t;
using u8 = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

// Unicode code point (UTF-32 code unit)
using c32 = char32_t;

// For raw data
using std::byte;

// Some hash value (checksum for example)
using hash16 = u16;
using hash32 = u32;
using hash64 = u64;

} // namespace Urho3D::PrimitiveTypes


namespace Urho3D
{

using namespace Urho3D::PrimitiveTypes;

} // namespace Urho3D
