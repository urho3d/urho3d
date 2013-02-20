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
// as_callfunc_arm.cpp
//
// These functions handle the actual calling of system functions on the arm platform
//
// Written by Fredrik Ehnbom in June 2009, based on as_callfunc_x86.cpp


// This code has to conform to both AAPCS and the modified ABI for iOS
//
// Reference:
//
// AAPCS: http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042d/IHI0042D_aapcs.pdf
// iOS: http://developer.apple.com/library/ios/documentation/Xcode/Conceptual/iPhoneOSABIReference/iPhoneOSABIReference.pdf


#include "as_config.h"

#ifndef AS_MAX_PORTABILITY
#ifdef AS_ARM

#include "as_callfunc.h"
#include "as_scriptengine.h"
#include "as_texts.h"
#include "as_tokendef.h"

BEGIN_AS_NAMESPACE

extern "C" asQWORD armFunc(const asDWORD *, int, asFUNCTION_t);
extern "C" asQWORD armFuncR0(const asDWORD *, int, asFUNCTION_t, asDWORD r0);
extern "C" asQWORD armFuncR0R1(const asDWORD *, int, asFUNCTION_t, asDWORD r0, asDWORD r1);
extern "C" asQWORD armFuncObjLast(const asDWORD *, int, asFUNCTION_t, asDWORD obj);
extern "C" asQWORD armFuncR0ObjLast(const asDWORD *, int, asFUNCTION_t, asDWORD r0, asDWORD obj);

