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
// as_callfunc_xenon.cpp
//
// These functions handle the actual calling of system functions
//
// This version is Xenon specific
// Modified from as_callfunc_ppc.cpp by Laszlo Perneky Februar 2007
//
// Modified by Cyril Tissier March 2010:
// various fixes in 'float' args passing / function return
// properly handling 'double' type
// various fixes in asm ppcFunc
// fix for variable arguments
//
#include "as_config.h"

#ifndef AS_MAX_PORTABILITY
#if defined(AS_XENON)

#include "as_callfunc.h"
#include "as_scriptengine.h"
#include "as_texts.h"
#include "as_tokendef.h"

#include <stdio.h>
#include <stdlib.h>
#include <xtl.h>

BEGIN_AS_NAMESPACE

#define AS_PPC_MAX_ARGS         32
#define AS_MAX_REG_FLOATS       13
#define AS_MAX_REG_INTS         8
#define AS_PPC_THISCALL_REG     1
#define AS_PPC_RETURNINMEM_REG  1
#define AS_PPC_ENDOFARGS        1

// The array used to send values to the correct places.
// Contains a byte of argTypes to indicate the register type to load, or zero if end of arguments

extern "C" {
	enum argTypes
	{
		ppcENDARG = 0,
		ppcINTARG,
		ppcFLOATARG,
		ppcDOUBLEARG
	};
	static asBYTE ppcArgsType[AS_PPC_MAX_ARGS + AS_PPC_RETURNINMEM_REG + AS_PPC_THISCALL_REG + AS_PPC_ENDOFARGS];
	static asDWORD ppcArgs[AS_PPC_MAX_ARGS + AS_PPC_RETURNINMEM_REG + AS_PPC_THISCALL_REG];
}

#define PPC_LINKAGE_SIZE  (0x14)                                 // how big the PPC linkage area is in a stack frame

