/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief If _USE_RAK_MEMORY_OVERRIDE is defined, memory allocations go through rakMalloc, rakRealloc, and rakFree
///



#ifndef __RAK_MEMORY_H
#define __RAK_MEMORY_H

#include "Export.h"
#include "defines.h"
#include <new>







#include "alloca.h"

// #if _USE_RAK_MEMORY_OVERRIDE==1
// 	#if defined(new)
// 		#pragma push_macro("new")
// 		#undef new
// 		#define RMO_NEW_UNDEF
// 	#endif
// #endif


// These pointers are statically and globally defined in RakMemoryOverride.cpp
// Change them to point to your own allocators if you want.
// Use the functions for a DLL, or just reassign the variable if using source
extern RAK_DLL_EXPORT void * (*rakMalloc) (size_t size);
extern RAK_DLL_EXPORT void * (*rakRealloc) (void *p, size_t size);
extern RAK_DLL_EXPORT void (*rakFree) (void *p);
extern RAK_DLL_EXPORT void * (*rakMalloc_Ex) (size_t size, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void * (*rakRealloc_Ex) (void *p, size_t size, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void (*rakFree_Ex) (void *p, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void (*notifyOutOfMemory) (const char *file, const long line);
extern RAK_DLL_EXPORT void * (*dlMallocMMap) (size_t size);
extern RAK_DLL_EXPORT void * (*dlMallocDirectMMap) (size_t size);
extern RAK_DLL_EXPORT int (*dlMallocMUnmap) (void* ptr, size_t size);

// Change to a user defined allocation function
void RAK_DLL_EXPORT SetMalloc( void* (*userFunction)(size_t size) );
void RAK_DLL_EXPORT SetRealloc( void* (*userFunction)(void *p, size_t size) );
void RAK_DLL_EXPORT SetFree( void (*userFunction)(void *p) );
void RAK_DLL_EXPORT SetMalloc_Ex( void* (*userFunction)(size_t size, const char *file, unsigned int line) );
void RAK_DLL_EXPORT SetRealloc_Ex( void* (*userFunction)(void *p, size_t size, const char *file, unsigned int line) );
void RAK_DLL_EXPORT SetFree_Ex( void (*userFunction)(void *p, const char *file, unsigned int line) );
// Change to a user defined out of memory function
void RAK_DLL_EXPORT SetNotifyOutOfMemory( void (*userFunction)(const char *file, const long line) );
void RAK_DLL_EXPORT SetDLMallocMMap( void* (*userFunction)(size_t size) );
void RAK_DLL_EXPORT SetDLMallocDirectMMap( void* (*userFunction)(size_t size) );
void RAK_DLL_EXPORT SetDLMallocMUnmap( int (*userFunction)(void* ptr, size_t size) );

extern RAK_DLL_EXPORT void * (*GetMalloc()) (size_t size);
extern RAK_DLL_EXPORT void * (*GetRealloc()) (void *p, size_t size);
extern RAK_DLL_EXPORT void (*GetFree()) (void *p);
extern RAK_DLL_EXPORT void * (*GetMalloc_Ex()) (size_t size, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void * (*GetRealloc_Ex()) (void *p, size_t size, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void (*GetFree_Ex()) (void *p, const char *file, unsigned int line);
extern RAK_DLL_EXPORT void *(*GetDLMallocMMap())(size_t size);
extern RAK_DLL_EXPORT void *(*GetDLMallocDirectMMap())(size_t size);
extern RAK_DLL_EXPORT int (*GetDLMallocMUnmap())(void* ptr, size_t size);

namespace SLNet
{

	template <class Type>
	RAK_DLL_EXPORT Type* OP_NEW(const char *file, unsigned int line)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(Type), file, line);
		Type *t = new (buffer) Type;
		return t;
#else
		(void) file;
		(void) line;
		return new Type;
#endif
	}

	template <class Type, class P1>
	RAK_DLL_EXPORT Type* OP_NEW_1(const char *file, unsigned int line, const P1 &p1)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(Type), file, line);
		Type *t = new (buffer) Type(p1);
		return t;
#else
		(void) file;
		(void) line;
		return new Type(p1);
#endif
	}

	template <class Type, class P1, class P2>
	RAK_DLL_EXPORT Type* OP_NEW_2(const char *file, unsigned int line, const P1 &p1, const P2 &p2)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(Type), file, line);
		Type *t = new (buffer) Type(p1, p2);
		return t;
#else
		(void) file;
		(void) line;
		return new Type(p1, p2);
#endif
	}

	template <class Type, class P1, class P2, class P3>
	RAK_DLL_EXPORT Type* OP_NEW_3(const char *file, unsigned int line, const P1 &p1, const P2 &p2, const P3 &p3)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(Type), file, line);
		Type *t = new (buffer) Type(p1, p2, p3);
		return t;
