// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include <cstddef> // std::byte

// User can inject Urho3D::PrimitiveTypes into other namespace
namespace Urho3D::PrimitiveTypes
{

// https://en.cppreference.com/w/cpp/language/types
using i8 = signed char;
using u8 = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

// Unicode code point (UTF-32 code unit)
using c32 = char32_t;

// For raw data
using std::byte;

// Some hash value (checksum for example)
using hash16 = u16;
using hash32 = u32;
using hash64 = u64;

// Some ID
using id32 = u32;

// Some mask
using mask32 = u32;

// Some flags
using flagset32 = u32;

} // namespace Urho3D::PrimitiveTypes

namespace Urho3D
{

using namespace Urho3D::PrimitiveTypes;

} // namespace Urho3D
