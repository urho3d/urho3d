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
// as_restore.cpp
//
// Functions for saving and restoring module bytecode
// asCRestore was originally written by Dennis Bollyn, dennis@gyrbo.be

#include "as_config.h"
#include "as_restore.h"
#include "as_bytecode.h"
#include "as_scriptobject.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

asCReader::asCReader(asCModule* _module, asIBinaryStream* _stream, asCScriptEngine* _engine)
 : module(_module), stream(_stream), engine(_engine)
{
	error = false;
}

void asCReader::ReadData(void *data, asUINT size)
{
	asASSERT(size == 1 || size == 2 || size == 4 || size == 8);
#if defined(AS_BIG_ENDIAN)
	for( asUINT n = 0; n < size; n++ )
		stream->Read(((asBYTE*)data)+n, 1);
#else
	for( int n = size-1; n >= 0; n-- )
		stream->Read(((asBYTE*)data)+n, 1);
#endif
}

int asCReader::Read()
{
	// Before starting the load, make sure that 
	// any existing resources have been freed
	module->InternalReset();

	// Call the inner method to do the actual loading
	int r = ReadInner();
	if( r < 0 )
	{
		// Something went wrong while loading the bytecode, so we need
		// to clean-up whatever has been created during the process.

		// Make sure none of the loaded functions attempt to release
		// references that have not yet been increased
		asUINT i;
		for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
			if( !dontTranslate.MoveTo(0, module->scriptFunctions[i]) )
				module->scriptFunctions[i]->byteCode.SetLength(0);
		for( i = 0; i < module->scriptGlobals.GetLength(); i++ )
			if( module->scriptGlobals[i]->GetInitFunc() )
				module->scriptGlobals[i]->GetInitFunc()->byteCode.SetLength(0);

		module->InternalReset();
	}
	else
	{
		// Init system functions properly
		engine->PrepareEngine();

		// Initialize the global variables (unless requested not to)
		if( engine->ep.initGlobalVarsAfterBuild )
			r = module->ResetGlobalVars(0);
	}

	return r;
}

int asCReader::ReadInner() 
{
	// This function will load each entity one by one from the stream.
	// If any error occurs, it will return to the caller who is 
	// responsible for cleaning up the partially loaded entities.

	engine->deferValidationOfTemplateTypes = true;

	unsigned long i, count;

	asCScriptFunction* func;

	// Read enums
	count = ReadEncodedUInt();
	module->enumTypes.Allocate(count, 0);
	for( i = 0; i < count && !error; i++ )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		if( ot == 0 )
			return asOUT_OF_MEMORY;

		ReadObjectTypeDeclaration(ot, 1);
		engine->classTypes.PushLast(ot);
		module->enumTypes.PushLast(ot);
		ot->AddRef();
		ReadObjectTypeDeclaration(ot, 2);
	}

	if( error ) return asERROR;

	// classTypes[]
	// First restore the structure names, then the properties
	count = ReadEncodedUInt();
	module->classTypes.Allocate(count, 0);
	for( i = 0; i < count && !error; ++i )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		if( ot == 0 )
			return asOUT_OF_MEMORY;

		ReadObjectTypeDeclaration(ot, 1);

		// If the type is shared, then we should use the original if it exists
		bool sharedExists = false;
		if( ot->IsShared() )
		{
			for( asUINT n = 0; n < engine->classTypes.GetLength(); n++ )
			{
				asCObjectType *t = engine->classTypes[n];
				if( t &&
					t->IsShared() &&
					t->name == ot->name &&
					t->IsInterface() == ot->IsInterface() )
				{
					asDELETE(ot, asCObjectType);
					ot = t;
					sharedExists = true;
					break;
				}
			}
		}

		if( sharedExists )
			existingShared.Insert(ot, true);
		else
		{
			engine->classTypes.PushLast(ot);

			// Add script classes to the GC
			if( (ot->GetFlags() & asOBJ_SCRIPT_OBJECT) && !ot->IsInterface() )
				engine->gc.AddScriptObjectToGC(ot, &engine->objectTypeBehaviours);
		}
		module->classTypes.PushLast(ot);
		ot->AddRef();
	}

	if( error ) return asERROR;

	// Read func defs
	count = ReadEncodedUInt();
	module->funcDefs.Allocate(count, 0);
	for( i = 0; i < count && !error; i++ )
	{
		asCScriptFunction *func = ReadFunction(false, true);
		if( func )
			module->funcDefs.PushLast(func);
		else
			error = true;
	}

	// Read interface methods
	for( i = 0; i < module->classTypes.GetLength() && !error; i++ )
	{
		if( module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 2);
	}

#ifdef AS_DEPRECATED
	// Deprecated since 2.23.0 - 2012-01-30
	asCArray<void*> substitutions;
	module->ResolveInterfaceIds(&substitutions);

	// The above method may have replaced the interface object types
	// so we must updated this in the savedDataTypes if it is there.
	// All the interface methods were also substituted so the 
	// savedFunctions must also be updated
	for( i = 0; i < substitutions.GetLength() && !error; i += 2 )
	{
		for( asUINT d = 0; d < savedDataTypes.GetLength() && !error; d++ )
		{
			if( savedDataTypes[d].GetObjectType() == substitutions[i] )
				savedDataTypes[d].SetObjectType(reinterpret_cast<asCObjectType*>(substitutions[i+1]));
		}

		for( asUINT f = 0; f < savedFunctions.GetLength() && !error; f++ )
		{
			if( savedFunctions[f] == substitutions[i] )
				savedFunctions[f] = reinterpret_cast<asCScriptFunction*>(substitutions[i+1]);
		}
	}
#endif

	// Read class methods and behaviours
	for( i = 0; i < module->classTypes.GetLength() && !error; ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 2);
	}

	// Read class properties
	for( i = 0; i < module->classTypes.GetLength() && !error; ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 3);
	}

	if( error ) return asERROR;

	// Read typedefs
	count = ReadEncodedUInt();
	module->typeDefs.Allocate(count, 0);
	for( i = 0; i < count && !error; i++ )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		if( ot == 0 )
			return asOUT_OF_MEMORY;

		ReadObjectTypeDeclaration(ot, 1);
		engine->classTypes.PushLast(ot);
		module->typeDefs.PushLast(ot);
		ot->AddRef();
		ReadObjectTypeDeclaration(ot, 2);
	}

	if( error ) return asERROR;

	// scriptGlobals[]
	count = ReadEncodedUInt();
	if( engine->ep.disallowGlobalVars )
	{
		engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, TXT_GLOBAL_VARS_NOT_ALLOWED);
		error = true;
	}
	module->scriptGlobals.Allocate(count, 0);
	for( i = 0; i < count && !error; ++i ) 
	{
		ReadGlobalProperty();
	}

	// scriptFunctions[]
	count = ReadEncodedUInt();
	for( i = 0; i < count && !error; ++i ) 
	{
		size_t len = module->scriptFunctions.GetLength();
		func = ReadFunction();
		if( func == 0 )
		{
			error = true;
			break;
		}
		
		// Is the function shared and was it created now?
		if( func->isShared && len != module->scriptFunctions.GetLength() )
		{
			// If the function already existed in another module, then
			// we need to replace it with previously existing one
			for( asUINT n = 0; n < engine->scriptFunctions.GetLength() && !error; n++ )
			{
				asCScriptFunction *realFunc = engine->scriptFunctions[n];
				if( realFunc &&
					realFunc != func &&
					realFunc->IsShared() &&
					realFunc->IsSignatureEqual(func) )
				{
					// Replace the recently created function with the pre-existing function
					module->scriptFunctions[module->scriptFunctions.GetLength()-1] = realFunc;
					realFunc->AddRef();
					savedFunctions[savedFunctions.GetLength()-1] = realFunc;
					engine->FreeScriptFunctionId(func->id);

					// Insert the function in the dontTranslate array
					dontTranslate.Insert(realFunc, true);

					// Release the function, but make sure nothing else is released
					func->id = 0;
					func->byteCode.SetLength(0);
					func->Release();
				}
			}
		}
	}

	// globalFunctions[]
	count = ReadEncodedUInt();
	for( i = 0; i < count && !error; ++i )
	{
		func = ReadFunction(false, false);
		if( func )
		{
			module->globalFunctions.PushLast(func);
			func->AddRef();
		}
		else
			error = true;
	}

	if( error ) return asERROR;

	// bindInformations[]
	count = ReadEncodedUInt();
	module->bindInformations.Allocate(count, 0);
	for( i = 0; i < count && !error; ++i )
	{
		sBindInfo *info = asNEW(sBindInfo);
		if( info == 0 )
			return asOUT_OF_MEMORY;

		info->importedFunctionSignature = ReadFunction(false, false);
		if( info->importedFunctionSignature == 0 )
		{
			error = true;
			break;
		}

		if( engine->freeImportedFunctionIdxs.GetLength() )
		{
			int id = engine->freeImportedFunctionIdxs.PopLast();
			info->importedFunctionSignature->id = int(FUNC_IMPORTED + id);
			engine->importedFunctions[id] = info;
		}
		else
		{
			info->importedFunctionSignature->id = int(FUNC_IMPORTED + engine->importedFunctions.GetLength());
			engine->importedFunctions.PushLast(info);
		}
		ReadString(&info->importFromModule);
		info->boundFunctionId = -1;
		module->bindInformations.PushLast(info);
	}

	if( error ) return asERROR;

	// usedTypes[]
	count = ReadEncodedUInt();
	usedTypes.Allocate(count, 0);
	for( i = 0; i < count && !error; ++i )
	{
		asCObjectType *ot = ReadObjectType();
		usedTypes.PushLast(ot);
	}

	// usedTypeIds[]
	if( !error )
		ReadUsedTypeIds();

	// usedFunctions[]
	if( !error )
		ReadUsedFunctions();

	// usedGlobalProperties[]
	if( !error )
		ReadUsedGlobalProps();

	// usedStringConstants[]
	if( !error ) 
		ReadUsedStringConstants();

	// usedObjectProperties
	if( !error )
		ReadUsedObjectProps();

	// Validate the template types
	for( i = 0; i < usedTypes.GetLength() && !error; i++ )
	{
		if( (usedTypes[i]->flags & asOBJ_TEMPLATE) && 
			usedTypes[i]->templateSubType.IsValid() &&
			usedTypes[i]->beh.templateCallback )
		{
			asCScriptFunction *callback = engine->scriptFunctions[usedTypes[i]->beh.templateCallback];
			if( !engine->CallGlobalFunctionRetBool(usedTypes[i], 0, callback->sysFuncIntf, callback) )
			{
				asCString str;
				str.Format(TXT_INSTANCING_INVLD_TMPL_TYPE_s_s, usedTypes[i]->name.AddressOf(), usedTypes[i]->templateSubType.Format().AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
			}
		}
	}
	engine->deferValidationOfTemplateTypes = false;

	if( error ) return asERROR;

	// Update the loaded bytecode to point to the correct types, property offsets,
	// function ids, etc. This is basically a linking stage.
	for( i = 0; i < module->scriptFunctions.GetLength() && !error; i++ )
		if( module->scriptFunctions[i]->funcType == asFUNC_SCRIPT )
			TranslateFunction(module->scriptFunctions[i]);
	for( i = 0; i < module->scriptGlobals.GetLength() && !error; i++ )
		if( module->scriptGlobals[i]->GetInitFunc() )
			TranslateFunction(module->scriptGlobals[i]->GetInitFunc());

	if( error ) return asERROR;

	// Add references for all functions (except for the pre-existing shared code)
	for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
		if( !dontTranslate.MoveTo(0, module->scriptFunctions[i]) )
			module->scriptFunctions[i]->AddReferences();
	for( i = 0; i < module->scriptGlobals.GetLength(); i++ )
		if( module->scriptGlobals[i]->GetInitFunc() )
			module->scriptGlobals[i]->GetInitFunc()->AddReferences();

	return error ? asERROR : asSUCCESS;
}

void asCReader::ReadUsedStringConstants()
{
	asCString str;

	asUINT count;
	count = ReadEncodedUInt();
	usedStringConstants.Allocate(count, 0);
	for( asUINT i = 0; i < count; ++i ) 
	{
		ReadString(&str);
		usedStringConstants.PushLast(engine->AddConstantString(str.AddressOf(), str.GetLength()));
	}
}

void asCReader::ReadUsedFunctions()
{
	asUINT count;
	count = ReadEncodedUInt();
	usedFunctions.SetLength(count);
	memset(usedFunctions.AddressOf(), 0, sizeof(asCScriptFunction *)*count);

	for( asUINT n = 0; n < usedFunctions.GetLength(); n++ )
	{
		char c;

		// Read the data to be able to uniquely identify the function

		// Is the function from the module or the application?
		ReadData(&c, 1);

		if( c == 'n' )
		{
			// Null function pointer
			usedFunctions[n] = 0;
		}
		else
		{
			asCScriptFunction func(engine, c == 'm' ? module : 0, asFUNC_DUMMY);
			ReadFunctionSignature(&func);

			// Find the correct function
			if( c == 'm' )
			{
				for( asUINT i = 0; i < module->scriptFunctions.GetLength(); i++ )
				{
					asCScriptFunction *f = module->scriptFunctions[i];
					if( !func.IsSignatureEqual(f) ||
						func.objectType != f->objectType ||
						func.funcType != f->funcType || 
						func.nameSpace != f->nameSpace )
						continue;

					usedFunctions[n] = f;
					break;
				}
			}
			else
			{
				for( asUINT i = 0; i < engine->scriptFunctions.GetLength(); i++ )
				{
					asCScriptFunction *f = engine->scriptFunctions[i];
					if( f == 0 ||
						!func.IsSignatureEqual(f) ||
						func.objectType != f->objectType ||
						func.nameSpace != f->nameSpace )
						continue;

					usedFunctions[n] = f;
					break;
				}
			}

			// Set the type to dummy so it won't try to release the id
			func.funcType = asFUNC_DUMMY;
		}
	}
}

