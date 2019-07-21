/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/port/AlignedAlloc.hpp>
#include <cstdlib>
#include <cstdio>
using namespace std;
using namespace cat;


#if defined(CAT_OS_WINDOWS)
#include <cat/port/WindowsInclude.hpp>

typedef BOOL (WINAPI *PtGetLogicalProcessorInformation)(
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, 
	PDWORD);

#elif defined(CAT_OS_APPLE)
#include <sys/sysctl.h>
#else
#endif


// Object for placement new
Aligned Aligned::ii;


//// Cache line size determination

static u32 _cacheline_bytes = 0;

static CAT_INLINE u32 DetermineCacheLineBytes()
{
	// Based on work by Nick Strupat (http://strupat.ca/)

	u32 discovered_cache_line_size = 0;

#if defined(CAT_OS_APPLE)

	u64 line_size;
	size_t size = sizeof(line_size);

	if (0 == sysctlbyname("hw.cachelinesize", &line_size, &size, 0, 0))
	{
		discovered_cache_line_size = (u32)line_size;
	}

#elif defined(CAT_OS_WINDOWS)

	DWORD buffer_size = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

	PtGetLogicalProcessorInformation glpi;

	// Attempt to use GetLogicalProcessorInformation
	glpi = (PtGetLogicalProcessorInformation)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");

	// If it is available,
	if (glpi)
	{
		// Grab the buffer size required to use GLPI
		glpi(0, &buffer_size);

		// If no error occurred,
		if (buffer_size > 0)
		{
			// Allocate space for buffer
			buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);

			// If buffer is allocated,
			if (buffer)
			{
				// Finally invoke GLPI and grab processor information
				glpi(buffer, &buffer_size);

				// For each piece of information,
				for (int i = 0; i < (int)(buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)); ++i)
				{
					// If it is L1 cache,
					if (buffer[i].Relationship == RelationCache &&
						buffer[i].Cache.Level == 1)
					{
						// Woot found it!
						discovered_cache_line_size = (u32)buffer[i].Cache.LineSize;
						break;
					}
				}

				free(buffer);
			}
		}
	}

#elif defined(CAT_OS_LINUX)

	FILE *file = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");

	if (file)
	{
		if (1 != fscanf(file, "%d", &discovered_cache_line_size))
		{
			discovered_cache_line_size = 0;
		}

		fclose(file);
	}

#elif defined(CAT_OS_XBOX) || defined(CAT_OS_PS3)

	discovered_cache_line_size = 128;

#endif

	// Validate cache line size and use default if discovery has failed
	if (discovered_cache_line_size <= 0 ||
		discovered_cache_line_size > 1024 ||
		!CAT_IS_POWER_OF_2(discovered_cache_line_size))
	{
		discovered_cache_line_size = CAT_DEFAULT_CACHE_LINE_SIZE; // From Config.hpp
	}

	return discovered_cache_line_size;
}

u32 cat::GetCacheLineBytes()
{
	if (!_cacheline_bytes)
		_cacheline_bytes = DetermineCacheLineBytes();

	return _cacheline_bytes;
}


//// Small to medium -size aligned heap allocator

static CAT_INLINE u8 DetermineOffset(void *ptr)
{
#if defined(CAT_WORD_64)
	return (u8)( _cacheline_bytes - ((u32)*(u64*)&ptr & (_cacheline_bytes-1)) );
#else
	return (u8)( _cacheline_bytes - (*(u32*)&ptr & (_cacheline_bytes-1)) );
#endif
}

// Allocates memory aligned to a CPU cache-line byte boundary from the heap
void *Aligned::Acquire(u32 bytes)
{
	if (!_cacheline_bytes)
	{
		_cacheline_bytes = DetermineCacheLineBytes();
	}

    u8 *buffer = (u8*)malloc(_cacheline_bytes + bytes);
    if (!buffer) return 0;

	// Get buffer aligned address
	u8 offset = DetermineOffset(buffer);
    buffer += offset;
    buffer[-1] = offset;

    return buffer;
}

// Resizes an aligned pointer
void *Aligned::Resize(void *ptr, u32 bytes)
{
	if (!ptr) return Acquire(bytes);

	// Can assume here that cacheline bytes has been determined

	// Get buffer base address
	u8 *buffer = reinterpret_cast<u8*>( ptr );
	buffer -= buffer[-1];

	buffer = (u8*)realloc(buffer, _cacheline_bytes + bytes);
	if (!buffer) return 0;

	// Get buffer aligned address
	u8 offset = DetermineOffset(buffer);
	buffer += offset;
	buffer[-1] = offset;

	return buffer;
}

// Frees an aligned pointer
void Aligned::Release(void *ptr)
{
    if (ptr)
    {
		// Get buffer base address
        u8 *buffer = reinterpret_cast<u8*>( ptr );
        buffer -= buffer[-1];

        free(buffer);
    }
}


//// Large-size aligned heap allocator

// Allocates memory aligned to a CPU cache-line byte boundary from the heap
void *LargeAligned::Acquire(u32 bytes)
{
#if defined(CAT_OS_WINDOWS)
	return VirtualAlloc(0, bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	return Aligned::Acquire(bytes);
#endif
}

// Frees an aligned pointer
void LargeAligned::Release(void *ptr)
{
	if (ptr)
	{
#if defined(CAT_OS_WINDOWS)
		VirtualFree(ptr, 0, MEM_RELEASE);
#else
		Aligned::Release(ptr);
#endif
	}
}
