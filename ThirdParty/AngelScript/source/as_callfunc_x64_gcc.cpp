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

/*
 * Implements the AMD64 calling convention for gcc-based 64bit Unices
 *
 * Author: Ionut "gargltk" Leonte <ileonte@bitdefender.com>
 *
 * Initial author: niteice
 */

#include "as_config.h"

#ifndef AS_MAX_PORTABILITY
#ifdef AS_X64_GCC

#include "as_scriptengine.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

enum argTypes { x64INTARG = 0, x64FLOATARG = 1 };
typedef asQWORD ( *funcptr_t )( void );

#define X64_MAX_ARGS             32
#define MAX_CALL_INT_REGISTERS    6
#define MAX_CALL_SSE_REGISTERS    8
#define X64_CALLSTACK_SIZE        ( X64_MAX_ARGS + MAX_CALL_SSE_REGISTERS + 3 )

// Note to self: Always remember to inform the used registers on the clobber line, 
// so that the gcc optimizer doesn't try to use them for other things

#define PUSH_LONG( val )                         \
	__asm__ __volatile__ (                       \
		"movq   %0, %%rax\n"                     \
		"pushq  %%rax"                           \
		:                                        \
		: "m" ( val )                            \
		: "%rax"                                 \
	)

#define ASM_GET_REG( name, dest )                \
	__asm__ __volatile__ (                       \
		"movq %" name ", %0\n"                   \
		:                                        \
		: "m" ( dest )                           \
		: name                                   \
	)

static void __attribute__((noinline)) GetReturnedXmm0Xmm1(asQWORD &a, asQWORD &b)
{
	__asm__ __volatile__ (
		"lea     %0, %%rax\n"
		"movq  %%xmm0, (%%rax)\n"
		"lea     %1, %%rdx\n"
		"movq  %%xmm1, (%%rdx)\n" 
		: // no optput
		: "m" (a), "m" (b)
		: "%rax", "%rdx", "%xmm0", "%xmm1"
	);
}

static asQWORD __attribute__((noinline)) X64_CallFunction( const asQWORD *args, int cnt, funcptr_t func ) 
{
	asQWORD   retval;
	funcptr_t call    = func;
	int       i       = 0;

	// Backup the stack pointer and then align it to 16 bytes.
	// The R15 register is guaranteed to maintain its value over function
	// calls, so it is safe for us to keep the original stack pointer here.
	__asm__ __volatile__ (
		"  movq %%rsp, %%r15 \n"
		"  movq %%rsp, %%rax \n"
		"  sub %0, %%rax \n"
		"  and $15, %%rax \n"
		"  sub %%rax, %%rsp \n"
		: : "r" ((asQWORD)cnt*8) 
		// Tell the compiler that we're using the RAX and R15.
		// This will make sure these registers are backed up by the compiler.
		: "%rax", "%r15", "%rsp");

	// Push the stack parameters
	for( i = MAX_CALL_INT_REGISTERS + MAX_CALL_SSE_REGISTERS; cnt-- > 0; i++ )
		PUSH_LONG( args[i] );

	// Populate integer and floating point parameters
	__asm__ __volatile__ (
		"  mov     (%%rax), %%rdi \n"
		"  mov    8(%%rax), %%rsi \n"
		"  mov   16(%%rax), %%rdx \n"
		"  mov   24(%%rax), %%rcx \n"
		"  mov   32(%%rax), %%r8 \n"
		"  mov   40(%%rax), %%r9 \n"
		"  add   $48, %%rax \n"
		"  movsd   (%%rax), %%xmm0 \n"
		"  movsd  8(%%rax), %%xmm1 \n"
		"  movsd 16(%%rax), %%xmm2 \n"
		"  movsd 24(%%rax), %%xmm3 \n"
		"  movsd 32(%%rax), %%xmm4 \n"
		"  movsd 40(%%rax), %%xmm5 \n"
		"  movsd 48(%%rax), %%xmm6 \n"
		"  movsd 56(%%rax), %%xmm7 \n"
		: 
		: "a" (args) // Pass args in rax
		: "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7", 
		  "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", 
		  // rsp and r15 is added too so the compiler doesn't try to use
		  // them to store anything over this piece of assembly
		  "%rsp", "%r15"); 
		
	// call the function with the arguments
	retval = call();

	// Restore the stack pointer
	__asm__ __volatile__ ("  mov %%r15, %%rsp \n" : : : "%r15", "%rsp");

	return retval;
}

// returns true if the given parameter is a 'variable argument'
static inline bool IsVariableArgument( asCDataType type )
{
	return ( type.GetTokenType() == ttQuestion ) ? true : false;
}