// Loads all data into the correct places and calls the function.
// ppcArgsType is an array containing a byte type (enum argTypes) for each argument.
// iStackArgSize is the size in bytes for how much data to put on the stack frame
//--------------------------------------------------------------------
asQWORD __declspec( naked ) ppcFunc(const asDWORD* pArgs, int iStackArgSize, asDWORD dwFunc)
{
	__asm
	{
//////////////////////////////////////////////////////////////////////////
// Prepare args
//////////////////////////////////////////////////////////////////////////
_ppcFunc:
		// setup stack
		// Read link register
		mflr    r12
		// Stack the link register
		stw     r12,-8(r1)
		// backup all registers we use in this fct
		std     r31,-10h(r1)
		std     r30,-18h(r1)
		std     r29,-20h(r1)
		std     r28,-28h(r1)
		std     r27,-30h(r1)
		std     r26,-38h(r1)
		std     r25,-40h(r1)
		std     r24,-48h(r1)
		std     r23,-50h(r1)
		std     r22,-58h(r1)
		std     r21,-60h(r1)
		// Move stack pointer
		stwu    r1,-0A0h(r1)

		mr r29, r3			//pArgs
		mr r30, r4			//iStackArgSize
		mr r27, r5			//dwFunc

		addi r31, r1, 14h	// stack args for next function call

		// Clear some registers
		sub r0, r0, r0
		// Counting of used/assigned GPR's
		mr  r23, r0
		// Counting of used/assigned Float Registers
		mr  r22, r0
		// Counting extra stack size
		mr  r21, r0

		// Fetch argument types array address
		lau r25, ppcArgsType
		lal r25, r25, ppcArgsType

		// Fetch arguments array address
		lau r26, ppcArgs
		lal r26, r26, ppcArgs

		// Begin loading and stacking registers
		subi r25, r25, 1

//////////////////////////////////////////////////////////////////////////
// Fetch the next argument
//////////////////////////////////////////////////////////////////////////
ppcNextArg:
		// Increment rArgTypePtr
		addi r25, r25, 1
		// Get data type
		lbz r24, 0(r25)

		// r24 holds the data type
		cmplwi cr6, r24, 0
		beq    cr6, ppcArgsEnd
		cmplwi cr6, r24, 1
		beq    cr6, ppcArgIsInteger
		cmplwi cr6, r24, 2
		beq    cr6, ppcArgIsFloat
		cmplwi cr6, r24, 3
		beq    cr6, ppcArgIsDouble

//////////////////////////////////////////////////////////////////////////
// Load and stack integer arguments
//////////////////////////////////////////////////////////////////////////
ppcArgIsInteger:
		// Get the arg from the stack
		lwz r12, 0(r26)

		// r23 holds the integer arg count so far
		cmplwi cr6, r23, 0
		beq    cr6, ppcLoadIntReg0
		cmplwi cr6, r23, 1
		beq    cr6, ppcLoadIntReg1
		cmplwi cr6, r23, 2
		beq    cr6, ppcLoadIntReg2
		cmplwi cr6, r23, 3
		beq    cr6, ppcLoadIntReg3
		cmplwi cr6, r23, 4
		beq    cr6, ppcLoadIntReg4
		cmplwi cr6, r23, 5
		beq    cr6, ppcLoadIntReg5
		cmplwi cr6, r23, 6
		beq    cr6, ppcLoadIntReg6
		cmplwi cr6, r23, 7
		beq    cr6, ppcLoadIntReg7

		// no more than 8 parameters
		b		ppcLoadIntRegUpd

		ppcLoadIntReg0:
		mr r3, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg1:
		mr r4, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg2:
		mr r5, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg3:
		mr r6, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg4:
		mr r7, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg5:
		mr r8, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg6:
		mr r9, r12
		b ppcLoadIntRegUpd
		ppcLoadIntReg7:
		mr r10, r12
		b ppcLoadIntRegUpd

		ppcLoadIntRegUpd:
		stw	    r12, 0(r31)			// push on the statck
		addi	r31, r31, 8			// inc stack by 1 reg

		addi r23, r23, 1			// Increment used int register count
		addi r29, r29, 4			// Increment rArgsPtr
		addi r26, r26, 4			// Increment rStackPtr
		b ppcNextArg				// Call next arg

//////////////////////////////////////////////////////////////////////////
// Load and stack float arguments
//////////////////////////////////////////////////////////////////////////
ppcArgIsFloat:
		// Get the arg from the stack
		lfs fr0, 0(r26)

		// r22 holds the float arg count so far
		cmplwi cr6, r22, 0
		beq    cr6, ppcLoadFloatReg0
		cmplwi cr6, r22, 1
		beq    cr6, ppcLoadFloatReg1
		cmplwi cr6, r22, 2
		beq    cr6, ppcLoadFloatReg2
		cmplwi cr6, r22, 3
		beq    cr6, ppcLoadFloatReg3
		cmplwi cr6, r22, 4
		beq    cr6, ppcLoadFloatReg4
		cmplwi cr6, r22, 5
		beq    cr6, ppcLoadFloatReg5
		cmplwi cr6, r22, 6
		beq    cr6, ppcLoadFloatReg6
		cmplwi cr6, r22, 7
		beq    cr6, ppcLoadFloatReg7
		cmplwi cr6, r22, 8
		beq    cr6, ppcLoadFloatReg8
		cmplwi cr6, r22, 9
		beq    cr6, ppcLoadFloatReg9
		cmplwi cr6, r22, 10
		beq    cr6, ppcLoadFloatReg10
		cmplwi cr6, r22, 11
		beq    cr6, ppcLoadFloatReg11
		cmplwi cr6, r22, 12
		beq    cr6, ppcLoadFloatReg12

		// no more than 12 parameters
		b		ppcLoadFloatRegUpd

		ppcLoadFloatReg0:
		fmr fr1, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg1:
		fmr fr2, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg2:
		fmr fr3, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg3:
		fmr fr4, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg4:
		fmr fr5, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg5:
		fmr fr6, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg6:
		fmr fr7, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg7:
		fmr fr8, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg8:
		fmr fr9, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg9:
		fmr fr10, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg10:
		fmr fr11, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg11:
		fmr fr12, fr0
		b ppcLoadFloatRegUpd
		ppcLoadFloatReg12:
		fmr fr13, fr0
		b ppcLoadFloatRegUpd

		ppcLoadFloatRegUpd:
		stfs	fr0, 0(r31)			// push on the statck
		addi	r31, r31, 8			// inc stack by 1 reg
		
		addi r22, r22, 1			// Increment used float register count
		addi r23, r23, 1			// Increment used int register count - a float reg eats up a GPR		
		addi r29, r29, 4			// Increment rArgsPtr		
		addi r26, r26, 4			// Increment rStackPtr
		b ppcNextArg				// Call next arg

//////////////////////////////////////////////////////////////////////////
// Load and stack double float arguments
//////////////////////////////////////////////////////////////////////////
ppcArgIsDouble:
		// Get the arg from the stack
		lfd fr0, 0(r26)

		// r22 holds the float arg count so far
		cmplwi cr6, r22, 0
		beq    cr6, ppcLoadDoubleReg0
		cmplwi cr6, r22, 1
		beq    cr6, ppcLoadDoubleReg1
		cmplwi cr6, r22, 2
		beq    cr6, ppcLoadDoubleReg2
		cmplwi cr6, r22, 3
		beq    cr6, ppcLoadDoubleReg3
		cmplwi cr6, r22, 4
		beq    cr6, ppcLoadDoubleReg4
		cmplwi cr6, r22, 5
		beq    cr6, ppcLoadDoubleReg5
		cmplwi cr6, r22, 6
		beq    cr6, ppcLoadDoubleReg6
		cmplwi cr6, r22, 7
		beq    cr6, ppcLoadDoubleReg7
		cmplwi cr6, r22, 8
		beq    cr6, ppcLoadDoubleReg8
		cmplwi cr6, r22, 9
		beq    cr6, ppcLoadDoubleReg9
		cmplwi cr6, r22, 10
		beq    cr6, ppcLoadDoubleReg10
		cmplwi cr6, r22, 11
		beq    cr6, ppcLoadDoubleReg11
		cmplwi cr6, r22, 12
		beq    cr6, ppcLoadDoubleReg12

		// no more than 12 parameters
		b      ppcLoadDoubleRegUpd

		ppcLoadDoubleReg0:
		fmr fr1, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg1:
		fmr fr2, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg2:
		fmr fr3, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg3:
		fmr fr4, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg4:
		fmr fr5, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg5:
		fmr fr6, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg6:
		fmr fr7, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg7:
		fmr fr8, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg8:
		fmr fr9, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg9:
		fmr fr10, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg10:
		fmr fr11, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg11:
		fmr fr12, fr0
		b ppcLoadDoubleRegUpd
		ppcLoadDoubleReg12:
		fmr fr13, fr0
		b ppcLoadDoubleRegUpd

		ppcLoadDoubleRegUpd:
		stfd	fr0, 0(r31)			// push on the statck
		addi	r31, r31, 8			// inc stack by 1 reg
		
		addi r22, r22, 1			// Increment used float register count		
		addi r23, r23, 1			// Increment used int register count
		addi r29, r29, 8			// Increment rArgsPtr
		addi r26, r26, 8			// Increment rStackPtr
		b ppcNextArg

//////////////////////////////////////////////////////////////////////////
// Finished
//////////////////////////////////////////////////////////////////////////
ppcArgsEnd:
		// Call the function
		mtctr r27
		bctrl

		// Function returned
		// Restore callers stack
		addi	r1, r1, 0A0h
		// Fetch return link to caller
		lwz     r12,-8(r1)
		mtlr	r12
		// restore all registers we used in this fct
		ld     r31,-10h(r1)
		ld     r30,-18h(r1)
		ld     r29,-20h(r1)
		ld     r28,-28h(r1)
		ld     r27,-30h(r1)
		ld     r26,-38h(r1)
		ld     r25,-40h(r1)
		ld     r24,-48h(r1)
		ld     r23,-50h(r1)
		ld     r22,-58h(r1)
		ld     r21,-60h(r1) 
		blr
	}
}




