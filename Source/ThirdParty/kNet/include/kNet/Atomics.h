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

// Modified by Lasse Oorni for Urho3D

#ifdef _WIN32
// Urho3D: windows.h in lowercase to fix MinGW cross-compiling on a case-sensitive system
#include <windows.h>
#endif

/** @file Atomics.h
	@brief Abstracts platform-specific atomics operations. */

// bool CmpXChgPointer(word *dst, word newVal, word cmp);
// Assigns *dst = newVal, but only if *dst == cmp before the assignment. This evaluation is done atomically.
// Returns true if the assignment succeeded.
// Do NOT call this macro with any side expressions on dst, newVal or cmp.

#ifdef _WIN32
// See http://msdn.microsoft.com/en-us/library/ms683568(VS.85).aspx
#define CmpXChgPointer(dst, newVal, cmp) (InterlockedCompareExchangePointer((dst), (newVal), (cmp)) == (cmp))
#else
// See http://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html
#define CmpXChgPointer(dst, newVal, cmp) __sync_bool_compare_and_swap((dst), (cmp), (newVal))
#endif
