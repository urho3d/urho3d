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

/** @file Alignment.h
	@brief Provides functions for working with pointer data alignment computations.*/

#include <cassert>

#include "Types.h"

#if defined(KNET_UNIX) || defined(ANDROID)
#include <stdint.h>
#endif

namespace kNet
{

/// Is value an exact power of 2? i.e. 1,2,4,8,16,...
#define IS_POW2(value) (((value) & ((value)-1)) == 0)

/// Is the given pointer aligned to the pow2-boundary specified by alignment?
inline bool IsPow2Aligned(uintptr_t pointer, u32 alignment)
{
	assert(IS_POW2(alignment));
	return (pointer & (alignment - 1)) == 0;
}

/// @return The given pointer aligned up to the next pow2-boundary specified by alignment. (Alignment must be a pow2)
inline uintptr_t AlignUpPow2(uintptr_t pointer, u32 alignment)
{
	assert(IS_POW2(alignment));
	return (pointer + alignment - 1) & ~((uintptr_t)alignment - 1);
}

/// @return The given pointer aligned down to the previous pow2-boundary specified by alignment. (Alignment must be a pow2)
inline uintptr_t AlignDownPow2(uintptr_t pointer, u32 alignment)
{
	assert(IS_POW2(alignment));
	return pointer & ~((uintptr_t)alignment - 1);
}

inline u32 RoundUpToNextPow2(u32 x)
{
	x = x - 1;
	x = x | (x >>  1);
	x = x | (x >>  2);
	x = x | (x >>  4);
	x = x | (x >>  8);
	x = x | (x >> 16);
	return x + 1;
}

inline u64 RoundUpToNextPow2(u64 x)
{
	x = x - 1;
	x = x | (x >>  1);
	x = x | (x >>  2);
	x = x | (x >>  4);
	x = x | (x >>  8);
	x = x | (x >> 16);
	x = x | (x >> 32);
	return x + 1; 
}

} // ~kNet
