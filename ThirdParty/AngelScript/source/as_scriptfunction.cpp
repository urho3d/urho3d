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
// as_scriptfunction.cpp
//
// A container for a compiled script function
//



#include "as_config.h"
#include "as_scriptfunction.h"
#include "as_tokendef.h"
#include "as_scriptengine.h"
#include "as_callfunc.h"
#include "as_bytecode.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

#ifdef AS_MAX_PORTABILITY

static void ScriptFunction_AddRef_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	self->AddRef();
}

static void ScriptFunction_Release_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	self->Release();
}

static void ScriptFunction_GetRefCount_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	*(int*)gen->GetAddressOfReturnLocation() = self->GetRefCount();
}

static void ScriptFunction_SetFlag_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	self->SetFlag();
}

static void ScriptFunction_GetFlag_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	*(bool*)gen->GetAddressOfReturnLocation() = self->GetFlag();
}

static void ScriptFunction_EnumReferences_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	asIScriptEngine *engine = *(asIScriptEngine**)gen->GetAddressOfArg(0);
	self->EnumReferences(engine);
}

static void ScriptFunction_ReleaseAllHandles_Generic(asIScriptGeneric *gen)
{
	asCScriptFunction *self = (asCScriptFunction*)gen->GetObject();
	asIScriptEngine *engine = *(asIScriptEngine**)gen->GetAddressOfArg(0);
	self->ReleaseAllHandles(engine);
}

#endif