void asCReader::ReadFunctionSignature(asCScriptFunction *func)
{
	int i, count;
	asCDataType dt;
	int num;

	ReadString(&func->name);
	ReadString(&func->nameSpace);
	ReadDataType(&func->returnType);

	count = ReadEncodedUInt();
	func->parameterTypes.Allocate(count, 0);
	for( i = 0; i < count; ++i ) 
	{
		ReadDataType(&dt);
		func->parameterTypes.PushLast(dt);
	}

	count = ReadEncodedUInt();
	func->inOutFlags.Allocate(count, 0);
	for( i = 0; i < count; ++i )
	{
		num = ReadEncodedUInt();
		func->inOutFlags.PushLast(static_cast<asETypeModifiers>(num));
	}

	func->funcType = (asEFuncType)ReadEncodedUInt();

	// Read the default args, from last to first
	count = ReadEncodedUInt();
	if( count )
	{
		func->defaultArgs.SetLength(func->parameterTypes.GetLength());
		memset(func->defaultArgs.AddressOf(), 0, sizeof(asCString*)*func->parameterTypes.GetLength());
		for( i = 0; i < count; i++ )
		{
			asCString *str = asNEW(asCString);
			if( str == 0 )
			{
				// Out of memory
				error = true;
				return;
			}
			func->defaultArgs[func->defaultArgs.GetLength()-1-i] = str;
			ReadString(str);
		}
	}
	
	func->objectType = ReadObjectType();
	if( func->objectType )
	{
		asBYTE b;
		ReadData(&b, 1);
		func->isReadOnly = (b & 1) ? true : false;
		func->isPrivate  = (b & 2) ? true : false;
	}
}

asCScriptFunction *asCReader::ReadFunction(bool addToModule, bool addToEngine, bool addToGC) 
{
	if( error ) return 0;

	char c;
	ReadData(&c, 1);

	if( c == '\0' )
	{
		// There is no function, so return a null pointer
		return 0;
	}

	if( c == 'r' )
	{
		// This is a reference to a previously saved function
		asUINT index = ReadEncodedUInt();
		if( index < savedFunctions.GetLength() )
			return savedFunctions[index];
		else
		{
			error = true;
			return 0;
		}
	}

	// Load the new function
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine,module,asFUNC_DUMMY);
	if( func == 0 )
	{
		// Out of memory
		error = true;
		return 0;
	}
	savedFunctions.PushLast(func);

	int i, count;
	asCDataType dt;
	int num;

	ReadFunctionSignature(func);

	func->id = engine->GetNextScriptFunctionId();

	if( func->funcType == asFUNC_SCRIPT )
	{
		if( addToGC )
			engine->gc.AddScriptObjectToGC(func, &engine->functionBehaviours);
		
		ReadByteCode(func);

		func->variableSpace = ReadEncodedUInt();

		count = ReadEncodedUInt();
		func->objVariablePos.Allocate(count, 0);
		func->objVariableTypes.Allocate(count, 0);
		func->funcVariableTypes.Allocate(count, 0);
		for( i = 0; i < count; ++i )
		{
			func->objVariableTypes.PushLast(ReadObjectType());
			asUINT idx = ReadEncodedUInt();
			func->funcVariableTypes.PushLast((asCScriptFunction*)(asPWORD)idx);
			num = ReadEncodedUInt();
			func->objVariablePos.PushLast(num);
		}
		if( count > 0 )
			func->objVariablesOnHeap = ReadEncodedUInt();
		else
			func->objVariablesOnHeap = 0;

		int length = ReadEncodedUInt();
		func->objVariableInfo.SetLength(length);
		for( i = 0; i < length; ++i )
		{
			func->objVariableInfo[i].programPos     = ReadEncodedUInt();
			func->objVariableInfo[i].variableOffset = ReadEncodedUInt(); // TODO: should be int
			func->objVariableInfo[i].option         = ReadEncodedUInt();
		}

		length = ReadEncodedUInt();
		func->lineNumbers.SetLength(length);
		for( i = 0; i < length; ++i )
			func->lineNumbers[i] = ReadEncodedUInt();

		ReadData(&func->isShared, 1);

		// Read the variable information
		length = ReadEncodedUInt();
		func->variables.Allocate(length, 0);
		for( i = 0; i < length; i++ )
		{
			asSScriptVariable *var = asNEW(asSScriptVariable);
			if( var == 0 )
			{
				// Out of memory
				error = true;
				return 0;
			}
			func->variables.PushLast(var);

			var->declaredAtProgramPos = ReadEncodedUInt();
			var->stackOffset = ReadEncodedUInt();
			ReadString(&var->name);
			ReadDataType(&var->type);
		}
	}
	else if( func->funcType == asFUNC_VIRTUAL )
	{
		func->vfTableIdx = ReadEncodedUInt();
	}

	// Read script section name
	asCString name;
	ReadString(&name);
	func->scriptSectionIdx = engine->GetScriptSectionNameIndex(name.AddressOf());

	if( addToModule )
	{
		// The refCount is already 1
		module->scriptFunctions.PushLast(func);
	}
	if( addToEngine )
		engine->SetScriptFunction(func);
	if( func->objectType )
		func->ComputeSignatureId();

	return func;
}

void asCReader::ReadObjectTypeDeclaration(asCObjectType *ot, int phase)
{
	if( phase == 1 )
	{
		// Read the initial attributes
		ReadString(&ot->name);
		ReadData(&ot->flags, 4);
		ot->size = ReadEncodedUInt();
		ReadString(&ot->nameSpace);

		// Reset the size of script classes, since it will be recalculated as properties are added
		if( (ot->flags & asOBJ_SCRIPT_OBJECT) && ot->size != 0 )
			ot->size = sizeof(asCScriptObject);

		// Use the default script class behaviours
		ot->beh = engine->scriptTypeBehaviours.beh;
		ot->beh.construct = 0;
		ot->beh.factory = 0;
		ot->beh.constructors.PopLast(); // These will be read from the file
		ot->beh.factories.PopLast(); // These will be read from the file
		engine->scriptFunctions[ot->beh.addref]->AddRef();
		engine->scriptFunctions[ot->beh.release]->AddRef();
		engine->scriptFunctions[ot->beh.gcEnumReferences]->AddRef();
		engine->scriptFunctions[ot->beh.gcGetFlag]->AddRef();
		engine->scriptFunctions[ot->beh.gcGetRefCount]->AddRef();
		engine->scriptFunctions[ot->beh.gcReleaseAllReferences]->AddRef();
		engine->scriptFunctions[ot->beh.gcSetFlag]->AddRef();
		engine->scriptFunctions[ot->beh.copy]->AddRef();
		for( asUINT i = 1; i < ot->beh.operators.GetLength(); i += 2 )
			engine->scriptFunctions[ot->beh.operators[i]]->AddRef();
	}
	else if( phase == 2 )
	{
		if( ot->flags & asOBJ_ENUM )
		{
			int count = ReadEncodedUInt();
			ot->enumValues.Allocate(count, 0);
			for( int n = 0; n < count; n++ )
			{
				asSEnumValue *e = asNEW(asSEnumValue);
				if( e == 0 )
				{
					// Out of memory
					error = true;
					return;
				}
				ReadString(&e->name);
				ReadData(&e->value, 4);
				ot->enumValues.PushLast(e);
			}
		}
		else if( ot->flags & asOBJ_TYPEDEF )
		{
			eTokenType t = (eTokenType)ReadEncodedUInt();
			ot->templateSubType = asCDataType::CreatePrimitive(t, false);
		}
		else
		{
			// If the type is shared and pre-existing, we should just 
			// validate that the loaded methods match the original 
			bool sharedExists = existingShared.MoveTo(0, ot);
			if( sharedExists )
			{
				asCObjectType *dt = ReadObjectType();
				if( ot->derivedFrom != dt )
				{
					// TODO: Write message
					error = true;
				}
			}
			else
			{
				ot->derivedFrom = ReadObjectType();
				if( ot->derivedFrom )
					ot->derivedFrom->AddRef();
			}

			// interfaces[]
			int size = ReadEncodedUInt();
			if( sharedExists )
			{
				for( int n = 0; n < size; n++ )
				{
					asCObjectType *intf = ReadObjectType();
					if( !ot->Implements(intf) )
					{
						// TODO: Write message
						error = true;
					}
				}
			}
			else
			{
				ot->interfaces.Allocate(size,0);
				for( int n = 0; n < size; n++ )
				{
					asCObjectType *intf = ReadObjectType();
					ot->interfaces.PushLast(intf);
				}
			}

			// behaviours
			if( !ot->IsInterface() && ot->flags != asOBJ_TYPEDEF && ot->flags != asOBJ_ENUM )
			{
				asCScriptFunction *func = ReadFunction(!sharedExists, !sharedExists, !sharedExists);
				if( sharedExists )
				{
					// Find the real function in the object, and update the savedFunctions array
					asCScriptFunction *realFunc = engine->GetScriptFunction(ot->beh.destruct);
					if( (realFunc == 0 && func == 0) || realFunc->IsSignatureEqual(func) )
					{
						// If the function is not the last, then the substitution has already occurred before
						if( func && savedFunctions[savedFunctions.GetLength()-1] == func )
							savedFunctions[savedFunctions.GetLength()-1] = realFunc;
					}
					else
					{
						// TODO: Write message
						error = true;
					}
					// Destroy the function without releasing any references
					if( func )
					{
						func->id = 0;
						func->byteCode.SetLength(0);
						func->Release();
						module->scriptFunctions.PushLast(realFunc);
						realFunc->AddRef();
						dontTranslate.Insert(realFunc, true);
					}
				}
				else
				{
					if( func )
					{
						ot->beh.destruct = func->id;
						func->AddRef();
					}
					else
						ot->beh.destruct = 0;
				}

				size = ReadEncodedUInt();
				for( int n = 0; n < size; n++ )
				{
					asCScriptFunction *func = ReadFunction(!sharedExists, !sharedExists, !sharedExists);
					if( func )
					{
						if( sharedExists )
						{
							// Find the real function in the object, and update the savedFunctions array
							bool found = false;
							for( asUINT n = 0; n < ot->beh.constructors.GetLength(); n++ )
							{
								asCScriptFunction *realFunc = engine->GetScriptFunction(ot->beh.constructors[n]);
								if( realFunc->IsSignatureEqual(func) )
								{
									// If the function is not the last, then the substitution has already occurred before
									if( savedFunctions[savedFunctions.GetLength()-1] == func )
										savedFunctions[savedFunctions.GetLength()-1] = realFunc;
									found = true;
									module->scriptFunctions.PushLast(realFunc);
									realFunc->AddRef();
									dontTranslate.Insert(realFunc, true);
									break;
								}
							}
							if( !found )
							{
								// TODO: Write message
								error = true;
							}
							// Destroy the function without releasing any references
							func->id = 0;
							func->byteCode.SetLength(0);
							func->Release();
						}
						else
						{
							ot->beh.constructors.PushLast(func->id);
							func->AddRef();

							if( func->parameterTypes.GetLength() == 0 )
								ot->beh.construct = func->id;
						}
					}
					else
					{
						// TODO: Write message
						error = true;
					}

					func = ReadFunction(!sharedExists, !sharedExists, !sharedExists);
					if( func )
					{
						if( sharedExists )
						{
							// Find the real function in the object, and update the savedFunctions array
							bool found = false;
							for( asUINT n = 0; n < ot->beh.factories.GetLength(); n++ )
							{
								asCScriptFunction *realFunc = engine->GetScriptFunction(ot->beh.factories[n]);
								if( realFunc->IsSignatureEqual(func) )
								{
									// If the function is not the last, then the substitution has already occurred before
									if( savedFunctions[savedFunctions.GetLength()-1] == func )
										savedFunctions[savedFunctions.GetLength()-1] = realFunc;
									found = true;
									module->scriptFunctions.PushLast(realFunc);
									realFunc->AddRef();
									dontTranslate.Insert(realFunc, true);
									break;
								}
							}
							if( !found )
							{
								// TODO: Write message
								error = true;
							}
							// Destroy the function without releasing any references
							func->id = 0;
							func->byteCode.SetLength(0);
							func->Release();
						}
						else
						{
							ot->beh.factories.PushLast(func->id);
							func->AddRef();

							if( func->parameterTypes.GetLength() == 0 )
								ot->beh.factory = func->id;
						}
					}
					else
					{
						// TODO: Write message
						error = true;
					}
				}
			}

			// methods[]
			size = ReadEncodedUInt();
			int n;
			for( n = 0; n < size; n++ ) 
			{
				asCScriptFunction *func = ReadFunction(!sharedExists, !sharedExists, !sharedExists);
				if( func )
				{
					if( sharedExists )
					{
						// Find the real function in the object, and update the savedFunctions array
						bool found = false;
						for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
						{
							asCScriptFunction *realFunc = engine->GetScriptFunction(ot->methods[n]);
							if( realFunc->IsSignatureEqual(func) )
							{
								// If the function is not the last, then the substitution has already occurred before
								if( savedFunctions[savedFunctions.GetLength()-1] == func )
									savedFunctions[savedFunctions.GetLength()-1] = realFunc;
								found = true;
								module->scriptFunctions.PushLast(realFunc);
								realFunc->AddRef();
								dontTranslate.Insert(realFunc, true);
								break;
							}
						}
						if( !found )
						{
							// TODO: Write message
							error = true;
						}
						// If the function received wasn't an already existing 
						// function we must now destroy it
						if( !savedFunctions.Exists(func) )
						{
							// Destroy the function without releasing any references
							func->id = 0;
							func->byteCode.SetLength(0);
							func->Release();
						}
					}
					else
					{
						ot->methods.PushLast(func->id);
						func->AddRef();
					}
				}
				else
				{
					// TODO: Write message
					error = true;
				}
			}

			// virtualFunctionTable[]
			size = ReadEncodedUInt();
			for( n = 0; n < size; n++ )
			{
				asCScriptFunction *func = ReadFunction(!sharedExists, !sharedExists, !sharedExists);
				if( func )
				{
					if( sharedExists )
					{
						// Find the real function in the object, and update the savedFunctions array
						bool found = false;
						for( asUINT n = 0; n < ot->virtualFunctionTable.GetLength(); n++ )
						{
							asCScriptFunction *realFunc = ot->virtualFunctionTable[n];
							if( realFunc->IsSignatureEqual(func) )
							{
								// If the function is not the last, then the substitution has already occurred before
								if( savedFunctions[savedFunctions.GetLength()-1] == func )
									savedFunctions[savedFunctions.GetLength()-1] = realFunc;
								found = true;
								module->scriptFunctions.PushLast(realFunc);
								realFunc->AddRef();
								dontTranslate.Insert(realFunc, true);
								break;
							}
						}
						if( !found )
						{
							// TODO: Write message
							error = true;
						}
						// If the function received wasn't an already existing 
						// function we must now destroy it
						if( !savedFunctions.Exists(func) )
						{
							// Destroy the function without releasing any references
							func->id = 0;
							func->byteCode.SetLength(0);
							func->Release();
						}
					}
					else
					{
						ot->virtualFunctionTable.PushLast(func);
						func->AddRef();
					}
				}
				else
				{
					// TODO: Write message
					error = true;
				}
			}
		}
	}
	else if( phase == 3 )
	{
		// properties[]
		asUINT size = ReadEncodedUInt();
		for( asUINT n = 0; n < size; n++ )
			ReadObjectProperty(ot);
	}
}

