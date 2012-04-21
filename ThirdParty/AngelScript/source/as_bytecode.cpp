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
// as_bytecode.cpp
//
// A class for constructing the final byte code
//

#include <stdio.h> // fopen(), fprintf(), fclose()

#include "as_config.h"

#ifndef AS_NO_COMPILER

#include "as_bytecode.h"
#include "as_debug.h" // mkdir()
#include "as_array.h"
#include "as_string.h"
#include "as_scriptengine.h"

BEGIN_AS_NAMESPACE

asCByteCode::asCByteCode(asCScriptEngine *engine)
{
	first = 0;
	last  = 0;
	largestStackUsed = -1;

	this->engine = engine;
}

asCByteCode::~asCByteCode()
{
	ClearAll();
}

void asCByteCode::Finalize()
{
	// verify the bytecode
	PostProcess();

	// Optimize the code (optionally)
	if( engine->ep.optimizeByteCode )
		Optimize();

	// Resolve jumps
	ResolveJumpAddresses();

	// Build line numbers buffer
	ExtractLineNumbers();
}

void asCByteCode::ClearAll()
{
	cByteInstruction *del = first;

	while( del ) 
	{
		first = del->next;
		engine->memoryMgr.FreeByteInstruction(del);
		del = first;
	}

	first = 0;
	last = 0;

	lineNumbers.SetLength(0);

	largestStackUsed = -1;

	temporaryVariables.SetLength(0);
}

void asCByteCode::InsertIfNotExists(asCArray<int> &vars, int var)
{
	if( !vars.Exists(var) )
		vars.PushLast(var);
}

void asCByteCode::GetVarsUsed(asCArray<int> &vars)
{
	cByteInstruction *curr = first;
	while( curr )
	{
		if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG )
		{
			InsertIfNotExists(vars, curr->wArg[0]);
			InsertIfNotExists(vars, curr->wArg[1]);
			InsertIfNotExists(vars, curr->wArg[2]);
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_rW_ARG    ||
			     asBCInfo[curr->op].type == asBCTYPE_wW_ARG    ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_W_ARG  ||
			     asBCInfo[curr->op].type == asBCTYPE_rW_DW_ARG ||
			     asBCInfo[curr->op].type == asBCTYPE_wW_DW_ARG ||
			     asBCInfo[curr->op].type == asBCTYPE_wW_QW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_W_DW_ARG )
		{
			InsertIfNotExists(vars, curr->wArg[0]);
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_rW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG )
		{
			InsertIfNotExists(vars, curr->wArg[0]);
			InsertIfNotExists(vars, curr->wArg[1]);
		}
		else if( curr->op == asBC_LoadThisR )
		{
			InsertIfNotExists(vars, 0);
		}

		curr = curr->next;
	}
}

bool asCByteCode::IsVarUsed(int offset)
{
	cByteInstruction *curr = first;
	while( curr )
	{
		// Verify all ops that use variables
		if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG )
		{
			if( curr->wArg[0] == offset || curr->wArg[1] == offset || curr->wArg[2] == offset )
				return true;
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_rW_ARG    ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_ARG    ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_W_ARG  ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_DW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_DW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_QW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_W_DW_ARG )
		{
			if( curr->wArg[0] == offset )
				return true;
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_rW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG )
		{
			if( curr->wArg[0] == offset || curr->wArg[1] == offset )
				return true;
		}
		else if( curr->op == asBC_LoadThisR )
		{
			if( offset == 0 )
				return true;
		}

		curr = curr->next;
	}

	return false;
}

void asCByteCode::ExchangeVar(int oldOffset, int newOffset)
{
	asASSERT(oldOffset != 0);

	cByteInstruction *curr = first;
	while( curr )
	{
		// Verify all ops that use variables
		if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG )
		{
			if( curr->wArg[0] == oldOffset )
				curr->wArg[0] = (short)newOffset;
			if( curr->wArg[1] == oldOffset )
				curr->wArg[1] = (short)newOffset;
			if( curr->wArg[2] == oldOffset )
				curr->wArg[2] = (short)newOffset;
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_rW_ARG    ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_ARG    ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_W_ARG  ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_DW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_DW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_wW_QW_ARG )
		{
			if( curr->wArg[0] == oldOffset )
				curr->wArg[0] = (short)newOffset;
		}
		else if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG ||
				 asBCInfo[curr->op].type == asBCTYPE_rW_rW_ARG )
		{
			if( curr->wArg[0] == oldOffset )
				curr->wArg[0] = (short)newOffset;
			if( curr->wArg[1] == oldOffset )
				curr->wArg[1] = (short)newOffset;
		}

		curr = curr->next;
	}
}

void asCByteCode::AddPath(asCArray<cByteInstruction *> &paths, cByteInstruction *instr, int stackSize)
{
	if( instr->marked )
	{
		// Verify the size of the stack
		asASSERT(instr->stackSize == stackSize);
	}
	else
	{
		// Add the destination to the code paths
		instr->marked = true;
		instr->stackSize = stackSize;
		paths.PushLast(instr);
	}
}

bool asCByteCode::IsCombination(cByteInstruction *curr, asEBCInstr bc1, asEBCInstr bc2)
{
	if( curr->op == bc1 && curr->next && curr->next->op == bc2 )
		return true;
	
	return false;
}

bool asCByteCode::IsCombination(cByteInstruction *curr, asEBCInstr bc1, asEBCInstr bc2, asEBCInstr bc3)
{
	if( curr->op == bc1 && 
		curr->next && curr->next->op == bc2 &&
		curr->next->next && curr->next->next->op == bc3 )
		return true;
	
	return false;
}

cByteInstruction *asCByteCode::ChangeFirstDeleteNext(cByteInstruction *curr, asEBCInstr bc)
{
	curr->op = bc;
	
	if( curr->next ) DeleteInstruction(curr->next);
	
	// Continue optimization with the instruction before the altered one
	if( curr->prev ) 
		return curr->prev;
	else
		return curr;
}

cByteInstruction *asCByteCode::DeleteFirstChangeNext(cByteInstruction *curr, asEBCInstr bc)
{
	asASSERT( curr->next );
	
	cByteInstruction *instr = curr->next;
	instr->op = bc;
	
	DeleteInstruction(curr);
	
	// Continue optimization with the instruction before the altered one
	if( instr->prev ) 
		return instr->prev;
	else
		return instr;
}

void asCByteCode::InsertBefore(cByteInstruction *before, cByteInstruction *instr)
{
	asASSERT(instr->next == 0);
	asASSERT(instr->prev == 0);

	if( before->prev ) before->prev->next = instr;
	instr->prev = before->prev;
	before->prev = instr;
	instr->next = before;

	if( first == before ) first = instr;
}

void asCByteCode::RemoveInstruction(cByteInstruction *instr)
{
	if( instr == first ) first = first->next;
	if( instr == last ) last = last->prev;

	if( instr->prev ) instr->prev->next = instr->next;
	if( instr->next ) instr->next->prev = instr->prev;

	instr->next = 0;
	instr->prev = 0;
}

bool asCByteCode::CanBeSwapped(cByteInstruction *curr)
{
	if( !curr || !curr->next || !curr->next->next ) return false;
	if( curr->next->next->op != asBC_SwapPtr ) return false;

	cByteInstruction *next = curr->next;

	if( curr->op != asBC_PshNull &&
		curr->op != asBC_PshVPtr &&
		curr->op != asBC_PSF )
		return false;

	if( next->op != asBC_PshNull &&
		next->op != asBC_PshVPtr &&
		next->op != asBC_PSF )
		return false;

	return true;
}

cByteInstruction *asCByteCode::GoBack(cByteInstruction *curr)
{
	// Go back 2 instructions
	if( !curr ) return 0;
	if( curr->prev ) curr = curr->prev;
	if( curr->prev ) curr = curr->prev;
	return curr;
}

bool asCByteCode::PostponeInitOfTemp(cByteInstruction *curr, cByteInstruction **next)
{
	// This is not done for pointers
	if( (curr->op != asBC_SetV4 && curr->op != asBC_SetV8) || 
		!IsTemporary(curr->wArg[0]) ) return false;

	// Move the initialization to just before it's use. 
	// Don't move it beyond any labels or jumps.
	cByteInstruction *use = curr->next;
	while( use )
	{
		if( IsTempVarReadByInstr(use, curr->wArg[0]) )
			break;

		if( IsTempVarOverwrittenByInstr(use, curr->wArg[0]) )
			return false;

		if( IsInstrJmpOrLabel(use) )
			return false;

		use = use->next;
	}

	if( use && use->prev != curr )
	{
		*next = curr->next;

		// Move the instruction
		RemoveInstruction(curr);
		InsertBefore(use, curr);

		// Try a RemoveUnusedValue to see if it can be combined with the other 
		cByteInstruction *temp;
		if( RemoveUnusedValue(curr, &temp) )
		{
			*next = GoBack(*next);
			return true;
		}
		
		// Return the instructions to its original position as it wasn't useful
		RemoveInstruction(curr);
		InsertBefore(*next, curr);
	}

	return false;
}

