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

/** @file DebugMemoryLeakCheck.h
	@brief Provides overloads of operators new and delete for tracking memory leaks. */

// Modified by Lasse Oorni for Urho3D

// Urho3D: only include on MSVC
#if defined(_MSC_VER) && defined(_DEBUG) && defined(KNET_MEMORY_LEAK_CHECK)

#include <new>
#include <crtdbg.h>

// On MSVC2008, include these files beforehand to avoid compilation errors from our operator new redefine.
#if _MSC_VER == 1500
#include <ios> 
#include <map>
#endif

#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif

// Urho3D: omit static to allow compilation on VS2015 Update 1
__forceinline void *operator new(size_t size, const char *file, int line)
{
	return _malloc_dbg(size, _NORMAL_BLOCK, file, line);
}

__forceinline void *operator new[](size_t size, const char *file, int line)
{
	return _malloc_dbg(size, _NORMAL_BLOCK, file, line);
}

__forceinline void operator delete(void *ptr, const char *, int)
{
	_free_dbg(ptr, _NORMAL_BLOCK);
}

__forceinline void operator delete[](void *ptr, const char *, int)
{
	_free_dbg(ptr, _NORMAL_BLOCK);
}

__forceinline void *operator new(size_t size)
{
#ifdef DEBUG_CPP_NAME
	return _malloc_dbg(size, _NORMAL_BLOCK, DEBUG_CPP_NAME, 1);
#else
	return _malloc_dbg(size, _NORMAL_BLOCK, "(No CPP Name)", 1);
#endif
}

__forceinline void *operator new[](size_t size)
{
#ifdef DEBUG_CPP_NAME
	return _malloc_dbg(size, _NORMAL_BLOCK, DEBUG_CPP_NAME " new[]", 1);
#else
	return _malloc_dbg(size, _NORMAL_BLOCK, "(No CPP Name new[])", 1);
#endif
}

__forceinline void operator delete(void *ptr)
{
	_free_dbg(ptr, _NORMAL_BLOCK);
}

__forceinline void operator delete[](void *ptr)
{
	_free_dbg(ptr, _NORMAL_BLOCK);
}

#define new new (__FILE__, __LINE__)

#endif

