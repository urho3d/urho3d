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
// as_compiler.cpp
//
// The class that does the actual compilation of the functions
//

#include <math.h> // fmodf()

#include "as_config.h"
#include "as_compiler.h"
#include "as_tokendef.h"
#include "as_tokenizer.h"
#include "as_string_util.h"
#include "as_texts.h"
#include "as_parser.h"

BEGIN_AS_NAMESPACE

// TODO: I must correct the interpretation of a references to objects in the compiler.
//       A reference should mean that a pointer to the object is on the stack.
//       No expression should end up as non-references to objects, as the actual object is 
//       never put on the stack.
//       Local variables are declared as non-references, but the expression should be a reference to the variable.
//       Function parameters of called functions can also be non-references, but in that case it means the 
//       object will be passed by value (currently on the heap, which will be moved to the application stack).

asCCompiler::asCCompiler(asCScriptEngine *engine) : byteCode(engine)
{
	builder = 0;
	script = 0;

	variables = 0;
	isProcessingDeferredParams = false;
	noCodeOutput = 0;
}

asCCompiler::~asCCompiler()
{
	while( variables )
	{
		asCVariableScope *var = variables;
		variables = variables->parent;

		asDELETE(var,asCVariableScope);
	}
}

void asCCompiler::Reset(asCBuilder *builder, asCScriptCode *script, asCScriptFunction *outFunc)
{
	this->builder = builder;
	this->engine = builder->engine;
	this->script = script;
	this->outFunc = outFunc;

	hasCompileErrors = false;

	m_isConstructor = false;
	m_isConstructorCalled = false;

	nextLabel = 0;
	breakLabels.SetLength(0);
	continueLabels.SetLength(0);

	byteCode.ClearAll();

	globalExpression = false;
}

int asCCompiler::CompileDefaultConstructor(asCBuilder *builder, asCScriptCode *script, asCScriptFunction *outFunc)
{
	Reset(builder, script, outFunc);

	// If the class is derived from another, then the base class' default constructor must be called
	if( outFunc->objectType->derivedFrom )
	{
		// Call the base class' default constructor
		byteCode.InstrSHORT(asBC_PSF, 0);
		byteCode.Instr(asBC_RDSPTR);
		byteCode.Call(asBC_CALL, outFunc->objectType->derivedFrom->beh.construct, AS_PTR_SIZE);
	}

	// Pop the object pointer from the stack
	byteCode.Ret(AS_PTR_SIZE);

	FinalizeFunction();

#ifdef AS_DEBUG
	// DEBUG: output byte code
	byteCode.DebugOutput(("__" + outFunc->objectType->name + "_" + outFunc->name + "__dc.txt").AddressOf(), engine, outFunc);
#endif

	return 0;
}

int asCCompiler::CompileFactory(asCBuilder *builder, asCScriptCode *script, asCScriptFunction *outFunc)
{
	Reset(builder, script, outFunc);

	unsigned int n;

	// Find the corresponding constructor
	asCDataType dt = asCDataType::CreateObject(outFunc->returnType.GetObjectType(), false);
	int constructor = 0;
	for( n = 0; n < dt.GetBehaviour()->factories.GetLength(); n++ )
	{
		if( dt.GetBehaviour()->factories[n] == outFunc->id )
		{
			constructor = dt.GetBehaviour()->constructors[n];
			break;
		}
	}

	// Allocate the class and instanciate it with the constructor
	int varOffset = AllocateVariable(dt, true);

	byteCode.Push(AS_PTR_SIZE);
	byteCode.InstrSHORT(asBC_PSF, (short)varOffset);

	// Copy all arguments to the top of the stack
	int argDwords = (int)outFunc->GetSpaceNeededForArguments();
	for( int a = argDwords-1; a >= 0; a-- )
		byteCode.InstrSHORT(asBC_PshV4, short(-a));

	byteCode.Alloc(asBC_ALLOC, dt.GetObjectType(), constructor, argDwords + AS_PTR_SIZE);

	// Return a handle to the newly created object
	byteCode.InstrSHORT(asBC_LOADOBJ, (short)varOffset);

	byteCode.Ret(argDwords);

	FinalizeFunction();

	// Tell the virtual machine not to clean up parameters on exception
	outFunc->dontCleanUpOnException = true;

/*
#ifdef AS_DEBUG
	// DEBUG: output byte code
	asCString args;
	args.Format("%d", outFunc->parameterTypes.GetLength());
	byteCode.DebugOutput(("__" + outFunc->name + "__factory" + args + ".txt").AddressOf(), engine);
#endif
*/
	return 0;
}

// Entry
int asCCompiler::CompileTemplateFactoryStub(asCBuilder *builder, int trueFactoryId, asCObjectType *objType, asCScriptFunction *outFunc)
{
	Reset(builder, 0, outFunc);

	asCScriptFunction *descr = builder->GetFunctionDescription(trueFactoryId);

	byteCode.InstrPTR(asBC_OBJTYPE, objType);
	byteCode.Call(asBC_CALLSYS, trueFactoryId, descr->GetSpaceNeededForArguments());
	byteCode.Ret(outFunc->GetSpaceNeededForArguments());

	FinalizeFunction();

	// Tell the virtual machine not to clean up the object on exception
	outFunc->dontCleanUpOnException = true;

	return 0;
}

// Entry
int asCCompiler::CompileFunction(asCBuilder *builder, asCScriptCode *script, asCScriptNode *func, asCScriptFunction *outFunc)
{
	Reset(builder, script, outFunc);
	int buildErrors = builder->numErrors;

	int stackPos = 0;
	if( outFunc->objectType )
		stackPos = -AS_PTR_SIZE; // The first parameter is the pointer to the object

	// Reserve a label for the cleanup code
	nextLabel++;

	// Add the first variable scope, which the parameters and
	// variables declared in the outermost statement block is
	// part of.
	AddVariableScope();

	//----------------------------------------------
	// Examine return type
	bool isDestructor = false;
	asCDataType returnType;
	if( func->firstChild->nodeType == snDataType )
	{
		returnType = builder->CreateDataTypeFromNode(func->firstChild, script);
		returnType = builder->ModifyDataTypeFromNode(returnType, func->firstChild->next, script, 0, 0);

		// Make sure the return type is instanciable or is void
		if( !returnType.CanBeInstanciated() &&
			returnType != asCDataType::CreatePrimitive(ttVoid, false) )
		{
			asCString str;
			str.Format(TXT_DATA_TYPE_CANT_BE_s, returnType.Format().AddressOf());
			Error(str.AddressOf(), func->firstChild);
		}
	}
	else
	{
		returnType = asCDataType::CreatePrimitive(ttVoid, false);
		if( func->firstChild->tokenType == ttBitNot )
			isDestructor = true;
		else
			m_isConstructor = true;
	}

	//----------------------------------------------
	// Declare parameters
	// Find first parameter
	asCScriptNode *node = func->firstChild;
	while( node && node->nodeType != snParameterList )
		node = node->next;

	// Register parameters from last to first, otherwise they will be destroyed in the wrong order
	asCVariableScope vs(0);

	if( node ) node = node->firstChild;
	while( node )
	{
		// Get the parameter type
		asCDataType type = builder->CreateDataTypeFromNode(node, script);

		asETypeModifiers inoutFlag = asTM_NONE;
		type = builder->ModifyDataTypeFromNode(type, node->next, script, &inoutFlag, 0);

		// Is the data type allowed?
		if( (type.IsReference() && inoutFlag != asTM_INOUTREF && !type.CanBeInstanciated()) ||
			(!type.IsReference() && !type.CanBeInstanciated()) )
		{
			asCString str;
			str.Format(TXT_PARAMETER_CANT_BE_s, type.Format().AddressOf());
			Error(str.AddressOf(), node);
		}

		// If the parameter has a name then declare it as variable
		node = node->next->next;
		if( node && node->nodeType == snIdentifier )
		{
			asCString name(&script->code[node->tokenPos], node->tokenLength);

			if( vs.DeclareVariable(name.AddressOf(), type, stackPos, true) < 0 )
				Error(TXT_PARAMETER_ALREADY_DECLARED, node);

			outFunc->AddVariable(name, type, stackPos);

			node = node->next;
		}
		else
			vs.DeclareVariable("", type, stackPos, true);

		// Move to next parameter
		stackPos -= type.GetSizeOnStackDWords();
	}

	int n;
	for( n = (int)vs.variables.GetLength() - 1; n >= 0; n-- )
	{
		variables->DeclareVariable(vs.variables[n]->name.AddressOf(), vs.variables[n]->type, vs.variables[n]->stackOffset, vs.variables[n]->onHeap);
	}

	// Is the return type allowed?
	if( (returnType.GetSizeOnStackDWords() == 0 && returnType != asCDataType::CreatePrimitive(ttVoid, false)) ||
		(returnType.IsReference() && !returnType.CanBeInstanciated()) )
	{
		asCString str;
		str.Format(TXT_RETURN_CANT_BE_s, returnType.Format().AddressOf());
		Error(str.AddressOf(), node);
	}

	variables->DeclareVariable("return", returnType, stackPos, true);

	//--------------------------------------------
	// Compile the statement block

	// We need to parse the statement block now

	// TODO: memory: We can parse the statement block one statement at a time, thus save even more memory
	asCParser parser(builder);
	int r = parser.ParseStatementBlock(script, func->lastChild);
	if( r < 0 ) return -1;
	asCScriptNode *block = parser.GetScriptNode();

	bool hasReturn;
	asCByteCode bc(engine);
	LineInstr(&bc, func->lastChild->tokenPos);
	CompileStatementBlock(block, false, &hasReturn, &bc);
	LineInstr(&bc, func->lastChild->tokenPos + func->lastChild->tokenLength);

	// Make sure there is a return in all paths (if not return type is void)
	if( returnType != asCDataType::CreatePrimitive(ttVoid, false) )
	{
		if( hasReturn == false )
			Error(TXT_NOT_ALL_PATHS_RETURN, func->lastChild);
	}

	//------------------------------------------------
	// Concatenate the bytecode

	// Insert a JitEntry at the start of the function for JIT compilers
	byteCode.InstrWORD(asBC_JitEntry, 0);

	// Count total variable size
	int varSize = GetVariableOffset((int)variableAllocations.GetLength()) - 1;
	byteCode.Push(varSize);

	if( outFunc->objectType )
	{
		// Call the base class' default constructor unless called manually in the code
		if( m_isConstructor && !m_isConstructorCalled && outFunc->objectType->derivedFrom )
		{
			byteCode.InstrSHORT(asBC_PSF, 0);
			byteCode.Instr(asBC_RDSPTR);
			byteCode.Call(asBC_CALL, outFunc->objectType->derivedFrom->beh.construct, AS_PTR_SIZE);
		}

		// Increase the reference for the object pointer, so that it is guaranteed to live during the entire call
		// TODO: optimize: This is probably not necessary for constructors as no outside reference to the object is created yet
		byteCode.InstrSHORT(asBC_PSF, 0);
		byteCode.Instr(asBC_RDSPTR);
		byteCode.Call(asBC_CALLSYS, outFunc->objectType->beh.addref, AS_PTR_SIZE);
	}

	// Add the code for the statement block
	byteCode.AddCode(&bc);

	// Deallocate all local variables
	for( n = (int)variables->variables.GetLength() - 1; n >= 0; n-- )
	{
		sVariable *v = variables->variables[n];
		if( v->stackOffset > 0 )
		{
			// Call variables destructors
			if( v->name != "return" && v->name != "return address" )
				CallDestructor(v->type, v->stackOffset, v->onHeap, &byteCode);

			DeallocateVariable(v->stackOffset);
		}
	}

	// This is the label that return statements jump to
	// in order to exit the function
	byteCode.Label(0);

	// Call destructors for function parameters
	for( n = (int)variables->variables.GetLength() - 1; n >= 0; n-- )
	{
		sVariable *v = variables->variables[n];
		if( v->stackOffset <= 0 )
		{
			// Call variable destructors here, for variables not yet destroyed
			if( v->name != "return" && v->name != "return address" )
				CallDestructor(v->type, v->stackOffset, v->onHeap, &byteCode);
		}

		// Do not deallocate parameters
	}

	// Release the object pointer again
	if( outFunc->objectType )
	{
		byteCode.InstrW_PTR(asBC_FREE, 0, outFunc->objectType);
	}

	// If there are compile errors, there is no reason to build the final code
	if( hasCompileErrors || builder->numErrors != buildErrors ) 
		return -1;

	// At this point there should be no variables allocated
	asASSERT(variableAllocations.GetLength() == freeVariables.GetLength());

	// Remove the variable scope
	RemoveVariableScope();

	// This POP is not necessary as the return will clean up the stack frame anyway.
	// The bytecode optimizer would remove this POP, however by not including it here
	// it is guaranteed it doesn't have to be adjusted by the asCRestore class when
	// a types are of a different size than originally compiled for.
	// byteCode.Pop(varSize);

	byteCode.Ret(-stackPos);

	FinalizeFunction();

#ifdef AS_DEBUG
	// DEBUG: output byte code
	if( outFunc->objectType )
		byteCode.DebugOutput(("__" + outFunc->objectType->name + "_" + outFunc->name + ".txt").AddressOf(), engine, outFunc);
	else
		byteCode.DebugOutput(("__" + outFunc->name + ".txt").AddressOf(), engine, outFunc);
#endif

	return 0;
}

int asCCompiler::CallCopyConstructor(asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc, asSExprContext *arg, asCScriptNode *node, bool isGlobalVar)
{
	if( !type.IsObject() )
		return 0;

	// CallCopyConstructor should not be called for object handles.
	asASSERT(!type.IsObjectHandle());

	asCArray<asSExprContext*> args;
	args.PushLast(arg);

	// The reference parameter must be pushed on the stack
	asASSERT( arg->type.dataType.GetObjectType() == type.GetObjectType() );

	// Since we're calling the copy constructor, we have to trust the function to not do 
	// anything stupid otherwise we will just enter a loop, as we try to make temporary
	// copies of the argument in order to guarantee safety.


	if( type.GetObjectType()->flags & asOBJ_REF )
	{
		asSExprContext ctx(engine);

		int func = 0;
		asSTypeBehaviour *beh = type.GetBehaviour();
		if( beh ) func = beh->copyfactory;

		if( func > 0 )
		{
			if( !isGlobalVar )
			{
				// Call factory and store the handle in the given variable
				PerformFunctionCall(func, &ctx, false, &args, type.GetObjectType(), true, offset);

				// Pop the reference left by the function call
				ctx.bc.Pop(AS_PTR_SIZE);
			}
			else
			{
				// Call factory
				PerformFunctionCall(func, &ctx, false, &args, type.GetObjectType());

				// Store the returned handle in the global variable
				ctx.bc.Instr(asBC_RDSPTR);
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				ctx.bc.InstrPTR(asBC_REFCPY, type.GetObjectType());
				ctx.bc.Pop(AS_PTR_SIZE);
				ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
			}

			bc->AddCode(&ctx.bc);

			return 0;
		}
	}
	else
	{
		asSTypeBehaviour *beh = type.GetBehaviour();
		int func = beh ? beh->copyconstruct : 0;
		if( func > 0 ) 
		{
			// Push the address where the object will be stored on the stack, before the argument
			// TODO: When the context is serializable this probably has to be changed, since this
			//       pointer can remain on the stack while the context is suspended. There is no
			//       risk the pointer becomes invalid though, there is just no easy way to serialize it.
			asCByteCode tmp(engine);
			if( isGlobalVar )
				tmp.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
			else if( isObjectOnHeap )
				tmp.InstrSHORT(asBC_PSF, (short)offset);
			tmp.AddCode(bc);
			bc->AddCode(&tmp);

			// When the object is allocated on the stack the object pointer 
			// must be pushed on the stack after the arguments
			if( !isObjectOnHeap )
			{
				asASSERT( !isGlobalVar );
				bc->InstrSHORT(asBC_PSF, (short)offset);
			}

			asSExprContext ctx(engine);
			PerformFunctionCall(func, &ctx, isObjectOnHeap, &args, type.GetObjectType());

			bc->AddCode(&ctx.bc);

			// TODO: value on stack: This probably needs to be done in PerformFunctionCall
			// Mark the object as initialized
			if( !isObjectOnHeap )
				bc->ObjInfo(offset, asOBJ_INIT); 


			return 0;
		}
	}

	// Class has no copy constructor/factory.
	asCString str;
	str.Format(TXT_NO_COPY_CONSTRUCTOR_FOR_s, type.GetObjectType()->GetName());
	Error(str.AddressOf(), node);

	return -1;
}

int asCCompiler::CallDefaultConstructor(asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc, asCScriptNode *node, bool isGlobalVar)
{
	if( !type.IsObject() || type.IsObjectHandle() )
		return 0;

	if( type.GetObjectType()->flags & asOBJ_REF )
	{
		asSExprContext ctx(engine);

		int func = 0;
		asSTypeBehaviour *beh = type.GetBehaviour();
		if( beh ) func = beh->factory;

		if( func > 0 )
		{
			if( !isGlobalVar )
			{
				// Call factory and store the handle in the given variable
				PerformFunctionCall(func, &ctx, false, 0, type.GetObjectType(), true, offset);

				// Pop the reference left by the function call
				ctx.bc.Pop(AS_PTR_SIZE);
			}
			else
			{
				// Call factory
				PerformFunctionCall(func, &ctx, false, 0, type.GetObjectType());

				// Store the returned handle in the global variable
				ctx.bc.Instr(asBC_RDSPTR);
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				ctx.bc.InstrPTR(asBC_REFCPY, type.GetObjectType());
				ctx.bc.Pop(AS_PTR_SIZE);
				ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
			}

			bc->AddCode(&ctx.bc);

			return 0;
		}
	}
	else
	{
		asSTypeBehaviour *beh = type.GetBehaviour();

		int func = 0;
		if( beh ) func = beh->construct;

		// Allocate and initialize with the default constructor
		if( func != 0 || (type.GetObjectType()->flags & asOBJ_POD) )
		{
			if( !isObjectOnHeap )
			{
				asASSERT( !isGlobalVar );

				// There is nothing to do if there is no function, 
				// as the memory is already allocated on the stack
				if( func )
				{
					// Call the constructor as a normal function
					bc->InstrSHORT(asBC_PSF, (short)offset);
					asSExprContext ctx(engine);
					PerformFunctionCall(func, &ctx, false, 0, type.GetObjectType());
					bc->AddCode(&ctx.bc);

					// TODO: value on stack: This probably needs to be done in PerformFunctionCall
					// Mark the object as initialized
					bc->ObjInfo(offset, asOBJ_INIT); 
				}
			}
			else
			{
				if( isGlobalVar )
					bc->InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				else
					bc->InstrSHORT(asBC_PSF, (short)offset);

				bc->Alloc(asBC_ALLOC, type.GetObjectType(), func, AS_PTR_SIZE);
			}

			return 0;
		}
	}

	// Class has no default factory/constructor.
	asCString str;
	// TODO: funcdef: asCDataType should have a GetTypeName()
	if( type.GetFuncDef() )
		str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, type.GetFuncDef()->GetName());
	else
		str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, type.GetObjectType()->GetName());
	Error(str.AddressOf(), node);

	return -1;
}

void asCCompiler::CallDestructor(asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc)
{
	if( !type.IsReference() )
	{
		// Call destructor for the data type
		if( type.IsObject() )
		{
			if( isObjectOnHeap || type.IsObjectHandle() )
			{
				// Free the memory
				bc->InstrW_PTR(asBC_FREE, (short)offset, type.GetObjectType());
			}
			else 
			{
				asASSERT( type.GetObjectType()->GetFlags() & asOBJ_VALUE );

				if( type.GetBehaviour()->destruct )
				{
					// Call the destructor as a regular function
					bc->InstrSHORT(asBC_PSF, offset);
					asSExprContext ctx(engine);
					PerformFunctionCall(type.GetBehaviour()->destruct, &ctx);
					bc->AddCode(&ctx.bc);
				}

				// TODO: Value on stack: This probably needs to be done in PerformFunctionCall
				// Mark the object as destroyed
				bc->ObjInfo(offset, asOBJ_UNINIT);
			}
		}
	}
}

void asCCompiler::LineInstr(asCByteCode *bc, size_t pos)
{
	int r, c;
	script->ConvertPosToRowCol(pos, &r, &c);
	bc->Line(r, c);
}

void asCCompiler::CompileStatementBlock(asCScriptNode *block, bool ownVariableScope, bool *hasReturn, asCByteCode *bc)
{
	*hasReturn = false;
	bool isFinished = false;
	bool hasWarned = false;

	if( ownVariableScope )
	{
		bc->Block(true);
		AddVariableScope();
	}

	asCScriptNode *node = block->firstChild;
	while( node )
	{
		if( !hasWarned && (*hasReturn || isFinished) )
		{
			hasWarned = true;
			Warning(TXT_UNREACHABLE_CODE, node);
		}

		if( node->nodeType == snBreak || node->nodeType == snContinue )
			isFinished = true;

		asCByteCode statement(engine);
		if( node->nodeType == snDeclaration )
			CompileDeclaration(node, &statement);
		else
			CompileStatement(node, hasReturn, &statement);

		LineInstr(bc, node->tokenPos);
		bc->AddCode(&statement);

		if( !hasCompileErrors )
			asASSERT( tempVariables.GetLength() == 0 );

		node = node->next;
	}

	if( ownVariableScope )
	{

		// Deallocate variables in this block, in reverse order
		for( int n = (int)variables->variables.GetLength() - 1; n >= 0; n-- )
		{
			sVariable *v = variables->variables[n];

			// Call variable destructors here, for variables not yet destroyed
			// If the block is terminated with a break, continue, or
			// return the variables are already destroyed
			if( !isFinished && !*hasReturn )
				CallDestructor(v->type, v->stackOffset, v->onHeap, bc);

			// Don't deallocate function parameters
			if( v->stackOffset > 0 )
				DeallocateVariable(v->stackOffset);
		}

		RemoveVariableScope();
		bc->Block(false);
	}
}

// Entry
int asCCompiler::CompileGlobalVariable(asCBuilder *builder, asCScriptCode *script, asCScriptNode *node, sGlobalVariableDescription *gvar, asCScriptFunction *outFunc)
{
	Reset(builder, script, outFunc);
	globalExpression = true;

	// Add a variable scope (even though variables can't be declared)
	AddVariableScope();

	asSExprContext ctx(engine);

	gvar->isPureConstant = false;

	// Parse the initialization nodes
	asCParser parser(builder);
	if( node )
	{
		int r = parser.ParseGlobalVarInit(script, node);
		if( r < 0 )
			return r;

		node = parser.GetScriptNode();
	}

	// Compile the expression
	if( node && node->nodeType == snArgList )
	{
		// Make sure that it is a registered type, and that it isn't a pointer
		if( gvar->datatype.GetObjectType() == 0 || gvar->datatype.IsObjectHandle() )
		{
			Error(TXT_MUST_BE_OBJECT, node);
		}
		else
		{
			// Compile the arguments
			asCArray<asSExprContext *> args;
			if( CompileArgumentList(node, args) >= 0 )
			{
				// Find all constructors
				asCArray<int> funcs;
				asSTypeBehaviour *beh = gvar->datatype.GetBehaviour();
				if( beh )
				{
					if( gvar->datatype.GetObjectType()->flags & asOBJ_REF )
						funcs = beh->factories;
					else
						funcs = beh->constructors;
				}

				asCString str = gvar->datatype.Format();
				MatchFunctions(funcs, args, node, str.AddressOf());

				if( funcs.GetLength() == 1 )
				{
					if( gvar->datatype.GetObjectType()->flags & asOBJ_REF )
					{
						MakeFunctionCall(&ctx, funcs[0], 0, args, node);

						// Store the returned handle in the global variable
						ctx.bc.Instr(asBC_RDSPTR);
						ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[gvar->index]->GetAddressOfValue());
						ctx.bc.InstrPTR(asBC_REFCPY, gvar->datatype.GetObjectType());
						ctx.bc.Pop(AS_PTR_SIZE);
						ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
					}
					else
					{
						// Push the address of the location where the variable will be stored on the stack.
						// This reference is safe, because the addresses of the global variables cannot change.
						// TODO: When serialization of the context is implemented this will probably have to change, 
						//       because this pointer may be on the stack while the context is suspended, and may
						//       be difficult to serialize as the context doesn't know that the value represents a 
						//       pointer.
						ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[gvar->index]->GetAddressOfValue());

						PrepareFunctionCall(funcs[0], &ctx.bc, args);
						MoveArgsToStack(funcs[0], &ctx.bc, args, false);

						PerformFunctionCall(funcs[0], &ctx, true, &args, gvar->datatype.GetObjectType());
					}
				}
			}

			// Cleanup
			for( asUINT n = 0; n < args.GetLength(); n++ )
				if( args[n] )
				{
					asDELETE(args[n],asSExprContext);
				}
		}
	}
	else if( node && node->nodeType == snInitList )
	{
		asCTypeInfo ti;
		ti.Set(gvar->datatype);
		ti.isVariable = false;
		ti.isTemporary = false;
		ti.stackOffset = (short)gvar->index;

		CompileInitList(&ti, node, &ctx.bc);

		node = node->next;
	}
	else if( node )
	{
		// Compile the right hand expression
		asSExprContext expr(engine);
		int r = CompileAssignment(node, &expr); if( r < 0 ) return r;

		// Assign the value to the variable
		if( gvar->datatype.IsPrimitive() )
		{
			if( gvar->datatype.IsReadOnly() && expr.type.isConstant )
			{
				ImplicitConversion(&expr, gvar->datatype, node, asIC_IMPLICIT_CONV);

				gvar->isPureConstant = true;
				gvar->constantValue = expr.type.qwordValue;
			}

			asSExprContext lctx(engine);
			lctx.type.Set(gvar->datatype);
			lctx.type.dataType.MakeReference(true);
			lctx.type.dataType.MakeReadOnly(false);

			// If it is an enum value that is being compiled, then
			// we skip this, as the bytecode won't be used anyway
			if( !gvar->isEnumValue )
				lctx.bc.InstrPTR(asBC_LDG, engine->globalProperties[gvar->index]->GetAddressOfValue());

			DoAssignment(&ctx, &lctx, &expr, node, node, ttAssignment, node);
		}
		else
		{
			// TODO: copy: Here we should look for the best matching constructor, instead of
			//             just the copy constructor. Only if no appropriate constructor is 
			//             available should the assignment operator be used.

			if( !gvar->datatype.IsObjectHandle() )
			{
				// Call the default constructor to have a valid object for the assignment
				CallDefaultConstructor(gvar->datatype, gvar->index, true, &ctx.bc, gvar->idNode, true);
			}

			asSExprContext lexpr(engine);
			lexpr.type.Set(gvar->datatype);
			lexpr.type.dataType.MakeReference(true);
			lexpr.type.dataType.MakeReadOnly(false);
			lexpr.type.stackOffset = -1;

			if( gvar->datatype.IsObjectHandle() )
				lexpr.type.isExplicitHandle = true;

			lexpr.bc.InstrPTR(asBC_PGA, engine->globalProperties[gvar->index]->GetAddressOfValue());

			// If left expression resolves into a registered type
			// check if the assignment operator is overloaded, and check
			// the type of the right hand expression. If none is found
			// the default action is a direct copy if it is the same type
			// and a simple assignment.
			bool assigned = false;
			if( lexpr.type.dataType.IsObject() && !lexpr.type.isExplicitHandle )
			{
				assigned = CompileOverloadedDualOperator(node, &lexpr, &expr, &ctx);
				if( assigned )
				{
					// Pop the resulting value
					ctx.bc.Pop(ctx.type.dataType.GetSizeOnStackDWords());

					// Release the argument
					ProcessDeferredParams(&ctx);
				}
			}

			if( !assigned )
			{
				PrepareForAssignment(&lexpr.type.dataType, &expr, node);

				// If the expression is constant and the variable also is constant
				// then mark the variable as pure constant. This will allow the compiler
				// to optimize expressions with this variable.
				if( gvar->datatype.IsReadOnly() && expr.type.isConstant )
				{
					gvar->isPureConstant = true;
					gvar->constantValue = expr.type.qwordValue;
				}

				// Add expression code to bytecode
				MergeExprBytecode(&ctx, &expr);

				// Add byte code for storing value of expression in variable
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[gvar->index]->GetAddressOfValue());

				PerformAssignment(&lexpr.type, &expr.type, &ctx.bc, node);

				// Release temporary variables used by expression
				ReleaseTemporaryVariable(expr.type, &ctx.bc);

				ctx.bc.Pop(expr.type.dataType.GetSizeOnStackDWords());
			}
		}
	}
	else if( gvar->datatype.IsObject() && !gvar->datatype.IsObjectHandle() )
	{
		// Call the default constructor in case no explicit initialization is given
		CallDefaultConstructor(gvar->datatype, gvar->index, true, &ctx.bc, gvar->idNode, true);
	}

	// Concatenate the bytecode
	int varSize = GetVariableOffset((int)variableAllocations.GetLength()) - 1;

	// Add information on the line number for the global variable
	size_t pos = 0;
	if( gvar->idNode )
		pos = gvar->idNode->tokenPos;
	else if( gvar->nextNode ) 
		pos = gvar->nextNode->tokenPos;
	LineInstr(&byteCode, pos);

	// We need to push zeroes on the stack to guarantee
	// that temporary object handles are clear
	int n;
	for( n = 0; n < varSize; n++ )
		byteCode.InstrINT(asBC_PshC4, 0);

	byteCode.AddCode(&ctx.bc);

	// Deallocate variables in this block, in reverse order
	for( n = (int)variables->variables.GetLength() - 1; n >= 0; --n )
	{
		sVariable *v = variables->variables[n];

		// Call variable destructors here, for variables not yet destroyed
		CallDestructor(v->type, v->stackOffset, v->onHeap, &byteCode);

		DeallocateVariable(v->stackOffset);
	}

	if( hasCompileErrors ) return -1;

	// At this point there should be no variables allocated
	asASSERT(variableAllocations.GetLength() == freeVariables.GetLength());

	// Remove the variable scope again
	RemoveVariableScope();

	byteCode.Ret(0);

	FinalizeFunction();

#ifdef AS_DEBUG
	// DEBUG: output byte code
	byteCode.DebugOutput(("___init_" + gvar->name + ".txt").AddressOf(), engine, outFunc);
#endif

	return 0;
}

void asCCompiler::FinalizeFunction()
{
	asUINT n;

	// Tell the bytecode which variables are temporary
	for( n = 0; n < variableIsTemporary.GetLength(); n++ )
	{
		if( variableIsTemporary[n] )
			byteCode.DefineTemporaryVariable(GetVariableOffset(n));
	}

	// Finalize the bytecode
	byteCode.Finalize();

	byteCode.ExtractObjectVariableInfo(outFunc);

	// Compile the list of object variables for the exception handler
	for( n = 0; n < variableAllocations.GetLength(); n++ )
	{
		if( variableAllocations[n].IsObject() && !variableAllocations[n].IsReference() )
		{
			outFunc->objVariableTypes.PushLast(variableAllocations[n].GetObjectType());
			outFunc->objVariablePos.PushLast(GetVariableOffset(n));
			outFunc->objVariableIsOnHeap.PushLast(variableIsOnHeap[n]);
		}
	}

	// Copy byte code to the function
	outFunc->byteCode.SetLength(byteCode.GetSize());
	byteCode.Output(outFunc->byteCode.AddressOf());
	outFunc->AddReferences();
	outFunc->stackNeeded = byteCode.largestStackUsed;
	outFunc->lineNumbers = byteCode.lineNumbers;
}

void asCCompiler::PrepareArgument(asCDataType *paramType, asSExprContext *ctx, asCScriptNode *node, bool isFunction, int refType, asCArray<int> *reservedVars, bool forceOnHeap)
{
	asCDataType param = *paramType;
	if( paramType->GetTokenType() == ttQuestion )
	{
		// Since the function is expecting a var type ?, then we don't want to convert the argument to anything else
		param = ctx->type.dataType;
		param.MakeHandle(ctx->type.isExplicitHandle);
		param.MakeReference(paramType->IsReference());
		param.MakeReadOnly(paramType->IsReadOnly());
	}
	else
		param = *paramType;

	asCDataType dt = param;

	// Need to protect arguments by reference
	if( isFunction && dt.IsReference() )
	{
		if( paramType->GetTokenType() == ttQuestion )
		{
			asCByteCode tmpBC(engine);

			// Place the type id on the stack as a hidden parameter
			tmpBC.InstrDWORD(asBC_TYPEID, engine->GetTypeIdFromDataType(param));

			// Insert the code before the expression code
			tmpBC.AddCode(&ctx->bc);
			ctx->bc.AddCode(&tmpBC);
		}

		// Allocate a temporary variable of the same type as the argument
		dt.MakeReference(false);
		dt.MakeReadOnly(false);

		int offset;
		if( refType == 1 ) // &in
		{
			ProcessPropertyGetAccessor(ctx, node);

			// If the reference is const, then it is not necessary to make a copy if the value already is a variable
			// Even if the same variable is passed in another argument as non-const then there is no problem
			if( dt.IsPrimitive() || dt.IsNullHandle() )
			{
				IsVariableInitialized(&ctx->type, node);

				if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);
				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true, reservedVars);

				if( !(param.IsReadOnly() && ctx->type.isVariable) )
					ConvertToTempVariable(ctx);

				PushVariableOnStack(ctx, true);
				ctx->type.dataType.MakeReadOnly(param.IsReadOnly());
			}
			else
			{
				IsVariableInitialized(&ctx->type, node);

				ImplicitConversion(ctx, param, node, asIC_IMPLICIT_CONV, true, reservedVars);

				if( !ctx->type.dataType.IsEqualExceptRef(param) )
				{
					asCString str;
					str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format().AddressOf(), param.Format().AddressOf());
					Error(str.AddressOf(), node);

					ctx->type.Set(param);
				}

				// If the argument already is a temporary
				// variable we don't need to allocate another

				// If the parameter is read-only and the object already is a local
				// variable then it is not necessary to make a copy either
				if( !ctx->type.isTemporary && !(param.IsReadOnly() && ctx->type.isVariable) )
				{
					// Make sure the variable is not used in the expression
					asCArray<int> vars;
					ctx->bc.GetVarsUsed(vars);
					if( reservedVars ) vars.Concatenate(*reservedVars);
					offset = AllocateVariableNotIn(dt, true, &vars);

					// TODO: copy: Use copy constructor if available. See PrepareTemporaryObject()

					// Allocate and construct the temporary object
					asCByteCode tmpBC(engine);

					CallDefaultConstructor(dt, offset, IsVariableOnHeap(offset), &tmpBC, node);

					// Insert the code before the expression code
					tmpBC.AddCode(&ctx->bc);
					ctx->bc.AddCode(&tmpBC);

					// Assign the evaluated expression to the temporary variable
					PrepareForAssignment(&dt, ctx, node);

					dt.MakeReference(IsVariableOnHeap(offset));
					asCTypeInfo type;
					type.Set(dt);
					type.isTemporary = true;
					type.stackOffset = (short)offset;

					if( dt.IsObjectHandle() )
						type.isExplicitHandle = true;

					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);

					PerformAssignment(&type, &ctx->type, &ctx->bc, node);

					ctx->bc.Pop(ctx->type.dataType.GetSizeOnStackDWords());

					ReleaseTemporaryVariable(ctx->type, &ctx->bc);

					ctx->type = type;

					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
					if( dt.IsObject() && !dt.IsObjectHandle() )
						ctx->bc.Instr(asBC_RDSPTR);

					if( paramType->IsReadOnly() )
						ctx->type.dataType.MakeReadOnly(true);
				}
			}
		}
		else if( refType == 2 ) // &out
		{
			// Make sure the variable is not used in the expression
			asCArray<int> vars;
			ctx->bc.GetVarsUsed(vars);
			if( reservedVars ) vars.Concatenate(*reservedVars);
			offset = AllocateVariableNotIn(dt, true, &vars);

			if( dt.IsPrimitive() )
			{
				ctx->type.SetVariable(dt, offset, true);
				PushVariableOnStack(ctx, true);
			}
			else
			{
				// Allocate and construct the temporary object
				asCByteCode tmpBC(engine);
				CallDefaultConstructor(dt, offset, IsVariableOnHeap(offset), &tmpBC, node);

				// Insert the code before the expression code
				tmpBC.AddCode(&ctx->bc);
				ctx->bc.AddCode(&tmpBC);

				dt.MakeReference((!dt.IsObject() || dt.IsObjectHandle()));
				asCTypeInfo type;
				type.Set(dt);
				type.isTemporary = true;
				type.stackOffset = (short)offset;

				ctx->type = type;

				ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
				if( dt.IsObject() && !dt.IsObjectHandle() )
					ctx->bc.Instr(asBC_RDSPTR);
			}

			// After the function returns the temporary variable will
			// be assigned to the expression, if it is a valid lvalue
		}
		else if( refType == asTM_INOUTREF )
		{
			// Literal constants cannot be passed to inout ref arguments
			if( !ctx->type.isVariable && ctx->type.isConstant )
			{
				Error(TXT_NOT_VALID_REFERENCE, node);
			}

			// Only objects that support object handles
			// can be guaranteed to be safe. Local variables are
			// already safe, so there is no need to add an extra
			// references
			if( !engine->ep.allowUnsafeReferences &&
				!ctx->type.isVariable &&
				ctx->type.dataType.IsObject() &&
				!ctx->type.dataType.IsObjectHandle() &&
				ctx->type.dataType.GetBehaviour()->addref &&
				ctx->type.dataType.GetBehaviour()->release )
			{
				// Store a handle to the object as local variable
				asSExprContext tmp(engine);
				asCDataType dt = ctx->type.dataType;
				dt.MakeHandle(true);
				dt.MakeReference(false);

				asCArray<int> vars;
				ctx->bc.GetVarsUsed(vars);
				if( reservedVars ) vars.Concatenate(*reservedVars);
				offset = AllocateVariableNotIn(dt, true, &vars);

				// Copy the handle
				if( !ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsReference() )
					ctx->bc.Instr(asBC_RDSPTR);
				ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);
				ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetObjectType());
				ctx->bc.Pop(AS_PTR_SIZE);
				ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);

				dt.MakeHandle(false);
				dt.MakeReference(true);

				// Release previous temporary variable stored in the context (if any)
				if( ctx->type.isTemporary )
				{
					ReleaseTemporaryVariable(ctx->type.stackOffset, &ctx->bc);
				}

				ctx->type.SetVariable(dt, offset, true);
			}

			// Make sure the reference to the value is on the stack
			if( ctx->type.dataType.IsObject() && ctx->type.dataType.IsReference() )
				Dereference(ctx, true);
			else if( ctx->type.isVariable && !ctx->type.dataType.IsObject() )
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			else if( ctx->type.dataType.IsPrimitive() )
				ctx->bc.Instr(asBC_PshRPtr);
		}
	}
	else
	{
		ProcessPropertyGetAccessor(ctx, node);

		if( dt.IsPrimitive() )
		{
			IsVariableInitialized(&ctx->type, node);

			if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);

			// Implicitly convert primitives to the parameter type
			ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true, reservedVars);

			if( ctx->type.isVariable )
			{
				PushVariableOnStack(ctx, dt.IsReference());
			}
			else if( ctx->type.isConstant )
			{
				ConvertToVariable(ctx);
				PushVariableOnStack(ctx, dt.IsReference());
			}
		}
		else
		{
			IsVariableInitialized(&ctx->type, node);

			// Implicitly convert primitives to the parameter type
			ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true, reservedVars);

			// Was the conversion successful?
			if( !ctx->type.dataType.IsEqualExceptRef(dt) )
			{
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format().AddressOf(), dt.Format().AddressOf());
				Error(str.AddressOf(), node);

				ctx->type.Set(dt);
			}

			if( dt.IsObjectHandle() )
				ctx->type.isExplicitHandle = true;

			if( dt.IsObject() )
			{
				if( !dt.IsReference() )
				{
					// Objects passed by value must be placed in temporary variables
					// so that they are guaranteed to not be referenced anywhere else.
					// The object must also be allocated on the heap, as the memory will
					// be deleted by in as_callfunc_xxx. 
					// TODO: value on stack: How can we avoid this unnecessary allocation?
					PrepareTemporaryObject(node, ctx, reservedVars, true);

					// The implicit conversion shouldn't convert the object to
					// non-reference yet. It will be dereferenced just before the call.
					// Otherwise the object might be missed by the exception handler.
					dt.MakeReference(true);
				}
				else
				{
					// An object passed by reference should place the pointer to
					// the object on the stack.
					dt.MakeReference(false);
				}
			}
		}
	}

	// Don't put any pointer on the stack yet
	if( param.IsReference() || param.IsObject() )
	{
		// &inout parameter may leave the reference on the stack already
		if( refType != 3 )
		{
			ctx->bc.Pop(AS_PTR_SIZE);
			ctx->bc.InstrSHORT(asBC_VAR, ctx->type.stackOffset);
		}

		ProcessDeferredParams(ctx);
	}
}

void asCCompiler::PrepareFunctionCall(int funcID, asCByteCode *bc, asCArray<asSExprContext *> &args)
{
	// When a match has been found, compile the final byte code using correct parameter types
	asCScriptFunction *descr = builder->GetFunctionDescription(funcID);

	// Add code for arguments
	asSExprContext e(engine);
	int n;
	for( n = (int)args.GetLength()-1; n >= 0; n-- )
	{
		// Make sure PrepareArgument doesn't use any variable that is already
		// being used by any of the following argument expressions
		asCArray<int> reservedVars;
		for( int m = n-1; m >= 0; m-- )
			args[m]->bc.GetVarsUsed(reservedVars);

		PrepareArgument2(&e, args[n], &descr->parameterTypes[n], true, descr->inOutFlags[n], &reservedVars);
	}

	bc->AddCode(&e.bc);
}

void asCCompiler::MoveArgsToStack(int funcID, asCByteCode *bc, asCArray<asSExprContext *> &args, bool addOneToOffset)
{
	asCScriptFunction *descr = builder->GetFunctionDescription(funcID);

	int offset = 0;
	if( addOneToOffset )
		offset += AS_PTR_SIZE;

	// Move the objects that are sent by value to the stack just before the call
	for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
	{
		if( descr->parameterTypes[n].IsReference() )
		{
			if( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() )
			{
				if( descr->inOutFlags[n] != asTM_INOUTREF )
				{
					if( (args[n]->type.isVariable || args[n]->type.isTemporary) && 
						!IsVariableOnHeap(args[n]->type.stackOffset) )
						// TODO: optimize: Actually the reference can be pushed on the stack directly
						//                 as the value allocated on the stack is guaranteed to be safe
						bc->InstrWORD(asBC_GETREF, (asWORD)offset);
					else
						bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
				}
				if( args[n]->type.dataType.IsObjectHandle() )
					bc->InstrWORD(asBC_ChkNullS, (asWORD)offset);
			}
			else if( descr->inOutFlags[n] != asTM_INOUTREF )
			{
				if( descr->parameterTypes[n].GetTokenType() == ttQuestion &&
					args[n]->type.dataType.IsObject() && !args[n]->type.dataType.IsObjectHandle() )
				{
					// Send the object as a reference to the object, 
					// and not to the variable holding the object
					bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
				}
				else
					bc->InstrWORD(asBC_GETREF, (asWORD)offset);
			}
		}
		else if( descr->parameterTypes[n].IsObject() )
		{
			// TODO: value on stack: What can we do to avoid this unnecessary allocation?
			// The object must be allocated on the heap, because this memory will be deleted in as_callfunc_xxx
			asASSERT(IsVariableOnHeap(args[n]->type.stackOffset));

			bc->InstrWORD(asBC_GETOBJ, (asWORD)offset);

			// The temporary variable must not be freed as it will no longer hold an object
			DeallocateVariable(args[n]->type.stackOffset);
			args[n]->type.isTemporary = false;
		}

		offset += descr->parameterTypes[n].GetSizeOnStackDWords();
	}
}

int asCCompiler::CompileArgumentList(asCScriptNode *node, asCArray<asSExprContext*> &args)
{
	asASSERT(node->nodeType == snArgList);

	// Count arguments
	asCScriptNode *arg = node->firstChild;
	int argCount = 0;
	while( arg )
	{
		argCount++;
		arg = arg->next;
	}

	// Prepare the arrays
	args.SetLength(argCount);
	int n;
	for( n = 0; n < argCount; n++ )
		args[n] = 0;

	n = argCount-1;

	// Compile the arguments in reverse order (as they will be pushed on the stack)
	bool anyErrors = false;
	arg = node->lastChild;
	while( arg )
	{
		asSExprContext expr(engine);
		int r = CompileAssignment(arg, &expr);
		if( r < 0 ) anyErrors = true;

		args[n] = asNEW(asSExprContext)(engine);
		MergeExprBytecodeAndType(args[n], &expr);

		n--;
		arg = arg->prev;
	}

	return anyErrors ? -1 : 0;
}

void asCCompiler::MatchFunctions(asCArray<int> &funcs, asCArray<asSExprContext*> &args, asCScriptNode *node, const char *name, asCObjectType *objectType, bool isConstMethod, bool silent, bool allowObjectConstruct, const asCString &scope)
{
	asCArray<int> origFuncs = funcs; // Keep the original list for error message

	asUINT n;
	if( funcs.GetLength() > 0 )
	{
		// Check the number of parameters in the found functions
		for( n = 0; n < funcs.GetLength(); ++n )
		{
			asCScriptFunction *desc = builder->GetFunctionDescription(funcs[n]);

			if( desc->parameterTypes.GetLength() != args.GetLength() )
			{
				// remove it from the list
				if( n == funcs.GetLength()-1 )
					funcs.PopLast();
				else
					funcs[n] = funcs.PopLast();
				n--;
			}
		}

		// Match functions with the parameters, and discard those that do not match
		asCArray<int> matchingFuncs = funcs;

		for( n = 0; n < args.GetLength(); ++n )
		{
			asCArray<int> tempFuncs;
			MatchArgument(funcs, tempFuncs, &args[n]->type, n, allowObjectConstruct);

			// Intersect the found functions with the list of matching functions
			for( asUINT f = 0; f < matchingFuncs.GetLength(); f++ )
			{
				asUINT c;
				for( c = 0; c < tempFuncs.GetLength(); c++ )
				{
					if( matchingFuncs[f] == tempFuncs[c] )
						break;
				}

				// Was the function a match?
				if( c == tempFuncs.GetLength() )
				{
					// No, remove it from the list
					if( f == matchingFuncs.GetLength()-1 )
						matchingFuncs.PopLast();
					else
						matchingFuncs[f] = matchingFuncs.PopLast();
					f--;
				}
			}
		}

		funcs = matchingFuncs;
	}

	if( !isConstMethod )
		FilterConst(funcs);

	if( funcs.GetLength() != 1 && !silent )
	{
		// Build a readable string of the function with parameter types
		asCString str;
		if( scope != "" )
		{
			if( scope == "::" )
				str = scope;
			else
				str = scope + "::";
		}
		str += name;
		str += "(";
		if( args.GetLength() )
			str += args[0]->type.dataType.Format();
		for( n = 1; n < args.GetLength(); n++ )
			str += ", " + args[n]->type.dataType.Format();
		str += ")";

		if( isConstMethod )
			str += " const";

		if( objectType && scope == "" )
			str = objectType->name + "::" + str;

		if( funcs.GetLength() == 0 )
		{
			str.Format(TXT_NO_MATCHING_SIGNATURES_TO_s, str.AddressOf());
			Error(str.AddressOf(), node);

			// Print the list of candidates
			if( origFuncs.GetLength() > 0 )
			{
				int r = 0, c = 0;
				asASSERT( node );
				if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);
				builder->WriteInfo(script->name.AddressOf(), TXT_CANDIDATES_ARE, r, c, false);
				PrintMatchingFuncs(origFuncs, node);
			}
		}
		else
		{
			str.Format(TXT_MULTIPLE_MATCHING_SIGNATURES_TO_s, str.AddressOf());
			Error(str.AddressOf(), node);
	
			PrintMatchingFuncs(funcs, node);
		}
	}
}

void asCCompiler::CompileDeclaration(asCScriptNode *decl, asCByteCode *bc)
{
	// Get the data type
	asCDataType type = builder->CreateDataTypeFromNode(decl->firstChild, script);

	// Declare all variables in this declaration
	asCScriptNode *node = decl->firstChild->next;
	while( node )
	{
		// Is the type allowed?
		if( !type.CanBeInstanciated() )
		{
			asCString str;
			// TODO: Change to "'type' cannot be declared as variable"
			str.Format(TXT_DATA_TYPE_CANT_BE_s, type.Format().AddressOf());
			Error(str.AddressOf(), node);

			// Use int instead to avoid further problems
			type = asCDataType::CreatePrimitive(ttInt, false);
		}

		// Get the name of the identifier
		asCString name(&script->code[node->tokenPos], node->tokenLength);

		// Verify that the name isn't used by a dynamic data type
		if( engine->GetObjectType(name.AddressOf()) != 0 )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_VARIABLE_NAME_s, name.AddressOf());
			Error(str.AddressOf(), node);
		}

		int offset = AllocateVariable(type, false);
		if( variables->DeclareVariable(name.AddressOf(), type, offset, IsVariableOnHeap(offset)) < 0 )
		{
			asCString str;
			str.Format(TXT_s_ALREADY_DECLARED, name.AddressOf());
			Error(str.AddressOf(), node);

			// Don't continue after this error, as it will just 
			// lead to more errors that are likely false
			return;
		}

		outFunc->AddVariable(name, type, offset);

		// Keep the node for the variable decl
		asCScriptNode *varNode = node;

		node = node->next;
		if( node && node->nodeType == snArgList )
		{
			// Make sure that it is a registered type, and that is isn't a pointer
			if( type.GetObjectType() == 0 || type.IsObjectHandle() )
			{
				Error(TXT_MUST_BE_OBJECT, node);
			}
			else
			{
				// Compile the arguments
				asCArray<asSExprContext *> args;

				if( CompileArgumentList(node, args) >= 0 )
				{
					// Find all constructors
					asCArray<int> funcs;
					asSTypeBehaviour *beh = type.GetBehaviour();
					if( beh )
					{
						if( type.GetObjectType()->flags & asOBJ_REF )
							funcs = beh->factories;
						else
							funcs = beh->constructors;
					}

					asCString str = type.Format();
					MatchFunctions(funcs, args, node, str.AddressOf());

					if( funcs.GetLength() == 1 )
					{
						sVariable *v = variables->GetVariable(name.AddressOf());
						asSExprContext ctx(engine);
						if( v->type.GetObjectType() && (v->type.GetObjectType()->flags & asOBJ_REF) )
						{
							MakeFunctionCall(&ctx, funcs[0], 0, args, node, true, v->stackOffset);

							// Pop the reference left by the function call
							ctx.bc.Pop(AS_PTR_SIZE);
						}
						else
						{
							// When the object is allocated on the heap, the address where the 
							// reference will be stored must be pushed on the stack before the 
							// arguments. This reference on the stack is safe, even if the script
							// is suspended during the evaluation of the arguments.
							if( v->onHeap )
								ctx.bc.InstrSHORT(asBC_PSF, (short)v->stackOffset);

							PrepareFunctionCall(funcs[0], &ctx.bc, args);
							MoveArgsToStack(funcs[0], &ctx.bc, args, false);

							// When the object is allocated on the stack, the address to the
							// object is pushed on the stack after the arguments as the object pointer
							if( !v->onHeap )
								ctx.bc.InstrSHORT(asBC_PSF, (short)v->stackOffset);

							PerformFunctionCall(funcs[0], &ctx, v->onHeap, &args, type.GetObjectType());

							// TODO: value on stack: This probably has to be done in PerformFunctionCall
							// Mark the object as initialized
							ctx.bc.ObjInfo(v->stackOffset, asOBJ_INIT);
						}
						bc->AddCode(&ctx.bc);
					}
				}

				// Cleanup
				for( asUINT n = 0; n < args.GetLength(); n++ )
					if( args[n] )
					{
						asDELETE(args[n],asSExprContext);
					}
			}

			node = node->next;
		}
		else if( node && node->nodeType == snInitList )
		{
			sVariable *v = variables->GetVariable(name.AddressOf());

			asCTypeInfo ti;
			ti.Set(type);
			ti.isVariable = true;
			ti.isTemporary = false;
			ti.stackOffset = (short)v->stackOffset;

			CompileInitList(&ti, node, bc);

			node = node->next;
		}
		else if( node && node->nodeType == snAssignment )
		{
			asSExprContext ctx(engine);

			// TODO: copy: Here we should look for the best matching constructor, instead of
			//             just the copy constructor. Only if no appropriate constructor is 
			//             available should the assignment operator be used.

			// Call the default constructor here
			CallDefaultConstructor(type, offset, IsVariableOnHeap(offset), &ctx.bc, varNode);

			// Compile the expression
			asSExprContext expr(engine);
			int r = CompileAssignment(node, &expr);
			if( r >= 0 )
			{
				if( type.IsPrimitive() )
				{
					if( type.IsReadOnly() && expr.type.isConstant )
					{
						ImplicitConversion(&expr, type, node, asIC_IMPLICIT_CONV);

						sVariable *v = variables->GetVariable(name.AddressOf());
						v->isPureConstant = true;
						v->constantValue = expr.type.qwordValue;
					}

					asSExprContext lctx(engine);
					lctx.type.SetVariable(type, offset, false);
					lctx.type.dataType.MakeReadOnly(false);

					DoAssignment(&ctx, &lctx, &expr, node, node, ttAssignment, node);
					ProcessDeferredParams(&ctx);
				}
				else
				{
					// TODO: We can use a copy constructor here

					sVariable *v = variables->GetVariable(name.AddressOf());

					asSExprContext lexpr(engine);
					lexpr.type.Set(type);
					lexpr.type.dataType.MakeReference(v->onHeap);
					// Allow initialization of constant variables
					lexpr.type.dataType.MakeReadOnly(false);

					if( type.IsObjectHandle() )
						lexpr.type.isExplicitHandle = true;

					lexpr.bc.InstrSHORT(asBC_PSF, (short)v->stackOffset);
					lexpr.type.stackOffset = (short)v->stackOffset;
					lexpr.type.isVariable = true;


					// If left expression resolves into a registered type
					// check if the assignment operator is overloaded, and check
					// the type of the right hand expression. If none is found
					// the default action is a direct copy if it is the same type
					// and a simple assignment.
					bool assigned = false;
					if( lexpr.type.dataType.IsObject() && !lexpr.type.isExplicitHandle )
					{
						assigned = CompileOverloadedDualOperator(node, &lexpr, &expr, &ctx);
						if( assigned )
						{
							// Pop the resulting value
							ctx.bc.Pop(ctx.type.dataType.GetSizeOnStackDWords());

							// Release the argument
							ProcessDeferredParams(&ctx);

							// Release temporary variable that may be allocated by the overloaded operator
							ReleaseTemporaryVariable(ctx.type, &ctx.bc);
						}
					}

					if( !assigned )
					{
						PrepareForAssignment(&lexpr.type.dataType, &expr, node);

						// If the expression is constant and the variable also is constant
						// then mark the variable as pure constant. This will allow the compiler
						// to optimize expressions with this variable.
						if( v->type.IsReadOnly() && expr.type.isConstant )
						{
							v->isPureConstant = true;
							v->constantValue = expr.type.qwordValue;
						}

						// Add expression code to bytecode
						MergeExprBytecode(&ctx, &expr);

						// Add byte code for storing value of expression in variable
						ctx.bc.AddCode(&lexpr.bc);
						lexpr.type.stackOffset = (short)v->stackOffset;

						PerformAssignment(&lexpr.type, &expr.type, &ctx.bc, node->prev);

						// Release temporary variables used by expression
						ReleaseTemporaryVariable(expr.type, &ctx.bc);

						ctx.bc.Pop(expr.type.dataType.GetSizeOnStackDWords());

						ProcessDeferredParams(&ctx);
					}
				}
			}

			node = node->next;

			bc->AddCode(&ctx.bc);

			// TODO: Can't this leave deferred output params without being compiled?
		}
		else
		{
			// Call the default constructor here if no explicit initialization is done
			CallDefaultConstructor(type, offset, IsVariableOnHeap(offset), bc, varNode);
		}
	}
}

void asCCompiler::CompileInitList(asCTypeInfo *var, asCScriptNode *node, asCByteCode *bc)
{
	// Check if the type supports initialization lists
	if( var->dataType.GetObjectType() == 0 ||
		var->dataType.GetBehaviour()->listFactory == 0 ||
		var->dataType.IsObjectHandle() )
	{
		asCString str;
		str.Format(TXT_INIT_LIST_CANNOT_BE_USED_WITH_s, var->dataType.Format().AddressOf());
		Error(str.AddressOf(), node);
		return;
	}

	// Count the number of elements and initialize the array with the correct size
	int countElements = 0;
	asCScriptNode *el = node->firstChild;
	while( el )
	{
		countElements++;
		el = el->next;
	}

	// Construct the array with the size elements

	// TODO: value on stack: This needs to support value types on the stack as well

	// Find the list factory
	// TODO: initlist: Add support for value types as well
	int funcId = var->dataType.GetBehaviour()->listFactory;

	asCArray<asSExprContext *> args;
	asSExprContext arg1(engine);
	arg1.bc.InstrDWORD(asBC_PshC4, countElements);
	arg1.type.Set(asCDataType::CreatePrimitive(ttUInt, false));
	args.PushLast(&arg1);

	asSExprContext ctx(engine);

	PrepareFunctionCall(funcId, &ctx.bc, args);
	MoveArgsToStack(funcId, &ctx.bc, args, false);

	if( var->isVariable )
	{
		// Call factory and store the handle in the given variable
		PerformFunctionCall(funcId, &ctx, false, &args, 0, true, var->stackOffset);
		ctx.bc.Pop(AS_PTR_SIZE);
	}
	else
	{
		PerformFunctionCall(funcId, &ctx, false, &args);

		// Store the returned handle in the global variable
		ctx.bc.Instr(asBC_RDSPTR);
		ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[var->stackOffset]->GetAddressOfValue());
		ctx.bc.InstrPTR(asBC_REFCPY, var->dataType.GetObjectType());
		ctx.bc.Pop(AS_PTR_SIZE);
		ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
	}

	bc->AddCode(&ctx.bc);

	// TODO: initlist: Should we have a special indexing operator for this? How can we support
	//                 initialization lists with different types for different elements? Maybe 
	//                 by using the variable arguments the initialization can be done with one 
	//                 call, passing all the elements as arguments. The registered function can
	//                 then traverse them however it wants.

	// Find the indexing operator that is not read-only that will be used for all elements
	asCDataType retType;
	retType = var->dataType.GetSubType();
	retType.MakeReference(true);
	retType.MakeReadOnly(false);
	funcId = 0;
	for( asUINT n = 0; n < var->dataType.GetObjectType()->methods.GetLength(); n++ )
	{
		asCScriptFunction *desc = builder->GetFunctionDescription(var->dataType.GetObjectType()->methods[n]);
		if( !desc->isReadOnly &&
			 desc->parameterTypes.GetLength() == 1 &&
			 (desc->parameterTypes[0] == asCDataType::CreatePrimitive(ttUInt, false) ||
			  desc->parameterTypes[0] == asCDataType::CreatePrimitive(ttInt,  false)) &&
			 desc->returnType == retType &&
			 desc->name == "opIndex" )
		{
			funcId = var->dataType.GetObjectType()->methods[n];
			break;
		}
	}
#ifdef AS_DEPRECATED
	// Since 2.20.0
	if( funcId == 0 )
	{
		asSTypeBehaviour *beh = var->dataType.GetBehaviour();
		for( asUINT n = 0; n < beh->operators.GetLength(); n += 2 )
		{
			if( asBEHAVE_INDEX == beh->operators[n] )
			{
				asCScriptFunction *desc = builder->GetFunctionDescription(beh->operators[n+1]);
				if( !desc->isReadOnly &&
					 desc->parameterTypes.GetLength() == 1 &&
					 (desc->parameterTypes[0] == asCDataType::CreatePrimitive(ttUInt, false) ||
					  desc->parameterTypes[0] == asCDataType::CreatePrimitive(ttInt,  false)) &&
					 desc->returnType == retType )
				{
					funcId = beh->operators[n+1];
					break;
				}
			}
		}
	}
#endif
	if( funcId == 0 )
	{
		Error(TXT_NO_APPROPRIATE_INDEX_OPERATOR, node);
		return;
	}

	asUINT index = 0;
	el = node->firstChild;
	while( el )
	{
		if( el->nodeType == snAssignment || el->nodeType == snInitList )
		{
			asSExprContext lctx(engine);
			asSExprContext rctx(engine);

			if( el->nodeType == snAssignment )
			{
				// Compile the assignment expression
				CompileAssignment(el, &rctx);
			}
			else if( el->nodeType == snInitList )
			{
				int offset = AllocateVariable(var->dataType.GetSubType(), true);

				rctx.type.Set(var->dataType.GetSubType());
				rctx.type.isVariable = true;
				rctx.type.isTemporary = true;
				rctx.type.stackOffset = (short)offset;

				CompileInitList(&rctx.type, el, &rctx.bc);

				// Put the object on the stack
				rctx.bc.InstrSHORT(asBC_PSF, rctx.type.stackOffset);

				// It is a reference that we place on the stack
				rctx.type.dataType.MakeReference(true);
			}

			// Compile the lvalue
			lctx.bc.InstrDWORD(asBC_PshC4, index);
			if( var->isVariable )
				lctx.bc.InstrSHORT(asBC_PSF, var->stackOffset);
			else
				lctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[var->stackOffset]->GetAddressOfValue());
			lctx.bc.Instr(asBC_RDSPTR);
			lctx.bc.Call(asBC_CALLSYS, funcId, 1+AS_PTR_SIZE);

			if( !var->dataType.GetSubType().IsPrimitive() )
				lctx.bc.Instr(asBC_PshRPtr);

			lctx.type.Set(var->dataType.GetSubType());

			if( !lctx.type.dataType.IsObject() || lctx.type.dataType.IsObjectHandle() )
				lctx.type.dataType.MakeReference(true);

			// If the element type is handles, then we're expected to do handle assignments
			if( lctx.type.dataType.IsObjectHandle() )
				lctx.type.isExplicitHandle = true;

			asSExprContext ctx(engine);
			DoAssignment(&ctx, &lctx, &rctx, el, el, ttAssignment, el);

			if( !lctx.type.dataType.IsPrimitive() )
				ctx.bc.Pop(AS_PTR_SIZE);

			// Release temporary variables used by expression
			ReleaseTemporaryVariable(ctx.type, &ctx.bc);

			ProcessDeferredParams(&ctx);

			bc->AddCode(&ctx.bc);
		}

		el = el->next;
		index++;
	}
}

void asCCompiler::CompileStatement(asCScriptNode *statement, bool *hasReturn, asCByteCode *bc)
{
	*hasReturn = false;

	if( statement->nodeType == snStatementBlock )
		CompileStatementBlock(statement, true, hasReturn, bc);
	else if( statement->nodeType == snIf )
		CompileIfStatement(statement, hasReturn, bc);
	else if( statement->nodeType == snFor )
		CompileForStatement(statement, bc);
	else if( statement->nodeType == snWhile )
		CompileWhileStatement(statement, bc);
	else if( statement->nodeType == snDoWhile )
		CompileDoWhileStatement(statement, bc);
	else if( statement->nodeType == snExpressionStatement )
		CompileExpressionStatement(statement, bc);
	else if( statement->nodeType == snBreak )
		CompileBreakStatement(statement, bc);
	else if( statement->nodeType == snContinue )
		CompileContinueStatement(statement, bc);
	else if( statement->nodeType == snSwitch )
		CompileSwitchStatement(statement, hasReturn, bc);
	else if( statement->nodeType == snReturn )
	{
		CompileReturnStatement(statement, bc);
		*hasReturn = true;
	}
}

void asCCompiler::CompileSwitchStatement(asCScriptNode *snode, bool *, asCByteCode *bc)
{
	// TODO: inheritance: Must guarantee that all options in the switch case call a constructor, or that none call it.

	// Reserve label for break statements
	int breakLabel = nextLabel++;
	breakLabels.PushLast(breakLabel);

	// Add a variable scope that will be used by CompileBreak
	// to know where to stop deallocating variables
	AddVariableScope(true, false);

	//---------------------------
	// Compile the switch expression
	//-------------------------------

	// Compile the switch expression
	asSExprContext expr(engine);
	CompileAssignment(snode->firstChild, &expr);

	// Verify that the expression is a primitive type
	if( !expr.type.dataType.IsIntegerType() && !expr.type.dataType.IsUnsignedType() && !expr.type.dataType.IsEnumType() )
	{
		Error(TXT_SWITCH_MUST_BE_INTEGRAL, snode->firstChild);
		return;
	}

	ProcessPropertyGetAccessor(&expr, snode);

	// TODO: Need to support 64bit integers
	// Convert the expression to a 32bit variable
	asCDataType to;
	if( expr.type.dataType.IsIntegerType() || expr.type.dataType.IsEnumType() )
		to.SetTokenType(ttInt);
	else if( expr.type.dataType.IsUnsignedType() )
		to.SetTokenType(ttUInt);

	// Make sure the value is in a variable
	if( expr.type.dataType.IsReference() ) 
		ConvertToVariable(&expr);

	ImplicitConversion(&expr, to, snode->firstChild, asIC_IMPLICIT_CONV, true);

	ConvertToVariable(&expr);
	int offset = expr.type.stackOffset;

	ProcessDeferredParams(&expr);

	//-------------------------------
	// Determine case values and labels
	//--------------------------------

	// Remember the first label so that we can later pass the
	// correct label to each CompileCase()
	int firstCaseLabel = nextLabel;
	int defaultLabel = 0;

	asCArray<int> caseValues;
	asCArray<int> caseLabels;

	// Compile all case comparisons and make them jump to the right label
	asCScriptNode *cnode = snode->firstChild->next;
	while( cnode )
	{
		// Each case should have a constant expression
		if( cnode->firstChild && cnode->firstChild->nodeType == snExpression )
		{
			// Compile expression
			asSExprContext c(engine);
			CompileExpression(cnode->firstChild, &c);

			// Verify that the result is a constant
			if( !c.type.isConstant )
				Error(TXT_SWITCH_CASE_MUST_BE_CONSTANT, cnode->firstChild);

			// Verify that the result is an integral number
			if( !c.type.dataType.IsIntegerType() && !c.type.dataType.IsUnsignedType() && !c.type.dataType.IsEnumType() )
				Error(TXT_SWITCH_MUST_BE_INTEGRAL, cnode->firstChild);

			ImplicitConversion(&c, to, cnode->firstChild, asIC_IMPLICIT_CONV, true);

			// Has this case been declared already?
			if( caseValues.IndexOf(c.type.intValue) >= 0 )
			{
				Error(TXT_DUPLICATE_SWITCH_CASE, cnode->firstChild);
			}

			// TODO: Optimize: We can insert the numbers sorted already

			// Store constant for later use
			caseValues.PushLast(c.type.intValue);

			// Reserve label for this case
			caseLabels.PushLast(nextLabel++);
		}
		else
		{
			// Is default the last case?
			if( cnode->next )
			{
				Error(TXT_DEFAULT_MUST_BE_LAST, cnode);
				break;
			}

			// Reserve label for this case
			defaultLabel = nextLabel++;
		}

		cnode = cnode->next;
	}

    // check for empty switch
	if (caseValues.GetLength() == 0)
	{
		Error(TXT_EMPTY_SWITCH, snode);
		return;
	}

	if( defaultLabel == 0 )
		defaultLabel = breakLabel;

	//---------------------------------
    // Output the optimized case comparisons
	// with jumps to the case code
	//------------------------------------

	// Sort the case values by increasing value. Do the sort together with the labels
	// A simple bubble sort is sufficient since we don't expect a huge number of values
	for( asUINT fwd = 1; fwd < caseValues.GetLength(); fwd++ )
	{
		for( int bck = fwd - 1; bck >= 0; bck-- )
		{
			int bckp = bck + 1;
			if( caseValues[bck] > caseValues[bckp] )
			{
				// Swap the values in both arrays
				int swap = caseValues[bckp];
				caseValues[bckp] = caseValues[bck];
				caseValues[bck] = swap;

				swap = caseLabels[bckp];
				caseLabels[bckp] = caseLabels[bck];
				caseLabels[bck] = swap;
			}
			else
				break;
		}
	}

	// Find ranges of consecutive numbers
	asCArray<int> ranges;
	ranges.PushLast(0);
	asUINT n;
	for( n = 1; n < caseValues.GetLength(); ++n )
	{
		// We can join numbers that are less than 5 numbers
		// apart since the output code will still be smaller
		if( caseValues[n] > caseValues[n-1] + 5 )
			ranges.PushLast(n);
	}

	// If the value is larger than the largest case value, jump to default
	int tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
	expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, caseValues[caseValues.GetLength()-1]);
	expr.bc.InstrW_W(asBC_CMPi, offset, tmpOffset);
	expr.bc.InstrDWORD(asBC_JP, defaultLabel);
	ReleaseTemporaryVariable(tmpOffset, &expr.bc);

	// TODO: optimize: We could possibly optimize this even more by doing a
	//                 binary search instead of a linear search through the ranges

	// For each range
	int range;
	for( range = 0; range < (int)ranges.GetLength(); range++ )
	{
		// Find the largest value in this range
		int maxRange = caseValues[ranges[range]];
		int index = ranges[range];
		for( ; (index < (int)caseValues.GetLength()) && (caseValues[index] <= maxRange + 5); index++ )
			maxRange = caseValues[index];

		// If there are only 2 numbers then it is better to compare them directly
		if( index - ranges[range] > 2 )
		{
			// If the value is smaller than the smallest case value in the range, jump to default
			tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
			expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, caseValues[ranges[range]]);
			expr.bc.InstrW_W(asBC_CMPi, offset, tmpOffset);
			expr.bc.InstrDWORD(asBC_JS, defaultLabel);
			ReleaseTemporaryVariable(tmpOffset, &expr.bc);

			int nextRangeLabel = nextLabel++;
			// If this is the last range we don't have to make this test
			if( range < (int)ranges.GetLength() - 1 )
			{
				// If the value is larger than the largest case value in the range, jump to the next range
				tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
				expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, maxRange);
				expr.bc.InstrW_W(asBC_CMPi, offset, tmpOffset);
				expr.bc.InstrDWORD(asBC_JP, nextRangeLabel);
				ReleaseTemporaryVariable(tmpOffset, &expr.bc);
			}

			// Jump forward according to the value
			tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
			expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, caseValues[ranges[range]]);
			expr.bc.InstrW_W_W(asBC_SUBi, tmpOffset, offset, tmpOffset);
			ReleaseTemporaryVariable(tmpOffset, &expr.bc);
			expr.bc.JmpP(tmpOffset, maxRange - caseValues[ranges[range]]);

			// Add the list of jumps to the correct labels (any holes, jump to default)
			index = ranges[range];
			for( int n = caseValues[index]; n <= maxRange; n++ )
			{
				if( caseValues[index] == n )
					expr.bc.InstrINT(asBC_JMP, caseLabels[index++]);
				else
					expr.bc.InstrINT(asBC_JMP, defaultLabel);
			}

			expr.bc.Label((short)nextRangeLabel);
		}
		else
		{
			// Simply make a comparison with each value
			int n;
			for( n = ranges[range]; n < index; ++n )
			{
				tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
				expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, caseValues[n]);
				expr.bc.InstrW_W(asBC_CMPi, offset, tmpOffset);
				expr.bc.InstrDWORD(asBC_JZ, caseLabels[n]);
				ReleaseTemporaryVariable(tmpOffset, &expr.bc);
			}
		}
	}

	// Catch any value that falls trough
	expr.bc.InstrINT(asBC_JMP, defaultLabel);

	// Release the temporary variable previously stored
	ReleaseTemporaryVariable(expr.type, &expr.bc);

	//----------------------------------
    // Output case implementations
	//----------------------------------

	// Compile case implementations, each one with the label before it
	cnode = snode->firstChild->next;
	while( cnode )
	{
		// Each case should have a constant expression
		if( cnode->firstChild && cnode->firstChild->nodeType == snExpression )
		{
			expr.bc.Label((short)firstCaseLabel++);

			CompileCase(cnode->firstChild->next, &expr.bc);
		}
		else
		{
			expr.bc.Label((short)defaultLabel);

			// Is default the last case?
			if( cnode->next )
			{
				// We've already reported this error
				break;
			}

			CompileCase(cnode->firstChild, &expr.bc);
		}

		cnode = cnode->next;
	}

	//--------------------------------

	bc->AddCode(&expr.bc);

	// Add break label
	bc->Label((short)breakLabel);

	breakLabels.PopLast();
	RemoveVariableScope();
}

void asCCompiler::CompileCase(asCScriptNode *node, asCByteCode *bc)
{
	bool isFinished = false;
	bool hasReturn = false;
	while( node )
	{
		if( hasReturn || isFinished )
		{
			Warning(TXT_UNREACHABLE_CODE, node);
			break;
		}

		if( node->nodeType == snBreak || node->nodeType == snContinue )
			isFinished = true;

		asCByteCode statement(engine);
		if( node->nodeType == snDeclaration )
		{
			Error(TXT_DECL_IN_SWITCH, node);

			// Compile it anyway to avoid further compiler errors
			CompileDeclaration(node, &statement);
		}
		else
			CompileStatement(node, &hasReturn, &statement);

		LineInstr(bc, node->tokenPos);
		bc->AddCode(&statement);

		if( !hasCompileErrors )
			asASSERT( tempVariables.GetLength() == 0 );

		node = node->next;
	}
}

void asCCompiler::CompileIfStatement(asCScriptNode *inode, bool *hasReturn, asCByteCode *bc)
{
	// We will use one label for the if statement
	// and possibly another for the else statement
	int afterLabel = nextLabel++;

	// Compile the expression
	asSExprContext expr(engine);
	CompileAssignment(inode->firstChild, &expr);
	if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
	{
		Error(TXT_EXPR_MUST_BE_BOOL, inode->firstChild);
		expr.type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), 1);
	}

	if( expr.type.dataType.IsReference() ) ConvertToVariable(&expr);
	ProcessDeferredParams(&expr);

	if( !expr.type.isConstant )
	{
		ProcessPropertyGetAccessor(&expr, inode);

		ConvertToVariable(&expr);

		// Add byte code from the expression
		bc->AddCode(&expr.bc);

		// Add a test
		bc->InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
		bc->Instr(asBC_ClrHi);
		bc->InstrDWORD(asBC_JZ, afterLabel);
		ReleaseTemporaryVariable(expr.type, bc);
	}
	else if( expr.type.dwordValue == 0 )
	{
		// Jump to the else case
		bc->InstrINT(asBC_JMP, afterLabel);

		// TODO: Should we warn that the expression will always go to the else?
	}

	// Compile the if statement
	bool origIsConstructorCalled = m_isConstructorCalled;

	bool hasReturn1;
	asCByteCode ifBC(engine);
	CompileStatement(inode->firstChild->next, &hasReturn1, &ifBC);

	// Add the byte code
	LineInstr(bc, inode->firstChild->next->tokenPos);
	bc->AddCode(&ifBC);

	if( inode->firstChild->next->nodeType == snExpressionStatement && inode->firstChild->next->firstChild == 0 )
	{
		// Don't allow  if( expr );
		Error(TXT_IF_WITH_EMPTY_STATEMENT, inode->firstChild->next);
	}

	// If one of the statements call the constructor, the other must as well
	// otherwise it is possible the constructor is never called
	bool constructorCall1 = false;
	bool constructorCall2 = false;
	if( !origIsConstructorCalled && m_isConstructorCalled )
		constructorCall1 = true;

	// Do we have an else statement?
	if( inode->firstChild->next != inode->lastChild )
	{
		// Reset the constructor called flag so the else statement can call the constructor too
		m_isConstructorCalled = origIsConstructorCalled;

		int afterElse = 0;
		if( !hasReturn1 )
		{
			afterElse = nextLabel++;

			// Add jump to after the else statement
			bc->InstrINT(asBC_JMP, afterElse);
		}

		// Add label for the else statement
		bc->Label((short)afterLabel);

		bool hasReturn2;
		asCByteCode elseBC(engine);
		CompileStatement(inode->lastChild, &hasReturn2, &elseBC);

		// Add byte code for the else statement
		LineInstr(bc, inode->lastChild->tokenPos);
		bc->AddCode(&elseBC);

		if( inode->lastChild->nodeType == snExpressionStatement && inode->lastChild->firstChild == 0 )
		{
			// Don't allow  if( expr ) {} else;
			Error(TXT_ELSE_WITH_EMPTY_STATEMENT, inode->lastChild);
		}

		if( !hasReturn1 )
		{
			// Add label for the end of else statement
			bc->Label((short)afterElse);
		}

		// The if statement only has return if both alternatives have
		*hasReturn = hasReturn1 && hasReturn2;

		if( !origIsConstructorCalled && m_isConstructorCalled )
			constructorCall2 = true;
	}
	else
	{
		// Add label for the end of if statement
		bc->Label((short)afterLabel);
		*hasReturn = false;
	}

	// Make sure both or neither conditions call a constructor
	if( (constructorCall1 && !constructorCall2) ||
		(constructorCall2 && !constructorCall1) )
	{
		Error(TXT_BOTH_CONDITIONS_MUST_CALL_CONSTRUCTOR, inode);
	}

	m_isConstructorCalled = origIsConstructorCalled || constructorCall1 || constructorCall2;
}

void asCCompiler::CompileForStatement(asCScriptNode *fnode, asCByteCode *bc)
{
	// TODO: optimize: We should be able to remove the static JMP to the beginning of the loop by rearranging the 
	//                 byte code a bit. 
	//
	//                 init
	//                 jump to before
	//                 begin:
	//                 statements
	//                 continue:
	//                 next
	//                 before:
	//                 condition
	//                 if loop jump to begin
	//                 break:

	// Add a variable scope that will be used by CompileBreak/Continue to know where to stop deallocating variables
	AddVariableScope(true, true);

	// We will use three labels for the for loop
	int beforeLabel = nextLabel++;
	int afterLabel = nextLabel++;
	int continueLabel = nextLabel++;

	continueLabels.PushLast(continueLabel);
	breakLabels.PushLast(afterLabel);

	//---------------------------------------
	// Compile the initialization statement
	asCByteCode initBC(engine);
	if( fnode->firstChild->nodeType == snDeclaration )
		CompileDeclaration(fnode->firstChild, &initBC);
	else
		CompileExpressionStatement(fnode->firstChild, &initBC);

	//-----------------------------------
	// Compile the condition statement
	asSExprContext expr(engine);
	asCScriptNode *second = fnode->firstChild->next;
	if( second->firstChild )
	{
		int r = CompileAssignment(second->firstChild, &expr);
		if( r >= 0 )
		{
			if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
				Error(TXT_EXPR_MUST_BE_BOOL, second);
			else
			{
				if( expr.type.dataType.IsReference() ) ConvertToVariable(&expr);
				ProcessDeferredParams(&expr);

				ProcessPropertyGetAccessor(&expr, second);

				// If expression is false exit the loop
				ConvertToVariable(&expr);
				expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
				expr.bc.Instr(asBC_ClrHi);
				expr.bc.InstrDWORD(asBC_JZ, afterLabel);
				ReleaseTemporaryVariable(expr.type, &expr.bc);
			}
		}
	}

	//---------------------------
	// Compile the increment statement
	asCByteCode nextBC(engine);
	asCScriptNode *third = second->next;
	if( third->nodeType == snExpressionStatement )
		CompileExpressionStatement(third, &nextBC);

	//------------------------------
	// Compile loop statement
	bool hasReturn;
	asCByteCode forBC(engine);
	CompileStatement(fnode->lastChild, &hasReturn, &forBC);

	//-------------------------------
	// Join the code pieces
	bc->AddCode(&initBC);
	bc->Label((short)beforeLabel);

	// Add a suspend bytecode inside the loop to guarantee
	// that the application can suspend the execution
	bc->Instr(asBC_SUSPEND);
	bc->InstrWORD(asBC_JitEntry, 0);


	bc->AddCode(&expr.bc);
	LineInstr(bc, fnode->lastChild->tokenPos);
	bc->AddCode(&forBC);
	bc->Label((short)continueLabel);
	bc->AddCode(&nextBC);
	bc->InstrINT(asBC_JMP, beforeLabel);
	bc->Label((short)afterLabel);

	continueLabels.PopLast();
	breakLabels.PopLast();

	// Deallocate variables in this block, in reverse order
	for( int n = (int)variables->variables.GetLength() - 1; n >= 0; n-- )
	{
		sVariable *v = variables->variables[n];

		// Call variable destructors here, for variables not yet destroyed
		CallDestructor(v->type, v->stackOffset, v->onHeap, bc);

		// Don't deallocate function parameters
		if( v->stackOffset > 0 )
			DeallocateVariable(v->stackOffset);
	}

	RemoveVariableScope();
}

void asCCompiler::CompileWhileStatement(asCScriptNode *wnode, asCByteCode *bc)
{
	// Add a variable scope that will be used by CompileBreak/Continue to know where to stop deallocating variables
	AddVariableScope(true, true);

	// We will use two labels for the while loop
	int beforeLabel = nextLabel++;
	int afterLabel = nextLabel++;

	continueLabels.PushLast(beforeLabel);
	breakLabels.PushLast(afterLabel);

	// Add label before the expression
	bc->Label((short)beforeLabel);

	// Compile expression
	asSExprContext expr(engine);
	CompileAssignment(wnode->firstChild, &expr);
	if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		Error(TXT_EXPR_MUST_BE_BOOL, wnode->firstChild);
	else
	{
		if( expr.type.dataType.IsReference() ) ConvertToVariable(&expr);
		ProcessDeferredParams(&expr);

		ProcessPropertyGetAccessor(&expr, wnode);

		// Add byte code for the expression
		ConvertToVariable(&expr);
		bc->AddCode(&expr.bc);

		// Jump to end of statement if expression is false
		bc->InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
		bc->Instr(asBC_ClrHi);
		bc->InstrDWORD(asBC_JZ, afterLabel);
		ReleaseTemporaryVariable(expr.type, bc);
	}

	// Add a suspend bytecode inside the loop to guarantee
	// that the application can suspend the execution
	bc->Instr(asBC_SUSPEND);
	bc->InstrWORD(asBC_JitEntry, 0);

	// Compile statement
	bool hasReturn;
	asCByteCode whileBC(engine);
	CompileStatement(wnode->lastChild, &hasReturn, &whileBC);

	// Add byte code for the statement
	LineInstr(bc, wnode->lastChild->tokenPos);
	bc->AddCode(&whileBC);

	// Jump to the expression
	bc->InstrINT(asBC_JMP, beforeLabel);

	// Add label after the statement
	bc->Label((short)afterLabel);

	continueLabels.PopLast();
	breakLabels.PopLast();

	RemoveVariableScope();
}

void asCCompiler::CompileDoWhileStatement(asCScriptNode *wnode, asCByteCode *bc)
{
	// Add a variable scope that will be used by CompileBreak/Continue to know where to stop deallocating variables
	AddVariableScope(true, true);

	// We will use two labels for the while loop
	int beforeLabel = nextLabel++;
	int beforeTest = nextLabel++;
	int afterLabel = nextLabel++;

	continueLabels.PushLast(beforeTest);
	breakLabels.PushLast(afterLabel);

	// Add label before the statement
	bc->Label((short)beforeLabel);

	// Compile statement
	bool hasReturn;
	asCByteCode whileBC(engine);
	CompileStatement(wnode->firstChild, &hasReturn, &whileBC);

	// Add byte code for the statement
	LineInstr(bc, wnode->firstChild->tokenPos);
	bc->AddCode(&whileBC);

	// Add label before the expression
	bc->Label((short)beforeTest);

	// Add a suspend bytecode inside the loop to guarantee
	// that the application can suspend the execution
	bc->Instr(asBC_SUSPEND);
	bc->InstrWORD(asBC_JitEntry, 0);

	// Add a line instruction
	LineInstr(bc, wnode->lastChild->tokenPos);

	// Compile expression
	asSExprContext expr(engine);
	CompileAssignment(wnode->lastChild, &expr);
	if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		Error(TXT_EXPR_MUST_BE_BOOL, wnode->firstChild);
	else
	{
		if( expr.type.dataType.IsReference() ) ConvertToVariable(&expr);
		ProcessDeferredParams(&expr);

		ProcessPropertyGetAccessor(&expr, wnode);

		// Add byte code for the expression
		ConvertToVariable(&expr);
		bc->AddCode(&expr.bc);

		// Jump to next iteration if expression is true
		bc->InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
		bc->Instr(asBC_ClrHi);
		bc->InstrDWORD(asBC_JNZ, beforeLabel);
		ReleaseTemporaryVariable(expr.type, bc);
	}

	// Add label after the statement
	bc->Label((short)afterLabel);

	continueLabels.PopLast();
	breakLabels.PopLast();

	RemoveVariableScope();
}

void asCCompiler::CompileBreakStatement(asCScriptNode *node, asCByteCode *bc)
{
	if( breakLabels.GetLength() == 0 )
	{
		Error(TXT_INVALID_BREAK, node);
		return;
	}

	// Add destructor calls for all variables that will go out of scope
	// Put this clean up in a block to allow exception handler to understand them
	bc->Block(true);
	asCVariableScope *vs = variables;
	while( !vs->isBreakScope )
	{
		for( int n = (int)vs->variables.GetLength() - 1; n >= 0; n-- )
			CallDestructor(vs->variables[n]->type, vs->variables[n]->stackOffset, vs->variables[n]->onHeap, bc);

		vs = vs->parent;
	}
	bc->Block(false);

	bc->InstrINT(asBC_JMP, breakLabels[breakLabels.GetLength()-1]);
}

void asCCompiler::CompileContinueStatement(asCScriptNode *node, asCByteCode *bc)
{
	if( continueLabels.GetLength() == 0 )
	{
		Error(TXT_INVALID_CONTINUE, node);
		return;
	}

	// Add destructor calls for all variables that will go out of scope
	// Put this clean up in a block to allow exception handler to understand them
	bc->Block(true);
	asCVariableScope *vs = variables;
	while( !vs->isContinueScope )
	{
		for( int n = (int)vs->variables.GetLength() - 1; n >= 0; n-- )
			CallDestructor(vs->variables[n]->type, vs->variables[n]->stackOffset, vs->variables[n]->onHeap, bc);

		vs = vs->parent;
	}
	bc->Block(false);

	bc->InstrINT(asBC_JMP, continueLabels[continueLabels.GetLength()-1]);
}

void asCCompiler::CompileExpressionStatement(asCScriptNode *enode, asCByteCode *bc)
{
	if( enode->firstChild )
	{
		// Compile the expression
		asSExprContext expr(engine);
		CompileAssignment(enode->firstChild, &expr);

		// Pop the value from the stack
		if( !expr.type.dataType.IsPrimitive() )
			expr.bc.Pop(expr.type.dataType.GetSizeOnStackDWords());

		// Release temporary variables used by expression
		ReleaseTemporaryVariable(expr.type, &expr.bc);

		ProcessDeferredParams(&expr);

		bc->AddCode(&expr.bc);
	}
}

void asCCompiler::PrepareTemporaryObject(asCScriptNode *node, asSExprContext *ctx, asCArray<int> *reservedVars, bool forceOnHeap)
{
	// If the object already is stored in temporary variable then nothing needs to be done
	// Note, a type can be temporary without being a variable, in which case it is holding off
	// on releasing a previously used object.
	if( ctx->type.isTemporary && ctx->type.isVariable && 
		!(forceOnHeap && !IsVariableOnHeap(ctx->type.stackOffset)) )
	{
		// If the temporary object is currently not a reference 
		// the expression needs to be reevaluated to a reference
		if( !ctx->type.dataType.IsReference() )
		{
			ctx->bc.Pop(AS_PTR_SIZE);
			ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			ctx->type.dataType.MakeReference(true);
		}

		return;
	}

	// Allocate temporary variable
	asCDataType dt = ctx->type.dataType;
	dt.MakeReference(false);
	dt.MakeReadOnly(false);

	int offset = AllocateVariableNotIn(dt, true, reservedVars, forceOnHeap);

	// Objects stored on the stack are not considered references
	dt.MakeReference(IsVariableOnHeap(offset));

	asCTypeInfo lvalue;
	lvalue.Set(dt);
	lvalue.isTemporary = true;
	lvalue.stackOffset = (short)offset;
	lvalue.isVariable = true;
	lvalue.isExplicitHandle = ctx->type.isExplicitHandle;

	if( !dt.IsObjectHandle() && dt.GetObjectType() && (dt.GetBehaviour()->copyconstruct || dt.GetBehaviour()->copyfactory) )
	{
		PrepareForAssignment(&lvalue.dataType, ctx, node);

		// Use the copy constructor/factory when available
		CallCopyConstructor(dt, offset, IsVariableOnHeap(offset), &ctx->bc, ctx, node);
	}
	else
	{
		// Allocate and construct the temporary object
		CallDefaultConstructor(dt, offset, IsVariableOnHeap(offset), &ctx->bc, node);

		// Assign the object to the temporary variable
		PrepareForAssignment(&lvalue.dataType, ctx, node);

		ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
		PerformAssignment(&lvalue, &ctx->type, &ctx->bc, node);

		// Pop the original reference
		ctx->bc.Pop(AS_PTR_SIZE);
	}

	// If the expression was holding off on releasing a 
	// previously used object, we need to release it now
	if( ctx->type.isTemporary )
		ReleaseTemporaryVariable(ctx->type, &ctx->bc);

	// Push the reference to the temporary variable on the stack
	ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
	lvalue.dataType.MakeReference(IsVariableOnHeap(offset));

	ctx->type = lvalue;
}

void asCCompiler::CompileReturnStatement(asCScriptNode *rnode, asCByteCode *bc)
{
	// Get return type and location
	sVariable *v = variables->GetVariable("return");

	// Basic validations
	if( v->type.GetSizeOnStackDWords() > 0 && !rnode->firstChild )
	{
		Error(TXT_MUST_RETURN_VALUE, rnode);
		return;
	}
	else if( v->type.GetSizeOnStackDWords() == 0 && rnode->firstChild )
	{
		Error(TXT_CANT_RETURN_VALUE, rnode);
		return;
	}

	// Compile the expression
	if( rnode->firstChild )
	{
		// Compile the expression
		asSExprContext expr(engine);
		int r = CompileAssignment(rnode->firstChild, &expr);
		if( r < 0 ) return;

		if( v->type.IsReference() )
		{
			// The expression that gives the reference must not use any of the 
			// variables that must be destroyed upon exit, because then it means
			// reference will stay alive while the clean-up is done, which could
			// potentially mean that the reference is invalidated by the clean-up.
			//       
			// When the function is returning a reference, the clean-up of the 
			// variables must be done before the evaluation of the expression.
			//
			// A reference to a global variable, or a class member for class methods
			// should be allowed to be returned.

			if( !(expr.type.dataType.IsReference() ||
				  (expr.type.dataType.IsObject() && !expr.type.dataType.IsObjectHandle())) )
			{
				// Clean up the potential deferred parameters
				ProcessDeferredParams(&expr);
				Error(TXT_NOT_VALID_REFERENCE, rnode);
				return;
			}

			// No references to local variables, temporary variables, or parameters
			// are allowed to be returned, since they go out of scope when the function
			// returns. Even reference parameters are disallowed, since it is not possible
			// to know the scope of them. The exception is the 'this' pointer, which 
			// is treated by the compiler as a local variable, but isn't really so.
			if( (expr.type.isVariable && !(expr.type.stackOffset == 0 && outFunc->objectType)) || expr.type.isTemporary )
			{
				// Clean up the potential deferred parameters
				ProcessDeferredParams(&expr);
				Error(TXT_CANNOT_RETURN_REF_TO_LOCAL, rnode);
				return;
			}

			// The type must match exactly as we cannot convert
			// the reference without loosing the original value
			if( !(v->type == expr.type.dataType ||
				(expr.type.dataType.IsObject() && !expr.type.dataType.IsObjectHandle() && v->type.IsEqualExceptRef(expr.type.dataType))) )
			{
				// Clean up the potential deferred parameters
				ProcessDeferredParams(&expr);
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, expr.type.dataType.Format().AddressOf(), v->type.Format().AddressOf());
				Error(str.AddressOf(), rnode);
				return;
			}

			// The expression must not have any deferred expressions, because the evaluation 
			// of these cannot be done without keeping the reference which is not safe
			if( expr.deferredParams.GetLength() )
			{
				// Clean up the potential deferred parameters
				ProcessDeferredParams(&expr);
				Error(TXT_REF_CANT_BE_RETURNED_DEFERRED_PARAM, rnode);
				return;
			}

			// Make sure the expression isn't using any local variables that  
			// will need to be cleaned up before the function completes
			asCArray<int> usedVars;
			expr.bc.GetVarsUsed(usedVars);
			for( asUINT n = 0; n < usedVars.GetLength(); n++ )
			{
				int var = GetVariableSlot(usedVars[n]);
				if( var != -1 )
				{
					asCDataType dt = variableAllocations[var];
					if( dt.IsObject() )
					{
						ProcessDeferredParams(&expr);
						Error(TXT_REF_CANT_BE_RETURNED_LOCAL_VARS, rnode);
						return;
					}
				}
			}

			// All objects in the function must be cleaned up before the expression 
			// is evaluated, otherwise there is a possibility that the cleanup will
			// invalidate the reference.

			// Destroy the local variables before loading 
			// the reference into the register. This will 
			// be done before the expression is evaluated.
			DestroyVariables(bc);

			// For primitives the reference is already in the register,
			// but for non-primitives the reference is on the stack so we 
			// need to load it into the register
			if( !expr.type.dataType.IsPrimitive() )
			{
				if( !expr.type.dataType.IsObjectHandle() && expr.type.dataType.IsReference() )
					expr.bc.Instr(asBC_RDSPTR);

				expr.bc.Instr(asBC_PopRPtr);
			}

			// There are no temporaries to release so we're done
		}
		else // if( !v->type.IsReference() )
		{
			ProcessPropertyGetAccessor(&expr, rnode);

			// Prepare the value for assignment
			IsVariableInitialized(&expr.type, rnode->firstChild);

			if( v->type.IsPrimitive() )
			{
				if( expr.type.dataType.IsReference() ) ConvertToVariable(&expr);

				// Implicitly convert the value to the return type
				ImplicitConversion(&expr, v->type, rnode->firstChild, asIC_IMPLICIT_CONV);

				// Verify that the conversion was successful
				if( expr.type.dataType != v->type )
				{
					asCString str;
					str.Format(TXT_NO_CONVERSION_s_TO_s, expr.type.dataType.Format().AddressOf(), v->type.Format().AddressOf());
					Error(str.AddressOf(), rnode);
					r = -1;
				}
				else
				{
					ConvertToVariable(&expr);

					// Clean up the local variables and process deferred parameters
					DestroyVariables(&expr.bc);
					ProcessDeferredParams(&expr);

					ReleaseTemporaryVariable(expr.type, &expr.bc);

					// Load the variable in the register
					if( v->type.GetSizeOnStackDWords() == 1 )
						expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
					else
						expr.bc.InstrSHORT(asBC_CpyVtoR8, expr.type.stackOffset);
				}
			}
			else if( v->type.IsObject() )
			{
				// Value types are still returned on the heap, so we must
				// copy the value to an object allocated on the heap here
				PrepareArgument(&v->type, &expr, rnode->firstChild, false, 0, 0, true);

				// Pop the reference to the temporary variable again
				expr.bc.Pop(AS_PTR_SIZE);

				// Clean up the local variables and process deferred parameters
				DestroyVariables(&expr.bc);
				ProcessDeferredParams(&expr);

				// Load the object pointer into the object register
				// LOADOBJ also clears the address in the variable
				expr.bc.InstrSHORT(asBC_LOADOBJ, expr.type.stackOffset);

				// LOADOBJ cleared the address in the variable so the object will not be freed
				// here, but the temporary variable must still be freed so the slot can be reused
				// By releasing without the bytecode we do just that.
				ReleaseTemporaryVariable(expr.type, 0);
			}
		}

		bc->AddCode(&expr.bc);
	}
	else
	{
		// For functions that don't return anything
		// we just detroy the local variables
		DestroyVariables(bc);
	}

	// Jump to the end of the function
	bc->InstrINT(asBC_JMP, 0);
}

void asCCompiler::DestroyVariables(asCByteCode *bc)
{
	// Call destructor on all variables except for the function parameters
	// Put the clean-up in a block to allow exception handler to understand this
	bc->Block(true);
	asCVariableScope *vs = variables;
	while( vs )
	{
		for( int n = (int)vs->variables.GetLength() - 1; n >= 0; n-- )
			if( vs->variables[n]->stackOffset > 0 )
				CallDestructor(vs->variables[n]->type, vs->variables[n]->stackOffset, vs->variables[n]->onHeap, bc);

		vs = vs->parent;
	}
	bc->Block(false);
}

void asCCompiler::AddVariableScope(bool isBreakScope, bool isContinueScope)
{
	variables = asNEW(asCVariableScope)(variables);
	variables->isBreakScope    = isBreakScope;
	variables->isContinueScope = isContinueScope;
}

void asCCompiler::RemoveVariableScope()
{
	if( variables )
	{
		asCVariableScope *var = variables;
		variables = variables->parent;
		asDELETE(var,asCVariableScope);
	}
}

void asCCompiler::Error(const char *msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteError(script->name.AddressOf(), msg, r, c);

	hasCompileErrors = true;
}

void asCCompiler::Warning(const char *msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteWarning(script->name.AddressOf(), msg, r, c);
}

void asCCompiler::Information(const char *msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteInfo(script->name.AddressOf(), msg, r, c, false);
}

void asCCompiler::PrintMatchingFuncs(asCArray<int> &funcs, asCScriptNode *node)
{
	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	for( unsigned int n = 0; n < funcs.GetLength(); n++ )
	{
		asIScriptFunction *func = builder->GetFunctionDescription(funcs[n]);

		builder->WriteInfo(script->name.AddressOf(), func->GetDeclaration(true), r, c, false);
	}
}

int asCCompiler::AllocateVariable(const asCDataType &type, bool isTemporary, bool forceOnHeap)
{
	return AllocateVariableNotIn(type, isTemporary, 0, forceOnHeap);
}

int asCCompiler::AllocateVariableNotIn(const asCDataType &type, bool isTemporary, asCArray<int> *vars, bool forceOnHeap)
{
	asCDataType t(type);

	if( t.IsPrimitive() && t.GetSizeOnStackDWords() == 1 )
		t.SetTokenType(ttInt);

	if( t.IsPrimitive() && t.GetSizeOnStackDWords() == 2 )
		t.SetTokenType(ttDouble);

	// Only null handles have the token type unrecognized token
	asASSERT( t.IsObjectHandle() || t.GetTokenType() != ttUnrecognizedToken );

	bool isOnHeap = true;
	// TODO: Remove this once the bugs with value types on stack is fixed
	// forceOnHeap = true;
	if( t.IsPrimitive() || 
		(t.GetObjectType() && (t.GetObjectType()->GetFlags() & asOBJ_VALUE) && !forceOnHeap) )
	{
		// Primitives and value types (unless overridden) are allocated on the stack
		isOnHeap = false;
	}

	// Find a free location with the same type
	for( asUINT n = 0; n < freeVariables.GetLength(); n++ )
	{
		int slot = freeVariables[n];

		if( variableAllocations[slot].IsEqualExceptConst(t) && 
			variableIsTemporary[slot] == isTemporary &&
			variableIsOnHeap[slot] == isOnHeap )
		{
			// We can't return by slot, must count variable sizes
			int offset = GetVariableOffset(slot);

			// Verify that it is not in the list of used variables
			bool isUsed = false;
			if( vars )
			{
				for( asUINT m = 0; m < vars->GetLength(); m++ )
				{
					if( offset == (*vars)[m] )
					{
						isUsed = true;
						break;
					}
				}
			}

			if( !isUsed )
			{
				if( n != freeVariables.GetLength() - 1 )
					freeVariables[n] = freeVariables.PopLast();
				else
					freeVariables.PopLast();

				if( isTemporary )
					tempVariables.PushLast(offset);

				return offset;
			}
		}
	}

	variableAllocations.PushLast(t);
	variableIsTemporary.PushLast(isTemporary);
	variableIsOnHeap.PushLast(isOnHeap);

	int offset = GetVariableOffset((int)variableAllocations.GetLength()-1);

	if( isTemporary )
		tempVariables.PushLast(offset);

	return offset;
}

int asCCompiler::GetVariableOffset(int varIndex)
{
	// Return offset to the last dword on the stack
	int varOffset = 1;
	for( int n = 0; n < varIndex; n++ )
	{
		if( !variableIsOnHeap[n] && variableAllocations[n].IsObject() )
			varOffset += variableAllocations[n].GetSizeInMemoryDWords();
		else
			varOffset += variableAllocations[n].GetSizeOnStackDWords();
	}

	if( varIndex < (int)variableAllocations.GetLength() )
	{
		int size;
		if( !variableIsOnHeap[varIndex] && variableAllocations[varIndex].IsObject() )
			size = variableAllocations[varIndex].GetSizeInMemoryDWords();
		else
			size = variableAllocations[varIndex].GetSizeOnStackDWords();
		if( size > 1 )
			varOffset += size-1;
	}

	return varOffset;
}

int asCCompiler::GetVariableSlot(int offset)
{
	int varOffset = 1;
	for( asUINT n = 0; n < variableAllocations.GetLength(); n++ )
	{
		if( !variableIsOnHeap[n] && variableAllocations[n].IsObject() )
			varOffset += -1 + variableAllocations[n].GetSizeInMemoryDWords();
		else
			varOffset += -1 + variableAllocations[n].GetSizeOnStackDWords();

		if( varOffset == offset )
			return n;

		varOffset++;
	}

	return -1;
}

bool asCCompiler::IsVariableOnHeap(int offset)
{
	int varSlot = GetVariableSlot(offset);
	if( varSlot < 0 ) 
	{
		// This happens for function arguments that are considered as on the heap
		return true;
	}

	return variableIsOnHeap[varSlot];
}

void asCCompiler::DeallocateVariable(int offset)
{
	// Remove temporary variable
	int n;
	for( n = 0; n < (int)tempVariables.GetLength(); n++ )
	{
		if( offset == tempVariables[n] )
		{
			if( n == (int)tempVariables.GetLength()-1 )
				tempVariables.PopLast();
			else
				tempVariables[n] = tempVariables.PopLast();
			break;
		}
	}

	n = GetVariableSlot(offset);
	if( n != -1 )
	{
		freeVariables.PushLast(n);
		return;
	}

	// We might get here if the variable was implicitly declared
	// because it was use before a formal declaration, in this case
	// the offset is 0x7FFF

	asASSERT(offset == 0x7FFF);
}

void asCCompiler::ReleaseTemporaryVariable(asCTypeInfo &t, asCByteCode *bc)
{
	if( t.isTemporary )
	{
		ReleaseTemporaryVariable(t.stackOffset, bc);
		t.isTemporary = false;
	}
}

void asCCompiler::ReleaseTemporaryVariable(int offset, asCByteCode *bc)
{
	if( bc )
	{
		// We need to call the destructor on the true variable type
		int n = GetVariableSlot(offset);
		asCDataType dt = variableAllocations[n];
		bool isOnHeap = variableIsOnHeap[n];

		// Call destructor
		CallDestructor(dt, offset, isOnHeap, bc);
	}

	DeallocateVariable(offset);
}

void asCCompiler::Dereference(asSExprContext *ctx, bool generateCode)
{
	if( ctx->type.dataType.IsReference() )
	{
		if( ctx->type.dataType.IsObject() )
		{
			ctx->type.dataType.MakeReference(false);
			if( generateCode )
			{
				ctx->bc.Instr(asBC_CHKREF);
				ctx->bc.Instr(asBC_RDSPTR);
			}
		}
		else
		{
			// This should never happen as primitives are treated differently
			asASSERT(false);
		}
	}
}


bool asCCompiler::IsVariableInitialized(asCTypeInfo *type, asCScriptNode *node)
{
	// Temporary variables are assumed to be initialized
	if( type->isTemporary ) return true;

	// Verify that it is a variable
	if( !type->isVariable ) return true;

	// Find the variable
	sVariable *v = variables->GetVariableByOffset(type->stackOffset);

	// The variable isn't found if it is a constant, in which case it is guaranteed to be initialized
	if( v == 0 ) return true;

	if( v->isInitialized ) return true;

	// Complex types don't need this test
	if( v->type.IsObject() ) return true;

	// Mark as initialized so that the user will not be bothered again
	v->isInitialized = true;

	// Write warning
	asCString str;
	str.Format(TXT_s_NOT_INITIALIZED, (const char *)v->name.AddressOf());
	Warning(str.AddressOf(), node);

	return false;
}

void asCCompiler::PrepareOperand(asSExprContext *ctx, asCScriptNode *node)
{
	// Check if the variable is initialized (if it indeed is a variable)
	IsVariableInitialized(&ctx->type, node);

	asCDataType to = ctx->type.dataType;
	to.MakeReference(false);

	ImplicitConversion(ctx, to, node, asIC_IMPLICIT_CONV);

	ProcessDeferredParams(ctx);
}

void asCCompiler::PrepareForAssignment(asCDataType *lvalue, asSExprContext *rctx, asCScriptNode *node, asSExprContext *lvalueExpr)
{
	ProcessPropertyGetAccessor(rctx, node);

	// Make sure the rvalue is initialized if it is a variable
	IsVariableInitialized(&rctx->type, node);

	if( lvalue->IsPrimitive() )
	{
		if( rctx->type.dataType.IsPrimitive() )
		{
			if( rctx->type.dataType.IsReference() )
			{
				// Cannot do implicit conversion of references so we first convert the reference to a variable
				ConvertToVariableNotIn(rctx, lvalueExpr);
			}
		}

		// Implicitly convert the value to the right type
		asCArray<int> usedVars;
		if( lvalueExpr ) lvalueExpr->bc.GetVarsUsed(usedVars);
		ImplicitConversion(rctx, *lvalue, node, asIC_IMPLICIT_CONV, true, &usedVars);

		// Check data type
		if( !lvalue->IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format().AddressOf(), lvalue->Format().AddressOf());
			Error(str.AddressOf(), node);

			rctx->type.SetDummy();
		}

		// Make sure the rvalue is a variable
		if( !rctx->type.isVariable )
			ConvertToVariableNotIn(rctx, lvalueExpr);
	}
	else
	{
		asCDataType to = *lvalue;
		to.MakeReference(false);

		// TODO: ImplicitConversion should know to do this by itself
		// First convert to a handle which will to a reference cast
		if( !lvalue->IsObjectHandle() &&
			(lvalue->GetObjectType()->flags & asOBJ_SCRIPT_OBJECT) )
			to.MakeHandle(true);

		// Don't allow the implicit conversion to create an object
		ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, 0, false);

		if( !lvalue->IsObjectHandle() &&
			(lvalue->GetObjectType()->flags & asOBJ_SCRIPT_OBJECT) )
		{
			// Then convert to a reference, which will validate the handle
			to.MakeHandle(false);
			ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, 0, false);
		}

		// Check data type
		if( !lvalue->IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format().AddressOf(), lvalue->Format().AddressOf());
			Error(str.AddressOf(), node);
		}
		else
		{
			// If the assignment will be made with the copy behaviour then the rvalue must not be a reference
			if( lvalue->IsObject() )
				asASSERT(!rctx->type.dataType.IsReference());
		}
	}
}

bool asCCompiler::IsLValue(asCTypeInfo &type)
{
	if( type.dataType.IsReadOnly() ) return false;
	if( !type.dataType.IsObject() && !type.isVariable && !type.dataType.IsReference() ) return false;
	if( type.isTemporary ) return false;
	return true;
}

void asCCompiler::PerformAssignment(asCTypeInfo *lvalue, asCTypeInfo *rvalue, asCByteCode *bc, asCScriptNode *node)
{
	if( lvalue->dataType.IsReadOnly() )
		Error(TXT_REF_IS_READ_ONLY, node);

	if( lvalue->dataType.IsPrimitive() )
	{
		if( lvalue->isVariable )
		{
			// Copy the value between the variables directly
			if( lvalue->dataType.GetSizeInMemoryDWords() == 1 )
				bc->InstrW_W(asBC_CpyVtoV4, lvalue->stackOffset, rvalue->stackOffset);
			else
				bc->InstrW_W(asBC_CpyVtoV8, lvalue->stackOffset, rvalue->stackOffset);

			// Mark variable as initialized
			sVariable *v = variables->GetVariableByOffset(lvalue->stackOffset);
			if( v ) v->isInitialized = true;
		}
		else if( lvalue->dataType.IsReference() )
		{
			// Copy the value of the variable to the reference in the register
			int s = lvalue->dataType.GetSizeInMemoryBytes();
			if( s == 1 )
				bc->InstrSHORT(asBC_WRTV1, rvalue->stackOffset);
			else if( s == 2 )
				bc->InstrSHORT(asBC_WRTV2, rvalue->stackOffset);
			else if( s == 4 )
				bc->InstrSHORT(asBC_WRTV4, rvalue->stackOffset);
			else if( s == 8 )
				bc->InstrSHORT(asBC_WRTV8, rvalue->stackOffset);
		}
		else
		{
			Error(TXT_NOT_VALID_LVALUE, node);
			return;
		}
	}
	else if( !lvalue->isExplicitHandle )
	{
		asSExprContext ctx(engine);
		ctx.type = *lvalue;
		Dereference(&ctx, true);
		*lvalue = ctx.type;
		bc->AddCode(&ctx.bc);

		// TODO: Can't this leave deferred output params unhandled?

		// TODO: Should find the opAssign method that implements the default copy behaviour.
		//       The beh->copy member will be removed.
		asSTypeBehaviour *beh = lvalue->dataType.GetBehaviour();
		if( beh->copy )
		{
			// Call the copy operator
			bc->Call(asBC_CALLSYS, (asDWORD)beh->copy, 2*AS_PTR_SIZE);
			bc->Instr(asBC_PshRPtr);
		}
		else
		{
			// Default copy operator
			if( lvalue->dataType.GetSizeInMemoryDWords() == 0 ||
				!(lvalue->dataType.GetObjectType()->flags & asOBJ_POD) )
			{
				Error(TXT_NO_DEFAULT_COPY_OP, node);
			}

			// Copy larger data types from a reference
			bc->InstrSHORT_DW(asBC_COPY, lvalue->dataType.GetSizeInMemoryDWords(), engine->GetTypeIdFromDataType(lvalue->dataType));
		}
	}
	else
	{
		// TODO: The object handle can be stored in a variable as well
		if( !lvalue->dataType.IsReference() )
		{
			Error(TXT_NOT_VALID_REFERENCE, node);
			return;
		}

		// TODO: optimize: Convert to register based
		bc->InstrPTR(asBC_REFCPY, lvalue->dataType.GetObjectType());

		// Mark variable as initialized
		if( variables )
		{
			sVariable *v = variables->GetVariableByOffset(lvalue->stackOffset);
			if( v ) v->isInitialized = true;
		}
	}
}

bool asCCompiler::CompileRefCast(asSExprContext *ctx, const asCDataType &to, bool isExplicit, asCScriptNode *node, bool generateCode)
{
	bool conversionDone = false;

	asCArray<int> ops;
	asUINT n;

	if( ctx->type.dataType.GetObjectType()->flags & asOBJ_SCRIPT_OBJECT )
	{
		// We need it to be a reference
		if( !ctx->type.dataType.IsReference() )
		{
			asCDataType to = ctx->type.dataType;
			to.MakeReference(true);
			ImplicitConversion(ctx, to, 0, isExplicit ? asIC_EXPLICIT_REF_CAST : asIC_IMPLICIT_CONV, generateCode);
		}

		if( isExplicit )
		{
			// Allow dynamic cast between object handles (only for script objects).
			// At run time this may result in a null handle,
			// which when used will throw an exception
			conversionDone = true;
			if( generateCode )
			{
				ctx->bc.InstrDWORD(asBC_Cast, engine->GetTypeIdFromDataType(to));

				// Allocate a temporary variable for the returned object
				int returnOffset = AllocateVariable(to, true);

				// Move the pointer from the object register to the temporary variable
				ctx->bc.InstrSHORT(asBC_STOREOBJ, (short)returnOffset);

				ctx->bc.InstrSHORT(asBC_PSF, (short)returnOffset);

				ReleaseTemporaryVariable(ctx->type, &ctx->bc);

				ctx->type.SetVariable(to, returnOffset, true);
				ctx->type.dataType.MakeReference(true);
			}
			else
			{
				ctx->type.dataType = to;
				ctx->type.dataType.MakeReference(true);
			}
		}
		else
		{
			if( ctx->type.dataType.GetObjectType()->DerivesFrom(to.GetObjectType()) )
			{
				conversionDone = true;
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
		}
	}
	else
	{
		// Find a suitable registered behaviour
		asSTypeBehaviour *beh = &ctx->type.dataType.GetObjectType()->beh;
		for( n = 0; n < beh->operators.GetLength(); n+= 2 )
		{
			if( (isExplicit && asBEHAVE_REF_CAST == beh->operators[n]) ||
				asBEHAVE_IMPLICIT_REF_CAST == beh->operators[n] )
			{
				int funcId = beh->operators[n+1];

				// Is the operator for the output type?
				asCScriptFunction *func = engine->scriptFunctions[funcId];
				if( func->returnType.GetObjectType() != to.GetObjectType() )
					continue;

				ops.PushLast(funcId);
			}
		}

		// Should only have one behaviour for each output type
		if( ops.GetLength() == 1 )
		{
			if( generateCode )
			{
				// TODO: optimize: Instead of producing bytecode for checking if the handle is 
				//                 null, we can create a special CALLSYS instruction that checks 
				//                 if the object pointer is null and if so sets the object register
				//                 to null directly without executing the function.
				//
				//                 Alternatively I could force the ref cast behaviours be global
				//                 functions with 1 parameter, even though they should still be 
				//                 registered with RegisterObjectBehaviour()

				// Add code to avoid calling the cast behaviour if the handle is already null,
				// because that will raise a null pointer exception due to the cast behaviour
				// being a class method, and the this pointer cannot be null.

				if( ctx->type.isVariable )
					ctx->bc.Pop(AS_PTR_SIZE);
				else
				{
					Dereference(ctx, true);
					ConvertToVariable(ctx);
				}

#ifdef AS_64BIT_PTR
				int offset = AllocateVariable(asCDataType::CreatePrimitive(ttUInt64, false), true);
				ctx->bc.InstrW_QW(asBC_SetV8, offset, 0);
				ctx->bc.InstrW_W(asBC_CMPi64, ctx->type.stackOffset, offset);
				DeallocateVariable(offset);
#else
				int offset = AllocateVariable(asCDataType::CreatePrimitive(ttUInt, false), true);
				ctx->bc.InstrW_DW(asBC_SetV4, offset, 0);
				ctx->bc.InstrW_W(asBC_CMPi, ctx->type.stackOffset, offset);
				DeallocateVariable(offset);
#endif
				int afterLabel = nextLabel++;
				ctx->bc.InstrDWORD(asBC_JZ, afterLabel);

				// Call the cast operator
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
				ctx->bc.Instr(asBC_RDSPTR);
				ctx->type.dataType.MakeReference(false);

				asCTypeInfo objType = ctx->type;
				asCArray<asSExprContext *> args;
				MakeFunctionCall(ctx, ops[0], objType.dataType.GetObjectType(), args, node);

				ctx->bc.Pop(AS_PTR_SIZE);

				int endLabel = nextLabel++;

				ctx->bc.InstrINT(asBC_JMP, endLabel);
				ctx->bc.Label((short)afterLabel);
				
				// Make a NULL pointer
#ifdef AS_64BIT_PTR
				ctx->bc.InstrW_QW(asBC_SetV8, ctx->type.stackOffset, 0);
#else
				ctx->bc.InstrW_DW(asBC_SetV4, ctx->type.stackOffset, 0);
#endif
				ctx->bc.Label((short)endLabel);

				// Since we're receiving a handle, we can release the original variable
				ReleaseTemporaryVariable(objType, &ctx->bc);
				
				// Push the reference to the handle on the stack
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			}
			else
			{
				asCScriptFunction *func = engine->scriptFunctions[ops[0]];
				ctx->type.Set(func->returnType);
			}
		}
		else if( ops.GetLength() > 1 )
		{
			// It shouldn't be possible to have more than one, should it?
			asASSERT( false );
		}
	}

	return conversionDone;
}


void asCCompiler::ImplicitConvPrimitiveToPrimitive(asSExprContext *ctx, const asCDataType &toOrig, asCScriptNode *node, EImplicitConv convType, bool generateCode, asCArray<int> *reservedVars)
{
	asCDataType to = toOrig;
	to.MakeReference(false);
	asASSERT( !ctx->type.dataType.IsReference() );

	// Start by implicitly converting constant values
	if( ctx->type.isConstant )
		ImplicitConversionConstant(ctx, to, node, convType);

	// A primitive is const or not
	ctx->type.dataType.MakeReadOnly(to.IsReadOnly());

	if( to == ctx->type.dataType )
		return;

	// Allow implicit conversion between numbers
	if( generateCode )
	{
		// Convert smaller types to 32bit first
		int s = ctx->type.dataType.GetSizeInMemoryBytes();
		if( s < 4 )
		{
			ConvertToTempVariableNotIn(ctx, reservedVars);
			if( ctx->type.dataType.IsIntegerType() )
			{
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_sbTOi, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_swTOi, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(ttInt);
			}
			else if( ctx->type.dataType.IsUnsignedType() )
			{
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_ubTOi, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_uwTOi, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(ttUInt);
			}
		}

		if( (to.IsIntegerType() && to.GetSizeInMemoryDWords() == 1) ||
			(to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST) )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() ||
				ctx->type.dataType.IsEnumType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetObjectType(to.GetObjectType());
				}
				else
				{
					ConvertToTempVariableNotIn(ctx, reservedVars);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariableNotIn(to, true, reservedVars);
					ctx->bc.InstrW_W(asBC_i64TOi, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_fTOi, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_dTOi, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}

			// Convert to smaller integer if necessary
			int s = to.GetSizeInMemoryBytes();
			if( s < 4 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_iTOb, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_iTOw, ctx->type.stackOffset);
			}
		}
		if( to.IsIntegerType() && to.GetSizeInMemoryDWords() == 2 )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() ||
				ctx->type.dataType.IsEnumType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetObjectType(to.GetObjectType());
				}
				else
				{
					ConvertToTempVariableNotIn(ctx, reservedVars);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariableNotIn(to, true, reservedVars);
					if( ctx->type.dataType.IsUnsignedType() )
						ctx->bc.InstrW_W(asBC_uTOi64, offset, ctx->type.stackOffset);
					else
						ctx->bc.InstrW_W(asBC_iTOi64, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_fTOi64, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_dTOi64, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
		}
		else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 1  )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() ||
				ctx->type.dataType.IsEnumType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetObjectType(to.GetObjectType());
				}
				else
				{
					ConvertToTempVariableNotIn(ctx, reservedVars);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariableNotIn(to, true, reservedVars);
					ctx->bc.InstrW_W(asBC_i64TOi, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_fTOu, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_dTOu, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}

			// Convert to smaller integer if necessary
			int s = to.GetSizeInMemoryBytes();
			if( s < 4 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_iTOb, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_iTOw, ctx->type.stackOffset);
			}
		}
		if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 2 )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() ||
				ctx->type.dataType.IsEnumType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetObjectType(to.GetObjectType());
				}
				else
				{
					ConvertToTempVariableNotIn(ctx, reservedVars);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariableNotIn(to, true, reservedVars);
					if( ctx->type.dataType.IsUnsignedType() )
						ctx->bc.InstrW_W(asBC_uTOi64, offset, ctx->type.stackOffset);
					else
						ctx->bc.InstrW_W(asBC_iTOi64, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_fTOu64, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_dTOu64, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
		}
		else if( to.IsFloatType() )
		{
			if( (ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsEnumType()) && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_iTOf, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_i64TOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_uTOf, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_u64TOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_dTOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
		}
		else if( to.IsDoubleType() )
		{
			if( (ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsEnumType()) && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_iTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_i64TOd, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_uTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ctx->bc.InstrSHORT(asBC_u64TOd, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetObjectType(to.GetObjectType());
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariableNotIn(ctx, reservedVars);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariableNotIn(to, true, reservedVars);
				ctx->bc.InstrW_W(asBC_fTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
		}
	}
	else
	{
		if( (to.IsIntegerType() || to.IsUnsignedType() ||
			 to.IsFloatType()   || to.IsDoubleType() ||
			 (to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST)) &&
			(ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsUnsignedType() ||
			 ctx->type.dataType.IsFloatType()   || ctx->type.dataType.IsDoubleType() ||
			 ctx->type.dataType.IsEnumType()) )
		{
			ctx->type.dataType.SetTokenType(to.GetTokenType());
			ctx->type.dataType.SetObjectType(to.GetObjectType());
		}
	}

	// Primitive types on the stack, can be const or non-const
	ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
}

void asCCompiler::ImplicitConversion(asSExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode, asCArray<int> *reservedVars, bool allowObjectConstruct)
{
	asASSERT( ctx->type.dataType.GetTokenType() != ttUnrecognizedToken ||
		      ctx->type.dataType.IsNullHandle() );

	// No conversion from void to any other type
	if( ctx->type.dataType.GetTokenType() == ttVoid )
		return;

	// Do we want a var type?
	if( to.GetTokenType() == ttQuestion )
	{
		// Any type can be converted to a var type, but only when not generating code
		asASSERT( !generateCode );

		ctx->type.dataType = to;

		return;
	}
	// Do we want a primitive?
	else if( to.IsPrimitive() )
	{
		if( !ctx->type.dataType.IsPrimitive() )
			ImplicitConvObjectToPrimitive(ctx, to, node, convType, generateCode, reservedVars);
		else
			ImplicitConvPrimitiveToPrimitive(ctx, to, node, convType, generateCode, reservedVars);
	}
	else // The target is a complex type
	{
		if( ctx->type.dataType.IsPrimitive() )
			ImplicitConvPrimitiveToObject(ctx, to, node, convType, generateCode, reservedVars, allowObjectConstruct);
		else
			ImplicitConvObjectToObject(ctx, to, node, convType, generateCode, reservedVars, allowObjectConstruct);
	}
}

void asCCompiler::ImplicitConvObjectToPrimitive(asSExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode, asCArray<int> *reservedVars)
{
	if( ctx->type.isExplicitHandle )
	{
		// An explicit handle cannot be converted to a primitive
		if( convType != asIC_IMPLICIT_CONV && node )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
			Error(str.AddressOf(), node);
		}
		return;
	}

	// TODO: Must use the const cast behaviour if the object is read-only

	// Find matching value cast behaviours
	// Here we're only interested in those that convert the type to a primitive type
	asCArray<int> funcs;
	asSTypeBehaviour *beh = ctx->type.dataType.GetBehaviour();
	if( beh )
	{
		if( convType == asIC_EXPLICIT_VAL_CAST )
		{
			for( unsigned int n = 0; n < beh->operators.GetLength(); n += 2 )
			{
				// accept both implicit and explicit cast
				if( (beh->operators[n] == asBEHAVE_VALUE_CAST ||
					 beh->operators[n] == asBEHAVE_IMPLICIT_VALUE_CAST) &&
					builder->GetFunctionDescription(beh->operators[n+1])->returnType.IsPrimitive() )
					funcs.PushLast(beh->operators[n+1]);
			}
		}
		else
		{
			for( unsigned int n = 0; n < beh->operators.GetLength(); n += 2 )
			{
				// accept only implicit cast
				if( beh->operators[n] == asBEHAVE_IMPLICIT_VALUE_CAST &&
					builder->GetFunctionDescription(beh->operators[n+1])->returnType.IsPrimitive() )
					funcs.PushLast(beh->operators[n+1]);
			}
		}
	}

	// This matrix describes the priorities of the types to search for, for each target type
	// The first column is the target type, the priorities goes from left to right
	eTokenType matchMtx[10][10] =
	{
		{ttDouble, ttFloat,  ttInt64,  ttUInt64, ttInt,    ttUInt,   ttInt16,  ttUInt16, ttInt8,   ttUInt8},
		{ttFloat,  ttDouble, ttInt64,  ttUInt64, ttInt,    ttUInt,   ttInt16,  ttUInt16, ttInt8,   ttUInt8},
		{ttInt64,  ttUInt64, ttInt,    ttUInt,   ttInt16,  ttUInt16, ttInt8,   ttUInt8,  ttDouble, ttFloat},
		{ttUInt64, ttInt64,  ttUInt,   ttInt,    ttUInt16, ttInt16,  ttUInt8,  ttInt8,   ttDouble, ttFloat},
		{ttInt,    ttUInt,   ttInt64,  ttUInt64, ttInt16,  ttUInt16, ttInt8,   ttUInt8,  ttDouble, ttFloat},
		{ttUInt,   ttInt,    ttUInt64, ttInt64,  ttUInt16, ttInt16,  ttUInt8,  ttInt8,   ttDouble, ttFloat},
		{ttInt16,  ttUInt16, ttInt,    ttUInt,   ttInt64,  ttUInt64, ttInt8,   ttUInt8,  ttDouble, ttFloat},
		{ttUInt16, ttInt16,  ttUInt,   ttInt,    ttUInt64, ttInt64,  ttUInt8,  ttInt8,   ttDouble, ttFloat},
		{ttInt8,   ttUInt8,  ttInt16,  ttUInt16, ttInt,    ttUInt,   ttInt64,  ttUInt64, ttDouble, ttFloat},
		{ttUInt8,  ttInt8,   ttUInt16, ttInt16,  ttUInt,   ttInt,    ttUInt64, ttInt64,  ttDouble, ttFloat},
	};

	// Which row to use?
	eTokenType *row = 0;
	for( unsigned int type = 0; type < 10; type++ )
	{
		if( to.GetTokenType() == matchMtx[type][0] )
		{
			row = &matchMtx[type][0];
			break;
		}
	}

	// Find the best matching cast operator
	int funcId = 0;
	if( row )
	{
		asCDataType target(to);

		// Priority goes from left to right in the matrix
		for( unsigned int attempt = 0; attempt < 10 && funcId == 0; attempt++ )
		{
			target.SetTokenType(row[attempt]);
			for( unsigned int n = 0; n < funcs.GetLength(); n++ )
			{
				asCScriptFunction *descr = builder->GetFunctionDescription(funcs[n]);
				if( descr->returnType.IsEqualExceptConst(target) )
				{
					funcId = funcs[n];
					break;
				}
			}
		}
	}

	// Did we find a suitable function?
	if( funcId != 0 )
	{
		asCScriptFunction *descr = builder->GetFunctionDescription(funcId);
		if( generateCode )
		{
			asCTypeInfo objType = ctx->type;

			Dereference(ctx, true);

			PerformFunctionCall(funcId, ctx);

			ReleaseTemporaryVariable(objType, &ctx->bc);
		}
		else
			ctx->type.Set(descr->returnType);

		// Allow one more implicit conversion to another primitive type
		ImplicitConversion(ctx, to, node, convType, generateCode, reservedVars, false);
	}
	else
	{
		if( convType != asIC_IMPLICIT_CONV && node )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
			Error(str.AddressOf(), node);
		}
	}
}



void asCCompiler::ImplicitConvObjectToObject(asSExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode, asCArray<int> *reservedVars, bool allowObjectConstruct)
{
	// Convert null to any object type handle, but not to a non-handle type
	if( ctx->type.IsNullConstant() )
	{
		if( to.IsObjectHandle() )
			ctx->type.dataType = to;

		return;
	}

	// First attempt to convert the base type without instanciating another instance
	if( to.GetObjectType() != ctx->type.dataType.GetObjectType() )
	{
		// If the to type is an interface and the from type implements it, then we can convert it immediately
		if( ctx->type.dataType.GetObjectType()->Implements(to.GetObjectType()) )
		{
			ctx->type.dataType.SetObjectType(to.GetObjectType());
		}

		// If the to type is a class and the from type derives from it, then we can convert it immediately
		if( ctx->type.dataType.GetObjectType()->DerivesFrom(to.GetObjectType()) )
		{
			ctx->type.dataType.SetObjectType(to.GetObjectType());
		}

		// If the types are not equal yet, then we may still be able to find a reference cast
		if( ctx->type.dataType.GetObjectType() != to.GetObjectType() )
		{
			// A ref cast must not remove the constness
			bool isConst = false;
			if( (ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsHandleToConst()) ||
				(!ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsReadOnly()) )
				isConst = true;

			// We may still be able to find an implicit ref cast behaviour
			CompileRefCast(ctx, to, convType == asIC_EXPLICIT_REF_CAST, node, generateCode);

			ctx->type.dataType.MakeHandleToConst(isConst);
		}
	}

	// If the base type is still different, and we are allowed to instance
	// another object then we can try an implicit value cast
	if( to.GetObjectType() != ctx->type.dataType.GetObjectType() && allowObjectConstruct )
	{
		// TODO: Implement support for implicit constructor/factory

		asCArray<int> funcs;
		asSTypeBehaviour *beh = ctx->type.dataType.GetBehaviour();
		if( beh )
		{
			if( convType == asIC_EXPLICIT_VAL_CAST )
			{
				for( unsigned int n = 0; n < beh->operators.GetLength(); n += 2 )
				{
					// accept both implicit and explicit cast
					if( (beh->operators[n] == asBEHAVE_VALUE_CAST ||
						 beh->operators[n] == asBEHAVE_IMPLICIT_VALUE_CAST) &&
						builder->GetFunctionDescription(beh->operators[n+1])->returnType.GetObjectType() == to.GetObjectType() )
						funcs.PushLast(beh->operators[n+1]);
				}
			}
			else
			{
				for( unsigned int n = 0; n < beh->operators.GetLength(); n += 2 )
				{
					// accept only implicit cast
					if( beh->operators[n] == asBEHAVE_IMPLICIT_VALUE_CAST &&
						builder->GetFunctionDescription(beh->operators[n+1])->returnType.GetObjectType() == to.GetObjectType() )
						funcs.PushLast(beh->operators[n+1]);
				}
			}
		}

		// TODO: If there are multiple valid value casts, then we must choose the most appropriate one
		asASSERT( funcs.GetLength() <= 1 );

		if( funcs.GetLength() == 1 )
		{
			asCScriptFunction *f = builder->GetFunctionDescription(funcs[0]);
			if( generateCode )
			{
				asCTypeInfo objType = ctx->type;
				Dereference(ctx, true);
				PerformFunctionCall(funcs[0], ctx);
				ReleaseTemporaryVariable(objType, &ctx->bc);
			}
			else
				ctx->type.Set(f->returnType);
		}
	}

	// If we still haven't converted the base type to the correct type, then there is no need to continue
	if( to.GetObjectType() != ctx->type.dataType.GetObjectType() )
		return;

	// Convert matching function types
	if( to.GetFuncDef() && ctx->type.dataType.GetFuncDef() &&
		to.GetFuncDef() != ctx->type.dataType.GetFuncDef() )
	{
		asCScriptFunction *toFunc = to.GetFuncDef();
		asCScriptFunction *fromFunc = ctx->type.dataType.GetFuncDef();
		if( toFunc->IsSignatureExceptNameEqual(fromFunc) )
		{
			ctx->type.dataType.SetFuncDef(toFunc);
		}
	}


	if( to.IsObjectHandle() )
	{
		// reference to handle -> handle
		// reference           -> handle
		// object              -> handle
		// handle              -> reference to handle
		// reference           -> reference to handle
		// object              -> reference to handle

		// TODO: If the type is handle, then we can't use IsReadOnly to determine the constness of the basetype

		// If the rvalue is a handle to a const object, then
		// the lvalue must also be a handle to a const object
		if( ctx->type.dataType.IsReadOnly() && !to.IsReadOnly() )
		{
			if( convType != asIC_IMPLICIT_CONV )
			{
				asASSERT(node);
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
				Error(str.AddressOf(), node);
			}
		}

		if( !ctx->type.dataType.IsObjectHandle() )
		{
			// An object type can be directly converted to a handle of the same type
			if( ctx->type.dataType.SupportHandles() )
			{
				ctx->type.dataType.MakeHandle(true);
			}

			if( ctx->type.dataType.IsObjectHandle() )
				ctx->type.dataType.MakeReadOnly(to.IsReadOnly());

			if( to.IsHandleToConst() && ctx->type.dataType.IsObjectHandle() )
				ctx->type.dataType.MakeHandleToConst(true);
		}
		else
		{
			// A handle to non-const can be converted to a  
			// handle to const, but not the other way
			if( to.IsHandleToConst() )
				ctx->type.dataType.MakeHandleToConst(true);

			// A const handle can be converted to a non-const 
			// handle and vice versa as the handle is just a value
			ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
		}

		if( to.IsReference() && !ctx->type.dataType.IsReference() )
		{
			if( generateCode )
			{
				// If the input type is a handle, then a simple ref copy is enough
				bool isExplicitHandle = ctx->type.isExplicitHandle;
				ctx->type.isExplicitHandle = ctx->type.dataType.IsObjectHandle();				

				// If the input type is read-only we'll need to temporarily
				// remove this constness, otherwise the assignment will fail
				bool typeIsReadOnly = ctx->type.dataType.IsReadOnly();
				ctx->type.dataType.MakeReadOnly(false);

				// If the object already is a temporary variable, then the copy 
				// doesn't have to be made as it is already a unique object
				PrepareTemporaryObject(node, ctx, reservedVars);

				ctx->type.dataType.MakeReadOnly(typeIsReadOnly);
				ctx->type.isExplicitHandle = isExplicitHandle;
			}

			// A non-reference can be converted to a reference,
			// by putting the value in a temporary variable
			ctx->type.dataType.MakeReference(true);

			// Since it is a new temporary variable it doesn't have to be const
			ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
		}
		else if( !to.IsReference() && ctx->type.dataType.IsReference() )
		{
			Dereference(ctx, generateCode);
		}
	}
	else
	{
		if( !to.IsReference() )
		{
			// reference to handle -> object
			// handle              -> object
			// reference           -> object

			// An implicit handle can be converted to an object by adding a check for null pointer
			if( ctx->type.dataType.IsObjectHandle() && !ctx->type.isExplicitHandle )
			{
				if( generateCode )
					ctx->bc.Instr(asBC_CHKREF);

				ctx->type.dataType.MakeHandle(false);
			}

			// A const object can be converted to a non-const object through a copy
			if( ctx->type.dataType.IsReadOnly() && !to.IsReadOnly() &&
				allowObjectConstruct )
			{
				// Does the object type allow a copy to be made?
				if( ctx->type.dataType.CanBeCopied() )
				{
					if( generateCode )
					{
						// Make a temporary object with the copy
						PrepareTemporaryObject(node, ctx, reservedVars);
					}

					// In case the object was already in a temporary variable, then the function
					// didn't really do anything so we need to remove the constness here
					ctx->type.dataType.MakeReadOnly(false);
				}
			}

			if( ctx->type.dataType.IsReference() )
			{
				Dereference(ctx, generateCode);

				// TODO: Can't this leave unhandled deferred output params?
			}

			// A non-const object can be converted to a const object directly
			if( !ctx->type.dataType.IsReadOnly() && to.IsReadOnly() )
			{
				ctx->type.dataType.MakeReadOnly(true);
			}
		}
		else
		{
			// reference to handle -> reference
			// handle              -> reference
			// object              -> reference

			if( ctx->type.dataType.IsReference() )
			{
				// A reference to a handle can be converted to a reference to an object
				// by first reading the address, then verifying that it is not null, then putting the address back on the stack
				if( !to.IsObjectHandle() && ctx->type.dataType.IsObjectHandle() && !ctx->type.isExplicitHandle )
				{
					ctx->type.dataType.MakeHandle(false);
					if( generateCode )
						ctx->bc.Instr(asBC_ChkRefS);
				}

				// A reference to a non-const can be converted to a reference to a const
				if( to.IsReadOnly() )
					ctx->type.dataType.MakeReadOnly(true);
				else if( ctx->type.dataType.IsReadOnly() )
				{
					// A reference to a const can be converted to a reference to a
					// non-const by copying the object to a temporary variable
					ctx->type.dataType.MakeReadOnly(false);

					if( generateCode )
					{
						// If the object already is a temporary variable, then the copy 
						// doesn't have to be made as it is already a unique object
						PrepareTemporaryObject(node, ctx, reservedVars);
					}
				}
			}
			else
			{
				// A value type allocated on the stack is differentiated
				// by it not being a reference. But it can be handled as 
				// reference by pushing the pointer on the stack
				if( (ctx->type.dataType.GetObjectType()->GetFlags() & asOBJ_VALUE) &&
					(ctx->type.isVariable || ctx->type.isTemporary) &&
					!IsVariableOnHeap(ctx->type.stackOffset) )
				{
					// Actually the pointer is already pushed on the stack in 
					// CompileVariableAccess, so we don't need to do anything else
				}
				else if( generateCode )
				{
					// A non-reference can be converted to a reference,
					// by putting the value in a temporary variable

					// If the input type is read-only we'll need to temporarily
					// remove this constness, otherwise the assignment will fail
					bool typeIsReadOnly = ctx->type.dataType.IsReadOnly();
					ctx->type.dataType.MakeReadOnly(false);

					// If the object already is a temporary variable, then the copy 
					// doesn't have to be made as it is already a unique object
					PrepareTemporaryObject(node, ctx, reservedVars);

					ctx->type.dataType.MakeReadOnly(typeIsReadOnly);
				}

				// A handle can be converted to a reference, by checking for a null pointer
				if( ctx->type.dataType.IsObjectHandle() )
				{
					if( generateCode )
						ctx->bc.InstrSHORT(asBC_ChkNullV, ctx->type.stackOffset);
					ctx->type.dataType.MakeHandle(false);
					ctx->type.dataType.MakeReference(true);

					// TODO: Make sure a handle to const isn't converted to non-const reference
				}
				else
				{
					// This may look strange as the conversion was to make the expression a reference
					// but a value type allocated on the stack is a reference even without the type 
					// being marked as such.
					ctx->type.dataType.MakeReference(IsVariableOnHeap(ctx->type.stackOffset));
				}

				// TODO: If the variable is an object allocated on the stack, this is not true
				// Since it is a new temporary variable it doesn't have to be const
				ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
			}
		}
	}
}

void asCCompiler::ImplicitConvPrimitiveToObject(asSExprContext * /*ctx*/, const asCDataType & /*to*/, asCScriptNode * /*node*/, EImplicitConv /*isExplicit*/, bool /*generateCode*/, asCArray<int> * /*reservedVars*/, bool /*allowObjectConstruct*/)
{
	// TODO: This function should call the constructor/factory that has been marked as available 
	//       for implicit conversions. The code will likely be similar to CallCopyConstructor()
}

void asCCompiler::ImplicitConversionConstant(asSExprContext *from, const asCDataType &to, asCScriptNode *node, EImplicitConv convType)
{
	asASSERT(from->type.isConstant);

	// TODO: node should be the node of the value that is
	//       converted (not the operator that provokes the implicit
	//       conversion)

	// If the base type is correct there is no more to do
	if( to.IsEqualExceptRefAndConst(from->type.dataType) ) return;

	// References cannot be constants
	if( from->type.dataType.IsReference() ) return;

	if( (to.IsIntegerType() && to.GetSizeInMemoryDWords() == 1) ||
		(to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST) )
	{
		if( from->type.dataType.IsFloatType() ||
			from->type.dataType.IsDoubleType() ||
			from->type.dataType.IsUnsignedType() ||
			from->type.dataType.IsIntegerType() ||
			from->type.dataType.IsEnumType() )
		{
			// Transform the value
			// Float constants can be implicitly converted to int
			if( from->type.dataType.IsFloatType() )
			{
				float fc = from->type.floatValue;
				int ic = int(fc);

				if( float(ic) != fc )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
				}

				from->type.intValue = ic;
			}
			// Double constants can be implicitly converted to int
			else if( from->type.dataType.IsDoubleType() )
			{
				double fc = from->type.doubleValue;
				int ic = int(fc);

				if( double(ic) != fc )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
				}

				from->type.intValue = ic;
			}
			else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				// Verify that it is possible to convert to signed without getting negative
				if( from->type.intValue < 0 )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
				}

				// Convert to 32bit
				if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
					from->type.intValue = from->type.byteValue;
				else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
					from->type.intValue = from->type.wordValue;
			}
			else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				// Convert to 32bit
				from->type.intValue = int(from->type.qwordValue);
			}
			else if( from->type.dataType.IsIntegerType() &&
					from->type.dataType.GetSizeInMemoryBytes() < 4 )
			{
				// Convert to 32bit
				if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
					from->type.intValue = (signed char)from->type.byteValue;
				else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
					from->type.intValue = (short)from->type.wordValue;
			}
			else if( from->type.dataType.IsEnumType() )
			{
				// Enum type is already an integer type
			}

			// Set the resulting type
			if( to.IsEnumType() )
				from->type.dataType = to;
			else
				from->type.dataType = asCDataType::CreatePrimitive(ttInt, true);
		}

		// Check if a downsize is necessary
		if( to.IsIntegerType() &&
			from->type.dataType.IsIntegerType() &&
		    from->type.dataType.GetSizeInMemoryBytes() > to.GetSizeInMemoryBytes() )
		{
			// Verify if it is possible
			if( to.GetSizeInMemoryBytes() == 1 )
			{
				if( char(from->type.intValue) != from->type.intValue )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.byteValue = char(from->type.intValue);
			}
			else if( to.GetSizeInMemoryBytes() == 2 )
			{
				if( short(from->type.intValue) != from->type.intValue )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.wordValue = short(from->type.intValue);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
		}
	}
	else if( to.IsIntegerType() && to.GetSizeInMemoryDWords() == 2 )
	{
		// Float constants can be implicitly converted to int
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.floatValue;
			asINT64 ic = asINT64(fc);

			if( float(ic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
			from->type.qwordValue = ic;
		}
		// Double constants can be implicitly converted to int
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.doubleValue;
			asINT64 ic = asINT64(fc);

			if( double(ic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
			from->type.qwordValue = ic;
		}
		else if( from->type.dataType.IsUnsignedType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.qwordValue = from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.qwordValue = from->type.wordValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.qwordValue = from->type.dwordValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 8 )
			{
				if( asINT64(from->type.qwordValue) < 0 )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
				}
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
		}
		else if( from->type.dataType.IsEnumType() )
		{
			from->type.qwordValue = from->type.intValue;
			from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
		}
		else if( from->type.dataType.IsIntegerType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.qwordValue = (signed char)from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.qwordValue = (short)from->type.wordValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.qwordValue = from->type.intValue;

			from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
		}
	}
	else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 1 )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.floatValue;
			int uic = int(fc);

			if( float(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}
			else if( uic < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttInt, true);
			from->type.intValue = uic;

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.doubleValue;
			int uic = int(fc);

			if( double(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttInt, true);
			from->type.intValue = uic;

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsEnumType() )
		{
			from->type.dataType = asCDataType::CreatePrimitive(ttUInt, true);

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsIntegerType() )
		{
			// Verify that it is possible to convert to unsigned without loosing negative
			if( from->type.intValue < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			// Convert to 32bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.intValue = (signed char)from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.intValue = (short)from->type.wordValue;

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt, true);

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsUnsignedType() &&
		         from->type.dataType.GetSizeInMemoryBytes() < 4 )
		{
			// Convert to 32bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.dwordValue = from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.dwordValue = from->type.wordValue;

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt, true);

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsUnsignedType() &&
		         from->type.dataType.GetSizeInMemoryBytes() > to.GetSizeInMemoryBytes() )
		{
			// Verify if it is possible
			if( to.GetSizeInMemoryBytes() == 1 )
			{
				if( asBYTE(from->type.dwordValue) != from->type.dwordValue )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.byteValue = asBYTE(from->type.dwordValue);
			}
			else if( to.GetSizeInMemoryBytes() == 2 )
			{
				if( asWORD(from->type.dwordValue) != from->type.dwordValue )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.wordValue = asWORD(from->type.dwordValue);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
		}
	}
	else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 2 )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.floatValue;
			// Convert first to int64 then to uint64 to avoid negative float becoming 0 on gnuc base compilers
			asQWORD uic = asQWORD(asINT64(fc));

			// TODO: MSVC6 doesn't permit UINT64 to double
			if( float((signed)uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
			from->type.qwordValue = uic;
		}
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.doubleValue;
			// Convert first to int64 then to uint64 to avoid negative float becoming 0 on gnuc base compilers
			asQWORD uic = asQWORD(asINT64(fc));

			// TODO: MSVC6 doesn't permit UINT64 to double
			if( double((signed)uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
			from->type.qwordValue = uic;
		}
		else if( from->type.dataType.IsEnumType() )
		{
			from->type.qwordValue = (asINT64)from->type.intValue;
			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.qwordValue = (asINT64)(signed char)from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.qwordValue = (asINT64)(short)from->type.wordValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.qwordValue = (asINT64)from->type.intValue;

			// Verify that it is possible to convert to unsigned without loosing negative
			if( asINT64(from->type.qwordValue) < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			// Verify that it is possible to convert to unsigned without loosing negative
			if( asINT64(from->type.qwordValue) < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
		else if( from->type.dataType.IsUnsignedType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.qwordValue = from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.qwordValue = from->type.wordValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.qwordValue = from->type.dwordValue;

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
	}
	else if( to.IsFloatType() )
	{
		if( from->type.dataType.IsDoubleType() )
		{
			double ic = from->type.doubleValue;
			float fc = float(ic);

			if( double(fc) != ic )
			{
				asCString str;
				str.Format(TXT_POSSIBLE_LOSS_OF_PRECISION);
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(str.AddressOf(), node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
		else if( from->type.dataType.IsEnumType() )
		{
			float fc = float(from->type.intValue);

			if( int(fc) != from->type.intValue )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			int ic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				ic = (signed char)from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				ic = (short)from->type.wordValue;
			else
				ic = from->type.intValue;
			float fc = float(ic);

			if( int(fc) != ic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			float fc = float(asINT64(from->type.qwordValue));
			if( asINT64(fc) != asINT64(from->type.qwordValue) )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			unsigned int uic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				uic = from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				uic = from->type.wordValue;
			else
				uic = from->type.dwordValue;
			float fc = float(uic);

			if( (unsigned int)(fc) != uic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			// TODO: MSVC6 doesn't permit UINT64 to double
			float fc = float((signed)from->type.qwordValue);

			if( asQWORD(fc) != from->type.qwordValue )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.floatValue = fc;
		}
	}
	else if( to.IsDoubleType() )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float ic = from->type.floatValue;
			double fc = double(ic);

			// Don't check for float->double
		//	if( float(fc) != ic )
		//	{
		//		acCString str;
		//		str.Format(TXT_NOT_EXACT_g_g_g, ic, fc, float(fc));
		//		if( !isExplicit ) Warning(str, node);
		//	}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
		else if( from->type.dataType.IsEnumType() )
		{
			double fc = double(from->type.intValue);

			if( int(fc) != from->type.intValue )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			int ic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				ic = (signed char)from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				ic = (short)from->type.wordValue;
			else
				ic = from->type.intValue;
			double fc = double(ic);

			if( int(fc) != ic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			double fc = double(asINT64(from->type.qwordValue));

			if( asINT64(fc) != asINT64(from->type.qwordValue) )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			unsigned int uic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				uic = from->type.byteValue;
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				uic = from->type.wordValue;
			else
				uic = from->type.dwordValue;
			double fc = double(uic);

			if( (unsigned int)(fc) != uic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			// TODO: MSVC6 doesn't permit UINT64 to double
			double fc = double((signed)from->type.qwordValue);

			if( asQWORD(fc) != from->type.qwordValue )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(to.GetTokenType(), true);
			from->type.doubleValue = fc;
		}
	}
}

int asCCompiler::DoAssignment(asSExprContext *ctx, asSExprContext *lctx, asSExprContext *rctx, asCScriptNode *lexpr, asCScriptNode *rexpr, int op, asCScriptNode *opNode)
{
	// Implicit handle types should always be treated as handles in assignments
	if (lctx->type.dataType.GetObjectType() && (lctx->type.dataType.GetObjectType()->flags & asOBJ_IMPLICIT_HANDLE) )
	{
		lctx->type.dataType.MakeHandle(true);
		lctx->type.isExplicitHandle = true;
	}

	// If the left hand expression is a property accessor, then that should be used
	// to do the assignment instead of the ordinary operator. The exception is when
	// the property accessor is for a handle property, and the operation is a value
	// assignment.
	if( (lctx->property_get || lctx->property_set) &&
		!(lctx->type.dataType.IsObjectHandle() && !lctx->type.isExplicitHandle) )
	{
		if( op != ttAssignment )
		{
			// TODO: getset: We may actually be able to support this, if we can 
			//               guarantee that the object reference will stay valid 
			//               between the calls to the get and set accessors.

			// Compound assignments are not allowed for properties
			Error(TXT_COMPOUND_ASGN_WITH_PROP, opNode);
			return -1;
		}

		// It is not allowed to do a handle assignment on a property accessor that
		//  doesn't take a handle in the set accessor.
		if( lctx->property_set && 
			lctx->type.isExplicitHandle && 
			!engine->scriptFunctions[lctx->property_set]->parameterTypes[0].IsObjectHandle() )
		{
			Error(TXT_HANDLE_ASSIGN_ON_NON_HANDLE_PROP, opNode);
			return -1;
		}

		MergeExprBytecodeAndType(ctx, lctx);

		return ProcessPropertySetAccessor(ctx, rctx, opNode);
	}

	if( lctx->type.dataType.IsPrimitive() )
	{
		if( op != ttAssignment )
		{
			// Compute the operator before the assignment
			asCTypeInfo lvalue = lctx->type;

			if( lctx->type.isTemporary && !lctx->type.isVariable )
			{
				// The temporary variable must not be freed until the
				// assignment has been performed. lvalue still holds
				// the information about the temporary variable
				lctx->type.isTemporary = false;
			}

			asSExprContext o(engine);
			CompileOperator(opNode, lctx, rctx, &o);
			MergeExprBytecode(rctx, &o);
			rctx->type = o.type;

			// Convert the rvalue to the right type and validate it
			PrepareForAssignment(&lvalue.dataType, rctx, rexpr);

			MergeExprBytecode(ctx, rctx);
			lctx->type = lvalue;

			// The lvalue continues the same, either it was a variable, or a reference in the register
		}
		else
		{
			// Convert the rvalue to the right type and validate it
			PrepareForAssignment(&lctx->type.dataType, rctx, rexpr, lctx);

			MergeExprBytecode(ctx, rctx);
			MergeExprBytecode(ctx, lctx);
		}

		ReleaseTemporaryVariable(rctx->type, &ctx->bc);

		PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

		ctx->type = lctx->type;
	}
	else if( lctx->type.isExplicitHandle )
	{
		// Verify that the left hand value isn't a temporary variable
		if( lctx->type.isTemporary )
		{
			Error(TXT_REF_IS_TEMP, lexpr);
			return -1;
		}

		// Object handles don't have any compound assignment operators
		if( op != ttAssignment )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), lexpr);
			return -1;
		}

		asCDataType dt = lctx->type.dataType;
		dt.MakeReference(false);

		PrepareArgument(&dt, rctx, rexpr, true, 1);
		if( !dt.IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format().AddressOf(), lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), rexpr);
			return -1;
		}

		MergeExprBytecode(ctx, rctx);
		MergeExprBytecode(ctx, lctx);

		ctx->bc.InstrWORD(asBC_GETOBJREF, AS_PTR_SIZE);

		PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

		ReleaseTemporaryVariable(rctx->type, &ctx->bc);

		ctx->type = rctx->type;
	}
	else // if( lctx->type.dataType.IsObject() )
	{
		// Verify that the left hand value isn't a temporary variable
		if( lctx->type.isTemporary )
		{
			Error(TXT_REF_IS_TEMP, lexpr);
			return -1;
		}

		if( lctx->type.dataType.IsObjectHandle() && !lctx->type.isExplicitHandle )
		{
			// Convert the handle to a object reference
			asCDataType to;
			to = lctx->type.dataType;
			to.MakeHandle(false);
			ImplicitConversion(lctx, to, lexpr, asIC_IMPLICIT_CONV);
		}

		// Check for overloaded assignment operator
		if( CompileOverloadedDualOperator(opNode, lctx, rctx, ctx) )
		{
			// An overloaded assignment operator was found (or a compilation error occured)
			return 0;
		}

		// No registered operator was found. In case the operation is a direct
		// assignment and the rvalue is the same type as the lvalue, then we can
		// still use the byte-for-byte copy to do the assignment

		if( op != ttAssignment )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), lexpr);
			return -1;
		}

		// Implicitly convert the rvalue to the type of the lvalue
		asCDataType dt = lctx->type.dataType;
		dt.MakeReference(true);
		dt.MakeReadOnly(true);
		PrepareArgument(&dt, rctx, rexpr, true, 1);
		if( !dt.IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format().AddressOf(), lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), rexpr);
			return -1;
		}

		MergeExprBytecode(ctx, rctx);
		MergeExprBytecode(ctx, lctx);

		if( (rctx->type.isVariable || rctx->type.isTemporary) && !IsVariableOnHeap(rctx->type.stackOffset) )
			// TODO: optimize: Actually the reference can be pushed on the stack directly
			//                 as the value allocated on the stack is guaranteed to be safe
			ctx->bc.InstrWORD(asBC_GETREF, AS_PTR_SIZE);
		else
			ctx->bc.InstrWORD(asBC_GETOBJREF, AS_PTR_SIZE);

		PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

		ReleaseTemporaryVariable(rctx->type, &ctx->bc);

		ctx->type = lctx->type;
	}

	return 0;
}

int asCCompiler::CompileAssignment(asCScriptNode *expr, asSExprContext *ctx)
{
	asCScriptNode *lexpr = expr->firstChild;
	if( lexpr->next )
	{
		if( globalExpression )
		{
			Error(TXT_ASSIGN_IN_GLOBAL_EXPR, expr);
			ctx->type.SetDummy();
			return -1;
		}

		// Compile the two expression terms
		asSExprContext lctx(engine), rctx(engine);
		int rr = CompileAssignment(lexpr->next->next, &rctx);
		int lr = CompileCondition(lexpr, &lctx);

		if( lr >= 0 && rr >= 0 )
			return DoAssignment(ctx, &lctx, &rctx, lexpr, lexpr->next->next, lexpr->next->tokenType, lexpr->next);

		// Since the operands failed, the assignment was not computed
		ctx->type.SetDummy();
		return -1;
	}

	return CompileCondition(lexpr, ctx);
}

int asCCompiler::CompileCondition(asCScriptNode *expr, asSExprContext *ctx)
{
	asCTypeInfo ctype;

	// Compile the conditional expression
	asCScriptNode *cexpr = expr->firstChild;
	if( cexpr->next )
	{
		//-------------------------------
		// Compile the condition
		asSExprContext e(engine);
		int r = CompileExpression(cexpr, &e);
		if( r < 0 )
			e.type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
		if( r >= 0 && !e.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		{
			Error(TXT_EXPR_MUST_BE_BOOL, cexpr);
			e.type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
		}
		ctype = e.type;

		ProcessPropertyGetAccessor(&e, cexpr);

		if( e.type.dataType.IsReference() ) ConvertToVariable(&e);
		ProcessDeferredParams(&e);

		//-------------------------------
		// Compile the left expression
		asSExprContext le(engine);
		int lr = CompileAssignment(cexpr->next, &le);

		//-------------------------------
		// Compile the right expression
		asSExprContext re(engine);
		int rr = CompileAssignment(cexpr->next->next, &re);

		if( lr >= 0 && rr >= 0 )
		{
			ProcessPropertyGetAccessor(&le, cexpr->next);
			ProcessPropertyGetAccessor(&re, cexpr->next->next);

			bool isExplicitHandle = le.type.isExplicitHandle || re.type.isExplicitHandle;

			// Allow a 0 in the first case to be implicitly converted to the second type
			if( le.type.isConstant && le.type.intValue == 0 && le.type.dataType.IsUnsignedType() )
			{
				asCDataType to = re.type.dataType;
				to.MakeReference(false);
				to.MakeReadOnly(true);
				ImplicitConversionConstant(&le, to, cexpr->next, asIC_IMPLICIT_CONV);
			}

			//---------------------------------
			// Output the byte code
			int afterLabel = nextLabel++;
			int elseLabel = nextLabel++;

			// If left expression is void, then we don't need to store the result
			if( le.type.dataType.IsEqualExceptConst(asCDataType::CreatePrimitive(ttVoid, false)) )
			{
				// Put the code for the condition expression on the output
				MergeExprBytecode(ctx, &e);

				// Added the branch decision
				ctx->type = e.type;
				ConvertToVariable(ctx);
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, ctx->type.stackOffset);
				ctx->bc.Instr(asBC_ClrHi);
				ctx->bc.InstrDWORD(asBC_JZ, elseLabel);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);

				// Add the left expression
				MergeExprBytecode(ctx, &le);
				ctx->bc.InstrINT(asBC_JMP, afterLabel);

				// Add the right expression
				ctx->bc.Label((short)elseLabel);
				MergeExprBytecode(ctx, &re);
				ctx->bc.Label((short)afterLabel);

				// Make sure both expressions have the same type
				if( le.type.dataType != re.type.dataType )
					Error(TXT_BOTH_MUST_BE_SAME, expr);

				// Set the type of the result
				ctx->type = le.type;
			}
			else
			{
				// Allocate temporary variable and copy the result to that one
				asCTypeInfo temp;
				temp = le.type;
				temp.dataType.MakeReference(false);
				temp.dataType.MakeReadOnly(false);
				// Make sure the variable isn't used in the initial expression
				asCArray<int> vars;
				e.bc.GetVarsUsed(vars);
				int offset = AllocateVariableNotIn(temp.dataType, true, &vars);
				temp.SetVariable(temp.dataType, offset, true);

				// TODO: copy: Use copy constructor if available. See PrepareTemporaryObject()

				CallDefaultConstructor(temp.dataType, offset, IsVariableOnHeap(offset), &ctx->bc, expr);

				// Put the code for the condition expression on the output
				MergeExprBytecode(ctx, &e);

				// Add the branch decision
				ctx->type = e.type;
				ConvertToVariable(ctx);
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, ctx->type.stackOffset);
				ctx->bc.Instr(asBC_ClrHi);
				ctx->bc.InstrDWORD(asBC_JZ, elseLabel);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);

				// Assign the result of the left expression to the temporary variable
				asCTypeInfo rtemp;
				rtemp = temp;
				if( rtemp.dataType.IsObjectHandle() )
					rtemp.isExplicitHandle = true;

				PrepareForAssignment(&rtemp.dataType, &le, cexpr->next);
				MergeExprBytecode(ctx, &le);

				if( !rtemp.dataType.IsPrimitive() )
				{
					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
					rtemp.dataType.MakeReference(IsVariableOnHeap(offset));
				}
				PerformAssignment(&rtemp, &le.type, &ctx->bc, cexpr->next);
				if( !rtemp.dataType.IsPrimitive() )
					ctx->bc.Pop(le.type.dataType.GetSizeOnStackDWords()); // Pop the original value

				// Release the old temporary variable
				ReleaseTemporaryVariable(le.type, &ctx->bc);

				ctx->bc.InstrINT(asBC_JMP, afterLabel);

				// Start of the right expression
				ctx->bc.Label((short)elseLabel);

				// Copy the result to the same temporary variable
				PrepareForAssignment(&rtemp.dataType, &re, cexpr->next);
				MergeExprBytecode(ctx, &re);

				if( !rtemp.dataType.IsPrimitive() )
				{
					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
					rtemp.dataType.MakeReference(IsVariableOnHeap(offset));
				}
				PerformAssignment(&rtemp, &re.type, &ctx->bc, cexpr->next);
				if( !rtemp.dataType.IsPrimitive() )
					ctx->bc.Pop(le.type.dataType.GetSizeOnStackDWords()); // Pop the original value

				// Release the old temporary variable
				ReleaseTemporaryVariable(re.type, &ctx->bc);

				ctx->bc.Label((short)afterLabel);

				// Make sure both expressions have the same type
				if( le.type.dataType != re.type.dataType )
					Error(TXT_BOTH_MUST_BE_SAME, expr);

				// Set the temporary variable as output
				ctx->type = rtemp;
				ctx->type.isExplicitHandle = isExplicitHandle;

				if( !ctx->type.dataType.IsPrimitive() )
				{
					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
					ctx->type.dataType.MakeReference(IsVariableOnHeap(offset));
				}

				// Make sure the output isn't marked as being a literal constant
				ctx->type.isConstant = false;
			}
		}
		else
		{
			ctx->type.SetDummy();
			return -1;
		}
	}
	else
		return CompileExpression(cexpr, ctx);

	return 0;
}

int asCCompiler::CompileExpression(asCScriptNode *expr, asSExprContext *ctx)
{
	asASSERT(expr->nodeType == snExpression);

	// Count the nodes
	int count = 0;
	asCScriptNode *node = expr->firstChild;
	while( node )
	{
		count++;
		node = node->next;
	}

	// Convert to polish post fix, i.e: a+b => ab+
	asCArray<asCScriptNode *> stack(count);
	asCArray<asCScriptNode *> stack2(count);
	asCArray<asCScriptNode *> postfix(count);

	node = expr->firstChild;
	while( node )
	{
		int precedence = GetPrecedence(node);

		while( stack.GetLength() > 0 &&
			   precedence <= GetPrecedence(stack[stack.GetLength()-1]) )
			stack2.PushLast(stack.PopLast());

		stack.PushLast(node);

		node = node->next;
	}

	while( stack.GetLength() > 0 )
		stack2.PushLast(stack.PopLast());

	// We need to swap operands so that the left
	// operand is always computed before the right
	SwapPostFixOperands(stack2, postfix);

	// Compile the postfix formatted expression
	return CompilePostFixExpression(&postfix, ctx);
}

void asCCompiler::SwapPostFixOperands(asCArray<asCScriptNode *> &postfix, asCArray<asCScriptNode *> &target)
{
	if( postfix.GetLength() == 0 ) return;

	asCScriptNode *node = postfix.PopLast();
	if( node->nodeType == snExprTerm )
	{
		target.PushLast(node);
		return;
	}

	SwapPostFixOperands(postfix, target);
	SwapPostFixOperands(postfix, target);

	target.PushLast(node);
}

int asCCompiler::CompilePostFixExpression(asCArray<asCScriptNode *> *postfix, asSExprContext *ctx)
{
	// Shouldn't send any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	// Set the context to a dummy type to avoid further 
	// errors in case the expression fails to compile
	ctx->type.SetDummy();

	// Pop the last node
	asCScriptNode *node = postfix->PopLast();
	ctx->exprNode = node;

	// If term, compile the term
	if( node->nodeType == snExprTerm )
		return CompileExpressionTerm(node, ctx);

	// Compile the two expression terms
	asSExprContext r(engine), l(engine);

	int ret;
	ret = CompilePostFixExpression(postfix, &l); if( ret < 0 ) return ret;
	ret = CompilePostFixExpression(postfix, &r); if( ret < 0 ) return ret;

	// Compile the operation
	return CompileOperator(node, &l, &r, ctx);
}

int asCCompiler::CompileExpressionTerm(asCScriptNode *node, asSExprContext *ctx)
{
	// Shouldn't send any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	// Set the type as a dummy by default, in case of any compiler errors
	ctx->type.SetDummy();

	// Compile the value node
	asCScriptNode *vnode = node->firstChild;
	while( vnode->nodeType != snExprValue )
		vnode = vnode->next;

	asSExprContext v(engine);
	int r = CompileExpressionValue(vnode, &v); if( r < 0 ) return r;

	// Compile post fix operators
	asCScriptNode *pnode = vnode->next;
	while( pnode )
	{
		r = CompileExpressionPostOp(pnode, &v); if( r < 0 ) return r;
		pnode = pnode->next;
	}

	// Compile pre fix operators
	pnode = vnode->prev;
	while( pnode )
	{
		r = CompileExpressionPreOp(pnode, &v); if( r < 0 ) return r;
		pnode = pnode->prev;
	}

	// Return the byte code and final type description
	MergeExprBytecodeAndType(ctx, &v);

	return 0;
}

int asCCompiler::CompileVariableAccess(const asCString &name, const asCString &scope, asSExprContext *ctx, asCScriptNode *errNode, bool isOptional, bool noFunction, asCObjectType *objType)
{
	bool found = false;

	// It is a local variable or parameter?
	sVariable *v = 0;
	if( scope == "" && !objType )
		v = variables->GetVariable(name.AddressOf());
	if( v )
	{
		found = true;

		if( v->isPureConstant )
			ctx->type.SetConstantQW(v->type, v->constantValue);
		else if( v->type.IsPrimitive() )
		{
			if( v->type.IsReference() )
			{
				// Copy the reference into the register
#if AS_PTR_SIZE == 1
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, (short)v->stackOffset);
#else
				ctx->bc.InstrSHORT(asBC_CpyVtoR8, (short)v->stackOffset);
#endif
				ctx->type.Set(v->type);
			}
			else
				ctx->type.SetVariable(v->type, v->stackOffset, false);
		}
		else
		{
			ctx->bc.InstrSHORT(asBC_PSF, (short)v->stackOffset);
			ctx->type.SetVariable(v->type, v->stackOffset, false);

			// If the variable is allocated on the heap we have a reference,
			// otherwise the actual object pointer is pushed on the stack.
			if( v->onHeap || v->type.IsObjectHandle() ) ctx->type.dataType.MakeReference(true);

			// Implicitly dereference handle parameters sent by reference
			if( v->type.IsReference() && (!v->type.IsObject() || v->type.IsObjectHandle()) )
				ctx->bc.Instr(asBC_RDSPTR);
		}
	}

	// Is it a class member?
	if( !found && ((objType) || (outFunc && outFunc->objectType && scope == "")) )
	{
		if( name == THIS_TOKEN && !objType )
		{
			asCDataType dt = asCDataType::CreateObject(outFunc->objectType, outFunc->isReadOnly);

			// The object pointer is located at stack position 0
			ctx->bc.InstrSHORT(asBC_PSF, 0);
			ctx->type.SetVariable(dt, 0, false);
			ctx->type.dataType.MakeReference(true);

			found = true;
		}

		if( !found )
		{
			// See if there are any matching property accessors
			asSExprContext access(engine);
			if( objType )
				access.type.Set(asCDataType::CreateObject(objType, false));
			else
				access.type.Set(asCDataType::CreateObject(outFunc->objectType, outFunc->isReadOnly));
			access.type.dataType.MakeReference(true);
			int r = 0;
			if( errNode->next && errNode->next->tokenType == ttOpenBracket )
			{
				// This is an index access, check if there is a property accessor that takes an index arg
				asSExprContext dummyArg(engine);
				r = FindPropertyAccessor(name, &access, &dummyArg, errNode);
			}
			if( r == 0 )
			{
				// Normal property access
				r = FindPropertyAccessor(name, &access, errNode);
			}
			if( r < 0 ) return -1;
			if( access.property_get || access.property_set )
			{
				if( !objType )
				{
					// Prepare the bytecode for the member access
					// This is only done when accessing through the implicit this pointer
					ctx->bc.InstrSHORT(asBC_PSF, 0);
				}
				MergeExprBytecodeAndType(ctx, &access);

				found = true;
			}
		}

		if( !found )
		{
			asCDataType dt;
			if( objType )
				dt = asCDataType::CreateObject(objType, false);
			else
				dt = asCDataType::CreateObject(outFunc->objectType, false);
			asCObjectProperty *prop = builder->GetObjectProperty(dt, name.AddressOf());
			if( prop )
			{
				if( !objType )
				{
					// The object pointer is located at stack position 0
					// This is only done when accessing through the implicit this pointer
					ctx->bc.InstrSHORT(asBC_PSF, 0);
					ctx->type.SetVariable(dt, 0, false);
					ctx->type.dataType.MakeReference(true);
					Dereference(ctx, true);
				}
				
				// TODO: This is the same as what is in CompileExpressionPostOp
				// Put the offset on the stack
				ctx->bc.InstrSHORT_DW(asBC_ADDSi, prop->byteOffset, engine->GetTypeIdFromDataType(dt));

				if( prop->type.IsReference() )
					ctx->bc.Instr(asBC_RDSPTR);

				// Reference to primitive must be stored in the temp register
				if( prop->type.IsPrimitive() )
				{
					// TODO: optimize: The ADD offset command should store the reference in the register directly
					ctx->bc.Instr(asBC_PopRPtr);
				}

				// Set the new type (keeping info about temp variable)
				ctx->type.dataType = prop->type;
				ctx->type.dataType.MakeReference(true);
				ctx->type.isVariable = false;

				if( ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle() )
				{
					// Objects that are members are not references
					ctx->type.dataType.MakeReference(false);
				}

				// If the object reference is const, the property will also be const
				ctx->type.dataType.MakeReadOnly(outFunc->isReadOnly);

				found = true;
			}
		}
	}

	// Is it a global property?
	if( !found && (scope == "" || scope == "::") && !objType )
	{
		// See if there are any matching global property accessors
		asSExprContext access(engine);
		int r = 0;
		if( errNode->next && errNode->next->tokenType == ttOpenBracket )
		{
			// This is an index access, check if there is a property accessor that takes an index arg
			asSExprContext dummyArg(engine);
			r = FindPropertyAccessor(name, &access, &dummyArg, errNode);
		}
		if( r == 0 )
		{
			// Normal property access
			r = FindPropertyAccessor(name, &access, errNode);
		}
		if( r < 0 ) return -1;
		if( access.property_get || access.property_set )
		{
			// Prepare the bytecode for the function call
			MergeExprBytecodeAndType(ctx, &access);

			found = true;
		}
		
		// See if there is any matching global property
		if( !found )
		{
			bool isCompiled = true;
			bool isPureConstant = false;
			asQWORD constantValue;
			asCGlobalProperty *prop = builder->GetGlobalProperty(name.AddressOf(), &isCompiled, &isPureConstant, &constantValue);
			if( prop )
			{
				found = true;

				// Verify that the global property has been compiled already
				if( isCompiled )
				{
					if( ctx->type.dataType.GetObjectType() && (ctx->type.dataType.GetObjectType()->flags & asOBJ_IMPLICIT_HANDLE) )
					{
						ctx->type.dataType.MakeHandle(true);
						ctx->type.isExplicitHandle = true;
					}

					// If the global property is a pure constant
					// we can allow the compiler to optimize it. Pure
					// constants are global constant variables that were
					// initialized by literal constants.
					if( isPureConstant )
						ctx->type.SetConstantQW(prop->type, constantValue);
					else
					{
						ctx->type.Set(prop->type);
						ctx->type.dataType.MakeReference(true);

						if( ctx->type.dataType.IsPrimitive() )
						{
							// Load the address of the variable into the register
							ctx->bc.InstrPTR(asBC_LDG, engine->globalProperties[prop->id]->GetAddressOfValue());
						}
						else
						{
							// Push the address of the variable on the stack
							ctx->bc.InstrPTR(asBC_PGA, engine->globalProperties[prop->id]->GetAddressOfValue());

							// If the object is a value type, then we must validate the existance,  
							// as it could potentially be accessed before it is initialized.
							if( ctx->type.dataType.GetObjectType()->flags & asOBJ_VALUE ||
								!ctx->type.dataType.IsObjectHandle() )
							{
								// TODO: optimize: This is not necessary for application registered properties
								ctx->bc.Instr(asBC_ChkRefS);
							}
						}
					}
				}
				else
				{
					asCString str;
					str.Format(TXT_UNINITIALIZED_GLOBAL_VAR_s, prop->name.AddressOf());
					Error(str.AddressOf(), errNode);
					return -1;
				}
			}
		}
	}

	// Is it the name of a global function?
	if( !noFunction && !found && (scope == "" || scope == "::") && !objType )
	{
		asCArray<int> funcs;
		builder->GetFunctionDescriptions(name.AddressOf(), funcs);

		if( funcs.GetLength() > 1 )
		{
			// TODO: funcdef: If multiple functions are found, then the compiler should defer the decision
			//                to which one it should use until the value is actually used. 
			//
			//                - assigning the function pointer to a variable
			//                - performing an explicit cast
			//                - passing the function pointer to a function as parameter
			asCString str;
			str.Format(TXT_MULTIPLE_MATCHING_SIGNATURES_TO_s, name.AddressOf());
			Error(str.AddressOf(), errNode);
			return -1;
		}
		else if( funcs.GetLength() == 1 )
		{
			found = true;

			// Push the function pointer on the stack
			ctx->bc.InstrPTR(asBC_FuncPtr, engine->scriptFunctions[funcs[0]]);
			ctx->type.Set(asCDataType::CreateFuncDef(engine->scriptFunctions[funcs[0]]));
		}
	}

	// Is it an enum value?
	if( !found && !objType )
	{
		asCObjectType *scopeType = 0;
		if( scope != "" )
		{
			// resolve the type before the scope
			scopeType = builder->GetObjectType( scope.AddressOf() );
		}

		asDWORD value = 0;
		asCDataType dt;
		if( scopeType && builder->GetEnumValueFromObjectType(scopeType, name.AddressOf(), dt, value) )
		{
			// scoped enum value found
			found = true;
		}
		else if( scope == "" && !engine->ep.requireEnumScope )
		{
			// look for the enum value with no namespace
			int e = builder->GetEnumValue(name.AddressOf(), dt, value);
			if( e )
			{
				found = true;
				if( e == 2 )
				{
					Error(TXT_FOUND_MULTIPLE_ENUM_VALUES, errNode);
				}
			}
		}

		if( found )
		{
			// an enum value was resolved
			ctx->type.SetConstantDW(dt, value);
		}
	}

	// The name doesn't match any variable
	if( !found )
	{
		// Give dummy value
		ctx->type.SetDummy();

		if( !isOptional )
		{
			// Prepend the scope to the name for the error message
			asCString ename;
			if( scope != "" && scope != "::" )
				ename = scope + "::";
			else
				ename = scope;
			ename += name;

			asCString str;
			str.Format(TXT_s_NOT_DECLARED, ename.AddressOf());
			Error(str.AddressOf(), errNode);

			// Declare the variable now so that it will not be reported again
			variables->DeclareVariable(name.AddressOf(), asCDataType::CreatePrimitive(ttInt, false), 0x7FFF, true);

			// Mark the variable as initialized so that the user will not be bother by it again
			sVariable *v = variables->GetVariable(name.AddressOf());
			asASSERT(v);
			if( v ) v->isInitialized = true;
		}

		// Return -1 to signal that the variable wasn't found
		return -1;
	}

	return 0;
}

int asCCompiler::CompileExpressionValue(asCScriptNode *node, asSExprContext *ctx)
{
	// Shouldn't receive any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	asCScriptNode *vnode = node->firstChild;
	ctx->exprNode = vnode;
	if( vnode->nodeType == snVariableAccess )
	{
		// Determine the scope resolution of the variable
		asCString scope = GetScopeFromNode(vnode);

		// Determine the name of the variable
		vnode = vnode->lastChild;
		asASSERT(vnode->nodeType == snIdentifier );
		asCString name(&script->code[vnode->tokenPos], vnode->tokenLength);

		return CompileVariableAccess(name, scope, ctx, node);
	}
	else if( vnode->nodeType == snConstant )
	{
		if( vnode->tokenType == ttIntConstant )
		{
			asCString value(&script->code[vnode->tokenPos], vnode->tokenLength);

			asQWORD val = asStringScanUInt64(value.AddressOf(), 10, 0);

			// Do we need 64 bits?
			if( val>>32 )
				ctx->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), val);
			else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), asDWORD(val));
		}
		else if( vnode->tokenType == ttBitsConstant )
		{
			asCString value(&script->code[vnode->tokenPos+2], vnode->tokenLength-2);

			// TODO: Check for overflow
			asQWORD val = asStringScanUInt64(value.AddressOf(), 16, 0);

			// Do we need 64 bits?
			if( val>>32 )
				ctx->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), val);
			else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), asDWORD(val));
		}
		else if( vnode->tokenType == ttFloatConstant )
		{
			asCString value(&script->code[vnode->tokenPos], vnode->tokenLength);

			// TODO: Check for overflow

			size_t numScanned;
			float v = float(asStringScanDouble(value.AddressOf(), &numScanned));
			ctx->type.SetConstantF(asCDataType::CreatePrimitive(ttFloat, true), v);
			asASSERT(numScanned == vnode->tokenLength - 1);
		}
		else if( vnode->tokenType == ttDoubleConstant )
		{
			asCString value(&script->code[vnode->tokenPos], vnode->tokenLength);

			// TODO: Check for overflow

			size_t numScanned;
			double v = asStringScanDouble(value.AddressOf(), &numScanned);
			ctx->type.SetConstantD(asCDataType::CreatePrimitive(ttDouble, true), v);
			asASSERT(numScanned == vnode->tokenLength);
		}
		else if( vnode->tokenType == ttTrue ||
			     vnode->tokenType == ttFalse )
		{
#if AS_SIZEOF_BOOL == 1
			ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), vnode->tokenType == ttTrue ? VALUE_OF_BOOLEAN_TRUE : 0);
#else
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), vnode->tokenType == ttTrue ? VALUE_OF_BOOLEAN_TRUE : 0);
#endif
		}
		else if( vnode->tokenType == ttStringConstant ||
			     vnode->tokenType == ttMultilineStringConstant ||
				 vnode->tokenType == ttHeredocStringConstant )
		{
			asCString str;
			asCScriptNode *snode = vnode->firstChild;
			if( script->code[snode->tokenPos] == '\'' && engine->ep.useCharacterLiterals )
			{
				// Treat the single quoted string as a single character literal
				str.Assign(&script->code[snode->tokenPos+1], snode->tokenLength-2);

				asDWORD val = 0;
				if( str.GetLength() && (unsigned char)str[0] > 127 && engine->ep.scanner == 1 )
				{
					// This is the start of a UTF8 encoded character. We need to decode it
					val = asStringDecodeUTF8(str.AddressOf(), 0);
					if( val == (asDWORD)-1 )
						Error(TXT_INVALID_CHAR_LITERAL, vnode);
				}
				else
				{
					val = ProcessStringConstant(str, snode);
					if( val == (asDWORD)-1 )
						Error(TXT_INVALID_CHAR_LITERAL, vnode);
				}

				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), val);
			}
			else
			{
				// Process the string constants
				while( snode )
				{
					asCString cat;
					if( snode->tokenType == ttStringConstant )
					{
						cat.Assign(&script->code[snode->tokenPos+1], snode->tokenLength-2);
						ProcessStringConstant(cat, snode);
					}
					else if( snode->tokenType == ttMultilineStringConstant )
					{
						if( !engine->ep.allowMultilineStrings )
							Error(TXT_MULTILINE_STRINGS_NOT_ALLOWED, snode);

						cat.Assign(&script->code[snode->tokenPos+1], snode->tokenLength-2);
						ProcessStringConstant(cat, snode);
					}
					else if( snode->tokenType == ttHeredocStringConstant )
					{
						cat.Assign(&script->code[snode->tokenPos+3], snode->tokenLength-6);
						ProcessHeredocStringConstant(cat, snode);
					}

					str += cat;

					snode = snode->next;
				}

				// Call the string factory function to create a string object
				asCScriptFunction *descr = engine->stringFactory;
				if( descr == 0 )
				{
					// Error
					Error(TXT_STRINGS_NOT_RECOGNIZED, vnode);

					// Give dummy value
					ctx->type.SetDummy();
					return -1;
				}
				else
				{
					// Register the constant string with the engine
					int id = engine->AddConstantString(str.AddressOf(), str.GetLength());
					ctx->bc.InstrWORD(asBC_STR, (asWORD)id);
					PerformFunctionCall(descr->id, ctx);
				}
			}
		}
		else if( vnode->tokenType == ttNull )
		{
#ifndef AS_64BIT_PTR
			ctx->bc.InstrDWORD(asBC_PshC4, 0);
#else
			ctx->bc.InstrQWORD(asBC_PshC8, 0);
#endif
			ctx->type.SetNullConstant();
		}
		else
			asASSERT(false);
	}
	else if( vnode->nodeType == snFunctionCall )
	{
		bool found = false;

		// Determine the scope resolution
		asCString scope = GetScopeFromNode(vnode);

		if( outFunc && outFunc->objectType && scope != "::" )
		{
			// TODO: funcdef: There may be a local variable of a function type with the same name

			// Check if a class method is being called
			asCScriptNode *nm = vnode->lastChild->prev;
			asCString name;
			name.Assign(&script->code[nm->tokenPos], nm->tokenLength);

			asCArray<int> funcs;

			// If we're compiling a constructor and the name of the function called
			// is 'super' then the base class' constructor is being called.
			// super cannot be called from another scope, i.e. must not be prefixed
			if( m_isConstructor && name == SUPER_TOKEN && nm->prev == 0 )
			{
				// Actually it is the base class' constructor that is being called,
				// but as we won't use the actual function ids here we can take the
				// object's own constructors and avoid the need to check if the
				// object actually derives from any other class
				funcs = outFunc->objectType->beh.constructors;

				// Must not allow calling constructors multiple times
				if( continueLabels.GetLength() > 0 )
				{
					// If a continue label is set we are in a loop
					Error(TXT_CANNOT_CALL_CONSTRUCTOR_IN_LOOPS, vnode);
				}
				else if( breakLabels.GetLength() > 0 )
				{
					// TODO: inheritance: Should eventually allow constructors in switch statements
					// If a break label is set we are either in a loop or a switch statements
					Error(TXT_CANNOT_CALL_CONSTRUCTOR_IN_SWITCH, vnode);
				}
				else if( m_isConstructorCalled )
				{
					Error(TXT_CANNOT_CALL_CONSTRUCTOR_TWICE, vnode);
				}
				m_isConstructorCalled = true;
			}
			else
				builder->GetObjectMethodDescriptions(name.AddressOf(), outFunc->objectType, funcs, false);

			if( funcs.GetLength() )
			{
				asCDataType dt = asCDataType::CreateObject(outFunc->objectType, false);

				// The object pointer is located at stack position 0
				ctx->bc.InstrSHORT(asBC_PSF, 0);
				ctx->type.SetVariable(dt, 0, false);
				ctx->type.dataType.MakeReference(true);

				// TODO: optimize: This adds a CHKREF. Is that really necessary?
				Dereference(ctx, true);

				CompileFunctionCall(vnode, ctx, outFunc->objectType, false, scope);
				found = true;
			}
		}

		if( !found )
			CompileFunctionCall(vnode, ctx, 0, false, scope);
	}
	else if( vnode->nodeType == snConstructCall )
	{
		CompileConstructCall(vnode, ctx);
	}
	else if( vnode->nodeType == snAssignment )
	{
		asSExprContext e(engine);
		int r = CompileAssignment(vnode, &e); 
		if( r < 0 ) 
		{
			ctx->type.SetDummy();
			return r;
		}
		MergeExprBytecodeAndType(ctx, &e);
	}
	else if( vnode->nodeType == snCast )
	{
		// Implement the cast operator
		CompileConversion(vnode, ctx);
	}
	else
		asASSERT(false);

	return 0;
}

asCString asCCompiler::GetScopeFromNode(asCScriptNode *node)
{
	asCString scope;
	asCScriptNode *sn = node->firstChild;
	if( sn->tokenType == ttScope )
	{
		// Global scope
		scope = "::";
		sn = sn->next;
	}
	else if( sn->next && sn->next->tokenType == ttScope )
	{
		scope.Assign(&script->code[sn->tokenPos], sn->tokenLength);
		sn = sn->next->next;
	}

	if( scope != "" )
	{
		// We don't support multiple levels of scope yet
		if( sn->next && sn->next->tokenType == ttScope )
		{
			Error(TXT_INVALID_SCOPE, sn->next);
		}
	}

	return scope;
}

asUINT asCCompiler::ProcessStringConstant(asCString &cstr, asCScriptNode *node, bool processEscapeSequences)
{
	int charLiteral = -1;

	// Process escape sequences
	asCArray<char> str((int)cstr.GetLength());

	for( asUINT n = 0; n < cstr.GetLength(); n++ )
	{
#ifdef AS_DOUBLEBYTE_CHARSET
		// Double-byte charset is only allowed for ASCII and not UTF16 encoded strings
		if( (cstr[n] & 0x80) && engine->ep.scanner == 0 && engine->ep.stringEncoding != 1 )
		{
			// This is the lead character of a double byte character
			// include the trail character without checking it's value.
			str.PushLast(cstr[n]);
			n++;
			str.PushLast(cstr[n]);
			continue;
		}
#endif

		asUINT val;

		if( processEscapeSequences && cstr[n] == '\\' )
		{
			++n;
			if( n == cstr.GetLength() )
			{
				if( charLiteral == -1 ) charLiteral = 0;
				return charLiteral;
			}

			// TODO: Consider deprecating use of hexadecimal escape sequences, 
			//       as they do not guarantee proper unicode sequences
			if( cstr[n] == 'x' || cstr[n] == 'X' )
			{
				++n;
				if( n == cstr.GetLength() ) break;

				val = 0;
				int c = engine->ep.stringEncoding == 1 ? 4 : 2;
				for( ; c > 0 && n < cstr.GetLength(); c--, n++ )
				{
					if( cstr[n] >= '0' && cstr[n] <= '9' )
						val = val*16 +  cstr[n] - '0';
					else if( cstr[n] >= 'a' && cstr[n] <= 'f' )
						val = val*16 + cstr[n] - 'a' + 10;
					else if( cstr[n] >= 'A' && cstr[n] <= 'F' )
						val = val*16 + cstr[n] - 'A' + 10;
					else
						break;
				}

				// Rewind one, since the loop will increment it again
				n--;

				// Hexadecimal escape sequences produce exact value, even if it is not proper unicode chars
				if( engine->ep.stringEncoding == 0 )
				{
					str.PushLast(val);
				}
				else
				{
#ifndef AS_BIG_ENDIAN
					str.PushLast(val);
					str.PushLast(val>>8);
#else
					str.PushLast(val>>8);
					str.PushLast(val);
#endif
				}
				if( charLiteral == -1 ) charLiteral = val;
				continue;
			}
			else if( cstr[n] == 'u' || cstr[n] == 'U' )
			{
				// \u expects 4 hex digits
				// \U expects 8 hex digits
				bool expect2 = cstr[n] == 'u';
				int c = expect2 ? 4 : 8;

				val = 0;

				for( ; c > 0; c-- )
				{
					++n;
					if( n == cstr.GetLength() ) break;

					if( cstr[n] >= '0' && cstr[n] <= '9' )
						val = val*16 + cstr[n] - '0';
					else if( cstr[n] >= 'a' && cstr[n] <= 'f' )
						val = val*16 + cstr[n] - 'a' + 10;
					else if( cstr[n] >= 'A' && cstr[n] <= 'F' )
						val = val*16 + cstr[n] - 'A' + 10;
					else
						break;
				}

				if( c != 0 )
				{
					// Give warning about invalid code point
					// TODO: Need code position for warning
					asCString msg;
					msg.Format(TXT_INVALID_UNICODE_FORMAT_EXPECTED_d, expect2 ? 4 : 8);
					Warning(msg.AddressOf(), node);
					continue;
				}
			}
			else
			{
				if( cstr[n] == '"' )
					val = '"';
				else if( cstr[n] == '\'' )
					val = '\'';
				else if( cstr[n] == 'n' )
					val = '\n';
				else if( cstr[n] == 'r' )
					val = '\r';
				else if( cstr[n] == 't' )
					val = '\t';
				else if( cstr[n] == '0' )
					val = '\0';
				else if( cstr[n] == '\\' )
					val = '\\';
				else
				{
					// Invalid escape sequence
					Warning(TXT_INVALID_ESCAPE_SEQUENCE, node);
					continue;
				}
			}
		}
		else
		{
			if( engine->ep.scanner == 1 && (cstr[n] & 0x80) )
			{
				unsigned int len;
				val = asStringDecodeUTF8(&cstr[n], &len);
				if( val == 0xFFFFFFFF || len < 0 )
				{
					// Incorrect UTF8 encoding. Use only the first byte
					// TODO: Need code position for warning
					Warning(TXT_INVALID_UNICODE_SEQUENCE_IN_SRC, node);
					val = (unsigned char)cstr[n];
				}
				else
					n += len-1;
			}
			else
				val = (unsigned char)cstr[n];
		}

		// Add the character to the final string
		char encodedValue[5];
		int len;
		if( engine->ep.scanner == 1 && engine->ep.stringEncoding == 0 )
		{
			// Convert to UTF8 encoded 
			len = asStringEncodeUTF8(val, encodedValue);
		}
		else if( engine->ep.stringEncoding == 1 )
		{
			// Convert to 16bit wide character string (even if the script is scanned as ASCII)
			len = asStringEncodeUTF16(val, encodedValue);
		}
		else
		{
			// Do not convert ASCII characters
			encodedValue[0] = val;
			len = 1;
		}

		if( len < 0 )
		{
			// Give warning about invalid code point
			// TODO: Need code position for warning
			Warning(TXT_INVALID_UNICODE_VALUE, node);
		}
		else
		{
			// Add the encoded value to the final string
			str.Concatenate(encodedValue, len);
			if( charLiteral == -1 ) charLiteral = val;
		}
	}

	cstr.Assign(str.AddressOf(), str.GetLength());
	return charLiteral;
}

void asCCompiler::ProcessHeredocStringConstant(asCString &str, asCScriptNode *node)
{
	// Remove first line if it only contains whitespace
	int start;
	for( start = 0; start < (int)str.GetLength(); start++ )
	{
		if( str[start] == '\n' )
		{
			// Remove the linebreak as well
			start++;
			break;
		}

		if( str[start] != ' '  &&
			str[start] != '\t' &&
			str[start] != '\r' )
		{
			// Don't remove anything
			start = 0;
			break;
		}
	}

	// Remove last line break and the line after that if it only contains whitespaces
	int end;
	for( end = (int)str.GetLength() - 1; end >= 0; end-- )
	{
		if( str[end] == '\n' )
			break;

		if( str[end] != ' '  &&
			str[end] != '\t' &&
			str[end] != '\r' )
		{
			// Don't remove anything
			end = (int)str.GetLength();
			break;
		}
	}

	if( end < 0 ) end = 0;

	asCString tmp;
	if( end > start ) 
		tmp.Assign(&str[start], end-start);

	ProcessStringConstant(tmp, node, false);

	str = tmp;
}

void asCCompiler::CompileConversion(asCScriptNode *node, asSExprContext *ctx)
{
	asSExprContext expr(engine);
	asCDataType to;
	bool anyErrors = false;
	EImplicitConv convType;
	if( node->nodeType == snConstructCall )
	{
		convType = asIC_EXPLICIT_VAL_CAST;

		// Verify that there is only one argument
		if( node->lastChild->firstChild == 0 ||
			node->lastChild->firstChild != node->lastChild->lastChild )
		{
			Error(TXT_ONLY_ONE_ARGUMENT_IN_CAST, node->lastChild);
			expr.type.SetDummy();
			anyErrors = true;
		}
		else
		{
			// Compile the expression
			int r = CompileAssignment(node->lastChild->firstChild, &expr);
			if( r < 0 )
				anyErrors = true;
		}

		// Determine the requested type
		to = builder->CreateDataTypeFromNode(node->firstChild, script);
		to.MakeReadOnly(true); // Default to const
		asASSERT(to.IsPrimitive());
	}
	else
	{
		convType = asIC_EXPLICIT_REF_CAST;

		// Compile the expression
		int r = CompileAssignment(node->lastChild, &expr);
		if( r < 0 )
			anyErrors = true;
		else
		{
			// Determine the requested type
			to = builder->CreateDataTypeFromNode(node->firstChild, script);
			to = builder->ModifyDataTypeFromNode(to, node->firstChild->next, script, 0, 0);

			// If the type support object handles, then use it
			if( to.SupportHandles() )
			{
				to.MakeHandle(true);
			}
			else if( !to.IsObjectHandle() )
			{
				// The cast<type> operator can only be used for reference casts
				Error(TXT_ILLEGAL_TARGET_TYPE_FOR_REF_CAST, node->firstChild);
				anyErrors = true;
			}
		}
	}

	if( anyErrors )
	{
		// Assume that the error can be fixed and allow the compilation to continue
		ctx->type.SetConstantDW(to, 0);
		return;
	}

	ProcessPropertyGetAccessor(&expr, node);

	// We don't want a reference
	if( expr.type.dataType.IsReference() )
	{
		if( expr.type.dataType.IsObject() )
			Dereference(&expr, true);
		else
			ConvertToVariable(&expr);
	}

	ImplicitConversion(&expr, to, node, convType);

	IsVariableInitialized(&expr.type, node);

	// If no type conversion is really tried ignore it
	if( to == expr.type.dataType )
	{
		// This will keep information about constant type
		MergeExprBytecode(ctx, &expr);
		ctx->type = expr.type;
		return;
	}

	if( to.IsEqualExceptConst(expr.type.dataType) && to.IsPrimitive() )
	{
		MergeExprBytecode(ctx, &expr);
		ctx->type = expr.type;
		ctx->type.dataType.MakeReadOnly(true);
		return;
	}

	// The implicit conversion already does most of the conversions permitted,
	// here we'll only treat those conversions that require an explicit cast.

	bool conversionOK = false;
	if( !expr.type.isConstant )
	{
		if( !expr.type.dataType.IsObject() )
			ConvertToTempVariable(&expr);

		if( to.IsObjectHandle() &&
			expr.type.dataType.IsObjectHandle() &&
			!(!to.IsHandleToConst() && expr.type.dataType.IsHandleToConst()) )
		{
			conversionOK = CompileRefCast(&expr, to, true, node);

			MergeExprBytecode(ctx, &expr);
			ctx->type = expr.type;
		}
	}

	if( conversionOK )
		return;

	// Conversion not available
	ctx->type.SetDummy();

	asCString strTo, strFrom;

	strTo = to.Format();
	strFrom = expr.type.dataType.Format();

	asCString msg;
	msg.Format(TXT_NO_CONVERSION_s_TO_s, strFrom.AddressOf(), strTo.AddressOf());

	Error(msg.AddressOf(), node);
}

void asCCompiler::AfterFunctionCall(int funcID, asCArray<asSExprContext*> &args, asSExprContext *ctx, bool deferAll)
{
	asCScriptFunction *descr = builder->GetFunctionDescription(funcID);

	// Parameters that are sent by reference should be assigned
	// to the evaluated expression if it is an lvalue

	// Evaluate the arguments from last to first
	int n = (int)descr->parameterTypes.GetLength() - 1;
	for( ; n >= 0; n-- )
	{
		if( (descr->parameterTypes[n].IsReference() && (descr->inOutFlags[n] & asTM_OUTREF)) ||
		    (descr->parameterTypes[n].IsObject() && deferAll) )
		{
			asASSERT( !(descr->parameterTypes[n].IsReference() && (descr->inOutFlags[n] == asTM_OUTREF)) || args[n]->origExpr );

			// For &inout, only store the argument if it is for a temporary variable
			if( engine->ep.allowUnsafeReferences ||
				descr->inOutFlags[n] != asTM_INOUTREF || args[n]->type.isTemporary )
			{
				// Store the argument for later processing
				asSDeferredParam outParam;
				outParam.argNode = args[n]->exprNode;
				outParam.argType = args[n]->type;
				outParam.argInOutFlags = descr->inOutFlags[n];
				outParam.origExpr = args[n]->origExpr;

				ctx->deferredParams.PushLast(outParam);
			}
		}
		else
		{
			// Release the temporary variable now
			ReleaseTemporaryVariable(args[n]->type, &ctx->bc);
		}

		// Move the argument's deferred expressions over to the final expression
		for( asUINT m = 0; m < args[n]->deferredParams.GetLength(); m++ )
		{
			ctx->deferredParams.PushLast(args[n]->deferredParams[m]);
			args[n]->deferredParams[m].origExpr = 0;
		}
		args[n]->deferredParams.SetLength(0);
	}
}

void asCCompiler::ProcessDeferredParams(asSExprContext *ctx)
{
	if( isProcessingDeferredParams ) return;

	isProcessingDeferredParams = true;

	for( asUINT n = 0; n < ctx->deferredParams.GetLength(); n++ )
	{
		asSDeferredParam outParam = ctx->deferredParams[n];
		if( outParam.argInOutFlags < asTM_OUTREF ) // &in, or not reference
		{
			// Just release the variable
			ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
		}
		else if( outParam.argInOutFlags == asTM_OUTREF )
		{
			asSExprContext *expr = outParam.origExpr;
			outParam.origExpr = 0;

			if( outParam.argType.dataType.IsObjectHandle() )
			{
				// Implicitly convert the value to a handle
				if( expr->type.dataType.IsObjectHandle() )
					expr->type.isExplicitHandle = true;
			}

			// Verify that the expression result in a lvalue, or a property accessor
			if( IsLValue(expr->type) || expr->property_get || expr->property_set )
			{
				asSExprContext rctx(engine);
				rctx.type = outParam.argType;
				if( rctx.type.dataType.IsPrimitive() )
					rctx.type.dataType.MakeReference(false);
				else
				{
					rctx.bc.InstrSHORT(asBC_PSF, outParam.argType.stackOffset);
					rctx.type.dataType.MakeReference(IsVariableOnHeap(outParam.argType.stackOffset));
					if( expr->type.isExplicitHandle )
						rctx.type.isExplicitHandle = true;
				}

				asSExprContext o(engine);
				DoAssignment(&o, expr, &rctx, outParam.argNode, outParam.argNode, ttAssignment, outParam.argNode);

				if( !o.type.dataType.IsPrimitive() ) o.bc.Pop(AS_PTR_SIZE);

				MergeExprBytecode(ctx, &o);
			}
			else
			{
				// We must still evaluate the expression
				MergeExprBytecode(ctx, expr);
				if( !expr->type.isConstant )
					ctx->bc.Pop(expr->type.dataType.GetSizeOnStackDWords());

				// Give a warning
				Warning(TXT_ARG_NOT_LVALUE, outParam.argNode);

				ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
			}

			ReleaseTemporaryVariable(expr->type, &ctx->bc);

			// Delete the original expression context
			asDELETE(expr,asSExprContext);
		}
		else // &inout
		{
			if( outParam.argType.isTemporary )
				ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
			else if( !outParam.argType.isVariable )
			{
				if( outParam.argType.dataType.IsObject() &&
					outParam.argType.dataType.GetBehaviour()->addref &&
					outParam.argType.dataType.GetBehaviour()->release )
				{
					// Release the object handle that was taken to guarantee the reference
					ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
				}
			}
		}
	}

	ctx->deferredParams.SetLength(0);
	isProcessingDeferredParams = false;
}


void asCCompiler::CompileConstructCall(asCScriptNode *node, asSExprContext *ctx)
{
	// The first node is a datatype node
	asCString name;
	asCTypeInfo tempObj;
	bool onHeap = true;
	asCArray<int> funcs;

	// It is possible that the name is really a constructor
	asCDataType dt;
	dt = builder->CreateDataTypeFromNode(node->firstChild, script);
	if( dt.IsPrimitive() )
	{
		// This is a cast to a primitive type
		CompileConversion(node, ctx);
		return;
	}

	if( globalExpression )
	{
		Error(TXT_FUNCTION_IN_GLOBAL_EXPR, node);

		// Output dummy code
		ctx->type.SetDummy();
		return;
	}

	// Compile the arguments
	asCArray<asSExprContext *> args;
	asCArray<asCTypeInfo> temporaryVariables;
	if( CompileArgumentList(node->lastChild, args) >= 0 )
	{
		// Check for a value cast behaviour
		if( args.GetLength() == 1 && args[0]->type.dataType.GetObjectType() )
		{
			asSExprContext conv(engine);
			conv.type = args[0]->type;
			ImplicitConversion(&conv, dt, node->lastChild, asIC_EXPLICIT_VAL_CAST, false);

			if( conv.type.dataType.IsEqualExceptRef(dt) )
			{
				ImplicitConversion(args[0], dt, node->lastChild, asIC_EXPLICIT_VAL_CAST);

				ctx->bc.AddCode(&args[0]->bc);
				ctx->type = args[0]->type;

				asDELETE(args[0],asSExprContext);

				return;
			}
		}

		// Check for possible constructor/factory
		name = dt.Format();

		asSTypeBehaviour *beh = dt.GetBehaviour();

		if( !(dt.GetObjectType()->flags & asOBJ_REF) )
		{
			funcs = beh->constructors;

			// Value types and script types are allocated through the constructor
			tempObj.dataType = dt;
			tempObj.stackOffset = (short)AllocateVariable(dt, true);
			tempObj.dataType.MakeReference(true);
			tempObj.isTemporary = true;
			tempObj.isVariable = true;

			onHeap = IsVariableOnHeap(tempObj.stackOffset);

			// Push the address of the object on the stack
			if( onHeap )
				ctx->bc.InstrSHORT(asBC_VAR, tempObj.stackOffset);
		}
		else
		{
			funcs = beh->factories;
		}

		// Special case: Allow calling func(void) with a void expression.
		if( args.GetLength() == 1 && args[0]->type.dataType == asCDataType::CreatePrimitive(ttVoid, false) )
		{
			// Evaluate the expression before the function call
			MergeExprBytecode(ctx, args[0]);
			asDELETE(args[0],asSExprContext);
			args.SetLength(0);
		}

		// Special case: If this is an object constructor and there are no arguments use the default constructor.
		// If none has been registered, just allocate the variable and push it on the stack.
		if( args.GetLength() == 0 )
		{
			asSTypeBehaviour *beh = tempObj.dataType.GetBehaviour();
			if( beh && beh->construct == 0 && !(dt.GetObjectType()->flags & asOBJ_REF) )
			{
				// Call the default constructor
				ctx->type = tempObj;

				if( onHeap )
				{
					asASSERT(ctx->bc.GetLastInstr() == asBC_VAR);
					ctx->bc.RemoveLastInstr();
				}

				CallDefaultConstructor(tempObj.dataType, tempObj.stackOffset, IsVariableOnHeap(tempObj.stackOffset), &ctx->bc, node);

				// Push the reference on the stack
				ctx->bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);
				return;
			}
		}

		MatchFunctions(funcs, args, node, name.AddressOf(), NULL, false);

		if( funcs.GetLength() != 1 )
		{
			// The error was reported by MatchFunctions()

			// Dummy value
			ctx->type.SetDummy();
		}
		else
		{
			asCByteCode objBC(engine);

			PrepareFunctionCall(funcs[0], &ctx->bc, args);

			MoveArgsToStack(funcs[0], &ctx->bc, args, false);

			if( !(dt.GetObjectType()->flags & asOBJ_REF) )
			{
				// If the object is allocated on the stack, then call the constructor as a normal function
				if( onHeap )
				{
					int offset = 0;
					asCScriptFunction *descr = builder->GetFunctionDescription(funcs[0]);
					for( asUINT n = 0; n < args.GetLength(); n++ )
						offset += descr->parameterTypes[n].GetSizeOnStackDWords();

					ctx->bc.InstrWORD(asBC_GETREF, (asWORD)offset);
				}
				else
					ctx->bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);

				PerformFunctionCall(funcs[0], ctx, onHeap, &args, tempObj.dataType.GetObjectType());

				// The constructor doesn't return anything,
				// so we have to manually inform the type of
				// the return value
				ctx->type = tempObj;
				if( !onHeap )
					ctx->type.dataType.MakeReference(false);

				// Push the address of the object on the stack again
				ctx->bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);
			}
			else
			{
				// Call the factory to create the reference type
				PerformFunctionCall(funcs[0], ctx, false, &args);
			}
		}
	}
	else
	{
		// Failed to compile the argument list, set the result to the dummy type
		ctx->type.SetDummy();
	}

	// Cleanup
	for( asUINT n = 0; n < args.GetLength(); n++ )
		if( args[n] )
		{
			asDELETE(args[n],asSExprContext);
		}
}


void asCCompiler::CompileFunctionCall(asCScriptNode *node, asSExprContext *ctx, asCObjectType *objectType, bool objIsConst, const asCString &scope)
{
	asCString name;
	asCTypeInfo tempObj;
	asCArray<int> funcs;
	int r = -1;

	asCScriptNode *nm = node->lastChild->prev;
	name.Assign(&script->code[nm->tokenPos], nm->tokenLength);

	// TODO: funcdef: First check for a local variable of a function type
	//                Must not allow function names, nor global variables to be returned in this instance
	asSExprContext funcPtr(engine);
	if( objectType == 0 )
		r = CompileVariableAccess(name, scope, &funcPtr, node, true, true, false);
	if( r < 0 )
	{
		if( objectType )
		{
			// If we're compiling a constructor and the name of the function is super then
			// the constructor of the base class is being called.
			// super cannot be prefixed with a scope operator
			if( m_isConstructor && name == SUPER_TOKEN && nm->prev == 0 )
			{
				// If the class is not derived from anyone else, calling super should give an error
				if( objectType->derivedFrom )
					funcs = objectType->derivedFrom->beh.constructors;
			}
			else
				builder->GetObjectMethodDescriptions(name.AddressOf(), objectType, funcs, objIsConst, scope);

			// It is still possible that there is a class member of a function type
			if( funcs.GetLength() == 0 )
				CompileVariableAccess(name, scope, &funcPtr, node, true, true, objectType);
		}
		else
		{
			builder->GetFunctionDescriptions(name.AddressOf(), funcs);

			// TODO: funcdef: It is still possible that there is a global variable of a function type
		}
	}

	if( funcs.GetLength() == 0 && funcPtr.type.dataType.GetFuncDef() )
	{
		funcs.PushLast(funcPtr.type.dataType.GetFuncDef()->id);
	}

	if( globalExpression )
	{
		Error(TXT_FUNCTION_IN_GLOBAL_EXPR, node);

		// Output dummy code
		ctx->type.SetDummy();
		return;
	}

	// Compile the arguments
	asCArray<asSExprContext *> args;
	asCArray<asCTypeInfo> temporaryVariables;

	if( CompileArgumentList(node->lastChild, args) >= 0 )
	{
		// Special case: Allow calling func(void) with a void expression.
		if( args.GetLength() == 1 && args[0]->type.dataType == asCDataType::CreatePrimitive(ttVoid, false) )
		{
			// Evaluate the expression before the function call
			MergeExprBytecode(ctx, args[0]);
			asDELETE(args[0],asSExprContext);
			args.SetLength(0);
		}

		MatchFunctions(funcs, args, node, name.AddressOf(), objectType, objIsConst, false, true, scope);

		if( funcs.GetLength() != 1 )
		{
			// The error was reported by MatchFunctions()

			// Dummy value
			ctx->type.SetDummy();
		}
		else
		{
			// TODO: funcdef: Do we have to make sure the handle is stored in a temporary variable, or
			//                is it enough to make sure it is in a local variable? 

			// For function pointer we must guarantee that the function is safe, i.e.
			// by first storing the function pointer in a local variable (if it isn't already in one)
			if( (funcs[0] & 0xFFFF0000) == 0 && engine->scriptFunctions[funcs[0]]->funcType == asFUNC_FUNCDEF )
			{
				if( objectType )
				{
					Dereference(ctx, true); // Dereference the object pointer to access the member

					// The actual function should be called as if a global function
					objectType = 0;
				}

				Dereference(&funcPtr, true);
				ConvertToVariable(&funcPtr);
				ctx->bc.AddCode(&funcPtr.bc);
				if( !funcPtr.type.isTemporary )
					ctx->bc.Pop(AS_PTR_SIZE);
			}

			MakeFunctionCall(ctx, funcs[0], objectType, args, node, false, 0, funcPtr.type.stackOffset);

			// If the function pointer was copied to a local variable for the call, then
			// release it again (temporary local variable)
			if( (funcs[0] & 0xFFFF0000) == 0 && engine->scriptFunctions[funcs[0]]->funcType == asFUNC_FUNCDEF )
			{
				ReleaseTemporaryVariable(funcPtr.type, &ctx->bc);
			}
		}
	}
	else
	{
		// Failed to compile the argument list, set the dummy type and continue compilation
		ctx->type.SetDummy();
	}

	// Cleanup
	for( asUINT n = 0; n < args.GetLength(); n++ )
		if( args[n] )
		{
			asDELETE(args[n],asSExprContext);
		}
}

int asCCompiler::CompileExpressionPreOp(asCScriptNode *node, asSExprContext *ctx)
{
	int op = node->tokenType;

	IsVariableInitialized(&ctx->type, node);

	if( op == ttHandle )
	{
		// Verify that the type allow its handle to be taken
		if( ctx->type.isExplicitHandle || !ctx->type.dataType.IsObject() || !ctx->type.dataType.GetObjectType()->beh.addref || !ctx->type.dataType.GetObjectType()->beh.release )
		{
			Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, node);
			return -1;
		}

		// Objects that are not local variables are not references
		if( !ctx->type.dataType.IsReference() && !(ctx->type.dataType.IsObject() && !ctx->type.isVariable) )
		{
			Error(TXT_NOT_VALID_REFERENCE, node);
			return -1;
		}

		// If this is really an object then the handle created is a const handle
		bool makeConst = !ctx->type.dataType.IsObjectHandle();

		// Mark the type as an object handle
		ctx->type.dataType.MakeHandle(true);
		ctx->type.isExplicitHandle = true;
		if( makeConst )
			ctx->type.dataType.MakeReadOnly(true);
	}
	else if( (op == ttMinus || op == ttBitNot || op == ttInc || op == ttDec) && ctx->type.dataType.IsObject() )
	{
		// Look for the appropriate method
		const char *opName = 0;
		switch( op )
		{
		case ttMinus:  opName = "opNeg";    break;
		case ttBitNot: opName = "opCom";    break;
		case ttInc:    opName = "opPreInc"; break;
		case ttDec:    opName = "opPreDec"; break;
		}

		if( opName )
		{
			// TODO: Should convert this to something similar to CompileOverloadedDualOperator2
			ProcessPropertyGetAccessor(ctx, node);

			// Is it a const value?
			bool isConst = false;
			if( ctx->type.dataType.IsObjectHandle() )
				isConst = ctx->type.dataType.IsHandleToConst();
			else
				isConst = ctx->type.dataType.IsReadOnly();

			// TODO: If the value isn't const, then first try to find the non const method, and if not found try to find the const method

			// Find the correct method
			asCArray<int> funcs;
			asCObjectType *ot = ctx->type.dataType.GetObjectType();
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
				if( func->name == opName &&
					func->parameterTypes.GetLength() == 0 &&
					(!isConst || func->isReadOnly) )
				{
					funcs.PushLast(func->id);
				}
			}

			// Did we find the method?
			if( funcs.GetLength() == 1 )
			{
				asCTypeInfo objType = ctx->type;
				asCArray<asSExprContext *> args;
				MakeFunctionCall(ctx, funcs[0], objType.dataType.GetObjectType(), args, node);
				ReleaseTemporaryVariable(objType, &ctx->bc);
				return 0;
			}
			else if( funcs.GetLength() == 0 )
			{
				asCString str;
				str = asCString(opName) + "()";
				if( isConst )
					str += " const";
				str.Format(TXT_FUNCTION_s_NOT_FOUND, str.AddressOf());
				Error(str.AddressOf(), node);
				ctx->type.SetDummy();
				return -1;
			}
			else if( funcs.GetLength() > 1 )
			{
				Error(TXT_MORE_THAN_ONE_MATCHING_OP, node);
				PrintMatchingFuncs(funcs, node);

				ctx->type.SetDummy();
				return -1;
			}
		}
	}
	else if( op == ttPlus || op == ttMinus )
	{
		ProcessPropertyGetAccessor(ctx, node);

		asCDataType to = ctx->type.dataType;

		// TODO: The case -2147483648 gives an unecessary warning of changed sign for implicit conversion

		if( ctx->type.dataType.IsUnsignedType() || ctx->type.dataType.IsEnumType() )
		{
			if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
				to = asCDataType::CreatePrimitive(ttInt8, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 2 )
				to = asCDataType::CreatePrimitive(ttInt16, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 4 )
				to = asCDataType::CreatePrimitive(ttInt, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 8 )
				to = asCDataType::CreatePrimitive(ttInt64, false);
			else
			{
				Error(TXT_INVALID_TYPE, node);
				return -1;
			}
		}

		if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);
		ImplicitConversion(ctx, to, node, asIC_IMPLICIT_CONV);

		if( !ctx->type.isConstant )
		{
			ConvertToTempVariable(ctx);

			if( op == ttMinus )
			{
				if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
					ctx->bc.InstrSHORT(asBC_NEGi, ctx->type.stackOffset);
				else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
					ctx->bc.InstrSHORT(asBC_NEGi64, ctx->type.stackOffset);
				else if( ctx->type.dataType.IsFloatType() )
					ctx->bc.InstrSHORT(asBC_NEGf, ctx->type.stackOffset);
				else if( ctx->type.dataType.IsDoubleType() )
					ctx->bc.InstrSHORT(asBC_NEGd, ctx->type.stackOffset);
				else
				{
					Error(TXT_ILLEGAL_OPERATION, node);
					return -1;
				}

				return 0;
			}
		}
		else
		{
			if( op == ttMinus )
			{
				if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
					ctx->type.intValue = -ctx->type.intValue;
				else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
					ctx->type.qwordValue = -(asINT64)ctx->type.qwordValue;
				else if( ctx->type.dataType.IsFloatType() )
					ctx->type.floatValue = -ctx->type.floatValue;
				else if( ctx->type.dataType.IsDoubleType() )
					ctx->type.doubleValue = -ctx->type.doubleValue;
				else
				{
					Error(TXT_ILLEGAL_OPERATION, node);
					return -1;
				}

				return 0;
			}
		}

		if( op == ttPlus )
		{
			if( !ctx->type.dataType.IsIntegerType() &&
				!ctx->type.dataType.IsFloatType() &&
				!ctx->type.dataType.IsDoubleType() )
			{
				Error(TXT_ILLEGAL_OPERATION, node);
				return -1;
			}
		}
	}
	else if( op == ttNot )
	{
		if( ctx->type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		{
			if( ctx->type.isConstant )
			{
				ctx->type.dwordValue = (ctx->type.dwordValue == 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
				return 0;
			}

			ProcessPropertyGetAccessor(ctx, node);

			ConvertToTempVariable(ctx);

			ctx->bc.InstrSHORT(asBC_NOT, ctx->type.stackOffset);
		}
		else
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			return -1;
		}
	}
	else if( op == ttBitNot )
	{
		ProcessPropertyGetAccessor(ctx, node);

		asCDataType to = ctx->type.dataType;

		if( ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsEnumType() )
		{
			if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
				to = asCDataType::CreatePrimitive(ttUInt8, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 2 )
				to = asCDataType::CreatePrimitive(ttUInt16, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 4 )
				to = asCDataType::CreatePrimitive(ttUInt, false);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 8 )
				to = asCDataType::CreatePrimitive(ttUInt64, false);
			else
			{
				Error(TXT_INVALID_TYPE, node);
				return -1;
			}
		}

		if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);
		ImplicitConversion(ctx, to, node, asIC_IMPLICIT_CONV);

		if( ctx->type.dataType.IsUnsignedType() )
		{
			if( ctx->type.isConstant )
			{
				ctx->type.qwordValue = ~ctx->type.qwordValue;
				return 0;
			}

			ConvertToTempVariable(ctx);
			if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				ctx->bc.InstrSHORT(asBC_BNOT, ctx->type.stackOffset);
			else
				ctx->bc.InstrSHORT(asBC_BNOT64, ctx->type.stackOffset);
		}
		else
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			return -1;
		}
	}
	else if( op == ttInc || op == ttDec )
	{
		// Need a reference to the primitive that will be updated
		// The result of this expression is the same reference as before
		if( globalExpression )
		{
			Error(TXT_INC_OP_IN_GLOBAL_EXPR, node);
			return -1;
		}

		// Make sure the reference isn't a temporary variable
		if( ctx->type.isTemporary )
		{
			Error(TXT_REF_IS_TEMP, node);
			return -1;
		}
		if( ctx->type.dataType.IsReadOnly() )
		{
			Error(TXT_REF_IS_READ_ONLY, node);
			return -1;
		}
		if( ctx->property_get || ctx->property_set )
		{
			Error(TXT_INVALID_REF_PROP_ACCESS, node);
			return -1;
		}

		if( ctx->type.isVariable && !ctx->type.dataType.IsReference() )
			ConvertToReference(ctx);
		else if( !ctx->type.dataType.IsReference() )
		{
			Error(TXT_NOT_VALID_REFERENCE, node);
			return -1;
		}

		if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt64, false)) ||
			ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt64, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCi64);
			else
				ctx->bc.Instr(asBC_DECi64);
		}
		else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt, false)) ||
			ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCi);
			else
				ctx->bc.Instr(asBC_DECi);
		}
		else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt16, false)) ||
			     ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt16, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCi16);
			else
				ctx->bc.Instr(asBC_DECi16);
		}
		else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt8, false)) ||
			     ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt8, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCi8);
			else
				ctx->bc.Instr(asBC_DECi8);
		}
		else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttFloat, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCf);
			else
				ctx->bc.Instr(asBC_DECf);
		}
		else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttDouble, false)) )
		{
			if( op == ttInc )
				ctx->bc.Instr(asBC_INCd);
			else
				ctx->bc.Instr(asBC_DECd);
		}
		else
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			return -1;
		}
	}
	else
	{
		// Unknown operator
		asASSERT(false);
		return -1;
	}

	return 0;
}

void asCCompiler::ConvertToReference(asSExprContext *ctx)
{
	if( ctx->type.isVariable && !ctx->type.dataType.IsReference() )
	{
		ctx->bc.InstrSHORT(asBC_LDV, ctx->type.stackOffset);
		ctx->type.dataType.MakeReference(true);
		ctx->type.SetVariable(ctx->type.dataType, ctx->type.stackOffset, ctx->type.isTemporary);
	}
}

int asCCompiler::FindPropertyAccessor(const asCString &name, asSExprContext *ctx, asCScriptNode *node)
{
	return FindPropertyAccessor(name, ctx, 0, node);
}

int asCCompiler::FindPropertyAccessor(const asCString &name, asSExprContext *ctx, asSExprContext *arg, asCScriptNode *node)
{
	if( engine->ep.propertyAccessorMode == 0 )
	{
		// Property accessors have been disabled by the application
		return 0;
	}

	int getId = 0, setId = 0;
	asCString getName = "get_" + name;
	asCString setName = "set_" + name;
	asCArray<int> multipleGetFuncs, multipleSetFuncs;

	if( ctx->type.dataType.IsObject() )
	{
		// Check if the object has any methods with the property name prefixed by get_ or set_
		asCObjectType *ot = ctx->type.dataType.GetObjectType();
		for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
		{
			asCScriptFunction *f = engine->scriptFunctions[ot->methods[n]];
			// TODO: The type of the parameter should match the argument (unless the arg is a dummy)
			if( f->name == getName && f->parameterTypes.GetLength() == (arg?1:0) )
			{
				if( getId == 0 )
					getId = ot->methods[n];
				else
				{
					if( multipleGetFuncs.GetLength() == 0 )
						multipleGetFuncs.PushLast(getId);

					multipleGetFuncs.PushLast(ot->methods[n]);
				}
			}
			// TODO: getset: If the parameter is a reference, it must not be an out reference. Should we allow inout ref?
			if( f->name == setName && f->parameterTypes.GetLength() == (arg?2:1) )
			{
				if( setId == 0 )
					setId = ot->methods[n];
				else
				{
					if( multipleSetFuncs.GetLength() == 0 )
						multipleSetFuncs.PushLast(setId);

					multipleSetFuncs.PushLast(ot->methods[n]);
				}
			}
		}
	}
	else
	{
		// Look for appropriate global functions. 
		asCArray<int> funcs;
		asUINT n;
		builder->GetFunctionDescriptions(getName.AddressOf(), funcs);
		for( n = 0; n < funcs.GetLength(); n++ )
		{
			asCScriptFunction *f = engine->scriptFunctions[funcs[n]];
			// TODO: The type of the parameter should match the argument (unless the arg is a dummy)
			if( f->parameterTypes.GetLength() == (arg?1:0) )
			{
				if( getId == 0 )
					getId = funcs[n];
				else
				{
					if( multipleGetFuncs.GetLength() == 0 )
						multipleGetFuncs.PushLast(getId);

					multipleGetFuncs.PushLast(funcs[n]);
				}
			}
		}

		funcs.SetLength(0);
		builder->GetFunctionDescriptions(setName.AddressOf(), funcs);
		for( n = 0; n < funcs.GetLength(); n++ )
		{
			asCScriptFunction *f = engine->scriptFunctions[funcs[n]];
			// TODO: getset: If the parameter is a reference, it must not be an out reference. Should we allow inout ref?
			if( f->parameterTypes.GetLength() == (arg?2:1) )
			{
				if( setId == 0 )
					setId = funcs[n];
				else
				{
					if( multipleSetFuncs.GetLength() == 0 )
						multipleSetFuncs.PushLast(getId);

					multipleSetFuncs.PushLast(funcs[n]);
				}
			}
		}
	}

	// Check for multiple matches
	if( multipleGetFuncs.GetLength() > 0 )
	{
		asCString str;
		str.Format(TXT_MULTIPLE_PROP_GET_ACCESSOR_FOR_s, name.AddressOf());
		Error(str.AddressOf(), node);

		PrintMatchingFuncs(multipleGetFuncs, node);

		return -1;
	}

	if( multipleSetFuncs.GetLength() > 0 )
	{
		asCString str;
		str.Format(TXT_MULTIPLE_PROP_SET_ACCESSOR_FOR_s, name.AddressOf());
		Error(str.AddressOf(), node);

		PrintMatchingFuncs(multipleSetFuncs, node);

		return -1;
	}

	// Check for type compatibility between get and set accessor
	if( getId && setId )
	{
		asCScriptFunction *getFunc = engine->scriptFunctions[getId];
		asCScriptFunction *setFunc = engine->scriptFunctions[setId];

		// It is permitted for a getter to return a handle and the setter to take a reference
		int idx = (arg?1:0);
		if( !getFunc->returnType.IsEqualExceptRefAndConst(setFunc->parameterTypes[idx]) &&
			!((getFunc->returnType.IsObjectHandle() && !setFunc->parameterTypes[idx].IsObjectHandle()) &&
			  (getFunc->returnType.GetObjectType() == setFunc->parameterTypes[idx].GetObjectType())) )
		{
			asCString str;
			str.Format(TXT_GET_SET_ACCESSOR_TYPE_MISMATCH_FOR_s, name.AddressOf());
			Error(str.AddressOf(), node);

			asCArray<int> funcs;
			funcs.PushLast(getId);
			funcs.PushLast(setId);

			PrintMatchingFuncs(funcs, node);

			return -1;
		}
	}

	// Check if we are within one of the accessors
	int realGetId = getId;
	int realSetId = setId;
	if( outFunc->objectType )
	{
		// The property accessors would be virtual functions, so we need to find the real implementation
		asCScriptFunction *getFunc = getId ? engine->scriptFunctions[getId] : 0;
		if( getFunc &&
			getFunc->funcType == asFUNC_VIRTUAL && 
			outFunc->objectType->DerivesFrom(getFunc->objectType) )
			realGetId = outFunc->objectType->virtualFunctionTable[getFunc->vfTableIdx]->id;
		asCScriptFunction *setFunc = setId ? engine->scriptFunctions[setId] : 0;
		if( setFunc &&
			setFunc->funcType == asFUNC_VIRTUAL &&
			outFunc->objectType->DerivesFrom(setFunc->objectType) )
			realSetId = outFunc->objectType->virtualFunctionTable[setFunc->vfTableIdx]->id;
	}

	if( (realGetId && realGetId == outFunc->id) ||
		(realSetId && realSetId == outFunc->id) )
	{
		// Avoid recursive call, by not treating this as a property accessor call.
		// This will also allow having the real property with the same name as the accessors.
		getId = 0;
		setId = 0;
	}

	// Check if the application has disabled script written property accessors
	if( engine->ep.propertyAccessorMode == 1 )
	{
		if( getId && engine->scriptFunctions[getId]->funcType != asFUNC_SYSTEM )
		  getId = 0;
		if( setId && engine->scriptFunctions[setId]->funcType != asFUNC_SYSTEM )
		  setId = 0;
	}

	if( getId || setId )
	{
		// Property accessors were found, but we don't know which is to be used yet, so 
		// we just prepare the bytecode for the method call, and then store the function ids
		// so that the right one can be used when we get there.
		ctx->property_get = getId;
		ctx->property_set = setId;

		if( ctx->type.dataType.IsObject() )
		{
			// If the object is read-only then we need to remember that
			if( (!ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsReadOnly()) ||
				(ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsHandleToConst()) )
				ctx->property_const = true;
			else
				ctx->property_const = false;

			// If the object is a handle then we need to remember that
			ctx->property_handle = ctx->type.dataType.IsObjectHandle();
			ctx->property_ref    = ctx->type.dataType.IsReference();
		}

		// The setter's parameter type is used as the property type,
		// unless only the getter is available	
		asCDataType dt;
		if( setId )
			dt = engine->scriptFunctions[setId]->parameterTypes[(arg?1:0)];
		else
			dt = engine->scriptFunctions[getId]->returnType;

		// Just change the type, the context must still maintain information 
		// about previous variable offset and the indicator of temporary variable.
		int offset = ctx->type.stackOffset;
		bool isTemp = ctx->type.isTemporary;
		ctx->type.Set(dt);
		ctx->type.stackOffset = offset;
		ctx->type.isTemporary = isTemp;
		ctx->exprNode = node;

		// Store the argument for later use
		if( arg )
		{
			ctx->property_arg = asNEW(asSExprContext)(engine);
			MergeExprBytecodeAndType(ctx->property_arg, arg);
		}

		return 1;
	}

	// No accessor was found
	return 0;
}

int asCCompiler::ProcessPropertySetAccessor(asSExprContext *ctx, asSExprContext *arg, asCScriptNode *node)
{
	// TODO: A lot of this code is similar to ProcessPropertyGetAccessor. Can we unify them?

	if( !ctx->property_set )
	{
		Error(TXT_PROPERTY_HAS_NO_SET_ACCESSOR, node);
		return -1;
	}

	asCTypeInfo objType = ctx->type;
	asCScriptFunction *func = engine->scriptFunctions[ctx->property_set];

	// Make sure the arg match the property
	asCArray<int> funcs;
	funcs.PushLast(ctx->property_set);
	asCArray<asSExprContext *> args;
	if( ctx->property_arg )
		args.PushLast(ctx->property_arg);
	args.PushLast(arg);
	MatchFunctions(funcs, args, node, func->GetName(), func->objectType, ctx->property_const);
	if( funcs.GetLength() == 0 )
	{
		// MatchFunctions already reported the error
		if( ctx->property_arg )
		{
			asDELETE(ctx->property_arg, asSExprContext);
			ctx->property_arg = 0;
		}
		return -1;
	}

	if( func->objectType )
	{
		// Setup the context with the original type so the method call gets built correctly
		ctx->type.dataType = asCDataType::CreateObject(func->objectType, ctx->property_const);
		if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
		if( ctx->property_ref )	ctx->type.dataType.MakeReference(true);

		// Don't allow the call if the object is read-only and the property accessor is not const
		if( ctx->property_const && !func->isReadOnly )
		{
			Error(TXT_NON_CONST_METHOD_ON_CONST_OBJ, node);
			asCArray<int> funcs;
			funcs.PushLast(ctx->property_set);
			PrintMatchingFuncs(funcs, node);
		}
	}

	// Call the accessor
	MakeFunctionCall(ctx, ctx->property_set, func->objectType, args, node);

	if( func->objectType )
	{
		// TODO: This is from CompileExpressionPostOp, can we unify the code?
		if( objType.isTemporary &&
			ctx->type.dataType.IsReference() &&
			!ctx->type.isVariable ) // If the resulting type is a variable, then the reference is not a member
		{
			// Remember the original object's variable, so that it can be released
			// later on when the reference to its member goes out of scope
			ctx->type.isTemporary = true;
			ctx->type.stackOffset = objType.stackOffset;
		}
		else
		{
			// As the method didn't return a reference to a member
			// we can safely release the original object now
			ReleaseTemporaryVariable(objType, &ctx->bc);
		}
	}

	ctx->property_get = 0;
	ctx->property_set = 0;
	if( ctx->property_arg )
	{
		asDELETE(ctx->property_arg, asSExprContext);
		ctx->property_arg = 0;
	}

	return 0;
}

void asCCompiler::ProcessPropertyGetAccessor(asSExprContext *ctx, asCScriptNode *node)
{
	// If no property accessor has been prepared then don't do anything
	if( !ctx->property_get && !ctx->property_set )
		return;

	if( !ctx->property_get )
	{
		// Raise error on missing accessor
		Error(TXT_PROPERTY_HAS_NO_GET_ACCESSOR, node);
		ctx->type.SetDummy();
		return;
	}

	asCTypeInfo objType = ctx->type;
	asCScriptFunction *func = engine->scriptFunctions[ctx->property_get];

	// Make sure the arg match the property
	asCArray<int> funcs;
	funcs.PushLast(ctx->property_get);
	asCArray<asSExprContext *> args;
	if( ctx->property_arg )
		args.PushLast(ctx->property_arg);
	MatchFunctions(funcs, args, node, func->GetName(), func->objectType, ctx->property_const);
	if( funcs.GetLength() == 0 )
	{
		// MatchFunctions already reported the error
		if( ctx->property_arg )
		{
			asDELETE(ctx->property_arg, asSExprContext);
			ctx->property_arg = 0;
		}
		ctx->type.SetDummy();
		return;
	}

	if( func->objectType )
	{
		// Setup the context with the original type so the method call gets built correctly
		ctx->type.dataType = asCDataType::CreateObject(func->objectType, ctx->property_const);
		if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
		if( ctx->property_ref )	ctx->type.dataType.MakeReference(true);

		// Don't allow the call if the object is read-only and the property accessor is not const
		if( ctx->property_const && !func->isReadOnly )
		{
			Error(TXT_NON_CONST_METHOD_ON_CONST_OBJ, node);
			asCArray<int> funcs;
			funcs.PushLast(ctx->property_get);
			PrintMatchingFuncs(funcs, node);
		}
	}

	// Call the accessor
	MakeFunctionCall(ctx, ctx->property_get, func->objectType, args, node);

	if( func->objectType )
	{
		// TODO: This is from CompileExpressionPostOp, can we unify the code?
		if( objType.isTemporary &&
			ctx->type.dataType.IsReference() &&
			!ctx->type.isVariable ) // If the resulting type is a variable, then the reference is not a member
		{
			// Remember the original object's variable, so that it can be released
			// later on when the reference to its member goes out of scope
			ctx->type.isTemporary = true;
			ctx->type.stackOffset = objType.stackOffset;
		}
		else
		{
			// As the method didn't return a reference to a member
			// we can safely release the original object now
			ReleaseTemporaryVariable(objType, &ctx->bc);
		}
	}

	ctx->property_get = 0;
	ctx->property_set = 0;
	if( ctx->property_arg )
	{
		asDELETE(ctx->property_arg, asSExprContext);
		ctx->property_arg = 0;
	}
}

int asCCompiler::CompileExpressionPostOp(asCScriptNode *node, asSExprContext *ctx)
{
	int op = node->tokenType;

	// Check if the variable is initialized (if it indeed is a variable)
	IsVariableInitialized(&ctx->type, node);

	if( (op == ttInc || op == ttDec) && ctx->type.dataType.IsObject() )
	{
		const char *opName = 0;
		switch( op )
		{
		case ttInc:    opName = "opPostInc"; break;
		case ttDec:    opName = "opPostDec"; break;
		}

		if( opName )
		{
			// TODO: Should convert this to something similar to CompileOverloadedDualOperator2
			ProcessPropertyGetAccessor(ctx, node);

			// Is it a const value?
			bool isConst = false;
			if( ctx->type.dataType.IsObjectHandle() )
				isConst = ctx->type.dataType.IsHandleToConst();
			else
				isConst = ctx->type.dataType.IsReadOnly();

			// TODO: If the value isn't const, then first try to find the non const method, and if not found try to find the const method

			// Find the correct method
			asCArray<int> funcs;
			asCObjectType *ot = ctx->type.dataType.GetObjectType();
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
				if( func->name == opName &&
					func->parameterTypes.GetLength() == 0 &&
					(!isConst || func->isReadOnly) )
				{
					funcs.PushLast(func->id);
				}
			}

			// Did we find the method?
			if( funcs.GetLength() == 1 )
			{
				asCTypeInfo objType = ctx->type;
				asCArray<asSExprContext *> args;
				MakeFunctionCall(ctx, funcs[0], objType.dataType.GetObjectType(), args, node);
				ReleaseTemporaryVariable(objType, &ctx->bc);
				return 0;
			}
			else if( funcs.GetLength() == 0 )
			{
				asCString str;
				str = asCString(opName) + "()";
				if( isConst )
					str += " const";
				str.Format(TXT_FUNCTION_s_NOT_FOUND, str.AddressOf());
				Error(str.AddressOf(), node);
				ctx->type.SetDummy();
				return -1;
			}
			else if( funcs.GetLength() > 1 )
			{
				Error(TXT_MORE_THAN_ONE_MATCHING_OP, node);
				PrintMatchingFuncs(funcs, node);

				ctx->type.SetDummy();
				return -1;
			}
		}
	}
	else if( op == ttInc || op == ttDec )
	{
		if( globalExpression )
		{
			Error(TXT_INC_OP_IN_GLOBAL_EXPR, node);
			return -1;
		}

		// Make sure the reference isn't a temporary variable
		if( ctx->type.isTemporary )
		{
			Error(TXT_REF_IS_TEMP, node);
			return -1;
		}
		if( ctx->type.dataType.IsReadOnly() )
		{
			Error(TXT_REF_IS_READ_ONLY, node);
			return -1;
		}
		if( ctx->property_get || ctx->property_set )
		{
			Error(TXT_INVALID_REF_PROP_ACCESS, node);
			return -1;
		}

		if( ctx->type.isVariable && !ctx->type.dataType.IsReference() )
			ConvertToReference(ctx);
		else if( !ctx->type.dataType.IsReference() )
		{
			Error(TXT_NOT_VALID_REFERENCE, node);
			return -1;
		}

		// Copy the value to a temp before changing it
		ConvertToTempVariable(ctx);

		// Increment the value pointed to by the reference still in the register
		asEBCInstr iInc = asBC_INCi, iDec = asBC_DECi;
		if( ctx->type.dataType.IsDoubleType() )
		{
			iInc = asBC_INCd;
			iDec = asBC_DECd;
		}
		else if( ctx->type.dataType.IsFloatType() )
		{
			iInc = asBC_INCf;
			iDec = asBC_DECf;
		}
		else if( ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsUnsignedType() )
		{
			if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt16, false)) ||
			    ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt16, false)) )
			{
				iInc = asBC_INCi16;
				iDec = asBC_DECi16;
			}
			else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt8, false)) ||
			         ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt8, false)) )
			{
				iInc = asBC_INCi8;
				iDec = asBC_DECi8;
			}
			else if( ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttInt64, false)) ||
			         ctx->type.dataType.IsEqualExceptRef(asCDataType::CreatePrimitive(ttUInt64, false)) )
			{
				iInc = asBC_INCi64;
				iDec = asBC_DECi64;
			}
		}
		else
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			return -1;
		}

		if( op == ttInc ) ctx->bc.Instr(iInc); else ctx->bc.Instr(iDec);
	}
	else if( op == ttDot )
	{
		if( node->firstChild->nodeType == snIdentifier )
		{
			ProcessPropertyGetAccessor(ctx, node);

			// Get the property name
			asCString name(&script->code[node->firstChild->tokenPos], node->firstChild->tokenLength);

			// We need to look for get/set property accessors.
			// If found, the context stores information on the get/set accessors
			// until it is known which is to be used.
			int r = 0;
			if( node->next && node->next->tokenType == ttOpenBracket )
			{
				// The property accessor should take an index arg
				asSExprContext dummyArg(engine);
				r = FindPropertyAccessor(name, ctx, &dummyArg, node);
			}
			if( r == 0 )
				r = FindPropertyAccessor(name, ctx, node);
			if( r != 0 )
				return r;
			
			if( !ctx->type.dataType.IsPrimitive() )
				Dereference(ctx, true);

			if( ctx->type.dataType.IsObjectHandle() )
			{
				// Convert the handle to a normal object
				asCDataType dt = ctx->type.dataType;
				dt.MakeHandle(false);

				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV);
			}

			// Find the property offset and type
			if( ctx->type.dataType.IsObject() )
			{
				bool isConst = ctx->type.dataType.IsReadOnly();

				asCObjectProperty *prop = builder->GetObjectProperty(ctx->type.dataType, name.AddressOf());
				if( prop )
				{
					// Is the property access allowed?
					if( prop->isPrivate && (!outFunc || outFunc->objectType != ctx->type.dataType.GetObjectType()) )
					{
						asCString msg;
						msg.Format(TXT_PRIVATE_PROP_ACCESS_s, name.AddressOf());
						Error(msg.AddressOf(), node);
					}

					// Put the offset on the stack
					ctx->bc.InstrSHORT_DW(asBC_ADDSi, prop->byteOffset, engine->GetTypeIdFromDataType(asCDataType::CreateObject(ctx->type.dataType.GetObjectType(), false)));

					if( prop->type.IsReference() )
						ctx->bc.Instr(asBC_RDSPTR);

					// Reference to primitive must be stored in the temp register
					if( prop->type.IsPrimitive() )
					{
						ctx->bc.Instr(asBC_PopRPtr);
					}

					// Set the new type (keeping info about temp variable)
					ctx->type.dataType = prop->type;
					ctx->type.dataType.MakeReference(true);
					ctx->type.isVariable = false;

					if( ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle() )
					{
						// Objects that are members are not references
						ctx->type.dataType.MakeReference(false);
					}

					ctx->type.dataType.MakeReadOnly(isConst ? true : prop->type.IsReadOnly());
				}
				else
				{
					asCString str;
					str.Format(TXT_s_NOT_MEMBER_OF_s, name.AddressOf(), ctx->type.dataType.Format().AddressOf());
					Error(str.AddressOf(), node);
					return -1;
				}
			}
			else
			{
				asCString str;
				str.Format(TXT_s_NOT_MEMBER_OF_s, name.AddressOf(), ctx->type.dataType.Format().AddressOf());
				Error(str.AddressOf(), node);
				return -1;
			}
		}
		else
		{
			if( globalExpression )
			{
				Error(TXT_METHOD_IN_GLOBAL_EXPR, node);
				return -1;
			}

			// Make sure it is an object we are accessing
			if( !ctx->type.dataType.IsObject() )
			{
				asCString str;
				str.Format(TXT_ILLEGAL_OPERATION_ON_s, ctx->type.dataType.Format().AddressOf());
				Error(str.AddressOf(), node);
				return -1;
			}
	
			// Process the get property accessor
			ProcessPropertyGetAccessor(ctx, node);

			bool isConst = false;
			if( ctx->type.dataType.IsObjectHandle() )
				isConst = ctx->type.dataType.IsHandleToConst();
			else
				isConst = ctx->type.dataType.IsReadOnly();

			asCObjectType *trueObj = ctx->type.dataType.GetObjectType();

			asCTypeInfo objType = ctx->type;

			// Compile function call
			CompileFunctionCall(node->firstChild, ctx, trueObj, isConst);

			// If the method returned a reference, then we can't release the original  
			// object yet, because the reference may be to a member of it
			if( objType.isTemporary &&
				(ctx->type.dataType.IsReference() || (ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle())) &&
				!ctx->type.isVariable ) // If the resulting type is a variable, then the reference is not a member
			{
				// Remember the original object's variable, so that it can be released
				// later on when the reference to its member goes out of scope
				ctx->type.isTemporary = true;
				ctx->type.stackOffset = objType.stackOffset;
			}
			else
			{
				// As the method didn't return a reference to a member
				// we can safely release the original object now
				ReleaseTemporaryVariable(objType, &ctx->bc);
			}
		}
	}
	else if( op == ttOpenBracket )
	{
		// If the property access takes an index arg, then we should use that instead of processing it now
		asCString propertyName;
		if( (ctx->property_get && engine->scriptFunctions[ctx->property_get]->GetParamCount() == 1) ||
			(ctx->property_set && engine->scriptFunctions[ctx->property_get]->GetParamCount() == 2) )
		{
			// Determine the name of the property accessor
			asCScriptFunction *func = 0;
			if( ctx->property_get )
				func = engine->scriptFunctions[ctx->property_get];
			else
				func = engine->scriptFunctions[ctx->property_get];
			propertyName = func->GetName();
			propertyName = propertyName.SubString(4);

			// Set the original type of the expression so we can re-evaluate the property accessor
			if( func->objectType )
			{
				ctx->type.dataType = asCDataType::CreateObject(func->objectType, ctx->property_const);
				if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
				if( ctx->property_ref )	ctx->type.dataType.MakeReference(true);
			}
			ctx->property_get = ctx->property_set = 0;
			if( ctx->property_arg )
			{
				asDELETE(ctx->property_arg, asSExprContext);
				ctx->property_arg = 0;
			}
		}
		else
		{
			if( !ctx->type.dataType.IsObject() )
			{
				asCString str;
				str.Format(TXT_OBJECT_DOESNT_SUPPORT_INDEX_OP, ctx->type.dataType.Format().AddressOf());
				Error(str.AddressOf(), node);
				return -1;
			}

			ProcessPropertyGetAccessor(ctx, node);
		}

		Dereference(ctx, true);
#ifdef AS_DEPRECATED
		// Since 2.20.0
		bool isConst = ctx->type.dataType.IsReadOnly();
#endif

		// Compile the expression
		asSExprContext expr(engine);
		CompileAssignment(node->firstChild, &expr);

		// Check for the existence of the opIndex method
		asSExprContext lctx(engine);
		MergeExprBytecodeAndType(&lctx, ctx);
		int r = 0; 
		if( propertyName == "" )
			r = CompileOverloadedDualOperator2(node, "opIndex", &lctx, &expr, ctx);
		if( r == 0 )
		{	
#ifndef AS_DEPRECATED
			// Check for accessors methods for the opIndex
			r = FindPropertyAccessor(propertyName == "" ? "opIndex" : propertyName.AddressOf(), &lctx, &expr, node);
			if( r == 0 )
			{
				asCString str;
				str.Format(TXT_OBJECT_DOESNT_SUPPORT_INDEX_OP, ctx->type.dataType.Format().AddressOf());
				Error(str.AddressOf(), node);
				return -1;	
			}
			else if( r < 0 )
				return -1;

			MergeExprBytecodeAndType(ctx, &lctx);
#else
			// Deprecated since 2.20.0

			MergeExprBytecodeAndType(ctx, &lctx);

			if( ctx->type.dataType.IsObjectHandle() )
			{
				// Convert the handle to a normal object
				asCDataType dt = ctx->type.dataType;
				dt.MakeHandle(false);

				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV);
			}

			asCTypeInfo objType = ctx->type;
			asSTypeBehaviour *beh = ctx->type.dataType.GetBehaviour();
			if( beh == 0 )
			{
				asCString str;
				str.Format(TXT_OBJECT_DOESNT_SUPPORT_INDEX_OP, ctx->type.dataType.Format().AddressOf());
				Error(str.AddressOf(), node);
				return -1;
			}
			else
			{
				// Now find a matching function for the object type and indexing type
				asCArray<int> ops;
				asUINT n;
				if( isConst )
				{
					// Only list const behaviours
					for( n = 0; n < beh->operators.GetLength(); n += 2 )
					{
						if( asBEHAVE_INDEX == beh->operators[n] && engine->scriptFunctions[beh->operators[n+1]]->isReadOnly )
							ops.PushLast(beh->operators[n+1]);
					}
				}
				else
				{
					// TODO: Prefer non-const over const
					for( n = 0; n < beh->operators.GetLength(); n += 2 )
					{
						if( asBEHAVE_INDEX == beh->operators[n] )
							ops.PushLast(beh->operators[n+1]);
					}
				}

				asCArray<int> ops1;
				MatchArgument(ops, ops1, &expr.type, 0);

				if( !isConst )
					FilterConst(ops1);

				// Did we find a suitable function?
				if( ops1.GetLength() == 1 )
				{
					asCScriptFunction *descr = engine->scriptFunctions[ops1[0]];

					// Store the code for the object
					asCByteCode objBC(engine);
					objBC.AddCode(&ctx->bc);

					// Add code for arguments

					PrepareArgument(&descr->parameterTypes[0], &expr, node->firstChild, true, descr->inOutFlags[0]);
					MergeExprBytecode(ctx, &expr);

					if( descr->parameterTypes[0].IsReference() )
					{
						if( descr->parameterTypes[0].IsObject() && !descr->parameterTypes[0].IsObjectHandle() )
							ctx->bc.InstrWORD(asBC_GETOBJREF, 0);
						else
							ctx->bc.InstrWORD(asBC_GETREF, 0);
					}
					else if( descr->parameterTypes[0].IsObject() )
					{
						ctx->bc.InstrWORD(asBC_GETOBJ, 0);

						// The temporary variable must not be freed as it will no longer hold an object
						DeallocateVariable(expr.type.stackOffset);
						expr.type.isTemporary = false;
					}

					// Add the code for the object again
					ctx->bc.AddCode(&objBC);

					asCArray<asSExprContext*> args;
					args.PushLast(&expr);
					PerformFunctionCall(descr->id, ctx, false, &args);
				}
				else if( ops.GetLength() > 1 )
				{
					Error(TXT_MORE_THAN_ONE_MATCHING_OP, node);
					PrintMatchingFuncs(ops, node);

					return -1;
				}
				else
				{
					asCString str;
					str.Format(TXT_NO_MATCHING_OP_FOUND_FOR_TYPE_s, expr.type.dataType.Format().AddressOf());
					Error(str.AddressOf(), node);
					return -1;
				}
			}

			// If the method returned a reference, then we can't release the original  
			// object yet, because the reference may be to a member of it
			if( objType.isTemporary &&
				(ctx->type.dataType.IsReference() || (ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle())) &&
				!ctx->type.isVariable ) // If the resulting type is a variable, then the reference is not to a member
			{
				// Remember the object's variable, so that it can be released
				// later on when the reference to its member goes out of scope
				ctx->type.isTemporary = true;
				ctx->type.stackOffset = objType.stackOffset;
			}
			else
			{
				// As the index operator didn't return a reference to a
				// member we can release the original object now
				ReleaseTemporaryVariable(objType, &ctx->bc);
			}
#endif
		}
	}

	return 0;
}

int asCCompiler::GetPrecedence(asCScriptNode *op)
{
	// x * y, x / y, x % y
	// x + y, x - y
	// x <= y, x < y, x >= y, x > y
	// x = =y, x != y, x xor y, x is y, x !is y
	// x and y
	// x or y

	// The following are not used in this function,
	// but should have lower precedence than the above
	// x ? y : z
	// x = y

	// The expression term have the highest precedence
	if( op->nodeType == snExprTerm )
		return 1;

	// Evaluate operators by token
	int tokenType = op->tokenType;
	if( tokenType == ttStar || tokenType == ttSlash || tokenType == ttPercent )
		return 0;

	if( tokenType == ttPlus || tokenType == ttMinus )
		return -1;

	if( tokenType == ttBitShiftLeft ||
		tokenType == ttBitShiftRight ||
		tokenType == ttBitShiftRightArith )
		return -2;

	if( tokenType == ttAmp )
		return -3;

	if( tokenType == ttBitXor )
		return -4;

	if( tokenType == ttBitOr )
		return -5;

	if( tokenType == ttLessThanOrEqual ||
		tokenType == ttLessThan ||
		tokenType == ttGreaterThanOrEqual ||
		tokenType == ttGreaterThan )
		return -6;

	if( tokenType == ttEqual || tokenType == ttNotEqual || tokenType == ttXor || tokenType == ttIs || tokenType == ttNotIs )
		return -7;

	if( tokenType == ttAnd )
		return -8;

	if( tokenType == ttOr )
		return -9;

	// Unknown operator
	asASSERT(false);

	return 0;
}

int asCCompiler::MatchArgument(asCArray<int> &funcs, asCArray<int> &matches, const asCTypeInfo *argType, int paramNum, bool allowObjectConstruct)
{
	bool isExactMatch        = false;
	bool isMatchExceptConst  = false;
	bool isMatchWithBaseType = false;
	bool isMatchExceptSign   = false;
	bool isMatchNotVarType   = false;

	asUINT n;

	matches.SetLength(0);

	for( n = 0; n < funcs.GetLength(); n++ )
	{
		asCScriptFunction *desc = builder->GetFunctionDescription(funcs[n]);

		// Does the function have arguments enough?
		if( (int)desc->parameterTypes.GetLength() <= paramNum )
			continue;

		// Can we make the match by implicit conversion?
		asSExprContext ti(engine);
		ti.type = *argType;
		if( argType->dataType.IsPrimitive() ) ti.type.dataType.MakeReference(false);
		ImplicitConversion(&ti, desc->parameterTypes[paramNum], 0, asIC_IMPLICIT_CONV, false, 0, allowObjectConstruct);
		if( desc->parameterTypes[paramNum].IsEqualExceptRef(ti.type.dataType) )
		{
			// Is it an exact match?
			if( argType->dataType.IsEqualExceptRef(ti.type.dataType) )
			{
				if( !isExactMatch ) matches.SetLength(0);

				isExactMatch = true;

				matches.PushLast(funcs[n]);
				continue;
			}

			if( !isExactMatch )
			{
				// Is it a match except const?
				if( argType->dataType.IsEqualExceptRefAndConst(ti.type.dataType) )
				{
					if( !isMatchExceptConst ) matches.SetLength(0);

					isMatchExceptConst = true;

					matches.PushLast(funcs[n]);
					continue;
				}

				if( !isMatchExceptConst )
				{
					// Is it a size promotion, e.g. int8 -> int?
					if( argType->dataType.IsSamePrimitiveBaseType(ti.type.dataType) || 
						(argType->dataType.IsEnumType() && ti.type.dataType.IsIntegerType()) )
					{
						if( !isMatchWithBaseType ) matches.SetLength(0);

						isMatchWithBaseType = true;

						matches.PushLast(funcs[n]);
						continue;
					}

					if( !isMatchWithBaseType )
					{
						// Conversion between signed and unsigned integer is better than between integer and float

						// Is it a match except for sign?
						if( (argType->dataType.IsIntegerType() && ti.type.dataType.IsUnsignedType()) ||
							(argType->dataType.IsUnsignedType() && ti.type.dataType.IsIntegerType()) ||
							(argType->dataType.IsEnumType() && ti.type.dataType.IsUnsignedType()) )
						{
							if( !isMatchExceptSign ) matches.SetLength(0);

							isMatchExceptSign = true;

							matches.PushLast(funcs[n]);
							continue;
						}

						if( !isMatchExceptSign )
						{
							// If there was any match without a var type it has higher priority
							if( desc->parameterTypes[paramNum].GetTokenType() != ttQuestion )
							{
								if( !isMatchNotVarType ) matches.SetLength(0);

								isMatchNotVarType = true;

								matches.PushLast(funcs[n]);
								continue;
							}

							// Implicit conversion to ?& has the smallest priority
							if( !isMatchNotVarType )
								matches.PushLast(funcs[n]);
						}
					}
				}
			}
		}
	}

	return (int)matches.GetLength();
}

void asCCompiler::PrepareArgument2(asSExprContext *ctx, asSExprContext *arg, asCDataType *paramType, bool isFunction, int refType, asCArray<int> *reservedVars)
{
	// Reference parameters whose value won't be used don't evaluate the expression
	if( paramType->IsReference() && !(refType & asTM_INREF) )
	{
		// Store the original bytecode so that it can be reused when processing the deferred output parameter
		asSExprContext *orig = asNEW(asSExprContext)(engine);
		MergeExprBytecodeAndType(orig, arg);
		arg->origExpr = orig;
	}

	PrepareArgument(paramType, arg, arg->exprNode, isFunction, refType, reservedVars);
	// arg still holds the original expression for output parameters
	ctx->bc.AddCode(&arg->bc);
}

bool asCCompiler::CompileOverloadedDualOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	ctx->exprNode = node;

	// What type of operator is it?
	int token = node->tokenType;
	if( token == ttUnrecognizedToken )
	{
		// This happens when the compiler is inferring an assignment 
		// operation from another action, for example in preparing a value 
		// as a function argument
		token = ttAssignment;
	}

	// boolean operators are not overloadable
	if( token == ttAnd ||
		token == ttOr ||
		token == ttXor )
		return false;

	// Dual operators can also be implemented as class methods
	if( token == ttEqual ||
		token == ttNotEqual )
	{
		// TODO: Should evaluate which of the two have the best match. If both have equal match, the first version should be used
		// Find the matching opEquals method 
		int r = CompileOverloadedDualOperator2(node, "opEquals", lctx, rctx, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
		if( r == 0 )
		{
			// Try again by switching the order of the operands
			r = CompileOverloadedDualOperator2(node, "opEquals", rctx, lctx, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
		}

		if( r == 1 )
		{
			if( token == ttNotEqual )
				ctx->bc.InstrSHORT(asBC_NOT, ctx->type.stackOffset);

			// Success, don't continue
			return true;
		}
		else if( r < 0 )
		{
			// Compiler error, don't continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
			return true;
		}
	}

	if( token == ttEqual ||
		token == ttNotEqual ||
		token == ttLessThan ||
		token == ttLessThanOrEqual ||
		token == ttGreaterThan ||
		token == ttGreaterThanOrEqual )
	{
		bool swappedOrder = false;

		// TODO: Should evaluate which of the two have the best match. If both have equal match, the first version should be used
		// Find the matching opCmp method
		int r = CompileOverloadedDualOperator2(node, "opCmp", lctx, rctx, ctx, true, asCDataType::CreatePrimitive(ttInt, false));
		if( r == 0 )
		{
			// Try again by switching the order of the operands
			swappedOrder = true;
			r = CompileOverloadedDualOperator2(node, "opCmp", rctx, lctx, ctx, true, asCDataType::CreatePrimitive(ttInt, false));
		}

		if( r == 1 )
		{
			ReleaseTemporaryVariable(ctx->type, &ctx->bc);

			int a = AllocateVariable(asCDataType::CreatePrimitive(ttBool, false), true);

			ctx->bc.InstrW_DW(asBC_CMPIi, ctx->type.stackOffset, 0);

			if( token == ttEqual )
				ctx->bc.Instr(asBC_TZ);
			else if( token == ttNotEqual )
				ctx->bc.Instr(asBC_TNZ);
			else if( (token == ttLessThan && !swappedOrder) ||
				     (token == ttGreaterThan && swappedOrder) )
				ctx->bc.Instr(asBC_TS);
			else if( (token == ttLessThanOrEqual && !swappedOrder) ||
				     (token == ttGreaterThanOrEqual && swappedOrder) )
				ctx->bc.Instr(asBC_TNP);
			else if( (token == ttGreaterThan && !swappedOrder) ||
				     (token == ttLessThan && swappedOrder) )
				ctx->bc.Instr(asBC_TP);
			else if( (token == ttGreaterThanOrEqual && !swappedOrder) ||
				     (token == ttLessThanOrEqual && swappedOrder) )
				ctx->bc.Instr(asBC_TNS);

			ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)a);

			ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, false), a, true);

			// Success, don't continue
			return true;
		}
		else if( r < 0 )
		{
			// Compiler error, don't continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
			return true;
		}
	}

	// The rest of the operators are not commutative, and doesn't require specific return type
	const char *op = 0, *op_r = 0;
	switch( token )
	{
	case ttPlus:               op = "opAdd";  op_r = "opAdd_r";  break;
	case ttMinus:              op = "opSub";  op_r = "opSub_r";  break;
	case ttStar:               op = "opMul";  op_r = "opMul_r";  break;
	case ttSlash:              op = "opDiv";  op_r = "opDiv_r";  break;
	case ttPercent:            op = "opMod";  op_r = "opMod_r";  break;
	case ttBitOr:              op = "opOr";   op_r = "opOr_r";   break;
	case ttAmp:                op = "opAnd";  op_r = "opAnd_r";  break;
	case ttBitXor:             op = "opXor";  op_r = "opXor_r";  break;
	case ttBitShiftLeft:       op = "opShl";  op_r = "opShl_r";  break;
	case ttBitShiftRight:      op = "opShr";  op_r = "opShr_r";  break;
	case ttBitShiftRightArith: op = "opUShr"; op_r = "opUShr_r"; break;
	}

	// TODO: Might be interesting to support a concatenation operator, e.g. ~

	if( op && op_r )
	{
		// TODO: Should evaluate which of the two have the best match. If both have equal match, the first version should be used
		// Find the matching operator method
		int r = CompileOverloadedDualOperator2(node, op, lctx, rctx, ctx);
		if( r == 0 )
		{
			// Try again by switching the order of the operands, and using the reversed operator
			r = CompileOverloadedDualOperator2(node, op_r, rctx, lctx, ctx);
		}

		if( r == 1 )
		{
			// Success, don't continue
			return true;
		}
		else if( r < 0 )
		{
			// Compiler error, don't continue
			ctx->type.SetDummy();
			return true;
		}
	}

	// Assignment operators
	op = 0;
	switch( token )
	{
	case ttAssignment:        op = "opAssign";     break;
	case ttAddAssign:         op = "opAddAssign";  break;
	case ttSubAssign:         op = "opSubAssign";  break;
	case ttMulAssign:         op = "opMulAssign";  break;
	case ttDivAssign:         op = "opDivAssign";  break;
	case ttModAssign:         op = "opModAssign";  break;
	case ttOrAssign:          op = "opOrAssign";   break;
	case ttAndAssign:         op = "opAndAssign";  break;
	case ttXorAssign:         op = "opXorAssign";  break;
	case ttShiftLeftAssign:   op = "opShlAssign";  break;
	case ttShiftRightLAssign: op = "opShrAssign";  break;
	case ttShiftRightAAssign: op = "opUShrAssign"; break;
	}

	if( op )
	{
		// TODO: Shouldn't accept const lvalue with the assignment operators

		// Find the matching operator method
		int r = CompileOverloadedDualOperator2(node, op, lctx, rctx, ctx);
		if( r == 1 )
		{
			// Success, don't continue
			return true;
		}
		else if( r < 0 )
		{
			// Compiler error, don't continue
			ctx->type.SetDummy();
			return true;
		}
	}

	// No suitable operator was found
	return false;
}

// Returns negative on compile error
//         zero on no matching operator
//         one on matching operator
int asCCompiler::CompileOverloadedDualOperator2(asCScriptNode *node, const char *methodName, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx, bool specificReturn, const asCDataType &returnType)
{
	// Find the matching method 
	if( lctx->type.dataType.IsObject() && !lctx->type.isExplicitHandle )
	{
		// Is the left value a const?
		bool isConst = false;
		if( lctx->type.dataType.IsObjectHandle() )
			isConst = lctx->type.dataType.IsHandleToConst();
		else
			isConst = lctx->type.dataType.IsReadOnly();

		asCArray<int> funcs;
		asCObjectType *ot = lctx->type.dataType.GetObjectType();
		for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
		{
			asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
			if( func->name == methodName &&
				(!specificReturn || func->returnType == returnType) &&
				func->parameterTypes.GetLength() == 1 &&
				(!isConst || func->isReadOnly) )
			{
				// Make sure the method is accessible by the module
				asCConfigGroup *group = engine->FindConfigGroupForFunction(func->id);
				if( !group || group->HasModuleAccess(builder->module->name.AddressOf()) )
					funcs.PushLast(func->id);
			}
		}

		// Which is the best matching function?
		asCArray<int> ops;
		MatchArgument(funcs, ops, &rctx->type, 0);

		// If the object is not const, then we need to prioritize non-const methods
		if( !isConst )
			FilterConst(ops);

		// Did we find an operator?
		if( ops.GetLength() == 1 )
		{
			// Process the lctx expression as get accessor
			ProcessPropertyGetAccessor(lctx, node);

			// Merge the bytecode so that it forms lvalue.methodName(rvalue)
			asCTypeInfo objType = lctx->type;
			asCArray<asSExprContext *> args;
			args.PushLast(rctx);
			MergeExprBytecode(ctx, lctx);
			ctx->type = lctx->type;
			MakeFunctionCall(ctx, ops[0], objType.dataType.GetObjectType(), args, node);

			// If the method returned a reference, then we can't release the original  
			// object yet, because the reference may be to a member of it
			if( objType.isTemporary &&
				(ctx->type.dataType.IsReference() || (ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle())) &&
				!ctx->type.isVariable ) // If the resulting type is a variable, then the reference is not to a member
			{
				// Remember the object's variable, so that it can be released
				// later on when the reference to its member goes out of scope
				ctx->type.isTemporary = true;
				ctx->type.stackOffset = objType.stackOffset;
			}
			else
			{
				// As the index operator didn't return a reference to a
				// member we can release the original object now
				ReleaseTemporaryVariable(objType, &ctx->bc);
			}

			// Found matching operator
			return 1;
		}
		else if( ops.GetLength() > 1 )
		{
			Error(TXT_MORE_THAN_ONE_MATCHING_OP, node);
			PrintMatchingFuncs(ops, node);

			ctx->type.SetDummy();

			// Compiler error
			return -1;
		}
	}

	// No matching operator
	return 0;
}

void asCCompiler::MakeFunctionCall(asSExprContext *ctx, int funcId, asCObjectType *objectType, asCArray<asSExprContext*> &args, asCScriptNode *node, bool useVariable, int stackOffset, int funcPtrVar)
{
	if( objectType )
	{
		Dereference(ctx, true);

		// Warn if the method is non-const and the object is temporary 
		// since the changes will be lost when the object is destroyed.
		// If the object is accessed through a handle, then it is assumed
		// the object is not temporary, even though the handle is.
		if( ctx->type.isTemporary && 
			!ctx->type.dataType.IsObjectHandle() && 
			!engine->scriptFunctions[funcId]->isReadOnly )
		{
			Warning(TXT_CALLING_NONCONST_METHOD_ON_TEMP, node);
			Information(engine->scriptFunctions[funcId]->GetDeclaration(), node);
		}
	}

	asCByteCode objBC(engine);
	objBC.AddCode(&ctx->bc);

	PrepareFunctionCall(funcId, &ctx->bc, args);

	// Verify if any of the args variable offsets are used in the other code.
	// If they are exchange the offset for a new one
	asUINT n;
	for( n = 0; n < args.GetLength(); n++ )
	{
		if( args[n]->type.isTemporary && objBC.IsVarUsed(args[n]->type.stackOffset) )
		{
			// Release the current temporary variable
			ReleaseTemporaryVariable(args[n]->type, 0);

			asCArray<int> usedVars;
			objBC.GetVarsUsed(usedVars);
			ctx->bc.GetVarsUsed(usedVars);

			asCDataType dt = args[n]->type.dataType;
			dt.MakeReference(false);
			int newOffset = AllocateVariableNotIn(dt, true, &usedVars, IsVariableOnHeap(args[n]->type.stackOffset));

			asASSERT( IsVariableOnHeap(args[n]->type.stackOffset) == IsVariableOnHeap(newOffset) );

			ctx->bc.ExchangeVar(args[n]->type.stackOffset, newOffset);
			args[n]->type.stackOffset = (short)newOffset;
			args[n]->type.isTemporary = true;
			args[n]->type.isVariable = true;
		}
	}

	ctx->bc.AddCode(&objBC);

	MoveArgsToStack(funcId, &ctx->bc, args, objectType ? true : false);

	PerformFunctionCall(funcId, ctx, false, &args, 0, useVariable, stackOffset, funcPtrVar);
}

int asCCompiler::CompileOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	IsVariableInitialized(&lctx->type, node);
	IsVariableInitialized(&rctx->type, node);

	if( lctx->type.isExplicitHandle || rctx->type.isExplicitHandle ||
		node->tokenType == ttIs || node->tokenType == ttNotIs )
	{
		CompileOperatorOnHandles(node, lctx, rctx, ctx);
		return 0;
	}
	else
	{
		// Compile an overloaded operator for the two operands
		if( CompileOverloadedDualOperator(node, lctx, rctx, ctx) )
			return 0;

		// If both operands are objects, then we shouldn't continue
		if( lctx->type.dataType.IsObject() && rctx->type.dataType.IsObject() )
		{
			asCString str;
			str.Format(TXT_NO_MATCHING_OP_FOUND_FOR_TYPES_s_AND_s, lctx->type.dataType.Format().AddressOf(), rctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), node);
			ctx->type.SetDummy();
			return -1;
		}

		// Make sure we have two variables or constants
		if( lctx->type.dataType.IsReference() ) ConvertToVariableNotIn(lctx, rctx);
		if( rctx->type.dataType.IsReference() ) ConvertToVariableNotIn(rctx, lctx);

		// Process the property get accessors (if any)
		ProcessPropertyGetAccessor(lctx, node);
		ProcessPropertyGetAccessor(rctx, node);

		// Make sure lctx doesn't end up with a variable used in rctx
		if( lctx->type.isTemporary && rctx->bc.IsVarUsed(lctx->type.stackOffset) )
		{
			asCArray<int> vars;
			rctx->bc.GetVarsUsed(vars);
			int offset = AllocateVariableNotIn(lctx->type.dataType, true, &vars);
			rctx->bc.ExchangeVar(lctx->type.stackOffset, offset);
			ReleaseTemporaryVariable(offset, 0);
		}

		// Math operators
		// + - * / % += -= *= /= %=
		int op = node->tokenType;
		if( op == ttPlus    || op == ttAddAssign ||
			op == ttMinus   || op == ttSubAssign ||
			op == ttStar    || op == ttMulAssign ||
			op == ttSlash   || op == ttDivAssign ||
			op == ttPercent || op == ttModAssign )
		{
			CompileMathOperator(node, lctx, rctx, ctx);
			return 0;
		}

		// Bitwise operators
		// << >> >>> & | ^ <<= >>= >>>= &= |= ^=
		if( op == ttAmp                || op == ttAndAssign         ||
			op == ttBitOr              || op == ttOrAssign          ||
			op == ttBitXor             || op == ttXorAssign         ||
			op == ttBitShiftLeft       || op == ttShiftLeftAssign   ||
			op == ttBitShiftRight      || op == ttShiftRightLAssign ||
			op == ttBitShiftRightArith || op == ttShiftRightAAssign )
		{
			CompileBitwiseOperator(node, lctx, rctx, ctx);
			return 0;
		}

		// Comparison operators
		// == != < > <= >=
		if( op == ttEqual       || op == ttNotEqual           ||
			op == ttLessThan    || op == ttLessThanOrEqual    ||
			op == ttGreaterThan || op == ttGreaterThanOrEqual )
		{
			CompileComparisonOperator(node, lctx, rctx, ctx);
			return 0;
		}

		// Boolean operators
		// && || ^^
		if( op == ttAnd || op == ttOr || op == ttXor )
		{
			CompileBooleanOperator(node, lctx, rctx, ctx);
			return 0;
		}
	}

	asASSERT(false);
	return -1;
}

void asCCompiler::ConvertToTempVariableNotIn(asSExprContext *ctx, asSExprContext *exclude)
{
	asCArray<int> excludeVars;
	if( exclude ) exclude->bc.GetVarsUsed(excludeVars);
	ConvertToTempVariableNotIn(ctx, &excludeVars);
}

void asCCompiler::ConvertToTempVariableNotIn(asSExprContext *ctx, asCArray<int> *reservedVars)
{
	// This is only used for primitive types and null handles
	asASSERT( ctx->type.dataType.IsPrimitive() || ctx->type.dataType.IsNullHandle() );

	ConvertToVariableNotIn(ctx, reservedVars);
	if( !ctx->type.isTemporary )
	{
		if( ctx->type.dataType.IsPrimitive() )
		{
			// Copy the variable to a temporary variable
			int offset = AllocateVariableNotIn(ctx->type.dataType, true, reservedVars);
			if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				ctx->bc.InstrW_W(asBC_CpyVtoV4, offset, ctx->type.stackOffset);
			else
				ctx->bc.InstrW_W(asBC_CpyVtoV8, offset, ctx->type.stackOffset);
			ctx->type.SetVariable(ctx->type.dataType, offset, true);
		}
		else
		{
			// We should never get here
			asASSERT(false);
		}
	}
}

void asCCompiler::ConvertToTempVariable(asSExprContext *ctx)
{
	ConvertToTempVariableNotIn(ctx, (asCArray<int>*)0);
}

void asCCompiler::ConvertToVariable(asSExprContext *ctx)
{
	ConvertToVariableNotIn(ctx, (asCArray<int>*)0);
}

void asCCompiler::ConvertToVariableNotIn(asSExprContext *ctx, asCArray<int> *reservedVars)
{
	asCArray<int> excludeVars;
	if( reservedVars ) excludeVars.Concatenate(*reservedVars);
	int offset;
	if( !ctx->type.isVariable &&
		(ctx->type.dataType.IsObjectHandle() || 
		 (ctx->type.dataType.IsObject() && ctx->type.dataType.SupportHandles())) )
	{
		offset = AllocateVariableNotIn(ctx->type.dataType, true, &excludeVars);
		if( ctx->type.IsNullConstant() )
		{
#ifdef AS_64BIT_PTR
			ctx->bc.InstrSHORT_QW(asBC_SetV8, (short)offset, 0);
#else
			ctx->bc.InstrSHORT_DW(asBC_SetV4, (short)offset, 0);
#endif
		}
		else
		{
			// Copy the object handle to a variable
			ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
			ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetObjectType());
			ctx->bc.Pop(AS_PTR_SIZE);
		}

		ReleaseTemporaryVariable(ctx->type, &ctx->bc);
		ctx->type.SetVariable(ctx->type.dataType, offset, true);
		ctx->type.dataType.MakeHandle(true);
	}
	else if( (!ctx->type.isVariable || ctx->type.dataType.IsReference()) &&
		     ctx->type.dataType.IsPrimitive() )
	{
		if( ctx->type.isConstant )
		{
			offset = AllocateVariableNotIn(ctx->type.dataType, true, &excludeVars);
			if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
				ctx->bc.InstrSHORT_B(asBC_SetV1, (short)offset, ctx->type.byteValue);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 2 )
				ctx->bc.InstrSHORT_W(asBC_SetV2, (short)offset, ctx->type.wordValue);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 4 )
				ctx->bc.InstrSHORT_DW(asBC_SetV4, (short)offset, ctx->type.dwordValue);
			else
				ctx->bc.InstrSHORT_QW(asBC_SetV8, (short)offset, ctx->type.qwordValue);

			ctx->type.SetVariable(ctx->type.dataType, offset, true);
			return;
		}
		else
		{
			asASSERT(ctx->type.dataType.IsPrimitive());
			asASSERT(ctx->type.dataType.IsReference());

			ctx->type.dataType.MakeReference(false);
			offset = AllocateVariableNotIn(ctx->type.dataType, true, &excludeVars);

			// Read the value from the address in the register directly into the variable
			if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
				ctx->bc.InstrSHORT(asBC_RDR1, (short)offset);
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 2 )
				ctx->bc.InstrSHORT(asBC_RDR2, (short)offset);
			else if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				ctx->bc.InstrSHORT(asBC_RDR4, (short)offset);
			else
				ctx->bc.InstrSHORT(asBC_RDR8, (short)offset);
		}

		ReleaseTemporaryVariable(ctx->type, &ctx->bc);
		ctx->type.SetVariable(ctx->type.dataType, offset, true);
	}
}

void asCCompiler::ConvertToVariableNotIn(asSExprContext *ctx, asSExprContext *exclude)
{
	asCArray<int> excludeVars;
	if( exclude ) exclude->bc.GetVarsUsed(excludeVars);
	ConvertToVariableNotIn(ctx, &excludeVars);
}


void asCCompiler::CompileMathOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext  *rctx, asSExprContext *ctx)
{
	// TODO: If a constant is only using 32bits, then a 32bit operation is preferred

	// Implicitly convert the operands to a number type
	asCDataType to;
	if( lctx->type.dataType.IsDoubleType() || rctx->type.dataType.IsDoubleType() )
		to.SetTokenType(ttDouble);
	else if( lctx->type.dataType.IsFloatType() || rctx->type.dataType.IsFloatType() )
		to.SetTokenType(ttFloat);
	else if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 || rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
	{
		if( lctx->type.dataType.IsIntegerType() || rctx->type.dataType.IsIntegerType() )
			to.SetTokenType(ttInt64);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt64);
	}
	else
	{
		if( lctx->type.dataType.IsIntegerType() || rctx->type.dataType.IsIntegerType() ||
			lctx->type.dataType.IsEnumType() || rctx->type.dataType.IsEnumType() )
			to.SetTokenType(ttInt);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt);
	}

	// If doing an operation with double constant and float variable, the constant should be converted to float
	if( (lctx->type.isConstant && lctx->type.dataType.IsDoubleType() && !rctx->type.isConstant && rctx->type.dataType.IsFloatType()) ||
		(rctx->type.isConstant && rctx->type.dataType.IsDoubleType() && !lctx->type.isConstant && lctx->type.dataType.IsFloatType()) )
		to.SetTokenType(ttFloat);

	// Do the actual conversion
	asCArray<int> reservedVars;
	rctx->bc.GetVarsUsed(reservedVars);
	lctx->bc.GetVarsUsed(reservedVars);

	if( lctx->type.dataType.IsReference() )
		ConvertToVariableNotIn(lctx, &reservedVars);
	if( rctx->type.dataType.IsReference() )
		ConvertToVariableNotIn(rctx, &reservedVars);

	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsIntegerType() &&
		!lctx->type.dataType.IsUnsignedType() &&
		!lctx->type.dataType.IsFloatType() &&
		!lctx->type.dataType.IsDoubleType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_MATH_TYPE, lctx->type.dataType.Format().AddressOf());
		Error(str.AddressOf(), node);

		ctx->type.SetDummy();
		return;
	}

	if( !rctx->type.dataType.IsIntegerType() &&
		!rctx->type.dataType.IsUnsignedType() &&
		!rctx->type.dataType.IsFloatType() &&
		!rctx->type.dataType.IsDoubleType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_MATH_TYPE, rctx->type.dataType.Format().AddressOf());
		Error(str.AddressOf(), node);

		ctx->type.SetDummy();
		return;
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

	// Verify if we are dividing with a constant zero
	int op = node->tokenType;
	if( rctx->type.isConstant && rctx->type.qwordValue == 0 &&
		(op == ttSlash   || op == ttDivAssign ||
		 op == ttPercent || op == ttModAssign) )
	{
		Error(TXT_DIVIDE_BY_ZERO, node);
	}

	if( !isConstant )
	{
		ConvertToVariableNotIn(lctx, rctx);
		ConvertToVariableNotIn(rctx, lctx);
		ReleaseTemporaryVariable(lctx->type, &lctx->bc);
		ReleaseTemporaryVariable(rctx->type, &rctx->bc);

		if( op == ttAddAssign || op == ttSubAssign ||
			op == ttMulAssign || op == ttDivAssign ||
			op == ttModAssign )
		{
			// Merge the operands in the different order so that they are evaluated correctly
			MergeExprBytecode(ctx, rctx);
			MergeExprBytecode(ctx, lctx);
		}
		else
		{
			MergeExprBytecode(ctx, lctx);
			MergeExprBytecode(ctx, rctx);
		}
		ProcessDeferredParams(ctx);

		asEBCInstr instruction = asBC_ADDi;
		if( lctx->type.dataType.IsIntegerType() ||
			lctx->type.dataType.IsUnsignedType() )
		{
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				if( op == ttPlus || op == ttAddAssign )
					instruction = asBC_ADDi;
				else if( op == ttMinus || op == ttSubAssign )
					instruction = asBC_SUBi;
				else if( op == ttStar || op == ttMulAssign )
					instruction = asBC_MULi;
				else if( op == ttSlash || op == ttDivAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_DIVi;
					else
						instruction = asBC_DIVu;
				}
				else if( op == ttPercent || op == ttModAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_MODi; 
					else
						instruction = asBC_MODu;
				}
			}
			else
			{
				if( op == ttPlus || op == ttAddAssign )
					instruction = asBC_ADDi64;
				else if( op == ttMinus || op == ttSubAssign )
					instruction = asBC_SUBi64;
				else if( op == ttStar || op == ttMulAssign )
					instruction = asBC_MULi64;
				else if( op == ttSlash || op == ttDivAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_DIVi64;
					else
						instruction = asBC_DIVu64;
				}
				else if( op == ttPercent || op == ttModAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_MODi64;
					else
						instruction = asBC_MODu64;
				}
			}
		}
		else if( lctx->type.dataType.IsFloatType() )
		{
			if( op == ttPlus || op == ttAddAssign )
				instruction = asBC_ADDf;
			else if( op == ttMinus || op == ttSubAssign )
				instruction = asBC_SUBf;
			else if( op == ttStar || op == ttMulAssign )
				instruction = asBC_MULf;
			else if( op == ttSlash || op == ttDivAssign )
				instruction = asBC_DIVf;
			else if( op == ttPercent || op == ttModAssign )
				instruction = asBC_MODf;
		}
		else if( lctx->type.dataType.IsDoubleType() )
		{
			if( op == ttPlus || op == ttAddAssign )
				instruction = asBC_ADDd;
			else if( op == ttMinus || op == ttSubAssign )
				instruction = asBC_SUBd;
			else if( op == ttStar || op == ttMulAssign )
				instruction = asBC_MULd;
			else if( op == ttSlash || op == ttDivAssign )
				instruction = asBC_DIVd;
			else if( op == ttPercent || op == ttModAssign )
				instruction = asBC_MODd;
		}
		else
		{
			// Shouldn't be possible
			asASSERT(false);
		}

		// Do the operation
		int a = AllocateVariable(lctx->type.dataType, true);
		int b = lctx->type.stackOffset;
		int c = rctx->type.stackOffset;

		ctx->bc.InstrW_W_W(instruction, a, b, c);

		ctx->type.SetVariable(lctx->type.dataType, a, true);
	}
	else
	{
		// Both values are constants
		if( lctx->type.dataType.IsIntegerType() ||
			lctx->type.dataType.IsUnsignedType() )
		{
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				int v = 0;
				if( op == ttPlus )
					v = lctx->type.intValue + rctx->type.intValue;
				else if( op == ttMinus )
					v = lctx->type.intValue - rctx->type.intValue;
				else if( op == ttStar )
					v = lctx->type.intValue * rctx->type.intValue;
				else if( op == ttSlash )
				{
					if( rctx->type.intValue == 0 )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = lctx->type.intValue / rctx->type.intValue; 
						else
							v = lctx->type.dwordValue / rctx->type.dwordValue; 
				}
				else if( op == ttPercent )
				{
					if( rctx->type.intValue == 0 )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = lctx->type.intValue % rctx->type.intValue;
						else
							v = lctx->type.dwordValue % rctx->type.dwordValue;
				}

				ctx->type.SetConstantDW(lctx->type.dataType, v);

				// If the right value is greater than the left value in a minus operation, then we need to convert the type to int
				if( lctx->type.dataType.GetTokenType() == ttUInt && op == ttMinus && lctx->type.intValue < rctx->type.intValue )
					ctx->type.dataType.SetTokenType(ttInt);
			}
			else
			{
				asQWORD v = 0;
				if( op == ttPlus )
					v = lctx->type.qwordValue + rctx->type.qwordValue;
				else if( op == ttMinus )
					v = lctx->type.qwordValue - rctx->type.qwordValue;
				else if( op == ttStar )
					v = lctx->type.qwordValue * rctx->type.qwordValue;
				else if( op == ttSlash )
				{
					if( rctx->type.qwordValue == 0 )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = asINT64(lctx->type.qwordValue) / asINT64(rctx->type.qwordValue);
						else
							v = lctx->type.qwordValue / rctx->type.qwordValue;
				}
				else if( op == ttPercent )
				{
					if( rctx->type.qwordValue == 0 )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = asINT64(lctx->type.qwordValue) % asINT64(rctx->type.qwordValue);
						else
							v = lctx->type.qwordValue % rctx->type.qwordValue;
				}

				ctx->type.SetConstantQW(lctx->type.dataType, v);

				// If the right value is greater than the left value in a minus operation, then we need to convert the type to int
				if( lctx->type.dataType.GetTokenType() == ttUInt64 && op == ttMinus && lctx->type.qwordValue < rctx->type.qwordValue )
					ctx->type.dataType.SetTokenType(ttInt64);
			}
		}
		else if( lctx->type.dataType.IsFloatType() )
		{
			float v = 0.0f;
			if( op == ttPlus )
				v = lctx->type.floatValue + rctx->type.floatValue;
			else if( op == ttMinus )
				v = lctx->type.floatValue - rctx->type.floatValue;
			else if( op == ttStar )
				v = lctx->type.floatValue * rctx->type.floatValue;
			else if( op == ttSlash )
			{
				if( rctx->type.floatValue == 0 )
					v = 0;
				else
					v = lctx->type.floatValue / rctx->type.floatValue;
			}
			else if( op == ttPercent )
			{
				if( rctx->type.floatValue == 0 )
					v = 0;
				else
					v = fmodf(lctx->type.floatValue, rctx->type.floatValue);
			}

			ctx->type.SetConstantF(lctx->type.dataType, v);
		}
		else if( lctx->type.dataType.IsDoubleType() )
		{
			double v = 0.0;
			if( op == ttPlus )
				v = lctx->type.doubleValue + rctx->type.doubleValue;
			else if( op == ttMinus )
				v = lctx->type.doubleValue - rctx->type.doubleValue;
			else if( op == ttStar )
				v = lctx->type.doubleValue * rctx->type.doubleValue;
			else if( op == ttSlash )
			{
				if( rctx->type.doubleValue == 0 )
					v = 0;
				else
					v = lctx->type.doubleValue / rctx->type.doubleValue;
			}
			else if( op == ttPercent )
			{
				if( rctx->type.doubleValue == 0 )
					v = 0;
				else
					v = fmod(lctx->type.doubleValue, rctx->type.doubleValue);
			}

			ctx->type.SetConstantD(lctx->type.dataType, v);
		}
		else
		{
			// Shouldn't be possible
			asASSERT(false);
		}
	}
}

void asCCompiler::CompileBitwiseOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	// TODO: If a constant is only using 32bits, then a 32bit operation is preferred

	int op = node->tokenType;
	if( op == ttAmp    || op == ttAndAssign ||
		op == ttBitOr  || op == ttOrAssign  ||
		op == ttBitXor || op == ttXorAssign )
	{
		// Convert left hand operand to integer if it's not already one
		asCDataType to;
		if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 ||
			rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			to.SetTokenType(ttUInt64);
		else
			to.SetTokenType(ttUInt);

		// Do the actual conversion
		asCArray<int> reservedVars;
		rctx->bc.GetVarsUsed(reservedVars);
		ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);

		// Verify that the conversion was successful
		if( !lctx->type.dataType.IsUnsignedType() )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
			Error(str.AddressOf(), node);
		}

		// Convert right hand operand to same type as left hand operand
		asCArray<int> vars;
		lctx->bc.GetVarsUsed(vars);
		ImplicitConversion(rctx, lctx->type.dataType, node, asIC_IMPLICIT_CONV, true, &vars);
		if( !rctx->type.dataType.IsEqualExceptRef(lctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format().AddressOf(), lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), node);
		}

		bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

		if( !isConstant )
		{
			ConvertToVariableNotIn(lctx, rctx);
			ConvertToVariableNotIn(rctx, lctx);
			ReleaseTemporaryVariable(lctx->type, &lctx->bc);
			ReleaseTemporaryVariable(rctx->type, &rctx->bc);

			if( op == ttAndAssign || op == ttOrAssign || op == ttXorAssign )
			{
				// Compound assignments execute the right hand value first
				MergeExprBytecode(ctx, rctx);
				MergeExprBytecode(ctx, lctx);
			}
			else
			{
				MergeExprBytecode(ctx, lctx);
				MergeExprBytecode(ctx, rctx);
			}
			ProcessDeferredParams(ctx);

			asEBCInstr instruction = asBC_BAND;
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				if( op == ttAmp || op == ttAndAssign )
					instruction = asBC_BAND;
				else if( op == ttBitOr || op == ttOrAssign )
					instruction = asBC_BOR;
				else if( op == ttBitXor || op == ttXorAssign )
					instruction = asBC_BXOR;
			}
			else
			{
				if( op == ttAmp || op == ttAndAssign )
					instruction = asBC_BAND64;
				else if( op == ttBitOr || op == ttOrAssign )
					instruction = asBC_BOR64;
				else if( op == ttBitXor || op == ttXorAssign )
					instruction = asBC_BXOR64;
			}

			// Do the operation
			int a = AllocateVariable(lctx->type.dataType, true);
			int b = lctx->type.stackOffset;
			int c = rctx->type.stackOffset;

			ctx->bc.InstrW_W_W(instruction, a, b, c);

			ctx->type.SetVariable(lctx->type.dataType, a, true);
		}
		else
		{
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				asQWORD v = 0;
				if( op == ttAmp )
					v = lctx->type.qwordValue & rctx->type.qwordValue;
				else if( op == ttBitOr )
					v = lctx->type.qwordValue | rctx->type.qwordValue;
				else if( op == ttBitXor )
					v = lctx->type.qwordValue ^ rctx->type.qwordValue;

				// Remember the result
				ctx->type.SetConstantQW(lctx->type.dataType, v);
			}
			else
			{
				asDWORD v = 0;
				if( op == ttAmp )
					v = lctx->type.dwordValue & rctx->type.dwordValue;
				else if( op == ttBitOr )
					v = lctx->type.dwordValue | rctx->type.dwordValue;
				else if( op == ttBitXor )
					v = lctx->type.dwordValue ^ rctx->type.dwordValue;

				// Remember the result
				ctx->type.SetConstantDW(lctx->type.dataType, v);
			}
		}
	}
	else if( op == ttBitShiftLeft       || op == ttShiftLeftAssign   ||
		     op == ttBitShiftRight      || op == ttShiftRightLAssign ||
			 op == ttBitShiftRightArith || op == ttShiftRightAAssign )
	{
		// Don't permit object to primitive conversion, since we don't know which integer type is the correct one
		if( lctx->type.dataType.IsObject() )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format().AddressOf());
			Error(str.AddressOf(), node);

			// Set an integer value and allow the compiler to continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), 0);
			return;
		}

		// Convert left hand operand to integer if it's not already one
		asCDataType to = lctx->type.dataType;
		if( lctx->type.dataType.IsUnsignedType() &&
			lctx->type.dataType.GetSizeInMemoryBytes() < 4 )
		{
			to = asCDataType::CreatePrimitive(ttUInt, false);
		}
		else if( !lctx->type.dataType.IsUnsignedType() )
		{
			asCDataType to;
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 2  )
				to.SetTokenType(ttInt64);
			else
				to.SetTokenType(ttInt);
		}

		// Do the actual conversion
		asCArray<int> reservedVars;
		rctx->bc.GetVarsUsed(reservedVars);
		ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);

		// Verify that the conversion was successful
		if( lctx->type.dataType != to )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
			Error(str.AddressOf(), node);
		}

		// Right operand must be 32bit uint
		asCArray<int> vars;
		lctx->bc.GetVarsUsed(vars);
		ImplicitConversion(rctx, asCDataType::CreatePrimitive(ttUInt, true), node, asIC_IMPLICIT_CONV, true, &vars);
		if( !rctx->type.dataType.IsUnsignedType() )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format().AddressOf(), "uint");
			Error(str.AddressOf(), node);
		}

		bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

		if( !isConstant )
		{
			ConvertToVariableNotIn(lctx, rctx);
			ConvertToVariableNotIn(rctx, lctx);
			ReleaseTemporaryVariable(lctx->type, &lctx->bc);
			ReleaseTemporaryVariable(rctx->type, &rctx->bc);

			if( op == ttShiftLeftAssign || op == ttShiftRightLAssign || op == ttShiftRightAAssign )
			{
				// Compound assignments execute the right hand value first
				MergeExprBytecode(ctx, rctx);
				MergeExprBytecode(ctx, lctx);
			}
			else
			{
				MergeExprBytecode(ctx, lctx);
				MergeExprBytecode(ctx, rctx);
			}
			ProcessDeferredParams(ctx);

			asEBCInstr instruction = asBC_BSLL;
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				if( op == ttBitShiftLeft || op == ttShiftLeftAssign )
					instruction = asBC_BSLL;
				else if( op == ttBitShiftRight || op == ttShiftRightLAssign )
					instruction = asBC_BSRL;
				else if( op == ttBitShiftRightArith || op == ttShiftRightAAssign )
					instruction = asBC_BSRA;
			}
			else
			{
				if( op == ttBitShiftLeft || op == ttShiftLeftAssign )
					instruction = asBC_BSLL64;
				else if( op == ttBitShiftRight || op == ttShiftRightLAssign )
					instruction = asBC_BSRL64;
				else if( op == ttBitShiftRightArith || op == ttShiftRightAAssign )
					instruction = asBC_BSRA64;
			}

			// Do the operation
			int a = AllocateVariable(lctx->type.dataType, true);
			int b = lctx->type.stackOffset;
			int c = rctx->type.stackOffset;

			ctx->bc.InstrW_W_W(instruction, a, b, c);

			ctx->type.SetVariable(lctx->type.dataType, a, true);
		}
		else
		{
			if( lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				asDWORD v = 0;
				if( op == ttBitShiftLeft )
					v = lctx->type.dwordValue << rctx->type.dwordValue;
				else if( op == ttBitShiftRight )
					v = lctx->type.dwordValue >> rctx->type.dwordValue;
				else if( op == ttBitShiftRightArith )
					v = lctx->type.intValue >> rctx->type.dwordValue;

				ctx->type.SetConstantDW(lctx->type.dataType, v);
			}
			else
			{
				asQWORD v = 0;
				if( op == ttBitShiftLeft )
					v = lctx->type.qwordValue << rctx->type.dwordValue;
				else if( op == ttBitShiftRight )
					v = lctx->type.qwordValue >> rctx->type.dwordValue;
				else if( op == ttBitShiftRightArith )
					v = asINT64(lctx->type.qwordValue) >> rctx->type.dwordValue;

				ctx->type.SetConstantQW(lctx->type.dataType, v);
			}
		}
	}
}

void asCCompiler::CompileComparisonOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	// Both operands must be of the same type

	// Implicitly convert the operands to a number type
	asCDataType to;
	if( lctx->type.dataType.IsDoubleType() || rctx->type.dataType.IsDoubleType() )
		to.SetTokenType(ttDouble);
	else if( lctx->type.dataType.IsFloatType() || rctx->type.dataType.IsFloatType() )
		to.SetTokenType(ttFloat);
	else if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 || rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
	{
		if( lctx->type.dataType.IsIntegerType() || rctx->type.dataType.IsIntegerType() )
			to.SetTokenType(ttInt64);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt64);
	}
	else
	{
		if( lctx->type.dataType.IsIntegerType() || rctx->type.dataType.IsIntegerType() ||
			lctx->type.dataType.IsEnumType() || rctx->type.dataType.IsEnumType() )
			to.SetTokenType(ttInt);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt);
		else if( lctx->type.dataType.IsBooleanType() || rctx->type.dataType.IsBooleanType() )
			to.SetTokenType(ttBool);
	}

	// If doing an operation with double constant and float variable, the constant should be converted to float
	if( (lctx->type.isConstant && lctx->type.dataType.IsDoubleType() && !rctx->type.isConstant && rctx->type.dataType.IsFloatType()) ||
		(rctx->type.isConstant && rctx->type.dataType.IsDoubleType() && !lctx->type.isConstant && lctx->type.dataType.IsFloatType()) )
		to.SetTokenType(ttFloat);

	// Is it an operation on signed values?
	bool signMismatch = false;
	if( !lctx->type.dataType.IsUnsignedType() || !rctx->type.dataType.IsUnsignedType() )
	{
		if( lctx->type.dataType.GetTokenType() == ttUInt64 )
		{
			if( !lctx->type.isConstant )
				signMismatch = true;
			else if( lctx->type.qwordValue & (I64(1)<<63) )
				signMismatch = true;
		}
		if( lctx->type.dataType.GetTokenType() == ttUInt )
		{
			if( !lctx->type.isConstant )
				signMismatch = true;
			else if( lctx->type.dwordValue & (1<<31) )
				signMismatch = true;
		}
		if( rctx->type.dataType.GetTokenType() == ttUInt64 )
		{
			if( !rctx->type.isConstant )
				signMismatch = true;
			else if( rctx->type.qwordValue & (I64(1)<<63) )
				signMismatch = true;
		}
		if( rctx->type.dataType.GetTokenType() == ttUInt )
		{
			if( !rctx->type.isConstant )
				signMismatch = true;
			else if( rctx->type.dwordValue & (1<<31) )
				signMismatch = true;
		}
	}

	// Check for signed/unsigned mismatch
	if( signMismatch )
		Warning(TXT_SIGNED_UNSIGNED_MISMATCH, node);

	// Do the actual conversion
	asCArray<int> reservedVars;
	rctx->bc.GetVarsUsed(reservedVars);

	if( lctx->type.dataType.IsReference() )
		ConvertToVariableNotIn(lctx, &reservedVars);
	if( rctx->type.dataType.IsReference() )
		ConvertToVariableNotIn(rctx, &reservedVars);

	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV);

	// Verify that the conversion was successful
	bool ok = true;
	if( !lctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
		Error(str.AddressOf(), node);
		ok = false;
	}

	if( !rctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
		Error(str.AddressOf(), node);
		ok = false;
	}

	if( !ok )
	{
		// It wasn't possible to get two valid operands, so we just return
		// a boolean result and let the compiler continue.
		ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
		return;
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;
	int op = node->tokenType;

	if( !isConstant )
	{
		if( to.IsBooleanType() )
		{
			int op = node->tokenType;
			if( op == ttEqual || op == ttNotEqual )
			{
				// Must convert to temporary variable, because we are changing the value before comparison
				ConvertToTempVariableNotIn(lctx, rctx);
				ConvertToTempVariableNotIn(rctx, lctx);
				ReleaseTemporaryVariable(lctx->type, &lctx->bc);
				ReleaseTemporaryVariable(rctx->type, &rctx->bc);

				// Make sure they are equal if not false
				lctx->bc.InstrWORD(asBC_NOT, lctx->type.stackOffset);
				rctx->bc.InstrWORD(asBC_NOT, rctx->type.stackOffset);

				MergeExprBytecode(ctx, lctx);
				MergeExprBytecode(ctx, rctx);
				ProcessDeferredParams(ctx);

				int a = AllocateVariable(asCDataType::CreatePrimitive(ttBool, true), true);
				int b = lctx->type.stackOffset;
				int c = rctx->type.stackOffset;

				if( op == ttEqual )
				{
					ctx->bc.InstrW_W(asBC_CMPi,b,c);
					ctx->bc.Instr(asBC_TZ);
					ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)a);
				}
				else if( op == ttNotEqual )
				{
					ctx->bc.InstrW_W(asBC_CMPi,b,c);
					ctx->bc.Instr(asBC_TNZ);
					ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)a);
				}

				ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, true), a, true);
			}
			else
			{
				// TODO: Use TXT_ILLEGAL_OPERATION_ON
				Error(TXT_ILLEGAL_OPERATION, node);
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), 0);
			}
		}
		else
		{
			ConvertToVariableNotIn(lctx, rctx);
			ConvertToVariableNotIn(rctx, lctx);
			ReleaseTemporaryVariable(lctx->type, &lctx->bc);
			ReleaseTemporaryVariable(rctx->type, &rctx->bc);

			MergeExprBytecode(ctx, lctx);
			MergeExprBytecode(ctx, rctx);
			ProcessDeferredParams(ctx);

			asEBCInstr iCmp = asBC_CMPi, iT = asBC_TZ;

			if( lctx->type.dataType.IsIntegerType() && lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				iCmp = asBC_CMPi;
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				iCmp = asBC_CMPu;
			else if( lctx->type.dataType.IsIntegerType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				iCmp = asBC_CMPi64;
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				iCmp = asBC_CMPu64;
			else if( lctx->type.dataType.IsFloatType() )
				iCmp = asBC_CMPf;
			else if( lctx->type.dataType.IsDoubleType() )
				iCmp = asBC_CMPd;
			else
				asASSERT(false);

			if( op == ttEqual )
				iT = asBC_TZ;
			else if( op == ttNotEqual )
				iT = asBC_TNZ;
			else if( op == ttLessThan )
				iT = asBC_TS;
			else if( op == ttLessThanOrEqual )
				iT = asBC_TNP;
			else if( op == ttGreaterThan )
				iT = asBC_TP;
			else if( op == ttGreaterThanOrEqual )
				iT = asBC_TNS;

			int a = AllocateVariable(asCDataType::CreatePrimitive(ttBool, true), true);
			int b = lctx->type.stackOffset;
			int c = rctx->type.stackOffset;

			ctx->bc.InstrW_W(iCmp, b, c);
			ctx->bc.Instr(iT);
			ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)a);

			ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, true), a, true);
		}
	}
	else
	{
		if( to.IsBooleanType() )
		{
			int op = node->tokenType;
			if( op == ttEqual || op == ttNotEqual )
			{
				// Make sure they are equal if not false
				if( lctx->type.dwordValue != 0 ) lctx->type.dwordValue = VALUE_OF_BOOLEAN_TRUE;
				if( rctx->type.dwordValue != 0 ) rctx->type.dwordValue = VALUE_OF_BOOLEAN_TRUE;

				asDWORD v = 0;
				if( op == ttEqual )
				{
					v = lctx->type.intValue - rctx->type.intValue;
					if( v == 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;
				}
				else if( op == ttNotEqual )
				{
					v = lctx->type.intValue - rctx->type.intValue;
					if( v != 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;
				}

				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), v);
			}
			else
			{
				// TODO: Use TXT_ILLEGAL_OPERATION_ON
				Error(TXT_ILLEGAL_OPERATION, node);
			}
		}
		else
		{
			int i = 0;
			if( lctx->type.dataType.IsIntegerType() && lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				int v = lctx->type.intValue - rctx->type.intValue;
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				asDWORD v1 = lctx->type.dwordValue;
				asDWORD v2 = rctx->type.dwordValue;
				if( v1 < v2 ) i = -1;
				if( v1 > v2 ) i = 1;
			}
			else if( lctx->type.dataType.IsIntegerType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				asINT64 v = asINT64(lctx->type.qwordValue) - asINT64(rctx->type.qwordValue);
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				asQWORD v1 = lctx->type.qwordValue;
				asQWORD v2 = rctx->type.qwordValue;
				if( v1 < v2 ) i = -1;
				if( v1 > v2 ) i = 1;
			}
			else if( lctx->type.dataType.IsFloatType() )
			{
				float v = lctx->type.floatValue - rctx->type.floatValue;
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsDoubleType() )
			{
				double v = lctx->type.doubleValue - rctx->type.doubleValue;
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}


			if( op == ttEqual )
				i = (i == 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
			else if( op == ttNotEqual )
				i = (i != 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
			else if( op == ttLessThan )
				i = (i < 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
			else if( op == ttLessThanOrEqual )
				i = (i <= 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
			else if( op == ttGreaterThan )
				i = (i > 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
			else if( op == ttGreaterThanOrEqual )
				i = (i >= 0 ? VALUE_OF_BOOLEAN_TRUE : 0);

			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), i);
		}
	}
}

void asCCompiler::PushVariableOnStack(asSExprContext *ctx, bool asReference)
{
	// Put the result on the stack
	ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
	if( asReference )
		ctx->type.dataType.MakeReference(true);
	else
	{
		if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			ctx->bc.Instr(asBC_RDS4);
		else
			ctx->bc.Instr(asBC_RDS8);
	}
}

void asCCompiler::CompileBooleanOperator(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	// Both operands must be booleans
	asCDataType to;
	to.SetTokenType(ttBool);

	// Do the actual conversion
	asCArray<int> reservedVars;
	rctx->bc.GetVarsUsed(reservedVars);
	lctx->bc.GetVarsUsed(reservedVars);
	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, &reservedVars);

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsBooleanType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format().AddressOf(), "bool");
		Error(str.AddressOf(), node);
		// Force the conversion to allow compilation to proceed
		lctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
	}

	if( !rctx->type.dataType.IsBooleanType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format().AddressOf(), "bool");
		Error(str.AddressOf(), node);
		// Force the conversion to allow compilation to proceed
		rctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

	ctx->type.Set(asCDataType::CreatePrimitive(ttBool, true));

	// What kind of operator is it?
	int op = node->tokenType;
	if( op == ttXor )
	{
		if( !isConstant )
		{
			// Must convert to temporary variable, because we are changing the value before comparison
			ConvertToTempVariableNotIn(lctx, rctx);
			ConvertToTempVariableNotIn(rctx, lctx);
			ReleaseTemporaryVariable(lctx->type, &lctx->bc);
			ReleaseTemporaryVariable(rctx->type, &rctx->bc);

			// Make sure they are equal if not false
			lctx->bc.InstrWORD(asBC_NOT, lctx->type.stackOffset);
			rctx->bc.InstrWORD(asBC_NOT, rctx->type.stackOffset);

			MergeExprBytecode(ctx, lctx);
			MergeExprBytecode(ctx, rctx);
			ProcessDeferredParams(ctx);

			int a = AllocateVariable(ctx->type.dataType, true);
			int b = lctx->type.stackOffset;
			int c = rctx->type.stackOffset;

			ctx->bc.InstrW_W_W(asBC_BXOR,a,b,c);

			ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, true), a, true);
		}
		else
		{
			// Make sure they are equal if not false
#if AS_SIZEOF_BOOL == 1
			if( lctx->type.byteValue != 0 ) lctx->type.byteValue = VALUE_OF_BOOLEAN_TRUE;
			if( rctx->type.byteValue != 0 ) rctx->type.byteValue = VALUE_OF_BOOLEAN_TRUE;

			asBYTE v = 0;
			v = lctx->type.byteValue - rctx->type.byteValue;
			if( v != 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;

			ctx->type.isConstant = true;
			ctx->type.byteValue = v;
#else
			if( lctx->type.dwordValue != 0 ) lctx->type.dwordValue = VALUE_OF_BOOLEAN_TRUE;
			if( rctx->type.dwordValue != 0 ) rctx->type.dwordValue = VALUE_OF_BOOLEAN_TRUE;

			asDWORD v = 0;
			v = lctx->type.intValue - rctx->type.intValue;
			if( v != 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;

			ctx->type.isConstant = true;
			ctx->type.dwordValue = v;
#endif
		}
	}
	else if( op == ttAnd ||
			 op == ttOr )
	{
		if( !isConstant )
		{
			// If or-operator and first value is 1 the second value shouldn't be calculated
			// if and-operator and first value is 0 the second value shouldn't be calculated
			ConvertToVariable(lctx);
			ReleaseTemporaryVariable(lctx->type, &lctx->bc);
			MergeExprBytecode(ctx, lctx);

			int offset = AllocateVariable(asCDataType::CreatePrimitive(ttBool, false), true);

			int label1 = nextLabel++;
			int label2 = nextLabel++;
			if( op == ttAnd )
			{
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, lctx->type.stackOffset);
				ctx->bc.Instr(asBC_ClrHi);
				ctx->bc.InstrDWORD(asBC_JNZ, label1);
				ctx->bc.InstrW_DW(asBC_SetV4, (asWORD)offset, 0);
				ctx->bc.InstrINT(asBC_JMP, label2);
			}
			else if( op == ttOr )
			{
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, lctx->type.stackOffset);
				ctx->bc.Instr(asBC_ClrHi);
				ctx->bc.InstrDWORD(asBC_JZ, label1);
#if AS_SIZEOF_BOOL == 1
				ctx->bc.InstrSHORT_B(asBC_SetV1, (short)offset, VALUE_OF_BOOLEAN_TRUE);
#else
				ctx->bc.InstrSHORT_DW(asBC_SetV4, (short)offset, VALUE_OF_BOOLEAN_TRUE);
#endif
				ctx->bc.InstrINT(asBC_JMP, label2);
			}

			ctx->bc.Label((short)label1);
			ConvertToVariable(rctx);
			ReleaseTemporaryVariable(rctx->type, &rctx->bc);
			rctx->bc.InstrW_W(asBC_CpyVtoV4, offset, rctx->type.stackOffset);
			MergeExprBytecode(ctx, rctx);
			ctx->bc.Label((short)label2);

			ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, false), offset, true);
		}
		else
		{
#if AS_SIZEOF_BOOL == 1
			asBYTE v = 0;
			if( op == ttAnd )
				v = lctx->type.byteValue && rctx->type.byteValue;
			else if( op == ttOr )
				v = lctx->type.byteValue || rctx->type.byteValue;

			// Remember the result
			ctx->type.isConstant = true;
			ctx->type.byteValue = v;
#else
			asDWORD v = 0;
			if( op == ttAnd )
				v = lctx->type.dwordValue && rctx->type.dwordValue;
			else if( op == ttOr )
				v = lctx->type.dwordValue || rctx->type.dwordValue;

			// Remember the result
			ctx->type.isConstant = true;
			ctx->type.dwordValue = v;
#endif
		}
	}
}

void asCCompiler::CompileOperatorOnHandles(asCScriptNode *node, asSExprContext *lctx, asSExprContext *rctx, asSExprContext *ctx)
{
	// Process the property accessor as get
	ProcessPropertyGetAccessor(lctx, node);
	ProcessPropertyGetAccessor(rctx, node);

	// Make sure lctx doesn't end up with a variable used in rctx
	if( lctx->type.isTemporary && rctx->bc.IsVarUsed(lctx->type.stackOffset) )
	{
		asCArray<int> vars;
		rctx->bc.GetVarsUsed(vars);
		int offset = AllocateVariable(lctx->type.dataType, true);
		rctx->bc.ExchangeVar(lctx->type.stackOffset, offset);
		ReleaseTemporaryVariable(offset, 0);
	}

	// Warn if not both operands are explicit handles
	if( (node->tokenType == ttEqual || node->tokenType == ttNotEqual) &&
		((!lctx->type.isExplicitHandle && !(lctx->type.dataType.GetObjectType() && (lctx->type.dataType.GetObjectType()->flags & asOBJ_IMPLICIT_HANDLE))) ||
		 (!rctx->type.isExplicitHandle && !(rctx->type.dataType.GetObjectType() && (rctx->type.dataType.GetObjectType()->flags & asOBJ_IMPLICIT_HANDLE)))) )
	{
		Warning(TXT_HANDLE_COMPARISON, node);
	}

	// Implicitly convert null to the other type
	asCDataType to;
	if( lctx->type.IsNullConstant() )
		to = rctx->type.dataType;
	else if( rctx->type.IsNullConstant() )
		to = lctx->type.dataType;
	else
	{
		// TODO: Use the common base type
		to = lctx->type.dataType;
	}

	// Need to pop the value if it is a null constant
	if( lctx->type.IsNullConstant() )
		lctx->bc.Pop(AS_PTR_SIZE);
	if( rctx->type.IsNullConstant() )
		rctx->bc.Pop(AS_PTR_SIZE);

	// Convert both sides to explicit handles
	to.MakeHandle(true);
	to.MakeReference(false);

	// Do the conversion
	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV);

	// Both operands must be of the same type

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
		Error(str.AddressOf(), node);
	}

	if( !rctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format().AddressOf(), to.Format().AddressOf());
		Error(str.AddressOf(), node);
	}

	ctx->type.Set(asCDataType::CreatePrimitive(ttBool, true));

	int op = node->tokenType;
	if( op == ttEqual || op == ttNotEqual || op == ttIs || op == ttNotIs )
	{
		// If the object handle already is in a variable we must manually pop it from the stack
		if( lctx->type.isVariable )
			lctx->bc.Pop(AS_PTR_SIZE);
		if( rctx->type.isVariable )
			rctx->bc.Pop(AS_PTR_SIZE);

		// TODO: optimize: Treat the object handles as two integers, i.e. don't do REFCPY
		ConvertToVariableNotIn(lctx, rctx);
		ConvertToVariable(rctx);

		MergeExprBytecode(ctx, lctx);
		MergeExprBytecode(ctx, rctx);

		int a = AllocateVariable(ctx->type.dataType, true);
		int b = lctx->type.stackOffset;
		int c = rctx->type.stackOffset;

		// TODO: When saving the bytecode we must be able to determine that this is 
		//       a comparison with a pointer, so that the instruction can be adapted 
		//       to the pointer size on the platform that will execute it.
#ifdef AS_64BIT_PTR
		ctx->bc.InstrW_W(asBC_CMPi64, b, c);
#else
		ctx->bc.InstrW_W(asBC_CMPi, b, c);
#endif

		if( op == ttEqual || op == ttIs )
			ctx->bc.Instr(asBC_TZ);
		else if( op == ttNotEqual || op == ttNotIs )
			ctx->bc.Instr(asBC_TNZ);

		ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)a);

		ctx->type.SetVariable(asCDataType::CreatePrimitive(ttBool, true), a, true);

		ReleaseTemporaryVariable(lctx->type, &ctx->bc);
		ReleaseTemporaryVariable(rctx->type, &ctx->bc);
		ProcessDeferredParams(ctx);
	}
	else
	{
		// TODO: Use TXT_ILLEGAL_OPERATION_ON
		Error(TXT_ILLEGAL_OPERATION, node);
	}
}


void asCCompiler::PerformFunctionCall(int funcId, asSExprContext *ctx, bool isConstructor, asCArray<asSExprContext*> *args, asCObjectType *objType, bool useVariable, int varOffset, int funcPtrVar)
{
	asCScriptFunction *descr = builder->GetFunctionDescription(funcId);

	// Check if the function is private
	if( descr->isPrivate && descr->GetObjectType() != outFunc->GetObjectType() )
	{
		asCString msg;
		msg.Format(TXT_PRIVATE_METHOD_CALL_s, descr->GetDeclarationStr().AddressOf());
		Error(msg.AddressOf(), ctx->exprNode);
	}

	int argSize = descr->GetSpaceNeededForArguments();

	if( descr->objectType && descr->returnType.IsReference() && 
		!ctx->type.isVariable && (ctx->type.dataType.IsObjectHandle() || ctx->type.dataType.SupportHandles()) &&
		!(ctx->type.dataType.GetObjectType()->GetFlags() & asOBJ_SCOPED) )
	{
		// The class method we're calling is returning a reference, which may be to a member of the object.
		// In order to guarantee the lifetime of the reference, we must hold a local reference to the object.
		// TODO: optimize: This can be avoided for local variables (non-handles) as they have a well defined life time
		int tempRef = AllocateVariable(ctx->type.dataType, true);
		ctx->bc.InstrSHORT(asBC_PSF, tempRef);
		ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetObjectType());

		// Add the release of this reference, as a deferred expression
		asSDeferredParam deferred;
		deferred.origExpr = 0;
		deferred.argInOutFlags = asTM_INREF;
		deferred.argNode = 0;
		deferred.argType.SetVariable(ctx->type.dataType, tempRef, true);

		ctx->deferredParams.PushLast(deferred);
	}

	ctx->type.Set(descr->returnType);

	if( isConstructor )
	{
		// Sometimes the value types are allocated on the heap,  
		// which is when this way of constructing them is used.

		asASSERT(useVariable == false);

		ctx->bc.Alloc(asBC_ALLOC, objType, descr->id, argSize+AS_PTR_SIZE);

		// The instruction has already moved the returned object to the variable
		ctx->type.Set(asCDataType::CreatePrimitive(ttVoid, false));

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, false);

		ProcessDeferredParams(ctx);

		return;
	}
	else if( descr->funcType == asFUNC_IMPORTED )
		ctx->bc.Call(asBC_CALLBND , descr->id, argSize + (descr->objectType ? AS_PTR_SIZE : 0));
	// TODO: Maybe we need two different byte codes
	else if( descr->funcType == asFUNC_INTERFACE || descr->funcType == asFUNC_VIRTUAL )
		ctx->bc.Call(asBC_CALLINTF, descr->id, argSize + (descr->objectType ? AS_PTR_SIZE : 0));
	else if( descr->funcType == asFUNC_SCRIPT )
		ctx->bc.Call(asBC_CALL    , descr->id, argSize + (descr->objectType ? AS_PTR_SIZE : 0));
	else if( descr->funcType == asFUNC_SYSTEM )
		ctx->bc.Call(asBC_CALLSYS , descr->id, argSize + (descr->objectType ? AS_PTR_SIZE : 0));
	else if( descr->funcType == asFUNC_FUNCDEF )
		ctx->bc.CallPtr(asBC_CallPtr, funcPtrVar, argSize);

	if( ctx->type.dataType.IsObject() && !descr->returnType.IsReference() )
	{
		int returnOffset = 0;

		if( useVariable )
		{
			// Use the given variable
			returnOffset = varOffset;
			ctx->type.SetVariable(descr->returnType, returnOffset, false);
		}
		else
		{
			// Allocate a temporary variable for the returned object
			// The returned object will actually be allocated on the heap, so
			// we must force the allocation of the variable to do the same
			returnOffset = AllocateVariable(descr->returnType, true, true);
			ctx->type.SetVariable(descr->returnType, returnOffset, true);
		}

		ctx->type.dataType.MakeReference(true);

		// Move the pointer from the object register to the temporary variable
		ctx->bc.InstrSHORT(asBC_STOREOBJ, (short)returnOffset);

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, false);

		ProcessDeferredParams(ctx);

		ctx->bc.InstrSHORT(asBC_PSF, (short)returnOffset);
	}
	else if( descr->returnType.IsReference() )
	{
		asASSERT(useVariable == false);

		// We cannot clean up the arguments yet, because the
		// reference might be pointing to one of them.

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, true);

		// Do not process the output parameters yet, because it
		// might invalidate the returned reference

		if( descr->returnType.IsPrimitive() )
			ctx->type.Set(descr->returnType);
		else
		{
			ctx->bc.Instr(asBC_PshRPtr);
			if( descr->returnType.IsObject() && !descr->returnType.IsObjectHandle() )
			{
				// We are getting the pointer to the object
				// not a pointer to a object variable
				ctx->type.dataType.MakeReference(false);
			}
		}
	}
	else
	{
		asASSERT(useVariable == false);

		if( descr->returnType.GetSizeInMemoryBytes() )
		{
			// Allocate a temporary variable to hold the value, but make sure 
			// the temporary variable isn't used in any of the deferred arguments
			asCArray<int> vars;
			for( asUINT n = 0; args && n < args->GetLength(); n++ )
			{
				asSExprContext *expr = (*args)[n]->origExpr;
				if( expr )
					expr->bc.GetVarsUsed(vars);
			}
			int offset = AllocateVariableNotIn(descr->returnType, true, &vars);

			ctx->type.SetVariable(descr->returnType, offset, true);

			// Move the value from the return register to the variable
			if( descr->returnType.GetSizeOnStackDWords() == 1 )
				ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)offset);
			else if( descr->returnType.GetSizeOnStackDWords() == 2 )
				ctx->bc.InstrSHORT(asBC_CpyRtoV8, (short)offset);
		}
		else
			ctx->type.Set(descr->returnType);

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, false);

		ProcessDeferredParams(ctx);
	}
}

// This only merges the bytecode, but doesn't modify the type of the final context
void asCCompiler::MergeExprBytecode(asSExprContext *before, asSExprContext *after)
{
	before->bc.AddCode(&after->bc);

	for( asUINT n = 0; n < after->deferredParams.GetLength(); n++ )
	{
		before->deferredParams.PushLast(after->deferredParams[n]);
		after->deferredParams[n].origExpr = 0;
	}

	after->deferredParams.SetLength(0);
}

// This merges both bytecode and the type of the final context
void asCCompiler::MergeExprBytecodeAndType(asSExprContext *before, asSExprContext *after)
{
	MergeExprBytecode(before, after);

	before->type            = after->type;
	before->property_get    = after->property_get;
	before->property_set    = after->property_set;
	before->property_const  = after->property_const;
	before->property_handle = after->property_handle;
	before->property_ref    = after->property_ref;
	before->property_arg    = after->property_arg;
	before->exprNode        = after->exprNode;

	after->property_arg = 0;

	// Do not copy the origExpr member
}

void asCCompiler::FilterConst(asCArray<int> &funcs)
{
	if( funcs.GetLength() == 0 ) return;

	// This is only done for object methods
	asCScriptFunction *desc = builder->GetFunctionDescription(funcs[0]);
	if( desc->objectType == 0 ) return;

	// Check if there are any non-const matches
	asUINT n;
	bool foundNonConst = false;
	for( n = 0; n < funcs.GetLength(); n++ )
	{
		desc = builder->GetFunctionDescription(funcs[n]);
		if( !desc->isReadOnly )
		{
			foundNonConst = true;
			break;
		}
	}

	if( foundNonConst )
	{
		// Remove all const methods
		for( n = 0; n < funcs.GetLength(); n++ )
		{
			desc = builder->GetFunctionDescription(funcs[n]);
			if( desc->isReadOnly )
			{
				if( n == funcs.GetLength() - 1 )
					funcs.PopLast();
				else
					funcs[n] = funcs.PopLast();

				n--;
			}
		}
	}
}

END_AS_NAMESPACE



