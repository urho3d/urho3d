/*
   AngelCode Scripting Library
   Copyright (c) 2003-2011 Andreas Jonsson

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

BEGIN_AS_NAMESPACE

#define WRITE_NUM(N) WriteData(&(N), sizeof(N))
#define READ_NUM(N) ReadData(&(N), sizeof(N))

asCRestore::asCRestore(asCModule* _module, asIBinaryStream* _stream, asCScriptEngine* _engine)
 : module(_module), stream(_stream), engine(_engine)
{
	error = false;
}

void asCRestore::WriteData(const void *data, asUINT size)
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

void asCRestore::ReadData(void *data, asUINT size)
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

int asCRestore::Save() 
{
	unsigned long i, count;

	// TODO: The first thing the code needs to do is build a list of the 
	//       types that are used, so that the function signatures, etc can
	//       be encoded in a small way.
	// 
	//       If only a few types are used, then maybe one byte is enough.
	//       By using a scheme similar to UTF8 I can support a high number
	//       of types without sacrifizing space.

	// Store everything in the same order that the builder parses scripts
	
	// Store enums
	count = (asUINT)module->enumTypes.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; i++ )
	{
		WriteObjectTypeDeclaration(module->enumTypes[i], 1);
		WriteObjectTypeDeclaration(module->enumTypes[i], 2);
	}

	// Store type declarations first
	count = (asUINT)module->classTypes.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; i++ )
	{
		// Store only the name of the class/interface types
		WriteObjectTypeDeclaration(module->classTypes[i], 1);
	}

	// Store func defs
	count = (asUINT)module->funcDefs.GetLength();
	WriteEncodedUInt(count);
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
	WriteEncodedUInt(count);
	for( i = 0; i < count; i++ )
	{
		WriteObjectTypeDeclaration(module->typeDefs[i], 1);
		WriteObjectTypeDeclaration(module->typeDefs[i], 2);
	}

	// scriptGlobals[]
	count = (asUINT)module->scriptGlobals.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; ++i ) 
		WriteGlobalProperty(module->scriptGlobals[i]);

	// scriptFunctions[]
	count = 0;
	for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
		if( module->scriptFunctions[i]->objectType == 0 )
			count++;
	WriteEncodedUInt(count);
	for( i = 0; i < module->scriptFunctions.GetLength(); ++i )
		if( module->scriptFunctions[i]->objectType == 0 )
			WriteFunction(module->scriptFunctions[i]);

	// globalFunctions[]
	count = (int)module->globalFunctions.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; i++ )
	{
		WriteFunction(module->globalFunctions[i]);
	}

	// bindInformations[]
	count = (asUINT)module->bindInformations.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; ++i )
	{
		WriteFunction(module->bindInformations[i]->importedFunctionSignature);
		WriteString(&module->bindInformations[i]->importFromModule);
	}

	// usedTypes[]
	asUINT numValueTypes = 0;
	count = (asUINT)usedTypes.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; ++i )
	{
		if( usedTypes[i]->flags & asOBJ_VALUE )
			numValueTypes++;

		WriteObjectType(usedTypes[i]);
	}

	// Write the size of value types so the code can be adjusted if they are not the same when reloading the code
	WriteEncodedUInt(numValueTypes);
	for( i = 0; i < count; i++ )
	{
		if( usedTypes[i]->flags & asOBJ_VALUE )
		{
			WriteEncodedUInt(i);
			WriteEncodedUInt(usedTypes[i]->GetSize());
		}
	}

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

int asCRestore::Restore() 
{
	// Before starting the load, make sure that 
	// any existing resources have been freed
	module->InternalReset();

	unsigned long i, count;

	asCScriptFunction* func;

	// Read enums
	count = ReadEncodedUInt();
	module->enumTypes.Allocate(count, 0);
	for( i = 0; i < count; i++ )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		ReadObjectTypeDeclaration(ot, 1);
		engine->classTypes.PushLast(ot);
		module->enumTypes.PushLast(ot);
		ot->AddRef();
		ReadObjectTypeDeclaration(ot, 2);
	}

	// classTypes[]
	// First restore the structure names, then the properties
	count = ReadEncodedUInt();
	module->classTypes.Allocate(count, 0);
	for( i = 0; i < count; ++i )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		ReadObjectTypeDeclaration(ot, 1);
		engine->classTypes.PushLast(ot);
		module->classTypes.PushLast(ot);
		ot->AddRef();

		// Add script classes to the GC
		if( (ot->GetFlags() & asOBJ_SCRIPT_OBJECT) && ot->GetSize() > 0 )
			engine->gc.AddScriptObjectToGC(ot, &engine->objectTypeBehaviours);
	}

	// Read func defs
	count = ReadEncodedUInt();
	module->funcDefs.Allocate(count, 0);
	for( i = 0; i < count; i++ )
	{
		asCScriptFunction *func = ReadFunction(false, true);
		module->funcDefs.PushLast(func);
	}

	// Read interface methods
	for( i = 0; i < module->classTypes.GetLength(); i++ )
	{
		if( module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 2);
	}

	asCArray<void*> substitutions;
	module->ResolveInterfaceIds(&substitutions);

	// The above method may have replaced the interface object types
	// so we must updated this in the savedDataTypes if it is there.
	// All the interface methods were also substituted so the 
	// savedFunctions must also be updated
	for( i = 0; i < substitutions.GetLength(); i += 2 )
	{
		for( asUINT d = 0; d < savedDataTypes.GetLength(); d++ )
		{
			if( savedDataTypes[d].GetObjectType() == substitutions[i] )
				savedDataTypes[d].SetObjectType(reinterpret_cast<asCObjectType*>(substitutions[i+1]));
		}

		for( asUINT f = 0; f < savedFunctions.GetLength(); f++ )
		{
			if( savedFunctions[f] == substitutions[i] )
				savedFunctions[f] = reinterpret_cast<asCScriptFunction*>(substitutions[i+1]);
		}
	}

	// Read class methods and behaviours
	for( i = 0; i < module->classTypes.GetLength(); ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 2);
	}

	// Read class properties
	for( i = 0; i < module->classTypes.GetLength(); ++i )
	{
		if( !module->classTypes[i]->IsInterface() )
			ReadObjectTypeDeclaration(module->classTypes[i], 3);
	}

	// Read typedefs
	count = ReadEncodedUInt();
	module->typeDefs.Allocate(count, 0);
	for( i = 0; i < count; i++ )
	{
		asCObjectType *ot = asNEW(asCObjectType)(engine);
		ReadObjectTypeDeclaration(ot, 1);
		engine->classTypes.PushLast(ot);
		module->typeDefs.PushLast(ot);
		ot->AddRef();
		ReadObjectTypeDeclaration(ot, 2);
	}

	// scriptGlobals[]
	count = ReadEncodedUInt();
	module->scriptGlobals.Allocate(count, 0);
	for( i = 0; i < count; ++i ) 
	{
		ReadGlobalProperty();
	}

	// scriptFunctions[]
	count = ReadEncodedUInt();
	for( i = 0; i < count; ++i ) 
	{
		func = ReadFunction();
	}

	// globalFunctions[]
	count = ReadEncodedUInt();
	for( i = 0; i < count; ++i )
	{
		func = ReadFunction(false, false);
		module->globalFunctions.PushLast(func);
		func->AddRef();
	}

	// bindInformations[]
	count = ReadEncodedUInt();
	module->bindInformations.SetLength(count);
	for( i = 0; i < count; ++i )
	{
		sBindInfo *info = asNEW(sBindInfo);
		info->importedFunctionSignature = ReadFunction(false, false);
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
		module->bindInformations[i] = info;
	}

	// usedTypes[]
	count = ReadEncodedUInt();
	usedTypes.Allocate(count, 0);
	for( i = 0; i < count; ++i )
	{
		asCObjectType *ot = ReadObjectType();
		usedTypes.PushLast(ot);
	}

	// Read the size of the value types so we can determine if it is necessary to adjust the code
	asUINT numValueTypes = ReadEncodedUInt();
	for( i = 0; i < numValueTypes; ++i )
	{
		asUINT idx = ReadEncodedUInt();
		asUINT size = ReadEncodedUInt();

		if( idx >= usedTypes.GetLength() )
		{
			// TODO: Write error message to the callback
			error = true;
			continue;
		}

		if( usedTypes[idx] && size != usedTypes[idx]->GetSize() )
		{
			// Keep track of the object types that have changed size 
			// so the bytecode can be adjusted.
			SObjChangeSize s = { usedTypes[idx], size };
			oldObjectSizes.PushLast(s);
		}
	}

	// usedTypeIds[]
	ReadUsedTypeIds();

	// usedFunctions[]
	ReadUsedFunctions();

	// usedGlobalProperties[]
	ReadUsedGlobalProps();

	// usedStringConstants[]
	ReadUsedStringConstants();

	// usedObjectProperties
	ReadUsedObjectProps();

	for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
		TranslateFunction(module->scriptFunctions[i]);
	for( i = 0; i < module->scriptGlobals.GetLength(); i++ )
		if( module->scriptGlobals[i]->GetInitFunc() )
			TranslateFunction(module->scriptGlobals[i]->GetInitFunc());

	// Init system functions properly
	engine->PrepareEngine();

	// Add references for all functions
	if( !error )
	{
		for( i = 0; i < module->scriptFunctions.GetLength(); i++ )
			module->scriptFunctions[i]->AddReferences();
		for( i = 0; i < module->scriptGlobals.GetLength(); i++ )
			if( module->scriptGlobals[i]->GetInitFunc() )
				module->scriptGlobals[i]->GetInitFunc()->AddReferences();

		if( engine->ep.initGlobalVarsAfterBuild )
		{
			int r = module->ResetGlobalVars(0);
			if( r < 0 ) error = true;
		}
	}

	return error ? asERROR : asSUCCESS;
}

int asCRestore::FindStringConstantIndex(int id)
{
	for( asUINT i = 0; i < usedStringConstants.GetLength(); i++ )
		if( usedStringConstants[i] == id )
			return i;

	usedStringConstants.PushLast(id);
	return int(usedStringConstants.GetLength() - 1);
}

void asCRestore::WriteUsedStringConstants()
{
	asUINT count = (asUINT)usedStringConstants.GetLength();
	WriteEncodedUInt(count);
	for( asUINT i = 0; i < count; ++i )
		WriteString(engine->stringConstants[usedStringConstants[i]]);
}

void asCRestore::ReadUsedStringConstants()
{
	asCString str;

	asUINT count;
	count = ReadEncodedUInt();
	usedStringConstants.SetLength(count);
	for( asUINT i = 0; i < count; ++i ) 
	{
		ReadString(&str);
		usedStringConstants[i] = engine->AddConstantString(str.AddressOf(), str.GetLength());
	}
}

void asCRestore::WriteUsedFunctions()
{
	asUINT count = (asUINT)usedFunctions.GetLength();
	WriteEncodedUInt(count);

	for( asUINT n = 0; n < usedFunctions.GetLength(); n++ )
	{
		char c;

		// Write enough data to be able to uniquely identify the function upon load

		// Is the function from the module or the application?
		c = usedFunctions[n]->module ? 'm' : 'a';
		WRITE_NUM(c);

		WriteFunctionSignature(usedFunctions[n]);
	}
}

void asCRestore::ReadUsedFunctions()
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
		READ_NUM(c);

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
					func.funcType != f->funcType )
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
					func.objectType != f->objectType )
					continue;

				usedFunctions[n] = f;
				break;
			}
		}

		// Set the type to dummy so it won't try to release the id
		func.funcType = asFUNC_DUMMY;
	}
}

void asCRestore::WriteFunctionSignature(asCScriptFunction *func)
{
	asUINT i, count;

	WriteString(&func->name);
	WriteDataType(&func->returnType);

	count = (asUINT)func->parameterTypes.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; ++i ) 
		WriteDataType(&func->parameterTypes[i]);
	
	count = (asUINT)func->inOutFlags.GetLength();
	WriteEncodedUInt(count);
	for( i = 0; i < count; ++i )
		WriteEncodedUInt(func->inOutFlags[i]);

	WRITE_NUM(func->funcType);

	// Write the default args, from last to first
	count = 0;
	for( i = (asUINT)func->defaultArgs.GetLength(); i-- > 0; )
		if( func->defaultArgs[i] )
			count++;
	WriteEncodedUInt(count);
	for( i = (asUINT)func->defaultArgs.GetLength(); i-- > 0; )
		if( func->defaultArgs[i] )
			WriteString(func->defaultArgs[i]);

	WriteObjectType(func->objectType);

	if( func->objectType )
	{
		asBYTE b = 0;
		b += func->isReadOnly ? 1 : 0;
		b += func->isPrivate  ? 2 : 0;
		WRITE_NUM(b);
	}
}

void asCRestore::ReadFunctionSignature(asCScriptFunction *func)
{
	int i, count;
	asCDataType dt;
	int num;

	ReadString(&func->name);
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

	READ_NUM(func->funcType);

	// Read the default args, from last to first
	count = ReadEncodedUInt();
	if( count )
	{
		func->defaultArgs.SetLength(func->parameterTypes.GetLength());
		for( i = 0; i < count; i++ )
		{
			asCString *str = asNEW(asCString);
			func->defaultArgs[func->defaultArgs.GetLength()-1-i] = str;
			ReadString(str);
		}
	}
	
	func->objectType = ReadObjectType();
	if( func->objectType )
	{
		asBYTE b;
		READ_NUM(b);
		func->isReadOnly = (b & 1) ? true : false;
		func->isPrivate  = (b & 2) ? true : false;
	}
}

void asCRestore::WriteFunction(asCScriptFunction* func) 
{
	char c;

	// If there is no function, then store a null char
	if( func == 0 )
	{
		c = '\0';
		WRITE_NUM(c);
		return;
	}

	// First check if the function has been saved already
	for( asUINT f = 0; f < savedFunctions.GetLength(); f++ )
	{
		if( savedFunctions[f] == func )
		{
			c = 'r';
			WRITE_NUM(c);
			WriteEncodedUInt(f);
			return;
		}
	}

	// Keep a reference to the function in the list
	savedFunctions.PushLast(func);

	c = 'f';
	WRITE_NUM(c);

	asUINT i, count;

	WriteFunctionSignature(func);

	if( func->funcType == asFUNC_SCRIPT )
	{
		count = (asUINT)func->byteCode.GetLength();
		WriteEncodedUInt(count);
		WriteByteCode(func->byteCode.AddressOf(), count);

		count = (asUINT)func->objVariablePos.GetLength();
		WriteEncodedUInt(count);
		for( i = 0; i < count; ++i )
		{
			WriteObjectType(func->objVariableTypes[i]);
			WriteEncodedUInt(func->objVariablePos[i]);
			WRITE_NUM(func->objVariableIsOnHeap[i]);
		}

		WriteEncodedUInt(func->stackNeeded);

		WriteEncodedUInt((asUINT)func->objVariableInfo.GetLength());
		for( i = 0; i < func->objVariableInfo.GetLength(); ++i )
		{
			WriteEncodedUInt(func->objVariableInfo[i].programPos);
			WriteEncodedUInt(func->objVariableInfo[i].variableOffset); // TODO: should be int
			WriteEncodedUInt(func->objVariableInfo[i].option);
		}

		asUINT length = (asUINT)func->lineNumbers.GetLength();
		WriteEncodedUInt(length);
		for( i = 0; i < length; ++i )
			WriteEncodedUInt(func->lineNumbers[i]);

		// TODO: Write variables
	}
	else if( func->funcType == asFUNC_VIRTUAL )
	{
		WriteEncodedUInt(func->vfTableIdx);
	}

	// Store script section name
	if( func->scriptSectionIdx >= 0 )
		WriteString(engine->scriptSectionNames[func->scriptSectionIdx]);
	else
	{
		char c = 0;
		WRITE_NUM(c);
	}
}

asCScriptFunction *asCRestore::ReadFunction(bool addToModule, bool addToEngine) 
{
	char c;
	READ_NUM(c);

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
			// TODO: Write to message callback
			error = true;
			return 0;
		}
	}

	// Load the new function
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine,module,asFUNC_DUMMY);
	savedFunctions.PushLast(func);

	int i, count;
	asCDataType dt;
	int num;

	ReadFunctionSignature(func);

	func->id = engine->GetNextScriptFunctionId();

	if( func->funcType == asFUNC_SCRIPT )
	{
		engine->gc.AddScriptObjectToGC(func, &engine->functionBehaviours);
		
		count = ReadEncodedUInt();
		func->byteCode.Allocate(count, 0);
		ReadByteCode(func->byteCode.AddressOf(), count);
		func->byteCode.SetLength(count);

		count = ReadEncodedUInt();
		func->objVariablePos.Allocate(count, 0);
		func->objVariableTypes.Allocate(count, 0);
		for( i = 0; i < count; ++i )
		{
			func->objVariableTypes.PushLast(ReadObjectType());
			num = ReadEncodedUInt();
			func->objVariablePos.PushLast(num);
			bool b; READ_NUM(b);
			func->objVariableIsOnHeap.PushLast(b);
		}

		func->stackNeeded = ReadEncodedUInt();

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
	}
	else if( func->funcType == asFUNC_VIRTUAL )
	{
		func->vfTableIdx = ReadEncodedUInt();
	}

	// Read script section name
	asCString name;
	ReadString(&name);
	if( name.GetLength() > 0 )
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

void asCRestore::WriteObjectTypeDeclaration(asCObjectType *ot, int phase)
{
	if( phase == 1 )
	{
		// name
		WriteString(&ot->name);
		// flags
		WRITE_NUM(ot->flags);
		// size
		WriteEncodedUInt(ot->size);
	}
	else if( phase == 2 )
	{
		if( ot->flags & asOBJ_ENUM )
		{
			// enumValues[]
			int size = (int)ot->enumValues.GetLength();
			WriteEncodedUInt(size);

			for( int n = 0; n < size; n++ )
			{
				WriteString(&ot->enumValues[n]->name);
				WRITE_NUM(ot->enumValues[n]->value);
			}
		}
		else if( ot->flags & asOBJ_TYPEDEF )
		{
			eTokenType t = ot->templateSubType.GetTokenType();
			WRITE_NUM(t);
		}
		else
		{
			WriteObjectType(ot->derivedFrom);

			// interfaces[]
			int size = (asUINT)ot->interfaces.GetLength();
			WriteEncodedUInt(size);
			asUINT n;
			for( n = 0; n < ot->interfaces.GetLength(); n++ )
			{
				WriteObjectType(ot->interfaces[n]);
			}

			// behaviours
			if( !ot->IsInterface() && ot->flags != asOBJ_TYPEDEF && ot->flags != asOBJ_ENUM )
			{
				WriteFunction(engine->scriptFunctions[ot->beh.construct]);
				WriteFunction(engine->scriptFunctions[ot->beh.destruct]);
				WriteFunction(engine->scriptFunctions[ot->beh.factory]);
				size = (int)ot->beh.constructors.GetLength() - 1;
				WriteEncodedUInt(size);
				for( n = 1; n < ot->beh.constructors.GetLength(); n++ )
				{
					WriteFunction(engine->scriptFunctions[ot->beh.constructors[n]]);
					WriteFunction(engine->scriptFunctions[ot->beh.factories[n]]);
				}
			}

			// methods[]
			size = (int)ot->methods.GetLength();
			WriteEncodedUInt(size);
			for( n = 0; n < ot->methods.GetLength(); n++ )
			{
				WriteFunction(engine->scriptFunctions[ot->methods[n]]);
			}

			// virtualFunctionTable[]
			size = (int)ot->virtualFunctionTable.GetLength();
			WriteEncodedUInt(size);
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
		WriteEncodedUInt(size);
		for( asUINT n = 0; n < ot->properties.GetLength(); n++ )
		{
			WriteObjectProperty(ot->properties[n]);
		}
	}
}

void asCRestore::ReadObjectTypeDeclaration(asCObjectType *ot, int phase)
{
	if( phase == 1 )
	{
		// name
		ReadString(&ot->name);
		// flags
		READ_NUM(ot->flags);
		// size
		ot->size = ReadEncodedUInt();
		// Reset the size of script classes, since it will be recalculated as properties are added
		if( (ot->flags & asOBJ_SCRIPT_OBJECT) && ot->size != 0 )
			ot->size = sizeof(asCScriptObject);

		// Use the default script class behaviours
		ot->beh = engine->scriptTypeBehaviours.beh;
		engine->scriptFunctions[ot->beh.addref]->AddRef();
		engine->scriptFunctions[ot->beh.release]->AddRef();
		engine->scriptFunctions[ot->beh.gcEnumReferences]->AddRef();
		engine->scriptFunctions[ot->beh.gcGetFlag]->AddRef();
		engine->scriptFunctions[ot->beh.gcGetRefCount]->AddRef();
		engine->scriptFunctions[ot->beh.gcReleaseAllReferences]->AddRef();
		engine->scriptFunctions[ot->beh.gcSetFlag]->AddRef();
		engine->scriptFunctions[ot->beh.copy]->AddRef();
		engine->scriptFunctions[ot->beh.factory]->AddRef();
		engine->scriptFunctions[ot->beh.construct]->AddRef();
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
				ReadString(&e->name);
				READ_NUM(e->value);
				ot->enumValues.PushLast(e);
			}
		}
		else if( ot->flags & asOBJ_TYPEDEF )
		{
			eTokenType t;
			READ_NUM(t);
			ot->templateSubType = asCDataType::CreatePrimitive(t, false);
		}
		else
		{
			ot->derivedFrom = ReadObjectType();
			if( ot->derivedFrom )
				ot->derivedFrom->AddRef();

			// interfaces[]
			int size = ReadEncodedUInt();
			ot->interfaces.Allocate(size,0);
			int n;
			for( n = 0; n < size; n++ )
			{
				asCObjectType *intf = ReadObjectType();
				ot->interfaces.PushLast(intf);
			}

			// behaviours
			if( !ot->IsInterface() && ot->flags != asOBJ_TYPEDEF && ot->flags != asOBJ_ENUM )
			{
				asCScriptFunction *func = ReadFunction();
				if( func )
				{
					engine->scriptFunctions[ot->beh.construct]->Release();
					ot->beh.construct = func->id;
					ot->beh.constructors[0] = func->id;
					func->AddRef();
				}

				func = ReadFunction();
				if( func )
				{
					ot->beh.destruct = func->id;
					func->AddRef();
				}

				func = ReadFunction();
				if( func )
				{
					engine->scriptFunctions[ot->beh.factory]->Release();
					ot->beh.factory = func->id;
					ot->beh.factories[0] = func->id;
					func->AddRef();
				}

				size = ReadEncodedUInt();
				for( n = 0; n < size; n++ )
				{
					asCScriptFunction *func = ReadFunction();
					if( func )
					{
						ot->beh.constructors.PushLast(func->id);
						func->AddRef();
					}

					func = ReadFunction();
					if( func )
					{
						ot->beh.factories.PushLast(func->id);
						func->AddRef();
					}
				}
			}

			// methods[]
			size = ReadEncodedUInt();
			for( n = 0; n < size; n++ ) 
			{
				asCScriptFunction *func = ReadFunction();
				if( func )
				{
					ot->methods.PushLast(func->id);
					func->AddRef();
				}
			}

			// virtualFunctionTable[]
			size = ReadEncodedUInt();
			for( n = 0; n < size; n++ )
			{
				asCScriptFunction *func = ReadFunction();
				if( func )
				{
					ot->virtualFunctionTable.PushLast(func);
					func->AddRef();
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

void asCRestore::WriteEncodedUInt(asUINT i)
{
	if( i < 128 )
	{
		asBYTE b = (asBYTE)i;
		WRITE_NUM(b);
	}
	else if( i < 16384 )
	{
		asBYTE b = asBYTE(0x80 + (i >> 8));
		WRITE_NUM(b);
		b = asBYTE(i & 0xFF);
		WRITE_NUM(b);
	}
	else if( i < 2097152 )
	{
		asBYTE b = asBYTE(0xC0 + (i >> 16));
		WRITE_NUM(b);
		b = asBYTE((i >> 8) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE(i & 0xFF);
		WRITE_NUM(b);
	}
	else if( i < 268435456 )
	{
		asBYTE b = asBYTE(0xE0 + (i >> 24));
		WRITE_NUM(b);
		b = asBYTE((i >> 16) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE((i >> 8) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE(i & 0xFF);
		WRITE_NUM(b);
	}
	else
	{
		asBYTE b = asBYTE(0xF0);
		WRITE_NUM(b);
		b = asBYTE((i >> 24) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE((i >> 16) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE((i >> 8) & 0xFF);
		WRITE_NUM(b);
		b = asBYTE(i & 0xFF);
		WRITE_NUM(b);
	}
}

asUINT asCRestore::ReadEncodedUInt()
{
	asUINT i = 0;
	asBYTE b;
	READ_NUM(b);
	if( b < 128 )
	{
		i = b;
	}
	else if( b < 192 )
	{
		i = asUINT(b & 0x3F) << 8;
		READ_NUM(b);
		i += b;
	}
	else if( b < 224 )
	{
		i = asUINT(b & 0x1F) << 16;
		READ_NUM(b);
		i += asUINT(b) << 8;
		READ_NUM(b);
		i += b;
	}
	else if( b < 240 )
	{
		i = asUINT(b & 0x0F) << 24;
		READ_NUM(b);
		i += asUINT(b) << 16;
		READ_NUM(b);
		i += asUINT(b) << 8;
		READ_NUM(b);
		i += b;
	}
	else
	{
		READ_NUM(b);
		i += asUINT(b) << 24;
		READ_NUM(b);
		i += asUINT(b) << 16;
		READ_NUM(b);
		i += asUINT(b) << 8;
		READ_NUM(b);
		i += b;
	}

	return i;
}

void asCRestore::WriteString(asCString* str) 
{
	// TODO: All strings should be stored in a separate section, and when
	//       they are used an offset into that section should be stored.
	//       This will make it unnecessary to store the extra byte to 
	//       identify new versus old strings.

	if( str->GetLength() == 0 )
	{
		char z = '\0';
		WRITE_NUM(z);
		return;
	}

	// First check if the string hasn't been saved already
	for( asUINT n = 0; n < savedStrings.GetLength(); n++ )
	{
		if( *str == savedStrings[n] )
		{
			// Save a reference to the existing string
			char b = 'r';
			WRITE_NUM(b);
			WriteEncodedUInt(n);
			return;
		}
	}

	// Save a new string
	char b = 'n';
	WRITE_NUM(b);

	asUINT len = (asUINT)str->GetLength();
	WriteEncodedUInt(len);
	stream->Write(str->AddressOf(), (asUINT)len);

	savedStrings.PushLast(*str);
}

void asCRestore::ReadString(asCString* str) 
{
	char b;
	READ_NUM(b);
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
		*str = savedStrings[n];
	}
}

void asCRestore::WriteGlobalProperty(asCGlobalProperty* prop) 
{
	// TODO: We might be able to avoid storing the name and type of the global 
	//       properties twice if we merge this with the WriteUsedGlobalProperties. 
	WriteString(&prop->name);
	WriteDataType(&prop->type);

	// Store the initialization function
	if( prop->GetInitFunc() )
	{
		bool f = true;
		WRITE_NUM(f);

		WriteFunction(prop->GetInitFunc());
	}
	else
	{
		bool f = false;
		WRITE_NUM(f);
	}
}

void asCRestore::ReadGlobalProperty() 
{
	asCString name;
	asCDataType type;

	ReadString(&name);
	ReadDataType(&type);

	asCGlobalProperty *prop = module->AllocateGlobalProperty(name.AddressOf(), type);

	// Read the initialization function
	bool f;
	READ_NUM(f);
	if( f )
	{
		asCScriptFunction *func = ReadFunction(false, true);

		prop->SetInitFunc(func);
		func->Release();
	}
}

void asCRestore::WriteObjectProperty(asCObjectProperty* prop) 
{
	WriteString(&prop->name);
	WriteDataType(&prop->type);
	WRITE_NUM(prop->isPrivate);
}

void asCRestore::ReadObjectProperty(asCObjectType *ot) 
{
	asCString name;
	ReadString(&name);
	asCDataType dt;
	ReadDataType(&dt);
	bool isPrivate;
	READ_NUM(isPrivate);

	ot->AddPropertyToClass(name, dt, isPrivate);
}

void asCRestore::WriteDataType(const asCDataType *dt) 
{
	// First check if the datatype has already been saved
	for( asUINT n = 0; n < savedDataTypes.GetLength(); n++ )
	{
		if( *dt == savedDataTypes[n] )
		{
			asUINT c = 0;
			WriteEncodedUInt(c);
			WriteEncodedUInt(n);
			return;
		}
	}

	// Save the new datatype
	savedDataTypes.PushLast(*dt);

	bool b;
	int t = dt->GetTokenType();
	WriteEncodedUInt(t);
	if( t == ttIdentifier )
	{
		WriteObjectType(dt->GetObjectType());
		b = dt->IsObjectHandle();
		WRITE_NUM(b);
		b = dt->IsHandleToConst();
		WRITE_NUM(b);
	}
	b = dt->IsReference();
	WRITE_NUM(b);
	b = dt->IsReadOnly();
	WRITE_NUM(b);

	if( t == ttIdentifier && dt->GetObjectType()->name == "_builtin_function_" )
	{
		WriteFunctionSignature(dt->GetFuncDef());
	}
}

void asCRestore::ReadDataType(asCDataType *dt) 
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
		READ_NUM(isObjectHandle);
		READ_NUM(isHandleToConst);
	}
	READ_NUM(isReference);
	READ_NUM(isReadOnly);

	asCScriptFunction *funcDef = 0;
	if( tokenType == ttIdentifier && objType && objType->name == "_builtin_function_" )
	{
		asCScriptFunction func(engine, module, asFUNC_DUMMY);
		ReadFunctionSignature(&func);
		for( asUINT n = 0; n < engine->registeredFuncDefs.GetLength(); n++ )
		{
			// TODO: Only return the definitions for the config groups that the module has access to
			if( engine->registeredFuncDefs[n]->name == func.name )
			{
				funcDef = engine->registeredFuncDefs[n];
				break;
			}
		}

		if( !funcDef && module )
		{
			for( asUINT n = 0; n < module->funcDefs.GetLength(); n++ )
			{
				if( module->funcDefs[n]->name == func.name )
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

void asCRestore::WriteObjectType(asCObjectType* ot) 
{
	char ch;

	// Only write the object type name
	if( ot )
	{
		// Check for template instances/specializations
		if( ot->templateSubType.GetTokenType() != ttUnrecognizedToken )
		{
			ch = 'a';
			WRITE_NUM(ch);
			WriteString(&ot->name);

			if( ot->templateSubType.IsObject() || ot->templateSubType.IsEnumType() )
			{
				ch = 's';
				WRITE_NUM(ch);
				WriteObjectType(ot->templateSubType.GetObjectType());

				if( ot->templateSubType.IsObjectHandle() )
					ch = 'h';
				else
					ch = 'o';
				WRITE_NUM(ch);
			}
			else
			{
				ch = 't';
				WRITE_NUM(ch);
				eTokenType t = ot->templateSubType.GetTokenType();
				WRITE_NUM(t);
			}
		}
		else if( ot->flags & asOBJ_TEMPLATE_SUBTYPE )
		{
			ch = 's';
			WRITE_NUM(ch);
			WriteString(&ot->name);
		}
		else
		{
			ch = 'o';
			WRITE_NUM(ch);
			WriteString(&ot->name);
		}
	}
	else
	{
		ch = '\0';
		WRITE_NUM(ch);
	}
}

asCObjectType* asCRestore::ReadObjectType() 
{
	asCObjectType *ot = 0;
	char ch;
	READ_NUM(ch);
	if( ch == 'a' )
	{
		// Read the name of the template type
		asCString typeName;
		ReadString(&typeName);
		asCObjectType *tmpl = engine->GetObjectType(typeName.AddressOf());
		if( tmpl == 0 )
		{
			// TODO: Move text to as_texts.h
			asCString str;
			str.Format("Template type '%s' doesn't exist", typeName.AddressOf());
			engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
			error = true;
			return 0;
		}

		READ_NUM(ch);
		if( ch == 's' )
		{
			ot = ReadObjectType();
			if( ot == 0 )
			{
				// TODO: Move text to as_texts.h
				asCString str;
				str.Format("Failed to read subtype of template type '%s'", typeName.AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}

			asCDataType dt = asCDataType::CreateObject(ot, false);

			READ_NUM(ch);
			if( ch == 'h' )
				dt.MakeHandle(true);

			if( tmpl->templateSubType.GetObjectType() == ot )
				ot = tmpl;
			else
				ot = engine->GetTemplateInstanceType(tmpl, dt);
			
			if( ot == 0 )
			{
				// TODO: Move text to as_texts.h
				asCString str;
				str.Format("Attempting to instanciate invalid template type '%s<%s>'", typeName.AddressOf(), dt.Format().AddressOf());
				engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
				error = true;
				return 0;
			}
		}
		else
		{
			eTokenType tokenType;
			READ_NUM(tokenType);
			asCDataType dt = asCDataType::CreatePrimitive(tokenType, false);

			ot = engine->GetTemplateInstanceType(tmpl, dt);
			
			if( ot == 0 )
			{
				// TODO: Move text to as_texts.h
				asCString str;
				str.Format("Attempting to instanciate invalid template type '%s<%s>'", typeName.AddressOf(), dt.Format().AddressOf());
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
			// TODO: Move text to as_texts.h
			asCString str;
			str.Format("Template subtype type '%s' doesn't exist", typeName.AddressOf());
			engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, str.AddressOf());
			error = true;
			return 0;
		}
	}
	else if( ch == 'o' )
	{
		// Read the object type name
		asCString typeName;
		ReadString(&typeName);

		if( typeName.GetLength() && typeName != "_builtin_object_" && typeName != "_builtin_function_" )
		{
			// Find the object type
			ot = module->GetObjectType(typeName.AddressOf());
			if( !ot )
				ot = engine->GetObjectType(typeName.AddressOf());
			
			if( ot == 0 )
			{
				// TODO: Move text to as_texts.h
				asCString str;
				str.Format("Object type '%s' doesn't exist", typeName.AddressOf());
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

void asCRestore::WriteByteCode(asDWORD *bc, int length)
{
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
		else if( c == asBC_FREE   || // wW_PTR_ARG
			     c == asBC_REFCPY || // PTR_ARG
				 c == asBC_OBJTYPE ) // PTR_ARG
		{
			// Translate object type pointers into indices
			*(int*)(tmp+1) = FindObjectTypeIdx(*(asCObjectType**)(tmp+1));
		}
		else if( c == asBC_TYPEID || // DW_ARG
			     c == asBC_Cast )   // DW_ARG
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
			*(asPTRWORD*)(tmp+1) = FindFunctionIndex(*(asCScriptFunction**)(tmp+1));
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
		else if( c == asBC_PGA ||      // PTR_ARG
			     c == asBC_LDG ||      // PTR_ARG
				 c == asBC_PshG4 ||    // PTR_ARG
				 c == asBC_LdGRdR4 ||  // wW_PTR_ARG
				 c == asBC_CpyGtoV4 || // wW_PTR_ARG
				 c == asBC_CpyVtoG4 || // rW_PTR_ARG
				 c == asBC_SetG4 )     // PTR_DW_ARG
		{
			// Translate global variable pointers into indices
			*(int*)(tmp+1) = FindGlobalPropPtrIndex(*(void**)(tmp+1));
		}

		// Now store the instruction in the smallest possible way
		switch( asBCInfo[c].type )
		{
		case asBCTYPE_NO_ARG:
			{
				// Just write 1 byte
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);
			}
			break;
		case asBCTYPE_W_ARG:
		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);
				
				// Write the argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);
			}
			break;
		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_W_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the word argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);

				// Write the dword argument
				// TODO: Should be WriteEncodedInt since we do not know if it is a signed value or not
				WriteEncodedUInt(tmp[1]);
			}
			break;
		case asBCTYPE_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the argument
				// TODO: Should be WriteEncodedInt since we do not know if it is a signed value or not
				WriteEncodedUInt(tmp[1]);
			}
			break;
		case asBCTYPE_DW_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the dword argument
				// TODO: Should be WriteEncodedInt since we do not know if it is a signed value or not
				WriteEncodedUInt(tmp[1]);

				// Write the dword argument
				// TODO: Should be WriteEncodedInt since we do not know if it is a signed value or not
				WriteEncodedUInt(tmp[2]);
			}
			break;
		case asBCTYPE_wW_rW_rW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the first argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);

				// Write the second argument
				w = *(((asWORD*)tmp)+2);
				WRITE_NUM(w);

				// Write the third argument
				w = *(((asWORD*)tmp)+3);
				WRITE_NUM(w);
			}
			break;
		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_rW_rW_ARG:
		case asBCTYPE_wW_W_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the first argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);

				// Write the second argument
				w = *(((asWORD*)tmp)+2);
				WRITE_NUM(w);
			}
			break;
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the first argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);

				// Write the second argument
				w = *(((asWORD*)tmp)+2);
				WRITE_NUM(w);

				// Write the third argument
				// TODO: This could be encoded as an int to decrease the size
				asDWORD dw = tmp[2];
				WRITE_NUM(dw);
			}
			break;
		case asBCTYPE_QW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the argument
				// TODO: This could be encoded as an int to decrease the size
				asQWORD qw = *(asQWORD*)&tmp[1];
				WRITE_NUM(qw);
			}
			break;
		case asBCTYPE_QW_DW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the argument
				// TODO: This could be encoded as an int to decrease the size
				asQWORD qw = *(asQWORD*)&tmp[1];
				WRITE_NUM(qw);

				// Write the second argument
				// TODO: This could be encoded as an int to decrease the size
				asDWORD dw = tmp[3];
				WRITE_NUM(dw);
			}
			break;
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_wW_QW_ARG:
			{
				// Write the instruction code
				asBYTE b = (asBYTE)c;
				WRITE_NUM(b);

				// Write the first argument
				asWORD w = *(((asWORD*)tmp)+1);
				WRITE_NUM(w);

				// Write the argument
				// TODO: This could be encoded as an int to decrease the size
				asQWORD qw = *(asQWORD*)&tmp[1];
				WRITE_NUM(qw);
			}
			break;
		default:
			{
				// This should never happen
				asASSERT(false);

				// Store the bc as is
				for( int n = 0; n < asBCTypeSize[asBCInfo[c].type]; n++ )
					WRITE_NUM(tmp[n]);
			}
		}

		// Move to the next instruction
		bc += asBCTypeSize[asBCInfo[c].type];
		length -= asBCTypeSize[asBCInfo[c].type];
	}
}

void asCRestore::ReadByteCode(asDWORD *bc, int length)
{
	while( length )
	{
		asBYTE b;
		READ_NUM(b);

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
				asWORD w;
				READ_NUM(w);
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
				asWORD w;
				READ_NUM(w);
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the dword argument
				// TODO: Should be ReadEncodedInt() since we do not know if it is a signed value or not
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the argument
				// TODO: Should be ReadEncodedInt() since we do not know if it is a signed value or not
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_DW_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the first argument
				// TODO: Should be ReadEncodedInt() since we do not know if it is a signed value or not
				*bc++ = ReadEncodedUInt();

				// Read the second argument
				// TODO: Should be ReadEncodedInt() since we do not know if it is a signed value or not
				*bc++ = ReadEncodedUInt();
			}
			break;
		case asBCTYPE_wW_rW_rW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w;
				READ_NUM(w);
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				READ_NUM(w);
				*(asWORD*)bc = w;

				// Read the third argument
				READ_NUM(w);
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
				asWORD w;
				READ_NUM(w);
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				READ_NUM(w);
				*(asWORD*)bc = w;

				bc++;
			}
			break;
		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w;
				READ_NUM(w);
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the second argument
				READ_NUM(w);
				*(asWORD*)bc = w;
				bc++;
	
				// Read the third argument
				asDWORD dw;
				READ_NUM(dw);
				*bc++ = dw;
			}
			break;
		case asBCTYPE_QW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the argument
				asQWORD qw;
				READ_NUM(qw);
				*(asQWORD*)bc = qw;
				bc += 2;
			}
			break;
		case asBCTYPE_QW_DW_ARG:
			{
				*(asBYTE*)(bc) = b;
				bc++;

				// Read the first argument
				asQWORD qw;
				READ_NUM(qw);
				*(asQWORD*)bc = qw;
				bc += 2;

				// Read the second argument
				asDWORD dw;
				READ_NUM(dw);
				*bc++ = dw;
			}
			break;
		case asBCTYPE_rW_QW_ARG:
		case asBCTYPE_wW_QW_ARG:
			{
				*(asBYTE*)(bc) = b;

				// Read the first argument
				asWORD w;
				READ_NUM(w);
				*(((asWORD*)bc)+1) = w;
				bc++;

				// Read the argument
				asQWORD qw;
				READ_NUM(qw);
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
				READ_NUM(t); c += t << 16;
				READ_NUM(t); c += t << 8;
				READ_NUM(t); c += t;
#else
				c = b;
				READ_NUM(t); c += t << 8;
				READ_NUM(t); c += t << 16;
				READ_NUM(t); c += t << 24;
#endif

				*bc++ = c;
				c = *(asBYTE*)&c;

				// Read the bc as is
				for( int n = 1; n < asBCTypeSize[asBCInfo[c].type]; n++ )
					READ_NUM(*bc++);
			}
		}

		length -= asBCTypeSize[asBCInfo[b].type];
	}
}

void asCRestore::WriteUsedTypeIds()
{
	asUINT count = (asUINT)usedTypeIds.GetLength();
	WriteEncodedUInt(count);
	for( asUINT n = 0; n < count; n++ )
		WriteDataType(engine->GetDataTypeFromTypeId(usedTypeIds[n]));
}

void asCRestore::ReadUsedTypeIds()
{
	asUINT count = ReadEncodedUInt();
	usedTypeIds.SetLength(count);
	for( asUINT n = 0; n < count; n++ )
	{
		asCDataType dt;
		ReadDataType(&dt);
		usedTypeIds[n] = engine->GetTypeIdFromDataType(dt);
	}
}

int asCRestore::FindGlobalPropPtrIndex(void *ptr)
{
	int i = usedGlobalProperties.IndexOf(ptr);
	if( i >= 0 ) return i;

	usedGlobalProperties.PushLast(ptr);
	return (int)usedGlobalProperties.GetLength()-1;
}

void asCRestore::WriteUsedGlobalProps()
{
	int c = (int)usedGlobalProperties.GetLength();
	WriteEncodedUInt(c);

	for( int n = 0; n < c; n++ )
	{
		size_t *p = (size_t*)usedGlobalProperties[n];
		
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
		WriteDataType(&prop->type);

		// Also store whether the property is a module property or a registered property
		WRITE_NUM(moduleProp);
	}
}

void asCRestore::ReadUsedGlobalProps()
{
	int c = ReadEncodedUInt();

	usedGlobalProperties.SetLength(c);

	for( int n = 0; n < c; n++ )
	{
		asCString name;
		asCDataType type;
		char moduleProp;

		ReadString(&name);
		ReadDataType(&type);
		READ_NUM(moduleProp);

		// Find the real property
		void *prop = 0;
		if( moduleProp )
		{
			for( asUINT p = 0; p < module->scriptGlobals.GetLength(); p++ )
			{
				if( module->scriptGlobals[p]->name == name &&
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
					engine->registeredGlobalProps[p]->type == type )
				{
					prop = engine->registeredGlobalProps[p]->GetAddressOfValue();
					break;
				}
			}
		}

		usedGlobalProperties[n] = prop;

		if( prop == 0 )
		{
			// TODO: Write error message to the callback
			error = true;
		}
	}
}

void asCRestore::WriteUsedObjectProps()
{
	int c = (int)usedObjectProperties.GetLength();
	WriteEncodedUInt(c);

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

void asCRestore::ReadUsedObjectProps()
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

//---------------------------------------------------------------------------------------------------
// Miscellaneous
//---------------------------------------------------------------------------------------------------

int asCRestore::FindObjectPropIndex(short offset, int typeId)
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

short asCRestore::FindObjectPropOffset(asWORD index)
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

int asCRestore::FindFunctionIndex(asCScriptFunction *func)
{
	for( asUINT n = 0; n < usedFunctions.GetLength(); n++ )
	{
		if( usedFunctions[n] == func )
			return n;
	}

	usedFunctions.PushLast(func);
	return (int)usedFunctions.GetLength() - 1;
}

asCScriptFunction *asCRestore::FindFunction(int idx)
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

void asCRestore::TranslateFunction(asCScriptFunction *func)
{
	asUINT n;
	asDWORD *bc = func->byteCode.AddressOf();
	for( n = 0; n < func->byteCode.GetLength(); )
	{
		int c = *(asBYTE*)&bc[n];
		if( c == asBC_FREE ||
			c == asBC_REFCPY || c == asBC_OBJTYPE )
		{
			// Translate the index to the true object type
			asPTRWORD *ot = (asPTRWORD*)&bc[n+1];
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
			const asCDataType *dt = engine->GetDataTypeFromTypeId(*tid);
			if( dt == 0 )
			{
				// TODO: Write error to message
				error = true;
			}
			else
				asBC_SWORDARG0(&bc[n]) = (short)dt->GetSizeInMemoryDWords();
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
			asPTRWORD *fid = (asPTRWORD*)&bc[n+1];
			*fid = (asPTRWORD)(size_t)FindFunction((int)*fid);
		}
		else if( c == asBC_ALLOC )
		{
			// Translate the index to the true object type
			asPTRWORD *arg = (asPTRWORD*)&bc[n+1];
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
		else if( c == asBC_PGA ||
			     c == asBC_LDG ||
				 c == asBC_PshG4 ||
				 c == asBC_LdGRdR4 ||
				 c == asBC_CpyGtoV4 ||
				 c == asBC_CpyVtoG4 ||
				 c == asBC_SetG4 )
		{
			// Translate the global var index to pointer
			asPTRWORD *index = (asPTRWORD*)&bc[n+1];
			if( *(asUINT*)index < usedGlobalProperties.GetLength() )
				*(void**)index = usedGlobalProperties[*(asUINT*)index];
			else
			{
				// TODO: Write to message callback
				error = true;
				return;
			}
		}

		n += asBCTypeSize[asBCInfo[c].type];
	}

	// As the bytecode may have been generated on a different platform it is necessary
	// to adjust the bytecode in case any of the value types allocated on the stack has
	// a different size on this platform.
	asCArray<int> adjustments;
	for( n = 0; n < func->objVariableTypes.GetLength(); n++ )
	{
		if( func->objVariableTypes[n] &&
			(func->objVariableTypes[n]->GetFlags() & asOBJ_VALUE) &&
			!func->objVariableIsOnHeap[n] )
		{
			// Check if type has a different size than originally
			for( asUINT s = 0; s < oldObjectSizes.GetLength(); s++ )
			{
				if( oldObjectSizes[s].objType == func->objVariableTypes[n] &&
					oldObjectSizes[s].oldSize != func->objVariableTypes[n]->GetSize() )
				{
					// How much needs to be adjusted? 
					int newSize = func->objVariableTypes[n]->GetSize();
					newSize = newSize < 4 ? 1 : newSize/4;
					int oldSize = oldObjectSizes[s].oldSize;
					oldSize = oldSize < 4 ? 1 : oldSize/4;

					int adjust = newSize - oldSize;
					if( adjust != 0 )
					{
						adjustments.PushLast(func->objVariablePos[n]);
						adjustments.PushLast(adjust);
					}
				}
			}
		}
	}

	asCArray<int> adjustByPos(func->stackNeeded);
	if( adjustments.GetLength() )
	{
		adjustByPos.SetLength(func->stackNeeded);
		memset(adjustByPos.AddressOf(), 0, adjustByPos.GetLength()*sizeof(int));

		// Build look-up table with the adjustments for each stack position
		for( n = 0; n < adjustments.GetLength(); n+=2 )
		{
			int pos    = adjustments[n];
			int adjust = adjustments[n+1];

			for( asUINT i = pos; i < adjustByPos.GetLength(); i++ )
				adjustByPos[i] += adjust;
		}

		// Adjust all variable positions
		asDWORD *bc = func->byteCode.AddressOf();
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
					short var = asBC_SWORDARG0(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG0(&bc[n]) += (short)adjustByPos[var];
				}
				break;

			case asBCTYPE_wW_rW_ARG:
			case asBCTYPE_wW_rW_DW_ARG:
			case asBCTYPE_rW_rW_ARG:
				{
					short var = asBC_SWORDARG0(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG0(&bc[n]) += (short)adjustByPos[var];

					var = asBC_SWORDARG1(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG1(&bc[n]) += (short)adjustByPos[var];
				}
				break;

			case asBCTYPE_wW_rW_rW_ARG:
				{
					short var = asBC_SWORDARG0(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG0(&bc[n]) += (short)adjustByPos[var];

					var = asBC_SWORDARG1(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG1(&bc[n]) += (short)adjustByPos[var];

					var = asBC_SWORDARG2(&bc[n]);
					if( var >= (int)adjustByPos.GetLength() ) 
						error = true;
					else if( var >= 0 ) 
						asBC_SWORDARG2(&bc[n]) += (short)adjustByPos[var];
				}
				break;

			default:
				// The other types don't treat variables so won't be modified
				break;
			}

			if( c == asBC_PUSH )
			{
				// TODO: Maybe the push instruction should be removed, and be kept in 
				//       the asCScriptFunction as a property instead. CallScriptFunction 
				//       can immediately reserve the space

				// PUSH is only used to reserve stack space for variables
				asBC_WORDARG0(&bc[n]) += (asWORD)adjustByPos[adjustByPos.GetLength()-1];
			}

			n += asBCTypeSize[asBCInfo[c].type];
		}

		// objVariablePos
		for( n = 0; n < func->objVariablePos.GetLength(); n++ )
		{
			if( func->objVariablePos[n] >= (int)adjustByPos.GetLength() )
				error = true;
			else if( func->objVariablePos[n] >= 0 )
				func->objVariablePos[n] += adjustByPos[func->objVariablePos[n]];
		}

		// objVariableInfo[x].variableOffset  // TODO: should be an index into the objVariablePos array
		for( n = 0; n < func->objVariableInfo.GetLength(); n++ )
		{
			if( func->objVariableInfo[n].variableOffset >= (int)adjustByPos.GetLength() )
				error = true;
			else if( func->objVariableInfo[n].variableOffset >= 0 )
				func->objVariableInfo[n].variableOffset += adjustByPos[func->objVariableInfo[n].variableOffset];
		}

		// variables[x].stackOffset
		for( n = 0; n < func->variables.GetLength(); n++ )
		{
			if( func->variables[n]->stackOffset >= (int)adjustByPos.GetLength() )
				error = true;
			else if( func->variables[n]->stackOffset >= 0 )
				func->variables[n]->stackOffset += adjustByPos[func->variables[n]->stackOffset];
		}

		// The stack needed by the function will be adjusted by the highest variable shift
		// TODO: When bytecode is adjusted for 32/64bit it is necessary to adjust 
		//       also for pointers pushed on the stack as function arguments
		func->stackNeeded += adjustByPos[adjustByPos.GetLength()-1];
	}
}

int asCRestore::FindTypeIdIdx(int typeId)
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

int asCRestore::FindTypeId(int idx)
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

int asCRestore::FindObjectTypeIdx(asCObjectType *obj)
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

asCObjectType *asCRestore::FindObjectType(int idx)
{
	if( idx < 0 || idx >= (int)usedTypes.GetLength() )
	{
		// TODO: Write to message callback
		error = true;
		return 0;
	}

	return usedTypes[idx];
}

END_AS_NAMESPACE