asWORD asCReader::ReadEncodedUInt16()
{
	asDWORD dw = ReadEncodedUInt();
	if( (dw>>16) != 0 && (dw>>16) != 0xFFFF )
	{
		// TODO: Write message
		error = true;
	}

	return asWORD(dw & 0xFFFF);
}

asUINT asCReader::ReadEncodedUInt()
{
	asQWORD qw = ReadEncodedUInt64();
	if( (qw>>32) != 0 && (qw>>32) != 0xFFFFFFFF )
	{
		// TODO: Write message
		error = true;
	}

	return asUINT(qw & 0xFFFFFFFFu);
}

asQWORD asCReader::ReadEncodedUInt64()
{
	asQWORD i = 0;
	asBYTE b;
	ReadData(&b, 1);
	bool isNegative = ( b & 0x80 ) ? true : false;
	b &= 0x7F;
	
	if( (b & 0x7F) == 0x7F )
	{
		ReadData(&b, 1); i = asQWORD(b) << 56;
		ReadData(&b, 1); i += asQWORD(b) << 48;
		ReadData(&b, 1); i += asQWORD(b) << 40;
		ReadData(&b, 1); i += asQWORD(b) << 32;
		ReadData(&b, 1); i += asUINT(b) << 24;
		ReadData(&b, 1); i += asUINT(b) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}
	else if( (b & 0x7E) == 0x7E )
	{
		i = asQWORD(b & 0x01) << 48;
		ReadData(&b, 1); i += asQWORD(b) << 40;
		ReadData(&b, 1); i += asQWORD(b) << 32;
		ReadData(&b, 1); i += asUINT(b) << 24;
		ReadData(&b, 1); i += asUINT(b) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}	
	else if( (b & 0x7C) == 0x7C )
	{
		i = asQWORD(b & 0x03) << 40;
		ReadData(&b, 1); i += asQWORD(b) << 32;
		ReadData(&b, 1); i += asUINT(b) << 24;
		ReadData(&b, 1); i += asUINT(b) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}	
	else if( (b & 0x78) == 0x78 )
	{
		i = asQWORD(b & 0x07) << 32;
		ReadData(&b, 1); i += asUINT(b) << 24;
		ReadData(&b, 1); i += asUINT(b) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}	
	else if( (b & 0x70) == 0x70 )
	{
		i = asUINT(b & 0x0F) << 24;
		ReadData(&b, 1); i += asUINT(b) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}
	else if( (b & 0x60) == 0x60 )
	{
		i = asUINT(b & 0x1F) << 16;
		ReadData(&b, 1); i += asUINT(b) << 8;
		ReadData(&b, 1); i += b;
	}
	else if( (b & 0x40) == 0x40 )
	{
		i = asUINT(b & 0x3F) << 8;
		ReadData(&b, 1); i += b;
	}
	else
	{
		i = b;
	}
	if( isNegative )
		i = (asQWORD)(-asINT64(i));

	return i;
}

void asCReader::ReadString(asCString* str) 
{
	char b;
	ReadData(&b, 1);
	if( b == '\0' )
	{
		str->SetLength(0);
	}
	else if( b == 'n' )
	{
		asUINT len = ReadEncodedUInt();
		str->SetLength(len);
		stream->Read(str->AddressOf(), len);

		savedStrings.PushLast(*str);
	}
	else
	{
		asUINT n = ReadEncodedUInt();
		if( n < savedStrings.GetLength() )
			*str = savedStrings[n];
		else
			error = true;
	}
}

void asCReader::ReadGlobalProperty() 
{
	asCString name;
	asCString nameSpace;
	asCDataType type;

	ReadString(&name);
	ReadString(&nameSpace);
	ReadDataType(&type);

	asCGlobalProperty *prop = module->AllocateGlobalProperty(name.AddressOf(), type, nameSpace);

	// Read the initialization function
	bool f;
	ReadData(&f, 1);
	if( f )
	{
		asCScriptFunction *func = ReadFunction(false, true);
		if( func )
		{
			prop->SetInitFunc(func);
			func->Release();
		}
		else
			error = true;
	}
}

void asCReader::ReadObjectProperty(asCObjectType *ot) 
{
	asCString name;
	ReadString(&name);
	asCDataType dt;
	ReadDataType(&dt);
	bool isPrivate;
	ReadData(&isPrivate, 1);

	// TODO: shared: If the type is shared and pre-existing, we should just 
	//               validate that the loaded methods match the original 
	if( !existingShared.MoveTo(0, ot) )
		ot->AddPropertyToClass(name, dt, isPrivate);
}

void asCReader::ReadDataType(asCDataType *dt) 
{
	eTokenType tokenType;

	tokenType = (eTokenType)ReadEncodedUInt();
	if( tokenType == 0 )
	{
		// Get the datatype from the cache
		asUINT n = ReadEncodedUInt();
		*dt = savedDataTypes[n];
		return;
	}

	// Read the datatype for the first time
	asCObjectType *objType = 0;
	bool isObjectHandle  = false;
	bool isReadOnly      = false;
	bool isHandleToConst = false;
	bool isReference     = false;

	if( tokenType == ttIdentifier )
	{
		objType = ReadObjectType();
		ReadData(&isObjectHandle, 1);
		ReadData(&isHandleToConst, 1);
	}
	ReadData(&isReference, 1);
	ReadData(&isReadOnly, 1);

	asCScriptFunction *funcDef = 0;
	if( tokenType == ttIdentifier && objType && objType->name == "_builtin_function_" )
	{
		asCScriptFunction func(engine, module, asFUNC_DUMMY);
		ReadFunctionSignature(&func);
		for( asUINT n = 0; n < engine->registeredFuncDefs.GetLength(); n++ )
		{
			// TODO: access: Only return the definitions that the module has access to
			if( engine->registeredFuncDefs[n]->name == func.name &&
				engine->registeredFuncDefs[n]->nameSpace == func.nameSpace )
			{
				funcDef = engine->registeredFuncDefs[n];
				break;
			}
		}

		if( !funcDef && module )
		{
			for( asUINT n = 0; n < module->funcDefs.GetLength(); n++ )
			{
				if( module->funcDefs[n]->name == func.name &&
					module->funcDefs[n]->nameSpace == func.nameSpace )
				{
					funcDef = module->funcDefs[n];
					break;
				}
			}
		}

		func.funcType = asFUNC_DUMMY;
	}

	if( funcDef )
		*dt = asCDataType::CreateFuncDef(funcDef);
	else if( tokenType == ttIdentifier )
		*dt = asCDataType::CreateObject(objType, false);
	else
		*dt = asCDataType::CreatePrimitive(tokenType, false);
	if( isObjectHandle )
	{
		dt->MakeReadOnly(isHandleToConst);
		dt->MakeHandle(true);
	}
	dt->MakeReadOnly(isReadOnly);
	dt->MakeReference(isReference);

	savedDataTypes.PushLast(*dt);
}

asCObjectType* asCReader::ReadObjectType() 
{
	asCObjectType *ot = 0;
	char ch;
	ReadData(&ch, 1);
	if( ch == 'a' )
	{
		// Read the name of the template type
		asCString typeName;
		ReadString(&typeName);
		asCObjectType *tmpl = engine->GetObjectType(typeName.AddressOf(), "");
		if( tmpl == 0 )
		{
			asCString str;
			str.Format(TXT_TEMPLATE_TYPE_s_DOESNT_EXIST, typeName.AddressOf());
			engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
			error = true;
			return 0;
		}

		ReadData(&ch, 1);
		if( ch == 's' )
		{
			ot = ReadObjectType();
			if( ot == 0 )
			{
				asCString str;
				str.Format(TXT_FAILED_READ_SUBTYPE_OF_TEMPLATE_s, typeName.AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}

			asCDataType dt = asCDataType::CreateObject(ot, false);

			ReadData(&ch, 1);
			if( ch == 'h' )
				dt.MakeHandle(true);

			if( tmpl->templateSubType.GetObjectType() == ot )
				ot = tmpl;
			else
				ot = engine->GetTemplateInstanceType(tmpl, dt);
			
			if( ot == 0 )
			{
				asCString str;
				str.Format(TXT_INSTANCING_INVLD_TMPL_TYPE_s_s, typeName.AddressOf(), dt.Format().AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}
		}
		else
		{
			eTokenType tokenType = (eTokenType)ReadEncodedUInt();
			asCDataType dt = asCDataType::CreatePrimitive(tokenType, false);

			ot = engine->GetTemplateInstanceType(tmpl, dt);
			
			if( ot == 0 )
			{
				asCString str;
				str.Format(TXT_INSTANCING_INVLD_TMPL_TYPE_s_s, typeName.AddressOf(), dt.Format().AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}
		}
	}
	else if( ch == 's' )
	{
		// Read the name of the template subtype
		asCString typeName;
		ReadString(&typeName);

		// Find the template subtype
		ot = 0;
		for( asUINT n = 0; n < engine->templateSubTypes.GetLength(); n++ )
		{
			if( engine->templateSubTypes[n] && engine->templateSubTypes[n]->name == typeName )
			{
				ot = engine->templateSubTypes[n];
				break;
			}
		}

		if( ot == 0 )
		{
			asCString str;
			str.Format(TXT_TEMPLATE_SUBTYPE_s_DOESNT_EXIST, typeName.AddressOf());
			engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
			error = true;
			return 0;
		}
	}
	else if( ch == 'o' )
	{
		// Read the object type name
		asCString typeName, nameSpace;
		ReadString(&typeName);
		ReadString(&nameSpace);

		if( typeName.GetLength() && typeName != "_builtin_object_" && typeName != "_builtin_function_" )
		{
			// Find the object type
			ot = module->GetObjectType(typeName.AddressOf(), nameSpace);
			if( !ot )
				ot = engine->GetObjectType(typeName.AddressOf(), nameSpace);
			
			if( ot == 0 )
			{
				asCString str;
				str.Format(TXT_OBJECT_TYPE_s_DOESNT_EXIST, typeName.AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}
		}
		else if( typeName == "_builtin_object_" )
		{
			ot = &engine->scriptTypeBehaviours;
		}
		else if( typeName == "_builtin_function_" )
		{
			ot = &engine->functionBehaviours;
		}
		else
			asASSERT( false );
	}
	else
	{
		// No object type
		asASSERT( ch == '\0' );
		ot = 0;
	}

	return ot;
}

void asCReader::ReadByteCode(asCScriptFunction *func)
{
	// Read number of instructions
	asUINT numInstructions = ReadEncodedUInt();

	// Reserve some space for the instructions
	func->byteCode.Allocate(numInstructions, 0);

	asUINT pos = 0;
	while( numInstructions )
	{
		asBYTE b;
		ReadData(&b, 1);

		// Allocate the space for the instruction
		asUINT len = asBCTypeSize[asBCInfo[b].type];
		func->byteCode.SetLength(func->byteCode.GetLength() + len);
		asDWORD *bc = func->byteCode.AddressOf() + pos;
		pos += len;

		switch( asBCInfo[b].type )
		{
		case asBCTYPE_NO_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;
			}
			break;
		case asBCTYPE_W_ARG:
		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;

				bc++;
			}
			break;
		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_W_DW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the word argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the dword argument
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the argument
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_DW_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the first argument
				*bc++ = ReadEncodedUInt();

				// Read the second argument
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_wW_rW_rW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				w = ReadEncodedUInt16();
				*(asWORD*)bc = w;

				// Read the third argument
				w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;

				bc++;
			}
			break;
		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_rW_rW_ARG:
		case asBCTYPE_wW_W_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				w = ReadEncodedUInt16();
				*(asWORD*)bc = w;

				bc++;
			}
			break;
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				w = ReadEncodedUInt16();
				*(asWORD*)bc = w;
				bc++;
	
				// Read the third argument
				asDWORD dw = ReadEncodedUInt();
				*bc++ = dw;
			}
			break;
		case asBCTYPE_QW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the argument
				asQWORD qw = ReadEncodedUInt64();
				*(asQWORD*)bc = qw;
				bc += 2;
			}
			break;
		case asBCTYPE_QW_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the first argument
				asQWORD qw = ReadEncodedUInt64();
				*(asQWORD*)bc = qw;
				bc += 2;

				// Read the second argument
				asDWORD dw = ReadEncodedUInt();
				*bc++ = dw;
			}
			break;
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_wW_QW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w = ReadEncodedUInt16();
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the argument
				asQWORD qw = ReadEncodedUInt64();
				*(asQWORD*)bc = qw;
				bc += 2;
			}
			break;
		default:
			{
				// This should never happen
				asASSERT(false);

				// Read the next 3 bytes
				asDWORD c; asBYTE t;
#if defined(AS_BIG_ENDIAN)
				c = b << 24;
				ReadData(&t, 1); c += t << 16;
				ReadData(&t, 1); c += t << 8;
				ReadData(&t, 1); c += t;
#else
				c = b;
				ReadData(&t, 1); c += t << 8;
				ReadData(&t, 1); c += t << 16;
				ReadData(&t, 1); c += t << 24;
#endif

				*bc++ = c;
				c = *(asBYTE*)&c;

				// Read the bc as is
				for( int n = 1; n < asBCTypeSize[asBCInfo[c].type]; n++ )
					ReadData(&*bc++, 4);
			}
		}

		numInstructions--;
	}
}