// Puts the arguments in the correct place in the stack array.
//-------------------------------------------------------------------
void stackArgs(const asDWORD *pArgs, int& iNumIntArgs, int& iNumFloatArgs, int& iNumDoubleArgs)
{
	asBYTE * pSrcArgs	= (asBYTE *) pArgs;		// pSrcArgs += (4*iArgWordPos);
	asBYTE * pDstArgs	= (asBYTE *) ppcArgs;	// pDstArgs += (4*iArgWordPos);

	for(int iArg = 0; iArg < AS_PPC_MAX_ARGS; iArg++)
	{
		if ( ppcArgsType[iArg] == ppcENDARG )
			break;

		if ( ppcArgsType[iArg] == ppcFLOATARG )
		{
			// stow float			
			*((float*) pDstArgs) = *((float*) pSrcArgs);
			pSrcArgs += 4;
			pDstArgs += 4;
			iNumFloatArgs++;
		}
		else if ( ppcArgsType[iArg] == ppcDOUBLEARG )
		{
			// stow double
			*((double*) pDstArgs) = *((double*) pSrcArgs);
			pSrcArgs += 8;
			pDstArgs += 8;
			iNumDoubleArgs++;
		}
		else if ( ppcArgsType[iArg] == ppcINTARG )
		{
			// stow register
			*((int*) pDstArgs) = *((int*) pSrcArgs);
			pSrcArgs += 4;
			pDstArgs += 4;
			iNumIntArgs++;
		}
	}
}

