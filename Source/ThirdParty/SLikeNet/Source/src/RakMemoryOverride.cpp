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

#include "slikenet/memoryoverride.h"
#include "slikenet/assert.h"
#include <stdlib.h>

#ifdef _RAKNET_SUPPORT_DL_MALLOC
#include "rdlmalloc.h"
#endif







using namespace SLNet;

#if _USE_RAK_MEMORY_OVERRIDE==1
	#if defined(malloc)
	#pragma push_macro("malloc")
	#undef malloc
	#define RMO_MALLOC_UNDEF
	#endif

	#if defined(realloc)
	#pragma push_macro("realloc")
	#undef realloc
	#define RMO_REALLOC_UNDEF
	#endif

	#if defined(free)
	#pragma push_macro("free")
	#undef free
	#define RMO_FREE_UNDEF
	#endif
#endif

void DefaultOutOfMemoryHandler(const char *file, const long line)
{
	(void) file;
	(void) line;
	RakAssert(0);
}

void * (*rakMalloc) (size_t size) = SLNet::_RakMalloc;
void* (*rakRealloc) (void *p, size_t size) = SLNet::_RakRealloc;
void (*rakFree) (void *p) = SLNet::_RakFree;
void* (*rakMalloc_Ex) (size_t size, const char *file, unsigned int line) = SLNet::_RakMalloc_Ex;
void* (*rakRealloc_Ex) (void *p, size_t size, const char *file, unsigned int line) = SLNet::_RakRealloc_Ex;
void (*rakFree_Ex) (void *p, const char *file, unsigned int line) = SLNet::_RakFree_Ex;
void (*notifyOutOfMemory) (const char *file, const long line)=DefaultOutOfMemoryHandler;
void * (*dlMallocMMap) (size_t size) = SLNet::_DLMallocMMap;
void * (*dlMallocDirectMMap) (size_t size) = SLNet::_DLMallocDirectMMap;
int (*dlMallocMUnmap) (void* ptr, size_t size) = SLNet::_DLMallocMUnmap;

void SetMalloc( void* (*userFunction)(size_t size) )
{
	rakMalloc=userFunction;
}
void SetRealloc( void* (*userFunction)(void *p, size_t size) )
{
	rakRealloc=userFunction;
}
void SetFree( void (*userFunction)(void *p) )
{
	rakFree=userFunction;
}
void SetMalloc_Ex( void* (*userFunction)(size_t size, const char *file, unsigned int line) )
{
	rakMalloc_Ex=userFunction;
}
void SetRealloc_Ex( void* (*userFunction)(void *p, size_t size, const char *file, unsigned int line) )
{
	rakRealloc_Ex=userFunction;
}
void SetFree_Ex( void (*userFunction)(void *p, const char *file, unsigned int line) )
{
	rakFree_Ex=userFunction;
}
void SetNotifyOutOfMemory( void (*userFunction)(const char *file, const long line) )
{
	notifyOutOfMemory=userFunction;
}
void SetDLMallocMMap( void* (*userFunction)(size_t size) )
{
	dlMallocMMap=userFunction;
}
void SetDLMallocDirectMMap( void* (*userFunction)(size_t size) )
{
	dlMallocDirectMMap=userFunction;
}
void SetDLMallocMUnmap( int (*userFunction)(void* ptr, size_t size) )
{
	dlMallocMUnmap=userFunction;
}
void * (*GetMalloc()) (size_t size)
{
	return rakMalloc;
}
void * (*GetRealloc()) (void *p, size_t size)
{
	return rakRealloc;
}
void (*GetFree()) (void *p)
{
	return rakFree;
}
void * (*GetMalloc_Ex()) (size_t size, const char *file, unsigned int line)
{
	return rakMalloc_Ex;
}
void * (*GetRealloc_Ex()) (void *p, size_t size, const char *file, unsigned int line)
{
	return rakRealloc_Ex;
}
void (*GetFree_Ex()) (void *p, const char *file, unsigned int line)
{
	return rakFree_Ex;
}
void *(*GetDLMallocMMap())(size_t size)
{
	return dlMallocMMap;
}
void *(*GetDLMallocDirectMMap())(size_t size)
{
	return dlMallocDirectMMap;
}
int (*GetDLMallocMUnmap())(void* ptr, size_t size)
{
	return dlMallocMUnmap;
}
void* SLNet::_RakMalloc (size_t size)
{
	return malloc(size);
}

void* SLNet::_RakRealloc (void *p, size_t size)
{
	return realloc(p,size);
}

void SLNet::_RakFree (void *p)
{
	free(p);
}

void* SLNet::_RakMalloc_Ex (size_t size, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	return malloc(size);
}

void* SLNet::_RakRealloc_Ex (void *p, size_t size, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	return realloc(p,size);
}

