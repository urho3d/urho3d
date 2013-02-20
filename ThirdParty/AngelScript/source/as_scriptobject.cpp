/*
   AngelCode Scripting Library
   Copyright (c) 2003-2013 Andreas Jonsson

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

// Modified by Lasse Oorni for Urho3D

#include <new>
#include "as_config.h"
#include "as_scriptengine.h"
#include "as_scriptobject.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

// This helper function will call the default factory, that is a script function
asIScriptObject *ScriptObjectFactory(const asCObjectType *objType, asCScriptEngine *engine)
{
	asIScriptContext *ctx = 0;
	int r = 0;
	bool isNested = false;

	// TODO: runtime optimize: There should be a pool for the context so it doesn't 
	//                         have to be allocated just for creating the script object

	// TODO: It must be possible for the application to debug the creation of the object too

	// Use nested call in the context if there is an active context
	ctx = asGetActiveContext();
	if( ctx )
	{
		r = ctx->PushState();

		// It may not always be possible to reuse the current context, 
		// in which case we'll have to create a new one any way.
		if( r == asSUCCESS )
			isNested = true;
		else
			ctx = 0;
	}
	
	if( ctx == 0 )
	{
		r = engine->CreateContext(&ctx, true);
		if( r < 0 )
			return 0;
	}

	r = ctx->Prepare(engine->scriptFunctions[objType->beh.factory]);
	if( r < 0 )
	{
		if( isNested )
			ctx->PopState();
		else
			ctx->Release();
		return 0;
	}

	for(;;)
	{
		r = ctx->Execute();

		// We can't allow this execution to be suspended 
		// so resume the execution immediately
		if( r != asEXECUTION_SUSPENDED )
			break;
	}

	if( r != asEXECUTION_FINISHED )
	{
		if( isNested )
		{
			ctx->PopState();

			// If the execution was aborted or an exception occurred,
			// then we should forward that to the outer execution.
			if( r == asEXECUTION_EXCEPTION )
			{
				// TODO: How to improve this exception
				ctx->SetException(TXT_EXCEPTION_IN_NESTED_CALL);
			}
			else if( r == asEXECUTION_ABORTED )
				ctx->Abort();
		}
		else
			ctx->Release();
		return 0;
	}

	asIScriptObject *ptr = (asIScriptObject*)ctx->GetReturnAddress();

	// Increase the reference, because the context will release its pointer
	ptr->AddRef();

	if( isNested )
		ctx->PopState();
	else
		ctx->Release();

	return ptr;
}

#ifdef AS_MAX_PORTABILITY

static void ScriptObject_AddRef_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	self->AddRef();
}

static void ScriptObject_Release_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	self->Release();
}

static void ScriptObject_GetRefCount_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	*(int*)gen->GetAddressOfReturnLocation() = self->GetRefCount();
}

static void ScriptObject_SetFlag_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	self->SetFlag();
}

static void ScriptObject_GetFlag_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	*(bool*)gen->GetAddressOfReturnLocation() = self->GetFlag();
}

static void ScriptObject_EnumReferences_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	asIScriptEngine *engine = *(asIScriptEngine**)gen->GetAddressOfArg(0);
	self->EnumReferences(engine);
}

static void ScriptObject_ReleaseAllHandles_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();
	asIScriptEngine *engine = *(asIScriptEngine**)gen->GetAddressOfArg(0);
	self->ReleaseAllHandles(engine);
}

#endif

void RegisterScriptObject(asCScriptEngine *engine)
{
	// Register the default script class behaviours
	int r = 0;
	UNUSED_VAR(r); // It is only used in debug mode
	engine->scriptTypeBehaviours.engine = engine;
	engine->scriptTypeBehaviours.flags = asOBJ_SCRIPT_OBJECT | asOBJ_REF | asOBJ_GC;
	engine->scriptTypeBehaviours.name = "_builtin_object_";
#ifndef AS_MAX_PORTABILITY
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_CONSTRUCT, "void f(int&in)", asFUNCTION(ScriptObject_Construct), asCALL_CDECL_OBJLAST); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_ADDREF, "void f()", asMETHOD(asCScriptObject,AddRef), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_RELEASE, "void f()", asMETHOD(asCScriptObject,Release), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterMethodToObjectType(&engine->scriptTypeBehaviours, "int &opAssign(int &in)", asFUNCTION(ScriptObject_Assignment), asCALL_CDECL_OBJLAST); asASSERT( r >= 0 );

	// Register GC behaviours
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_GETREFCOUNT, "int f()", asMETHOD(asCScriptObject,GetRefCount), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_SETGCFLAG, "void f()", asMETHOD(asCScriptObject,SetFlag), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_GETGCFLAG, "bool f()", asMETHOD(asCScriptObject,GetFlag), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_ENUMREFS, "void f(int&in)", asMETHOD(asCScriptObject,EnumReferences), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHOD(asCScriptObject,ReleaseAllHandles), asCALL_THISCALL); asASSERT( r >= 0 );
#else
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_CONSTRUCT, "void f(int&in)", asFUNCTION(ScriptObject_Construct_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_ADDREF, "void f()", asFUNCTION(ScriptObject_AddRef_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_RELEASE, "void f()", asFUNCTION(ScriptObject_Release_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterMethodToObjectType(&engine->scriptTypeBehaviours, "int &opAssign(int &in)", asFUNCTION(ScriptObject_Assignment_Generic), asCALL_GENERIC); asASSERT( r >= 0 );

	// Register GC behaviours
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_GETREFCOUNT, "int f()", asFUNCTION(ScriptObject_GetRefCount_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_SETGCFLAG, "void f()", asFUNCTION(ScriptObject_SetFlag_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_GETGCFLAG, "bool f()", asFUNCTION(ScriptObject_GetFlag_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_ENUMREFS, "void f(int&in)", asFUNCTION(ScriptObject_EnumReferences_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->scriptTypeBehaviours, asBEHAVE_RELEASEREFS, "void f(int&in)", asFUNCTION(ScriptObject_ReleaseAllHandles_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
#endif
}

void ScriptObject_Construct_Generic(asIScriptGeneric *gen)
{
	asCObjectType *objType = *(asCObjectType**)gen->GetAddressOfArg(0);
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();

	ScriptObject_Construct(objType, self);
}

void ScriptObject_Construct(asCObjectType *objType, asCScriptObject *self)
{
	new(self) asCScriptObject(objType);
}

void ScriptObject_ConstructUnitialized(asCObjectType *objType, asCScriptObject *self)
{
	new(self) asCScriptObject(objType, false);
}

asCScriptObject::asCScriptObject(asCObjectType *ot, bool doInitialize)
{
	refCount.set(1);
	objType = ot;
	objType->AddRef();
	isDestructCalled = false;

	// Notify the garbage collector of this object
	if( objType->flags & asOBJ_GC )
		objType->engine->gc.AddScriptObjectToGC(this, objType);

	if( doInitialize )
	{
#ifndef AS_NO_MEMBER_INIT
		// The actual initialization will be done by the bytecode, so here we should just clear the
		// memory to guarantee that no pointers with have scratch values in case of an exception
		// TODO: runtime optimize: Is it quicker to just do a memset on the entire object? 
		for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
		{
			asCObjectProperty *prop = objType->properties[n];
			if( prop->type.IsObject() )
			{
				asPWORD *ptr = reinterpret_cast<asPWORD*>(reinterpret_cast<asBYTE*>(this) + prop->byteOffset);
				*ptr = 0;
			}
		}
#else
		// When member initialization is disabled the constructor must make sure
		// to allocate and initialize all members with the default constructor
		for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
		{
			asCObjectProperty *prop = objType->properties[n];
			if( prop->type.IsObject() )
			{
				asPWORD *ptr = reinterpret_cast<asPWORD*>(reinterpret_cast<asBYTE*>(this) + prop->byteOffset);
				if( prop->type.IsObjectHandle() )
					*ptr = 0;
				else
				{
					if( prop->type.GetObjectType()->flags & asOBJ_SCRIPT_OBJECT )
						*ptr = (asPWORD)ScriptObjectFactory(prop->type.GetObjectType(), ot->engine);
					else
						*ptr = (asPWORD)AllocateUninitializedObject(prop->type.GetObjectType(), ot->engine);
				}
			}
		}
#endif
	}
	else
	{
		// When the object is created without initialization, all non-handle members must be allocated, but not initialized
		asCScriptEngine *engine = objType->engine;
		for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
		{
			asCObjectProperty *prop = objType->properties[n];
			if( prop->type.IsObject() )
			{
				asPWORD *ptr = reinterpret_cast<asPWORD*>(reinterpret_cast<asBYTE*>(this) + prop->byteOffset);
				if( prop->type.IsObjectHandle() )
					*ptr = 0;
				else
					*ptr = (asPWORD)AllocateUninitializedObject(prop->type.GetObjectType(), engine);
			}
		}
	}
	
	// Urho3D: initialize userdata
	userData = 0;
}

void asCScriptObject::Destruct()
{
	// Call the destructor, which will also call the GCObject's destructor
	this->~asCScriptObject();

	// Free the memory
	userFree(this);
}

asCScriptObject::~asCScriptObject()
{
	// The engine pointer should be available from the objectType
	asCScriptEngine *engine = objType->engine;

	// Destroy all properties
	for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
	{
		asCObjectProperty *prop = objType->properties[n];
		if( prop->type.IsObject() )
		{
			// Destroy the object
			void **ptr = (void**)(((char*)this) + prop->byteOffset);
			if( *ptr )
			{
				FreeObject(*ptr, prop->type.GetObjectType(), engine);
				*(asDWORD*)ptr = 0;
			}
		}
	}

	objType->Release();
}

asIScriptEngine *asCScriptObject::GetEngine() const
{
	return objType->engine;
}

int asCScriptObject::AddRef() const
{
	// Increase counter and clear flag set by GC
	gcFlag = false;
	return refCount.atomicInc();
}

int asCScriptObject::Release() const
{
	// Clear the flag set by the GC
	gcFlag = false;

	// Call the script destructor behaviour if the reference counter is 1.
	if( refCount.get() == 1 && !isDestructCalled )
	{
		// This cast is OK since we are the last reference
		const_cast<asCScriptObject*>(this)->CallDestructor();
	}

	// Now do the actual releasing
	int r = refCount.atomicDec();
	if( r == 0 )
	{
		// This cast is OK since we are the last reference
		const_cast<asCScriptObject*>(this)->Destruct();
		return 0;
	}

	return r;
}

void asCScriptObject::CallDestructor()
{
	asIScriptContext *ctx = 0;
	bool isNested = false;
	bool doAbort = false;

	// Make sure the destructor is called once only, even if the  
	// reference count is increased and then decreased again
	isDestructCalled = true;

	// Call the destructor for this class and all the super classes
	asCObjectType *ot = objType;
	while( ot )
	{
		int funcIndex = ot->beh.destruct;
		if( funcIndex )
		{
			if( ctx == 0 )
			{
				// Check for active context first as it is quicker
				// to reuse than to set up a new one.
				ctx = asGetActiveContext();
				if( ctx )
				{
					int r = ctx->PushState();
					if( r == asSUCCESS )
						isNested = true;
					else
						ctx = 0;
				}

				if( ctx == 0 )
				{
					// Setup a context for calling the default constructor
					asCScriptEngine *engine = objType->engine;
					int r = engine->CreateContext(&ctx, true);
					if( r < 0 ) return;
				}
			}

			int r = ctx->Prepare(objType->engine->scriptFunctions[funcIndex]);
			if( r >= 0 )
			{
				ctx->SetObject(this);

				for(;;)
				{
					r = ctx->Execute();

					// If the script tries to suspend itself just restart it
					if( r != asEXECUTION_SUSPENDED )
						break;
				}

				// Exceptions in the destructor will be ignored, as there is not much
				// that can be done about them. However a request to abort the execution
				// will be forwarded to the outer execution, in case of a nested call.
				if( r == asEXECUTION_ABORTED )
					doAbort = true;

				// Observe, even though the current destructor was aborted or an exception
				// occurred, we still try to execute the base class' destructor if available
				// in order to free as many resources as possible.
			}
		}

		ot = ot->derivedFrom;
	}

	if( ctx )
	{
		if( isNested )
		{
			ctx->PopState();

			// Forward any request to abort the execution to the outer call
			if( doAbort )
				ctx->Abort();
		}
		else
			ctx->Release();
	}
}

asIObjectType *asCScriptObject::GetObjectType() const
{
	return objType;
}

int asCScriptObject::GetRefCount()
{
	return refCount.get();
}

void asCScriptObject::SetFlag()
{
	gcFlag = true;
}

bool asCScriptObject::GetFlag()
{
	return gcFlag;
}

// interface
int asCScriptObject::GetTypeId() const
{
	asCDataType dt = asCDataType::CreateObject(objType, false);
	return objType->engine->GetTypeIdFromDataType(dt);
}

// Urho3D: added function
void *asCScriptObject::SetUserData(void *data)
{
	void *oldData = userData;
	userData = data;
	return oldData;
}

// Urho3D: added function
void *asCScriptObject::GetUserData() const
{
	return userData;
}

asUINT asCScriptObject::GetPropertyCount() const
{
	return asUINT(objType->properties.GetLength());
}

int asCScriptObject::GetPropertyTypeId(asUINT prop) const
{
	if( prop >= objType->properties.GetLength() )
		return asINVALID_ARG;

	return objType->engine->GetTypeIdFromDataType(objType->properties[prop]->type);
}

const char *asCScriptObject::GetPropertyName(asUINT prop) const
{
	if( prop >= objType->properties.GetLength() )
		return 0;

	return objType->properties[prop]->name.AddressOf();
}

void *asCScriptObject::GetAddressOfProperty(asUINT prop)
{
	if( prop >= objType->properties.GetLength() )
		return 0;

	// Objects are stored by reference, so this must be dereferenced
	asCDataType *dt = &objType->properties[prop]->type;
	if( dt->IsObject() && !dt->IsObjectHandle() )
		return *(void**)(((char*)this) + objType->properties[prop]->byteOffset);

	return (void*)(((char*)this) + objType->properties[prop]->byteOffset);
}

void asCScriptObject::EnumReferences(asIScriptEngine *engine)
{
	// We'll notify the GC of all object handles that we're holding
	for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
	{
		asCObjectProperty *prop = objType->properties[n];
		if( prop->type.IsObject() )
		{
			void *ptr = *(void**)(((char*)this) + prop->byteOffset);
			if( ptr )
				((asCScriptEngine*)engine)->GCEnumCallback(ptr);
		}
	}
}

void asCScriptObject::ReleaseAllHandles(asIScriptEngine *engine)
{
	for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
	{
		asCObjectProperty *prop = objType->properties[n];
		if( prop->type.IsObject() && prop->type.IsObjectHandle() )
		{
			void **ptr = (void**)(((char*)this) + prop->byteOffset);
			if( *ptr )
			{
				asASSERT( (prop->type.GetObjectType()->flags & asOBJ_NOCOUNT) || prop->type.GetBehaviour()->release );
				if( prop->type.GetBehaviour()->release )
					((asCScriptEngine*)engine)->CallObjectMethod(*ptr, prop->type.GetBehaviour()->release);
				*ptr = 0;
			}
		}
	}
}

void ScriptObject_Assignment_Generic(asIScriptGeneric *gen)
{
	asCScriptObject *other = *(asCScriptObject**)gen->GetAddressOfArg(0);
	asCScriptObject *self = (asCScriptObject*)gen->GetObject();

	*self = *other;

	*(asCScriptObject**)gen->GetAddressOfReturnLocation() = self;
}

asCScriptObject &ScriptObject_Assignment(asCScriptObject *other, asCScriptObject *self)
{
	return (*self = *other);
}

asCScriptObject &asCScriptObject::operator=(const asCScriptObject &other)
{
	if( &other != this )
	{
		asASSERT( other.objType->DerivesFrom(objType) );

		// If the script class implements the opAssign method, it should be called
		asCScriptEngine *engine = objType->engine;
		asCScriptFunction *func = engine->scriptFunctions[objType->beh.copy];
		if( func->funcType == asFUNC_SYSTEM )
		{
			// Copy all properties
			for( asUINT n = 0; n < objType->properties.GetLength(); n++ )
			{
				asCObjectProperty *prop = objType->properties[n];
				if( prop->type.IsObject() )
				{
					void **dst = (void**)(((char*)this) + prop->byteOffset);
					void **src = (void**)(((char*)&other) + prop->byteOffset);
					if( !prop->type.IsObjectHandle() )
						CopyObject(*src, *dst, prop->type.GetObjectType(), engine);
					else
						CopyHandle((asPWORD*)src, (asPWORD*)dst, prop->type.GetObjectType(), engine);
				}
				else
				{
					void *dst = ((char*)this) + prop->byteOffset;
					void *src = ((char*)&other) + prop->byteOffset;
					memcpy(dst, src, prop->type.GetSizeInMemoryBytes());
				}
			}
		}
		else
		{
			// Reuse the active context or create a new one to call the script class' opAssign method
			asIScriptContext *ctx = 0;
			int r = 0;
			bool isNested = false;

			ctx = asGetActiveContext();
			if( ctx )
			{
				r = ctx->PushState();
				if( r == asSUCCESS )
					isNested = true;
				else
					ctx = 0;
			}

			if( ctx == 0 )
			{
				r = engine->CreateContext(&ctx, true);
				if( r < 0 )
					return *this;
			}

			r = ctx->Prepare(engine->scriptFunctions[objType->beh.copy]);
			if( r < 0 )
			{
				if( isNested )
					ctx->PopState();
				else
					ctx->Release();
				return *this;
			}

			r = ctx->SetArgAddress(0, const_cast<asCScriptObject*>(&other));
			asASSERT( r >= 0 );
			r = ctx->SetObject(this);
			asASSERT( r >= 0 );

			for(;;)
			{
				r = ctx->Execute();

				// We can't allow this execution to be suspended 
				// so resume the execution immediately
				if( r != asEXECUTION_SUSPENDED )
					break;
			}

			if( r != asEXECUTION_FINISHED )
			{
				if( isNested )
				{
					ctx->PopState();

					// If the execution was aborted or an exception occurred,
					// then we should forward that to the outer execution.
					if( r == asEXECUTION_EXCEPTION )
					{
						// TODO: How to improve this exception
						ctx->SetException(TXT_EXCEPTION_IN_NESTED_CALL);
					}
					else if( r == asEXECUTION_ABORTED )
						ctx->Abort();
				}
				else
					ctx->Release();
				return *this;
			}

			if( isNested )
				ctx->PopState();
			else
				ctx->Release();
		}
	}

	return *this;
}

int asCScriptObject::CopyFrom(asIScriptObject *other)
{
	if( other == 0 ) return asINVALID_ARG;

	if( GetTypeId() != other->GetTypeId() )
		return asINVALID_TYPE;

	*this = *(asCScriptObject*)other;

	return 0;
}

void *asCScriptObject::AllocateUninitializedObject(asCObjectType *objType, asCScriptEngine *engine)
{
	void *ptr = 0;

	if( objType->flags & asOBJ_SCRIPT_OBJECT )
	{
		ptr = engine->CallAlloc(objType);
		ScriptObject_ConstructUnitialized(objType, reinterpret_cast<asCScriptObject*>(ptr));
	}
	else if( objType->flags & asOBJ_TEMPLATE )
	{
		// Templates store the original factory that takes the object
		// type as a hidden parameter in the construct behaviour
		ptr = engine->CallGlobalFunctionRetPtr(objType->beh.construct, objType);
	}
	else if( objType->flags & asOBJ_REF )
	{
		ptr = engine->CallGlobalFunctionRetPtr(objType->beh.factory);
	}
	else
	{
		ptr = engine->CallAlloc(objType);
		int funcIndex = objType->beh.construct;
		if( funcIndex )
			engine->CallObjectMethod(ptr, funcIndex);
	}

	return ptr;
}

void asCScriptObject::FreeObject(void *ptr, asCObjectType *objType, asCScriptEngine *engine)
{
	if( objType->flags & asOBJ_REF )
	{
		asASSERT( (objType->flags & asOBJ_NOCOUNT) || objType->beh.release );
		if( objType->beh.release )
			engine->CallObjectMethod(ptr, objType->beh.release);
	}
	else
	{
		if( objType->beh.destruct )
			engine->CallObjectMethod(ptr, objType->beh.destruct);

		engine->CallFree(ptr);
	}
}

void asCScriptObject::CopyObject(void *src, void *dst, asCObjectType *objType, asCScriptEngine *engine)
{
	int funcIndex = objType->beh.copy;
	if( funcIndex )
	{
		asCScriptFunction *func = engine->scriptFunctions[objType->beh.copy];
		if( func->funcType == asFUNC_SYSTEM )
			engine->CallObjectMethod(dst, src, funcIndex);
		else
		{
			// Call the script class' opAssign method
			asASSERT( objType->flags & asOBJ_SCRIPT_OBJECT );
			reinterpret_cast<asCScriptObject*>(dst)->CopyFrom(reinterpret_cast<asCScriptObject*>(src));
		}
	}
	else if( objType->size && (objType->flags & asOBJ_POD) )
		memcpy(dst, src, objType->size);
}

void asCScriptObject::CopyHandle(asPWORD *src, asPWORD *dst, asCObjectType *objType, asCScriptEngine *engine)
{
	// asOBJ_NOCOUNT doesn't have addref or release behaviours
	asASSERT( (objType->flags & asOBJ_NOCOUNT) || (objType->beh.release && objType->beh.addref) );

	if( *dst && objType->beh.release )
		engine->CallObjectMethod(*(void**)dst, objType->beh.release);
	*dst = *src;
	if( *dst && objType->beh.addref )
		engine->CallObjectMethod(*(void**)dst, objType->beh.addref);
}

END_AS_NAMESPACE