asQWORD CallSystemFunctionNative(asCContext *context, asCScriptFunction *descr, void *obj, asDWORD *args, void *retPointer, asQWORD &/*retQW2*/)
{
	asCScriptEngine *engine = context->m_engine;
	asSSystemFunctionInterface *sysFunc = descr->sysFuncIntf;
	int callConv = sysFunc->callConv;

	asQWORD       retQW             = 0;
	asFUNCTION_t  func              = sysFunc->func;
	int           paramSize         = sysFunc->paramSize;
	asFUNCTION_t *vftable;

	if( sysFunc->hostReturnInMemory )
	{
		// The return is made in memory
		callConv++;
	}

	asDWORD paramBuffer[64+2];
	// Android needs to align 64bit types on even registers, but this isn't done on iOS or Windows Phone
	// TODO: optimize runtime: There should be a check for this in PrepareSystemFunction() so this 
	//                         doesn't have to be done for functions that don't have any 64bit types
#ifndef AS_ANDROID
	if( sysFunc->takesObjByVal )
#endif
	{
#ifdef AS_ANDROID
		// mask is used as a toggler to skip uneven registers.
		int mask = 1;

		// Check for object pointer as first argument
		switch( callConv )
		{
			case ICC_THISCALL:
			case ICC_CDECL_OBJFIRST:
			case ICC_VIRTUAL_THISCALL:
			case ICC_THISCALL_RETURNINMEM:
			case ICC_CDECL_OBJFIRST_RETURNINMEM:
			case ICC_VIRTUAL_THISCALL_RETURNINMEM:
				mask = 0;
				break;
			default:
				break;
		}
		// Check for hidden address in case of return by value
		if( sysFunc->hostReturnInMemory )
			mask = !mask;
#endif
		paramSize = 0;
		int spos = 0;
		int dpos = 2;
		for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
		{
			if( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() && !descr->parameterTypes[n].IsReference() )
			{
#ifdef COMPLEX_OBJS_PASSED_BY_REF
				if( descr->parameterTypes[n].GetObjectType()->flags & COMPLEX_MASK )
				{
					paramBuffer[dpos++] = args[spos++];
					paramSize++;
				}
				else
#endif
				{
#ifdef AS_ANDROID
					if( (descr->parameterTypes[n].GetObjectType()->flags & asOBJ_APP_CLASS_ALIGN8) &&
						((dpos & 1) == mask) )
					{
						// 64 bit value align
						dpos++;
						paramSize++;
					}
#endif
					// Copy the object's memory to the buffer
					memcpy(&paramBuffer[dpos], *(void**)(args+spos), descr->parameterTypes[n].GetSizeInMemoryBytes());

					// Delete the original memory
					engine->CallFree(*(char**)(args+spos));
					spos++;
					dpos += descr->parameterTypes[n].GetSizeInMemoryDWords();
					paramSize += descr->parameterTypes[n].GetSizeInMemoryDWords();
				}
			}
			else
			{
#ifdef AS_ANDROID
				// Should an alignment be performed?
				if( !descr->parameterTypes[n].IsObjectHandle() && 
					!descr->parameterTypes[n].IsReference() && 
					descr->parameterTypes[n].GetSizeOnStackDWords() == 2 && 
					((dpos & 1) == mask) )
				{
					// 64 bit value align
					dpos++;
					paramSize++;
				}
#endif

				// Copy the value directly
				paramBuffer[dpos++] = args[spos++];
				if( descr->parameterTypes[n].GetSizeOnStackDWords() > 1 )
					paramBuffer[dpos++] = args[spos++];
				paramSize += descr->parameterTypes[n].GetSizeOnStackDWords();
			}
		}
		// Keep a free location at the beginning
		args = &paramBuffer[2];
	}

	switch( callConv )
	{
	case ICC_CDECL_RETURNINMEM:     // fall through
	case ICC_STDCALL_RETURNINMEM:
		retQW = armFuncR0(args, paramSize<<2, func, (asDWORD)retPointer);
		break;
	case ICC_CDECL:     // fall through
	case ICC_STDCALL:
		retQW = armFunc(args, paramSize<<2, func);
		break;
	case ICC_THISCALL:  // fall through
	case ICC_CDECL_OBJFIRST:
		retQW = armFuncR0(args, paramSize<<2, func, (asDWORD)obj);
		break;
	case ICC_THISCALL_RETURNINMEM:
#ifdef __GNUC__
		// On GNUC the address where the return value will be placed should be put in R0
		retQW = armFuncR0R1(args, paramSize<<2, func, (asDWORD)retPointer, (asDWORD)obj);
#else
		// On Windows the R0 should always hold the object pointer, and the address for the return value comes after
		retQW = armFuncR0R1(args, paramSize<<2, func, (asDWORD)obj, (asDWORD)retPointer);
#endif
		break;
	case ICC_CDECL_OBJFIRST_RETURNINMEM:
		retQW = armFuncR0R1(args, paramSize<<2, func, (asDWORD)retPointer, (asDWORD)obj);
		break;
	case ICC_VIRTUAL_THISCALL:
		// Get virtual function table from the object pointer
		vftable = *(asFUNCTION_t**)obj;
		retQW = armFuncR0(args, paramSize<<2, vftable[FuncPtrToUInt(func)>>2], (asDWORD)obj);
		break;
	case ICC_VIRTUAL_THISCALL_RETURNINMEM:
		// Get virtual function table from the object pointer
		vftable = *(asFUNCTION_t**)obj;
#ifdef __GNUC__
		// On GNUC the address where the return value will be placed should be put in R0
		retQW = armFuncR0R1(args, (paramSize+1)<<2, vftable[FuncPtrToUInt(func)>>2], (asDWORD)retPointer, (asDWORD)obj);
#else
		// On Windows the R0 should always hold the object pointer, and the address for the return value comes after
		retQW = armFuncR0R1(args, (paramSize+1)<<2, vftable[FuncPtrToUInt(func)>>2], (asDWORD)obj, (asDWORD)retPointer);
#endif
		break;
	case ICC_CDECL_OBJLAST:
		retQW = armFuncObjLast(args, paramSize<<2, func, (asDWORD)obj);
		break;
	case ICC_CDECL_OBJLAST_RETURNINMEM:
		retQW = armFuncR0ObjLast(args, paramSize<<2, func, (asDWORD)retPointer, (asDWORD)obj);
		break;
	default:
		context->SetInternalException(TXT_INVALID_CALLING_CONVENTION);
	}

	return retQW;
}

END_AS_NAMESPACE

#endif // AS_ARM
#endif // AS_MAX_PORTABILITY