bool asCByteCode::RemoveUnusedValue(cByteInstruction *curr, cByteInstruction **next)
{
	// TODO: runtime optimize: Should work for 64bit types as well

	// The value isn't used for anything
	if( (asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG ||
		 asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG    ||
		 asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG ||
		 asBCInfo[curr->op].type == asBCTYPE_wW_ARG       ||
		 asBCInfo[curr->op].type == asBCTYPE_wW_DW_ARG    ||
		 asBCInfo[curr->op].type == asBCTYPE_wW_QW_ARG) &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr, curr->wArg[0]) &&
		curr->op != asBC_FREE ) // Can't remove the FREE instruction
	{
		if( curr->op == asBC_LdGRdR4 && IsTempRegUsed(curr) )
		{
			curr->op = asBC_LDG;
			*next = GoBack(curr);
			return true;
		}

		*next = GoBack(DeleteInstruction(curr));
		return true;
	}

	// TODO: runtime optimize: There should be one for doubles as well
	// The value is immediately used and then never again
	if( curr->op == asBC_SetV4 &&
		curr->next && 
		(curr->next->op == asBC_CMPi ||
		 curr->next->op == asBC_CMPf ||
		 curr->next->op == asBC_CMPu) &&
		curr->wArg[0] == curr->next->wArg[1] &&
		(IsTemporary(curr->wArg[0]) &&                       // The variable is temporary and never used again
		 !IsTempVarRead(curr->next, curr->wArg[0])) )
	{
		if(      curr->next->op == asBC_CMPi ) curr->next->op = asBC_CMPIi;
		else if( curr->next->op == asBC_CMPf ) curr->next->op = asBC_CMPIf;
		else if( curr->next->op == asBC_CMPu ) curr->next->op = asBC_CMPIu;
		curr->next->size = asBCTypeSize[asBCInfo[asBC_CMPIi].type];
		curr->next->arg = curr->arg;
		*next = GoBack(DeleteInstruction(curr));
		return true;
	}
	
	// The value is immediately used and then never again
	if( curr->op == asBC_SetV4 &&
		curr->next && 
		(curr->next->op == asBC_ADDi ||
		 curr->next->op == asBC_SUBi ||
		 curr->next->op == asBC_MULi ||
		 curr->next->op == asBC_ADDf ||
		 curr->next->op == asBC_SUBf ||
		 curr->next->op == asBC_MULf) &&
		curr->wArg[0] == curr->next->wArg[2] &&
		(curr->next->wArg[0] == curr->wArg[0] ||        // The variable is overwritten
		 (IsTemporary(curr->wArg[0]) &&                 // The variable is temporary and never used again
		  !IsTempVarRead(curr->next, curr->wArg[0]))) )
	{
		if(      curr->next->op == asBC_ADDi ) curr->next->op = asBC_ADDIi;
		else if( curr->next->op == asBC_SUBi ) curr->next->op = asBC_SUBIi;
		else if( curr->next->op == asBC_MULi ) curr->next->op = asBC_MULIi;
		else if( curr->next->op == asBC_ADDf ) curr->next->op = asBC_ADDIf;
		else if( curr->next->op == asBC_SUBf ) curr->next->op = asBC_SUBIf;
		else if( curr->next->op == asBC_MULf ) curr->next->op = asBC_MULIf;
		curr->next->size = asBCTypeSize[asBCInfo[asBC_ADDIi].type];
		curr->next->arg = curr->arg;
		*next = GoBack(DeleteInstruction(curr));
		return true;
	}

	if( curr->op == asBC_SetV4 &&
		curr->next && 
		(curr->next->op == asBC_ADDi ||
		 curr->next->op == asBC_MULi ||
		 curr->next->op == asBC_ADDf ||
		 curr->next->op == asBC_MULf) &&
		curr->wArg[0] == curr->next->wArg[1] &&
		(curr->next->wArg[0] == curr->wArg[0] ||        // The variable is overwritten
		 (IsTemporary(curr->wArg[0]) &&                 // The variable is temporary and never used again
		  !IsTempVarRead(curr->next, curr->wArg[0]))) )
	{
		if(      curr->next->op == asBC_ADDi ) curr->next->op = asBC_ADDIi;
		else if( curr->next->op == asBC_MULi ) curr->next->op = asBC_MULIi;
		else if( curr->next->op == asBC_ADDf ) curr->next->op = asBC_ADDIf;
		else if( curr->next->op == asBC_MULf ) curr->next->op = asBC_MULIf;
		curr->next->size = asBCTypeSize[asBCInfo[asBC_ADDIi].type];
		curr->next->arg = curr->arg;

		// The order of the operands are changed
		curr->next->wArg[1] = curr->next->wArg[2];

		*next = GoBack(DeleteInstruction(curr));
		return true;
	}

	// The values is immediately moved to another variable and then not used again
	if( (asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG || 
		 asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG) && 
		curr->next && curr->next->op == asBC_CpyVtoV4 &&
		curr->wArg[0] == curr->next->wArg[1] && 
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->wArg[0] = curr->next->wArg[0];
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}

	// The constant value is immediately moved to another variable and then not used again
	if( curr->op == asBC_SetV4 && curr->next && curr->next->op == asBC_CpyVtoV4 &&
		curr->wArg[0] == curr->next->wArg[1] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->wArg[0] = curr->next->wArg[0];
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}

	// The register is copied to a temp variable and then back to the register again without being used afterwards
	if( curr->op == asBC_CpyRtoV4 && curr->next && curr->next->op == asBC_CpyVtoR4 &&
		curr->wArg[0] == curr->next->wArg[0] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		// Delete both instructions
		DeleteInstruction(curr->next);
		*next = GoBack(DeleteInstruction(curr));
		return true;
	}

	// The global value is copied to a temp and then immediately pushed on the stack
	if( curr->op == asBC_CpyGtoV4 && curr->next && curr->next->op == asBC_PshV4 &&
		curr->wArg[0] == curr->next->wArg[0] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->op = asBC_PshG4;
		curr->size = asBCTypeSize[asBCInfo[asBC_PshG4].type];
		curr->stackInc = asBCInfo[asBC_PshG4].stackInc;
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}

	// The constant is copied to a temp and then immediately pushed on the stack
	if( curr->op == asBC_SetV4 && curr->next && curr->next->op == asBC_PshV4 &&
		curr->wArg[0] == curr->next->wArg[0] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->op = asBC_PshC4;
		curr->stackInc = asBCInfo[asBC_PshC4].stackInc;
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}
	if( curr->op == asBC_SetV8 && curr->next && curr->next->op == asBC_PshV8 &&
		curr->wArg[0] == curr->next->wArg[0] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->op = asBC_PshC8;
		curr->stackInc = asBCInfo[asBC_PshC8].stackInc;
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}

	// The constant is copied to a global variable and then never used again
	if( curr->op == asBC_SetV4 && curr->next && curr->next->op == asBC_CpyVtoG4 &&
		curr->wArg[0] == curr->next->wArg[0] &&
		IsTemporary(curr->wArg[0]) &&
		!IsTempVarRead(curr->next, curr->wArg[0]) )
	{
		curr->op = asBC_SetG4;
		curr->size = asBCTypeSize[asBCInfo[asBC_SetG4].type];
		*(((asDWORD*)&curr->arg)+AS_PTR_SIZE) = *ARG_DW(curr->arg);
		*ARG_PTR(curr->arg) = *ARG_PTR(curr->next->arg);
		DeleteInstruction(curr->next);
		*next = GoBack(curr);
		return true;
	}

	return false;
}

bool asCByteCode::IsTemporary(short offset)
{
	for( asUINT n = 0; n < temporaryVariables.GetLength(); n++ )
		if( temporaryVariables[n] == offset )
			return true;

	return false;
}