void asCReader::ReadUsedTypeIds()
{
	asUINT count = ReadEncodedUInt();
	usedTypeIds.Allocate(count, 0);
	for( asUINT n = 0; n < count; n++ )
	{
		asCDataType dt;
		ReadDataType(&dt);
		usedTypeIds.PushLast(engine->GetTypeIdFromDataType(dt));
	}
}

void asCReader::ReadUsedGlobalProps()
{
	int c = ReadEncodedUInt();

	usedGlobalProperties.Allocate(c, 0);

	for( int n = 0; n < c; n++ )
	{
		asCString name, nameSpace;
		asCDataType type;
		char moduleProp;

		ReadString(&name);
		ReadString(&nameSpace);
		ReadDataType(&type);
		ReadData(&moduleProp, 1);

		// Find the real property
		void *prop = 0;
		if( moduleProp )
		{
			for( asUINT p = 0; p < module->scriptGlobals.GetLength(); p++ )
			{
				if( module->scriptGlobals[p]->name == name &&
					module->scriptGlobals[p]->nameSpace == nameSpace &&
					module->scriptGlobals[p]->type == type )
				{
					prop = module->scriptGlobals[p]->GetAddressOfValue();
					break;
				}
			}
		}
		else
		{
			for( asUINT p = 0; p < engine->registeredGlobalProps.GetLength(); p++ )
			{
				if( engine->registeredGlobalProps[p] &&
					engine->registeredGlobalProps[p]->name == name &&
					engine->registeredGlobalProps[p]->nameSpace == nameSpace &&
					engine->registeredGlobalProps[p]->type == type )
				{
					prop = engine->registeredGlobalProps[p]->GetAddressOfValue();
					break;
				}
			}
		}

		usedGlobalProperties.PushLast(prop);

		if( prop == 0 )
		{
			// TODO: Write error message to the callback
			error = true;
		}
	}
}

void asCReader::ReadUsedObjectProps()
{
	asUINT c = ReadEncodedUInt();

	usedObjectProperties.SetLength(c);
	for( asUINT n = 0; n < c; n++ )
	{
		asCObjectType *objType = ReadObjectType();
		if( objType == 0 )
		{
			// TODO: Write error message to callback
			error = true;
			break;
		}

		asCString name;
		ReadString(&name);

		// Find the property offset
		bool found = false;
		for( asUINT p = 0; p < objType->properties.GetLength(); p++ )
		{
			if( objType->properties[p]->name == name )
			{
				usedObjectProperties[n].objType = objType;
				usedObjectProperties[n].offset = objType->properties[p]->byteOffset;
				found = true;
				break;
			}
		}

		if( !found )
		{
			// TODO: Write error message to callback
			error = true;
			return;
		}
	}
}

short asCReader::FindObjectPropOffset(asWORD index)
{
	if( index >= usedObjectProperties.GetLength() )
	{
		// TODO: Write to message callback
		asASSERT(false);
		error = true;
		return 0;
	}

	return (short)usedObjectProperties[index].offset;
}

asCScriptFunction *asCReader::FindFunction(int idx)
{
	if( idx >= 0 && idx < (int)usedFunctions.GetLength() )
		return usedFunctions[idx];
	else
	{
		// TODO: Write to message callback
		error = true;
		return 0;
	}
}

void asCReader::TranslateFunction(asCScriptFunction *func)
{
	// Skip this if the function is part of an pre-existing shared object
	if( dontTranslate.MoveTo(0, func) ) return;

	// Pre-compute the size of each instruction in order to translate jump offsets
	asUINT n;
	asDWORD *bc = func->byteCode.AddressOf();
	asCArray<asUINT> bcSizes(func->byteCode.GetLength());
	asCArray<asUINT> instructionNbrToPos(func->byteCode.GetLength());
	for( n = 0; n < func->byteCode.GetLength(); )
	{
		int c = *(asBYTE*)&bc[n];
		asUINT size = asBCTypeSize[asBCInfo[c].type];
		bcSizes.PushLast(size);
		instructionNbrToPos.PushLast(n);
		n += size;
	}

	asUINT bcNum = 0;
	for( n = 0; n < func->byteCode.GetLength(); bcNum++ )
	{
		int c = *(asBYTE*)&bc[n];
		if( c == asBC_FREE ||
			c == asBC_REFCPY || 
			c == asBC_RefCpyV ||
			c == asBC_OBJTYPE )
		{
			// Translate the index to the true object type
			asPWORD *ot = (asPWORD*)&bc[n+1];
			*(asCObjectType**)ot = FindObjectType(*(int*)ot);
		}
		else if( c == asBC_TYPEID ||
			     c == asBC_Cast )
		{
			// Translate the index to the type id
			int *tid = (int*)&bc[n+1];
			*tid = FindTypeId(*tid);
		}
		else if( c == asBC_ADDSi ||
			     c == asBC_LoadThisR )
		{
			// Translate the index to the type id
			int *tid = (int*)&bc[n+1];
			*tid = FindTypeId(*tid);

			// Translate the prop index into the property offset
			*(((short*)&bc[n])+1) = FindObjectPropOffset(*(((short*)&bc[n])+1));
		}
		else if( c == asBC_LoadRObjR ||
			     c == asBC_LoadVObjR )
		{
			// Translate the index to the type id
			int *tid = (int*)&bc[n+2];
			*tid = FindTypeId(*tid);

			// Translate the prop index into the property offset
			*(((short*)&bc[n])+2) = FindObjectPropOffset(*(((short*)&bc[n])+2));
		}
		else if( c == asBC_COPY )
		{
			// Translate the index to the type id
			int *tid = (int*)&bc[n+1];
			*tid = FindTypeId(*tid);

			// COPY is used to copy POD types that don't have the opAssign method
			// Update the number of dwords to copy as it may be different on the target platform
			asCDataType dt = engine->GetDataTypeFromTypeId(*tid);
			if( !dt.IsValid() )
			{
				// TODO: Write error to message
				error = true;
			}
			else
				asBC_SWORDARG0(&bc[n]) = (short)dt.GetSizeInMemoryDWords();
		}
		else if( c == asBC_RET )
		{
			// Determine the correct amount of DWORDs to pop
			asWORD dw = (asWORD)func->GetSpaceNeededForArguments();
			if( func->DoesReturnOnStack() ) dw += AS_PTR_SIZE;
			if( func->objectType ) dw += AS_PTR_SIZE;
			asBC_WORDARG0(&bc[n]) = dw;
		}
		else if( c == asBC_CALL ||
				 c == asBC_CALLINTF ||
				 c == asBC_CALLSYS )
		{
			// Translate the index to the func id
			int *fid = (int*)&bc[n+1];
			asCScriptFunction *f = FindFunction(*fid);
			if( f )
				*fid = f->id;
			else
			{
				// TODO: Write to message callback
				error = true;
				return;
			}
		}
		else if( c == asBC_FuncPtr )
		{
			// Translate the index to the func pointer
			asPWORD *fid = (asPWORD*)&bc[n+1];
			*fid = (asPWORD)FindFunction((int)*fid);
		}
		else if( c == asBC_ALLOC )
		{
			// Translate the index to the true object type
			asPWORD *arg = (asPWORD*)&bc[n+1];
			*(asCObjectType**)arg = FindObjectType(*(int*)arg);

			// If the object type is a script class then the constructor id must be translated
			asCObjectType *ot = *(asCObjectType**)arg;
			if( ot && (ot->flags & asOBJ_SCRIPT_OBJECT) )
			{
				int *fid = (int*)&bc[n+1+AS_PTR_SIZE];
				asCScriptFunction *f = FindFunction(*fid);
				if( f )
					*fid = f->id;
				else
				{
					// TODO: Write to message callback
					error = true;
					return;
				}
			}
		}
		else if( c == asBC_STR )
		{
			// Translate the index to the true string id
			asWORD *arg = ((asWORD*)&bc[n])+1;

			if( *arg < usedStringConstants.GetLength() )	
				*arg = (asWORD)usedStringConstants[*arg];
			else
			{
				// TODO: Write to message callback
				error = true;
				return;
			}
		}
		else if( c == asBC_CALLBND )
		{
			// Translate the function id
			asUINT *fid = (asUINT*)&bc[n+1];
			if( *fid < module->bindInformations.GetLength() )
			{
				sBindInfo *bi = module->bindInformations[*fid];
				if( bi )
					*fid = bi->importedFunctionSignature->id;
				else
				{
					// TODO: Write to message callback
					error = true;
					return;
				}
			}
			else
			{
				// TODO: Write to message callback
				error = true;
				return;
			}
		}
		else if( c == asBC_PGA      ||
			     c == asBC_PshGPtr  ||
			     c == asBC_LDG      ||
				 c == asBC_PshG4    ||
				 c == asBC_LdGRdR4  ||
				 c == asBC_CpyGtoV4 ||
				 c == asBC_CpyVtoG4 ||
				 c == asBC_SetG4    )
		{
			// Translate the global var index to pointer
			asPWORD *index = (asPWORD*)&bc[n+1];
			if( *(asUINT*)index < usedGlobalProperties.GetLength() )
				*(void**)index = usedGlobalProperties[*(asUINT*)index];
			else
			{
				// TODO: Write to message callback
				error = true;
				return;
			}
		}
		else if( c == asBC_JMP    ||
			     c == asBC_JZ     ||
				 c == asBC_JNZ    ||
			     c == asBC_JLowZ  ||
				 c == asBC_JLowNZ ||
				 c == asBC_JS     ||
				 c == asBC_JNS    ||
				 c == asBC_JP     ||
				 c == asBC_JNP    ) // The JMPP instruction doesn't need modification
		{
			// Get the offset 
			int offset = int(bc[n+1]);

			// Count the instruction sizes to the destination instruction
			int size = 0;
			if( offset >= 0 )
				// If moving ahead, then start from next instruction
				for( asUINT num = bcNum+1; offset-- > 0; num++ )
					size += bcSizes[num];
			else
				// If moving backwards, then start at current instruction
				for( asUINT num = bcNum; offset++ < 0; num-- )
					size -= bcSizes[num];

			// The size is dword offset 
			bc[n+1] = size;
		}

		n += asBCTypeSize[asBCInfo[c].type];
	}

	// Calculate the stack adjustments
	CalculateAdjustmentByPos(func);

	// Adjust all variable positions in the bytecode
	bc = func->byteCode.AddressOf();
	for( n = 0; n < func->byteCode.GetLength(); )
	{
		int c = *(asBYTE*)&bc[n];
		switch( asBCInfo[c].type )
		{
		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_QW_ARG:
		case asBCTYPE_rW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_wW_W_ARG:
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				asBC_SWORDARG0(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG0(&bc[n]));
			}
			break;

		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_rW_ARG:
			{
				asBC_SWORDARG0(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG0(&bc[n]));
				asBC_SWORDARG1(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG1(&bc[n]));
			}
			break;

		case asBCTYPE_wW_rW_rW_ARG:
			{
				asBC_SWORDARG0(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG0(&bc[n]));
				asBC_SWORDARG1(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG1(&bc[n]));
				asBC_SWORDARG2(&bc[n]) = (short)AdjustStackPosition(asBC_SWORDARG2(&bc[n]));
			}
			break;

		default:
			// The other types don't treat variables so won't be modified
			break;
		}

		n += asBCTypeSize[asBCInfo[c].type];
	}

	// Adjust the space needed for local variables
	func->variableSpace = AdjustStackPosition(func->variableSpace);

	// Adjust the variable information. This will be used during the adjustment below
	for( n = 0; n < func->variables.GetLength(); n++ )
	{
		func->variables[n]->declaredAtProgramPos = instructionNbrToPos[func->variables[n]->declaredAtProgramPos];
		func->variables[n]->stackOffset = AdjustStackPosition(func->variables[n]->stackOffset);
	}

	// objVariablePos
	for( n = 0; n < func->objVariablePos.GetLength(); n++ )
	{
		func->objVariablePos[n] = AdjustStackPosition(func->objVariablePos[n]);
		func->funcVariableTypes[n] = FindFunction((int)(asPWORD)func->funcVariableTypes[n]);
	}

	// Adjust the get offsets. This must be done in the second iteration because
	// it relies on the function ids and variable position already being correct in the 
	// bytecodes that come after the GET instructions.
	// TODO: optimize: Instead of doing a full extra loop. We can push the GET instructions
	//                 on a stack, and then when a call instruction is found update all of them.
	//                 This will also make the AdjustGetOffset() function quicker as it can 
	//                 receive the called function directly instead of having to search for it.
	bc = func->byteCode.AddressOf();
	for( n = 0; n < func->byteCode.GetLength(); )
	{
		int c = *(asBYTE*)&bc[n];

		if( c == asBC_GETREF ||
		    c == asBC_GETOBJ ||
		    c == asBC_GETOBJREF )
		{
			asBC_WORDARG0(&bc[n]) = (asWORD)AdjustGetOffset(asBC_WORDARG0(&bc[n]), func, n);
		}

		n += asBCTypeSize[asBCInfo[c].type];
	}

	// objVariableInfo[x].variableOffset  // TODO: should be an index into the objVariablePos array
	for( n = 0; n < func->objVariableInfo.GetLength(); n++ )
	{
		// The program position must be adjusted as it is stored in number of instructions
		func->objVariableInfo[n].programPos = instructionNbrToPos[func->objVariableInfo[n].programPos];
		func->objVariableInfo[n].variableOffset = AdjustStackPosition(func->objVariableInfo[n].variableOffset);
	}

	// The program position (every even number) needs to be adjusted
	// for the line numbers to be in number of dwords instead of number of instructions 
	for( n = 0; n < func->lineNumbers.GetLength(); n += 2 )
	{
		func->lineNumbers[n] = instructionNbrToPos[func->lineNumbers[n]];
	}

	CalculateStackNeeded(func);
}

