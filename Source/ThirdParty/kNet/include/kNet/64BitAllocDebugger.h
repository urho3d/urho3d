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

/** @file 64BitAllocDebugger.h
	@brief Virtually reserves all memory on Windows in the < 4GB memory area so that all
		pointers used by the application are outside the 32-bit range.
	
	Idea and code taken from http://randomascii.wordpress.com/2012/02/14/64-bit-made-easy/ */

#ifdef _WIN64

#include <vector>

class BottomMemoryAllocator
{
public:
	BottomMemoryAllocator();

	~BottomMemoryAllocator();

	std::vector<void *> virtualAllocated;
	std::vector<void *> heapAllocated;
	std::vector<void *> mallocAllocated;

	void ReserveBottomMemory();
	void FreeBottomMemory();
};

#else

/// On other platforms than 64-bit Windows, this debugging feature is not enabled.
class BottomMemoryAllocator {};

#endif