void RegisterScriptFunction(asCScriptEngine *engine)
{
	// Register the gc behaviours for the script functions
	int r = 0;
	UNUSED_VAR(r); // It is only used in debug mode
	engine->functionBehaviours.engine = engine;
	engine->functionBehaviours.flags = asOBJ_REF | asOBJ_GC;
	engine->functionBehaviours.name = "_builtin_function_";
#ifndef AS_MAX_PORTABILITY
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_ADDREF, "void f()", asMETHOD(asCScriptFunction,AddRef), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_RELEASE, "void f()", asMETHOD(asCScriptFunction,Release), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_GETREFCOUNT, "int f()", asMETHOD(asCScriptFunction,GetRefCount), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_SETGCFLAG, "void f()", asMETHOD(asCScriptFunction,SetFlag), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_GETGCFLAG, "bool f()", asMETHOD(asCScriptFunction,GetFlag), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_ENUMREFS, "void f(int&in)", asMETHOD(asCScriptFunction,EnumReferences), asCALL_THISCALL); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHOD(asCScriptFunction,ReleaseAllHandles), asCALL_THISCALL); asASSERT( r >= 0 );
#else
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_ADDREF, "void f()", asFUNCTION(ScriptFunction_AddRef_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_RELEASE, "void f()", asFUNCTION(ScriptFunction_Release_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_GETREFCOUNT, "int f()", asFUNCTION(ScriptFunction_GetRefCount_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_SETGCFLAG, "void f()", asFUNCTION(ScriptFunction_SetFlag_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_GETGCFLAG, "bool f()", asFUNCTION(ScriptFunction_GetFlag_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_ENUMREFS, "void f(int&in)", asFUNCTION(ScriptFunction_EnumReferences_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
	r = engine->RegisterBehaviourToObjectType(&engine->functionBehaviours, asBEHAVE_RELEASEREFS, "void f(int&in)", asFUNCTION(ScriptFunction_ReleaseAllHandles_Generic), asCALL_GENERIC); asASSERT( r >= 0 );
#endif
}

// internal
asCScriptFunction::asCScriptFunction(asCScriptEngine *engine, asCModule *mod, asEFuncType _funcType)
{
	refCount.set(1);
	this->engine           = engine;
	funcType               = _funcType;
	module                 = mod; 
	objectType             = 0; 
	name                   = ""; 
	isReadOnly             = false;
	isPrivate              = false;
	isFinal                = false;
	isOverride             = false;
	stackNeeded            = 0;
	sysFuncIntf            = 0;
	signatureId            = 0;
	scriptSectionIdx       = -1;
	dontCleanUpOnException = false;
	vfTableIdx             = -1;
	jitFunction            = 0;
	gcFlag                 = false;
	userData               = 0;
	id                     = 0;
	accessMask             = 0xFFFFFFFF;
	isShared               = false;
	variableSpace          = 0;

	// TODO: runtime optimize: The engine could notify the GC just before it wants to
	//                         discard the function. That way the GC won't waste time
	//                         trying to determine if the functions are garbage before
	//                         they can actually be considered garbage.
	// Notify the GC of script functions
	if( funcType == asFUNC_SCRIPT )
		engine->gc.AddScriptObjectToGC(this, &engine->functionBehaviours);
}

// internal
asCScriptFunction::~asCScriptFunction()
{
	// Imported functions are not reference counted, nor are dummy 
	// functions that are allocated on the stack
	asASSERT( funcType == asFUNC_DUMMY    ||
		      funcType == asFUNC_IMPORTED ||
		      refCount.get() == 0         );

	// If the engine pointer is 0, then DestroyInternal has already been called and there is nothing more to do
	if( engine == 0 ) return;

	DestroyInternal();

	// Tell engine to free the function id. This will make it impossible to
	// refer to the function by id. Where this is done, it is quite possible
	// they will leak.
	if( funcType != -1 && funcType != asFUNC_IMPORTED && id )
		engine->FreeScriptFunctionId(id);
	id = 0;

	// Finally set the engine pointer to 0 because it must not be accessed again
	engine = 0;
}

// internal
void asCScriptFunction::DestroyInternal()
{
	// Clean up user data
	if( userData && engine->cleanFunctionFunc )
		engine->cleanFunctionFunc(this);
	userData = 0;

	// Release all references the function holds to other objects
	ReleaseReferences();
	parameterTypes.SetLength(0);
	returnType = asCDataType::CreatePrimitive(ttVoid, false);
	byteCode.SetLength(0);

	for( asUINT n = 0; n < variables.GetLength(); n++ )
		asDELETE(variables[n],asSScriptVariable);
	variables.SetLength(0);
	
	for( asUINT p = 0; p < defaultArgs.GetLength(); p++ )
		if( defaultArgs[p] )
			asDELETE(defaultArgs[p], asCString);
	defaultArgs.SetLength(0);

	if( sysFuncIntf )
		asDELETE(sysFuncIntf,asSSystemFunctionInterface);
	sysFuncIntf = 0;
}

// interface
int asCScriptFunction::GetId() const
{
	return id;
}

// interface
int asCScriptFunction::AddRef() const
{
	gcFlag = false;
	asASSERT( funcType != asFUNC_IMPORTED );
	return refCount.atomicInc();
}

// interface
int asCScriptFunction::Release() const
{
	gcFlag = false;
	asASSERT( funcType != asFUNC_IMPORTED );
	int r = refCount.atomicDec();
	if( r == 0 && funcType != asFUNC_DUMMY ) // Dummy functions are allocated on the stack and cannot be deleted
		asDELETE(const_cast<asCScriptFunction*>(this),asCScriptFunction);

	return r;
}

// interface
const char *asCScriptFunction::GetModuleName() const
{
	if( module )
	{
		return module->name.AddressOf();
	}

	return 0;
}

// interface
asIObjectType *asCScriptFunction::GetObjectType() const
{
	return objectType;
}

// interface
const char *asCScriptFunction::GetObjectName() const 
{
	if( objectType )
		return objectType->GetName();

	return 0;
}

// interface
const char *asCScriptFunction::GetName() const
{
	return name.AddressOf();
}

// interface
const char *asCScriptFunction::GetNamespace() const
{
	return nameSpace.AddressOf();
}

// interface
bool asCScriptFunction::IsReadOnly() const
{
	return isReadOnly;
}

// interface
bool asCScriptFunction::IsPrivate() const
{
	return isPrivate;
}

// internal
int asCScriptFunction::GetSpaceNeededForArguments()
{
	// We need to check the size for each type
	int s = 0;
	for( asUINT n = 0; n < parameterTypes.GetLength(); n++ )
		s += parameterTypes[n].GetSizeOnStackDWords();

	return s;
}

// internal
int asCScriptFunction::GetSpaceNeededForReturnValue()
{
	return returnType.GetSizeOnStackDWords();
}

// internal
bool asCScriptFunction::DoesReturnOnStack() const
{
	if( returnType.GetObjectType() &&
		(returnType.GetObjectType()->flags & asOBJ_VALUE) &&
		!returnType.IsReference() )
		return true;
		
	return false;
}

// internal
asCString asCScriptFunction::GetDeclarationStr(bool includeObjectName, bool includeNamespace) const
{
	asCString str;

	// TODO: default arg: Make the declaration with the default args an option

	// Don't add the return type for constructors and destructors
	if( !(returnType.GetTokenType() == ttVoid && 
		  objectType && 
		  (name == objectType->name || (name.GetLength() > 0 && name[0] == '~'))) ) 
	{
		str = returnType.Format();
		str += " ";
	}
	if( objectType && includeObjectName )
	{
		if( includeNamespace )
			str += objectType->nameSpace + "::";
			
		if( objectType->name != "" )
			str += objectType->name + "::";
		else
			str += "_unnamed_type_::";
	}
	else if( includeNamespace )
	{
		str += nameSpace + "::";
	}
	if( name == "" )
		str += "_unnamed_function_(";
	else
		str += name + "(";

	if( parameterTypes.GetLength() > 0 )
	{
		asUINT n;
		for( n = 0; n < parameterTypes.GetLength() - 1; n++ )
		{
			str += parameterTypes[n].Format();
			if( parameterTypes[n].IsReference() && inOutFlags.GetLength() > n )
			{
				if( inOutFlags[n] == asTM_INREF ) str += "in";
				else if( inOutFlags[n] == asTM_OUTREF ) str += "out";
				else if( inOutFlags[n] == asTM_INOUTREF ) str += "inout";
			}

			if( defaultArgs.GetLength() > n && defaultArgs[n] )
			{
				asCString tmp;
				tmp.Format(" arg%d = %s", n, defaultArgs[n]->AddressOf());
				str += tmp;
			}

			str += ", ";
		}

		// Add the last parameter
		str += parameterTypes[n].Format();
		if( parameterTypes[n].IsReference() && inOutFlags.GetLength() > n )
		{
			if( inOutFlags[n] == asTM_INREF ) str += "in";
			else if( inOutFlags[n] == asTM_OUTREF ) str += "out";
			else if( inOutFlags[n] == asTM_INOUTREF ) str += "inout";
		}

		if( defaultArgs.GetLength() > n && defaultArgs[n] )
		{
			asCString tmp;
			tmp.Format(" arg%d = %s", n, defaultArgs[n]->AddressOf());
			str += tmp;
		}
	}

	str += ")";

	if( isReadOnly )
		str += " const";

	return str;
}

// interface
int asCScriptFunction::FindNextLineWithCode(int line) const
{
	if( lineNumbers.GetLength() == 0 ) return -1;

	// Check if given line is outside function
	// TODO: should start at declaration instead of first line of code
	if( line < (lineNumbers[1]&0xFFFFF) ) return -1;
	if( line > (lineNumbers[lineNumbers.GetLength()-1]&0xFFFFF) ) return -1;

	// Find the line with code on or right after the input line
	// TODO: optimize: Do binary search instead
	if( line == (lineNumbers[1]&0xFFFFF) ) return line;
	for( asUINT n = 3; n < lineNumbers.GetLength(); n += 2 )
	{
		if( line <= (lineNumbers[n]&0xFFFFF) )
			return (lineNumbers[n]&0xFFFFF);
	}

	return -1;
}

// internal
int asCScriptFunction::GetLineNumber(int programPosition)
{
	if( lineNumbers.GetLength() == 0 ) return 0;

	// Do a binary search in the buffer
	int max = (int)lineNumbers.GetLength()/2 - 1;
	int min = 0;
	int i = max/2;

	for(;;)
	{
		if( lineNumbers[i*2] < programPosition )
		{
			// Have we found the largest number < programPosition?
			if( max == i ) return lineNumbers[i*2+1];
			if( lineNumbers[i*2+2] > programPosition ) return lineNumbers[i*2+1];

			min = i + 1;
			i = (max + min)/2; 
		}
		else if( lineNumbers[i*2] > programPosition )
		{
			// Have we found the smallest number > programPosition?
			if( min == i ) return lineNumbers[i*2+1];

			max = i - 1;
			i = (max + min)/2;
		}
		else
		{
			// We found the exact position
			return lineNumbers[i*2+1];
		}
	}
}

// interface
asEFuncType asCScriptFunction::GetFuncType() const
{
	return funcType;
}

// interface
asUINT asCScriptFunction::GetVarCount() const
{
	return int(variables.GetLength());
}

// interface
int asCScriptFunction::GetVar(asUINT index, const char **name, int *typeId) const
{
	if( index >= variables.GetLength() )
		return asINVALID_ARG;

	if( name )
		*name = variables[index]->name.AddressOf();
	if( typeId )
		*typeId = engine->GetTypeIdFromDataType(variables[index]->type);

	return asSUCCESS;
}

// interface
const char *asCScriptFunction::GetVarDecl(asUINT index) const
{
	if( index >= variables.GetLength() )
		return 0;

	asCString *tempString = &asCThreadManager::GetLocalData()->string;
	*tempString = variables[index]->type.Format();
	*tempString += " " + variables[index]->name;

	return tempString->AddressOf();	
}

// internal
void asCScriptFunction::AddVariable(asCString &name, asCDataType &type, int stackOffset)
{
	asSScriptVariable *var = asNEW(asSScriptVariable);
	if( var == 0 )
	{
		// Out of memory
		return;
	}
	var->name                 = name;
	var->type                 = type;
	var->stackOffset          = stackOffset;
	var->declaredAtProgramPos = 0;
	variables.PushLast(var);
}

// internal
void asCScriptFunction::ComputeSignatureId()
{
	// This function will compute the signatureId based on the 
	// function name, return type, and parameter types. The object 
	// type for methods is not used, so that class methods and  
	// interface methods match each other.
	for( asUINT n = 0; n < engine->signatureIds.GetLength(); n++ )
	{
		if( !IsSignatureEqual(engine->signatureIds[n]) ) continue;

		// We don't need to increment the reference counter here, because 
		// asCScriptEngine::FreeScriptFunctionId will maintain the signature
		// id as the function is freed.
		signatureId = engine->signatureIds[n]->signatureId;
		return;
	}

	signatureId = id;
	engine->signatureIds.PushLast(this);
}

// internal
bool asCScriptFunction::IsSignatureEqual(const asCScriptFunction *func) const
{
	if( !IsSignatureExceptNameEqual(func) || name != func->name ) return false;
	
	return true;
}

// internal
bool asCScriptFunction::IsSignatureExceptNameEqual(const asCScriptFunction *func) const
{
	return IsSignatureExceptNameEqual(func->returnType, func->parameterTypes, func->inOutFlags, func->objectType, func->isReadOnly);
}

// internal
bool asCScriptFunction::IsSignatureExceptNameEqual(const asCDataType &retType, const asCArray<asCDataType> &paramTypes, const asCArray<asETypeModifiers> &paramInOut, const asCObjectType *objType, bool readOnly) const
{
	if( this->returnType != retType ) return false;

	return IsSignatureExceptNameAndReturnTypeEqual(paramTypes, paramInOut, objType, readOnly);
}

// internal
bool asCScriptFunction::IsSignatureExceptNameAndReturnTypeEqual(const asCArray<asCDataType> &paramTypes, const asCArray<asETypeModifiers> &paramInOut, const asCObjectType *objType, bool readOnly) const
{
	if( this->isReadOnly        != readOnly       ) return false;
	if( this->inOutFlags        != paramInOut     ) return false;
	if( this->parameterTypes    != paramTypes     ) return false;
	if( (this->objectType != 0) != (objType != 0) ) return false;

	return true;
}

// internal
void asCScriptFunction::AddReferences()
{
	asUINT n;

	// This array will be used to make sure we only add the reference to the same resource once
	// This is especially important for global variables, as it expects the initialization function
	// to hold only one reference to the variable. However, if the variable is initialized through
	// the default constructor followed by the assignment operator we will have two references to
	// the variable in the function.
	asCArray<void*> ptrs;

	// Only count references if there is any bytecode
	if( byteCode.GetLength() ) 
	{
		if( returnType.IsObject() )
			returnType.GetObjectType()->AddRef();

		for( asUINT p = 0; p < parameterTypes.GetLength(); p++ )
			if( parameterTypes[p].IsObject() )
				parameterTypes[p].GetObjectType()->AddRef();

		for( asUINT n = 0; n < objVariableTypes.GetLength(); n++ )
			objVariableTypes[n]->AddRef();
	}

	// Go through the byte code and add references to all resources used by the function
	for( n = 0; n < byteCode.GetLength(); n += asBCTypeSize[asBCInfo[*(asBYTE*)&byteCode[n]].type] )
	{
		switch( *(asBYTE*)&byteCode[n] )
		{
		// Object types
		case asBC_OBJTYPE:
		case asBC_FREE:
		case asBC_REFCPY:
		case asBC_RefCpyV:
			{
                asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				objType->AddRef();
			}
			break;

		// Object type and function
		case asBC_ALLOC:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				objType->AddRef();

				int func = asBC_INTARG(&byteCode[n]+AS_PTR_SIZE);
				if( func )
					engine->scriptFunctions[func]->AddRef();
			}
			break;

		// Global variables
		case asBC_PGA:
		case asBC_PshGPtr:
		case asBC_LDG:
		case asBC_PshG4:
		case asBC_LdGRdR4:
		case asBC_CpyGtoV4:
		case asBC_CpyVtoG4:
		case asBC_SetG4:
			// Need to increase the reference for each global variable
			{
				void *gvarPtr = (void*)asBC_PTRARG(&byteCode[n]);
				if( !gvarPtr ) break;
				asCGlobalProperty *prop = GetPropertyByGlobalVarPtr(gvarPtr);
				if( !prop ) break;

				// Only addref the properties once
				if( !ptrs.Exists(gvarPtr) )
				{
					prop->AddRef();
					ptrs.PushLast(gvarPtr);
				}

				asCConfigGroup *group = engine->FindConfigGroupForGlobalVar(prop->id);
				if( group != 0 ) group->AddRef();
			}
			break;

		// System functions
		case asBC_CALLSYS:
			{
				int funcId = asBC_INTARG(&byteCode[n]);
				asCConfigGroup *group = engine->FindConfigGroupForFunction(funcId);
				if( group != 0 ) group->AddRef();

				engine->scriptFunctions[funcId]->AddRef();
			}
			break;

		// Functions
		case asBC_CALL:
		case asBC_CALLINTF:
			{
				int func = asBC_INTARG(&byteCode[n]);
				engine->scriptFunctions[func]->AddRef();
			}
			break;

		// Function pointers
		case asBC_FuncPtr:
			{
				asCScriptFunction *func = (asCScriptFunction*)asBC_PTRARG(&byteCode[n]);
				func->AddRef();
			}
			break;
		}
	}
}

// internal
void asCScriptFunction::ReleaseReferences()
{
	asUINT n;

	asCArray<void*> ptrs;

	// Only count references if there is any bytecode
	if( byteCode.GetLength() )
	{
		if( returnType.IsObject() )
			returnType.GetObjectType()->Release();

		for( asUINT p = 0; p < parameterTypes.GetLength(); p++ )
			if( parameterTypes[p].IsObject() )
				parameterTypes[p].GetObjectType()->Release();

		for( asUINT n = 0; n < objVariableTypes.GetLength(); n++ )
			if( objVariableTypes[n] )
				objVariableTypes[n]->Release();
	}

	// Go through the byte code and release references to all resources used by the function
	for( n = 0; n < byteCode.GetLength(); n += asBCTypeSize[asBCInfo[*(asBYTE*)&byteCode[n]].type] )
	{
		switch( *(asBYTE*)&byteCode[n] )
		{
		// Object types
		case asBC_OBJTYPE:
		case asBC_FREE:
		case asBC_REFCPY:
		case asBC_RefCpyV:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				if( objType ) 
					objType->Release();
			}
			break;

		// Object type and function
		case asBC_ALLOC:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				if( objType )
					objType->Release();

				int func = asBC_INTARG(&byteCode[n]+AS_PTR_SIZE);
				if( func )
				{
					asCScriptFunction *fptr = engine->scriptFunctions[func];
					if( fptr )
						fptr->Release();

					// The engine may have been forced to destroy the function internals early
					// and this may will make it impossible to find the function by id anymore.
					// This should only happen if the engine is released while the application
					// is still keeping functions alive.
					// TODO: Fix this possible memory leak
				}
			}
			break;

		// Global variables
		case asBC_PGA:
		case asBC_PshGPtr:
		case asBC_LDG:
		case asBC_PshG4:
		case asBC_LdGRdR4:
		case asBC_CpyGtoV4:
		case asBC_CpyVtoG4:
		case asBC_SetG4:
			// Need to increase the reference for each global variable
			{
				void *gvarPtr = (void*)asBC_PTRARG(&byteCode[n]);
				if( !gvarPtr ) break;
				asCGlobalProperty *prop = GetPropertyByGlobalVarPtr(gvarPtr);
				if( !prop ) break;
				
				// Only release the properties once
				if( !ptrs.Exists(gvarPtr) )
				{
					prop->Release();
					ptrs.PushLast(gvarPtr);
				}

				asCConfigGroup *group = engine->FindConfigGroupForGlobalVar(prop->id);
				if( group != 0 ) group->Release();
			}
			break;

		// System functions
		case asBC_CALLSYS:
			{
				int funcId = asBC_INTARG(&byteCode[n]);
				asCConfigGroup *group = engine->FindConfigGroupForFunction(funcId);
				if( group != 0 ) group->Release();

				if( funcId )
					engine->scriptFunctions[funcId]->Release();
			}
			break;

		// Functions
		case asBC_CALL:
		case asBC_CALLINTF:
			{
				int func = asBC_INTARG(&byteCode[n]);
				if( func )
				{
					asCScriptFunction *fptr = engine->scriptFunctions[func];
					if( fptr )
						fptr->Release();

					// The engine may have been forced to destroy the function internals early
					// and this may will make it impossible to find the function by id anymore.
					// This should only happen if the engine is released while the application
					// is still keeping functions alive.
					// TODO: Fix this possible memory leak
				}
			}
			break;

		// Function pointers
		case asBC_FuncPtr:
			{
				asCScriptFunction *func = (asCScriptFunction*)asBC_PTRARG(&byteCode[n]);
				if( func )
					func->Release();
			}
			break;
		}
	}

	// Release the jit compiled function
	if( jitFunction )
		engine->jitCompiler->ReleaseJITFunction(jitFunction);
	jitFunction = 0;
}

// interface
int asCScriptFunction::GetReturnTypeId() const
{
	return engine->GetTypeIdFromDataType(returnType);
}

// interface
asUINT asCScriptFunction::GetParamCount() const
{
	return (asUINT)parameterTypes.GetLength();
}

// interface
int asCScriptFunction::GetParamTypeId(asUINT index, asDWORD *flags) const
{
	if( index >= parameterTypes.GetLength() )
		return asINVALID_ARG;

	if( flags )
		*flags = inOutFlags[index];

	return engine->GetTypeIdFromDataType(parameterTypes[index]);
}

// interface
asIScriptEngine *asCScriptFunction::GetEngine() const
{
	return engine;
}

// interface
const char *asCScriptFunction::GetDeclaration(bool includeObjectName, bool includeNamespace) const
{
	asCString *tempString = &asCThreadManager::GetLocalData()->string;
	*tempString = GetDeclarationStr(includeObjectName, includeNamespace);
	return tempString->AddressOf();
}

// interface
const char *asCScriptFunction::GetScriptSectionName() const
{
	if( scriptSectionIdx >= 0 )
		return engine->scriptSectionNames[scriptSectionIdx]->AddressOf();
	
	return 0;
}

// interface
const char *asCScriptFunction::GetConfigGroup() const
{
	asCConfigGroup *group = 0;
	if( funcType != asFUNC_FUNCDEF )
		group = engine->FindConfigGroupForFunction(id);
	else
		group = engine->FindConfigGroupForFuncDef(this);

	if( group == 0 )
		return 0;

	return group->groupName.AddressOf();
}

// interface
asDWORD asCScriptFunction::GetAccessMask() const
{
	return accessMask;
}

// internal
void asCScriptFunction::JITCompile()
{
    asIJITCompiler *jit = engine->GetJITCompiler();
    if( !jit )
        return;

	// Release the previous function, if any
    if( jitFunction )
    {
        engine->jitCompiler->ReleaseJITFunction(jitFunction);
        jitFunction = 0;
    }

	// Compile for native system
	int r = jit->CompileFunction(this, &jitFunction);
	if( r < 0 )
	{
		asASSERT( jitFunction == 0 );
	}
}

// interface
asDWORD *asCScriptFunction::GetByteCode(asUINT *length)
{
	if( length )
		*length = (asUINT)byteCode.GetLength();

	if( byteCode.GetLength() )
	{
		return byteCode.AddressOf();
	}

	return 0;
}

// interface
void *asCScriptFunction::SetUserData(void *data)
{
	void *oldData = userData;
	userData = data;
	return oldData;
}

// interface
void *asCScriptFunction::GetUserData() const
{
	return userData;
}

// internal
asCGlobalProperty *asCScriptFunction::GetPropertyByGlobalVarPtr(void *gvarPtr)
{
	for( asUINT g = 0; g < engine->globalProperties.GetLength(); g++ )
		if( engine->globalProperties[g] && engine->globalProperties[g]->GetAddressOfValue() == gvarPtr )
			return engine->globalProperties[g];

	return 0;
}

// internal
int asCScriptFunction::GetRefCount()
{
	return refCount.get();
}

// internal
void asCScriptFunction::SetFlag()
{
	gcFlag = true;
}

// internal
bool asCScriptFunction::GetFlag()
{
	return gcFlag;
}

// internal
void asCScriptFunction::EnumReferences(asIScriptEngine *)
{
	// Notify the GC of all object types used
	if( returnType.IsObject() )
		engine->GCEnumCallback(returnType.GetObjectType());

	for( asUINT p = 0; p < parameterTypes.GetLength(); p++ )
		if( parameterTypes[p].IsObject() )
			engine->GCEnumCallback(parameterTypes[p].GetObjectType());

	for( asUINT t = 0; t < objVariableTypes.GetLength(); t++ )
		engine->GCEnumCallback(objVariableTypes[t]);

	// Notify the GC of all script functions that is accessed
	for( asUINT n = 0; n < byteCode.GetLength(); n += asBCTypeSize[asBCInfo[*(asBYTE*)&byteCode[n]].type] )
	{
		switch( *(asBYTE*)&byteCode[n] )
		{
		case asBC_OBJTYPE:
		case asBC_FREE:
		case asBC_REFCPY:
		case asBC_RefCpyV:
			{
                asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				engine->GCEnumCallback(objType);
			}
			break;

		case asBC_ALLOC:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				engine->GCEnumCallback(objType);

				int func = asBC_INTARG(&byteCode[n]+AS_PTR_SIZE);
				if( func )
					engine->GCEnumCallback(engine->scriptFunctions[func]);
			}
			break;

		case asBC_CALL:
		case asBC_CALLINTF:
			{
				int func = asBC_INTARG(&byteCode[n]);
				if( func )
					engine->GCEnumCallback(engine->scriptFunctions[func]);
			}
			break;

		// Function pointers
		case asBC_FuncPtr:
			{
				asCScriptFunction *func = (asCScriptFunction*)asBC_PTRARG(&byteCode[n]);
				if( func )
					engine->GCEnumCallback(func);
			}
			break;

		// Global variables
		case asBC_PGA:
		case asBC_PshGPtr:
		case asBC_LDG:
		case asBC_PshG4:
		case asBC_LdGRdR4:
		case asBC_CpyGtoV4:
		case asBC_CpyVtoG4:
		case asBC_SetG4:
			// Need to enumerate the reference for each global variable
			{
				// TODO: optimize: Keep an array of accessed global properties
				void *gvarPtr = (void*)asBC_PTRARG(&byteCode[n]);
				asCGlobalProperty *prop = GetPropertyByGlobalVarPtr(gvarPtr);

				engine->GCEnumCallback(prop);
			}
			break;
		}
	}
}

// internal
void asCScriptFunction::ReleaseAllHandles(asIScriptEngine *)
{
	// Release paramaters
	if( byteCode.GetLength() ) 
	{
		if( returnType.IsObject() )
		{
			returnType.GetObjectType()->Release();
			returnType = asCDataType::CreatePrimitive(ttVoid, false);
		}

		for( asUINT p = 0; p < parameterTypes.GetLength(); p++ )
			if( parameterTypes[p].IsObject() )
			{
				parameterTypes[p].GetObjectType()->Release();
				parameterTypes[p] = asCDataType::CreatePrimitive(ttInt, false);
			}

		for( asUINT n = 0; n < objVariableTypes.GetLength(); n++ )
			objVariableTypes[n]->Release();
		objVariableTypes.SetLength(0);
	}

	// Release all script functions
	for( asUINT n = 0; n < byteCode.GetLength(); n += asBCTypeSize[asBCInfo[*(asBYTE*)&byteCode[n]].type] )
	{
		switch( *(asBYTE*)&byteCode[n] )
		{
		// Object types
		case asBC_OBJTYPE:
		case asBC_FREE:
		case asBC_REFCPY:
		case asBC_RefCpyV:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				if( objType )
				{
					objType->Release();
					*(void**)&byteCode[n+1] = 0;
				}
			}
			break;

		case asBC_ALLOC:
			{
				asCObjectType *objType = (asCObjectType*)asBC_PTRARG(&byteCode[n]);
				if( objType )
				{
					objType->Release();
				*	(void**)&byteCode[n+1] = 0;
				}

				int func = asBC_INTARG(&byteCode[n]+AS_PTR_SIZE);
				if( func )
				{
					engine->scriptFunctions[func]->Release();
					byteCode[n+AS_PTR_SIZE+1] = 0;
				}
			}
			break;

		case asBC_CALL:
		case asBC_CALLINTF:
			{
				int func = asBC_INTARG(&byteCode[n]);
				if( func )
				{
					engine->scriptFunctions[func]->Release();
					byteCode[n+1] = 0;
				}
			}
			break;

		// Function pointers
		case asBC_FuncPtr:
			{
				asCScriptFunction *func = (asCScriptFunction*)asBC_PTRARG(&byteCode[n]);
				if( func )
				{
					func->Release();
					*(asPWORD*)&byteCode[n+1] = 0;
				}
			}
			break;

		// The global variables are not released here. It is enough that the global 
		// variable itself release the function to break the circle
		}
	}
}

// internal
bool asCScriptFunction::IsShared() const
{
	// All system functions are shared
	if( funcType == asFUNC_SYSTEM ) return true;

	// All class methods for shared classes are also shared
	if( objectType && (objectType->flags & asOBJ_SHARED) ) return true;

	// Functions that have been specifically marked as shared are shared
	return isShared;
}

// internal
bool asCScriptFunction::IsFinal() const
{
	return isFinal;
}

// internal
bool asCScriptFunction::IsOverride() const
{
	return isOverride;
}

END_AS_NAMESPACE

