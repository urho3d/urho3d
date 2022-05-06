// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <cstdint>

// https://en.cppreference.com/w/cpp/language/types
static_assert(sizeof(char) == 1);
static_assert(sizeof(int) == 4);
static_assert(sizeof(long) == 4 || sizeof(long) == 8); // (Win32, Win64, Unix32) || Unix64
static_assert(sizeof(long long) == 8);

// https://en.cppreference.com/w/cpp/types/integer
typedef int8_t   i8;
typedef uint8_t  u8;
typedef int16_t  i16;
typedef uint16_t u16;
typedef int32_t  i32;
typedef uint32_t u32;
typedef int64_t  i64;
typedef uint64_t u64;
