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

/** @file 64BitAllocDebugger.cpp
	@brief Virtually reserves all memory on Windows in the < 4GB memory area so that all
		pointers used by the application are outside the 32-bit range.
	
	Idea and code taken from http://randomascii.wordpress.com/2012/02/14/64-bit-made-easy/ */

// Modified by Lasse Oorni for Urho3D

#ifdef _WIN64
#include "kNet/64BitAllocDebugger.h"
#include <stdio.h>
// Urho3D: windows.h in lowercase to fix MinGW cross-compiling on a case-sensitive system
#include <windows.h>
#include <vector>

BottomMemoryAllocator::BottomMemoryAllocator()
{
	ReserveBottomMemory();
}

BottomMemoryAllocator::~BottomMemoryAllocator()
{
	FreeBottomMemory();
}

void BottomMemoryAllocator::ReserveBottomMemory()
{
	static bool s_initialized = false;
	if ( s_initialized )
		return;
	s_initialized = true;

	// Start by reserving large blocks of address space, and then
	// gradually reduce the size in order to capture all of the
	// fragments. Technically we should continue down to 64 KB but
	// stopping at 1 MB is sufficient to keep most allocators out.
	const size_t LOW_MEM_LINE = 0x100000000LL;
	size_t totalReservation = 0;
	size_t numVAllocs = 0;
	size_t numHeapAllocs = 0;
	size_t oneMB = 1024 * 1024;
	for (size_t size = 256 * oneMB; size >= oneMB; size /= 2)
	{
		for (;;)
		{
			void* p = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
			if (!p)
				break;
 
			if ((size_t)p >= LOW_MEM_LINE)
			{
				// We don't need this memory, so release it completely.
				VirtualFree(p, 0, MEM_RELEASE);
				break;
			}
			totalReservation += size;
			++numVAllocs;
			virtualAllocated.push_back(p);
		}
	}

	// Now repeat the same process but making heap allocations, to use up
	// the already reserved heap blocks that are below the 4 GB line.
	HANDLE heap = GetProcessHeap();
	for (size_t blockSize = 64 * 1024; blockSize >= 16; blockSize /= 2)
	{
		for (;;)
		{
			void* p = HeapAlloc(heap, 0, blockSize);

			if (!p)
				break;

			if ((size_t)p >= LOW_MEM_LINE)
			{
				// We don't need this memory, so release it completely.
				HeapFree(heap, 0, p);
				break;
			}

			totalReservation += blockSize;
			++numHeapAllocs;
			heapAllocated.push_back(p);
		}
	}

	// Perversely enough the CRT doesn't use the process heap. Suck up
	// the memory the CRT heap has already reserved.

	for (size_t blockSize = 64 * 1024; blockSize >= 16; blockSize /= 2)
	{
		for (;;)
		{
			void* p = malloc(blockSize);

			if (!p)
				break;

			if ((size_t)p >= LOW_MEM_LINE)
			{
				// We don't need this memory, so release it completely.
				free(p);
				break;
			}

			totalReservation += blockSize;
			++numHeapAllocs;
			mallocAllocated.push_back(p);
		}
	}

	// Print diagnostics showing how many allocations we had to make in
	// order to reserve all of low memory, typically less than 200.
	printf("Reserved %1.3f MB (%d vallocs," 
					"%d heap allocs) of low-memory.\n",
			totalReservation / (1024 * 1024.0),
			(int)numVAllocs, (int)numHeapAllocs);
}

void BottomMemoryAllocator::FreeBottomMemory()
{
	for(size_t i = 0; i < virtualAllocated.size(); ++i)
		VirtualFree(virtualAllocated[i], 0, MEM_RELEASE);

	HANDLE heap = GetProcessHeap();
	for(size_t i = 0; i < heapAllocated.size(); ++i)
		HeapFree(heap, 0, heapAllocated[i]);

	for(size_t i = 0; i < mallocAllocated.size(); ++i)
		free(mallocAllocated[i]);
}

#endif