asQWORD CallSystemFunctionNative(asCContext *context, asCScriptFunction *descr, void *obj, asDWORD *args, void *retPointer, asQWORD &retQW2)
{
	asCScriptEngine            *engine             = context->engine;
	asSSystemFunctionInterface *sysFunc            = descr->sysFuncIntf;
	int                         callConv           = sysFunc->callConv;
	asQWORD                     retQW              = 0;
	asDWORD                    *stack_pointer      = args;
	funcptr_t                  *vftable            = NULL;
	int                         totalArgumentCount = 0;
	int                         n                  = 0;
	int                         param_post         = 0;
	int                         argIndex           = 0;
	funcptr_t                   func               = (funcptr_t)sysFunc->func;

	if( sysFunc->hostReturnInMemory ) 
	{
		// The return is made in memory
		callConv++;
	}

	// Determine the real function pointer in case of virtual method
	if ( obj && ( callConv == ICC_VIRTUAL_THISCALL || callConv == ICC_VIRTUAL_THISCALL_RETURNINMEM ) ) 
	{
		vftable = *((funcptr_t**)obj);
		func = vftable[FuncPtrToUInt(asFUNCTION_t(func)) >> 3];
	}

	// Determine the type of the arguments, and prepare the input array for the X64_CallFunction 
	asQWORD  paramBuffer[X64_CALLSTACK_SIZE] = { 0 };
	asBYTE	 argsType[X64_CALLSTACK_SIZE] = { 0 };

	switch ( callConv ) 
	{
		case ICC_CDECL_RETURNINMEM:
		case ICC_STDCALL_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			argsType[0] = x64INTARG;

			argIndex = 1;

			break;
		}
		case ICC_THISCALL:
		case ICC_VIRTUAL_THISCALL:
		case ICC_CDECL_OBJFIRST: 
		{
			paramBuffer[0] = (asPWORD)obj;
			argsType[0] = x64INTARG;

			argIndex = 1;

			break;
		}
		case ICC_THISCALL_RETURNINMEM:
		case ICC_VIRTUAL_THISCALL_RETURNINMEM:
		case ICC_CDECL_OBJFIRST_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			paramBuffer[1] = (asPWORD)obj;
			argsType[0] = x64INTARG;
			argsType[1] = x64INTARG;

			argIndex = 2;

			break;
		}
		case ICC_CDECL_OBJLAST: 
			param_post = 1;
			break;
		case ICC_CDECL_OBJLAST_RETURNINMEM: 
		{
			paramBuffer[0] = (asPWORD)retPointer;
			argsType[0] = x64INTARG;

			argIndex = 1;
			param_post = 1;

			break;
		}
	}

	int argumentCount = ( int )descr->parameterTypes.GetLength();
	for( int a = 0; a < argumentCount; ++a ) 
	{
		if( descr->parameterTypes[a].IsFloatType() && !descr->parameterTypes[a].IsReference() ) 
		{
			argsType[argIndex] = x64FLOATARG;
			memcpy(paramBuffer + argIndex, stack_pointer, sizeof(float));
			argIndex++;
			stack_pointer++;
		}
		else if( descr->parameterTypes[a].IsDoubleType() && !descr->parameterTypes[a].IsReference() ) 
		{
			argsType[argIndex] = x64FLOATARG;
			memcpy(paramBuffer + argIndex, stack_pointer, sizeof(double));
			argIndex++;
			stack_pointer += 2;
		}
		else if( IsVariableArgument( descr->parameterTypes[a] ) ) 
		{
			// The variable args are really two, one pointer and one type id
			argsType[argIndex] = x64INTARG;
			argsType[argIndex+1] = x64INTARG;
			memcpy(paramBuffer + argIndex, stack_pointer, sizeof(void*));
			memcpy(paramBuffer + argIndex + 1, stack_pointer + 2, sizeof(asDWORD));
			argIndex += 2;
			stack_pointer += 3;
		}
		else if( descr->parameterTypes[a].IsPrimitive() ||
		         descr->parameterTypes[a].IsReference() || 
		         descr->parameterTypes[a].IsObjectHandle() )
		{
			argsType[argIndex] = x64INTARG;
			if( descr->parameterTypes[a].GetSizeOnStackDWords() == 1 )
			{
				memcpy(paramBuffer + argIndex, stack_pointer, sizeof(asDWORD));
				stack_pointer++;
			}
			else
			{
				memcpy(paramBuffer + argIndex, stack_pointer, sizeof(asQWORD));
				stack_pointer += 2;
			}
			argIndex++;
		}
		else
		{
			// An object is being passed by value
			if( (descr->parameterTypes[a].GetObjectType()->flags & COMPLEX_MASK) ||
			    descr->parameterTypes[a].GetSizeInMemoryDWords() > 4 )
			{
				// Copy the address of the object
				argsType[argIndex] = x64INTARG;
				memcpy(paramBuffer + argIndex, stack_pointer, sizeof(asQWORD));
				argIndex++;
			}
			else if( descr->parameterTypes[a].GetObjectType()->flags & asOBJ_APP_CLASS_ALLINTS )
			{
				// Copy the value of the object
				if( descr->parameterTypes[a].GetSizeInMemoryDWords() > 2 )
				{
					argsType[argIndex] = x64INTARG;
					argsType[argIndex+1] = x64INTARG;
					memcpy(paramBuffer + argIndex, *(asDWORD**)stack_pointer, descr->parameterTypes[a].GetSizeInMemoryBytes());
					argIndex += 2;
				}
				else
				{
					argsType[argIndex] = x64INTARG;
					memcpy(paramBuffer + argIndex, *(asDWORD**)stack_pointer, descr->parameterTypes[a].GetSizeInMemoryBytes());
					argIndex++;
				}
				// Delete the original memory
				engine->CallFree(*(void**)stack_pointer);
			}
			else if( descr->parameterTypes[a].GetObjectType()->flags & asOBJ_APP_CLASS_ALLFLOATS )
			{
				// Copy the value of the object
				if( descr->parameterTypes[a].GetSizeInMemoryDWords() > 2 )
				{
					argsType[argIndex] = x64FLOATARG;
					argsType[argIndex+1] = x64FLOATARG;
					memcpy(paramBuffer + argIndex, *(asDWORD**)stack_pointer, descr->parameterTypes[a].GetSizeInMemoryBytes());
					argIndex += 2;
				}
				else
				{
					argsType[argIndex] = x64FLOATARG;
					memcpy(paramBuffer + argIndex, *(asDWORD**)stack_pointer, descr->parameterTypes[a].GetSizeInMemoryBytes());
					argIndex++;
				}
				// Delete the original memory
				engine->CallFree(*(void**)stack_pointer);
			}
			stack_pointer += 2;
		}
	}

	// For the CDECL_OBJ_LAST calling convention we need to add the object pointer as the last argument
	if( param_post )
	{
		paramBuffer[argIndex] = (asPWORD)obj;
		argsType[argIndex] = x64INTARG;
		argIndex++;
	}

	totalArgumentCount = argIndex;

	/*
	 * Q: WTF is going on here !?
	 *
	 * A: The idea is to pre-arange the parameters so that X64_CallFunction() can do
	 * it's little magic which must work regardless of how the compiler decides to
	 * allocate registers. Basically:
	 * - the first MAX_CALL_INT_REGISTERS entries in tempBuff will
	 *   contain the values/types of the x64INTARG parameters - that is the ones who
	 *   go into the registers. If the function has less then MAX_CALL_INT_REGISTERS
	 *   integer parameters then the last entries will be set to 0
	 * - the next MAX_CALL_SSE_REGISTERS entries will contain the float/double arguments
	 *   that go into the floating point registers. If the function has less than
	 *   MAX_CALL_SSE_REGISTERS floating point parameters then the last entries will
	 *   be set to 0
	 * - index MAX_CALL_INT_REGISTERS + MAX_CALL_SSE_REGISTERS marks the start of the
	 *   parameters which will get passed on the stack. These are added to the array
	 *   in reverse order so that X64_CallFunction() can simply push them to the stack
	 *   without the need to perform further tests
	 */
	asQWORD tempBuff[X64_CALLSTACK_SIZE] = { 0 };
	asBYTE  argsSet[X64_CALLSTACK_SIZE]  = { 0 };
	int     used_int_regs   = 0;
	int     used_sse_regs   = 0;
	int     used_stack_args = 0;
	int     idx             = 0;
	for ( n = 0; ( n < totalArgumentCount ) && ( used_int_regs < MAX_CALL_INT_REGISTERS ); n++ ) 
	{
		if ( argsType[n] == x64INTARG ) 
		{
			argsSet[n] = 1;
			tempBuff[idx++] = paramBuffer[n];
			used_int_regs++;
		}
	}
	idx = MAX_CALL_INT_REGISTERS;
	for ( n = 0; ( n < totalArgumentCount ) && ( used_sse_regs < MAX_CALL_SSE_REGISTERS ); n++ ) 
	{
		if ( argsType[n] == x64FLOATARG ) 
		{
			argsSet[n] = 1;
			tempBuff[idx++] = paramBuffer[n];
			used_sse_regs++;
		}
	}
	idx = MAX_CALL_INT_REGISTERS + MAX_CALL_SSE_REGISTERS;
	for ( n = totalArgumentCount - 1; n >= 0; n-- ) 
	{
		if ( !argsSet[n] ) 
		{
			tempBuff[idx++] = paramBuffer[n];
			used_stack_args++;
		}
	}

	retQW = X64_CallFunction( tempBuff, used_stack_args, func );
	ASM_GET_REG( "%rdx", retQW2 );

	// If the return is a float value we need to get the value from the FP register
	if( sysFunc->hostReturnFloat )
		GetReturnedXmm0Xmm1(retQW, retQW2);

	return retQW;
}

END_AS_NAMESPACE

#endif // AS_X64_GCC
#endif // AS_MAX_PORTABILITY

