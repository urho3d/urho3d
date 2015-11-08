// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_HASH_H
#define TB_HASH_H

#include "tb_types.h"

namespace tb {

// On C++ compilers that support it, use const expr for hash so that
// TBID comparisions turn into simple uint32 comparisions compiletime.
// Disabled for TB_RUNTIME_DEBUG_INFO builds, so TBID string debugging
// is available.
//
// Note: GCC may need -std=c++0x or -std=c++11 to enable this feature.

#ifndef TB_RUNTIME_DEBUG_INFO
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#define TB_SUPPORT_CONSTEXPR
#endif
#endif

#ifdef TB_SUPPORT_CONSTEXPR

// FNV constants
static constexpr uint32 basis = 2166136261U;
static constexpr uint32 prime = 16777619U;

// compile-time hash helper function
constexpr uint32 TBGetHash_one(char c, const char* remain, uint32 value)
{
	return c == 0 ? value : TBGetHash_one(remain[0], remain + 1, (value ^ c) * prime);
}

// compile-time hash
constexpr uint32 TBGetHash(const char* str)
{
	return (str && *str) ? TBGetHash_one(str[0], str + 1, basis) : 0;
}

#define TBIDC(str) TBGetHash(str)

#else // TB_SUPPORT_CONSTEXPR

#define TBIDC(str) TBID(str)

/** Get hash value from string */
uint32 TBGetHash(const char *str);

#endif // !TB_SUPPORT_CONSTEXPR

}; // namespace tb

#endif // TB_HASH_H