void asCReader::CalculateStackNeeded(asCScriptFunction *func)
{
	int largestStackUsed = 0;

	// Clear the known stack size for each bytecode
	asCArray<int> stackSize;
	stackSize.SetLength(func->byteCode.GetLength());
	memset(&stackSize[0], -1, stackSize.GetLength()*4);

	// Add the first instruction to the list of unchecked code 
	// paths and set the stack size at that instruction to variableSpace
	asCArray<asUINT> paths;
	paths.PushLast(0);
	stackSize[0] = func->variableSpace;

	// Go through each of the code paths
	for( asUINT p = 0; p < paths.GetLength(); ++p )
	{
		asUINT pos = paths[p];
		int currStackSize = stackSize[pos];
		
		asBYTE bc = *(asBYTE*)&func->byteCode[pos];
		if( bc == asBC_RET )
			continue;

		// Determine the change in stack size for this instruction
		int stackInc = asBCInfo[bc].stackInc;
		if( stackInc == 0xFFFF )
		{
			// Determine the true delta from the instruction arguments
			if( bc == asBC_CALL ||
			    bc == asBC_CALLSYS ||
				bc == asBC_CALLBND ||
				bc == asBC_ALLOC ||
				bc == asBC_CALLINTF ||
				bc == asBC_CallPtr )
			{
				asCScriptFunction *called = GetCalledFunction(func, pos);
				if( called )
				{
					stackInc = -called->GetSpaceNeededForArguments();
					if( called->objectType )
						stackInc -= AS_PTR_SIZE;
					if( called->DoesReturnOnStack() )
						stackInc -= AS_PTR_SIZE;
				}
				else
				{
					// It is an allocation for an object without a constructor
					asASSERT( bc == asBC_ALLOC );
					stackInc = -AS_PTR_SIZE;
				}
			}
		}
		
		currStackSize += stackInc;
		asASSERT( currStackSize >= 0 );

		if( currStackSize > largestStackUsed )
			largestStackUsed = currStackSize;

		if( bc == asBC_JMP )
		{
			// Find the label that we should jump to
			int offset = asBC_INTARG(&func->byteCode[pos]);
			pos += 2 + offset;

			// Add the destination as a new path
			if( stackSize[pos] == -1 )
			{
				stackSize[pos] = currStackSize;
				paths.PushLast(pos);
			}
			else
				asASSERT(stackSize[pos] == currStackSize);
			continue;
		}
		else if( bc == asBC_JZ    || bc == asBC_JNZ    ||
				 bc == asBC_JLowZ || bc == asBC_JLowNZ ||
				 bc == asBC_JS    || bc == asBC_JNS    ||
				 bc == asBC_JP    || bc == asBC_JNP )
		{
			// Find the label that is being jumped to
			int offset = asBC_INTARG(&func->byteCode[pos]);
			
			// Add both paths to the code paths
			pos += 2;
			if( stackSize[pos] == -1 )
			{
				stackSize[pos] = currStackSize;
				paths.PushLast(pos);
			}
			else
				asASSERT(stackSize[pos] == currStackSize);

			pos += offset;
			if( stackSize[pos] == -1 )
			{
				stackSize[pos] = currStackSize;
				paths.PushLast(pos);
			}
			else
				asASSERT(stackSize[pos] == currStackSize);

			continue;
		}
		else if( bc == asBC_JMPP )
		{
			pos++;
			
			// Add all subsequent JMP instructions to the path
			while( *(asBYTE*)&func->byteCode[pos] == asBC_JMP )
			{
				if( stackSize[pos] == -1 )
				{
					stackSize[pos] = currStackSize;
					paths.PushLast(pos);
				}
				else
					asASSERT(stackSize[pos] == currStackSize);
				pos += 2;
			}			
			continue;				
		}
		else
		{
			// Add next instruction to the paths
			pos += asBCTypeSize[asBCInfo[bc].type];
			if( stackSize[pos] == -1 )
			{
				stackSize[pos] = currStackSize;
				paths.PushLast(pos);
			}
			else
				asASSERT(stackSize[pos] == currStackSize);

			continue;
		}
	}

	func->stackNeeded = largestStackUsed;
}

void asCReader::CalculateAdjustmentByPos(asCScriptFunction *func)
{
	// Adjust the offset of all negative variables (parameters) as  
	// all pointers have been stored as having a size of 1 dword
	asUINT n;
	asCArray<int> adjustments;
	asUINT offset = 0;
	if( func->objectType )
	{
		adjustments.PushLast(offset);
		adjustments.PushLast(1-AS_PTR_SIZE);
		offset += 1;
	}
	if( func->DoesReturnOnStack() )
	{
		adjustments.PushLast(offset);
		adjustments.PushLast(1-AS_PTR_SIZE);
		offset += 1;
	}
	for( n = 0; n < func->parameterTypes.GetLength(); n++ )
	{
		if( func->parameterTypes[n].GetObjectType() ||
			func->parameterTypes[n].IsReference() )
		{
			adjustments.PushLast(offset);
			adjustments.PushLast(1-AS_PTR_SIZE);
			offset += 1;
		}
		else
		{
			asASSERT( func->parameterTypes[n].IsPrimitive() );
			offset += func->parameterTypes[n].GetSizeOnStackDWords();
		}
	}

	// Build look-up table with the adjustments for each stack position
	adjustNegativeStackByPos.SetLength(offset);
	memset(adjustNegativeStackByPos.AddressOf(), 0, adjustNegativeStackByPos.GetLength()*sizeof(int));
	for( n = 0; n < adjustments.GetLength(); n+=2 )
	{
		int pos    = adjustments[n];
		int adjust = adjustments[n+1];

		for( asUINT i = pos+1; i < adjustNegativeStackByPos.GetLength(); i++ )
			adjustNegativeStackByPos[i] += adjust;
	}

	// The bytecode has been stored as if all object variables take up only 1 dword. 
	// It is necessary to adjust to the size according to the current platform.
	adjustments.SetLength(0);
	int highestPos = 0;
	for( n = 0; n < func->objVariableTypes.GetLength(); n++ )
	{
		if( func->objVariableTypes[n] )
		{
			// Determine the size the variable currently occupies on the stack
			int size = AS_PTR_SIZE;
			if( (func->objVariableTypes[n]->GetFlags() & asOBJ_VALUE) &&
				n >= func->objVariablesOnHeap )
			{
				size = func->objVariableTypes[n]->GetSize();
				if( size < 4 ) 
					size = 1; 
				else 
					size /= 4;
			}

			// Check if type has a different size than stored
			if( size > 1 )
			{
				if( func->objVariablePos[n] > highestPos )
					highestPos = func->objVariablePos[n];

				adjustments.PushLast(func->objVariablePos[n]);
				adjustments.PushLast(size-1);
			}
		}
	}

	// Count position 0 too
	adjustByPos.SetLength(highestPos+1);
	memset(adjustByPos.AddressOf(), 0, adjustByPos.GetLength()*sizeof(int));

	// Build look-up table with the adjustments for each stack position
	for( n = 0; n < adjustments.GetLength(); n+=2 )
	{
		int pos    = adjustments[n];
		int adjust = adjustments[n+1];

		for( asUINT i = pos; i < adjustByPos.GetLength(); i++ )
			adjustByPos[i] += adjust;
	}
}

int asCReader::AdjustStackPosition(int pos)
{
	if( pos >= (int)adjustByPos.GetLength() )
	{
		// It can be higher for primitives allocated on top of highest object variable
		if( adjustByPos.GetLength() )
			pos += (short)adjustByPos[adjustByPos.GetLength()-1];
	}
	else if( pos >= 0 ) 
		pos += (short)adjustByPos[pos];
	else if( -pos >= (int)adjustNegativeStackByPos.GetLength() )
		error = true;
	else
		pos += (short)adjustNegativeStackByPos[-pos];

	return pos;
}

asCScriptFunction *asCReader::GetCalledFunction(asCScriptFunction *func, asDWORD programPos)
{
	asBYTE bc = *(asBYTE*)&func->byteCode[programPos];

	if( bc == asBC_CALL ||
		bc == asBC_CALLSYS ||
		bc == asBC_CALLINTF )
	{
		// Find the function from the function id in bytecode
		int funcId = asBC_INTARG(&func->byteCode[programPos]);
		return engine->scriptFunctions[funcId];
	}
	else if( bc == asBC_ALLOC )
	{
		// Find the function from the function id in the bytecode
		int funcId = asBC_INTARG(&func->byteCode[programPos+AS_PTR_SIZE]);
		return engine->scriptFunctions[funcId];
	}
	else if( bc == asBC_CALLBND )
	{
		// Find the function from the engine's bind array
		int funcId = asBC_INTARG(&func->byteCode[programPos]);
		return engine->importedFunctions[funcId&0xFFFF]->importedFunctionSignature;
	}
	else if( bc == asBC_CallPtr )
	{
		// Find the funcdef from the local variable
		int var = asBC_SWORDARG0(&func->byteCode[programPos]);
		for( asUINT v = 0; v < func->objVariablePos.GetLength(); v++ )
			if( func->objVariablePos[v] == var )
				return func->funcVariableTypes[v];
	}

	return 0;
}

int asCReader::AdjustGetOffset(int offset, asCScriptFunction *func, asDWORD programPos)
{
	// TODO: optimize: multiple instructions for the same function doesn't need to look for the function everytime
	//                 the function can remember where it found the function and check if the programPos is still valid

	// Get offset 0 doesn't need adjustment
	if( offset == 0 ) return 0;

	// Find out which function that will be called
	asCScriptFunction *calledFunc = 0;
	for( asUINT n = programPos; func->byteCode.GetLength(); )
	{
		asBYTE bc = *(asBYTE*)&func->byteCode[n];
		if( bc == asBC_CALL ||
			bc == asBC_CALLSYS ||
			bc == asBC_CALLINTF || 
			bc == asBC_ALLOC ||
			bc == asBC_CALLBND ||
			bc == asBC_CallPtr )
		{
			calledFunc = GetCalledFunction(func, n);
			break;
		}
		else if( bc == asBC_REFCPY ||
				 bc == asBC_COPY )
		{
			// In this case we know there is only 1 pointer on the stack above
			asASSERT( offset == 1 );
			return offset - (1 - AS_PTR_SIZE);
		}

		n += asBCTypeSize[asBCInfo[bc].type];
	}

	if( calledFunc == 0 )
	{
		// TODO: Report error
		error = true;
		return offset;
	}

	// Count the number of pointers pushed on the stack above the 
	// current offset, and then adjust the offset accordingly
	asUINT numPtrs = 0;
	int currOffset = 0;
	if( offset > currOffset && calledFunc->GetObjectType() )
	{
		numPtrs++;
		currOffset++;
	}
	if( offset > currOffset && calledFunc->DoesReturnOnStack() )
	{
		numPtrs++;
		currOffset++;
	}
	for( asUINT p = 0; p < calledFunc->parameterTypes.GetLength(); p++ )
	{
		if( offset <= currOffset ) break;

		if( calledFunc->parameterTypes[p].GetObjectType() ||
			calledFunc->parameterTypes[p].IsReference() )
		{
			numPtrs++;
			currOffset++;
		}
		else
		{
			asASSERT( calledFunc->parameterTypes[p].IsPrimitive() );
			currOffset += calledFunc->parameterTypes[p].GetSizeOnStackDWords();
		}
	}

	return offset - numPtrs * (1 - AS_PTR_SIZE);
}

int asCReader::FindTypeId(int idx)
{
	if( idx >= 0 && idx < (int)usedTypeIds.GetLength() )
		return usedTypeIds[idx];
	else
	{
		// TODO: Write to message callback
		error = true;
		return 0;
	}
}

asCObjectType *asCReader::FindObjectType(int idx)
{
	if( idx < 0 || idx >= (int)usedTypes.GetLength() )
	{
		// TODO: Write to message callback
		error = true;
		return 0;
	}

	return usedTypes[idx];
}

#ifndef AS_NO_COMPILER

asCWriter::asCWriter(asCModule* _module, asIBinaryStream* _stream, asCScriptEngine* _engine)
 : module(_module), stream(_stream), engine(_engine)
{
}

