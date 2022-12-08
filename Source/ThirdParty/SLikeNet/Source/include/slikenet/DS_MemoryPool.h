/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file DS_MemoryPool.h
///


#ifndef __MEMORY_POOL_H
#define __MEMORY_POOL_H

#ifndef __APPLE__
// Use stdlib and not malloc for compatibility
#include <stdlib.h>
#endif
#include "assert.h"
#include "Export.h"

#include "memoryoverride.h"

// DS_MEMORY_POOL_MAX_FREE_PAGES must be > 1
#define DS_MEMORY_POOL_MAX_FREE_PAGES 4

//#define _DISABLE_MEMORY_POOL

namespace DataStructures
{
	/// Very fast memory pool for allocating and deallocating structures that don't have constructors or destructors.
	/// Contains a list of pages, each of which has an array of the user structures
	template <class MemoryBlockType>
	class RAK_DLL_EXPORT MemoryPool
	{
	public:
		struct Page;
		struct MemoryWithPage
		{
			MemoryBlockType userMemory;
			Page *parentPage;
		};
		struct Page
		{
			MemoryWithPage** availableStack;
			int availableStackSize;
			MemoryWithPage* block;
			Page *next, *prev;
		};

		MemoryPool();
		~MemoryPool();
		void SetPageSize(int size); // Defaults to 16384 bytes
		MemoryBlockType *Allocate(const char *file, unsigned int line);
		void Release(MemoryBlockType *m, const char *file, unsigned int line);
		void Clear(const char *file, unsigned int line);

		int GetAvailablePagesSize(void) const {return availablePagesSize;}
		int GetUnavailablePagesSize(void) const {return unavailablePagesSize;}
		int GetMemoryPoolPageSize(void) const {return memoryPoolPageSize;}
	protected:
		int BlocksPerPage(void) const;
		void AllocateFirst(void);
		bool InitPage(Page *page, Page *prev, const char *file, unsigned int line);

		// availablePages contains pages which have room to give the user new blocks.  We return these blocks from the head of the list
		// unavailablePages are pages which are totally full, and from which we do not return new blocks.
		// Pages move from the head of unavailablePages to the tail of availablePages, and from the head of availablePages to the tail of unavailablePages
		Page *availablePages, *unavailablePages;
		int availablePagesSize, unavailablePagesSize;
		int memoryPoolPageSize;
	};

	template<class MemoryBlockType>
	MemoryPool<MemoryBlockType>::MemoryPool()
	{
#ifndef _DISABLE_MEMORY_POOL
		//AllocateFirst();
		availablePagesSize=0;
		unavailablePagesSize=0;
		memoryPoolPageSize=16384;
#endif
	}
	template<class MemoryBlockType>
	MemoryPool<MemoryBlockType>::~MemoryPool()
	{
#ifndef _DISABLE_MEMORY_POOL
		Clear(_FILE_AND_LINE_);
#endif
	}

	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::SetPageSize(int size)
	{
		memoryPoolPageSize=size;
	}

