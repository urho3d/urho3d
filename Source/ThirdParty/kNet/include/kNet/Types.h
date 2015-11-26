/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file Types.h
	@brief Provides platform-independent fixed size types. */

// Preprocessor macro for suppressing unused formal parameter warnings while still showing the variable name in Doxygen documentation.
#if defined(DOXYGEN) // DOXYGEN is a special define used when Doxygen is run.
#define UNUSED(x) x
#else
#define UNUSED(x)
#endif

#ifndef MARK_UNUSED
/// If a variable is labelled with this directive, the compiler should not emit a warning even if it is unused in the code.
#define MARK_UNUSED(x) ((void)x)
#endif

#ifndef KNET_NO_FIXEDWIDTH_TYPES

#include "kNetBuildConfig.h"

#ifdef __MINGW32__
#include <stdint.h>
#endif

// As a reminder: http://predef.sourceforge.net/prestd.html

// If we have C99, take the types from there.
#if (__STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1600)

#include <cstdint>

typedef uint8_t u8; ///< a single byte: 0-255.
typedef uint16_t u16; ///< 2 bytes: 0 - 65535.
typedef uint32_t u32; ///< 4 bytes: 0 - 4,294,967,295 ~ 4000 million or 4e9.
typedef uint64_t u64; ///< 8 bytes: 18,446,744,073,709,551,615 ~1.8e19.

typedef int8_t s8; ///< a single byte: -128 - 127.
typedef int16_t s16; ///< 2 bytes: -32768 - 32767.
typedef int32_t s32; ///< 4 bytes signed: max 2,147,483,647 ~ 2000 million or 2e9.
typedef int64_t s64; ///< 8 bytes signed. 9,223,372,036,854,775,807 ~ 9e18.

// Otherwise, if we have boost, we can also pull the types from there.
#elif defined(KNET_USE_BOOST)

#include <boost/cstdint.hpp>

typedef boost::uint8_t u8; ///< a single byte: 0-255.
typedef boost::uint16_t u16; ///< 2 bytes: 0 - 65535.
typedef boost::uint32_t u32; ///< 4 bytes: 0 - 4,294,967,295 ~ 4000 million or 4e9.
typedef boost::uint64_t u64; ///< 8 bytes: 18,446,744,073,709,551,615 ~1.8e19.

typedef boost::int8_t s8; ///< a single byte: -128 - 127.
typedef boost::int16_t s16; ///< 2 bytes: -32768 - 32767.
typedef boost::int32_t s32; ///< 4 bytes signed: max 2,147,483,647 ~ 2000 million or 2e9.
typedef boost::int64_t s64; ///< 8 bytes signed. 9,223,372,036,854,775,807 ~ 9e18.

#else // No boost or unknown if we have C99. Have to guess the following are correct.

#include <limits.h>

//#pragma warning "Not using boost and C99 not defined. Guessing the built-ins for fixed-width types!"

typedef unsigned char u8; ///< a single byte: 0-255.
typedef unsigned short u16; ///< 2 bytes: 0 - 65535.
typedef unsigned long long u64; ///< 8 bytes: 18,446,744,073,709,551,615 ~1.8e19.

typedef signed char s8; ///< a single byte: -128 - 127.
typedef signed short s16; ///< 2 bytes: -32768 - 32767.

#if ULONG_MAX == 0xffffffff
typedef unsigned long u32; ///< 4 bytes: 0 - 4,294,967,295 ~ 4000 million or 4e9.
typedef long s32; ///< 4 bytes signed: max 2,147,483,647 ~ 2000 million or 2e9.
#elif UINT_MAX == 0xffffffff
typedef unsigned int u32; ///< 4 bytes: 0 - 4,294,967,295 ~ 4000 million or 4e9.
typedef int s32; ///< 4 bytes signed: max 2,147,483,647 ~ 2000 million or 2e9.
#endif

typedef signed long long s64; ///< 8 bytes signed. 9,223,372,036,854,775,807 ~ 9e18.

#endif

// kNet special types:

namespace kNet
{
	/// Identifies a UDP datagram by auto-incrementing number. Contains 22 actual bits of data.
	typedef unsigned long packet_id_t;
	/// Identifies the type of a network message. Contains 30 actual bits of data.
	/// Valid user range is [6, 1073741821 == 0x3FFFFFFD].
	typedef unsigned long message_id_t;
}

#endif // ~KNET_NO_FIXEDWIDTH_TYPES