// Prepare the arg list for a CDecl funtion and then call it
//--------------------------------------------------------------------
asQWORD CallCDeclFunction(const asDWORD* pArgs, int iArgSize, asDWORD dwFunc)
{
	int iIntArgs = 0;
	int iFloatArgs = 0;
	int iDoubleArgs = 0;

	// Put the arguments in the correct places in the ppcArgs array
	if ( iArgSize > 0 )
		stackArgs( pArgs, iIntArgs, iFloatArgs, iDoubleArgs );
	
	return ppcFunc( ppcArgs, iArgSize, dwFunc);
}

// This function is identical to CallCDeclFunction, with the only difference that
// the value in the first parameter is the object
//--------------------------------------------------------------------
asQWORD CallThisCallFunction(const void* pObj, const asDWORD* pArgs, int iArgSize, asDWORD dwFunc )
{
	int iIntArgs = 0;
	int iFloatArgs = 0;
	int iDoubleArgs = 0;

	// Put the arguments in the correct places in the ppcArgs array /the this ptr is already in pArgs/
	if ( iArgSize > 0 )
		stackArgs( pArgs, iIntArgs, iFloatArgs, iDoubleArgs );

	return ppcFunc( ppcArgs, iArgSize, dwFunc);
}

// This function is identical to CallCDeclFunction, with the only difference that
// the value in the last parameter is the object
//--------------------------------------------------------------------
asQWORD CallThisCallFunction_objLast(const void* pObj, const asDWORD* pArgs, int iArgSize, asDWORD dwFunc)
{
	int iIntArgs = 0;
	int iFloatArgs = 0;
	int iDoubleArgs = 0;

	// Put the arguments in the correct places in the ppcArgs array /the this ptr is already in pArgs/
	if ( iArgSize > 0 )
		stackArgs( pArgs, iIntArgs, iFloatArgs, iDoubleArgs );

	int iNumArgs	= iIntArgs + iFloatArgs + iDoubleArgs;
	int iDWordCount = (iIntArgs + iFloatArgs + 2*iDoubleArgs);
	if ( iDWordCount < AS_PPC_MAX_ARGS )
	{
		ppcArgs[iDWordCount]  = (asDWORD)pObj;
		ppcArgsType[iNumArgs] = ppcINTARG;
	}

	return ppcFunc( ppcArgs, iArgSize + sizeof(pObj), dwFunc );
}

//--------------------------------------------------------------------
asDWORD GetReturnedFloat()
{
	asDWORD f;

	__asm
	{
		stfs fr1, f
	}

	return f;
}


asQWORD GetReturnedDouble()
//--------------------------------------------------------------------
{
	asQWORD f;

	__asm
	{
		stfd fr1, f
	}

	return f;
}

// returns true if the given parameter is a 'variable argument'
inline bool IsVariableArgument( asCDataType type )
{
	return (type.GetTokenType() == ttQuestion) ? true : false;
}