void asCWriter::WriteData(const void *data, asUINT size)
{
	asASSERT(size == 1 || size == 2 || size == 4 || size == 8);
#if defined(AS_BIG_ENDIAN)
	for( asUINT n = 0; n < size; n++ )
		stream->Write(((asBYTE*)data)+n, 1);
#else
	for( int n = size-1; n >= 0; n-- )
		stream->Write(((asBYTE*)data)+n, 1);
#endif
}

int asCWriter::Write() 
{
	unsigned long i, count;

	// Store everything in the same order that the builder parses scripts
	
	// Store enums
	count = (asUINT)module->enumTypes.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; i++ )
	{
		WriteObjectTypeDeclaration(module->enumTypes[i], 1);
		WriteObjectTypeDeclaration(module->enumTypes[i], 2);
	}

	// Store type declarations first
	count = (asUINT)module->classTypes.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; i++ )
	{
		// Store only the name of the class/interface types
		WriteObjectTypeDeclaration(module->classTypes[i], 1);
	}

	// Store func defs
	count = (asUINT)module->funcDefs.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; i++ )
	{
		WriteFunction(module->funcDefs[i]);
	}

	// Now store all interface methods
	count = (asUINT)module->classTypes.GetLength();
	for( i = 0; i < count; i++ )
	{
		if( module->classTypes[i]->IsInterface() )
			WriteObjectTypeDeclaration(module->classTypes[i], 2);
	}

	// Then store the class methods and behaviours
	for( i = 0; i < count; ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			WriteObjectTypeDeclaration(module->classTypes[i], 2);
	}

	// Then store the class properties
	for( i = 0; i < count; ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			WriteObjectTypeDeclaration(module->classTypes[i], 3);
	}

	// Store typedefs
	count = (asUINT)module->typeDefs.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; i++ )
	{
		WriteObjectTypeDeclaration(module->typeDefs[i], 1);
		WriteObjectTypeDeclaration(module->typeDefs[i], 2);
	}

	// scriptGlobals[]
	count = (asUINT)module->scriptGlobals.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; ++i ) 
		WriteGlobalProperty(module->scriptGlobals[i]);

	// scriptFunctions[]
	count = 0;
	for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
		if( module->scriptFunctions[i]->objectType == 0 )
			count++;
	WriteEncodedInt64(count);
	for( i = 0; i < module->scriptFunctions.GetLength(); ++i )
		if( module->scriptFunctions[i]->objectType == 0 )
			WriteFunction(module->scriptFunctions[i]);

	// globalFunctions[]
	count = (int)module->globalFunctions.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; i++ )
	{
		WriteFunction(module->globalFunctions[i]);
	}

	// bindInformations[]
	count = (asUINT)module->bindInformations.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; ++i )
	{
		WriteFunction(module->bindInformations[i]->importedFunctionSignature);
		WriteString(&module->bindInformations[i]->importFromModule);
	}

	// usedTypes[]
	count = (asUINT)usedTypes.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; ++i )
		WriteObjectType(usedTypes[i]);

	// usedTypeIds[]
	WriteUsedTypeIds();

	// usedFunctions[]
	WriteUsedFunctions();

	// usedGlobalProperties[]
	WriteUsedGlobalProps();

	// usedStringConstants[]
	WriteUsedStringConstants();

	// usedObjectProperties[]
	WriteUsedObjectProps();

	return asSUCCESS;
}

int asCWriter::FindStringConstantIndex(int id)
{
	asSMapNode<int,int> *cursor = 0;
	if (stringIdToIndexMap.MoveTo(&cursor, id))
		return cursor->value;

	usedStringConstants.PushLast(id);
	int index = int(usedStringConstants.GetLength() - 1);
	stringIdToIndexMap.Insert(id, index);
	return index;
}

void asCWriter::WriteUsedStringConstants()
{
	asUINT count = (asUINT)usedStringConstants.GetLength();
	WriteEncodedInt64(count);
	for( asUINT i = 0; i < count; ++i )
		WriteString(engine->stringConstants[usedStringConstants[i]]);
}

void asCWriter::WriteUsedFunctions()
{
	asUINT count = (asUINT)usedFunctions.GetLength();
	WriteEncodedInt64(count);

	for( asUINT n = 0; n < usedFunctions.GetLength(); n++ )
	{
		char c;

		// Write enough data to be able to uniquely identify the function upon load

		if( usedFunctions[n] )
		{
			// Is the function from the module or the application?
			c = usedFunctions[n]->module ? 'm' : 'a';
			WriteData(&c, 1);
			WriteFunctionSignature(usedFunctions[n]);
		}
		else
		{
			// null function pointer
			c = 'n'; 
			WriteData(&c, 1);
		}
	}
}

void asCWriter::WriteFunctionSignature(asCScriptFunction *func)
{
	asUINT i, count;

	WriteString(&func->name);
	WriteString(&func->nameSpace);
	WriteDataType(&func->returnType);

	count = (asUINT)func->parameterTypes.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; ++i ) 
		WriteDataType(&func->parameterTypes[i]);
	
	count = (asUINT)func->inOutFlags.GetLength();
	WriteEncodedInt64(count);
	for( i = 0; i < count; ++i )
		WriteEncodedInt64(func->inOutFlags[i]);

	WriteEncodedInt64(func->funcType);

	// Write the default args, from last to first
	count = 0;
	for( i = (asUINT)func->defaultArgs.GetLength(); i-- > 0; )
		if( func->defaultArgs[i] )
			count++;
	WriteEncodedInt64(count);
	for( i = (asUINT)func->defaultArgs.GetLength(); i-- > 0; )
		if( func->defaultArgs[i] )
			WriteString(func->defaultArgs[i]);

	WriteObjectType(func->objectType);

	if( func->objectType )
	{
		asBYTE b = 0;
		b += func->isReadOnly ? 1 : 0;
		b += func->isPrivate  ? 2 : 0;
		WriteData(&b, 1);
	}
}

void asCWriter::WriteFunction(asCScriptFunction* func) 
{
	char c;

	// If there is no function, then store a null char
	if( func == 0 )
	{
		c = '\0';
		WriteData(&c, 1);
		return;
	}

	// First check if the function has been saved already
	for( asUINT f = 0; f < savedFunctions.GetLength(); f++ )
	{
		if( savedFunctions[f] == func )
		{
			c = 'r';
			WriteData(&c, 1);
			WriteEncodedInt64(f);
			return;
		}
	}

	// Keep a reference to the function in the list
	savedFunctions.PushLast(func);

	c = 'f';
	WriteData(&c, 1);

	asUINT i, count;

	WriteFunctionSignature(func);

	if( func->funcType == asFUNC_SCRIPT )
	{
		// Calculate the adjustment by position lookup table
		CalculateAdjustmentByPos(func);

		WriteByteCode(func);

		asDWORD varSpace = AdjustStackPosition(func->variableSpace);
		WriteEncodedInt64(varSpace);

		count = (asUINT)func->objVariablePos.GetLength();
		WriteEncodedInt64(count);
		for( i = 0; i < count; ++i )
		{
			WriteObjectType(func->objVariableTypes[i]);
			// TODO: Only write this if the object type is the builtin function type
			WriteEncodedInt64(FindFunctionIndex(func->funcVariableTypes[i]));
			WriteEncodedInt64(AdjustStackPosition(func->objVariablePos[i]));
		}
		if( count > 0 )
			WriteEncodedInt64(func->objVariablesOnHeap);

		WriteEncodedInt64((asUINT)func->objVariableInfo.GetLength());
		for( i = 0; i < func->objVariableInfo.GetLength(); ++i )
		{
			// The program position must be adjusted to be in number of instructions
			WriteEncodedInt64(bytecodeNbrByPos[func->objVariableInfo[i].programPos]);
			WriteEncodedInt64(AdjustStackPosition(func->objVariableInfo[i].variableOffset)); // TODO: should be int
			WriteEncodedInt64(func->objVariableInfo[i].option);
		}

		// The program position (every even number) needs to be adjusted
		// to be in number of instructions instead of DWORD offset
		asUINT length = (asUINT)func->lineNumbers.GetLength();
		WriteEncodedInt64(length);
		for( i = 0; i < length; ++i )
		{
			if( (i & 1) == 0 )
				WriteEncodedInt64(bytecodeNbrByPos[func->lineNumbers[i]]);
			else
				WriteEncodedInt64(func->lineNumbers[i]);
		}

		WriteData(&func->isShared, 1);

		// Write the variable information
		WriteEncodedInt64((asUINT)func->variables.GetLength());
		for( i = 0; i < func->variables.GetLength(); i++ )
		{
			// The program position must be adjusted to be in number of instructions
			WriteEncodedInt64(bytecodeNbrByPos[func->variables[i]->declaredAtProgramPos]);
			// The stack position must be adjusted according to the pointer sizes
			WriteEncodedInt64(AdjustStackPosition(func->variables[i]->stackOffset));
			WriteString(&func->variables[i]->name);
			WriteDataType(&func->variables[i]->type);
		}
	}
	else if( func->funcType == asFUNC_VIRTUAL )
	{
		WriteEncodedInt64(func->vfTableIdx);
	}

	// Store script section name
	if( func->scriptSectionIdx >= 0 )
		WriteString(engine->scriptSectionNames[func->scriptSectionIdx]);
	else
	{
		char c = 0;
		WriteData(&c, 1);
	}
}

void asCWriter::WriteObjectTypeDeclaration(asCObjectType *ot, int phase)
{
	if( phase == 1 )
	{
		// name
		WriteString(&ot->name);
		// flags
		WriteData(&ot->flags, 4);

		// size
		if( (ot->flags & asOBJ_SCRIPT_OBJECT) && ot->size > 0 )
		{
			// The size for script objects may vary from platform to platform so 
			// only store 1 to diferentiate from interfaces that have size 0.
			WriteEncodedInt64(1); 
		}
		else
		{
			// Enums, typedefs, and interfaces have fixed sizes independently
			// of platform so it is safe to serialize the size directly.
			WriteEncodedInt64(ot->size);
		}

		// namespace
		WriteString(&ot->nameSpace);
	}
	else if( phase == 2 )
	{
		if( ot->flags & asOBJ_ENUM )
		{
			// enumValues[]
			int size = (int)ot->enumValues.GetLength();
			WriteEncodedInt64(size);

			for( int n = 0; n < size; n++ )
			{
				WriteString(&ot->enumValues[n]->name);
				WriteData(&ot->enumValues[n]->value, 4);
			}
		}
		else if( ot->flags & asOBJ_TYPEDEF )
		{
			eTokenType t = ot->templateSubType.GetTokenType();
			WriteEncodedInt64(t);
		}
		else
		{
			WriteObjectType(ot->derivedFrom);

			// interfaces[]
			int size = (asUINT)ot->interfaces.GetLength();
			WriteEncodedInt64(size);
			asUINT n;
			for( n = 0; n < ot->interfaces.GetLength(); n++ )
			{
				WriteObjectType(ot->interfaces[n]);
			}

			// behaviours
			if( !ot->IsInterface() && ot->flags != asOBJ_TYPEDEF && ot->flags != asOBJ_ENUM )
			{
				WriteFunction(engine->scriptFunctions[ot->beh.destruct]);
				size = (int)ot->beh.constructors.GetLength();
				WriteEncodedInt64(size);
				for( n = 0; n < ot->beh.constructors.GetLength(); n++ )
				{
					WriteFunction(engine->scriptFunctions[ot->beh.constructors[n]]);
					WriteFunction(engine->scriptFunctions[ot->beh.factories[n]]);
				}
			}

			// methods[]
			size = (int)ot->methods.GetLength();
			WriteEncodedInt64(size);
			for( n = 0; n < ot->methods.GetLength(); n++ )
			{
				WriteFunction(engine->scriptFunctions[ot->methods[n]]);
			}

			// virtualFunctionTable[]
			size = (int)ot->virtualFunctionTable.GetLength();
			WriteEncodedInt64(size);
			for( n = 0; n < (asUINT)size; n++ )
			{
				WriteFunction(ot->virtualFunctionTable[n]);
			}
		}
	}
	else if( phase == 3 )
	{
		// properties[]
		asUINT size = (asUINT)ot->properties.GetLength();
		WriteEncodedInt64(size);
		for( asUINT n = 0; n < ot->properties.GetLength(); n++ )
		{
			WriteObjectProperty(ot->properties[n]);
		}
	}
}

void asCWriter::WriteEncodedInt64(asINT64 i)
{
	asBYTE signBit = ( i & asINT64(1)<<63 ) ? 0x80 : 0;
	if( signBit ) i = -i;

	asBYTE b;
	if( i < (1<<6) )
	{
		b = (asBYTE)(signBit + i); WriteData(&b, 1);
	}
	else if( i < (1<<13) )
	{
		b = asBYTE(0x40 + signBit + (i >> 8)); WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                  WriteData(&b, 1);
	}
	else if( i < (1<<20) )
	{
		b = asBYTE(0x60 + signBit + (i >> 16)); WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);            WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                   WriteData(&b, 1);
	}
	else if( i < (1<<27) )
	{
		b = asBYTE(0x70 + signBit + (i >> 24)); WriteData(&b, 1);
		b = asBYTE((i >> 16) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);            WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                   WriteData(&b, 1);
	}
	else if( i < (asINT64(1)<<34) )
	{
		b = asBYTE(0x78 + signBit + (i >> 32)); WriteData(&b, 1);
		b = asBYTE((i >> 24) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 16) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);            WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                   WriteData(&b, 1);
	}
	else if( i < (asINT64(1)<<41) )
	{
		b = asBYTE(0x7C + signBit + (i >> 40)); WriteData(&b, 1);
		b = asBYTE((i >> 32) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 24) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 16) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);            WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                   WriteData(&b, 1);
	}
	else if( i < (asINT64(1)<<48) )
	{
		b = asBYTE(0x7E + signBit + (i >> 48)); WriteData(&b, 1);
		b = asBYTE((i >> 40) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 32) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 24) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 16) & 0xFF);           WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);            WriteData(&b, 1);
		b = asBYTE(i & 0xFF);                   WriteData(&b, 1);
	}
	else 
	{
		b = asBYTE(0x7F + signBit);   WriteData(&b, 1);
		b = asBYTE((i >> 56) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 48) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 40) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 32) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 24) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 16) & 0xFF); WriteData(&b, 1);
		b = asBYTE((i >> 8) & 0xFF);  WriteData(&b, 1);
		b = asBYTE(i & 0xFF);         WriteData(&b, 1);
	}
}