	template<class MemoryBlockType>
	MemoryBlockType* MemoryPool<MemoryBlockType>::Allocate(const char *file, unsigned int line)
	{
#ifdef _DISABLE_MEMORY_POOL
		return (MemoryBlockType*) rakMalloc_Ex(sizeof(MemoryBlockType), file, line);
#else

		if (availablePagesSize>0)
		{
			MemoryBlockType *retVal;
			Page *curPage;
			curPage=availablePages;
			retVal = (MemoryBlockType*) curPage->availableStack[--(curPage->availableStackSize)];
			if (curPage->availableStackSize==0)
			{
				--availablePagesSize;
				availablePages=curPage->next;
				RakAssert(availablePagesSize==0 || availablePages->availableStackSize>0);
				curPage->next->prev=curPage->prev;
				curPage->prev->next=curPage->next;

				if (unavailablePagesSize++==0)
				{
					unavailablePages=curPage;
					curPage->next=curPage;
					curPage->prev=curPage;	
				}
				else
				{
					curPage->next=unavailablePages;
					curPage->prev=unavailablePages->prev;
					unavailablePages->prev->next=curPage;
					unavailablePages->prev=curPage;
				}			
			}

			RakAssert(availablePagesSize==0 || availablePages->availableStackSize>0);
			return retVal;
		}

		availablePages = (Page *) rakMalloc_Ex(sizeof(Page), file, line);
		if (availablePages==0)
			return 0;
		availablePagesSize=1;
		if (InitPage(availablePages, availablePages, file, line)==false)
			return 0;
		// If this assert hits, we couldn't allocate even 1 block per page. Increase the page size
		RakAssert(availablePages->availableStackSize>1);

		return (MemoryBlockType *) availablePages->availableStack[--availablePages->availableStackSize];
#endif
	}
	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::Release(MemoryBlockType *m, const char *file, unsigned int line)
	{
#ifdef _DISABLE_MEMORY_POOL
		rakFree_Ex(m, file, line);
		return;
#else
		// Find the page this block is in and return it.
		Page *curPage;
		MemoryWithPage *memoryWithPage = (MemoryWithPage*)m;
		curPage=memoryWithPage->parentPage;

		if (curPage->availableStackSize==0)
		{
			// The page is in the unavailable list so move it to the available list
			curPage->availableStack[curPage->availableStackSize++]=memoryWithPage;
			unavailablePagesSize--;

			// As this page is no longer totally empty, move it to the end of available pages
			curPage->next->prev=curPage->prev;
			curPage->prev->next=curPage->next;
			
			if (unavailablePagesSize>0 && curPage==unavailablePages)
				unavailablePages=unavailablePages->next;
			
			if (availablePagesSize++==0)
			{
				availablePages=curPage;
				curPage->next=curPage;
				curPage->prev=curPage;
			}
			else
			{
				curPage->next=availablePages;
				curPage->prev=availablePages->prev;
				availablePages->prev->next=curPage;
				availablePages->prev=curPage;	
			}
		}
		else
		{
			curPage->availableStack[curPage->availableStackSize++]=memoryWithPage;

			if (curPage->availableStackSize==BlocksPerPage() &&
				availablePagesSize>=DS_MEMORY_POOL_MAX_FREE_PAGES)
			{
				// After a certain point, just deallocate empty pages rather than keep them around
				if (curPage==availablePages)
				{
					availablePages=curPage->next;
					RakAssert(availablePages->availableStackSize>0);
				}
				curPage->prev->next=curPage->next;
				curPage->next->prev=curPage->prev;
				availablePagesSize--;
				rakFree_Ex(curPage->availableStack, file, line );
				rakFree_Ex(curPage->block, file, line );
				rakFree_Ex(curPage, file, line );
			}
		}
#endif
	}
	template<class MemoryBlockType>
	void MemoryPool<MemoryBlockType>::Clear(const char *file, unsigned int line)
	{
#ifdef _DISABLE_MEMORY_POOL
		return;
#else
		Page *cur, *freed;

		if (availablePagesSize>0)
		{
			cur = availablePages;
			for (;;)
			// do
			{
				rakFree_Ex(cur->availableStack, file, line );
				rakFree_Ex(cur->block, file, line );
				freed=cur;
				cur=cur->next;
				if (cur==availablePages)
				{
					rakFree_Ex(freed, file, line );
					break;
				}
				rakFree_Ex(freed, file, line );
			}// while(cur!=availablePages);
		}
		
		if (unavailablePagesSize>0)
		{
			cur = unavailablePages;
			for(;;)
			//do 
			{
				rakFree_Ex(cur->availableStack, file, line );
				rakFree_Ex(cur->block, file, line );
				freed=cur;
				cur=cur->next;
				if (cur==unavailablePages)
				{
					rakFree_Ex(freed, file, line );
					break;
				}
				rakFree_Ex(freed, file, line );
			} // while(cur!=unavailablePages);
		}

		availablePagesSize=0;
		unavailablePagesSize=0;
#endif
	}
	template<class MemoryBlockType>
	int MemoryPool<MemoryBlockType>::BlocksPerPage(void) const
	{
		return memoryPoolPageSize / sizeof(MemoryWithPage);
	}
	template<class MemoryBlockType>
	bool MemoryPool<MemoryBlockType>::InitPage(Page *page, Page *prev, const char *file, unsigned int line)
	{
		int i=0;
		const int bpp = BlocksPerPage();
		page->block=(MemoryWithPage*) rakMalloc_Ex(memoryPoolPageSize, file, line);
		if (page->block==0)
			return false;
		page->availableStack=(MemoryWithPage**)rakMalloc_Ex(sizeof(MemoryWithPage*)*bpp, file, line);
		if (page->availableStack==0)
		{
			rakFree_Ex(page->block, file, line );
			return false;
		}
		MemoryWithPage *curBlock = page->block;
		MemoryWithPage **curStack = page->availableStack;
		while (i < bpp)
		{
			curBlock->parentPage=page;
			curStack[i]=curBlock++;
			i++;
		}
		page->availableStackSize=bpp;
		page->next=availablePages;
		page->prev=prev;
		return true;
	}
}

#endif

/*
#include "DS_MemoryPool.h"
#include "DS_List.h"

struct TestMemoryPool
{
	int allocationId;
};

int main(void)
{
	DataStructures::MemoryPool<TestMemoryPool> memoryPool;
	DataStructures::List<TestMemoryPool*> returnList;

	for (int i=0; i < 100000; i++)
		returnList.Push(memoryPool.Allocate(_FILE_AND_LINE_), _FILE_AND_LINE_);
	for (int i=0; i < returnList.Size(); i+=2)
	{
		memoryPool.Release(returnList[i], _FILE_AND_LINE_);
		returnList.RemoveAtIndexFast(i);
	}
	for (int i=0; i < 100000; i++)
		returnList.Push(memoryPool.Allocate(_FILE_AND_LINE_), _FILE_AND_LINE_);
	while (returnList.Size())
	{
		memoryPool.Release(returnList[returnList.Size()-1], _FILE_AND_LINE_);
		returnList.RemoveAtIndex(returnList.Size()-1);
	}
	for (int i=0; i < 100000; i++)
		returnList.Push(memoryPool.Allocate(_FILE_AND_LINE_), _FILE_AND_LINE_);
	while (returnList.Size())
	{
		memoryPool.Release(returnList[returnList.Size()-1], _FILE_AND_LINE_);
		returnList.RemoveAtIndex(returnList.Size()-1);
	}
	for (int i=0; i < 100000; i++)
		returnList.Push(memoryPool.Allocate(_FILE_AND_LINE_), _FILE_AND_LINE_);
	for (int i=100000-1; i <= 0; i-=2)
	{
		memoryPool.Release(returnList[i], _FILE_AND_LINE_);
		returnList.RemoveAtIndexFast(i);
	}
	for (int i=0; i < 100000; i++)
		returnList.Push(memoryPool.Allocate(_FILE_AND_LINE_), _FILE_AND_LINE_);
	while (returnList.Size())
	{
		memoryPool.Release(returnList[returnList.Size()-1], _FILE_AND_LINE_);
		returnList.RemoveAtIndex(returnList.Size()-1);
	}

	return 0;
}
*/
