/*
   AngelCode Scripting Library
   Copyright (c) 2003-2010 Andreas Jonsson

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


#include <stdio.h>

#include "as_config.h"

#ifndef AS_MAX_PORTABILITY
#ifdef AS_X64_MSVC

#include "as_callfunc.h"
#include "as_scriptengine.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

// These functions are implemented in as_callfunc_x64_msvc.asm
extern "C" asQWORD CallX64(const asQWORD *args, const asQWORD *floatArgs, int paramSize, asQWORD func);
extern "C" asDWORD GetReturnedFloat();
extern "C" asQWORD GetReturnedDouble();

int CallSystemFunction(int id, asCContext *context, void *objectPointer)
{
	asCScriptEngine *engine = context->engine;
	asCScriptFunction *descr = engine->scriptFunctions[id];
	asSSystemFunctionInterface *sysFunc = descr->sysFuncIntf;
	int callConv = sysFunc->callConv;
	if( callConv == ICC_GENERIC_FUNC || callConv == ICC_GENERIC_METHOD )
		return context->CallGeneric(id, objectPointer);

	asQWORD  retQW             = 0;
	void    *func              = (void*)sysFunc->func;
	asUINT   paramSize         = 0; // QWords
	asDWORD *args              = context->regs.stackPointer;
	void    *retPointer        = 0;
	void    *obj               = 0;
	void   **vftable;
	int      popSize           = sysFunc->paramSize; // DWords

	asQWORD  allArgBuffer[64];
	asQWORD  floatArgBuffer[4];

	context->regs.objectType = descr->returnType.GetObjectType();
	if( descr->returnType.IsObject() && !descr->returnType.IsReference() && !descr->returnType.IsObjectHandle() )
	{
		// Allocate the memory for the object
		retPointer = engine->CallAlloc(descr->returnType.GetObjectType());
	}

	if( callConv >= ICC_THISCALL )
	{
		if( objectPointer )
		{
			obj = objectPointer;
		}
		else
		{
			// The object pointer should be popped from the context stack
			popSize += AS_PTR_SIZE;

			// Check for null pointer
			obj = (void*)*(size_t*)(args);
			if( obj == 0 )
			{
				context->SetInternalException(TXT_NULL_POINTER_ACCESS);
				if( retPointer )
					engine->CallFree(retPointer);
				return 0;
			}

			// Add the base offset for multiple inheritance
			obj = (void*)(size_t(obj) + sysFunc->baseOffset);

			// Skip the object pointer
			args += AS_PTR_SIZE;
		}
	}

	if( callConv == ICC_THISCALL ||
		callConv == ICC_THISCALL_RETURNINMEM ||
		callConv == ICC_VIRTUAL_THISCALL || 
		callConv == ICC_VIRTUAL_THISCALL_RETURNINMEM )
	{
		// Add the object pointer as the first parameter
		allArgBuffer[paramSize++] = (asQWORD)obj;
	}

	if( sysFunc->hostReturnInMemory )
	{
		// The return is made in memory
		callConv++;

		// Set the return pointer as the first argument
		allArgBuffer[paramSize++] = (asQWORD)retPointer;
	}

	if( callConv == ICC_CDECL_OBJFIRST ||
		callConv == ICC_CDECL_OBJFIRST_RETURNINMEM )
	{
		// Add the object pointer as the first parameter
		allArgBuffer[paramSize++] = (asQWORD)obj;
	}

	if( callConv == ICC_VIRTUAL_THISCALL ||
		callConv == ICC_VIRTUAL_THISCALL_RETURNINMEM )
	{
		// Get the true function pointer from the virtual function table
		vftable = *(void***)obj;
		func = vftable[size_t(func)>>2];
	}

	// Move the arguments to the buffer
	asUINT dpos = paramSize;
	asUINT spos = 0;
	for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
	{
		if( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() && !descr->parameterTypes[n].IsReference() )
		{
			if( descr->parameterTypes[n].GetSizeInMemoryDWords() > 2 )
			{
				allArgBuffer[dpos++] = *(asQWORD*)&args[spos];
				spos += AS_PTR_SIZE;
				paramSize++;
			}
			else
			{
				// Copy the object's memory to the buffer
				memcpy(&allArgBuffer[dpos], *(void**)(args+spos), descr->parameterTypes[n].GetSizeInMemoryBytes());

				// Delete the original memory
				engine->CallFree(*(char**)(args+spos));
				spos += AS_PTR_SIZE;
				asUINT dwords = descr->parameterTypes[n].GetSizeInMemoryDWords();
				asUINT qwords = (dwords >> 1) + (dwords & 1);
				dpos      += qwords;
				paramSize += qwords;
			}
		}
		else if( descr->parameterTypes[n].GetTokenType() == ttQuestion )
		{
			// Copy the reference and the type id
			allArgBuffer[dpos++] = *(asQWORD*)&args[spos];
			spos += 2;
			allArgBuffer[dpos++] = args[spos++];
			paramSize += 2;
		}
		else
		{
			// Copy the value directly
			asUINT dwords = descr->parameterTypes[n].GetSizeOnStackDWords();
			if( dwords > 1 )
			{
				allArgBuffer[dpos] = *(asQWORD*)&args[spos];

				// Double arguments are moved to a separate buffer in order to be placed in the XMM registers,
				// though this is only done for first 4 arguments, the rest are placed on the stack
				if( paramSize < 4 && descr->parameterTypes[n].IsDoubleType() )
					floatArgBuffer[dpos] = *(asQWORD*)&args[spos];

				dpos++;
				spos += 2;
			}
			else
			{
				allArgBuffer[dpos] = args[spos];

				// Float arguments are moved to a separate buffer in order to be placed in the XMM registers,
				// though this is only done for first 4 arguments, the rest are placed on the stack
				if( paramSize < 4 && descr->parameterTypes[n].IsFloatType() )
					floatArgBuffer[dpos] = args[spos];
				
				dpos++;
				spos++;
			}

			paramSize++;
		}
	}

	if( callConv == ICC_CDECL_OBJLAST ||
		callConv == ICC_CDECL_OBJLAST_RETURNINMEM )
	{
		// Add the object pointer as the last parameter
		allArgBuffer[paramSize++] = (asQWORD)obj;
	}

	context->isCallingSystemFunction = true;
	retQW = CallX64(allArgBuffer, floatArgBuffer, paramSize*8, (size_t)func);
	context->isCallingSystemFunction = false;

	if( sysFunc->takesObjByVal )
	{
		// Need to free the complex objects passed by value
		args = context->regs.stackPointer;
		if( callConv >= ICC_THISCALL && !objectPointer )
		    args += AS_PTR_SIZE;;

		int spos = 0;
		for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
		{
			if( descr->parameterTypes[n].IsObject() &&
				!descr->parameterTypes[n].IsReference() &&
				descr->parameterTypes[n].GetSizeInMemoryDWords() > 2 )
			{
				void *obj = (void*)*(size_t*)&args[spos];
				spos += AS_PTR_SIZE;

				// The destructor is called by the function before  
				// it returns so we should only free the memory
				engine->CallFree(obj);
			}
			else
				spos += descr->parameterTypes[n].GetSizeOnStackDWords();
		}
	}

	// Store the returned value in our stack
	if( descr->returnType.IsObject() && !descr->returnType.IsReference() )
	{
		if( descr->returnType.IsObjectHandle() )
		{
			context->regs.objectRegister = (void*)(size_t)retQW;

			if( sysFunc->returnAutoHandle && context->regs.objectRegister )
				engine->CallObjectMethod(context->regs.objectRegister, descr->returnType.GetObjectType()->beh.addref);
		}
		else
		{
			if( !sysFunc->hostReturnInMemory )
			{
				// Copy the returned value to the pointer sent by the script engine
				if( sysFunc->hostReturnSize == 1 )
					*(asDWORD*)retPointer = (asDWORD)retQW;
				else
					*(asQWORD*)retPointer = retQW;
			}

			// Store the object in the register
			context->regs.objectRegister = retPointer;
		}
	}
	else
	{
		// Store value in value register
		if( sysFunc->hostReturnFloat )
		{
			if( sysFunc->hostReturnSize == 1 )
				*(asDWORD*)&context->regs.valueRegister = GetReturnedFloat();
			else
				context->regs.valueRegister = GetReturnedDouble();
		}
		else if( sysFunc->hostReturnSize == 1 )
			*(asDWORD*)&context->regs.valueRegister = (asDWORD)retQW;
		else
			context->regs.valueRegister = retQW;
	}

	if( sysFunc->hasAutoHandles )
	{
		args = context->regs.stackPointer;
		if( callConv >= ICC_THISCALL && !objectPointer )
			args += AS_PTR_SIZE;

		int spos = 0;
		for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
		{
			if( sysFunc->paramAutoHandles[n] && *(size_t*)&args[spos] )
			{
				// Call the release method on the type
				engine->CallObjectMethod((void*)*(size_t*)&args[spos], descr->parameterTypes[n].GetObjectType()->beh.release);
				*(size_t*)&args[spos] = 0;
			}

			if( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() && !descr->parameterTypes[n].IsReference() )
				spos += AS_PTR_SIZE;
			else
				spos += descr->parameterTypes[n].GetSizeOnStackDWords();
		}
	}

	return popSize;
}


END_AS_NAMESPACE

#endif // AS_X64_MSVC
#endif // AS_MAX_PORTABILITY