void asCWriter::WriteString(asCString* str) 
{
	// TODO: All strings should be stored in a separate section, and when
	//       they are used an offset into that section should be stored.
	//       This will make it unnecessary to store the extra byte to 
	//       identify new versus old strings.

	if( str->GetLength() == 0 )
	{
		char z = '\0';
		WriteData(&z, 1);
		return;
	}

	// First check if the string hasn't been saved already
	asSMapNode<asCStringPointer, int> *cursor = 0;
	if (stringToIdMap.MoveTo(&cursor, asCStringPointer(str)))
	{
		// Save a reference to the existing string
		char b = 'r';
		WriteData(&b, 1);
		WriteEncodedInt64(cursor->value);
		return;
	}

	// Save a new string
	char b = 'n';
	WriteData(&b, 1);

	asUINT len = (asUINT)str->GetLength();
	WriteEncodedInt64(len);
	stream->Write(str->AddressOf(), (asUINT)len);

	savedStrings.PushLast(*str);
	stringToIdMap.Insert(asCStringPointer(str), int(savedStrings.GetLength()) - 1);
}

void asCWriter::WriteGlobalProperty(asCGlobalProperty* prop) 
{
	// TODO: We might be able to avoid storing the name and type of the global 
	//       properties twice if we merge this with the WriteUsedGlobalProperties. 
	WriteString(&prop->name);
	WriteString(&prop->nameSpace);
	WriteDataType(&prop->type);

	// Store the initialization function
	if( prop->GetInitFunc() )
	{
		bool f = true;
		WriteData(&f, 1);

		WriteFunction(prop->GetInitFunc());
	}
	else
	{
		bool f = false;
		WriteData(&f, 1);
	}
}

void asCWriter::WriteObjectProperty(asCObjectProperty* prop) 
{
	WriteString(&prop->name);
	WriteDataType(&prop->type);
	WriteData(&prop->isPrivate, 1);
}

void asCWriter::WriteDataType(const asCDataType *dt) 
{
	// First check if the datatype has already been saved
	for( asUINT n = 0; n < savedDataTypes.GetLength(); n++ )
	{
		if( *dt == savedDataTypes[n] )
		{
			asUINT c = 0;
			WriteEncodedInt64(c);
			WriteEncodedInt64(n);
			return;
		}
	}

	// Save the new datatype
	savedDataTypes.PushLast(*dt);

	bool b;
	int t = dt->GetTokenType();
	WriteEncodedInt64(t);
	if( t == ttIdentifier )
	{
		WriteObjectType(dt->GetObjectType());
		b = dt->IsObjectHandle();
		WriteData(&b, 1);
		b = dt->IsHandleToConst();
		WriteData(&b, 1);
	}
	b = dt->IsReference();
	WriteData(&b, 1);
	b = dt->IsReadOnly();
	WriteData(&b, 1);

	if( t == ttIdentifier && dt->GetObjectType()->name == "_builtin_function_" )
	{
		WriteFunctionSignature(dt->GetFuncDef());
	}
}

void asCWriter::WriteObjectType(asCObjectType* ot) 
{
	char ch;

	// Only write the object type name
	if( ot )
	{
		// Check for template instances/specializations
		if( ot->templateSubType.GetTokenType() != ttUnrecognizedToken )
		{
			ch = 'a';
			WriteData(&ch, 1);
			WriteString(&ot->name);

			if( ot->templateSubType.IsObject() || ot->templateSubType.IsEnumType() )
			{
				ch = 's';
				WriteData(&ch, 1);
				WriteObjectType(ot->templateSubType.GetObjectType());

				if( ot->templateSubType.IsObjectHandle() )
					ch = 'h';
				else
					ch = 'o';
				WriteData(&ch, 1);
			}
			else
			{
				ch = 't';
				WriteData(&ch, 1);
				eTokenType t = ot->templateSubType.GetTokenType();
				WriteEncodedInt64(t);
			}
		}
		else if( ot->flags & asOBJ_TEMPLATE_SUBTYPE )
		{
			ch = 's';
			WriteData(&ch, 1);
			WriteString(&ot->name);
		}
		else
		{
			ch = 'o';
			WriteData(&ch, 1);
			WriteString(&ot->name);
			WriteString(&ot->nameSpace);
		}
	}
	else
	{
		ch = '\0';
		WriteData(&ch, 1);
	}
}

void asCWriter::CalculateAdjustmentByPos(asCScriptFunction *func)
{
	// Adjust the offset of all negative variables (parameters) so all pointers will have a size of 1 dword
	asUINT n;
	asCArray<int> adjustments;
	asUINT offset = 0;
	if( func->objectType )
	{
		adjustments.PushLast(offset);
		adjustments.PushLast(1-AS_PTR_SIZE);
		offset += AS_PTR_SIZE;
	}
	if( func->DoesReturnOnStack() )
	{
		adjustments.PushLast(offset);
		adjustments.PushLast(1-AS_PTR_SIZE);
		offset += AS_PTR_SIZE;
	}
	for( n = 0; n < func->parameterTypes.GetLength(); n++ )
	{
		if( func->parameterTypes[n].GetObjectType() ||
			func->parameterTypes[n].IsReference() )
		{
			adjustments.PushLast(offset);
			adjustments.PushLast(1-AS_PTR_SIZE);
			offset += AS_PTR_SIZE;
		}
		else
		{
			asASSERT( func->parameterTypes[n].IsPrimitive() );
			offset += func->parameterTypes[n].GetSizeOnStackDWords();
		}
	}

	// Build look-up table with the adjustments for each stack position
	adjustNegativeStackByPos.SetLength(offset);
	memset(adjustNegativeStackByPos.AddressOf(), 0, adjustNegativeStackByPos.GetLength()*sizeof(int));
	for( n = 0; n < adjustments.GetLength(); n+=2 )
	{
		int pos    = adjustments[n];
		int adjust = adjustments[n+1];

		for( asUINT i = pos+1; i < adjustNegativeStackByPos.GetLength(); i++ )
			adjustNegativeStackByPos[i] += adjust;
	}

	// Adjust the offset of all positive variables so that all object types and handles have a size of 1 dword
	// This is similar to how the adjustment is done in the asCReader::TranslateFunction, only the reverse
	adjustments.SetLength(0);
	for( n = 0; n < func->objVariableTypes.GetLength(); n++ )
	{
		if( func->objVariableTypes[n] )
		{
			// Determine the size the variable currently occupies on the stack
			int size = AS_PTR_SIZE;
			if( (func->objVariableTypes[n]->GetFlags() & asOBJ_VALUE) &&
				n >= func->objVariablesOnHeap )
			{
				size = func->objVariableTypes[n]->GetSize();
				if( size < 4 ) 
					size = 1; 
				else 
					size /= 4;
			}

			// If larger than 1 dword, adjust the offsets accordingly
			if( size > 1 )
			{
				// How much needs to be adjusted?
				adjustments.PushLast(func->objVariablePos[n]);
				adjustments.PushLast(-(size-1));
			}
		}
	}

	// Build look-up table with the adjustments for each stack position
	adjustStackByPos.SetLength(func->stackNeeded);
	memset(adjustStackByPos.AddressOf(), 0, adjustStackByPos.GetLength()*sizeof(int));
	for( n = 0; n < adjustments.GetLength(); n+=2 )
	{
		int pos    = adjustments[n];
		int adjust = adjustments[n+1];

		for( asUINT i = pos; i < adjustStackByPos.GetLength(); i++ )
			adjustStackByPos[i] += adjust;
	}

	// Compute the sequence number of each bytecode instruction in order to update the jump offsets
	asUINT length = func->byteCode.GetLength();
	asDWORD *bc = func->byteCode.AddressOf();
	bytecodeNbrByPos.SetLength(length);
	asUINT num;
	for( offset = 0, num = 0; offset < length; )
	{
		bytecodeNbrByPos[offset] = num;
		offset += asBCTypeSize[asBCInfo[*(asBYTE*)(bc+offset)].type];
		num++;
	}
	// The last instruction is always a BC_RET. This make it possible to query 
	// the number of instructions by checking the last entry in bytecodeNbrByPos
	asASSERT(*(asBYTE*)(bc+length-1) == asBC_RET);
}

int asCWriter::AdjustStackPosition(int pos)
{
	if( pos >= (int)adjustStackByPos.GetLength() )
	{
		// This happens for example if the function only have temporary variables
		// The adjustByPos can also be empty if the function doesn't have any variables at all, but receive a handle by parameter
		if( adjustStackByPos.GetLength() > 0 )
			pos += adjustStackByPos[adjustStackByPos.GetLength()-1];
	}
	else if( pos >= 0 )
		pos += adjustStackByPos[pos];
	else
	{
		asASSERT( -pos < (int)adjustNegativeStackByPos.GetLength() );
		pos -= (short)adjustNegativeStackByPos[-pos];
	}

	return pos;
}

int asCWriter::AdjustGetOffset(int offset, asCScriptFunction *func, asDWORD programPos)
{
	// TODO: optimize: multiple instructions for the same function doesn't need to look for the function everytime
	//                 the function can remember where it found the function and check if the programPos is still valid

	// Get offset 0 doesn't need adjustment
	if( offset == 0 ) return 0;

	// Find out which function that will be called
	asCScriptFunction *calledFunc = 0;
	for( asUINT n = programPos; n < func->byteCode.GetLength(); )
	{
		asBYTE bc = *(asBYTE*)&func->byteCode[n];
		if( bc == asBC_CALL ||
			bc == asBC_CALLSYS ||
			bc == asBC_CALLINTF )
		{
			// Find the function from the function id in bytecode
			int funcId = asBC_INTARG(&func->byteCode[n]);
			calledFunc = engine->scriptFunctions[funcId];
			break;
		}
		else if( bc == asBC_ALLOC )
		{
			// Find the function from the function id in the bytecode
			int funcId = asBC_INTARG(&func->byteCode[n+AS_PTR_SIZE]);
			calledFunc = engine->scriptFunctions[funcId];
			break;
		}
		else if( bc == asBC_CALLBND )
		{
			// Find the function from the engine's bind array
			int funcId = asBC_INTARG(&func->byteCode[n]);
			calledFunc = engine->importedFunctions[funcId&0xFFFF]->importedFunctionSignature;
			break;
		}
		else if( bc == asBC_CallPtr )
		{
			// Find the funcdef from the local variable
			int var = asBC_SWORDARG0(&func->byteCode[n]);
			for( asUINT v = 0; v < func->objVariablePos.GetLength(); v++ )
				if( func->objVariablePos[v] == var )
				{
					calledFunc = func->funcVariableTypes[v];
					break;
				}
			break;
		}
		else if( bc == asBC_REFCPY ||
				 bc == asBC_COPY )
		{
			// In this case we know there is only 1 pointer on the stack above
			asASSERT( offset == AS_PTR_SIZE );
			return offset + (1 - AS_PTR_SIZE);
		}

		n += asBCTypeSize[asBCInfo[bc].type];
	}

	asASSERT( calledFunc );

	// Count the number of pointers pushed on the stack above the 
	// current offset, and then adjust the offset accordingly
	asUINT numPtrs = 0;
	int currOffset = 0;
	if( offset > currOffset && calledFunc->GetObjectType() )
	{
		numPtrs++;
		currOffset += AS_PTR_SIZE;
	}
	if( offset > currOffset && calledFunc->DoesReturnOnStack() )
	{
		numPtrs++;
		currOffset += AS_PTR_SIZE;
	}
	for( asUINT p = 0; p < calledFunc->parameterTypes.GetLength(); p++ )
	{
		if( offset <= currOffset ) break;

		if( calledFunc->parameterTypes[p].GetObjectType() ||
			calledFunc->parameterTypes[p].IsReference() )
		{
			numPtrs++;
			currOffset += AS_PTR_SIZE;
		}
		else
		{
			asASSERT( calledFunc->parameterTypes[p].IsPrimitive() );
			currOffset += calledFunc->parameterTypes[p].GetSizeOnStackDWords();
		}
	}

	// The get offset must match one of the parameter offsets
	asASSERT( offset == currOffset );
	
	return offset + numPtrs * (1 - AS_PTR_SIZE);
}

