/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#ifndef _ODE_UTIL_H_
#define _ODE_UTIL_H_

#include "objects.h"


/* the efficient alignment. most platforms align data structures to some
 * number of bytes, but this is not always the most efficient alignment.
 * for example, many x86 compilers align to 4 bytes, but on a pentium it
 * is important to align doubles to 8 byte boundaries (for speed), and
 * the 4 floats in a SIMD register to 16 byte boundaries. many other
 * platforms have similar behavior. setting a larger alignment can waste
 * a (very) small amount of memory. NOTE: this number must be a power of
 * two. this is set to 16 by default.
 */
#ifndef EFFICIENT_ALIGNMENT
#define EFFICIENT_ALIGNMENT 16
#endif


/* utility */


/* round something up to be a multiple of the EFFICIENT_ALIGNMENT */

#define dEFFICIENT_SIZE(x) (((x)+(EFFICIENT_ALIGNMENT-1)) & ~((size_t)(EFFICIENT_ALIGNMENT-1)))
#define dEFFICIENT_PTR(p) ((void *)dEFFICIENT_SIZE((size_t)(p)))
#define dOFFSET_EFFICIENTLY(p, b) ((void *)((size_t)(p) + dEFFICIENT_SIZE(b)))

/* alloca aligned to the EFFICIENT_ALIGNMENT. note that this can waste
 * up to 15 bytes per allocation, depending on what alloca() returns.
 */

#define dALLOCA16(n) \
  ((char*)dEFFICIENT_PTR(alloca((n)+(EFFICIENT_ALIGNMENT-1))))


#ifndef SIZE_MAX
#define SIZE_MAX  ((size_t)(-1))
#endif

void dInternalHandleAutoDisabling (dxWorld *world, dReal stepsize);
void dxStepBody (dxBody *b, dReal h);


struct dxWorldProcessMemoryManager:
  public dBase
{
  typedef void *(*alloc_block_fn_t)(size_t block_size);
  typedef void *(*shrink_block_fn_t)(void *block_pointer, size_t block_current_size, size_t block_smaller_size);
  typedef void (*free_block_fn_t)(void *block_pointer, size_t block_current_size);
  
  dxWorldProcessMemoryManager(alloc_block_fn_t fnAlloc, shrink_block_fn_t fnShrink, free_block_fn_t fnFree)
  {
    Assign(fnAlloc, fnShrink, fnFree);
  }

  void Assign(alloc_block_fn_t fnAlloc, shrink_block_fn_t fnShrink, free_block_fn_t fnFree)
  {
    m_fnAlloc = fnAlloc;
    m_fnShrink = fnShrink;
    m_fnFree = fnFree;
  }

  alloc_block_fn_t m_fnAlloc;
  shrink_block_fn_t m_fnShrink;
  free_block_fn_t m_fnFree;
};

extern dxWorldProcessMemoryManager g_WorldProcessMallocMemoryManager;

struct dxWorldProcessMemoryReserveInfo:
  public dBase
{
  dxWorldProcessMemoryReserveInfo(float fReserveFactor, unsigned uiReserveMinimum)
  {
    Assign(fReserveFactor, uiReserveMinimum);
  }

  void Assign(float fReserveFactor, unsigned uiReserveMinimum)
  {
    m_fReserveFactor = fReserveFactor;
    m_uiReserveMinimum = uiReserveMinimum;
  }

  float m_fReserveFactor; // Use float as precision does not matter here
  unsigned m_uiReserveMinimum;
};

extern dxWorldProcessMemoryReserveInfo g_WorldProcessDefaultReserveInfo;


struct dxWorldProcessContext
{
#define BUFFER_TO_ARENA_EXTRA (EFFICIENT_ALIGNMENT + dEFFICIENT_SIZE(sizeof(dxWorldProcessContext)))
  static bool IsArenaPossible(size_t nBufferSize)
  {
    return SIZE_MAX - BUFFER_TO_ARENA_EXTRA >= nBufferSize; // This ensures there will be no overflow
  }