#else
		(void) file;
		(void) line;
		return new Type(p1, p2, p3);
#endif
	}

	template <class Type, class P1, class P2, class P3, class P4>
	RAK_DLL_EXPORT Type* OP_NEW_4(const char *file, unsigned int line, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(Type), file, line);
		Type *t = new (buffer) Type(p1, p2, p3, p4);
		return t;
#else
		(void) file;
		(void) line;
		return new Type(p1, p2, p3, p4);
#endif
	}


	template <class Type>
	RAK_DLL_EXPORT Type* OP_NEW_ARRAY(const int count, const char *file, unsigned int line)
	{
		if (count==0)
			return 0;

#if _USE_RAK_MEMORY_OVERRIDE==1
//		Type *t;
		char *buffer = (char *) (GetMalloc_Ex())(sizeof(int)+sizeof(Type)*count, file, line);
		((int*)buffer)[0]=count;
		for (int i=0; i<count; i++)
		{
			//t = 
				new(buffer+sizeof(int)+i*sizeof(Type)) Type;
		}
		return (Type *) (buffer+sizeof(int));
#else
		(void) file;
		(void) line;
		return new Type[count];
#endif

	}

	template <class Type>
	RAK_DLL_EXPORT void OP_DELETE(Type *buff, const char *file, unsigned int line)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		if (buff==0) return;
		buff->~Type();
		(GetFree_Ex())((char*)buff, file, line );
#else
		(void) file;
		(void) line;
		delete buff;
#endif

	}

	template <class Type>
	RAK_DLL_EXPORT void OP_DELETE_ARRAY(Type *buff, const char *file, unsigned int line)
	{
#if _USE_RAK_MEMORY_OVERRIDE==1
		if (buff==0)
			return;

		int count = ((int*)((char*)buff-sizeof(int)))[0];
		Type *t;
		for (int i=0; i<count; i++)
		{
			t = buff+i;
			t->~Type();
		}
		(GetFree_Ex())((char*)buff-sizeof(int), file, line );
#else
		(void) file;
		(void) line;
		delete [] buff;
#endif

	}

	void RAK_DLL_EXPORT * _RakMalloc (size_t size);
	void RAK_DLL_EXPORT * _RakRealloc (void *p, size_t size);
	void RAK_DLL_EXPORT _RakFree (void *p);
	void RAK_DLL_EXPORT * _RakMalloc_Ex (size_t size, const char *file, unsigned int line);
	void RAK_DLL_EXPORT * _RakRealloc_Ex (void *p, size_t size, const char *file, unsigned int line);
	void RAK_DLL_EXPORT _RakFree_Ex (void *p, const char *file, unsigned int line);
	void RAK_DLL_EXPORT * _DLMallocMMap (size_t size);
	void RAK_DLL_EXPORT * _DLMallocDirectMMap (size_t size);
	int RAK_DLL_EXPORT _DLMallocMUnmap (void *p, size_t size);

}

// Call to make RakNet allocate a large block of memory, and do all subsequent allocations in that memory block
// Initial and reallocations will be done through whatever function is pointed to by yourMMapFunction, and yourDirectMMapFunction (default is malloc)
// Allocations will be freed through whatever function is pointed to by yourMUnmapFunction (default free)
void UseRaknetFixedHeap(size_t initialCapacity,
						void * (*yourMMapFunction) (size_t size) = SLNet::_DLMallocMMap,
						void * (*yourDirectMMapFunction) (size_t size) = SLNet::_DLMallocDirectMMap,
						int (*yourMUnmapFunction) (void *p, size_t size) = SLNet::_DLMallocMUnmap);

// Free memory allocated from UseRaknetFixedHeap
void FreeRakNetFixedHeap(void);

// #if _USE_RAK_MEMORY_OVERRIDE==1
// 	#if defined(RMO_NEW_UNDEF)
// 	#pragma pop_macro("new")
// 	#undef RMO_NEW_UNDEF
// 	#endif
// #endif

#endif