void asCWriter::WriteByteCode(asCScriptFunction *func)
{
	asDWORD *bc   = func->byteCode.AddressOf();
	asUINT length = func->byteCode.GetLength();

	// The length cannot be stored, because it is platform dependent, 
	// instead we store the number of instructions
	asUINT count = bytecodeNbrByPos[bytecodeNbrByPos.GetLength()-1] + 1;
	WriteEncodedInt64(count);

	asDWORD *startBC = bc;
	while( length )
	{
		asDWORD tmp[4]; // The biggest instructions take up 4 DWORDs
		asDWORD c = *(asBYTE*)bc;

		// Copy the instruction to a temp buffer so we can work on it before saving
		memcpy(tmp, bc, asBCTypeSize[asBCInfo[c].type]*sizeof(asDWORD));

		if( c == asBC_ALLOC ) // PTR_DW_ARG
		{
			// Translate the object type 
			asCObjectType *ot = *(asCObjectType**)(tmp+1);
			*(int*)(tmp+1) = FindObjectTypeIdx(ot);

			// Translate the constructor func id, if it is a script class
			if( ot->flags & asOBJ_SCRIPT_OBJECT )
				*(int*)&tmp[1+AS_PTR_SIZE] = FindFunctionIndex(engine->scriptFunctions[*(int*)&tmp[1+AS_PTR_SIZE]]);
		}
		else if( c == asBC_FREE    || // wW_PTR_ARG
			     c == asBC_REFCPY  || // PTR_ARG
				 c == asBC_RefCpyV || // wW_PTR_ARG
				 c == asBC_OBJTYPE )  // PTR_ARG
		{
			// Translate object type pointers into indices
			*(int*)(tmp+1) = FindObjectTypeIdx(*(asCObjectType**)(tmp+1));
		}
		else if( c == asBC_JitEntry ) // PTR_ARG
		{
			// We don't store the JIT argument
			*(asPWORD*)(tmp+1) = 0;
		}
		else if( c == asBC_TYPEID || // DW_ARG
			     c == asBC_Cast )    // DW_ARG
		{
			// Translate type ids into indices
			*(int*)(tmp+1) = FindTypeIdIdx(*(int*)(tmp+1));
		}
		else if( c == asBC_ADDSi ||      // W_DW_ARG
			     c == asBC_LoadThisR )   // W_DW_ARG	 
		{
			// Translate property offsets into indices
			*(((short*)tmp)+1) = (short)FindObjectPropIndex(*(((short*)tmp)+1), *(int*)(tmp+1));

			// Translate type ids into indices
			*(int*)(tmp+1) = FindTypeIdIdx(*(int*)(tmp+1));
		}
		else if( c == asBC_LoadRObjR ||    // rW_W_DW_ARG
			     c == asBC_LoadVObjR )     // rW_W_DW_ARG
		{
			// Translate property offsets into indices
			*(((short*)tmp)+2) = (short)FindObjectPropIndex(*(((short*)tmp)+2), *(int*)(tmp+2));

			// Translate type ids into indices
			*(int*)(tmp+2) = FindTypeIdIdx(*(int*)(tmp+2));
		}
		else if( c == asBC_COPY )        // W_DW_ARG
		{
			// Translate type ids into indices
			*(int*)(tmp+1) = FindTypeIdIdx(*(int*)(tmp+1));

			// Update the WORDARG0 to 0, as this will be recalculated on the target platform
			asBC_WORDARG0(tmp) = 0;
		}
		else if( c == asBC_RET ) // W_ARG
		{
			// Save with arg 0, as this will be recalculated on the target platform
			asBC_WORDARG0(tmp) = 0;
		}
		else if( c == asBC_CALL ||     // DW_ARG
				 c == asBC_CALLINTF || // DW_ARG
				 c == asBC_CALLSYS )   // DW_ARG
		{
			// Translate the function id
			*(int*)(tmp+1) = FindFunctionIndex(engine->scriptFunctions[*(int*)(tmp+1)]);
		}
		else if( c == asBC_FuncPtr ) // PTR_ARG
		{
			// Translate the function pointer
			*(asPWORD*)(tmp+1) = FindFunctionIndex(*(asCScriptFunction**)(tmp+1));
		}
		else if( c == asBC_STR ) // W_ARG
		{
			// Translate the string constant id
			asWORD *arg = ((asWORD*)tmp)+1;
			*arg = (asWORD)FindStringConstantIndex(*arg);
		}
		else if( c == asBC_CALLBND ) // DW_ARG
		{
			// Translate the function id
			int funcId = tmp[1];
			for( asUINT n = 0; n < module->bindInformations.GetLength(); n++ )
				if( module->bindInformations[n]->importedFunctionSignature->id == funcId )
				{
					funcId = n;
					break;
				}

			tmp[1] = funcId;
		}
		else if( c == asBC_PGA      || // PTR_ARG
			     c == asBC_PshGPtr  || // PTR_ARG 
			     c == asBC_LDG      || // PTR_ARG
				 c == asBC_PshG4    || // PTR_ARG
				 c == asBC_LdGRdR4  || // wW_PTR_ARG
				 c == asBC_CpyGtoV4 || // wW_PTR_ARG
				 c == asBC_CpyVtoG4 || // rW_PTR_ARG
				 c == asBC_SetG4    )  // PTR_DW_ARG
		{
			// Translate global variable pointers into indices
			*(int*)(tmp+1) = FindGlobalPropPtrIndex(*(void**)(tmp+1));
		}
		else if( c == asBC_JMP    ||	// DW_ARG
			     c == asBC_JZ     ||
				 c == asBC_JNZ    ||
				 c == asBC_JLowZ  ||
				 c == asBC_JLowNZ ||
				 c == asBC_JS     ||
				 c == asBC_JNS    ||
				 c == asBC_JP     ||
				 c == asBC_JNP    ) // The JMPP instruction doesn't need modification
		{
			// Get the DWORD offset from arg
			int offset = *(int*)(tmp+1);

			// Determine instruction number for next instruction and destination
			int bcSeqNum = bytecodeNbrByPos[bc - startBC] + 1;
			asDWORD *targetBC = bc + 2 + offset;
			int targetBcSeqNum = bytecodeNbrByPos[targetBC - startBC];

			// Set the offset in number of instructions
			*(int*)(tmp+1) = targetBcSeqNum - bcSeqNum;
		}
		else if( c == asBC_GETOBJ ||    // W_ARG
			     c == asBC_GETOBJREF ||
				 c == asBC_GETREF )
		{
			// Adjust the offset according to the function call that comes after
			asBC_WORDARG0(tmp) = (asWORD)AdjustGetOffset(asBC_WORDARG0(tmp), func, bc - startBC);
		}

		// Adjust the variable offsets
		switch( asBCInfo[c].type )
		{
		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_QW_ARG:
		case asBCTYPE_rW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_wW_W_ARG:
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				asBC_SWORDARG0(tmp) = (short)AdjustStackPosition(asBC_SWORDARG0(tmp));
			}
			break;

		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_rW_ARG:
			{
				asBC_SWORDARG0(tmp) = (short)AdjustStackPosition(asBC_SWORDARG0(tmp));
				asBC_SWORDARG1(tmp) = (short)AdjustStackPosition(asBC_SWORDARG1(tmp));
			}
			break;

		case asBCTYPE_wW_rW_rW_ARG:
			{
				asBC_SWORDARG0(tmp) = (short)AdjustStackPosition(asBC_SWORDARG0(tmp));
				asBC_SWORDARG1(tmp) = (short)AdjustStackPosition(asBC_SWORDARG1(tmp));
				asBC_SWORDARG2(tmp) = (short)AdjustStackPosition(asBC_SWORDARG2(tmp));
			}
			break;

		default:
			// The other types don't treat variables so won't be modified
			break;
		}

		// TODO: bytecode: Must make sure that floats and doubles are always stored the same way regardless of platform. 
		//                 Some platforms may not use the IEEE 754 standard, in which case it is necessary to encode the values
		
		// Now store the instruction in the smallest possible way
		switch( asBCInfo[c].type )
		{
		case asBCTYPE_NO_ARG:
			{
				// Just write 1 byte
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);
			}
			break;
		case asBCTYPE_W_ARG:
		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);
				
				// Write the argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);
			}
			break;
		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_W_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the word argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);

				// Write the dword argument
				WriteEncodedInt64((int)tmp[1]);
			}
			break;
		case asBCTYPE_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the argument
				WriteEncodedInt64((int)tmp[1]);
			}
			break;
		case asBCTYPE_DW_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the dword argument
				WriteEncodedInt64((int)tmp[1]);

				// Write the dword argument
				WriteEncodedInt64((int)tmp[2]);
			}
			break;
		case asBCTYPE_wW_rW_rW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the first argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);

				// Write the second argument
				w = *(((short*)tmp)+2);
				WriteEncodedInt64(w);

				// Write the third argument
				w = *(((short*)tmp)+3);
				WriteEncodedInt64(w);
			}
			break;
		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_rW_rW_ARG:
		case asBCTYPE_wW_W_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the first argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);

				// Write the second argument
				w = *(((short*)tmp)+2);
				WriteEncodedInt64(w);
			}
			break;
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the first argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);

				// Write the second argument
				w = *(((short*)tmp)+2);
				WriteEncodedInt64(w);

				// Write the third argument
				int dw = tmp[2];
				WriteEncodedInt64(dw);
			}
			break;
		case asBCTYPE_QW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the argument
				asQWORD qw = *(asQWORD*)&tmp[1];
				WriteEncodedInt64(qw);
			}
			break;
		case asBCTYPE_QW_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the argument
				// TODO: This could be encoded as an int to decrease the size
				asQWORD qw = *(asQWORD*)&tmp[1];
				WriteEncodedInt64(qw);

				// Write the second argument
				// TODO: This could be encoded as an int to decrease the size
				int dw = tmp[3];
				WriteEncodedInt64(dw);
			}
			break;
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_wW_QW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WriteData(&b, 1);

				// Write the first argument
				short w = *(((short*)tmp)+1);
				WriteEncodedInt64(w);

				// Write the argument
				// TODO: This could be encoded as an int to decrease the size
				asQWORD qw = *(asQWORD*)&tmp[1];
				WriteEncodedInt64(qw);
			}
			break;
		default:
			{
				// This should never happen
				asASSERT(false);

				// Store the bc as is
				for( int n = 0; n < asBCTypeSize[asBCInfo[c].type]; n++ )
					WriteData(&tmp[n], 4);
			}
		}

		// Move to the next instruction
		bc += asBCTypeSize[asBCInfo[c].type];
		length -= asBCTypeSize[asBCInfo[c].type];
	}
}

void asCWriter::WriteUsedTypeIds()
{
	asUINT count = (asUINT)usedTypeIds.GetLength();
	WriteEncodedInt64(count);
	for( asUINT n = 0; n < count; n++ )
	{
		asCDataType dt = engine->GetDataTypeFromTypeId(usedTypeIds[n]);
		WriteDataType(&dt);
	}
}

int asCWriter::FindGlobalPropPtrIndex(void *ptr)
{
	int i = usedGlobalProperties.IndexOf(ptr);
	if( i >= 0 ) return i;

	usedGlobalProperties.PushLast(ptr);
	return (int)usedGlobalProperties.GetLength()-1;
}

void asCWriter::WriteUsedGlobalProps()
{
	int c = (int)usedGlobalProperties.GetLength();
	WriteEncodedInt64(c);

	for( int n = 0; n < c; n++ )
	{
		asPWORD *p = (asPWORD*)usedGlobalProperties[n];
		
		// First search for the global in the module
		char moduleProp = 0;
		asCGlobalProperty *prop = 0;
		for( int i = 0; i < (signed)module->scriptGlobals.GetLength(); i++ )
		{
			if( p == module->scriptGlobals[i]->GetAddressOfValue() )
			{
				prop = module->scriptGlobals[i];
				moduleProp = 1;
				break;
			}
		}

		// If it is not in the module, it must be an application registered property
		if( !prop )
		{
			for( int i = 0; i < (signed)engine->registeredGlobalProps.GetLength(); i++ )
			{
				if( engine->registeredGlobalProps[i]->GetAddressOfValue() == p )
				{
					prop = engine->registeredGlobalProps[i];
					break;
				}
			}
		}

		asASSERT(prop);

		// Store the name and type of the property so we can find it again on loading
		WriteString(&prop->name);
		WriteString(&prop->nameSpace);
		WriteDataType(&prop->type);

		// Also store whether the property is a module property or a registered property
		WriteData(&moduleProp, 1);
	}
}

void asCWriter::WriteUsedObjectProps()
{
	int c = (int)usedObjectProperties.GetLength();
	WriteEncodedInt64(c);

	for( asUINT n = 0; n < usedObjectProperties.GetLength(); n++ )
	{
		asCObjectType *objType = usedObjectProperties[n].objType;
		WriteObjectType(objType);

		// Find the property name
		for( asUINT p = 0; p < objType->properties.GetLength(); p++ )
		{
			if( objType->properties[p]->byteOffset == usedObjectProperties[n].offset )
			{
				WriteString(&objType->properties[p]->name);
				break;
			}
		}
	}
}

int asCWriter::FindObjectPropIndex(short offset, int typeId)
{
	asCObjectType *objType = engine->GetObjectTypeFromTypeId(typeId);
	for( asUINT n = 0; n < usedObjectProperties.GetLength(); n++ )
	{
		if( usedObjectProperties[n].objType == objType &&
			usedObjectProperties[n].offset  == offset )
			return n;
	}

	SObjProp prop = {objType, offset};
	usedObjectProperties.PushLast(prop);
	return (int)usedObjectProperties.GetLength() - 1;
}

int asCWriter::FindFunctionIndex(asCScriptFunction *func)
{
	for( asUINT n = 0; n < usedFunctions.GetLength(); n++ )
	{
		if( usedFunctions[n] == func )
			return n;
	}

	usedFunctions.PushLast(func);
	return (int)usedFunctions.GetLength() - 1;
}

int asCWriter::FindTypeIdIdx(int typeId)
{
	asUINT n;
	for( n = 0; n < usedTypeIds.GetLength(); n++ )
	{
		if( usedTypeIds[n] == typeId )
			return n;
	}

	usedTypeIds.PushLast(typeId);
	return (int)usedTypeIds.GetLength() - 1;
}

int asCWriter::FindObjectTypeIdx(asCObjectType *obj)
{
	asUINT n;
	for( n = 0; n < usedTypes.GetLength(); n++ )
	{
		if( usedTypes[n] == obj )
			return n;
	}

	usedTypes.PushLast(obj);
	return (int)usedTypes.GetLength() - 1;
}

#endif // AS_NO_COMPILER

END_AS_NAMESPACE