  static size_t MakeBufferSize(size_t nArenaSize)
  {
    return nArenaSize - BUFFER_TO_ARENA_EXTRA;
  }

  static size_t MakeArenaSize(size_t nBufferSize)
  {
    return BUFFER_TO_ARENA_EXTRA + nBufferSize;
  }
#undef BUFFER_TO_ARENA_EXTRA

  bool IsStructureValid() const
  {
    return !m_pPreallocationcContext && m_pAllocBegin && m_pAllocEnd && m_pAllocBegin <= m_pAllocEnd && m_pAllocCurrent == m_pAllocBegin && m_pArenaBegin && m_pArenaBegin <= m_pAllocBegin; 
  }

  size_t GetMemorySize() const
  {
    return (size_t)m_pAllocEnd - (size_t)m_pAllocBegin;
  }

  void *SaveState() const
  {
    return m_pAllocCurrent;
  }

  void RestoreState(void *state)
  {
    m_pAllocCurrent = state;
  }

  void ResetState()
  {
    m_pAllocCurrent = m_pAllocBegin;
  }

  void *PeekBufferRemainder() const
  {
    return m_pAllocCurrent;
  }

  void *AllocateBlock(size_t size)
  {
    void *block = m_pAllocCurrent;
    m_pAllocCurrent = dOFFSET_EFFICIENTLY(block, size);
    dIASSERT(m_pAllocCurrent <= m_pAllocEnd);
    return block;
  }

  template<typename ElementType>
  ElementType *AllocateArray(size_t count)
  {
    return (ElementType *)AllocateBlock(count * sizeof(ElementType));
  }

  template<typename ElementType>
  void ShrinkArray(ElementType *arr, size_t oldcount, size_t newcount)
  {
    dIASSERT(newcount <= oldcount);
    dIASSERT(dOFFSET_EFFICIENTLY(arr, oldcount * sizeof(ElementType)) == m_pAllocCurrent);
    m_pAllocCurrent = dOFFSET_EFFICIENTLY(arr, newcount * sizeof(ElementType));
  }



  void CleanupContext();

  void SavePreallocations(int islandcount, int const *islandsizes, dxBody *const *bodies, dxJoint *const *joints);
  void RetrievePreallocations(int &islandcount, int const *&islandsizes, dxBody *const *&bodies, dxJoint *const *&joints);
  void OffsetPreallocations(size_t stOffset);
  void CopyPreallocations(const dxWorldProcessContext *othercontext);
  void ClearPreallocations();

  void FreePreallocationsContext();
  bool IsPreallocationsContextAssigned() const { return m_pPreallocationcContext != NULL; }


  void *m_pAllocBegin;
  void *m_pAllocEnd;
  void *m_pAllocCurrent;
  void *m_pArenaBegin;

  int m_IslandCount;
  int const *m_pIslandSizes;
  dxBody *const *m_pBodies;
  dxJoint *const *m_pJoints;

  const dxWorldProcessMemoryManager *m_pArenaMemMgr;
  dxWorldProcessContext *m_pPreallocationcContext;
};



#define BEGIN_STATE_SAVE(context, state) void *state = context->SaveState();
#define END_STATE_SAVE(context, state) context->RestoreState(state)

typedef void (*dstepper_fn_t) (dxWorldProcessContext *context, 
        dxWorld *world, dxBody * const *body, int nb,
        dxJoint * const *_joint, int _nj, dReal stepsize);

void dxProcessIslands (dxWorld *world, dReal stepsize, dstepper_fn_t stepper);


typedef size_t (*dmemestimate_fn_t) (dxBody * const *body, int nb, 
  dxJoint * const *_joint, int _nj);

bool dxReallocateWorldProcessContext (dxWorld *world, 
  dReal stepsize, dmemestimate_fn_t stepperestimate);
dxWorldProcessContext *dxReallocateTemporayWorldProcessContext(dxWorldProcessContext *oldcontext, 
  size_t memreq, const dxWorldProcessMemoryManager *memmgr/*=NULL*/, const dxWorldProcessMemoryReserveInfo *reserveinfo/*=NULL*/);
