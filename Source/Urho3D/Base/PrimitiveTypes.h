// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <cstddef> // std::byte
#include <cstdint> // std::int8_t, ...

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
