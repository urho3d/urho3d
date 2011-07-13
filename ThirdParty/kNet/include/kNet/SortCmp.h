/* Copyright 2010 Jukka Jylänki

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

/** @file SortCmp.h
	@brief The TriCmp and TriCmpObj constructs are the default sorting predicate objects. */

#include <cassert>

namespace kNet
{
namespace sort
{

template<typename T>
int TriCmp(const T &a, const T &b)
{
//	assume(!(a < b && b < a));
	if (a < b) return -1;
	if (b < a) return 1;
//	assert(a == b); // Require trichotomy.

	return 0;
}

template<typename T>
class TriCmpObj
{
public:
	int operator ()(const T &a, const T &b)
	{
		if (a < b) return -1;
		if (b < a) return 1;
		assert(a == b); // Require trichotomy.
		return 0;
	}
};

} // ~sort
} // ~kNet

