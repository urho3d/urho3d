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
// as_property.h
//
// A class for storing object property information
//



#ifndef AS_PROPERTY_H
#define AS_PROPERTY_H

#include "as_string.h"
#include "as_datatype.h"
#include "as_atomic.h"
#include "as_scriptfunction.h"

BEGIN_AS_NAMESPACE

class asCObjectProperty
{
public:
	asCObjectProperty() {accessMask = 0xFFFFFFFF;}
	asCString   name;
	asCDataType type;
	int         byteOffset;
	bool		isPrivate;
	asDWORD     accessMask;
};

class asCGlobalProperty
{
public:
	asCGlobalProperty();
	~asCGlobalProperty();

	void AddRef();
	void Release();
	int  GetRefCount();

	void *GetAddressOfValue();
	void  AllocateMemory();
	void  SetRegisteredAddress(void *p);
	void *GetRegisteredAddress() const;

	asCString          name;
	asCDataType        type;
	asUINT             id;
	asCString          nameSpace;

	void SetInitFunc(asCScriptFunction *initFunc);
	asCScriptFunction *GetInitFunc();

	static void RegisterGCBehaviours(asCScriptEngine *engine);

//protected:
	void SetGCFlag();
	bool GetGCFlag();
	void EnumReferences(asIScriptEngine *);
	void ReleaseAllHandles(asIScriptEngine *);

	// This is only stored for registered properties, and keeps the pointer given by the application
	void       *realAddress;

	bool        memoryAllocated;
	void       *memory;
	asQWORD     storage;

	asCScriptFunction *initFunc;

	asDWORD accessMask;

	// The global property structure is reference counted, so that the
	// engine can keep track of how many references to the property there are.
	asCAtomic refCount;
	bool      gcFlag;
};

END_AS_NAMESPACE

#endif