asQWORD CallSystemFunctionNative(asCContext *context, asCScriptFunction *descr, void *obj, asDWORD *args, void *retPointer, asQWORD &/*retQW2*/)
{
	// TODO: optimize: This memset shouldn't be necessary
	memset( ppcArgsType, 0, sizeof(ppcArgsType));

	asCScriptEngine            *engine  = context->engine;
	asSSystemFunctionInterface *sysFunc = descr->sysFuncIntf;	

	int callConv = sysFunc->callConv;

	asQWORD retQW = 0;

	void*    func       = (void*)sysFunc->func;
	int      paramSize  = sysFunc->paramSize;
	asDWORD* vftable;

	// We generate the parameter list to this, so it fits to teh callingconvention
	asDWORD fixedArgs[ AS_PPC_MAX_ARGS + AS_PPC_RETURNINMEM_REG + AS_PPC_THISCALL_REG ];
	memset(fixedArgs, 0, sizeof(fixedArgs));
	int argsPtr = 0;

	// If the function returns an object in memory, we allocate the memory and put the ptr to the front (will go to r3)
	if ( descr->returnType.IsObject() && !descr->returnType.IsReference() && !descr->returnType.IsObjectHandle() )
	{
		fixedArgs  [ argsPtr ] = (asDWORD)retPointer;
		ppcArgsType[ argsPtr ] = ppcINTARG;
		argsPtr++;
	}



	// If we have an object and it's not objectlast, then we put it az the first arg
	if ( obj
		&& callConv != ICC_CDECL_OBJLAST
		&& callConv != ICC_CDECL_OBJLAST_RETURNINMEM )
	{
		fixedArgs  [ argsPtr ] = (asDWORD)obj;
		ppcArgsType[ argsPtr ] = ppcINTARG;
		argsPtr++;
	}

	asASSERT(descr->parameterTypes.GetLength() <= AS_PPC_MAX_ARGS);

	// Parameter calculation magic
	asDWORD paramBuffer[64];
	if ( sysFunc->takesObjByVal )
	{
		paramSize = 0;
		int spos = 0;
		int dpos = 1;

		for ( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
		{
			// Parameter object by value
			if (  descr->parameterTypes[n].IsObject()
				&& !descr->parameterTypes[n].IsObjectHandle()
				&& !descr->parameterTypes[n].IsReference() )
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
					// Copy the object's memory to the buffer
					memcpy( &paramBuffer[dpos], *(void**)(args + spos), descr->parameterTypes[n].GetSizeInMemoryBytes() );
					// Delete the original memory
					engine->CallFree(*(char**)(args + spos) );

					spos++;
					dpos += descr->parameterTypes[n].GetSizeInMemoryDWords();
					paramSize += descr->parameterTypes[n].GetSizeInMemoryDWords();
				}
			}
			else
			{
				// Copy the value directly
				paramBuffer[dpos++] = args[spos++];
				if( descr->parameterTypes[n].GetSizeOnStackDWords() > 1 )
					paramBuffer[dpos++] = args[spos++];
				paramSize += descr->parameterTypes[n].GetSizeOnStackDWords();
			}

			// if this was a variable argument parameter, then account for the implicit typeID
			if( IsVariableArgument( descr->parameterTypes[n] ) )
			{
				// the TypeID is just a DWORD
				paramBuffer[dpos++] = args[spos++];
				++paramSize;
			}
		}

		// Keep a free location at the beginning
		args = &paramBuffer[1];
	}


	const asUINT paramCount = (asUINT)descr->parameterTypes.GetLength();

	asBYTE * pCurArgType		= (asBYTE*)&ppcArgsType[argsPtr];
	asBYTE * pCurFixedArgValue	= (asBYTE*)&fixedArgs[argsPtr];
	asBYTE * pCurStackArgValue	= (asBYTE*)args;

	for( asUINT n = 0; n < paramCount ; n++ )
	{		
		argsPtr++;

		if (descr->parameterTypes[n].IsFloatType() && !descr->parameterTypes[n].IsReference())
		{
			*pCurArgType++ = ppcFLOATARG;

			*((float*) pCurFixedArgValue) = *((float*) pCurStackArgValue);

			pCurFixedArgValue += 4;
			pCurStackArgValue += 4;
		}
		else if (descr->parameterTypes[n].IsDoubleType() && !descr->parameterTypes[n].IsReference())
		{
			*pCurArgType++ = ppcDOUBLEARG;

			*((double*) pCurFixedArgValue) = *((double*) pCurStackArgValue);

			pCurFixedArgValue += 8;
			pCurStackArgValue += 8;
		}
		else
		{
			// TODO: How should int64 and uint64 be passed natively? 
			//       Currently the code doesn't handle these types

			// TODO: The code also ignore the fact that large objects
			//       passed by value has been copied to the stack
			//       in the above loop.

			*pCurArgType++ = ppcINTARG;

			*((int*) pCurFixedArgValue) = *((int*) pCurStackArgValue);

			if( !descr->parameterTypes[n].IsReference() )
			{
				// If the arg is less that 4 bytes, then move the  
				// bytes to the higher bytes within the dword
				asUINT numBytes = descr->parameterTypes[n].GetSizeInMemoryBytes();
				if( numBytes == 1 )
				{
					pCurFixedArgValue[3] = pCurFixedArgValue[0];
					pCurFixedArgValue[0] = 0;
				}
				else if( numBytes == 2 )
				{
					*(asWORD*)&pCurFixedArgValue[2] = *(asWORD*)&pCurFixedArgValue[0];
					*(asWORD*)&pCurFixedArgValue[0] = 0;
				}
			}

			pCurFixedArgValue += 4;
			pCurStackArgValue += 4;
		}

		// if it is a variable argument, account for the typeID
		// implicitly add another parameter (AFTER the parameter above), for the TypeID
		if( IsVariableArgument(descr->parameterTypes[n]) )
		{			
			argsPtr++;

			*pCurArgType++ = ppcINTARG;

			*((int*) pCurFixedArgValue) = *((int*) pCurStackArgValue);

			pCurFixedArgValue += 4;
			pCurStackArgValue += 4;
		}
	}

	switch( callConv )
	{
	case ICC_CDECL:
	case ICC_CDECL_RETURNINMEM:
	case ICC_STDCALL:
	case ICC_STDCALL_RETURNINMEM:
		retQW = CallCDeclFunction( fixedArgs, argsPtr, (asDWORD)func );
		break;
	case ICC_THISCALL:
	case ICC_THISCALL_RETURNINMEM:
		retQW = CallThisCallFunction( obj, fixedArgs, argsPtr, (asDWORD)func );
		break;
	case ICC_VIRTUAL_THISCALL:
	case ICC_VIRTUAL_THISCALL_RETURNINMEM:
		// Get virtual function table from the object pointer
		vftable = *(asDWORD**)obj;
		retQW = CallThisCallFunction( obj, fixedArgs, argsPtr, vftable[asDWORD(func)>>2] );
		break;
	case ICC_CDECL_OBJLAST:
	case ICC_CDECL_OBJLAST_RETURNINMEM:
		retQW = CallThisCallFunction_objLast( obj, fixedArgs, argsPtr, (asDWORD)func );
		break;
	case ICC_CDECL_OBJFIRST:
	case ICC_CDECL_OBJFIRST_RETURNINMEM:
		retQW = CallThisCallFunction( obj, fixedArgs, argsPtr, (asDWORD)func );
		break;
	default:
		context->SetInternalException( TXT_INVALID_CALLING_CONVENTION );
	}

	// If the return is a float value we need to get the value from the FP register
	if( sysFunc->hostReturnFloat )
	{
		if( sysFunc->hostReturnSize == 1 )
			*(asDWORD*)&retQW = GetReturnedFloat();
		else
			retQW = GetReturnedDouble();
	}
	else if( sysFunc->hostReturnSize == 1 )
	{
		// Move the bits to the higher value to compensate for the adjustment that the caller does
		retQW <<= 32;
	}

	return retQW;
}

END_AS_NAMESPACE

#endif // AS_XENON
#endif // AS_MAX_PORTABILITY

//------------------------------------------------------------------

