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
// as_thread.h
//
// Classes for multi threading support
//

#ifndef AS_THREAD_H
#define AS_THREAD_H

#include "as_config.h"
#include "as_string.h"
#include "as_array.h"
#include "as_map.h"
#include "as_criticalsection.h"

BEGIN_AS_NAMESPACE

class asCThreadLocalData;

class asCThreadManager
{
public:
	static asCThreadLocalData *GetLocalData();
	static int CleanupLocalData();

	static void AddRef();
	static void Release();

protected:
	asCThreadManager();
	~asCThreadManager();

	// No need to use the atomic int here, as it will only be
	// updated within the thread manager's critical section
	int refCount;

#ifndef AS_NO_THREADS
	asCThreadLocalData *GetLocalData(asPWORD threadId);
	void SetLocalData(asPWORD threadId, asCThreadLocalData *tld);

	asCMap<asPWORD,asCThreadLocalData*> tldMap;
#else
	asCThreadLocalData *tld;
#endif
};

//======================================================================

class asIScriptContext;

class asCThreadLocalData
{
public:
	asCArray<asIScriptContext *> activeContexts;
	asCString string;

protected:
	friend class asCThreadManager;

	asCThreadLocalData();
	~asCThreadLocalData();
};

END_AS_NAMESPACE

#endif