int asCByteCode::Optimize()
{
	// TODO: runtime optimize: The optimizer should be able to inline function calls.
	//                         If the called function has only a few instructions, the function call should be inlined.
	//                         This is especially useful with the factory stubs used for template types and script classes.

	// TODO: runtime optimize: Need a bytecode BC_AddRef so that BC_CALLSYS doesn't have to be used for this trivial call
	
	// TODO: runtime optimize: A single bytecode for incrementing a variable, comparing, and jumping can probably improve 
	//                         loops a lot. How often do these loops really occur?

	// TODO: runtime optimize: VAR + GET... should be optimized if the only instructions between them are trivial, i.e. no 
	//                         function calls that can suspend the execution.

	cByteInstruction *instr = first;
	while( instr )
	{
		cByteInstruction *curr = instr;
		instr = instr->next;

		// Remove or combine instructions 
		if( RemoveUnusedValue(curr, &instr) ) continue;

		// Postpone initializations so that they may be combined in the second pass
		if( PostponeInitOfTemp(curr, &instr) ) continue;

		// XXX x, YYY y, SwapPtr -> YYY y, XXX x
		if( CanBeSwapped(curr) )
		{
			// Delete SwapPtr
			DeleteInstruction(instr->next);

			// Swap instructions
			RemoveInstruction(instr);
			InsertBefore(curr, instr);

			instr = GoBack(instr);
		}
		// T??, ClrHi -> T??
		else if( IsCombination(curr, asBC_TZ , asBC_ClrHi) ||
				 IsCombination(curr, asBC_TNZ, asBC_ClrHi) ||
				 IsCombination(curr, asBC_TS , asBC_ClrHi) ||
				 IsCombination(curr, asBC_TNS, asBC_ClrHi) ||
				 IsCombination(curr, asBC_TP , asBC_ClrHi) ||
				 IsCombination(curr, asBC_TNP, asBC_ClrHi) )
		{
			// Remove the ClrHi instruction, since the test instructions always clear the top bytes anyway
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// ClrHi, JZ -> JLowZ
		else if( IsCombination(curr, asBC_ClrHi, asBC_JZ) )
		{
			DeleteInstruction(curr);
			instr->op = asBC_JLowZ;
			instr = GoBack(instr);
		}
		// ClrHi, JNZ -> JLowNZ
		else if( IsCombination(curr, asBC_ClrHi, asBC_JNZ) )
		{
			DeleteInstruction(curr);
			instr->op = asBC_JLowNZ;
			instr = GoBack(instr);
		}
		// PGA, RDSPtr -> PshGPtr
		else if( IsCombination(curr, asBC_PGA, asBC_RDSPtr) )
		{
			curr->op = asBC_PshGPtr;
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// ChkRefS, RDSPtr -> RDSPtr, CHKREF
		else if( IsCombination(curr, asBC_ChkRefS, asBC_RDSPtr) )
		{
			// This exchange removes one pointer dereference, and also 
			// makes it easier to completely remove the CHKREF instruction
			curr->op = asBC_RDSPtr;
			instr->op = asBC_CHKREF;
			instr = GoBack(curr);
		}
		// CHKREF, ADDSi -> ADDSi
		// CHKREF, RDSPtr -> RDSPtr
		else if( IsCombination(curr, asBC_CHKREF, asBC_ADDSi) ||
			     IsCombination(curr, asBC_CHKREF, asBC_RDSPtr) )
		{
			// As ADDSi & RDSPtr already checks the pointer, the CHKREF instruction is unnecessary
			DeleteInstruction(curr);
			instr = GoBack(instr);
		}
		// ADDSi, CHKREF -> ADDSi
		else if( IsCombination(curr, asBC_ADDSi, asBC_CHKREF) )
		{
			// As ADDSi is guaranteed to work on valid pointers, then CHKREF is not necessary
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PshVPtr 0, ADDSi, PopRPtr -> LoadThisR
		else if( IsCombination(curr, asBC_PshVPtr, asBC_ADDSi) &&
		         IsCombination(instr, asBC_ADDSi, asBC_PopRPtr) &&
				 curr->wArg[0] == 0 )
		{
			DeleteInstruction(curr);
			instr = GoBack(ChangeFirstDeleteNext(instr, asBC_LoadThisR));
		}
		// TODO: runtime optimize: PshVPtr x, PopRPtr -> LoadRObjR x, 0
		// PshVPtr x, ADDSi, PopRPtr -> LoadRObjR
		else if( IsCombination(curr, asBC_PshVPtr, asBC_ADDSi) &&
		         IsCombination(instr, asBC_ADDSi, asBC_PopRPtr) &&
				 curr->wArg[0] != 0 )
		{
			curr->op = asBC_LoadRObjR;
			curr->size = asBCTypeSize[asBCInfo[asBC_LoadRObjR].type];
			curr->stackInc = asBCInfo[asBC_LoadRObjR].stackInc;
			curr->wArg[1] = instr->wArg[0];
			*(asDWORD*)&curr->arg = *(asDWORD*)&instr->arg;
			DeleteInstruction(instr->next);
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PSF x, REFCPY -> RefCpyV x
		else if( IsCombination(curr, asBC_PSF, asBC_REFCPY) )
		{
			instr->op = asBC_RefCpyV;
			instr->wArg[0] = curr->wArg[0];
			instr->stackInc = asBCInfo[asBC_LoadVObjR].stackInc;
			DeleteInstruction(curr);
			instr = GoBack(instr);
		}
		// PshNull, RefCpyV, PopPtr -> FREE
		else if( IsCombination(curr, asBC_PshNull, asBC_RefCpyV) &&
			     IsCombination(instr, asBC_RefCpyV, asBC_PopPtr) )
		{
			DeleteInstruction(curr);
			instr->op = asBC_FREE;
			DeleteInstruction(instr->next);
			instr = GoBack(instr);
		}
		// PSF x, ADDSi, PopRPtr -> LoadVObjR
		else if( IsCombination(curr, asBC_PSF, asBC_ADDSi) &&
		         IsCombination(instr, asBC_ADDSi, asBC_PopRPtr) )
		{
			curr->op = asBC_LoadVObjR;
			curr->size = asBCTypeSize[asBCInfo[asBC_LoadVObjR].type];
			curr->stackInc = asBCInfo[asBC_LoadVObjR].stackInc;
			curr->wArg[1] = instr->wArg[0];
			*(asDWORD*)&curr->arg = *(asDWORD*)&instr->arg;
			DeleteInstruction(instr->next);
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// LDG x, WRTV4 y -> CpyVtoG4 y, x
		else if( IsCombination(curr, asBC_LDG, asBC_WRTV4) && !IsTempRegUsed(instr) )
		{
			curr->op = asBC_CpyVtoG4;
			curr->size = asBCTypeSize[asBCInfo[asBC_CpyVtoG4].type];
			curr->wArg[0] = instr->wArg[0];

			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// LDG x, RDR4 y -> CpyGtoV4 y, x
		else if( IsCombination(curr, asBC_LDG, asBC_RDR4) )
		{
			if( !IsTempRegUsed(instr) )
				curr->op = asBC_CpyGtoV4;
			else 
				curr->op = asBC_LdGRdR4;
			curr->size = asBCTypeSize[asBCInfo[asBC_CpyGtoV4].type];
			curr->wArg[0] = instr->wArg[0];

			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// LDV x, INCi -> IncVi x
		else if( IsCombination(curr, asBC_LDV, asBC_INCi) && !IsTempRegUsed(instr) )
		{
			curr->op = asBC_IncVi;
			
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// LDV x, DECi -> DecVi x
		else if( IsCombination(curr, asBC_LDV, asBC_DECi) && !IsTempRegUsed(instr) )
		{
			curr->op = asBC_DecVi;
			
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PopPtr, RET b -> RET b
		else if( IsCombination(curr, asBC_PopPtr, asBC_RET) )
		{
			// We don't combine the PopPtr+RET because RET first restores
			// the previous stack pointer and then pops the arguments

			// Delete PopPtr
			instr = GoBack(DeleteInstruction(curr));
		}
		// Delete JitEntry if the JIT instructions are not supposed to be included
		else if( curr->op == asBC_JitEntry && !engine->ep.includeJitInstructions )
		{
			instr = GoBack(DeleteInstruction(curr));
		}
		// SUSPEND, JitEntry, SUSPEND -> SUSPEND
		// LINE, JitEntry, LINE -> LINE
		else if( (IsCombination(curr, asBC_SUSPEND, asBC_JitEntry) && IsCombination(instr, asBC_JitEntry, asBC_SUSPEND)) || 
			     (IsCombination(curr, asBC_LINE, asBC_JitEntry) && IsCombination(instr, asBC_JitEntry, asBC_LINE)) )
		{
			// Delete the two first instructions
			DeleteInstruction(instr);
			instr = GoBack(DeleteInstruction(curr));
		}
		// SUSPEND, SUSPEND -> SUSPEND
		// LINE, LINE -> LINE
		else if( IsCombination(curr, asBC_SUSPEND, asBC_SUSPEND) || 
			     IsCombination(curr, asBC_LINE, asBC_LINE) ) 
		{
			// Delete the first instruction
			instr = GoBack(DeleteInstruction(curr));
		}
		// SUSPEND, Block, SUSPEND -> Block, SUSPEND
		else if( (IsCombination(curr, asBC_SUSPEND, asBC_Block) && IsCombination(instr, asBC_Block, asBC_SUSPEND)) ||
			     (IsCombination(curr, asBC_LINE, asBC_Block) && IsCombination(instr, asBC_Block, asBC_LINE)) )
		{
			// Delete the first instruction
			instr = GoBack(DeleteInstruction(curr));
		}
		// VAR a, GETREF 0 -> PSF a
		else if( IsCombination(curr, asBC_VAR, asBC_GETREF) && instr->wArg[0] == 0 )
		{
			instr = GoBack(ChangeFirstDeleteNext(curr, asBC_PSF));
		}
		// PGA, CHKREF -> PGA 
		// PSF, CHKREF -> PSF
		else if( IsCombination(curr, asBC_PGA, asBC_CHKREF) ||
			     IsCombination(curr, asBC_PSF, asBC_CHKREF) )
		{
			// Delete CHKREF since PGA and PSF always pushes a valid address on the stack
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PGA, ChkRefS, CHKREF -> PGA, ChkRefS
		else if( IsCombination(curr, asBC_PGA, asBC_ChkRefS) &&
			     IsCombination(instr, asBC_ChkRefS, asBC_CHKREF) )
		{
			// Delete CHKREF since PGA always pushes a valid address on the stack
			DeleteInstruction(instr->next);
			instr = GoBack(curr);
		}
		// PSF, FREE -> FREE, PSF
		else if( IsCombination(curr, asBC_PSF, asBC_FREE) )
		{
			// This pattern usually happens when a function returns an object, or handle
			// and then releases a temporary variable, possibly used in one of the arguments.
			// By swapping the order of these instructions, the code can be further optimized
			// to combine the PSF with the following instructions
			RemoveInstruction(instr);
			InsertBefore(curr, instr);
			instr = GoBack(instr);
		}
		// PshVPtr y, PopPtr -> nothing
		// PSF y    , PopPtr -> nothing
		// VAR y    , PopPtr -> nothing
		// PshNull  , PopPtr -> nothing
		// PshRPtr  , PopPtr -> nothing
		else if( IsCombination(curr, asBC_PshRPtr, asBC_PopPtr) ||
			     IsCombination(curr, asBC_PSF    , asBC_PopPtr) ||
				 IsCombination(curr, asBC_VAR    , asBC_PopPtr) || 
				 IsCombination(curr, asBC_PshVPtr, asBC_PopPtr) ||
			     IsCombination(curr, asBC_PshNull, asBC_PopPtr) )
		{
			// A pointer is pushed on the stack then immediately removed
			// Remove both instructions as they cancel each other
			cByteInstruction *instr2 = instr->next;
			DeleteInstruction(curr);
			DeleteInstruction(instr);
			instr = GoBack(instr2);
		}
// Begin PATTERN
		// T**; J** +x -> J** +x
		else if( IsCombination(curr, asBC_TZ , asBC_JZ ) || 
			     IsCombination(curr, asBC_TNZ, asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JNZ));
		else if( IsCombination(curr, asBC_TNZ, asBC_JZ ) ||
			     IsCombination(curr, asBC_TZ , asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JZ));
		else if( IsCombination(curr, asBC_TS , asBC_JZ ) ||
			     IsCombination(curr, asBC_TNS, asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JNS));
		else if( IsCombination(curr, asBC_TNS, asBC_JZ ) ||
			     IsCombination(curr, asBC_TS , asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JS));
		else if( IsCombination(curr, asBC_TP , asBC_JZ ) ||
			     IsCombination(curr, asBC_TNP, asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JNP));
		else if( IsCombination(curr, asBC_TNP, asBC_JZ ) ||
			     IsCombination(curr, asBC_TP , asBC_JNZ) )
			instr = GoBack(DeleteFirstChangeNext(curr, asBC_JP));
// End PATTERN
		// JMP +0 -> remove
		else if( IsCombination(curr, asBC_JMP, asBC_LABEL) && *(int*)&curr->arg == instr->wArg[0] )
			instr = GoBack(DeleteInstruction(curr));
		// PSF, RDSPtr -> PshVPtr
		else if( IsCombination(curr, asBC_PSF, asBC_RDSPtr) )
		{
			curr->op = asBC_PshVPtr;
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PSF, ChkRefS, RDSPtr -> PshVPtr, CHKREF
		else if( IsCombination(curr, asBC_PSF, asBC_ChkRefS) &&
		         IsCombination(instr, asBC_ChkRefS, asBC_RDSPtr) )
		{
			curr->op = asBC_PshVPtr;
			instr->op = asBC_CHKREF;
			DeleteInstruction(instr->next);
			instr = GoBack(curr);
		}
		// PSF, ChkRefS, PopPtr -> ChkNullV
		else if( IsCombination(curr, asBC_PSF, asBC_ChkRefS) &&
		         IsCombination(instr, asBC_ChkRefS, asBC_PopPtr) )
		{
			curr->op = asBC_ChkNullV;
			curr->stackInc = 0;
			// Delete the PopPtr instruction
			DeleteInstruction(instr->next);
			// Delete the ChkRefS instruction
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
		// PshVPtr, CHKREF, PopPtr -> ChkNullV
		else if( IsCombination(curr, asBC_PshVPtr, asBC_CHKREF) &&
		         IsCombination(instr, asBC_CHKREF, asBC_PopPtr) )
		{
			curr->op = asBC_ChkNullV;
			curr->stackInc = 0;
			DeleteInstruction(instr->next);
			DeleteInstruction(instr);
			instr = GoBack(curr);
		}
	}

	return 0;
}

bool asCByteCode::IsTempVarReadByInstr(cByteInstruction *curr, int offset)
{
	// Which instructions read from variables?
	if( asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG && 
		(curr->wArg[1] == offset || curr->wArg[2] == offset) )
		return true;
	else if( (asBCInfo[curr->op].type == asBCTYPE_rW_ARG    ||
			  asBCInfo[curr->op].type == asBCTYPE_rW_DW_ARG ||
			  asBCInfo[curr->op].type == asBCTYPE_rW_QW_ARG ||
			  asBCInfo[curr->op].type == asBCTYPE_rW_W_DW_ARG ||
			  curr->op == asBC_FREE) &&  // FREE both read and write to the variable
			  curr->wArg[0] == offset )
		return true;
	else if( (asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG) &&
			 curr->wArg[1] == offset )
		return true;
	else if( asBCInfo[curr->op].type == asBCTYPE_rW_rW_ARG &&
			 ((signed)curr->wArg[0] == offset || (signed)curr->wArg[1] == offset) )
		return true;
	else if( curr->op == asBC_LoadThisR && offset == 0 )
		return true;

	return false;
}

bool asCByteCode::IsInstrJmpOrLabel(cByteInstruction *curr)
{
	if( curr->op == asBC_JS      ||
		curr->op == asBC_JNS     ||
		curr->op == asBC_JP      ||
		curr->op == asBC_JNP     ||
		curr->op == asBC_JMPP    ||
		curr->op == asBC_JMP     ||
		curr->op == asBC_JZ      ||
		curr->op == asBC_JNZ     ||
		curr->op == asBC_JLowZ   ||
		curr->op == asBC_JLowNZ  ||
		curr->op == asBC_LABEL   )
		return true;

	return false;
}

bool asCByteCode::IsTempVarOverwrittenByInstr(cByteInstruction *curr, int offset)
{
	// Which instructions overwrite the variable or discard it?
	if( curr->op == asBC_RET     ||
		curr->op == asBC_SUSPEND )
		return true;
	else if( (asBCInfo[curr->op].type == asBCTYPE_wW_rW_rW_ARG || 
			  asBCInfo[curr->op].type == asBCTYPE_wW_rW_ARG    ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_rW_DW_ARG ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_ARG       ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_W_ARG     ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_DW_ARG    ||
			  asBCInfo[curr->op].type == asBCTYPE_wW_QW_ARG) &&
			 curr->wArg[0] == offset )
		return true;

	return false;
}

bool asCByteCode::IsTempVarRead(cByteInstruction *curr, int offset)
{
	asCArray<cByteInstruction *> openPaths;
	asCArray<cByteInstruction *> closedPaths;

	// We're not interested in the first instruction, since it is the one that sets the variable
	openPaths.PushLast(curr->next);

	while( openPaths.GetLength() )
	{
		curr = openPaths.PopLast();

		// Add the instruction to the closed paths so that we don't verify it again
		closedPaths.PushLast(curr);

		while( curr )
		{
			if( IsTempVarReadByInstr(curr, offset) ) return true;

			if( IsTempVarOverwrittenByInstr(curr, offset) ) break;

			// In case of jumps, we must follow the each of the paths
			if( curr->op == asBC_JMP )
			{
				int label = *((int*)ARG_DW(curr->arg));
				int r = FindLabel(label, curr, &curr, 0); asASSERT( r == 0 ); UNUSED_VAR(r);

				if( !closedPaths.Exists(curr) &&
					!openPaths.Exists(curr) )
					openPaths.PushLast(curr);

				break;
			}
			else if( curr->op == asBC_JZ    || curr->op == asBC_JNZ    ||
				     curr->op == asBC_JS    || curr->op == asBC_JNS    ||
					 curr->op == asBC_JP    || curr->op == asBC_JNP    ||
					 curr->op == asBC_JLowZ || curr->op == asBC_JLowNZ )
			{
				cByteInstruction *dest = 0;
				int label = *((int*)ARG_DW(curr->arg));
				int r = FindLabel(label, curr, &dest, 0); asASSERT( r == 0 ); UNUSED_VAR(r);

				if( !closedPaths.Exists(dest) &&
					!openPaths.Exists(dest) )
					openPaths.PushLast(dest);
			}
			else if( curr->op == asBC_JMPP ) 
			{
				// A JMPP instruction is always followed by a series of JMP instructions 
				// that give the real destination (like a look-up table). We need add all
				// of these as open paths.
				curr = curr->next;
				while( curr->op == asBC_JMP )
				{
					cByteInstruction *dest = 0;
					int label = *((int*)ARG_DW(curr->arg));
					int r = FindLabel(label, curr, &dest, 0); asASSERT( r == 0 ); UNUSED_VAR(r);

					if( !closedPaths.Exists(dest) &&
						!openPaths.Exists(dest) )
						openPaths.PushLast(dest);

					curr = curr->next;
				}

				// We should now be on a label which is the destination of the 
				// first JMP in the sequence and is already added in the open paths
				asASSERT(curr->op == asBC_LABEL);
				break;
			}

			curr = curr->next;
		}
	}

	return false;
}

bool asCByteCode::IsTempRegUsed(cByteInstruction *curr)
{
	// We're not interested in the first instruction, since it is the one that sets the register
	while( curr->next )
	{
		curr = curr->next;

		// Which instructions read from the register?
		if( curr->op == asBC_INCi     ||
			curr->op == asBC_INCi16   ||
			curr->op == asBC_INCi8    ||
			curr->op == asBC_INCf     ||
			curr->op == asBC_INCd     ||
			curr->op == asBC_DECi     ||
			curr->op == asBC_DECi16   ||
			curr->op == asBC_DECi8    ||
			curr->op == asBC_DECf     ||
			curr->op == asBC_DECd     ||
			curr->op == asBC_WRTV1    ||
			curr->op == asBC_WRTV2    ||
			curr->op == asBC_WRTV4    ||
			curr->op == asBC_WRTV8    ||
			curr->op == asBC_RDR1     ||
			curr->op == asBC_RDR2     ||
			curr->op == asBC_RDR4     ||
			curr->op == asBC_RDR8     ||
			curr->op == asBC_PshRPtr  ||
			curr->op == asBC_CpyRtoV4 ||
			curr->op == asBC_CpyRtoV8 ||
			curr->op == asBC_TZ       ||
			curr->op == asBC_TNZ      ||
			curr->op == asBC_TS       ||
			curr->op == asBC_TNS      ||
			curr->op == asBC_TP       ||
			curr->op == asBC_TNP      ||
			curr->op == asBC_JZ       ||
			curr->op == asBC_JNZ      ||
			curr->op == asBC_JLowZ    ||
			curr->op == asBC_JLowNZ   ||
			curr->op == asBC_JS       ||
			curr->op == asBC_JNS      ||
			curr->op == asBC_JP       ||
			curr->op == asBC_JNP      )
			return true;

		// Which instructions overwrite the register or discard the value?
		if( curr->op == asBC_CALL      ||
			curr->op == asBC_PopRPtr   ||
			curr->op == asBC_CALLSYS   ||
			curr->op == asBC_CALLBND   ||
			curr->op == asBC_SUSPEND   ||
			curr->op == asBC_ALLOC     ||
			curr->op == asBC_CpyVtoR4  ||
			curr->op == asBC_LdGRdR4   ||
			curr->op == asBC_LDG       ||
			curr->op == asBC_LDV       ||
			curr->op == asBC_TZ        ||
			curr->op == asBC_TNZ       ||
			curr->op == asBC_TS        ||
			curr->op == asBC_TNS       ||
			curr->op == asBC_TP        ||
			curr->op == asBC_TNP       ||
			curr->op == asBC_JS        ||
			curr->op == asBC_JNS       ||
			curr->op == asBC_JP        ||
			curr->op == asBC_JNP       ||
			curr->op == asBC_JMPP      ||
			curr->op == asBC_JMP       ||
			curr->op == asBC_JZ        ||
			curr->op == asBC_JNZ       ||
			curr->op == asBC_JLowZ     ||
			curr->op == asBC_JLowNZ    ||
			curr->op == asBC_CMPi      ||
			curr->op == asBC_CMPu      ||
			curr->op == asBC_CMPf      ||
			curr->op == asBC_CMPd      ||
			curr->op == asBC_CMPIi     ||
			curr->op == asBC_CMPIu     ||
			curr->op == asBC_CMPIf     ||
			curr->op == asBC_LABEL     ||
			curr->op == asBC_LoadThisR ||
			curr->op == asBC_LoadRObjR ||
			curr->op == asBC_LoadVObjR )
			return false;
	}

	return false;
}

bool asCByteCode::IsSimpleExpression()
{
	// A simple expression is one that cannot be suspended at any time, i.e.
	// it doesn't have any calls to other routines, and doesn't have any suspend instructions
	cByteInstruction *instr = first;
	while( instr )
	{
		if( instr->op == asBC_ALLOC ||
			instr->op == asBC_CALL ||
			instr->op == asBC_CALLSYS ||
			instr->op == asBC_SUSPEND ||
			instr->op == asBC_LINE ||
			instr->op == asBC_FREE ||
			instr->op == asBC_CallPtr ||
			instr->op == asBC_CALLINTF ||
			instr->op == asBC_CALLBND )
			return false;

		instr = instr->next;
	}

	return true;
}

void asCByteCode::ExtractLineNumbers()
{
	int lastLinePos = -1;
	int pos = 0;
	cByteInstruction *instr = first;
	while( instr )
	{
		cByteInstruction *curr = instr;
		instr = instr->next;
		
		if( curr->op == asBC_LINE )
		{
			if( lastLinePos == pos )
			{
				lineNumbers.PopLast();
				lineNumbers.PopLast();
			}

			lastLinePos = pos;
			lineNumbers.PushLast(pos);
			lineNumbers.PushLast(*(int*)ARG_DW(curr->arg));

			if( !engine->ep.buildWithoutLineCues )
			{
				// Transform BC_LINE into BC_SUSPEND
				curr->op = asBC_SUSPEND;
				curr->size = asBCTypeSize[asBCInfo[asBC_SUSPEND].type];
				pos += curr->size;
			}
			else
			{
				// Delete the instruction
				DeleteInstruction(curr);
			}
		}
		else
			pos += curr->size;
	}
}

void asCByteCode::ExtractObjectVariableInfo(asCScriptFunction *outFunc)
{
	int pos = 0;
	cByteInstruction *instr = first;
	while( instr )
	{
		if( instr->op == asBC_Block )
		{
			asSObjectVariableInfo info;
			info.programPos     = pos;
			info.variableOffset = 0;
			info.option         = instr->wArg[0] ? asBLOCK_BEGIN : asBLOCK_END;
			outFunc->objVariableInfo.PushLast(info);
		}
		else if( instr->op == asBC_ObjInfo )
		{
			asSObjectVariableInfo info;
			info.programPos     = pos;
			info.variableOffset = (short)instr->wArg[0];
			info.option         = *(int*)ARG_DW(instr->arg);
			outFunc->objVariableInfo.PushLast(info);
		}
		else if( instr->op == asBC_VarDecl )
		{
			outFunc->variables[instr->wArg[0]]->declaredAtProgramPos = pos;
		}
		else
			pos += instr->size;

		instr = instr->next;
	}
}

int asCByteCode::GetSize()
{
	int size = 0;
	cByteInstruction *instr = first;
	while( instr )
	{
		size += instr->GetSize();

		instr = instr->next;
	}

	return size;
}

void asCByteCode::AddCode(asCByteCode *bc)
{
	if( bc->first )
	{
		if( first == 0 )
		{
			first = bc->first;
			last = bc->last;
			bc->first = 0;
			bc->last = 0;
		}
		else
		{
			last->next = bc->first;
			bc->first->prev = last;
			last = bc->last;
			bc->first = 0;
			bc->last = 0;
		}
	}
}

int asCByteCode::AddInstruction()
{
	cByteInstruction *instr = new(engine->memoryMgr.AllocByteInstruction()) cByteInstruction();
	if( first == 0 )
	{
		first = last = instr;
	}
	else
	{
		last->AddAfter(instr);
		last = instr;
	}

	return 0;
}

int asCByteCode::AddInstructionFirst()
{
	cByteInstruction *instr = new(engine->memoryMgr.AllocByteInstruction()) cByteInstruction();
	if( first == 0 )
	{
		first = last = instr;
	}
	else
	{
		first->AddBefore(instr);
		first = instr;
	}

	return 0;
}

void asCByteCode::Call(asEBCInstr instr, int funcID, int pop)
{
	if( AddInstruction() < 0 )
		return;

	asASSERT(asBCInfo[instr].type == asBCTYPE_DW_ARG);

	last->op = instr;
	last->size = asBCTypeSize[asBCInfo[instr].type];
	last->stackInc = -pop; // BC_CALL and BC_CALLBND doesn't pop the argument but when the callee returns the arguments are already popped
	*((int*)ARG_DW(last->arg)) = funcID;

    // Add a JitEntry instruction after function calls so that JIT's can resume execution
    InstrPTR(asBC_JitEntry, 0);
}

void asCByteCode::CallPtr(asEBCInstr instr, int funcPtrVar, int pop)
{
	if( AddInstruction() < 0 )
		return;

	asASSERT(asBCInfo[instr].type == asBCTYPE_rW_ARG);

	last->op = instr;
	last->size = asBCTypeSize[asBCInfo[instr].type];
	last->stackInc = -pop;
	last->wArg[0] = (short)funcPtrVar;

    // Add a JitEntry instruction after function calls so that JIT's can resume execution
    InstrPTR(asBC_JitEntry, 0);
}

void asCByteCode::Alloc(asEBCInstr instr, void *objID, int funcID, int pop)
{
	if( AddInstruction() < 0 )
		return;

	last->op = instr;
	last->size = asBCTypeSize[asBCInfo[instr].type];
	last->stackInc = -pop; // BC_ALLOC

	asASSERT(asBCInfo[instr].type == asBCTYPE_PTR_DW_ARG);
	*ARG_PTR(last->arg) = (asPWORD)objID;
	*((int*)(ARG_DW(last->arg)+AS_PTR_SIZE)) = funcID;

    // Add a JitEntry instruction after function calls so that JIT's can resume execution
    InstrPTR(asBC_JitEntry, 0);
}

void asCByteCode::Ret(int pop)
{
	if( AddInstruction() < 0 )
		return;

	asASSERT(asBCInfo[asBC_RET].type == asBCTYPE_W_ARG);

	last->op = asBC_RET;
	last->size = asBCTypeSize[asBCInfo[asBC_RET].type];
	last->stackInc = 0; // The instruction pops the argument, but it doesn't affect current function
	last->wArg[0] = (short)pop;
}

void asCByteCode::JmpP(int var, asDWORD max)
{
	if( AddInstruction() < 0 )
		return;
	
	asASSERT(asBCInfo[asBC_JMPP].type == asBCTYPE_rW_ARG);

	last->op       = asBC_JMPP;
	last->size     = asBCTypeSize[asBCInfo[asBC_JMPP].type];
	last->stackInc = asBCInfo[asBC_JMPP].stackInc;
	last->wArg[0]  = (short)var;

	// Store the largest jump that is made for PostProcess()
	*ARG_DW(last->arg) = max;
}

void asCByteCode::Label(short label)
{
	if( AddInstruction() < 0 )
		return;

	last->op       = asBC_LABEL;
	last->size     = 0;
	last->stackInc = 0;
	last->wArg[0]  = label;
}

void asCByteCode::Line(int line, int column)
{
	if( AddInstruction() < 0 )
		return;

	last->op       = asBC_LINE;
	// If the build is without line cues these instructions will be removed
	// otherwise they will be transformed into SUSPEND instructions.
	if( engine->ep.buildWithoutLineCues )
		last->size = 0;
	else
		last->size = asBCTypeSize[asBCInfo[asBC_SUSPEND].type];
	last->stackInc = 0;
	*((int*)ARG_DW(last->arg)) = (line & 0xFFFFF)|((column & 0xFFF)<<20);

    // Add a JitEntry after the line instruction to allow the JIT function to resume after a suspend
    InstrPTR(asBC_JitEntry, 0);
}

void asCByteCode::ObjInfo(int offset, int info)
{
	if( AddInstruction() < 0 )
		return;

	// Add the special instruction that will be used to tell the exception
	// handler when an object is initialized and deinitialized.
	last->op                   = asBC_ObjInfo;
	last->size                 = 0;
	last->stackInc             = 0;
	last->wArg[0]              = (short)offset;
	*((int*)ARG_DW(last->arg)) = info;
}

void asCByteCode::Block(bool start)
{
	if( AddInstruction() < 0 )
		return;

	last->op       = asBC_Block;
	last->size     = 0;
	last->stackInc = 0;
	last->wArg[0]  = start ? 1 : 0;
}

void asCByteCode::VarDecl(int varDeclIdx)
{
	if( AddInstruction() < 0 )
		return;

	last->op       = asBC_VarDecl;
	last->size     = 0;
	last->stackInc = 0;
	last->wArg[0]  = (asWORD)varDeclIdx;
}


int asCByteCode::FindLabel(int label, cByteInstruction *from, cByteInstruction **dest, int *positionDelta)
{
	// Search forward
	int labelPos = -from->GetSize();

	cByteInstruction *labelInstr = from;
	while( labelInstr )
	{
		labelPos += labelInstr->GetSize();
		labelInstr = labelInstr->next;

		if( labelInstr && labelInstr->op == asBC_LABEL )
		{
			if( labelInstr->wArg[0] == label )
				break;
		}
	}

	if( labelInstr == 0 )
	{
		// Search backwards
		labelPos = -from->GetSize();

		labelInstr = from;
		while( labelInstr )
		{
			labelInstr = labelInstr->prev;
			if( labelInstr )
			{
				labelPos -= labelInstr->GetSize();

				if( labelInstr->op == asBC_LABEL )
				{
					if( labelInstr->wArg[0] == label )
						break;
				}
			}
		}
	}

	if( labelInstr != 0 )
	{
		if( dest ) *dest = labelInstr;
		if( positionDelta ) *positionDelta = labelPos;
		return 0;
	}

	return -1;
}

int asCByteCode::ResolveJumpAddresses()
{
	cByteInstruction *instr = first;
	while( instr )
	{
		if( instr->op == asBC_JMP   || 
			instr->op == asBC_JZ    || instr->op == asBC_JNZ    ||
			instr->op == asBC_JLowZ || instr->op == asBC_JLowNZ ||
			instr->op == asBC_JS    || instr->op == asBC_JNS    || 
			instr->op == asBC_JP    || instr->op == asBC_JNP    )
		{
			int label = *((int*) ARG_DW(instr->arg));
			int labelPosOffset;			
			int r = FindLabel(label, instr, 0, &labelPosOffset);
			if( r == 0 )
				*((int*) ARG_DW(instr->arg)) = labelPosOffset;
			else
				return -1;
		}

		instr = instr->next;
	}

	return 0;
}


cByteInstruction *asCByteCode::DeleteInstruction(cByteInstruction *instr)
{
	if( instr == 0 ) return 0;

	cByteInstruction *ret = instr->prev ? instr->prev : instr->next;
	
	RemoveInstruction(instr);

	engine->memoryMgr.FreeByteInstruction(instr);

	return ret;
}

void asCByteCode::Output(asDWORD *array)
{
	// TODO: Receive a script function pointer instead of the bytecode array

	asDWORD *ap = array;

	cByteInstruction *instr = first;
	while( instr )
	{
		if( instr->GetSize() > 0 )
		{
			*(asBYTE*)ap = asBYTE(instr->op);
			*(((asBYTE*)ap)+1) = 0; // Second byte is always zero
			switch( asBCInfo[instr->op].type ) 
			{
			case asBCTYPE_NO_ARG:
				*(((asWORD*)ap)+1) = 0; // Clear upper bytes
				break;
			case asBCTYPE_wW_rW_rW_ARG:
				*(((asWORD*)ap)+1) = instr->wArg[0];
				*(((asWORD*)ap)+2) = instr->wArg[1];
				*(((asWORD*)ap)+3) = instr->wArg[2];
				break;
			case asBCTYPE_wW_DW_ARG:
			case asBCTYPE_rW_DW_ARG:
			case asBCTYPE_W_DW_ARG:
				*(((asWORD*)ap)+1) = instr->wArg[0];
				*(ap+1) = *(asDWORD*)&instr->arg;
				break;
			case asBCTYPE_wW_rW_DW_ARG:
			case asBCTYPE_rW_W_DW_ARG:
				*(((asWORD*)ap)+1) = instr->wArg[0];
				*(((asWORD*)ap)+2) = instr->wArg[1];
				*(ap+2) = *(asDWORD*)&instr->arg;
				break;
			case asBCTYPE_wW_QW_ARG:
			case asBCTYPE_rW_QW_ARG:
				*(((asWORD*)ap)+1) = instr->wArg[0];
				*(asQWORD*)(ap+1) = asQWORD(instr->arg);
				break;
			case asBCTYPE_W_ARG:
			case asBCTYPE_rW_ARG: 
			case asBCTYPE_wW_ARG:
				*(((asWORD*)ap)+1) = instr->wArg[0];
				break;
			case asBCTYPE_wW_rW_ARG:
			case asBCTYPE_rW_rW_ARG:
			case asBCTYPE_wW_W_ARG:
				*(((asWORD *)ap)+1) = instr->wArg[0];
				*(((asWORD *)ap)+2) = instr->wArg[1];
				break;
			case asBCTYPE_QW_DW_ARG:
			case asBCTYPE_DW_DW_ARG:
			case asBCTYPE_QW_ARG:
			case asBCTYPE_DW_ARG:
				*(((asWORD*)ap)+1) = 0; // Clear upper bytes
				memcpy(ap+1, &instr->arg, instr->GetSize()*4-4);
				break;
			default:
				// How did we get here?
				asASSERT(false);
				break;
			}
		}

		ap += instr->GetSize();
		instr = instr->next;
	}
}

void asCByteCode::PostProcess()
{
	if( first == 0 ) return;

	// This function will do the following
	// - Verify if there is any code that never gets executed and remove it
	// - Calculate the stack size at the position of each byte code 
	// - Calculate the largest stack needed

	largestStackUsed = 0;

	cByteInstruction *instr = first;
	while( instr )
	{
		instr->marked = false;
		instr->stackSize = -1;
		instr = instr->next;
	}

	// Add the first instruction to the list of unchecked code paths
	asCArray<cByteInstruction *> paths;
	AddPath(paths, first, 0);

	// Go through each of the code paths
	for( asUINT p = 0; p < paths.GetLength(); ++p )
	{
		instr = paths[p];
		int stackSize = instr->stackSize;
		
		while( instr )
		{
			instr->marked = true;
			instr->stackSize = stackSize;
			stackSize += instr->stackInc;
			if( stackSize > largestStackUsed ) 
				largestStackUsed = stackSize;

			if( instr->op == asBC_JMP )
			{
				// Find the label that we should jump to
				int label = *((int*) ARG_DW(instr->arg));
				cByteInstruction *dest = 0;
				int r = FindLabel(label, instr, &dest, 0); asASSERT( r == 0 ); UNUSED_VAR(r);
				
				AddPath(paths, dest, stackSize);
				break;
			}
			else if( instr->op == asBC_JZ    || instr->op == asBC_JNZ ||
					 instr->op == asBC_JLowZ || instr->op == asBC_JLowNZ ||
					 instr->op == asBC_JS    || instr->op == asBC_JNS ||
					 instr->op == asBC_JP    || instr->op == asBC_JNP )
			{
				// Find the label that is being jumped to
				int label = *((int*) ARG_DW(instr->arg));
				cByteInstruction *dest = 0;
				int r = FindLabel(label, instr, &dest, 0); asASSERT( r == 0 ); UNUSED_VAR(r);
				
				AddPath(paths, dest, stackSize);
				
				// Add both paths to the code paths
				AddPath(paths, instr->next, stackSize);
				
				break;
			}
			else if( instr->op == asBC_JMPP )
			{
				// I need to know the largest value possible
				asDWORD max = *ARG_DW(instr->arg);
								
				// Add all destinations to the code paths
				cByteInstruction *dest = instr->next;
				for( asDWORD n = 0; n <= max && dest != 0; ++n )
				{
					AddPath(paths, dest, stackSize);
					dest = dest->next;
				}				
				
				break;				
			}
			else
			{
				instr = instr->next;
				if( instr == 0 || instr->marked )
					break;
			}
		}
	}
	
	// Are there any instructions that didn't get visited?
	instr = first;
	while( instr )
	{
		if( instr->marked == false )
		{
			// TODO: Give warning of unvisited code

			// Remove it
			cByteInstruction *curr = instr;
			instr = instr->next;
			DeleteInstruction(curr);
		}
		else
			instr = instr->next;
	}	
}

#ifdef AS_DEBUG
void asCByteCode::DebugOutput(const char *name, asCScriptEngine *engine, asCScriptFunction *func)
{
	_mkdir("AS_DEBUG");

	asCString str = "AS_DEBUG/";
	str += name;

#if _MSC_VER >= 1500 
	FILE *file;
	fopen_s(&file, str.AddressOf(), "w");
#else
	FILE *file = fopen(str.AddressOf(), "w");
#endif

#if !defined(AS_XENON) // XBox 360: When running in DVD Emu, no write is allowed
	asASSERT( file );
#endif

	if( file == 0 )
		return;

	asUINT n;

	fprintf(file, "%s\n\n", func->GetDeclaration());

	fprintf(file, "Temps: ");
	for( n = 0; n < temporaryVariables.GetLength(); n++ )
	{
		fprintf(file, "%d", temporaryVariables[n]);
		if( n < temporaryVariables.GetLength()-1 )
			fprintf(file, ", ");
	}
	fprintf(file, "\n\n");

	fprintf(file, "Variables: \n");
	for( n = 0; n < func->variables.GetLength(); n++ )
	{
		fprintf(file, " %.3d: %s %s\n", func->variables[n]->stackOffset, func->variables[n]->type.Format().AddressOf(), func->variables[n]->name.AddressOf());
	}
	asUINT offset = 0;
	if( func->objectType )
	{
		fprintf(file, " %.3d: %s this\n", 0, func->objectType->name.AddressOf());
		offset -= AS_PTR_SIZE;
	}
	for( n = 0; n < func->parameterTypes.GetLength(); n++ )
	{
		bool found = false;
		for( asUINT v = 0; v < func->variables.GetLength(); v++ )
		{
			if( func->variables[v]->stackOffset == (int)offset )
			{
				found = true;
				break;
			}
		}
		if( !found )
			fprintf(file, " %.3d: %s {noname param}\n", offset, func->parameterTypes[n].Format().AddressOf());

		offset -= func->parameterTypes[n].GetSizeOnStackDWords();
	}
	for( n = 0; n < func->objVariablePos.GetLength(); n++ )
	{
		bool found = false;
		for( asUINT v = 0; v < func->variables.GetLength(); v++ )
		{
			if( func->variables[v]->stackOffset == func->objVariablePos[n] )
			{
				found = true;
				break;
			}
		}
		if( !found )
			fprintf(file, " %.3d: %s {noname}\n", func->objVariablePos[n], func->objVariableTypes[n]->name.AddressOf());
	}
	fprintf(file, "\n\n");

	int pos = 0;
	asUINT lineIndex = 0;
	cByteInstruction *instr = first;
	while( instr )
	{
		if( lineIndex < lineNumbers.GetLength() && lineNumbers[lineIndex] == pos )
		{
			asDWORD line = lineNumbers[lineIndex+1];
			fprintf(file, "- %d,%d -\n", (int)(line&0xFFFFF), (int)(line>>20));
			lineIndex += 2;
		}

		fprintf(file, "%5d ", pos);
		pos += instr->GetSize();

		fprintf(file, "%3d %c ", instr->stackSize + func->variableSpace, instr->marked ? '*' : ' ');

		switch( asBCInfo[instr->op].type )
		{
		case asBCTYPE_W_ARG:
			if( instr->op == asBC_STR )
			{
				int id = instr->wArg[0];
				const asCString &str = engine->GetConstantString(id);
				fprintf(file, "   %-8s %d         (l:%ld s:\"%.10s\")\n", asBCInfo[instr->op].name, instr->wArg[0], (long int)str.GetLength(), str.AddressOf());
			}
			else
				fprintf(file, "   %-8s %d\n", asBCInfo[instr->op].name, instr->wArg[0]);
			break;

		case asBCTYPE_wW_ARG:
		case asBCTYPE_rW_ARG:
			fprintf(file, "   %-8s v%d\n", asBCInfo[instr->op].name, instr->wArg[0]);
			break;

		case asBCTYPE_wW_rW_ARG:
		case asBCTYPE_rW_rW_ARG:
			fprintf(file, "   %-8s v%d, v%d\n", asBCInfo[instr->op].name, instr->wArg[0], instr->wArg[1]);
			break;

		case asBCTYPE_wW_W_ARG:
			fprintf(file, "   %-8s v%d, %d\n", asBCInfo[instr->op].name, instr->wArg[0], instr->wArg[1]);
			break;

		case asBCTYPE_wW_rW_DW_ARG:
		case asBCTYPE_rW_W_DW_ARG:
			switch( instr->op )
			{
			case asBC_ADDIf:
			case asBC_SUBIf:
			case asBC_MULIf:
				fprintf(file, "   %-8s v%d, v%d, %f\n", asBCInfo[instr->op].name, instr->wArg[0], instr->wArg[1], *((float*) ARG_DW(instr->arg)));
				break;
			default:
				fprintf(file, "   %-8s v%d, v%d, %d\n", asBCInfo[instr->op].name, instr->wArg[0], instr->wArg[1], *((int*) ARG_DW(instr->arg)));
				break;
			}
			break;

		case asBCTYPE_DW_ARG:
			switch( instr->op )
			{
			case asBC_OBJTYPE:
				fprintf(file, "   %-8s 0x%x\n", asBCInfo[instr->op].name, (asUINT)*ARG_DW(instr->arg));
				break;

			case asBC_PshC4:
			case asBC_Cast:
				fprintf(file, "   %-8s 0x%x          (i:%d, f:%g)\n", asBCInfo[instr->op].name, (asUINT)*ARG_DW(instr->arg), *((int*) ARG_DW(instr->arg)), *((float*) ARG_DW(instr->arg)));
				break;

			case asBC_TYPEID:
				fprintf(file, "   %-8s 0x%x          '%s'\n", asBCInfo[instr->op].name, (asUINT)*ARG_DW(instr->arg), engine->GetTypeDeclaration((int)*ARG_DW(instr->arg)));
				break;

			case asBC_CALL:
			case asBC_CALLSYS:
			case asBC_CALLBND:
			case asBC_CALLINTF:
				{
					int funcID = *(int*)ARG_DW(instr->arg);
					asCString decl = engine->GetFunctionDeclaration(funcID);

					fprintf(file, "   %-8s %d           (%s)\n", asBCInfo[instr->op].name, *((int*) ARG_DW(instr->arg)), decl.AddressOf());
				}
				break;	

			case asBC_REFCPY:
				fprintf(file, "   %-8s 0x%x\n", asBCInfo[instr->op].name, *((int*) ARG_DW(instr->arg)));
				break;

			case asBC_JMP:
			case asBC_JZ:
			case asBC_JLowZ:
			case asBC_JS:
			case asBC_JP:
			case asBC_JNZ:
			case asBC_JLowNZ:
			case asBC_JNS:
			case asBC_JNP:
				fprintf(file, "   %-8s %+d              (d:%d)\n", asBCInfo[instr->op].name, *((int*) ARG_DW(instr->arg)), pos+*((int*) ARG_DW(instr->arg)));
				break;

			default:
				fprintf(file, "   %-8s %d\n", asBCInfo[instr->op].name, *((int*) ARG_DW(instr->arg)));
				break;
			}
			break;

		case asBCTYPE_QW_ARG:
#ifdef __GNUC__
#ifdef _LP64
			fprintf(file, "   %-8s 0x%lx           (i:%ld, f:%g)\n", asBCInfo[instr->op].name, *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#else
			fprintf(file, "   %-8s 0x%llx           (i:%lld, f:%g)\n", asBCInfo[instr->op].name, *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#endif
#else
			fprintf(file, "   %-8s 0x%I64x          (i:%I64d, f:%g)\n", asBCInfo[instr->op].name, *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#endif
			break;

		case asBCTYPE_wW_QW_ARG:
		case asBCTYPE_rW_QW_ARG:
#ifdef __GNUC__
#ifdef _LP64
			fprintf(file, "   %-8s v%d, 0x%lx           (i:%ld, f:%g)\n", asBCInfo[instr->op].name, instr->wArg[0], *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#else
			fprintf(file, "   %-8s v%d, 0x%llx           (i:%lld, f:%g)\n", asBCInfo[instr->op].name, instr->wArg[0], *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#endif
#else
			fprintf(file, "   %-8s v%d, 0x%I64x          (i:%I64d, f:%g)\n", asBCInfo[instr->op].name, instr->wArg[0], *ARG_QW(instr->arg), *((asINT64*) ARG_QW(instr->arg)), *((double*) ARG_QW(instr->arg)));
#endif
			break;

		case asBCTYPE_DW_DW_ARG:
			if( instr->op == asBC_ALLOC )
			{
				asCObjectType *ot = *(asCObjectType**)ARG_DW(instr->arg);
				fprintf(file, "   %-8s 0x%x, %d             (type:%s)\n", asBCInfo[instr->op].name, *(int*)ARG_DW(instr->arg), *(int*)(ARG_DW(instr->arg)+1), ot->GetName());
			}
			else
				fprintf(file, "   %-8s %u, %d\n", asBCInfo[instr->op].name, *(int*)ARG_DW(instr->arg), *(int*)(ARG_DW(instr->arg)+1));
			break;

		case asBCTYPE_QW_DW_ARG:
			if( instr->op == asBC_ALLOC )
			{
				asCObjectType *ot = *(asCObjectType**)ARG_QW(instr->arg);
#ifdef __GNUC__
#ifdef AS_64BIT_PTR
				fprintf(file, "   %-8s 0x%lx, %d             (type:%s)\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2), ot->GetName());
#else
				fprintf(file, "   %-8s 0x%llx, %d             (type:%s)\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2), ot->GetName());
#endif
#else
				fprintf(file, "   %-8s 0x%I64x, %d             (type:%s)\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2), ot->GetName());
#endif
			}
			else
#ifdef __GNUC__
#ifdef AS_64BIT_PTR
				fprintf(file, "   %-8s %lu, %d\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2));
#else
				fprintf(file, "   %-8s %llu, %d\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2));
#endif
#else
				fprintf(file, "   %-8s %I64u, %d\n", asBCInfo[instr->op].name, *(asINT64*)ARG_QW(instr->arg), *(int*)(ARG_DW(instr->arg)+2));
#endif
			break;

		case asBCTYPE_INFO:
			if( instr->op == asBC_LABEL )
				fprintf(file, "%d:\n", instr->wArg[0]);
			else if( instr->op == asBC_LINE )
				fprintf(file, "   %s\n", asBCInfo[instr->op].name);
			else if( instr->op == asBC_Block )
				fprintf(file, "%c\n", instr->wArg[0] ? '{' : '}');
			break;

		case asBCTYPE_rW_DW_ARG:
		case asBCTYPE_wW_DW_ARG:
		case asBCTYPE_W_DW_ARG:
			if( instr->op == asBC_SetV1 )
				fprintf(file, "   %-8s v%d, 0x%x\n", asBCInfo[instr->op].name, instr->wArg[0], *(asBYTE*)ARG_DW(instr->arg));
			else if( instr->op == asBC_SetV2 )
				fprintf(file, "   %-8s v%d, 0x%x\n", asBCInfo[instr->op].name, instr->wArg[0], *(asWORD*)ARG_DW(instr->arg));
			else if( instr->op == asBC_SetV4 )
				fprintf(file, "   %-8s v%d, 0x%x          (i:%d, f:%g)\n", asBCInfo[instr->op].name, instr->wArg[0], (asUINT)*ARG_DW(instr->arg), *((int*) ARG_DW(instr->arg)), *((float*) ARG_DW(instr->arg)));
			else if( instr->op == asBC_CMPIf )
				fprintf(file, "   %-8s v%d, %f\n", asBCInfo[instr->op].name, instr->wArg[0], *(float*)ARG_DW(instr->arg));
			else
				fprintf(file, "   %-8s v%d, %d\n", asBCInfo[instr->op].name, instr->wArg[0], (asUINT)*ARG_DW(instr->arg));
			break;

		case asBCTYPE_wW_rW_rW_ARG:
			fprintf(file, "   %-8s v%d, v%d, v%d\n", asBCInfo[instr->op].name, instr->wArg[0], instr->wArg[1], instr->wArg[2]);
			break;

		case asBCTYPE_NO_ARG:
			fprintf(file, "   %s\n", asBCInfo[instr->op].name);
			break;

		default:
			asASSERT(false);
		}

		instr = instr->next;
	}

	fclose(file);
}
#endif

//=============================================================================

int asCByteCode::InsertFirstInstrDWORD(asEBCInstr bc, asDWORD param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstructionFirst() < 0 )
		return 0;

	first->op = bc;
	*ARG_DW(first->arg) = param;
	first->size = asBCTypeSize[asBCInfo[bc].type];
	first->stackInc = asBCInfo[bc].stackInc;

	return first->stackInc;
}

int asCByteCode::InsertFirstInstrQWORD(asEBCInstr bc, asQWORD param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_QW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstructionFirst() < 0 )
		return 0;

	first->op = bc;
	*ARG_QW(first->arg) = param;
	first->size = asBCTypeSize[asBCInfo[bc].type];
	first->stackInc = asBCInfo[bc].stackInc;

	return first->stackInc;
}

int asCByteCode::Instr(asEBCInstr bc)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_NO_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_W_W(asEBCInstr bc, int a, int b, int c)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_rW_rW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = (short)a;
	last->wArg[1]  = (short)b;
	last->wArg[2]  = (short)c;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_W(asEBCInstr bc, int a, int b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_rW_ARG ||
	         asBCInfo[bc].type == asBCTYPE_rW_rW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = (short)a;
	last->wArg[1]  = (short)b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_PTR(asEBCInstr bc, short a, void *param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_PTR_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*ARG_PTR(last->arg) = (asPWORD)param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_DW(asEBCInstr bc, asWORD a, asDWORD b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_DW_ARG ||
             asBCInfo[bc].type == asBCTYPE_rW_DW_ARG ||
			 asBCInfo[bc].type == asBCTYPE_W_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*((int*) ARG_DW(last->arg)) = b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrSHORT_B(asEBCInstr bc, short a, asBYTE b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_DW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_rW_DW_ARG ||
			 asBCInfo[bc].type == asBCTYPE_W_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;

	// We'll have to be careful to store the byte correctly, independent of endianess.
	// Some optimizing compilers may change the order of operations, so we make sure 
	// the value is not overwritten even if that happens.
	asBYTE *argPtr = (asBYTE*)ARG_DW(last->arg);
	argPtr[0] = b; // The value is always stored in the lower byte
	argPtr[1] = 0; // and clear the rest of the DWORD
	argPtr[2] = 0;
	argPtr[3] = 0;

	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrSHORT_W(asEBCInstr bc, short a, asWORD b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_DW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_rW_DW_ARG ||
			 asBCInfo[bc].type == asBCTYPE_W_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	
	// We'll have to be careful to store the word correctly, independent of endianess.
	// Some optimizing compilers may change the order of operations, so we make sure 
	// the value is not overwritten even if that happens.
	asWORD *argPtr = (asWORD*)ARG_DW(last->arg);
	argPtr[0] = b; // The value is always stored in the lower word
	argPtr[1] = 0; // and clear the rest of the DWORD

	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrSHORT_DW(asEBCInstr bc, short a, asDWORD b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_DW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_rW_DW_ARG ||
			 asBCInfo[bc].type == asBCTYPE_W_DW_ARG);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*((int*) ARG_DW(last->arg)) = b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_QW(asEBCInstr bc, asWORD a, asQWORD b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_QW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*ARG_QW(last->arg) = b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrSHORT_QW(asEBCInstr bc, short a, asQWORD b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_QW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*ARG_QW(last->arg) = b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrW_FLOAT(asEBCInstr bc, asWORD a, float b)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_wW_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc == 0);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = a;
	*((float*) ARG_DW(last->arg)) = b;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrSHORT(asEBCInstr bc, short param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_rW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_wW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_W_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrINT(asEBCInstr bc, int param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	*((int*) ARG_DW(last->arg)) = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrDWORD(asEBCInstr bc, asDWORD param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	*ARG_DW(last->arg) = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrPTR(asEBCInstr bc, void *param)
{
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	asASSERT(asBCInfo[bc].type == asBCTYPE_PTR_ARG);
	*ARG_PTR(last->arg) = (asPWORD)param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrQWORD(asEBCInstr bc, asQWORD param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_QW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	*ARG_QW(last->arg) = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrWORD(asEBCInstr bc, asWORD param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_W_ARG  || 
	         asBCInfo[bc].type == asBCTYPE_rW_ARG || 
	         asBCInfo[bc].type == asBCTYPE_wW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op       = bc;
	last->wArg[0]  = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrFLOAT(asEBCInstr bc, float param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_DW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	*((float*) ARG_DW(last->arg)) = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::InstrDOUBLE(asEBCInstr bc, double param)
{
	asASSERT(asBCInfo[bc].type == asBCTYPE_QW_ARG);
	asASSERT(asBCInfo[bc].stackInc != 0xFFFF);

	if( AddInstruction() < 0 )
		return 0;

	last->op = bc;
	*((double*) ARG_QW(last->arg)) = param;
	last->size     = asBCTypeSize[asBCInfo[bc].type];
	last->stackInc = asBCInfo[bc].stackInc;

	return last->stackInc;
}

int asCByteCode::GetLastInstr()
{
	if( last == 0 ) return -1;

	return last->op;
}

int asCByteCode::RemoveLastInstr()
{
	if( last == 0 ) return -1;

	if( first == last )
	{
		engine->memoryMgr.FreeByteInstruction(last);
		first = 0;
		last = 0;
	}
	else
	{
		cByteInstruction *bc = last;
		last = bc->prev;

		bc->Remove();
		engine->memoryMgr.FreeByteInstruction(bc);
	}

	return 0;
}

asDWORD asCByteCode::GetLastInstrValueDW()
{
	if( last == 0 ) return 0;

	return *ARG_DW(last->arg);
}

void asCByteCode::DefineTemporaryVariable(int varOffset)
{
	temporaryVariables.PushLast(varOffset);
}

//===================================================================

cByteInstruction::cByteInstruction()
{
	next      = 0;
	prev      = 0;

	op        = asBC_LABEL;

	arg       = 0;
	wArg[0]   = 0;
	wArg[1]   = 0;
	wArg[2]   = 0;
	size      = 0;
	stackInc  = 0;
	marked    = false;
	stackSize = 0;
}

void cByteInstruction::AddAfter(cByteInstruction *nextCode)
{
	if( next )
		next->prev = nextCode;

	nextCode->next = next;
	nextCode->prev = this;
	next = nextCode;
}

void cByteInstruction::AddBefore(cByteInstruction *prevCode)
{
	if( prev )
		prev->next = prevCode;

	prevCode->prev = prev;
	prevCode->next = this;
	prev = prevCode;
}

int cByteInstruction::GetSize()
{
	return size;
}

int cByteInstruction::GetStackIncrease()
{
	return stackInc;
}

void cByteInstruction::Remove()
{
	if( prev ) prev->next = next;
	if( next ) next->prev = prev;
	prev = 0;
	next = 0;
}

END_AS_NAMESPACE

#endif // AS_NO_COMPILER

