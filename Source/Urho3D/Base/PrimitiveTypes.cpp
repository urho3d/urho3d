// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <cstddef> // std::ptrdiff_t
#include <cstdint> // std::intptr_t
#include <limits> // std::numeric_limits

// https://en.cppreference.com/w/cpp/language/types
static_assert(std::numeric_limits<unsigned char>::digits == 8);
static_assert(sizeof(short) == 2);
static_assert(sizeof(int) == 4);
static_assert(sizeof(long long) == 8);
static_assert(sizeof(char32_t) == 4);

#ifdef _WIN32 // Windows
static_assert(sizeof(long) == 4);
#else // Unix
static_assert(sizeof(long) == sizeof(void*)); // 4 or 8
#endif

// Pointer arithmetics
static_assert(sizeof(void*) == sizeof(std::ptrdiff_t));
static_assert(sizeof(void*) == sizeof(std::intptr_t));
