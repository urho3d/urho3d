/*
   AngelCode Scripting Library
   Copyright (c) 2003-2012 Andreas Jonsson

   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any 
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and 
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product 
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.

   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/

   Andreas Jonsson
   andreas@angelcode.com
*/



//
// as_thread.cpp
//
// Functions for multi threading support
//

#include "as_config.h"
#include "as_thread.h"
#include "as_atomic.h"

BEGIN_AS_NAMESPACE

//======================================================================

extern "C"
{

// Global API function
AS_API int asThreadCleanup()
{
	return asCThreadManager::CleanupLocalData();
}

}

//=======================================================================

// Singleton
static asCThreadManager *threadManager = 0;

#ifndef AS_NO_THREADS
static DECLARECRITICALSECTION(criticalSection)
#endif

//======================================================================

asCThreadManager::asCThreadManager()
{
	// We're already in the critical section when this function is called

#ifdef AS_NO_THREADS
	tld = 0;
#endif
	refCount = 1;
}

void asCThreadManager::AddRef()
{
	// It's necessary to protect this section to 
	// avoid two threads attempting to create thread
	// managers at the same time.
	ENTERCRITICALSECTION(criticalSection);

	if( threadManager == 0 )
		threadManager = asNEW(asCThreadManager);
	else
		threadManager->refCount++;

	LEAVECRITICALSECTION(criticalSection);
}

void asCThreadManager::Release()
{
	// It's necessary to protect this section so no
	// other thread attempts to call AddRef or Release
	// while clean up is in progress.
	ENTERCRITICALSECTION(criticalSection);
	if( --threadManager->refCount == 0 )
	{
		// The last engine has been destroyed, so we 
		// need to delete the thread manager as well
		asDELETE(threadManager,asCThreadManager);
		threadManager = 0;
	}
	LEAVECRITICALSECTION(criticalSection);
}

asCThreadManager::~asCThreadManager()
{
#ifndef AS_NO_THREADS
	// Delete all thread local datas
	asSMapNode<asPWORD,asCThreadLocalData*> *cursor = 0;
	if( tldMap.MoveFirst(&cursor) )
	{
		do
		{
			if( tldMap.GetValue(cursor) ) 
			{
				asDELETE(tldMap.GetValue(cursor),asCThreadLocalData);
			}
		} while( tldMap.MoveNext(&cursor, cursor) );
	}
#else
	if( tld ) 
	{
		asDELETE(tld,asCThreadLocalData);
	}
	tld = 0;
#endif
}

int asCThreadManager::CleanupLocalData()
{
#ifndef AS_NO_THREADS
	int r = 0;
#if defined AS_POSIX_THREADS
	asPWORD id = (asPWORD)pthread_self();
#elif defined AS_WINDOWS_THREADS
	asPWORD id = (asPWORD)GetCurrentThreadId();
#endif

	ENTERCRITICALSECTION(criticalSection);

	if( threadManager == 0 )
	{
		LEAVECRITICALSECTION(criticalSection);
		return 0;
	}

	asSMapNode<asPWORD,asCThreadLocalData*> *cursor = 0;
	if( threadManager->tldMap.MoveTo(&cursor, id) )
	{
		asCThreadLocalData *tld = threadManager->tldMap.GetValue(cursor);
		
		// Can we really remove it at this time?
		if( tld->activeContexts.GetLength() == 0 )
		{
			asDELETE(tld,asCThreadLocalData);
			threadManager->tldMap.Erase(cursor);
			r = 0;
		}
		else
			r = asCONTEXT_ACTIVE;
	}

	LEAVECRITICALSECTION(criticalSection);

	return r;
#else
	if( threadManager && threadManager->tld )
	{
		if( threadManager->tld->activeContexts.GetLength() == 0 )
		{
			asDELETE(threadManager->tld,asCThreadLocalData);
			threadManager->tld = 0;
		}
		else
			return asCONTEXT_ACTIVE;
	}
	return 0;
#endif
}

#ifndef AS_NO_THREADS
asCThreadLocalData *asCThreadManager::GetLocalData(asPWORD threadId)
{
	// We're already in the critical section when this function is called

	asCThreadLocalData *tld = 0;

	asSMapNode<asPWORD,asCThreadLocalData*> *cursor = 0;
	if( threadManager->tldMap.MoveTo(&cursor, threadId) )
		tld = threadManager->tldMap.GetValue(cursor);

	return tld;
}

void asCThreadManager::SetLocalData(asPWORD threadId, asCThreadLocalData *tld)
{
	// We're already in the critical section when this function is called

	tldMap.Insert(threadId, tld);
}
#endif

asCThreadLocalData *asCThreadManager::GetLocalData()
{
#ifndef AS_NO_THREADS
#if defined AS_POSIX_THREADS
	asPWORD id = (asPWORD)pthread_self();
#elif defined AS_WINDOWS_THREADS
	asPWORD id = (asPWORD)GetCurrentThreadId();
#endif

	ENTERCRITICALSECTION(criticalSection);

	asASSERT(threadManager);

	if( threadManager == 0 )
	{
		LEAVECRITICALSECTION(criticalSection);
		return 0;
	}

	asCThreadLocalData *tld = threadManager->GetLocalData(id);
	if( tld == 0 )
	{
		// Create a new tld
		tld = asNEW(asCThreadLocalData)();
		threadManager->SetLocalData(id, tld);
	}

	LEAVECRITICALSECTION(criticalSection);

	return tld;
#else
	if( threadManager == 0 )
		return 0;

	if( threadManager->tld == 0 )
		threadManager->tld = asNEW(asCThreadLocalData)();

	return threadManager->tld;
#endif
}

//=========================================================================

asCThreadLocalData::asCThreadLocalData()
{
}

asCThreadLocalData::~asCThreadLocalData()
{
}

//=========================================================================

#ifndef AS_NO_THREADS
asCThreadCriticalSection::asCThreadCriticalSection()
{
#if defined AS_POSIX_THREADS
	pthread_mutex_init(&criticalSection, 0);
#elif defined AS_WINDOWS_THREADS
	InitializeCriticalSection(&criticalSection);
#endif
}

asCThreadCriticalSection::~asCThreadCriticalSection()
{
#if defined AS_POSIX_THREADS
	pthread_mutex_destroy(&criticalSection);
#elif defined AS_WINDOWS_THREADS
	DeleteCriticalSection(&criticalSection);
#endif
}

void asCThreadCriticalSection::Enter()
{
#if defined AS_POSIX_THREADS
	pthread_mutex_lock(&criticalSection);
#elif defined AS_WINDOWS_THREADS
	EnterCriticalSection(&criticalSection);
#endif
}

void asCThreadCriticalSection::Leave()
{
#if defined AS_POSIX_THREADS
	pthread_mutex_unlock(&criticalSection);
#elif defined AS_WINDOWS_THREADS
	LeaveCriticalSection(&criticalSection);
#endif
}

bool asCThreadCriticalSection::TryEnter()
{
#if defined AS_POSIX_THREADS
	return !pthread_mutex_trylock(&criticalSection);
#elif defined AS_WINDOWS_THREADS
	return TryEnterCriticalSection(&criticalSection) ? true : false;
#else
	return true;
#endif
}
#endif

//========================================================================

END_AS_NAMESPACE