void SLNet::_RakFree_Ex (void *p, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	free(p);
}
#ifdef _RAKNET_SUPPORT_DL_MALLOC
void * SLNet::_DLMallocMMap (size_t size)
{
	return RAK_MMAP_DEFAULT(size);
}
void * SLNet::_DLMallocDirectMMap (size_t size)
{
	return RAK_DIRECT_MMAP_DEFAULT(size);
}
int SLNet::_DLMallocMUnmap (void *p, size_t size)
{
	return RAK_MUNMAP_DEFAULT(p,size);
}

static mspace rakNetFixedHeapMSpace=0;

void* _DLMalloc(size_t size)
{
	return rak_mspace_malloc(rakNetFixedHeapMSpace,size);
}

void* _DLRealloc(void *p, size_t size)
{
	return rak_mspace_realloc(rakNetFixedHeapMSpace,p,size);
}

void _DLFree(void *p)
{
	if (p)
		rak_mspace_free(rakNetFixedHeapMSpace,p);
}
void* _DLMalloc_Ex (size_t size, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	return rak_mspace_malloc(rakNetFixedHeapMSpace,size);
}

void* _DLRealloc_Ex (void *p, size_t size, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	return rak_mspace_realloc(rakNetFixedHeapMSpace,p,size);
}

void _DLFree_Ex (void *p, const char *file, unsigned int line)
{
	(void) file;
	(void) line;

	if (p)
		rak_mspace_free(rakNetFixedHeapMSpace,p);
}

void UseRaknetFixedHeap(size_t initialCapacity,
						void * (*yourMMapFunction) (size_t size),
						void * (*yourDirectMMapFunction) (size_t size),
						int (*yourMUnmapFunction) (void *p, size_t size))
{
	SetDLMallocMMap(yourMMapFunction);
	SetDLMallocDirectMMap(yourDirectMMapFunction);
	SetDLMallocMUnmap(yourMUnmapFunction);
	SetMalloc(_DLMalloc);
	SetRealloc(_DLRealloc);
	SetFree(_DLFree);
	SetMalloc_Ex(_DLMalloc_Ex);
	SetRealloc_Ex(_DLRealloc_Ex);
	SetFree_Ex(_DLFree_Ex);

	rakNetFixedHeapMSpace=rak_create_mspace(initialCapacity, 0);
}
void FreeRakNetFixedHeap(void)
{
	if (rakNetFixedHeapMSpace)
	{
		rak_destroy_mspace(rakNetFixedHeapMSpace);
		rakNetFixedHeapMSpace=0;
	}

	SetMalloc(_RakMalloc);
	SetRealloc(_RakRealloc);
	SetFree(_RakFree);
	SetMalloc_Ex(_RakMalloc_Ex);
	SetRealloc_Ex(_RakRealloc_Ex);
	SetFree_Ex(_RakFree_Ex);
}
#else
void * SLNet::_DLMallocMMap (size_t size) {(void) size; return 0;}
void * SLNet::_DLMallocDirectMMap (size_t size) {(void) size; return 0;}
int SLNet::_DLMallocMUnmap (void *p, size_t size) {(void) size; (void) p; return 0;}
void* _DLMalloc(size_t size) {(void) size; return 0;}
void* _DLRealloc(void *p, size_t size) {(void) p; (void) size; return 0;}
void _DLFree(void *p) {(void) p;}
void* _DLMalloc_Ex (size_t size, const char *file, unsigned int line) {(void) size; (void) file; (void) line; return 0;}
void* _DLRealloc_Ex (void *p, size_t size, const char *file, unsigned int line) {(void) p; (void) size; (void) file; (void) line; return 0;}
void _DLFree_Ex (void *p, const char *file, unsigned int line) {(void) p; (void) file; (void) line;}

void UseRaknetFixedHeap(size_t initialCapacity,
						void * (*yourMMapFunction) (size_t size),
						void * (*yourDirectMMapFunction) (size_t size),
						int (*yourMUnmapFunction) (void *p, size_t size))
{
	(void) initialCapacity;
	(void) yourMMapFunction;
	(void) yourDirectMMapFunction;
	(void) yourMUnmapFunction;
}
void FreeRakNetFixedHeap(void) {}
#endif

#if _USE_RAK_MEMORY_OVERRIDE==1
	#if defined(RMO_MALLOC_UNDEF)
	#pragma pop_macro("malloc")
	#undef RMO_MALLOC_UNDEF
	#endif

	#if defined(RMO_REALLOC_UNDEF)
	#pragma pop_macro("realloc")
	#undef RMO_REALLOC_UNDEF
	#endif

	#if defined(RMO_FREE_UNDEF)
	#pragma pop_macro("free")
	#undef RMO_FREE_UNDEF
	#endif
#endif