void dxFreeWorldProcessContext (dxWorldProcessContext *context);




// World stepping working memory object
class dxStepWorkingMemory:
  public dBase
{
public:
  dxStepWorkingMemory(): m_uiRefCount(1), m_ppcProcessingContext(NULL), m_priReserveInfo(NULL), m_pmmMemoryManager(NULL) {}

private:
  friend struct dBase; // To avoid GCC warning regarding private destructor
  ~dxStepWorkingMemory() // Use Release() instead
  {
    if (m_ppcProcessingContext) dxFreeWorldProcessContext(m_ppcProcessingContext);
    delete m_priReserveInfo;
    delete m_pmmMemoryManager;
  }

public:
  void Addref()
  {
    dIASSERT(~m_uiRefCount != 0);
    ++m_uiRefCount;
  }

  void Release()
  {
    dIASSERT(m_uiRefCount != 0);
    if (--m_uiRefCount == 0)
    {
      delete this;
    }
  }

public:
  void CleanupMemory()
  {
    if (m_ppcProcessingContext)
    {
      dxFreeWorldProcessContext(m_ppcProcessingContext);
      m_ppcProcessingContext = NULL;
    }
  }

public: 
  dxWorldProcessContext *GetWorldProcessingContext() const { return m_ppcProcessingContext; }
  void SetWorldProcessingContext(dxWorldProcessContext *ppcInstance) { m_ppcProcessingContext = ppcInstance; }

  const dxWorldProcessMemoryReserveInfo *GetMemoryReserveInfo() const { return m_priReserveInfo; }
  const dxWorldProcessMemoryReserveInfo *SureGetMemoryReserveInfo() const { return m_priReserveInfo ? m_priReserveInfo : &g_WorldProcessDefaultReserveInfo; }
  void SetMemoryReserveInfo(float fReserveFactor, unsigned uiReserveMinimum)
  {
    if (m_priReserveInfo) { m_priReserveInfo->Assign(fReserveFactor, uiReserveMinimum); }
    else { m_priReserveInfo = new dxWorldProcessMemoryReserveInfo(fReserveFactor, uiReserveMinimum); }
  }
  void ResetMemoryReserveInfoToDefault()
  {
    if (m_priReserveInfo) { delete m_priReserveInfo; m_priReserveInfo = NULL; }
  }

  const dxWorldProcessMemoryManager *GetMemoryManager() const { return m_pmmMemoryManager; }
  const dxWorldProcessMemoryManager *SureGetMemoryManager() const { return m_pmmMemoryManager ? m_pmmMemoryManager : &g_WorldProcessMallocMemoryManager; }
  void SetMemoryManager(dxWorldProcessMemoryManager::alloc_block_fn_t fnAlloc, 
    dxWorldProcessMemoryManager::shrink_block_fn_t fnShrink, 
    dxWorldProcessMemoryManager::free_block_fn_t fnFree) 
  {
    if (m_pmmMemoryManager) { m_pmmMemoryManager->Assign(fnAlloc, fnShrink, fnFree); }
    else { m_pmmMemoryManager = new dxWorldProcessMemoryManager(fnAlloc, fnShrink, fnFree); }
  }
  void ResetMemoryManagerToDefault()
  {
    if (m_pmmMemoryManager) { delete m_pmmMemoryManager; m_pmmMemoryManager = NULL; }
  }

private:
  unsigned m_uiRefCount;
  dxWorldProcessContext *m_ppcProcessingContext;
  dxWorldProcessMemoryReserveInfo *m_priReserveInfo;
  dxWorldProcessMemoryManager *m_pmmMemoryManager;
};

template<class ClassType>
inline ClassType *AllocateOnDemand(ClassType *&pctStorage)
{
  ClassType *pctCurrentInstance = pctStorage;

  if (!pctCurrentInstance)
  {
    pctCurrentInstance = new ClassType();
    pctStorage = pctCurrentInstance;
  }

  return pctCurrentInstance;
}

#endif
