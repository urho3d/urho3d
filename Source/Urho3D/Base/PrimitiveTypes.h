// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <climits>
#include <cstdint>
#include <stddef.h>

// https://en.cppreference.com/w/cpp/language/types
static_assert(CHAR_BIT == 8);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 4);
static_assert(sizeof(long) == 4 || sizeof(long) == 8); // (Win32, Win64, Unix32) || Unix64
static_assert(sizeof(long long) == 8);

// https://en.cppreference.com/w/cpp/types/integer
using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

// Unicode code point (UTF-32 code unit)
static_assert(sizeof(char32_t) == 4);
using c32 = char32_t;

// Pointer arithmetics
static_assert(sizeof(void*) == sizeof(ptrdiff_t));
static_assert(sizeof(void*) == sizeof(intptr_t));

// Some hash value (checksum for example)
using hash16 = u16;
using hash32 = u32;
using hash64 = u64;
