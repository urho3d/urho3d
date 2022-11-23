/*
   AngelCode Scripting Library
   Copyright (c) 2003-2021 Andreas Jonsson

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

// Modified for Urho3D

//
// as_compiler.cpp
//
// The class that does the actual compilation of the functions
//

#include <math.h> // fmodf() pow()

#include "as_config.h"

#ifndef AS_NO_COMPILER

#include "as_compiler.h"
#include "as_tokendef.h"
#include "as_tokenizer.h"
#include "as_string_util.h"
#include "as_texts.h"
#include "as_parser.h"
#include "as_debug.h"
#include "as_context.h"  // as_powi()

BEGIN_AS_NAMESPACE

//
// The calling convention rules for script functions:
// - If a class method returns a reference, the caller must guarantee the object pointer stays alive until the function returns, and the reference is no longer going to be used
// - If a class method doesn't return a reference, it must guarantee by itself that the this pointer stays alive during the function call. If no outside access is made, then the function is guaranteed to stay alive and nothing needs to be done
// - The object pointer is always passed as the first argument, position 0
// - If the function returns a value type the caller must reserve the memory for this and pass the pointer as the first argument after the object pointer
//





// TODO: I must correct the interpretation of a reference to objects in the compiler.
//       A reference should mean that a pointer to the object is on the stack.
//       No expression should end up as non-references to objects, as the actual object is
//       never put on the stack.
//       Local variables are declared as non-references, but the expression should be a reference to the variable.
//       Function parameters of called functions can also be non-references, but in that case it means the
//       object will be passed by value (currently on the heap, which will be moved to the application stack).
//
//       The compiler shouldn't use the asCDataType::IsReference. The datatype should always be stored as non-references.
//       Instead the compiler should keep track of references in TypeInfo, where it should also state how the reference
//       is currently stored, i.e. in variable, in register, on stack, etc.

asCCompiler::asCCompiler(asCScriptEngine *engine) : byteCode(engine)
{
	builder = 0;
	script = 0;

	variables = 0;
	isProcessingDeferredParams = false;
	isCompilingDefaultArg = false;
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

	// Clean up all the string constants that were allocated. By now the script
	// functions that were compiled successfully already holds their own references
	for (asUINT n = 0; n < usedStringConstants.GetLength(); n++)
		engine->stringFactory->ReleaseStringConstant(usedStringConstants[n]);
	usedStringConstants.SetLength(0);

	// Clean up the temporary script nodes that were allocated during compilation
	for (asUINT n = 0; n < nodesToFreeUponComplete.GetLength(); n++)
		nodesToFreeUponComplete[n]->Destroy(engine);
}

void asCCompiler::Reset(asCBuilder *in_builder, asCScriptCode *in_script, asCScriptFunction *in_outFunc)
{
	this->builder = in_builder;
	this->engine = in_builder->engine;
	this->script = in_script;
	this->outFunc = in_outFunc;

	hasCompileErrors = false;

	m_isConstructor       = false;
	m_isConstructorCalled = false;
	m_classDecl           = 0;
	m_globalVar           = 0;

	nextLabel = 0;
	breakLabels.SetLength(0);
	continueLabels.SetLength(0);

	numLambdas = 0;

	byteCode.ClearAll();
}

int asCCompiler::CompileDefaultConstructor(asCBuilder *in_builder, asCScriptCode *in_script, asCScriptNode *in_node, asCScriptFunction *in_outFunc, sClassDeclaration *in_classDecl)
{
	Reset(in_builder, in_script, in_outFunc);

	m_classDecl = in_classDecl;

	// Insert a JitEntry at the start of the function for JIT compilers
	byteCode.InstrPTR(asBC_JitEntry, 0);

	// Add a variable scope that might be needed to declare dummy variables
	// in case the member initialization refers to undefined symbols.
	AddVariableScope();

	// Initialize the class members that have no explicit expression first. This will allow the
	// base class' constructor to access these members without worry they will be uninitialized.
	// This can happen if the base class' constructor calls a method that is overridden by the derived class
	CompileMemberInitialization(&byteCode, true);

	// If the class is derived from another, then the base class' default constructor must be called
	if( outFunc->objectType->derivedFrom )
	{
		// Make sure the base class really has a default constructor
		if( outFunc->objectType->derivedFrom->beh.construct == 0 )
			Error(TEXT_BASE_DOESNT_HAVE_DEF_CONSTR, in_node);

		// Call the base class' default constructor
		byteCode.InstrSHORT(asBC_PSF, 0);
		byteCode.Instr(asBC_RDSPtr);
		byteCode.Call(asBC_CALL, outFunc->objectType->derivedFrom->beh.construct, AS_PTR_SIZE);
	}

	// Initialize the class members that explicit expressions afterwards. This allow the expressions
	// to access the base class members without worry they will be uninitialized
	CompileMemberInitialization(&byteCode, false);
	byteCode.OptimizeLocally(tempVariableOffsets);

	// If there are compile errors, there is no reason to build the final code
	if( hasCompileErrors )
		return -1;

	// Pop the object pointer from the stack
	byteCode.Ret(AS_PTR_SIZE);

	// Count total variable size
	int varSize = GetVariableOffset((int)variableAllocations.GetLength()) - 1;
	outFunc->scriptData->variableSpace = varSize;

	FinalizeFunction();

#ifdef AS_DEBUG
	// DEBUG: output byte code
	byteCode.DebugOutput(("__" + outFunc->objectType->name + "_" + outFunc->name + "__defconstr.txt").AddressOf(), in_outFunc);
#endif

	return 0;
}

int asCCompiler::CompileFactory(asCBuilder *in_builder, asCScriptCode *in_script, asCScriptFunction *in_outFunc)
{
	Reset(in_builder, in_script, in_outFunc);

	// Insert a JitEntry at the start of the function for JIT compilers
	byteCode.InstrPTR(asBC_JitEntry, 0);

	// Find the corresponding constructor
	asCDataType dt = asCDataType::CreateType(outFunc->returnType.GetTypeInfo(), false);
	int constructor = 0;
	for( unsigned int n = 0; n < dt.GetBehaviour()->factories.GetLength(); n++ )
	{
		if( dt.GetBehaviour()->factories[n] == outFunc->id )
		{
			constructor = dt.GetBehaviour()->constructors[n];
			break;
		}
	}

	// Allocate the class and instantiate it with the constructor
	int varOffset = AllocateVariable(dt, true);

	outFunc->scriptData->variableSpace = AS_PTR_SIZE;
	byteCode.InstrSHORT(asBC_PSF, (short)varOffset);

	// Copy all arguments to the top of the stack
	// TODO: runtime optimize: Might be interesting to have a specific instruction for copying all arguments
	int offset = (int)outFunc->GetSpaceNeededForArguments();
	for( int a = int(outFunc->parameterTypes.GetLength()) - 1; a >= 0; a-- )
	{
		if( !outFunc->parameterTypes[a].IsPrimitive() ||
			outFunc->parameterTypes[a].IsReference() )
		{
			offset -= AS_PTR_SIZE;
			byteCode.InstrSHORT(asBC_PshVPtr, short(-offset));
		}
		else
		{
			if( outFunc->parameterTypes[a].GetSizeOnStackDWords() == 2 )
			{
				offset -= 2;
				byteCode.InstrSHORT(asBC_PshV8, short(-offset));
			}
			else
			{
				offset -= 1;
				byteCode.InstrSHORT(asBC_PshV4, short(-offset));
			}
		}
	}

	int argDwords = (int)outFunc->GetSpaceNeededForArguments();
	byteCode.Alloc(asBC_ALLOC, dt.GetTypeInfo(), constructor, argDwords + AS_PTR_SIZE);

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

void asCCompiler::FinalizeFunction()
{
	TimeIt("asCCompiler::FinalizeFunction");

	asASSERT( outFunc->scriptData );
	asUINT n;

	// Finalize the bytecode
	byteCode.Finalize(tempVariableOffsets);

	// extract the try/catch info before object variable info, as 
	// some variable info is not needed if there are no try/catch blocks
	byteCode.ExtractTryCatchInfo(outFunc);

	byteCode.ExtractObjectVariableInfo(outFunc);

	// Compile the list of object variables for the exception handler and the bytecode serialization
	// Start with the variables allocated on the heap, and then the ones allocated on the stack
	for( n = 0; n < variableAllocations.GetLength(); n++ )
	{
		// The exception handler doesn't need to know about references, but the bytecode serialization must adjust the size of the pointer
		if( (variableAllocations[n].IsObject() || variableAllocations[n].IsFuncdef()) )
		{
			if( variableIsOnHeap[n] )
			{
				// For references, we just store a null pointer so the exception handler can identify that it shouldn't do anything, 
				// but the bytecode serializer can still understand that it needs to adjust the size of the pointer
				if (variableAllocations[n].IsReference())
					outFunc->scriptData->objVariableTypes.PushLast(0);
				else
					outFunc->scriptData->objVariableTypes.PushLast(variableAllocations[n].GetTypeInfo());
				outFunc->scriptData->objVariablePos.PushLast(GetVariableOffset(n));
			}
		}
	}
	outFunc->scriptData->objVariablesOnHeap = asUINT(outFunc->scriptData->objVariablePos.GetLength());
	for( n = 0; n < variableAllocations.GetLength(); n++ )
	{
		// The exception handler doesn't need to know about references, but the bytecode serialization must adjust the size of the pointer
		if( (variableAllocations[n].IsObject() || variableAllocations[n].IsFuncdef()) )
		{
			if( !variableIsOnHeap[n] )
			{
				// For references, we just store a null pointer so the exception handler can identify that it shouldn't do anything, 
				// but the bytecode serializer can still understand that it needs to adjust the size of the pointer
				if (variableAllocations[n].IsReference())
					outFunc->scriptData->objVariableTypes.PushLast(0);
				else
					outFunc->scriptData->objVariableTypes.PushLast(variableAllocations[n].GetTypeInfo());
				outFunc->scriptData->objVariablePos.PushLast(GetVariableOffset(n));
			}
		}
	}

	// Copy byte code to the function
	asASSERT( outFunc->scriptData->byteCode.GetLength() == 0 );
	outFunc->scriptData->byteCode.SetLength(byteCode.GetSize());
	byteCode.Output(outFunc->scriptData->byteCode.AddressOf());
	outFunc->AddReferences();
	outFunc->scriptData->stackNeeded = byteCode.largestStackUsed + outFunc->scriptData->variableSpace;
	outFunc->scriptData->lineNumbers = byteCode.lineNumbers;

	// Extract the script section indexes too if there are any entries that are different from the function's script section
	int lastIdx = outFunc->scriptData->scriptSectionIdx;
	for( n = 0; n < byteCode.sectionIdxs.GetLength(); n++ )
	{
		if( byteCode.sectionIdxs[n] != lastIdx )
		{
			lastIdx = byteCode.sectionIdxs[n];
			outFunc->scriptData->sectionIdxs.PushLast(byteCode.lineNumbers[n*2]);
			outFunc->scriptData->sectionIdxs.PushLast(lastIdx);
		}
	}
}

// internal
int asCCompiler::SetupParametersAndReturnVariable(asCArray<asCString> &parameterNames, asCScriptNode *func)
{
	int stackPos = 0;

	if( outFunc->objectType )
		stackPos = -AS_PTR_SIZE; // The first parameter is the pointer to the object

	// Add the first variable scope, which the parameters and
	// variables declared in the outermost statement block is
	// part of.
	AddVariableScope();

	bool isDestructor = false;
	asCDataType returnType;

	// Examine return type
	returnType = outFunc->returnType;

	// Check if this is a constructor or destructor
	if( returnType.GetTokenType() == ttVoid && outFunc->objectType )
	{
		if( outFunc->name[0] == '~' )
			isDestructor = true;
		else if( outFunc->objectType->name == outFunc->name )
			m_isConstructor = true;
	}

	// Is the return type allowed?
	if( returnType != asCDataType::CreatePrimitive(ttVoid, false) &&
		!returnType.CanBeInstantiated() &&
		!returnType.IsReference() &&
		!returnType.IsObjectHandle() )
	{
		// TODO: Hasn't this been validated by the builder already?
		asCString str;
		str.Format(TXT_RETURN_CANT_BE_s, returnType.Format(outFunc->nameSpace).AddressOf());
		Error(str, func);
	}

	// If the return type is a value type returned by value the address of the
	// location where the value will be stored is pushed on the stack before
	// the arguments
	if( !(isDestructor || m_isConstructor) && outFunc->DoesReturnOnStack() )
		stackPos -= AS_PTR_SIZE;

	asCVariableScope vs(0);

	// Declare parameters
	asUINT n;
	for( n = 0; n < parameterNames.GetLength(); n++ )
	{
		// Get the parameter type
		asCDataType &type = outFunc->parameterTypes[n];
		asETypeModifiers inoutFlag = n < outFunc->inOutFlags.GetLength() ? outFunc->inOutFlags[n] : asTM_NONE;

		// Is the data type allowed?
		// TODO: Hasn't this been validated by the builder already?
		if( (type.IsReference() && inoutFlag != asTM_INOUTREF && !type.CanBeInstantiated()) ||
			(!type.IsReference() && !type.CanBeInstantiated()) )
		{
			asCString parm = type.Format(outFunc->nameSpace);
			if( inoutFlag == asTM_INREF )
				parm += "in";
			else if( inoutFlag == asTM_OUTREF )
				parm += "out";

			asCString str;
			str.Format(TXT_PARAMETER_CANT_BE_s, parm.AddressOf());
			Error(str, func);
		}

		// If the parameter has a name then declare it as variable
		if( parameterNames[n] != "" )
		{
			asCString &name = parameterNames[n];
			if( vs.DeclareVariable(name.AddressOf(), type, stackPos, true) < 0 )
			{
				// TODO: It might be an out-of-memory too
				Error(TXT_PARAMETER_ALREADY_DECLARED, func);
			}

			// Add marker for variable declaration
			byteCode.VarDecl((int)outFunc->scriptData->variables.GetLength());
			outFunc->AddVariable(name, type, stackPos);
		}
		else
			vs.DeclareVariable("", type, stackPos, true);

		// Move to next parameter
		stackPos -= type.GetSizeOnStackDWords();
	}

	for( n = asUINT(vs.variables.GetLength()); n-- > 0; )
		variables->DeclareVariable(vs.variables[n]->name.AddressOf(), vs.variables[n]->type, vs.variables[n]->stackOffset, vs.variables[n]->onHeap);

	variables->DeclareVariable("return", returnType, stackPos, true);

	return stackPos;
}

void asCCompiler::CompileMemberInitialization(asCByteCode *bc, bool onlyDefaults)
{
	asASSERT( m_classDecl );

	// Initialize each member in the order they were declared
	for( asUINT n = 0; n < outFunc->objectType->properties.GetLength(); n++ )
	{
		asCObjectProperty *prop = outFunc->objectType->properties[n];

		// Check if the property has an initialization expression
		asCParser parser(builder);
		asCScriptNode *declNode = 0;
		asCScriptNode *initNode = 0;
		asCScriptCode *initScript = 0;
		for( asUINT m = 0; m < m_classDecl->propInits.GetLength(); m++ )
		{
			if( m_classDecl->propInits[m].name == prop->name )
			{
				declNode   = m_classDecl->propInits[m].declNode;
				initNode   = m_classDecl->propInits[m].initNode;
				initScript = m_classDecl->propInits[m].file;
				break;
			}
		}

		// If declNode is null, the property was inherited in which case
		// it was already initialized by the base class' constructor
		if( declNode )
		{
			if( initNode )
			{
				if( onlyDefaults )
					continue;

#ifdef AS_NO_MEMBER_INIT
				// Give an error as the initialization in the declaration has been disabled
				asCScriptCode *origScript = script;
				script = initScript;
				Error("Initialization of members in declaration is not supported", initNode);
				script = origScript;

				// Clear the initialization node
				initNode = 0;
				initScript = script;
#else
				// Re-parse the initialization expression as the parser now knows the types, which it didn't earlier
				int r = parser.ParseVarInit(initScript, initNode);
				if( r < 0 )
					continue;

				initNode = parser.GetScriptNode();
#endif
			}
			else
			{
				if( !onlyDefaults )
					continue;
			}

#ifdef AS_NO_MEMBER_INIT
			// The initialization will be done in the asCScriptObject constructor, so
			// here we should just validate that the member has a default constructor
			if( prop->type.IsObject() &&
				!prop->type.IsObjectHandle() &&
				(((prop->type.GetTypeInfo()->flags & asOBJ_REF) &&
				  prop->type.GetBehaviour()->factory == 0) ||
				 ((prop->type.GetTypeInfo()->flags & asOBJ_VALUE) &&
				  prop->type.GetBehaviour()->construct == 0 &&
				  !(prop->type.GetTypeInfo()->flags & asOBJ_POD))) )
			{
				// Class has no default factory/constructor.
				asCString str;
				// TODO: funcdef: asCDataType should have a GetTypeName()
				if( prop->type.GetFuncDef() )
					str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, prop->type.GetFuncDef()->GetName());
				else
					str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, prop->type.GetTypeInfo()->GetName());
				Error(str, declNode);
			}
#else
			// Temporarily set the script that is being compiled to where the member initialization is declared.
			// The script can be different when including mixin classes from a different script section
			asCScriptCode *origScript = script;
			script = initScript;

			// Add a line instruction with the position of the declaration
			LineInstr(bc, declNode->tokenPos);

			// Compile the initialization
			asQWORD constantValue;
			asCByteCode bcInit(engine);
			CompileInitialization(initNode, &bcInit, prop->type, declNode, prop->byteOffset, &constantValue, 2);
			bcInit.OptimizeLocally(tempVariableOffsets);
			bc->AddCode(&bcInit);

			script = origScript;
#endif
		}
	}
}

// Entry
int asCCompiler::CompileFunction(asCBuilder *in_builder, asCScriptCode *in_script, asCArray<asCString> &in_parameterNames, asCScriptNode *in_func, asCScriptFunction *in_outFunc, sClassDeclaration *in_classDecl)
{
	TimeIt("asCCompiler::CompileFunction");

	Reset(in_builder, in_script, in_outFunc);
	int buildErrors = builder->numErrors;

	int stackPos = SetupParametersAndReturnVariable(in_parameterNames, in_func);

	//--------------------------------------------
	// Compile the statement block

	if( m_isConstructor )
		m_classDecl = in_classDecl;

	// We need to parse the statement block now
	asCScriptNode *blockBegin;

	// If the function signature was implicit, e.g. virtual property accessor or
	// lambda function, then the received node already is the statement block
	if( in_func->nodeType != snStatementBlock )
		blockBegin = in_func->lastChild;
	else
		blockBegin = in_func;

	// TODO: memory: We can parse the statement block one statement at a time, thus save even more memory
	// TODO: optimize: For large functions, the parsing of the statement block can take a long time. Presumably because a lot of memory needs to be allocated
	asCParser parser(builder);
	int r = parser.ParseStatementBlock(script, blockBegin);
	if( r < 0 ) return -1;
	asCScriptNode *block = parser.GetScriptNode();

	// Reserve a label for the cleanup code
	nextLabel++;

	bool hasReturn;
	asCByteCode bc(engine);
	LineInstr(&bc, blockBegin->tokenPos);
	CompileStatementBlock(block, false, &hasReturn, &bc);
	LineInstr(&bc, blockBegin->tokenPos + blockBegin->tokenLength);

	// Make sure there is a return in all paths (if not return type is void)
	// Don't bother with this check if there are compiler errors, e.g. Unreachable code
	if( !hasCompileErrors && outFunc->returnType != asCDataType::CreatePrimitive(ttVoid, false) )
	{
		if( hasReturn == false )
			Error(TXT_NOT_ALL_PATHS_RETURN, blockBegin);
	}

	//------------------------------------------------
	// Concatenate the bytecode

	// Insert a JitEntry at the start of the function for JIT compilers
	byteCode.InstrPTR(asBC_JitEntry, 0);

	if( outFunc->objectType )
	{
		if( m_isConstructor )
		{
			if( outFunc->objectType->derivedFrom )
			{
				// Call the base class' default constructor unless called manually in the code
				if( !m_isConstructorCalled )
				{
					if( outFunc->objectType->derivedFrom->beh.construct )
					{
						// Initialize members without explicit expression first
						CompileMemberInitialization(&byteCode, true);

						// Call base class' constructor
						asCByteCode tmpBC(engine);
						tmpBC.InstrSHORT(asBC_PSF, 0);
						tmpBC.Instr(asBC_RDSPtr);
						tmpBC.Call(asBC_CALL, outFunc->objectType->derivedFrom->beh.construct, AS_PTR_SIZE);
						tmpBC.OptimizeLocally(tempVariableOffsets);
						byteCode.AddCode(&tmpBC);

						// Add the initialization of the members with explicit expressions
						CompileMemberInitialization(&byteCode, false);
					}
					else
						Error(TEXT_BASE_DOESNT_HAVE_DEF_CONSTR, blockBegin);
				}
				else
				{
					// Only initialize members that don't have an explicit expression
					// The members that are explicitly initialized will be initialized after the call to base class' constructor
					CompileMemberInitialization(&byteCode, true);
				}
			}
			else
			{
				// Add the initialization of the members
				CompileMemberInitialization(&byteCode, true);
				CompileMemberInitialization(&byteCode, false);
			}
		}
	}

	// Add the code for the statement block
	byteCode.AddCode(&bc);

	// Count total variable size
	int varSize = GetVariableOffset((int)variableAllocations.GetLength()) - 1;
	outFunc->scriptData->variableSpace = varSize;

	// Deallocate all local variables
	int n;
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

	// Check if the number of labels in the functions isn't too many to be handled
	if( nextLabel >= (1<<15) )
		Error(TXT_TOO_MANY_JUMP_LABELS, in_func);

	// If there are compile errors, there is no reason to build the final code
	if( hasCompileErrors || builder->numErrors != buildErrors )
		return -1;

	// At this point there should be no variables allocated
	asASSERT(variableAllocations.GetLength() == freeVariables.GetLength());

	// Remove the variable scope
	RemoveVariableScope();

	byteCode.Ret(-stackPos);

	FinalizeFunction();

#ifdef AS_DEBUG
	// DEBUG: output byte code
	if( outFunc->objectType )
		byteCode.DebugOutput(("__" + outFunc->objectType->name + "_" + outFunc->name + ".txt").AddressOf(), in_outFunc);
	else
		byteCode.DebugOutput(("__" + outFunc->name + ".txt").AddressOf(), in_outFunc);
#endif

	return 0;
}

int asCCompiler::CallCopyConstructor(asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc, asCExprContext *arg, asCScriptNode *node, bool isGlobalVar, bool derefDest)
{
	if( !type.IsObject() )
		return 0;

	// CallCopyConstructor should not be called for object handles.
	asASSERT( !type.IsObjectHandle() );

	asCArray<asCExprContext*> args;
	args.PushLast(arg);

	// The reference parameter must be pushed on the stack
	asASSERT( arg->type.dataType.GetTypeInfo() == type.GetTypeInfo() );

	// Since we're calling the copy constructor, we have to trust the function to not do
	// anything stupid otherwise we will just enter a loop, as we try to make temporary
	// copies of the argument in order to guarantee safety.


	if( type.GetTypeInfo()->flags & asOBJ_REF )
	{
		asCExprContext ctx(engine);

		int func = 0;
		asSTypeBehaviour *beh = type.GetBehaviour();
		if( beh ) func = beh->copyfactory;

		if( func > 0 )
		{
			if( !isGlobalVar )
			{
				// Call factory and store the handle in the given variable
				PerformFunctionCall(func, &ctx, false, &args, CastToObjectType(type.GetTypeInfo()), true, offset);

				// Pop the reference left by the function call
				ctx.bc.Instr(asBC_PopPtr);
			}
			else
			{
				// Call factory
				PerformFunctionCall(func, &ctx, false, &args, CastToObjectType(type.GetTypeInfo()));

				// Store the returned handle in the global variable
				ctx.bc.Instr(asBC_RDSPtr);
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				ctx.bc.InstrPTR(asBC_REFCPY, type.GetTypeInfo());
				ctx.bc.Instr(asBC_PopPtr);
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
				if( derefDest )
				{
					// The variable is a reference to the real location, so we need to dereference it
					bc->Instr(asBC_RDSPtr);
				}
			}

			asCExprContext ctx(engine);
			PerformFunctionCall(func, &ctx, isObjectOnHeap, &args, CastToObjectType(type.GetTypeInfo()));

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
	str.Format(TXT_NO_COPY_CONSTRUCTOR_FOR_s, type.GetTypeInfo()->GetName());
	Error(str, node);

	return -1;
}

int asCCompiler::CallDefaultConstructor(const asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc, asCScriptNode *node, int isVarGlobOrMem, bool derefDest)
{
	if( !type.IsObject() || type.IsObjectHandle() )
		return 0;

	if( type.GetTypeInfo()->flags & asOBJ_REF )
	{
		asCExprContext ctx(engine);
		ctx.exprNode = node;

		int func = 0;
		asSTypeBehaviour *beh = type.GetBehaviour();
		if( beh )
		{
			func = beh->factory;

			// If no trivial default factory is found, look for a factory where all params have default args
			if( func == 0 )
			{
				for( asUINT n = 0; n < beh->factories.GetLength(); n++ )
				{
					asCScriptFunction *f = engine->scriptFunctions[beh->factories[n]];
					if( f->defaultArgs.GetLength() == f->parameterTypes.GetLength() &&
						f->defaultArgs[0] != 0 )
					{
						func = beh->factories[n];
						break;
					}
				}
			}
		}

		if( func > 0 )
		{
			asCArray<asCExprContext *> args;
			asCScriptFunction *f = engine->scriptFunctions[func];
			if( f->parameterTypes.GetLength() )
			{
				// Add the default values for arguments not explicitly supplied
				CompileDefaultAndNamedArgs(node, args, func, CastToObjectType(type.GetTypeInfo()));

				PrepareFunctionCall(func, &ctx.bc, args);

				MoveArgsToStack(func, &ctx.bc, args, false);
			}

			if( isVarGlobOrMem == 0 )
			{
				// Call factory and store the handle in the given variable
				PerformFunctionCall(func, &ctx, false, &args, CastToObjectType(type.GetTypeInfo()), true, offset);

				// Pop the reference left by the function call
				ctx.bc.Instr(asBC_PopPtr);
			}
			else
			{
				// Call factory
				PerformFunctionCall(func, &ctx, false, &args, CastToObjectType(type.GetTypeInfo()));

				// TODO: runtime optimize: Should have a way of storing the object pointer directly to the destination
				//                         instead of first storing it in a local variable and then copying it to the
				//                         destination.

				if( !(type.GetTypeInfo()->flags & asOBJ_SCOPED) )
				{
					// Only dereference the variable if not a scoped type
					ctx.bc.Instr(asBC_RDSPtr);
				}

				if( isVarGlobOrMem == 1 )
				{
					// Store the returned handle in the global variable
					ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				}
				else
				{
					// Store the returned handle in the class member
					ctx.bc.InstrSHORT(asBC_PSF, 0);
					ctx.bc.Instr(asBC_RDSPtr);
					ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
				}

				if( type.GetTypeInfo()->flags & asOBJ_SCOPED )
				{
					// For scoped typed we must move the reference from the local
					// variable rather than copy it as there is no AddRef behaviour
					ctx.bc.InstrSHORT_DW(asBC_COPY, AS_PTR_SIZE, asTYPEID_OBJHANDLE | engine->GetTypeIdFromDataType(type));

					// Clear the local variable so the reference isn't released
					ctx.bc.InstrSHORT(asBC_ClrVPtr, ctx.type.stackOffset);
				}
				else
				{
					if( type.IsFuncdef() )
						ctx.bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
					else
						ctx.bc.InstrPTR(asBC_REFCPY, type.GetTypeInfo());
				}
				ctx.bc.Instr(asBC_PopPtr);
				ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
			}

			bc->AddCode(&ctx.bc);

			// Cleanup
			for( asUINT n = 0; n < args.GetLength(); n++ )
				if( args[n] )
				{
					asDELETE(args[n], asCExprContext);
				}

			return 0;
		}
	}
	else
	{
		asCExprContext ctx(engine);
		ctx.exprNode = node;

		asSTypeBehaviour *beh = type.GetBehaviour();

		int func = 0;
		if( beh )
		{
			func = beh->construct;

			// If no trivial default constructor is found, look for a constructor where all params have default args
			if( func == 0 )
			{
				for( asUINT n = 0; n < beh->constructors.GetLength(); n++ )
				{
					asCScriptFunction *f = engine->scriptFunctions[beh->constructors[n]];
					if( f->defaultArgs.GetLength() == f->parameterTypes.GetLength() &&
						f->defaultArgs[0] != 0 )
					{
						func = beh->constructors[n];
						break;
					}
				}
			}
		}

		// Allocate and initialize with the default constructor
		if( func != 0 || (type.GetTypeInfo()->flags & asOBJ_POD) )
		{
			asCArray<asCExprContext *> args;
			asCScriptFunction *f = engine->scriptFunctions[func];
			if( f && f->parameterTypes.GetLength() )
			{
				// Add the default values for arguments not explicitly supplied
				CompileDefaultAndNamedArgs(node, args, func, CastToObjectType(type.GetTypeInfo()));

				PrepareFunctionCall(func, &ctx.bc, args);

				MoveArgsToStack(func, &ctx.bc, args, false);
			}

			if( !isObjectOnHeap )
			{
				if( isVarGlobOrMem == 0 )
				{
					// There is nothing to do if there is no function,
					// as the memory is already allocated on the stack
					if( func )
					{
						// Call the constructor as a normal function
						bc->InstrSHORT(asBC_PSF, (short)offset);
						if( derefDest )
							bc->Instr(asBC_RDSPtr);

						asCExprContext ctxCall(engine);
						PerformFunctionCall(func, &ctxCall, false, 0, CastToObjectType(type.GetTypeInfo()));
						bc->AddCode(&ctxCall.bc);

						// TODO: value on stack: This probably needs to be done in PerformFunctionCall
						// Mark the object as initialized
						bc->ObjInfo(offset, asOBJ_INIT);
					}
				}
				else if( isVarGlobOrMem == 2 )
				{
					// Only POD types can be allocated inline in script classes
					asASSERT( type.GetTypeInfo()->flags & asOBJ_POD );

					if( func )
					{
						// Call the constructor as a normal function
						bc->InstrSHORT(asBC_PSF, 0);
						bc->Instr(asBC_RDSPtr);
						bc->InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));

						asCExprContext ctxCall(engine);
						PerformFunctionCall(func, &ctxCall, false, 0, CastToObjectType(type.GetTypeInfo()));
						bc->AddCode(&ctxCall.bc);
					}
				}
				else
				{
					asASSERT( false );
				}
			}
			else
			{
				if( isVarGlobOrMem == 0 )
					bc->InstrSHORT(asBC_PSF, (short)offset);
				else if( isVarGlobOrMem == 1 )
					bc->InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
				else
				{
					bc->InstrSHORT(asBC_PSF, 0);
					bc->Instr(asBC_RDSPtr);
					bc->InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
				}

				if( (type.GetTypeInfo()->flags & asOBJ_TEMPLATE) )
				{
					asCScriptFunction *descr = engine->scriptFunctions[func];
					asASSERT( descr->funcType == asFUNC_SCRIPT );

					// Find the id of the real constructor and not the generated stub
					asUINT id = 0;
					asDWORD *funcBc = descr->scriptData->byteCode.AddressOf();
					while( funcBc )
					{
						if( (*(asBYTE*)funcBc) == asBC_CALLSYS )
						{
							id = asBC_INTARG(funcBc);
							break;
						}
						funcBc += asBCTypeSize[asBCInfo[*(asBYTE*)funcBc].type];
					}

					asASSERT( id );

					bc->InstrPTR(asBC_OBJTYPE, type.GetTypeInfo());
					bc->Alloc(asBC_ALLOC, type.GetTypeInfo(), id, AS_PTR_SIZE + AS_PTR_SIZE);
				}
				else
					bc->Alloc(asBC_ALLOC, type.GetTypeInfo(), func, AS_PTR_SIZE);
			}

			// Cleanup
			for( asUINT n = 0; n < args.GetLength(); n++ )
				if( args[n] )
				{
					asDELETE(args[n], asCExprContext);
				}

			return 0;
		}
	}

	// Class has no default factory/constructor.
	asCString str;
	str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, type.GetTypeInfo()->GetName());
	Error(str, node);

	return -1;
}

void asCCompiler::CallDestructor(asCDataType &type, int offset, bool isObjectOnHeap, asCByteCode *bc)
{
	if( !type.IsReference() )
	{
		// Call destructor for the data type
		if( type.IsObject() || type.IsFuncdef() )
		{
			// The null pointer doesn't need to be destroyed
			if( type.IsNullHandle() )
				return;

			// Nothing is done for list pattern types, as this is taken care of by the CompileInitList method
			if( type.GetTypeInfo()->flags & asOBJ_LIST_PATTERN )
				return;

			if( isObjectOnHeap || type.IsObjectHandle() )
			{
				// Free the memory
				if (type.IsFuncdef())
					bc->InstrW_PTR(asBC_FREE, (short)offset, &engine->functionBehaviours);
				else
					bc->InstrW_PTR(asBC_FREE, (short)offset, type.GetTypeInfo());
			}
			else
			{
				asASSERT( type.GetTypeInfo()->GetFlags() & asOBJ_VALUE );

				if( type.GetBehaviour()->destruct )
				{
					// Call the destructor as a regular function
					asCExprContext ctx(engine);
					ctx.bc.InstrSHORT(asBC_PSF, (short)offset);
					PerformFunctionCall(type.GetBehaviour()->destruct, &ctx);
					ctx.bc.OptimizeLocally(tempVariableOffsets);
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
	bc->Line(r, c, script->idx);
}

void asCCompiler::CompileStatementBlock(asCScriptNode *block, bool ownVariableScope, bool *hasReturn, asCByteCode *bc)
{
	*hasReturn = false;
	bool isFinished = false;
	bool hasUnreachableCode = false;
	bool hasReturnBefore = false;

	if( ownVariableScope )
	{
		bc->Block(true);
		AddVariableScope();
	}

	asCScriptNode *node = block->firstChild;
	while( node )
	{
#ifdef AS_DEBUG
		// Keep the current line in a variable so it will be easier
		// to determine where in a script an assert is occurring.
		int currentLine = 0;
		script->ConvertPosToRowCol(node->tokenPos, &currentLine, 0);
#endif

		if( !hasUnreachableCode && (*hasReturn || isFinished) )
		{
			// Empty statements don't count
			if( node->nodeType != snExpressionStatement || node->firstChild )
			{
				hasUnreachableCode = true;
				Warning(TXT_UNREACHABLE_CODE, node);
			}

			if( *hasReturn )
				hasReturnBefore = true;
		}

		if( node->nodeType == snBreak || node->nodeType == snContinue )
			isFinished = true;

		asCByteCode statement(engine);
		if( node->nodeType == snDeclaration )
			CompileDeclaration(node, &statement);
		else
			CompileStatement(node, hasReturn, &statement);

		// Ignore missing returns in unreachable code paths
		if( !(*hasReturn) && hasReturnBefore )
			*hasReturn = true;

		LineInstr(bc, node->tokenPos);
		bc->AddCode(&statement);

		if( !hasCompileErrors )
		{
			asASSERT( tempVariables.GetLength() == 0 );
			asASSERT( reservedVariables.GetLength() == 0 );
		}

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
int asCCompiler::CompileGlobalVariable(asCBuilder *in_builder, asCScriptCode *in_script, asCScriptNode *in_node, sGlobalVariableDescription *in_gvar, asCScriptFunction *in_outFunc)
{
	Reset(in_builder, in_script, in_outFunc);
	m_globalVar = in_gvar;

	// Add a variable scope (even though variables can't be declared)
	AddVariableScope();

	in_gvar->isPureConstant = false;

	// Parse the initialization nodes
	asCParser parser(builder);
	if (in_node)
	{
		int r = parser.ParseVarInit(in_script, in_node);
		if (r < 0)
			return r;

		in_node = parser.GetScriptNode();
	}

	asCExprContext compiledCtx(engine);
	bool preCompiled = false;
	if (in_gvar->datatype.IsAuto())
	{
		preCompiled = CompileAutoType(in_gvar->datatype, compiledCtx, in_node, in_gvar->declaredAtNode);
		if (!preCompiled)
		{
			// If it wasn't possible to determine the type from the expression then there
			// is no need to continue with the initialization. The error was already reported
			// in CompileAutoType.
			return -1;
		}
	}
	if( in_gvar->property == 0 )
	{
		in_gvar->property = builder->module->AllocateGlobalProperty(in_gvar->name.AddressOf(), in_gvar->datatype, in_gvar->ns);
		in_gvar->index = in_gvar->property->id;
	}

	// Compile the expression
	asCExprContext ctx(engine);
	asQWORD constantValue = 0;
	if( CompileInitialization(in_node, &ctx.bc, in_gvar->datatype, in_gvar->declaredAtNode, in_gvar->index, &constantValue, 1, preCompiled ? &compiledCtx : 0) )
	{
		// Should the variable be marked as pure constant?
		if( in_gvar->datatype.IsPrimitive() && in_gvar->datatype.IsReadOnly() )
		{
			in_gvar->isPureConstant = true;
			in_gvar->constantValue = constantValue;
		}
	}

	// Concatenate the bytecode
	int varSize = GetVariableOffset((int)variableAllocations.GetLength()) - 1;

	// Add information on the line number for the global variable
	size_t pos = 0;
	if( in_gvar->declaredAtNode )
		pos = in_gvar->declaredAtNode->tokenPos;
	else if( in_gvar->initializationNode )
		pos = in_gvar->initializationNode->tokenPos;
	LineInstr(&byteCode, pos);

	// Reserve space for all local variables
	outFunc->scriptData->variableSpace = varSize;

	ctx.bc.OptimizeLocally(tempVariableOffsets);

	byteCode.AddCode(&ctx.bc);

	// Deallocate variables in this block, in reverse order
	for( int n = (int)variables->variables.GetLength() - 1; n >= 0; --n )
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
	byteCode.DebugOutput(("___init_" + in_gvar->name + ".txt").AddressOf(), outFunc);
#endif

	return 0;
}

void asCCompiler::DetermineSingleFunc(asCExprContext *ctx, asCScriptNode *node)
{
	// Don't do anything if this is not a deferred global function
	if( !ctx->IsGlobalFunc() )
		return;

	// Determine the namespace
	asSNameSpace *ns = 0;
	asCString name = "";
	int pos = ctx->methodName.FindLast("::");
	if( pos >= 0 )
	{
		asCString nsName = ctx->methodName.SubString(0, pos+2);

		// Cut off the ::
		if( nsName.GetLength() > 2 )
			nsName.SetLength(nsName.GetLength()-2);

		ns = DetermineNameSpace(nsName);
		name = ctx->methodName.SubString(pos+2);
	}
	else
	{
		DetermineNameSpace("");
		name = ctx->methodName;
	}

	asCArray<int> funcs;
	if( ns )
		builder->GetFunctionDescriptions(name.AddressOf(), funcs, ns);

	// CompileVariableAccess should guarantee that at least one function is exists
	asASSERT( funcs.GetLength() > 0 );

	if( funcs.GetLength() > 1 )
	{
		asCString str;
		str.Format(TXT_MULTIPLE_MATCHING_SIGNATURES_TO_s, ctx->methodName.AddressOf());
		Error(str, node);

		// Fall through so the compiler can continue as if only one function was matching
	}

	// A shared object may not access global functions unless they too are shared (e.g. registered functions)
	if( !builder->GetFunctionDescription(funcs[0])->IsShared() &&
		outFunc->IsShared() )
	{
		asCString msg;
		msg.Format(TXT_SHARED_CANNOT_CALL_NON_SHARED_FUNC_s, builder->GetFunctionDescription(funcs[0])->GetDeclaration());
		Error(msg, node);

		// Fall through so the compiler can continue anyway
	}

	// Push the function pointer on the stack
	ctx->bc.InstrPTR(asBC_FuncPtr, builder->GetFunctionDescription(funcs[0]));
	ctx->type.Set(asCDataType::CreateType(engine->FindMatchingFuncdef(builder->GetFunctionDescription(funcs[0]), builder->module), false));
	ctx->type.dataType.MakeHandle(true);
	ctx->type.isExplicitHandle = true;
	ctx->methodName = "";
}

void asCCompiler::CompileInitAsCopy(asCDataType &dt, int offset, asCByteCode *bc, asCExprContext *arg, asCScriptNode *node, bool derefDestination)
{
	bool isObjectOnHeap = derefDestination ? false : IsVariableOnHeap(offset);

	// Use copy constructor if available.
	asCObjectType *ot = CastToObjectType(dt.GetTypeInfo());
	if(!dt.IsObjectHandle() && ot && (ot->beh.copyconstruct || ot->beh.copyfactory))
	{
		PrepareForAssignment(&dt, arg, node, true);
		int r = CallCopyConstructor(dt, offset, isObjectOnHeap, bc, arg, node, 0, derefDestination);
		if( r < 0 && tempVariables.Exists(offset) )
			Error(TXT_FAILED_TO_CREATE_TEMP_OBJ, node);
	}
	else
	{
		// TODO: Need to reserve variables, as the default constructor may need
		//       to allocate temporary variables to compute default args

		// Allocate and construct the temporary object before whatever is already in the bytecode
		asCByteCode tmpBC(engine);
		int r = CallDefaultConstructor(dt, offset, isObjectOnHeap, &tmpBC, node, 0, derefDestination);
		if( r < 0 )
		{
			if( tempVariables.Exists(offset) )
				Error(TXT_FAILED_TO_CREATE_TEMP_OBJ, node);
			return;
		}

		tmpBC.AddCode(bc);
		bc->AddCode(&tmpBC);

		// Assign the evaluated expression to the temporary variable
		PrepareForAssignment(&dt, arg, node, true);
		bc->AddCode(&arg->bc);

		// Call the opAssign method to assign the value to the temporary object
		dt.MakeReference(isObjectOnHeap);
		asCExprValue type;
		type.Set(dt);
		type.isTemporary = true;
		type.stackOffset = (short)offset;

		if( dt.IsObjectHandle() )
			type.isExplicitHandle = true;

		bc->InstrSHORT(asBC_PSF, (short)offset);
		if( derefDestination )
			bc->Instr(asBC_RDSPtr);

		r = PerformAssignment(&type, &arg->type, bc, node);
		if( r < 0 )
		{
			if( tempVariables.Exists(offset) )
				Error(TXT_FAILED_TO_CREATE_TEMP_OBJ, node);
			return;
		}

		// Pop the reference that was pushed on the stack if the result is an object
		if( type.dataType.IsObject() || type.dataType.IsFuncdef() )
			bc->Instr(asBC_PopPtr);

		// If the assignment operator returned an object by value it will
		// be in a temporary variable which we need to destroy now
		if( type.isTemporary && type.stackOffset != (short)offset )
			ReleaseTemporaryVariable(type.stackOffset, bc);

		// Release the original value too in case it is a temporary
		ReleaseTemporaryVariable(arg->type, bc);
	}
}

int asCCompiler::PrepareArgument(asCDataType *paramType, asCExprContext *ctx, asCScriptNode *node, bool isFunction, int refType, bool isMakingCopy)
{
	asCDataType param = *paramType;
	if( paramType->GetTokenType() == ttQuestion )
	{
		// The function is expecting a var type. If the argument is a function name, we must now decide which function it is
		DetermineSingleFunc(ctx, node);

		// Since the function is expecting a var type ?, then we don't want to convert the argument to anything else
		param = ctx->type.dataType;
		param.MakeHandle(ctx->type.isExplicitHandle || ctx->type.IsNullConstant());

		// Treat the void expression like a null handle when working with var types
		if( ctx->IsVoidExpression() )
			param = asCDataType::CreateNullHandle();

		// If value assign is disabled for reference types, then make
		// sure to always pass the handle to ? parameters
		if( builder->engine->ep.disallowValueAssignForRefType &&
			ctx->type.dataType.GetTypeInfo() && (ctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCOPED) )
		{
			param.MakeHandle(true);
		}

		param.MakeReference(paramType->IsReference());
		param.MakeReadOnly(paramType->IsReadOnly());
	}
	else
		param = *paramType;

	asCDataType dt = param;

	// Need to protect arguments by reference
	if( isFunction && dt.IsReference() )
	{
		// Allocate a temporary variable of the same type as the argument
		dt.MakeReference(false);

		int offset;
		if( refType == asTM_INREF )
		{
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// Add the type id as hidden arg if the parameter is a ? type
			if( paramType->GetTokenType() == ttQuestion )
			{
				asCByteCode tmpBC(engine);

				// Place the type id on the stack as a hidden parameter
				tmpBC.InstrDWORD(asBC_TYPEID, engine->GetTypeIdFromDataType(param));

				// Insert the code before the expression code
				tmpBC.AddCode(&ctx->bc);
				ctx->bc.AddCode(&tmpBC);
			}

			if( dt.IsPrimitive() )
			{
				// If the reference is const, then it is not necessary to make a copy if the value already is a variable
				// Even if the same variable is passed in another argument as non-const then there is no problem
				IsVariableInitialized(&ctx->type, node);

				if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);
				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true);

				if( !(param.IsReadOnly() && ctx->type.isVariable) )
					ConvertToTempVariable(ctx);

				PushVariableOnStack(ctx, true);
				ctx->type.dataType.MakeReadOnly(param.IsReadOnly());
			}
			else if( ctx->type.dataType.IsNullHandle() )
			{
				// Make sure the argument type can support handles (or is itself a handle)
				// Don't allow null handle to be converted to an object type of ASHANDLE here, that would require more logic to call the constructor (which should be handled in ImplicitConversion)
				if( (!dt.SupportHandles() && !dt.IsObjectHandle()) || (dt.GetTypeInfo() && (dt.GetTypeInfo()->GetFlags() & asOBJ_ASHANDLE)) )
				{
					asCString str;
					str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), param.Format(outFunc->nameSpace).AddressOf());
					Error(str, node);

					ctx->type.Set(param);
					return -1;
				}

				// Need to initialize a local temporary variable to
				// represent the null handle when passed as reference
				asASSERT( ctx->bc.GetLastInstr() == asBC_PshNull );
				ctx->bc.Instr(asBC_PopPtr);

				dt.MakeHandle(true);
				dt.MakeReadOnly(false);
				offset = AllocateVariableNotIn(dt, true, false, ctx);

				// Push the reference to the variable on the stack
				ctx->bc.InstrWORD(asBC_PSF, (short)offset);

				ctx->type.SetVariable(dt, offset, true);
				ctx->type.isExplicitHandle = true;
			}
			else
			{
				IsVariableInitialized(&ctx->type, node);

				if( !isMakingCopy )
				{
					// For parameters expecting a reference to a handle we need to make sure the argument
					// is really a handle, and not just a reference to the object. Do this check before the
					// implicit conversion so it can be treated correctly.
					if (dt.IsObjectHandle() && !ctx->type.dataType.IsObjectHandle())
					{
						// Make a refCopy into a local handle variable
						// Allocate a handle variable
						dt.MakeHandle(true);
						dt.MakeReadOnly(false);
						offset = AllocateVariableNotIn(dt, true, false, ctx);

						// Copy the handle
						Dereference(ctx, true);
						ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);
						if (ctx->type.dataType.IsFuncdef())
							ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
						else
							ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());
						ctx->bc.Instr(asBC_PopPtr);
						ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);

						// Release the original temporary variable
						if( ctx->type.isTemporary )
							ReleaseTemporaryVariable(ctx->type.stackOffset, &ctx->bc);

						ctx->type.SetVariable(dt, offset, true);
					}

					// Even though the parameter expects a reference, it is only meant to be
					// used as input value and doesn't have to refer to the actual object, so it
					// is OK to do an implicit conversion.
					ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true);
					if( !ctx->type.dataType.IsEqualExceptRefAndConst(param) )
					{
						asCString str;
						str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), param.Format(outFunc->nameSpace).AddressOf());
						Error(str, node);

						ctx->type.Set(param);
						return -1;
					}

					// The compiler must guarantee that the object stays alive during the execution
					// of the function, and it must also guarantee that the value isn't modified by
					// the function.

					// If the argument is a temporary local variable then it is safe to be passed to
					// the function as it is, since the local variable will stay alive, and since it
					// is temporary there is no side effect if the function modifies it.

					// If the parameter is read-only and therefore guaranteed not to be modified by the
					// function, then it is enough that the variable is local to guarantee the lifetime.
					if( !ctx->type.isTemporary && !(param.IsReadOnly() && (ctx->type.isVariable || ctx->type.isRefSafe)) )
					{
						if( ctx->type.dataType.IsFuncdef() || ((ctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && param.IsReadOnly() && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCOPED)) )
						{
							// Funcdefs only need an extra handle to guarantee the lifetime.

							// If the object is a reference type (except scoped reference types), and the
							// parameter is a const reference, then it is not necessary to make a copy of the
							// object. The compiler just needs to hold a handle to guarantee the lifetime.

							// Allocate a handle variable
							dt.MakeHandle(true);
							dt.MakeReadOnly(false);
							offset = AllocateVariableNotIn(dt, true, false, ctx);

							// Copy the handle
							Dereference(ctx, true);
							ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);
							if (ctx->type.dataType.IsFuncdef())
								ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
							else
								ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());
							ctx->bc.Instr(asBC_PopPtr);
							ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);

							// The type should be set to the param type instead of dt to guarantee
							// that the expression keeps the correct type for variable ? args. Otherwise
							// MoveArgsToStack will use the wrong bytecode to move the arg to the stack
							bool isExplicitHandle = ctx->type.isExplicitHandle;
							ctx->type.SetVariable(param, offset, true);
							ctx->type.dataType.MakeHandle(true);
							ctx->type.isExplicitHandle = isExplicitHandle;
						}
						else
						{
							// Make a copy of the object to guarantee that the original isn't modified
							asASSERT(!dt.IsFuncdef());

							// Allocate and initialize a temporary local object
							dt.MakeReadOnly(false);
							offset = AllocateVariableNotIn(dt, true, false, ctx);
							CompileInitAsCopy(dt, offset, &ctx->bc, ctx, node, false);

							// Push the object pointer on the stack
							ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
							if( dt.IsObject() && !dt.IsObjectHandle() )
								ctx->bc.Instr(asBC_RDSPtr);

							// Set the resulting type
							ctx->type.Set(dt);
							ctx->type.isTemporary = true;
							ctx->type.stackOffset = short(offset);
							if( dt.IsObjectHandle() )
								ctx->type.isExplicitHandle = true;
							ctx->type.dataType.MakeReference(false);
							if( paramType->IsReadOnly() )
								ctx->type.dataType.MakeReadOnly(true);
						}
					}

					// When calling a function expecting a var arg with a parameter received as reference to handle
					// then it is necessary to copy the handle to a local variable, otherwise MoveArgsToStack will
					// not be able to do the correct double dereference to put the reference to the object on the stack.
					if (paramType->GetTokenType() == ttQuestion && !param.IsObjectHandle() && ctx->type.isVariable)
					{
						sVariable *var = variables->GetVariableByOffset(ctx->type.stackOffset);
						if (var && var->type.IsReference() && var->type.IsObjectHandle())
						{
							// Copy the handle to local variable

							// Allocate a handle variable
							dt.MakeHandle(true);
							dt.MakeReadOnly(false);
							offset = AllocateVariableNotIn(dt, true, false, ctx);

							// Copy the handle
							Dereference(ctx, true);
							ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);
							if (ctx->type.dataType.IsFuncdef())
								ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
							else
								ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());
							ctx->bc.Instr(asBC_PopPtr);
							ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);

							// The type should be set to the param type instead of dt to guarantee
							// that the expression keeps the correct type for variable ? args. Otherwise
							// MoveArgsToStack will use the wrong bytecode to move the arg to the stack
							ctx->type.SetVariable(param, offset, true);
						}
					}
				}
				else
				{
					// We must guarantee that the address to the value is on the stack
					if( (ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) &&
						!ctx->type.dataType.IsObjectHandle() &&
						ctx->type.dataType.IsReference() )
						Dereference(ctx, true);
				}
			}
		}
		else if( refType == asTM_OUTREF )
		{
			// Add the type id as hidden arg if the parameter is a ? type
			if( paramType->GetTokenType() == ttQuestion )
			{
				asCByteCode tmpBC(engine);

				// Place the type id on the stack as a hidden parameter
				tmpBC.InstrDWORD(asBC_TYPEID, engine->GetTypeIdFromDataType(param));

				// Insert the code before the expression code
				tmpBC.AddCode(&ctx->bc);
				ctx->bc.AddCode(&tmpBC);
			}

			// If the expression is marked as clean, then it can be used directly
			// without the need to allocate another temporary value as it is known
			// that the argument has no other value than the default
			if( ctx->isCleanArg )
			{
				// Must be a local variable
				asASSERT( ctx->type.isVariable );
			}
			else
			{
				// Null handles and void expressions must be marked as explicit
				// handles for correct treatement in MoveArgsToStack
				if (dt.IsNullHandle())
					ctx->type.isExplicitHandle = true;

				// Make sure the variable is not used in the expression
				dt.MakeReadOnly(false);
				offset = AllocateVariableNotIn(dt, true, false, ctx);

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

					dt.MakeReference(!(dt.IsObject() || dt.IsFuncdef()) || dt.IsObjectHandle());
					asCExprValue type;
					type.Set(dt);
					type.isTemporary = true;
					type.stackOffset = (short)offset;

					type.isExplicitHandle = ctx->type.isExplicitHandle;
					ctx->type = type;

					ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
					if( (dt.IsObject() || dt.IsFuncdef()) && !dt.IsObjectHandle() )
						ctx->bc.Instr(asBC_RDSPtr);
				}

				// After the function returns the temporary variable will
				// be assigned to the expression, if it is a valid lvalue
			}
		}
		else if( refType == asTM_INOUTREF )
		{
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// Add the type id as hidden arg if the parameter is a ? type
			if( paramType->GetTokenType() == ttQuestion )
			{
				asCByteCode tmpBC(engine);

				// Place the type id on the stack as a hidden parameter
				tmpBC.InstrDWORD(asBC_TYPEID, engine->GetTypeIdFromDataType(param));

				// Insert the code before the expression code
				tmpBC.AddCode(&ctx->bc);
				ctx->bc.AddCode(&tmpBC);
			}

			// Literal constants cannot be passed to inout ref arguments
			if( !ctx->type.isVariable &&
				ctx->type.isConstant &&
				!ctx->type.dataType.IsEqualExceptRefAndConst(engine->stringType) )
			{
				// Unless unsafe references are turned on and the reference is const
				if( param.IsReadOnly() && engine->ep.allowUnsafeReferences )
				{
					// Since the parameter is a const & make a copy.
					ConvertToTempVariable(ctx);
					ctx->type.dataType.MakeReadOnly(true);
				}
				else
				{
					Error(TXT_NOT_VALID_REFERENCE, node);
					return -1;
				}
			}

			// Allow anonymous init lists to be converted to the arg type
			if( ctx->IsAnonymousInitList() )
				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true, true);
			
			if( (ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) && ctx->type.dataType.GetTypeInfo() != dt.GetTypeInfo() )
				ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV, true, false);

			// Only objects that support object handles
			// can be guaranteed to be safe. Local variables are
			// already safe, so there is no need to add an extra
			// references
			if( !engine->ep.allowUnsafeReferences &&
				!ctx->type.isVariable &&
				(ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) &&
				!ctx->type.dataType.IsObjectHandle() &&
				((ctx->type.dataType.GetBehaviour()->addref &&
				  ctx->type.dataType.GetBehaviour()->release) ||
				 (ctx->type.dataType.GetTypeInfo()->flags & asOBJ_NOCOUNT) ||
				 ctx->type.dataType.IsFuncdef()) )
			{
				// Store a handle to the object as local variable
				asCExprContext tmp(engine);
				dt = ctx->type.dataType;
				dt.MakeHandle(true);
				dt.MakeReference(false);
				dt.MakeReadOnly(false);

				offset = AllocateVariableNotIn(dt, true, false, ctx);

				// Copy the handle
				if( !ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsReference() )
					ctx->bc.Instr(asBC_RDSPtr);
				ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);
				if( ctx->type.dataType.IsFuncdef() )
					ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
				else
					ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());
				ctx->bc.Instr(asBC_PopPtr);
				ctx->bc.InstrWORD(asBC_PSF, (asWORD)offset);

				dt.MakeHandle(false);
				dt.MakeReference(true);

				// Release previous temporary variable stored in the context (if any)
				if( ctx->type.isTemporary )
					ReleaseTemporaryVariable(ctx->type.stackOffset, &ctx->bc);

				ctx->type.SetVariable(dt, offset, true);
			}

			// Make sure the reference to the value is on the stack
			// For objects, the reference needs to be dereferenced so the pointer on the stack is to the actual object
			// For handles, the reference shouldn't be changed because the pointer on the stack should be to the handle
			if( (ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) && ctx->type.dataType.IsReference() && !param.IsObjectHandle() )
				Dereference(ctx, true);
			else if( ctx->type.isVariable && !(ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) )
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			else if( ctx->type.dataType.IsPrimitive() )
				ctx->bc.Instr(asBC_PshRPtr);
			else if( ctx->type.dataType.IsObjectHandle() && !ctx->type.dataType.IsReference() )
				ImplicitConversion(ctx, param, node, asIC_IMPLICIT_CONV, true, false);
		}
	}
	else
	{
		if( ProcessPropertyGetAccessor(ctx, node) < 0 )
			return -1;

		if( dt.IsPrimitive() )
		{
			IsVariableInitialized(&ctx->type, node);

			if( ctx->type.dataType.IsReference() ) ConvertToVariable(ctx);

			// Implicitly convert primitives to the parameter type
			ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV);

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
			ImplicitConversion(ctx, dt, node, asIC_IMPLICIT_CONV);

			// Was the conversion successful?
			if( !ctx->type.dataType.IsEqualExceptRef(dt) )
			{
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), dt.Format(outFunc->nameSpace).AddressOf());
				Error(str, node);

				ctx->type.Set(dt);
				return -1;
			}

			if( dt.IsObjectHandle() )
				ctx->type.isExplicitHandle = true;

			if( (dt.IsObject() || dt.IsFuncdef()) && !dt.IsNullHandle() && !dt.IsReference() )
			{
				// Objects passed by value must be placed in temporary variables
				// so that they are guaranteed to not be referenced anywhere else.
				// The object must also be allocated on the heap, as the memory will
				// be deleted by the called function.

				// Handles passed by value must also be placed in a temporary variable
				// to guarantee that the object referred to isn't freed too early.

				// TODO: value on stack: How can we avoid this unnecessary allocation?

				// Don't make temporary copies of handles if it is going to be used
				// for handle assignment anyway, i.e. REFCPY.
				if( !(!isFunction && isMakingCopy && ctx->type.dataType.IsObjectHandle() && ctx->type.isVariable) )
					PrepareTemporaryVariable(node, ctx, true);
			}
		}
	}

	// Don't put any pointer on the stack yet
	if( param.IsReference() || ((param.IsObject() || param.IsFuncdef()) && !param.IsNullHandle()) )
	{
		// &inout parameter may leave the reference on the stack already
		// references considered safe too, i.e. when the life time is known
		if( refType != asTM_INOUTREF && !ctx->type.isRefSafe )
		{
			asASSERT( ctx->type.isVariable || ctx->type.isRefSafe || ctx->type.isTemporary || isMakingCopy );

			if( ctx->type.isVariable || ctx->type.isTemporary )
			{
				ctx->bc.Instr(asBC_PopPtr);
				ctx->bc.InstrSHORT(asBC_VAR, ctx->type.stackOffset);

				ProcessDeferredParams(ctx);
			}
		}
	}

	return 0;
}

int asCCompiler::PrepareFunctionCall(int funcId, asCByteCode *bc, asCArray<asCExprContext *> &args)
{
	// When a match has been found, compile the final byte code using correct parameter types
	asCScriptFunction *descr = builder->GetFunctionDescription(funcId);

	asASSERT( descr->parameterTypes.GetLength() == args.GetLength() );

	// If the function being called is the opAssign or copy constructor for the same type
	// as the argument, then we should avoid making temporary copy of the argument
	bool makingCopy = false;
	if( descr->parameterTypes.GetLength() == 1 &&
		descr->parameterTypes[0].IsEqualExceptRefAndConst(args[0]->type.dataType) &&
		(((descr->name == "opAssign" || descr->name == "$beh0") && descr->objectType && descr->objectType == args[0]->type.dataType.GetTypeInfo()) ||
		 (descr->objectType == 0 && args[0]->type.dataType.GetTypeInfo() && descr->name == args[0]->type.dataType.GetTypeInfo()->name)) )
		makingCopy = true;

	// Add code for arguments
	asCExprContext e(engine);
	for( int n = (int)args.GetLength()-1; n >= 0; n-- )
	{
		// Make sure PrepareArgument doesn't use any variable that is already
		// being used by the argument or any of the following argument expressions
		int l = int(reservedVariables.GetLength());
		for( int m = n; m >= 0; m-- )
			args[m]->bc.GetVarsUsed(reservedVariables);

		int r = PrepareArgument2(&e, args[n], &descr->parameterTypes[n], true, descr->inOutFlags[n], makingCopy);
		reservedVariables.SetLength(l);

		if (r < 0)
			return r;
	}

	bc->AddCode(&e.bc);

	return 0;
}

void asCCompiler::MoveArgsToStack(int funcId, asCByteCode *bc, asCArray<asCExprContext *> &args, bool addOneToOffset)
{
	asCScriptFunction *descr = builder->GetFunctionDescription(funcId);

	int offset = 0;
	if( addOneToOffset )
		offset += AS_PTR_SIZE;

	// The address of where the return value should be stored is push on top of the arguments
	if( descr->DoesReturnOnStack() )
		offset += AS_PTR_SIZE;

#ifdef AS_DEBUG
	// If the function being called is the opAssign or copy constructor for the same type
	// as the argument, then we should avoid making temporary copy of the argument
	bool makingCopy = false;
	if( descr->parameterTypes.GetLength() == 1 &&
		descr->parameterTypes[0].IsEqualExceptRefAndConst(args[0]->type.dataType) &&
		(((descr->name == "opAssign" || descr->name == "$beh0") && descr->objectType && descr->objectType == args[0]->type.dataType.GetTypeInfo()) ||
		 (descr->objectType == 0 && args[0]->type.dataType.GetTypeInfo() && descr->name == args[0]->type.dataType.GetTypeInfo()->name)) )
		makingCopy = true;
#endif

	// Move the objects that are sent by value to the stack just before the call
	for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
	{
		if( descr->parameterTypes[n].IsReference() )
		{
			if( (descr->parameterTypes[n].IsObject() || descr->parameterTypes[n].IsFuncdef()) && !descr->parameterTypes[n].IsObjectHandle() )
			{
				if( descr->inOutFlags[n] != asTM_INOUTREF && !args[n]->type.isRefSafe )
				{
#ifdef AS_DEBUG
					// This assert is inside AS_DEBUG because of the variable makingCopy which is only defined in debug mode
					asASSERT( args[n]->type.isVariable || args[n]->type.isTemporary || makingCopy );
#endif

					if( (args[n]->type.isVariable || args[n]->type.isTemporary) )
					{
						if( !IsVariableOnHeap(args[n]->type.stackOffset) )
							// TODO: runtime optimize: Actually the reference can be pushed on the stack directly
							//                         as the value allocated on the stack is guaranteed to be safe
							bc->InstrWORD(asBC_GETREF, (asWORD)offset);
						else
							bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
					}
				}
				if( args[n]->type.dataType.IsObjectHandle() )
					bc->InstrWORD(asBC_ChkNullS, (asWORD)offset);
			}
			else if( descr->inOutFlags[n] != asTM_INOUTREF )
			{
				// If the argument is already known to be safe, i.e. has a guaranteed lifetime,
				// then the address on the stack is already pointing to the correct object so no
				// need to do anything else
				if (!args[n]->type.isRefSafe)
				{
					if (descr->parameterTypes[n].GetTokenType() == ttQuestion &&
						(args[n]->type.dataType.IsObject() || args[n]->type.dataType.IsFuncdef()) &&
						!args[n]->type.dataType.IsObjectHandle())
					{
						// Send the object as a reference to the object,
						// and not to the variable holding the object
						if (!IsVariableOnHeap(args[n]->type.stackOffset))
							// TODO: runtime optimize: Actually the reference can be pushed on the stack directly
							//                         as the value allocated on the stack is guaranteed to be safe
							bc->InstrWORD(asBC_GETREF, (asWORD)offset);
						else
							bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
					}
					else if (descr->parameterTypes[n].GetTokenType() == ttQuestion &&
						args[n]->type.dataType.IsObjectHandle() && !args[n]->type.isExplicitHandle)
					{
						// The object handle is being passed as an object, so dereference it before
						// the call so the reference will be to the object rather than to the handle
						if (engine->ep.disallowValueAssignForRefType)
						{
							// With disallow value assign all ref type objects are always passed by handle
							bc->InstrWORD(asBC_GETREF, (asWORD)offset);
						}
						else
							bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
					}
					else
					{
						// If the variable is really an argument of @& type, then it is necessary
						// to use asBC_GETOBJREF so the pointer is correctly dereferenced.
						sVariable *var = variables->GetVariableByOffset(args[n]->type.stackOffset);
						if (var == 0 || !var->type.IsReference() || !var->type.IsObjectHandle())
							bc->InstrWORD(asBC_GETREF, (asWORD)offset);
						else
							bc->InstrWORD(asBC_GETOBJREF, (asWORD)offset);
					}
				}
			}
		}
		else if( descr->parameterTypes[n].IsObject() || descr->parameterTypes[n].IsFuncdef() )
		{
			asASSERT(!args[n]->type.isRefSafe);

			// TODO: value on stack: What can we do to avoid this unnecessary allocation?
			// The object must be allocated on the heap, because this memory will be deleted in as_callfunc_xxx
			asASSERT(IsVariableOnHeap(args[n]->type.stackOffset));

			// The pointer in the variable will be moved to the stack
			bc->InstrWORD(asBC_GETOBJ, (asWORD)offset);

			// Deallocate the variable slot so it can be reused, but do not attempt to
			// free the content of the variable since it was moved to the stack for the call
			DeallocateVariable(args[n]->type.stackOffset);
			args[n]->type.isTemporary = false;
		}

		offset += descr->parameterTypes[n].GetSizeOnStackDWords();
	}
}

int asCCompiler::CompileArgumentList(asCScriptNode *node, asCArray<asCExprContext*> &args, asCArray<asSNamedArgument> &namedArgs)
{
	asASSERT(node->nodeType == snArgList);

	// Count arguments
	asCScriptNode *arg = node->firstChild;
	int argCount = 0;
	while( arg )
	{
		if( arg->nodeType != snNamedArgument )
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
	bool anyErrors = false, inPositionalArguments = false;
	arg = node->lastChild;
	while( arg )
	{
		asCScriptNode *asgNode = arg, *namedNode = 0;
		if( asgNode->nodeType == snNamedArgument )
		{
			if( inPositionalArguments )
			{
				Error(TXT_POS_ARG_AFTER_NAMED_ARG, node);
				return -1;
			}

			asgNode = arg->firstChild->next;
			namedNode = arg->firstChild;

			asASSERT( namedNode->nodeType == snIdentifier );
		}
		else
			inPositionalArguments = true;

		asCExprContext expr(engine);
		int r = CompileAssignment(asgNode, &expr);
		if( r < 0 ) anyErrors = true;

		asCExprContext *ctx = asNEW(asCExprContext)(engine);
		if( ctx == 0 )
		{
			// Out of memory
			return -1;
		}
		MergeExprBytecodeAndType(ctx, &expr);

		if( inPositionalArguments )
		{
			args[n] = ctx;
			n--;
		}
		else
		{
			asSNamedArgument namedArg;
			namedArg.name = asCString(&script->code[namedNode->tokenPos], namedNode->tokenLength);
			namedArg.ctx = ctx;

			// Error out when multiple arguments with the same name are passed
			for( asUINT a = 0; a < namedArgs.GetLength(); ++a )
			{
				if( namedArgs[a].name == namedArg.name )
				{
					Error(TXT_DUPLICATE_NAMED_ARG, asgNode);
					anyErrors = true;
					break;
				}
			}

			namedArgs.PushLast(namedArg);
		}

		arg = arg->prev;
	}

	return anyErrors ? -1 : 0;
}

int asCCompiler::CompileDefaultAndNamedArgs(asCScriptNode *node, asCArray<asCExprContext*> &args, int funcId, asCObjectType *objectType, asCArray<asSNamedArgument> *namedArgs)
{
	asCScriptFunction *func = builder->GetFunctionDescription(funcId);
	if( func == 0 || args.GetLength() >= (asUINT)func->GetParamCount() )
		return 0;

	// Make sure to use the real function for virtual functions
	if( func->funcType == asFUNC_VIRTUAL )
	{
		asASSERT( objectType );
		func = objectType->virtualFunctionTable[func->vfTableIdx];
	}

	// Make sure none of the variables used in the previous arguments are reused in the default arguments
	bool anyErrors = false;
	int prevReservedVars = reservedVariables.GetLength();

	int explicitArgs = (int)args.GetLength();

	for( int p = 0; p < explicitArgs; p++ )
		args[p]->bc.GetVarsUsed(reservedVariables);

	// Make space for all the new arguments
	args.SetLength(func->parameterTypes.GetLength());
	for( asUINT c = explicitArgs; c < args.GetLength(); c++ )
		args[c] = 0;

	// Add the named arguments to the argument list in the right position
	if( namedArgs )
	{
		for( asUINT n = 0; n < namedArgs->GetLength(); ++n )
		{
			asSNamedArgument &named = (*namedArgs)[n];
			named.ctx->bc.GetVarsUsed(reservedVariables);

			// Find the right spot to put it in
			asUINT index = asUINT(-1);
			for( asUINT j = 0; j < func->parameterTypes.GetLength(); ++j )
			{
				if( func->parameterNames[j] == (*namedArgs)[n].name )
				{
					index = j;
					break;
				}
			}

			asASSERT( index < args.GetLength() );
			args[index] = named.ctx;
			named.ctx = 0;
		}
	}

	// Compile the arguments in reverse order (as they will be pushed on the stack)
	for( int n = (int)func->parameterTypes.GetLength() - 1; n >= explicitArgs; n-- )
	{
		if( args[n] != 0 ) continue;
		if( func->defaultArgs[n] == 0 ) { anyErrors = true; continue; }

		// Parse the default arg string
		asCParser parser(builder);
		asCScriptCode *code = builder->FindOrAddCode("default arg", func->defaultArgs[n]->AddressOf(), func->defaultArgs[n]->GetLength());
		int r = parser.ParseExpression(code);
		if( r < 0 )
		{
			asCString msg;
			msg.Format(TXT_FAILED_TO_COMPILE_DEF_ARG_d_IN_FUNC_s, n, func->GetDeclaration());
			Error(msg, node);
			anyErrors = true;
			continue;
		}

		asCScriptNode *arg = parser.GetScriptNode();

		// Temporarily set the script code to the default arg expression
		asCScriptCode *origScript = script;
		script = code;

		// Don't allow the expression to access local variables
		isCompilingDefaultArg = true;

		// Temporarily set the namespace in the output function to the namespace of the called
		// function so that the default arguments are evaluated in the correct namespace
		asSNameSpace *origNameSpace = outFunc->nameSpace;
		outFunc->nameSpace = func->nameSpace;

		asCExprContext expr(engine);
		r = CompileExpression(arg, &expr);

		// Restore the namespace
		outFunc->nameSpace = origNameSpace;

		// Don't allow address of class method
		if( expr.IsClassMethod() )
		{
			// TODO: Improve error message
			Error(TXT_DEF_ARG_TYPE_DOESNT_MATCH, arg);
			r = -1;
		}

		// Make sure the expression can be implicitly converted to the parameter type
		if( r >= 0 )
		{
			asCArray<int> funcs;
			funcs.PushLast(func->id);
			asCArray<asSOverloadCandidate> matches;
			if( MatchArgument(funcs, matches, &expr, n) == 0 )
			{
				Error(TXT_DEF_ARG_TYPE_DOESNT_MATCH, arg);
				r = -1;
			}
		}

		isCompilingDefaultArg = false;

		script = origScript;

		if( r < 0 )
		{
			asCString msg;
			msg.Format(TXT_FAILED_TO_COMPILE_DEF_ARG_d_IN_FUNC_s, n, func->GetDeclaration());
			Error(msg, node);
			anyErrors = true;
			continue;
		}

		args[n] = asNEW(asCExprContext)(engine);
		if( args[n] == 0 )
		{
			// Out of memory
			reservedVariables.SetLength(prevReservedVars);
			return -1;
		}

		MergeExprBytecodeAndType(args[n], &expr);
		if (args[n]->exprNode)
		{
			// Disconnect the node from the parser, and tell the compiler to free it when complete
			args[n]->exprNode->DisconnectParent();
			nodesToFreeUponComplete.PushLast(args[n]->exprNode);
		}
	}

	reservedVariables.SetLength(prevReservedVars);
	return anyErrors ? -1 : 0;
}

asUINT asCCompiler::MatchFunctions(asCArray<int> &funcs, asCArray<asCExprContext*> &args, asCScriptNode *node, const char *name, asCArray<asSNamedArgument> *namedArgs, asCObjectType *objectType, bool isConstMethod, bool silent, bool allowObjectConstruct, const asCString &scope)
{
	asCArray<int> origFuncs = funcs; // Keep the original list for error message
	asUINT cost = 0;
	asUINT n;

	if( funcs.GetLength() > 0 )
	{
		// Check the number of parameters in the found functions
		asUINT totalArgs = (asUINT)args.GetLength();
		if( namedArgs != 0 )
			totalArgs += (asUINT)namedArgs->GetLength();

		for( n = 0; n < funcs.GetLength(); ++n )
		{
			asCScriptFunction *desc = builder->GetFunctionDescription(funcs[n]);

			if( desc->parameterTypes.GetLength() != totalArgs )
			{
				bool noMatch = true;
				if( totalArgs < desc->parameterTypes.GetLength() )
				{
					// For virtual functions, the default args are defined in the real function of the object
					if( desc->funcType == asFUNC_VIRTUAL )
						desc = objectType->virtualFunctionTable[desc->vfTableIdx];

					// Count the number of default args
					asUINT defaultArgs = 0;
					for( asUINT d = 0; d < desc->defaultArgs.GetLength(); d++ )
						if( desc->defaultArgs[d] )
							defaultArgs++;

					if( totalArgs >= desc->parameterTypes.GetLength() - defaultArgs )
						noMatch = false;
				}

				if( noMatch )
				{
					// remove it from the list
					if( n == funcs.GetLength()-1 )
						funcs.PopLast();
					else
						funcs[n] = funcs.PopLast();
					n--;
				}
			}
		}

		// Match functions with the parameters, and discard those that do not match
		asCArray<asSOverloadCandidate> matchingFuncs;
		matchingFuncs.SetLengthNoConstruct( funcs.GetLength() );
		for ( n = 0; n < funcs.GetLength(); ++n )
		{
			matchingFuncs[n].funcId = funcs[n];
			matchingFuncs[n].cost = 0;
		}

		// Match positionally passed arguments
		for( n = 0; n < args.GetLength(); ++n )
		{
			asCArray<asSOverloadCandidate> tempFuncs;
			MatchArgument(funcs, tempFuncs, args[n], n, allowObjectConstruct);

			// Intersect the found functions with the list of matching functions
			for( asUINT f = 0; f < matchingFuncs.GetLength(); f++ )
			{
				asUINT c;
				for( c = 0; c < tempFuncs.GetLength(); c++ )
				{
					if( matchingFuncs[f].funcId == tempFuncs[c].funcId )
					{
						// Sum argument cost
						matchingFuncs[f].cost += tempFuncs[c].cost;
						break;

					} // End if match
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

		// Match named arguments
		if( namedArgs != 0 )
		{
			for( asUINT i = 0; i < matchingFuncs.GetLength(); ++i )
			{
				asCScriptFunction *desc = builder->GetFunctionDescription(matchingFuncs[i].funcId);
				if( desc->funcType == asFUNC_VIRTUAL )
					desc = objectType->virtualFunctionTable[desc->vfTableIdx];

				// Match every named argument to an argument in the function
				for( n = 0; n < namedArgs->GetLength(); ++n )
					(*namedArgs)[n].match = asUINT(-1);

				bool matchedAll = true;
				for( asUINT j = 0; j < desc->parameterTypes.GetLength(); ++j )
				{
					asUINT match = asUINT(-1);
					for( n = 0; n < namedArgs->GetLength(); ++n )
					{
						asSNamedArgument &namedArg = (*namedArgs)[n];
						if( desc->parameterNames[j] == namedArg.name )
						{
							namedArg.match = j;
							match = n;
							break;
						}
					}

					// Check that every position is filled somehow
					if( j >= args.GetLength() )
					{
						if( match == asUINT(-1) && !desc->defaultArgs[j] )
						{
							// No argument was found for this, and there is no
							// default, so it doesn't work.
							matchedAll = false;
							break;
						}
					}
					else
					{
						if( match != asUINT(-1) )
						{
							// Can't name an argument that was already passed
							matchedAll = false;
							break;
						}
					}
				}

				// Check that every named argument was matched
				if( matchedAll )
				{
					for( n = 0; n < namedArgs->GetLength(); ++n )
					{
						asSNamedArgument &named = (*namedArgs)[n];

						if( named.match == asUINT(-1) )
						{
							matchedAll = false;
							break;
						}

						// Add to the cost
						cost = MatchArgument(desc, named.ctx, named.match, allowObjectConstruct);
						if( cost == asUINT(-1) )
						{
							matchedAll = false;
							break;
						}

						matchingFuncs[i].cost += cost;
					}
				}

				if( !matchedAll )
				{
					// Remove the function, we didn't match all the arguments.
					if( i == matchingFuncs.GetLength()-1 )
						matchingFuncs.PopLast();
					else
						matchingFuncs[i] = matchingFuncs.PopLast();
					i--;
				}
			}
		}

		// Select the overload(s) with the lowest overall cost
		funcs.SetLength(0);
		asUINT bestCost = asUINT(-1);
		for( n = 0; n < matchingFuncs.GetLength(); ++n )
		{
			cost = matchingFuncs[n].cost;
			if( cost < bestCost )
			{
				funcs.SetLength(0);
				bestCost = cost;
			}
			if( cost == bestCost )
				funcs.PushLast( matchingFuncs[n].funcId );
		}

		// Cost returned is equivalent to the best cost discovered
		cost = bestCost;
	}

	if( !isConstMethod )
		FilterConst(funcs);

	if( funcs.GetLength() != 1 && !silent )
	{
		// Build a readable string of the function with parameter types
		bool attemptsPassingClassMethod = false;
		asCString str;
		if( scope != "" && scope != "::" )
			str = scope + "::";
		str += name;
		str += "(";
		for( n = 0; n < args.GetLength(); n++ )
		{
			if( n > 0 )
				str += ", ";
			if( args[n]->methodName != "" )
			{
				if( args[n]->IsClassMethod() )
				{
					attemptsPassingClassMethod = true;
					str += args[n]->type.dataType.GetTypeInfo()->GetName();
					str += "::";
				}
				str += args[n]->methodName;
			}
			else if (args[n]->IsAnonymousInitList())
			{
				str += "{...}";
			}
			else
				str += args[n]->type.dataType.Format(outFunc->nameSpace);
		}
		if( namedArgs != 0 )
		{
			for( n = 0; n < namedArgs->GetLength(); n++ )
			{
				if( n > 0 || args.GetLength() )
					str += ", ";

				asSNamedArgument &named = (*namedArgs)[n];
				str += named.name;
				str += ": ";
				if( named.ctx->methodName != "" )
					str += named.ctx->methodName;
				else
					str += named.ctx->type.dataType.Format(outFunc->nameSpace);
			}
		}
		str += ")";

		if( isConstMethod )
			str += " const";

		if( objectType && scope == "" )
			str = objectType->name + "::" + str;

		if( funcs.GetLength() == 0 )
		{
			str.Format(TXT_NO_MATCHING_SIGNATURES_TO_s, str.AddressOf());
			Error(str, node);

			if( attemptsPassingClassMethod )
			{
				// Class methods must use delegate objects
				Error(TXT_CANNOT_PASS_CLASS_METHOD_AS_ARG, node);
			}
			else
			{
				// Print the list of candidates
				if( origFuncs.GetLength() > 0 )
				{
					int r = 0, c = 0;
					asASSERT( node );
					if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);
					builder->WriteInfo(script->name.AddressOf(), TXT_CANDIDATES_ARE, r, c, false);
					PrintMatchingFuncs(origFuncs, node, objectType);
				}
			}
		}
		else
		{
			asASSERT( attemptsPassingClassMethod == false );

			str.Format(TXT_MULTIPLE_MATCHING_SIGNATURES_TO_s, str.AddressOf());
			Error(str, node);

			PrintMatchingFuncs(funcs, node, objectType);
		}
	}

	return cost;
}

bool asCCompiler::CompileAutoType(asCDataType &type, asCExprContext &compiledCtx, asCScriptNode *node, asCScriptNode *errNode)
{
	if( node && node->nodeType == snAssignment )
	{
		int r = CompileAssignment(node, &compiledCtx);
		if( r >= 0 )
		{
			// Must not have unused ambiguous names
			if (compiledCtx.IsClassMethod() || compiledCtx.IsGlobalFunc())
			{
				// TODO: Should mention that the problem is the ambiguous name
				Error(TXT_CANNOT_RESOLVE_AUTO, errNode);
				return false;
			}

			// Must not have unused anonymous functions
			if (compiledCtx.IsLambda())
			{
				// TODO: Should mention that the problem is the anonymous function
				Error(TXT_CANNOT_RESOLVE_AUTO, errNode);
				return false;
			}

			// Must not be a null handle
			if (compiledCtx.type.dataType.IsNullHandle())
			{
				// TODO: Should mention that the problem is the null pointer
				Error(TXT_CANNOT_RESOLVE_AUTO, errNode);
				return false;
			}

			asCDataType newType = compiledCtx.type.dataType;

			// Handle const qualifier on auto
			if (type.IsReadOnly())
				newType.MakeReadOnly(true);
			else if (type.IsHandleToConst())
				newType.MakeHandleToConst(true);
			else if (newType.IsPrimitive())
				newType.MakeReadOnly(false);

			// Handle reference/value stuff
			newType.MakeReference(false);
			if (!newType.IsObjectHandle())
			{
				// We got a value object or an object reference.
				// Turn the variable into a handle if specified
				// as auto@, otherwise make it a 'value'.
				if (type.IsHandleToAuto())
				{
					if (newType.MakeHandle(true) < 0)
					{
						Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, errNode);
						return false;
					}
				}
			}

			// Implicit handle types should always be handles
			if (newType.GetTypeInfo() &&
				(newType.GetTypeInfo()->flags & asOBJ_IMPLICIT_HANDLE))
				newType.MakeHandle(true);
				
			// For types that support handles auto should prefer handle 
			// as it is more efficient than making a copy
			if( newType.SupportHandles() )
				newType.MakeHandle(true);

			type = newType;
			return true;
		}

		return false;
	}
	else
	{
		Error(TXT_CANNOT_RESOLVE_AUTO, errNode);
		type = asCDataType::CreatePrimitive(ttInt, false);
		return false;
	}
}

void asCCompiler::CompileDeclaration(asCScriptNode *decl, asCByteCode *bc)
{
	// Get the data type
	asCDataType type = builder->CreateDataTypeFromNode(decl->firstChild, script, outFunc->nameSpace, false, outFunc->objectType);

	// Declare all variables in this declaration
	asCScriptNode *node = decl->firstChild->next;
	while( node )
	{
		// If this is an auto type, we have to compile the assignment now to figure out the type
		asCExprContext compiledCtx(engine);
		bool preCompiled = false;
		if (type.IsAuto())
		{
			preCompiled = CompileAutoType(type, compiledCtx, node->next, node);
			if (!preCompiled)
			{
				// If it wasn't possible to determine the type from the expression then there
				// is no need to continue with the initialization. The error was already reported
				// in CompileAutoType.
				return;
			}
		}

		// Is the type allowed?
		if( !type.CanBeInstantiated() )
		{
			asCString str;
			if( type.IsAbstractClass() )
				str.Format(TXT_ABSTRACT_CLASS_s_CANNOT_BE_INSTANTIATED, type.Format(outFunc->nameSpace).AddressOf());
			else if( type.IsInterface() )
				str.Format(TXT_INTERFACE_s_CANNOT_BE_INSTANTIATED, type.Format(outFunc->nameSpace).AddressOf());
			else
				// TODO: Improve error message to explain why
				str.Format(TXT_DATA_TYPE_CANT_BE_s, type.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);

			// Don't continue, as it will most likely lead to further
			// errors that may just mislead the script writer
			return;
		}

		// A shared object may not declare variables of non-shared types
		if( outFunc->IsShared() )
		{
			asCTypeInfo *ot = type.GetTypeInfo();
			if( ot && !ot->IsShared() )
			{
				asCString msg;
				msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, ot->name.AddressOf());
				Error(msg, decl);
			}
		}

		// Get the name of the identifier
		asCString name(&script->code[node->tokenPos], node->tokenLength);

		// Verify that the name isn't used by a dynamic data type
		// TODO: Must check against registered funcdefs too
		if( engine->GetRegisteredType(name.AddressOf(), outFunc->nameSpace) != 0 )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_VARIABLE_NAME_s, name.AddressOf());
			Error(str, node);
		}

		int offset = AllocateVariable(type, false);
		if( variables->DeclareVariable(name.AddressOf(), type, offset, IsVariableOnHeap(offset)) < 0 )
		{
			// TODO: It might be an out-of-memory too

			asCString str;
			str.Format(TXT_s_ALREADY_DECLARED, name.AddressOf());
			Error(str, node);

			// Don't continue after this error, as it will just
			// lead to more errors that are likely false
			return;
		}
		else
		{
			// Warn if this variable hides another variable in a higher scope
			if( variables->parent && variables->parent->GetVariable(name.AddressOf()) )
			{
				asCString str;
				str.Format(TXT_s_HIDES_VAR_IN_OUTER_SCOPE, name.AddressOf());
				Warning(str, node);
			}
		}

		// Add marker that the variable has been declared
		bc->VarDecl((int)outFunc->scriptData->variables.GetLength());
		outFunc->AddVariable(name, type, offset);

		// Keep the node for the variable decl
		asCScriptNode *varNode = node;

		node = node->next;

		if( node == 0 || node->nodeType == snIdentifier )
		{
			// Initialize with default constructor
			CompileInitialization(0, bc, type, varNode, offset, 0, 0);
		}
		else
		{
			// Compile the initialization expression
			asQWORD constantValue = 0;
			if( CompileInitialization(node, bc, type, varNode, offset, &constantValue, 0, preCompiled ? &compiledCtx : 0) )
			{
				// Check if the variable should be marked as pure constant
				if( type.IsPrimitive() && type.IsReadOnly() )
				{
					sVariable *v = variables->GetVariable(name.AddressOf());
					v->isPureConstant = true;
					v->constantValue = constantValue;
				}
			}
			node = node->next;
		}
	}

	bc->OptimizeLocally(tempVariableOffsets);
}

// Returns true if the initialization expression is a constant expression
bool asCCompiler::CompileInitialization(asCScriptNode *node, asCByteCode *bc, const asCDataType &type, asCScriptNode *errNode, int offset, asQWORD *constantValue, int isVarGlobOrMem, asCExprContext *preCompiled)
{
	bool isConstantExpression = false;
	if( node && node->nodeType == snArgList )
	{
		// Make sure it is an object and not a handle
		if( type.GetTypeInfo() == 0 || type.IsObjectHandle() )
		{
			Error(TXT_MUST_BE_OBJECT, node);
		}
		else
		{
			// Compile the arguments
			asCArray<asCExprContext *> args;
			asCArray<asSNamedArgument> namedArgs;
			if( CompileArgumentList(node, args, namedArgs) >= 0 )
			{
				// Find all constructors
				asCArray<int> funcs;
				asSTypeBehaviour *beh = type.GetBehaviour();
				if( beh )
				{
					if( type.GetTypeInfo()->flags & asOBJ_REF )
						funcs = beh->factories;
					else
						funcs = beh->constructors;
				}

				asCString str = type.Format(outFunc->nameSpace);
				MatchFunctions(funcs, args, node, str.AddressOf(), &namedArgs);

				if( funcs.GetLength() == 1 )
				{
					// Add the default values for arguments not explicitly supplied
					int r = CompileDefaultAndNamedArgs(node, args, funcs[0], CastToObjectType(type.GetTypeInfo()), &namedArgs);

					if( r == asSUCCESS )
					{
						asCExprContext ctx(engine);
						if( type.GetTypeInfo() && (type.GetTypeInfo()->flags & asOBJ_REF) )
						{
							if( isVarGlobOrMem == 0 )
								MakeFunctionCall(&ctx, funcs[0], 0, args, node, true, offset);
							else
							{
								MakeFunctionCall(&ctx, funcs[0], 0, args, node);
								ctx.bc.Instr(asBC_RDSPtr);
								if( isVarGlobOrMem == 1 )
								{
									// Store the returned handle in the global variable
									ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
								}
								else
								{
									// Store the returned handle in the member
									ctx.bc.InstrSHORT(asBC_PSF, 0);
									ctx.bc.Instr(asBC_RDSPtr);
									ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
								}
								if( type.IsFuncdef())
									ctx.bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
								else
									ctx.bc.InstrPTR(asBC_REFCPY, type.GetTypeInfo());
								ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
							}

							// Pop the reference left by the function call
							ctx.bc.Instr(asBC_PopPtr);
						}
						else
						{
							bool onHeap = false;

							if( isVarGlobOrMem == 0 )
							{
								// When the object is allocated on the heap, the address where the
								// reference will be stored must be pushed on the stack before the
								// arguments. This reference on the stack is safe, even if the script
								// is suspended during the evaluation of the arguments.
								onHeap = IsVariableOnHeap(offset);
								if( onHeap )
									ctx.bc.InstrSHORT(asBC_PSF, (short)offset);
							}
							else if( isVarGlobOrMem == 1 )
							{
								// Push the address of the location where the variable will be stored on the stack.
								// This reference is safe, because the addresses of the global variables cannot change.
								onHeap = true;
								ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
							}
							else
							{
								// Value types may be allocated inline if they are POD types
								onHeap = !(type.IsObject() || type.IsFuncdef()) || type.IsReference() || (type.GetTypeInfo()->flags & asOBJ_REF);
								if( onHeap )
								{
									ctx.bc.InstrSHORT(asBC_PSF, 0);
									ctx.bc.Instr(asBC_RDSPtr);
									ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
								}
							}

							PrepareFunctionCall(funcs[0], &ctx.bc, args);
							MoveArgsToStack(funcs[0], &ctx.bc, args, false);

							// When the object is allocated on the stack, the address to the
							// object is pushed on the stack after the arguments as the object pointer
							if( !onHeap )
							{
								if( isVarGlobOrMem == 2 )
								{
									ctx.bc.InstrSHORT(asBC_PSF, 0);
									ctx.bc.Instr(asBC_RDSPtr);
									ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
								}
								else
								{
									ctx.bc.InstrSHORT(asBC_PSF, (short)offset);
								}
							}

							PerformFunctionCall(funcs[0], &ctx, onHeap, &args, CastToObjectType(type.GetTypeInfo()));

							if( isVarGlobOrMem == 0 )
							{
								// Mark the object in the local variable as initialized
								ctx.bc.ObjInfo(offset, asOBJ_INIT);
							}
						}
						bc->AddCode(&ctx.bc);
					}
				}
			}

			// Cleanup
			for( asUINT n = 0; n < args.GetLength(); n++ )
				if( args[n] )
				{
					asDELETE(args[n], asCExprContext);
				}
			for( asUINT n = 0; n < namedArgs.GetLength(); n++ )
				if( namedArgs[n].ctx )
				{
					asDELETE(namedArgs[n].ctx, asCExprContext);
				}
		}
	}
	else if( node && node->nodeType == snInitList )
	{
		asCExprValue ti;
		ti.Set(type);
		ti.isVariable = (isVarGlobOrMem == 0);
		ti.isTemporary = false;
		ti.stackOffset = (short)offset;
		ti.isLValue = true;

		CompileInitList(&ti, node, bc, isVarGlobOrMem);
	}
	else if( node && node->nodeType == snAssignment )
	{
		// Compile the expression
		asCExprContext newExpr(engine);
		asCExprContext* expr;
		int r = 0;

		if( preCompiled )
		{
			expr = preCompiled;
		}
		else
		{
			expr = &newExpr;
			r = CompileAssignment(node, expr);
		}

		// handles initialized with null doesn't need any bytecode
		// since handles will be initialized to null by default anyway
		if (type.IsObjectHandle() && expr->type.IsNullConstant() && expr->bc.IsSimpleExpression() )
			return false;

		// Look for appropriate constructor
		asCArray<int> funcs;
		asCArray<asCExprContext *> args;

		// Handles must use the handle assignment operation.
		// Types that are ASHANDLE must not allow the use of the constructor in this case,
		// because it is ambiguous whether a value assignment or handle assignment will be done.
		// Only do this if the expression is of the same type, as the expression is an assignment
		// and an initialization constructor may not have the same meaning.
		// TODO: Should allow initialization constructor if it is declared as allowed for implicit conversions.
		if( !type.IsObjectHandle() && !expr->type.isExplicitHandle &&
			!(type.GetTypeInfo() && (type.GetTypeInfo()->GetFlags() & asOBJ_ASHANDLE)) &&
			type.IsEqualExceptRefAndConst(expr->type.dataType) )
		{
			asSTypeBehaviour *beh = type.GetBehaviour();
			if( beh )
			{
				if( type.GetTypeInfo()->flags & asOBJ_REF )
					funcs = beh->factories;
				else
					funcs = beh->constructors;
			}

			asCString str = type.Format(outFunc->nameSpace);
			args.PushLast(expr);
			MatchFunctions(funcs, args, node, str.AddressOf(), 0, 0, 0, true);

			// Make sure the argument is of the right type (and not just compatible with the expression)
			if (funcs.GetLength() == 1)
			{
				asCScriptFunction *f = engine->scriptFunctions[funcs[0]];
				if (!f->parameterTypes[0].IsEqualExceptRefAndConst(expr->type.dataType))
					funcs.PopLast();
			}
		}

		if( funcs.GetLength() == 1 )
		{
			// Use the constructor

			// TODO: clean-up: A large part of this is identical to the initalization with argList above

			// Add the default values for arguments not explicitly supplied
			r = CompileDefaultAndNamedArgs(node, args, funcs[0], CastToObjectType(type.GetTypeInfo()));

			if( r == asSUCCESS )
			{
				asCExprContext ctx(engine);
				if( type.GetTypeInfo() && (type.GetTypeInfo()->flags & asOBJ_REF) )
				{
					if( isVarGlobOrMem == 0 )
						MakeFunctionCall(&ctx, funcs[0], 0, args, node, true, offset);
					else
					{
						MakeFunctionCall(&ctx, funcs[0], 0, args, node);
						ctx.bc.Instr(asBC_RDSPtr);
						if( isVarGlobOrMem == 1 )
						{
							// Store the returned handle in the global variable
							ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
						}
						else
						{
							// Store the returned handle in the member
							ctx.bc.InstrSHORT(asBC_PSF, 0);
							ctx.bc.Instr(asBC_RDSPtr);
							ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
						}
						if( type.IsFuncdef() )
							ctx.bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
						else
							ctx.bc.InstrPTR(asBC_REFCPY, type.GetTypeInfo());
						ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
					}

					// Pop the reference left by the function call
					ctx.bc.Instr(asBC_PopPtr);
				}
				else
				{
					bool onHeap = false;

					if( isVarGlobOrMem == 0 )
					{
						// When the object is allocated on the heap, the address where the
						// reference will be stored must be pushed on the stack before the
						// arguments. This reference on the stack is safe, even if the script
						// is suspended during the evaluation of the arguments.
						onHeap = IsVariableOnHeap(offset);
						if( onHeap )
							ctx.bc.InstrSHORT(asBC_PSF, (short)offset);
					}
					else if( isVarGlobOrMem == 1 )
					{
						// Push the address of the location where the variable will be stored on the stack.
						// This reference is safe, because the addresses of the global variables cannot change.
						onHeap = true;
						ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
					}
					else
					{
						// Value types may be allocated inline if they are POD types
						onHeap = !(type.IsObject() || type.IsFuncdef()) || type.IsReference() || (type.GetTypeInfo()->flags & asOBJ_REF);
						if( onHeap )
						{
							ctx.bc.InstrSHORT(asBC_PSF, 0);
							ctx.bc.Instr(asBC_RDSPtr);
							ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
						}
					}

					PrepareFunctionCall(funcs[0], &ctx.bc, args);
					MoveArgsToStack(funcs[0], &ctx.bc, args, false);

					// When the object is allocated on the stack, the address to the
					// object is pushed on the stack after the arguments as the object pointer
					if( !onHeap )
					{
						if( isVarGlobOrMem == 2 )
						{
							ctx.bc.InstrSHORT(asBC_PSF, 0);
							ctx.bc.Instr(asBC_RDSPtr);
							ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
						}
						else
						{
							ctx.bc.InstrSHORT(asBC_PSF, (short)offset);
						}
					}

					PerformFunctionCall(funcs[0], &ctx, onHeap, &args, CastToObjectType(type.GetTypeInfo()));

					if( isVarGlobOrMem == 0 )
					{
						// Mark the object in the local variable as initialized
						ctx.bc.ObjInfo(offset, asOBJ_INIT);
					}
				}
				bc->AddCode(&ctx.bc);
			}
		}
		else
		{
			// Call the default constructor, then call the assignment operator
			asCExprContext ctx(engine);

			// Call the default constructor here
			if( isVarGlobOrMem == 0 )
				CallDefaultConstructor(type, offset, IsVariableOnHeap(offset), &ctx.bc, errNode);
			else if( isVarGlobOrMem == 1 )
				CallDefaultConstructor(type, offset, true, &ctx.bc, errNode, isVarGlobOrMem);
			else if( isVarGlobOrMem == 2 )
				CallDefaultConstructor(type, offset, type.IsReference(), &ctx.bc, errNode, isVarGlobOrMem);

			if( r >= 0 )
			{
				if( type.IsPrimitive() )
				{
					if( type.IsReadOnly() && expr->type.isConstant )
					{
						ImplicitConversion(expr, type, node, asIC_IMPLICIT_CONV);

						// Tell caller that the expression is a constant so it can mark the variable as pure constant
						isConstantExpression = true;
						*constantValue = expr->type.GetConstantData();
					}

					asCExprContext lctx(engine);
					if( isVarGlobOrMem == 0 )
						lctx.type.SetVariable(type, offset, false);
					else if( isVarGlobOrMem == 1 )
					{
						lctx.type.Set(type);
						lctx.type.dataType.MakeReference(true);

						// If it is an enum value, i.e. offset is negative, that is being compiled then
						// we skip this as the bytecode won't be used anyway, only the constant value
						if( offset >= 0 )
							lctx.bc.InstrPTR(asBC_LDG, engine->globalProperties[offset]->GetAddressOfValue());
					}
					else
					{
						asASSERT( isVarGlobOrMem == 2 );
						lctx.type.Set(type);
						lctx.type.dataType.MakeReference(true);

						// Load the reference of the primitive member into the register
						lctx.bc.InstrSHORT(asBC_PSF, 0);
						lctx.bc.Instr(asBC_RDSPtr);
						lctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
						lctx.bc.Instr(asBC_PopRPtr);
					}
					lctx.type.dataType.MakeReadOnly(false);
					lctx.type.isLValue = true;

					DoAssignment(&ctx, &lctx, expr, node, node, ttAssignment, node);
					ProcessDeferredParams(&ctx);
				}
				else
				{
					// TODO: runtime optimize: Here we should look for the best matching constructor, instead of
					//                         just the copy constructor. Only if no appropriate constructor is
					//                         available should the assignment operator be used.

					asCExprContext lexpr(engine);
					lexpr.type.Set(type);
					if( isVarGlobOrMem == 0 )
						lexpr.type.dataType.MakeReference(IsVariableOnHeap(offset));
					else if( isVarGlobOrMem == 1 )
						lexpr.type.dataType.MakeReference(true);
					else if( isVarGlobOrMem == 2 )
					{
						if( !lexpr.type.dataType.IsObject() || lexpr.type.dataType.IsFuncdef() || (lexpr.type.dataType.GetTypeInfo()->flags & asOBJ_REF) )
							lexpr.type.dataType.MakeReference(true);
					}

					// Allow initialization of constant variables
					lexpr.type.dataType.MakeReadOnly(false);

					if( type.IsObjectHandle() )
						lexpr.type.isExplicitHandle = true;

					if( isVarGlobOrMem == 0 )
					{
						lexpr.bc.InstrSHORT(asBC_PSF, (short)offset);
						lexpr.type.stackOffset = (short)offset;
						lexpr.type.isVariable = true;
					}
					else if( isVarGlobOrMem == 1 )
					{
						lexpr.bc.InstrPTR(asBC_PGA, engine->globalProperties[offset]->GetAddressOfValue());
					}
					else
					{
						lexpr.bc.InstrSHORT(asBC_PSF, 0);
						lexpr.bc.Instr(asBC_RDSPtr);
						lexpr.bc.InstrSHORT_DW(asBC_ADDSi, (short)offset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
						lexpr.type.stackOffset = -1;
					}
					lexpr.type.isLValue = true;


					// If left expression resolves into a registered type
					// check if the assignment operator is overloaded, and check
					// the type of the right hand expression. If none is found
					// the default action is a direct copy if it is the same type
					// and a simple assignment.
					bool assigned = false;
					// Even though an ASHANDLE can be an explicit handle the overloaded operator needs to be called
					if( (lexpr.type.dataType.IsObject() || lexpr.type.dataType.IsFuncdef()) && (!lexpr.type.isExplicitHandle || (lexpr.type.dataType.GetTypeInfo() && (lexpr.type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE))) )
					{
						bool useHndlAssign = false;
						if (lexpr.type.dataType.IsHandleToAsHandleType())
						{
							useHndlAssign = true;

							// Make sure the right hand expression is treated as a handle
							if (!expr->type.isExplicitHandle && !expr->type.IsNullConstant() )
							{
								// TODO: Clean-up: This code is from CompileExpressionPreOp. Create a reusable function
								// Convert the expression to a handle
								if (!expr->type.dataType.IsObjectHandle() && expr->type.dataType.GetTypeInfo() && !(expr->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE))
								{
									asCDataType to = expr->type.dataType;
									to.MakeHandle(true);
									to.MakeReference(true);
									to.MakeHandleToConst(expr->type.dataType.IsReadOnly());
									ImplicitConversion(expr, to, node, asIC_IMPLICIT_CONV, true, false);

									asASSERT(expr->type.dataType.IsObjectHandle());
								}
								else if (expr->type.dataType.GetTypeInfo() && expr->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE)
								{
									// For the ASHANDLE type we'll simply set the expression as a handle
									expr->type.dataType.MakeHandle(true);
								}

								if( !expr->type.dataType.IsObjectHandle() && !expr->type.dataType.SupportHandles())
								{
									Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, node);
								}
								expr->type.isExplicitHandle = true;
							}
						}
						assigned = CompileOverloadedDualOperator(node, &lexpr, expr, false, &ctx, useHndlAssign);
						if( assigned )
						{
							// Pop the resulting value
							if( !ctx.type.dataType.IsPrimitive() )
								ctx.bc.Instr(asBC_PopPtr);

							// Release the argument
							ProcessDeferredParams(&ctx);

							// Release temporary variable that may be allocated by the overloaded operator
							ReleaseTemporaryVariable(ctx.type, &ctx.bc);
						}
					}

					if( !assigned )
					{
						PrepareForAssignment(&lexpr.type.dataType, expr, node, false);

						// If the expression is constant and the variable also is constant
						// then mark the variable as pure constant. This will allow the compiler
						// to optimize expressions with this variable.
						if( type.IsReadOnly() && expr->type.isConstant )
						{
							isConstantExpression = true;
							*constantValue = expr->type.GetConstantQW();
						}

						// Add expression code to bytecode
						MergeExprBytecode(&ctx, expr);

						// Add byte code for storing value of expression in variable
						ctx.bc.AddCode(&lexpr.bc);

						PerformAssignment(&lexpr.type, &expr->type, &ctx.bc, errNode);

						// Release temporary variables used by expression
						ReleaseTemporaryVariable(expr->type, &ctx.bc);

						ctx.bc.Instr(asBC_PopPtr);

						ProcessDeferredParams(&ctx);
					}
				}
			}

			bc->AddCode(&ctx.bc);
		}
	}
	else
	{
		asASSERT( node == 0 );

		// Call the default constructor here, as no explicit initialization is done
		if( isVarGlobOrMem == 0 )
			CallDefaultConstructor(type, offset, IsVariableOnHeap(offset), bc, errNode);
		else if( isVarGlobOrMem == 1 )
			CallDefaultConstructor(type, offset, true, bc, errNode, isVarGlobOrMem);
		else if( isVarGlobOrMem == 2 )
		{
			if( !(type.IsObject() || type.IsFuncdef()) || type.IsReference() || (type.GetTypeInfo()->flags & asOBJ_REF) )
				CallDefaultConstructor(type, offset, true, bc, errNode, isVarGlobOrMem);
			else
				CallDefaultConstructor(type, offset, false, bc, errNode, isVarGlobOrMem);
		}
	}

	return isConstantExpression;
}

void asCCompiler::CompileInitList(asCExprValue *var, asCScriptNode *node, asCByteCode *bc, int isVarGlobOrMem)
{
	// Check if the type supports initialization lists
	if( var->dataType.GetTypeInfo() == 0 ||
		var->dataType.GetBehaviour()->listFactory == 0 )
	{
		asCString str;
		str.Format(TXT_INIT_LIST_CANNOT_BE_USED_WITH_s, var->dataType.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
		return;
	}

	// Construct the buffer with the elements

	// Find the list factory
	int funcId = var->dataType.GetBehaviour()->listFactory;
	asASSERT( engine->scriptFunctions[funcId]->listPattern );

	// TODO: runtime optimize: A future optimization should be to use the stack space directly
	//                         for small buffers so that the dynamic allocation is skipped

	// Create a new special object type for the lists. Both asCRestore and the
	// context exception handler will need this to know how to parse the buffer.
	asCObjectType *listPatternType = engine->GetListPatternType(funcId);

	// Allocate a temporary variable to hold the pointer to the buffer
	int bufferVar = AllocateVariable(asCDataType::CreateType(listPatternType, false), true);
	asUINT bufferSize = 0;

	// Evaluate all elements of the list
	asCExprContext valueExpr(engine);
	asCScriptNode *el = node;
	asSListPatternNode *patternNode = engine->scriptFunctions[listPatternType->templateSubTypes[0].GetBehaviour()->listFactory]->listPattern;
	int elementsInSubList = -1;
	int r = CompileInitListElement(patternNode, el, engine->GetTypeIdFromDataType(asCDataType::CreateType(listPatternType, false)), short(bufferVar), bufferSize, valueExpr.bc, elementsInSubList);
	asASSERT( r || patternNode == 0 );
	if (r < 0)
	{
		asCString msg;
		msg.Format(TXT_PREV_ERROR_WHILE_COMP_LIST_FOR_TYPE_s, var->dataType.Format(outFunc->nameSpace).AddressOf());
		Error(msg, node);
	}

	// After all values have been evaluated we know the final size of the buffer
	asCExprContext allocExpr(engine);
	allocExpr.bc.InstrSHORT_DW(asBC_AllocMem, short(bufferVar), bufferSize);

	// Merge the bytecode into the final sequence
	bc->AddCode(&allocExpr.bc);
	bc->AddCode(&valueExpr.bc);

	// The object itself is the last to be created and will receive the pointer to the buffer
	asCArray<asCExprContext *> args;
	asCExprContext arg1(engine);
	arg1.type.Set(asCDataType::CreatePrimitive(ttUInt, false));
	arg1.type.dataType.MakeReference(true);
	arg1.bc.InstrSHORT(asBC_PshVPtr, short(bufferVar));
	args.PushLast(&arg1);

	asCExprContext ctx(engine);

	if( var->isVariable )
	{
		asASSERT( isVarGlobOrMem == 0 );

		if( var->dataType.GetTypeInfo()->GetFlags() & asOBJ_REF )
		{
			ctx.bc.AddCode(&arg1.bc);

			// Call factory and store the handle in the given variable
			PerformFunctionCall(funcId, &ctx, false, &args, 0, true, var->stackOffset);
			ctx.bc.Instr(asBC_PopPtr);
		}
		else
		{
			// Call the constructor

			// When the object is allocated on the heap, the address where the
			// reference will be stored must be pushed on the stack before the
			// arguments. This reference on the stack is safe, even if the script
			// is suspended during the evaluation of the arguments.
			bool onHeap = IsVariableOnHeap(var->stackOffset);
			if( onHeap )
				ctx.bc.InstrSHORT(asBC_PSF, var->stackOffset);

			ctx.bc.AddCode(&arg1.bc);

			// When the object is allocated on the stack, the address to the
			// object is pushed on the stack after the arguments as the object pointer
			if( !onHeap )
				ctx.bc.InstrSHORT(asBC_PSF, var->stackOffset);

			PerformFunctionCall(funcId, &ctx, onHeap, &args, CastToObjectType(var->dataType.GetTypeInfo()));

			// Mark the object in the local variable as initialized
			ctx.bc.ObjInfo(var->stackOffset, asOBJ_INIT);
		}
	}
	else
	{
		if( var->dataType.GetTypeInfo()->GetFlags() & asOBJ_REF )
		{
			ctx.bc.AddCode(&arg1.bc);

			PerformFunctionCall(funcId, &ctx, false, &args);

			ctx.bc.Instr(asBC_RDSPtr);
			if( isVarGlobOrMem == 1 )
			{
				// Store the returned handle in the global variable
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[var->stackOffset]->GetAddressOfValue());
			}
			else
			{
				// Store the returned handle in the member
				ctx.bc.InstrSHORT(asBC_PSF, 0);
				ctx.bc.Instr(asBC_RDSPtr);
				ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)var->stackOffset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
			}
			if (var->dataType.IsFuncdef())
				ctx.bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
			else
				ctx.bc.InstrPTR(asBC_REFCPY, var->dataType.GetTypeInfo());
			ctx.bc.Instr(asBC_PopPtr);
			ReleaseTemporaryVariable(ctx.type.stackOffset, &ctx.bc);
		}
		else
		{
			bool onHeap = true;

			// Put the address where the object pointer will be placed on the stack
			if( isVarGlobOrMem == 1 )
				ctx.bc.InstrPTR(asBC_PGA, engine->globalProperties[var->stackOffset]->GetAddressOfValue());
			else
			{
				onHeap = !(var->dataType.IsObject() || var->dataType.IsFuncdef()) || var->dataType.IsReference() || (var->dataType.GetTypeInfo()->flags & asOBJ_REF);
				if( onHeap )
				{
					ctx.bc.InstrSHORT(asBC_PSF, 0);
					ctx.bc.Instr(asBC_RDSPtr);
					ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)var->stackOffset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
				}
			}

			// Add the address of the list buffer as the argument
			ctx.bc.AddCode(&arg1.bc);

			if( !onHeap )
			{
				ctx.bc.InstrSHORT(asBC_PSF, 0);
				ctx.bc.Instr(asBC_RDSPtr);
				ctx.bc.InstrSHORT_DW(asBC_ADDSi, (short)var->stackOffset, engine->GetTypeIdFromDataType(asCDataType::CreateType(outFunc->objectType, false)));
			}

			// Call the ALLOC instruction to allocate memory and invoke constructor
			PerformFunctionCall(funcId, &ctx, onHeap, &args, CastToObjectType(var->dataType.GetTypeInfo()));
		}
	}

	bc->AddCode(&ctx.bc);

	// Free the temporary buffer. The FREE instruction will make sure to destroy
	// each element in the buffer so there is no need to do this manually
	bc->InstrW_PTR(asBC_FREE, short(bufferVar), listPatternType);
	ReleaseTemporaryVariable(bufferVar, bc);
}

int asCCompiler::CompileInitListElement(asSListPatternNode *&patternNode, asCScriptNode *&valueNode, int bufferTypeId, short bufferVar, asUINT &bufferSize, asCByteCode &bcInit, int &elementsInSubList)
{
	if( patternNode->type == asLPT_START )
	{
		if( valueNode == 0 || valueNode->nodeType != snInitList )
		{
			Error(TXT_EXPECTED_LIST, valueNode);
			return -1;
		}

		// Compile all values until asLPT_END
		patternNode = patternNode->next;
		asCScriptNode *node = valueNode->firstChild;
		while( patternNode->type != asLPT_END )
		{
			// Check for missing value here, else the error reporting will not have a source position to report the error for
			if( node == 0 && patternNode->type == asLPT_TYPE )
			{
				Error(TXT_NOT_ENOUGH_VALUES_FOR_LIST, valueNode);
				return -1;
			}

			asCScriptNode *errNode = node;
			int r = CompileInitListElement(patternNode, node, bufferTypeId, bufferVar, bufferSize, bcInit, elementsInSubList);
			if( r < 0 ) return r;

			if( r == 1 )
			{
				asASSERT( engine->ep.disallowEmptyListElements );
				// Empty elements in the middle are not allowed
				Error(TXT_EMPTY_LIST_ELEMENT_IS_NOT_ALLOWED, errNode);
			}

			asASSERT( patternNode );
		}

		if( node )
		{
			Error(TXT_TOO_MANY_VALUES_FOR_LIST, valueNode);
			return -1;
		}

		// Move to the next node
		valueNode = valueNode->next;
		patternNode = patternNode->next;
	}
	else if( patternNode->type == asLPT_REPEAT || patternNode->type == asLPT_REPEAT_SAME )
	{
		// TODO: list: repeat_inner should make sure the list has the same size as the inner list, i.e. square area
		// TODO: list: repeat_prev should make sure the list is the same size as the previous

		asEListPatternNodeType repeatType = patternNode->type;
		asCScriptNode *firstValue = valueNode;

		// The following values will be repeated N times
		patternNode = patternNode->next;

		// Keep track of the patternNode so it can be reset
		asSListPatternNode *nextNode = patternNode;

		// Align the buffer size to 4 bytes in case previous value was smaller than 4 bytes
		if( bufferSize & 0x3 )
			bufferSize += 4 - (bufferSize & 0x3);

		// The first dword will hold the number of elements in the list
		asDWORD currSize = bufferSize;
		bufferSize += 4;
		asUINT countElements = 0;

		int elementsInSubSubList = -1;

		asCExprContext ctx(engine);
		while( valueNode )
		{
			patternNode = nextNode;
			asCScriptNode *errNode = valueNode;
			int r = CompileInitListElement(patternNode, valueNode, bufferTypeId, bufferVar, bufferSize, ctx.bc, elementsInSubSubList);
			if( r < 0 ) return r;

			if( r == 0 )
				countElements++;
			else
			{
				asASSERT( r == 1 && engine->ep.disallowEmptyListElements );
				if( valueNode )
				{
					// Empty elements in the middle are not allowed
					Error(TXT_EMPTY_LIST_ELEMENT_IS_NOT_ALLOWED, errNode);
				}
			}
		}

		if( countElements == 0 )
		{
			// Skip the sub pattern that was expected to be repeated, otherwise the caller will try to match these when we return
			patternNode = nextNode;
			if( patternNode->type == asLPT_TYPE )
				patternNode = patternNode->next;
			else if( patternNode->type == asLPT_START )
			{
				int subCount = 1;
				do
				{
					patternNode = patternNode->next;
					if( patternNode->type == asLPT_START )
						subCount++;
					else if( patternNode->type == asLPT_END )
						subCount--;
				} while( subCount > 0 );
				patternNode = patternNode->next;
			}
		}

		// For repeat_same each repeated sublist must have the same size to form a rectangular array
		if( repeatType == asLPT_REPEAT_SAME && elementsInSubList != -1 && asUINT(elementsInSubList) != countElements )
		{
			if( countElements < asUINT(elementsInSubList) )
				Error(TXT_NOT_ENOUGH_VALUES_FOR_LIST, firstValue);
			else
				Error(TXT_TOO_MANY_VALUES_FOR_LIST, firstValue);

			return -1;
		}
		else
		{
			// Return to caller the amount of elments in this sublist
			elementsInSubList = countElements;
		}

		// The first dword in the buffer will hold the number of elements
		bcInit.InstrSHORT_DW_DW(asBC_SetListSize, bufferVar, currSize, countElements);

		// Add the values
		bcInit.AddCode(&ctx.bc);
	}
	else if( patternNode->type == asLPT_TYPE )
	{
		bool isEmpty = false;

		// Determine the size of the element
		asUINT size = 0;

		asCDataType dt = reinterpret_cast<asSListPatternDataTypeNode*>(patternNode)->dataType;

		if( valueNode->nodeType == snAssignment || valueNode->nodeType == snInitList )
		{
			asCExprContext lctx(engine);
			asCExprContext rctx(engine);

			if( valueNode->nodeType == snAssignment )
			{
				// Compile the assignment expression
				CompileAssignment(valueNode, &rctx);

				if( dt.GetTokenType() == ttQuestion )
				{
					// Make sure the type is not ambiguous
					DetermineSingleFunc(&rctx, valueNode);

					// We now know the type
					dt = rctx.type.dataType;
					dt.MakeReadOnly(false);
					dt.MakeReference(false);

					// Values on the list must be aligned to 32bit boundaries, except if the type is smaller than 32bit.
					if( bufferSize & 0x3 )
						bufferSize += 4 - (bufferSize & 0x3);

					// When value assignment for reference types us disabled, make sure all ref types are passed in as handles
					if (engine->ep.disallowValueAssignForRefType && dt.SupportHandles())
						dt.MakeHandle(true);

					// Place the type id in the buffer
					bcInit.InstrSHORT_DW_DW(asBC_SetListType, bufferVar, bufferSize, engine->GetTypeIdFromDataType(dt));
					bufferSize += 4;
				}
			}
			else if( valueNode->nodeType == snInitList )
			{
				if( dt.GetTokenType() == ttQuestion )
				{
					// Can't use init lists with var type as it is not possible to determine what type should be allocated
					asCString str;
					str.Format(TXT_INIT_LIST_CANNOT_BE_USED_WITH_s, "?");
					Error(str.AddressOf(), valueNode);
					rctx.type.SetDummy();
					dt = rctx.type.dataType;
				}
				else
				{
					// Allocate a temporary variable that will be initialized with the list
					int offset = AllocateVariable(dt, true);

					rctx.type.Set(dt);
					rctx.type.isVariable = true;
					rctx.type.isTemporary = true;
					rctx.type.stackOffset = (short)offset;

					CompileInitList(&rctx.type, valueNode, &rctx.bc, 0);

					// Put the object on the stack
					rctx.bc.InstrSHORT(asBC_PSF, rctx.type.stackOffset);

					// It is a reference that we place on the stack
					rctx.type.dataType.MakeReference(true);
				}
			}

			// Determine size of the element
			if( dt.IsPrimitive() || (!dt.IsNullHandle() && (dt.GetTypeInfo()->flags & asOBJ_VALUE)) )
				size = dt.GetSizeInMemoryBytes();
			else
				size = AS_PTR_SIZE*4;

			// Values on the list must be aligned to 32bit boundaries, except if the type is smaller than 32bit.
			if( size >= 4 && (bufferSize & 0x3) )
				bufferSize += 4 - (bufferSize & 0x3);

			// Compile the lvalue
			lctx.bc.InstrSHORT_DW(asBC_PshListElmnt, bufferVar, bufferSize);
			lctx.type.Set(dt);
			lctx.type.isLValue = true;
			if( dt.IsPrimitive() )
			{
				lctx.bc.Instr(asBC_PopRPtr);
				lctx.type.dataType.MakeReference(true);
			}
			else if( dt.IsObjectHandle() ||
					 dt.GetTypeInfo()->flags & asOBJ_REF )
			{
				lctx.type.isExplicitHandle = true;
				lctx.type.dataType.MakeReference(true);
			}
			else
			{
				asASSERT( dt.GetTypeInfo()->flags & asOBJ_VALUE );

				// Make sure the object has been constructed before the assignment
				// TODO: runtime optimize: Use copy constructor instead of assignment to initialize the objects
				asSTypeBehaviour *beh = dt.GetBehaviour();
				int func = 0;
				if( beh ) func = beh->construct;
				if( func == 0 && (dt.GetTypeInfo()->flags & asOBJ_POD) == 0 )
				{
					asCString str;
					str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, dt.GetTypeInfo()->GetName());
					Error(str, valueNode);
				}
				else if( func )
				{
					// Call the constructor as a normal function
					bcInit.InstrSHORT_DW(asBC_PshListElmnt, bufferVar, bufferSize);

					asCExprContext ctx(engine);
					PerformFunctionCall(func, &ctx, false, 0, CastToObjectType(dt.GetTypeInfo()));
					bcInit.AddCode(&ctx.bc);
				}
			}

			if( lctx.type.dataType.IsNullHandle() )
			{
				// Don't add any code to assign a null handle. RefCpy doesn't work without a known type.
				// The buffer is already initialized to zero in asBC_AllocMem anyway.
				asASSERT( rctx.bc.GetLastInstr() == asBC_PshNull );
				asASSERT( reinterpret_cast<asSListPatternDataTypeNode*>(patternNode)->dataType.GetTokenType() == ttQuestion );
			}
			else
			{
				asCExprContext ctx(engine);
				DoAssignment(&ctx, &lctx, &rctx, valueNode, valueNode, ttAssignment, valueNode);

				if( !ctx.type.dataType.IsPrimitive() )
					ctx.bc.Instr(asBC_PopPtr);

				// Release temporary variables used by expression
				ReleaseTemporaryVariable(ctx.type, &ctx.bc);

				ProcessDeferredParams(&ctx);

				bcInit.AddCode(&ctx.bc);
			}
		}
		else
		{
			if( builder->engine->ep.disallowEmptyListElements )
			{
				// Empty elements are not allowed, except if it is the last in the list
				isEmpty = true;
			}
			else
			{
				// There is no specific value so we need to fill it with a default value
				if( dt.GetTokenType() == ttQuestion )
				{
					// Values on the list must be aligned to 32bit boundaries, except if the type is smaller than 32bit.
					if( bufferSize & 0x3 )
						bufferSize += 4 - (bufferSize & 0x3);

					// Place the type id for a null handle in the buffer
					bcInit.InstrSHORT_DW_DW(asBC_SetListType, bufferVar, bufferSize, 0);
					bufferSize += 4;

					dt = asCDataType::CreateNullHandle();

					// No need to initialize the handle as the buffer is already initialized with zeroes
				}
				else if( dt.GetTypeInfo() && dt.GetTypeInfo()->flags & asOBJ_VALUE )
				{
					// For value types with default constructor we need to call the constructor
					asSTypeBehaviour *beh = dt.GetBehaviour();
					int func = 0;
					if( beh ) func = beh->construct;
					if( func == 0 && (dt.GetTypeInfo()->flags & asOBJ_POD) == 0 )
					{
						asCString str;
						str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, dt.GetTypeInfo()->GetName());
						Error(str, valueNode);
					}
					else if( func )
					{
						// Values on the list must be aligned to 32bit boundaries, except if the type is smaller than 32bit.
						if( bufferSize & 0x3 )
							bufferSize += 4 - (bufferSize & 0x3);

						// Call the constructor as a normal function
						bcInit.InstrSHORT_DW(asBC_PshListElmnt, bufferVar, bufferSize);

						asCExprContext ctx(engine);
						PerformFunctionCall(func, &ctx, false, 0, CastToObjectType(dt.GetTypeInfo()));
						bcInit.AddCode(&ctx.bc);
					}
				}
				else if( !dt.IsObjectHandle() && dt.GetTypeInfo() && dt.GetTypeInfo()->flags & asOBJ_REF )
				{
					// For ref types (not handles) we need to call the default factory
					asSTypeBehaviour *beh = dt.GetBehaviour();
					int func = 0;
					if( beh ) func = beh->factory;
					if( func == 0 )
					{
						asCString str;
						str.Format(TXT_NO_DEFAULT_CONSTRUCTOR_FOR_s, dt.GetTypeInfo()->GetName());
						Error(str, valueNode);
					}
					else if( func )
					{
						asCExprContext rctx(engine);
						PerformFunctionCall(func, &rctx, false, 0, CastToObjectType(dt.GetTypeInfo()));

						// Values on the list must be aligned to 32bit boundaries, except if the type is smaller than 32bit.
						if( bufferSize & 0x3 )
							bufferSize += 4 - (bufferSize & 0x3);

						asCExprContext lctx(engine);
						lctx.bc.InstrSHORT_DW(asBC_PshListElmnt, bufferVar, bufferSize);
						lctx.type.Set(dt);
						lctx.type.isLValue = true;
						lctx.type.isExplicitHandle = true;
						lctx.type.dataType.MakeReference(true);

						asCExprContext ctx(engine);
						DoAssignment(&ctx, &lctx, &rctx, valueNode, valueNode, ttAssignment, valueNode);

						if( !ctx.type.dataType.IsPrimitive() )
							ctx.bc.Instr(asBC_PopPtr);

						// Release temporary variables used by expression
						ReleaseTemporaryVariable(ctx.type, &ctx.bc);

						ProcessDeferredParams(&ctx);

						bcInit.AddCode(&ctx.bc);
					}
				}
			}
		}

		if( !isEmpty )
		{
			// Determine size of the element
			if( dt.IsPrimitive() || (!dt.IsNullHandle() && (dt.GetTypeInfo()->flags & asOBJ_VALUE)) )
				size = dt.GetSizeInMemoryBytes();
			else
				size = AS_PTR_SIZE*4;
			asASSERT( size <= 4 || (size & 0x3) == 0 );

			bufferSize += size;
		}

		// Move to the next element
		patternNode = patternNode->next;
		valueNode = valueNode->next;

		if( isEmpty )
		{
			// The caller will determine if the empty element should be ignored or not
			return 1;
		}
	}
	else
		asASSERT( false );

	return 0;
}

void asCCompiler::CompileStatement(asCScriptNode *statement, bool *hasReturn, asCByteCode *bc)
{
	// Don't clear the hasReturn flag if this is an empty statement
	// to avoid false errors of 'not all paths return'
	if( statement->nodeType != snExpressionStatement || statement->firstChild )
		*hasReturn = false;

	if (statement->nodeType == snStatementBlock)
		CompileStatementBlock(statement, true, hasReturn, bc);
	else if (statement->nodeType == snIf)
		CompileIfStatement(statement, hasReturn, bc);
	else if (statement->nodeType == snFor)
		CompileForStatement(statement, bc);
	else if (statement->nodeType == snWhile)
		CompileWhileStatement(statement, bc);
	else if (statement->nodeType == snDoWhile)
		CompileDoWhileStatement(statement, bc);
	else if (statement->nodeType == snExpressionStatement)
		CompileExpressionStatement(statement, bc);
	else if (statement->nodeType == snBreak)
		CompileBreakStatement(statement, bc);
	else if (statement->nodeType == snContinue)
		CompileContinueStatement(statement, bc);
	else if (statement->nodeType == snSwitch)
		CompileSwitchStatement(statement, hasReturn, bc);
	else if (statement->nodeType == snTryCatch)
		CompileTryCatch(statement, hasReturn, bc);
	else if (statement->nodeType == snReturn)
	{
		CompileReturnStatement(statement, bc);
		*hasReturn = true;
	}
	else
		asASSERT(false);
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
	asCExprContext expr(engine);
	CompileAssignment(snode->firstChild, &expr);

	// Verify that the expression is a primitive type
	if( !expr.type.dataType.IsIntegerType() && !expr.type.dataType.IsUnsignedType() )
	{
		Error(TXT_SWITCH_MUST_BE_INTEGRAL, snode->firstChild);
		return;
	}

	if( ProcessPropertyGetAccessor(&expr, snode) < 0 )
		return;

	// TODO: Need to support 64bit integers
	// Convert the expression to a 32bit variable
	asCDataType to;
	if( expr.type.dataType.IsIntegerType() )
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
			asCExprContext c(engine);
			CompileExpression(cnode->firstChild, &c);

			// Verify that the result is a constant
			if( !c.type.isConstant )
				Error(TXT_SWITCH_CASE_MUST_BE_CONSTANT, cnode->firstChild);

			// Verify that the result is an integral number
			if (!c.type.dataType.IsIntegerType() && !c.type.dataType.IsUnsignedType())
				Error(TXT_SWITCH_MUST_BE_INTEGRAL, cnode->firstChild);
			else
			{
				ImplicitConversion(&c, to, cnode->firstChild, asIC_IMPLICIT_CONV, true);

				// Has this case been declared already?
				if (caseValues.IndexOf(c.type.GetConstantDW()) >= 0)
					Error(TXT_DUPLICATE_SWITCH_CASE, cnode->firstChild);

				// TODO: Optimize: We can insert the numbers sorted already

				// Store constant for later use
				caseValues.PushLast(c.type.GetConstantDW());

				// Reserve label for this case
				caseLabels.PushLast(nextLabel++);
			}
		}
		else
		{
			// TODO: It shouldn't be necessary for the default case to be the last one.
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

	// TODO: runtime optimize: We could possibly optimize this even more by doing a
	//                         binary search instead of a linear search through the ranges

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
			for( int i = caseValues[index]; i <= maxRange; i++ )
			{
				if( caseValues[index] == i )
					expr.bc.InstrINT(asBC_JMP, caseLabels[index++]);
				else
					expr.bc.InstrINT(asBC_JMP, defaultLabel);
			}

			expr.bc.Label((short)nextRangeLabel);
		}
		else
		{
			// Simply make a comparison with each value
			for( int i = ranges[range]; i < index; ++i )
			{
				tmpOffset = AllocateVariable(asCDataType::CreatePrimitive(ttInt, false), true);
				expr.bc.InstrSHORT_DW(asBC_SetV4, (short)tmpOffset, caseValues[i]);
				expr.bc.InstrW_W(asBC_CMPi, offset, tmpOffset);
				expr.bc.InstrDWORD(asBC_JZ, caseLabels[i]);
				ReleaseTemporaryVariable(tmpOffset, &expr.bc);
			}
		}
	}

	// Catch any value that falls trough
	expr.bc.InstrINT(asBC_JMP, defaultLabel);

	// Release the temporary variable previously stored
	ReleaseTemporaryVariable(expr.type, &expr.bc);

	// TODO: optimize: Should optimize each piece individually
	expr.bc.OptimizeLocally(tempVariableOffsets);

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
	bool hasUnreachableCode = false;
	while( node )
	{
		if( !hasUnreachableCode && (hasReturn || isFinished) )
		{
			hasUnreachableCode = true;
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

void asCCompiler::CompileTryCatch(asCScriptNode *node, bool *hasReturn, asCByteCode *bc)
{
	// We will use one label before and another after the catch statement
	int beforeCatchLabel = nextLabel++;
	int afterCatchLabel = nextLabel++;

	// Compile the try block
	bool hasReturnTry;
	asCByteCode tryBC(engine);
	CompileStatement(node->firstChild, &hasReturnTry, &tryBC);

	// Add marker to unwind exception until here, then jump to catch block
	bc->TryBlock((short)beforeCatchLabel);

	// Add the byte code
	LineInstr(bc, node->firstChild->tokenPos);
	bc->AddCode(&tryBC);

	// Add jump to after catch
	bc->InstrINT(asBC_JMP, afterCatchLabel);

	// Compile the catch block
	bool hasReturnCatch;
	asCByteCode catchBC(engine);
	CompileStatement(node->firstChild->next, &hasReturnCatch, &catchBC);

	// Add marker to tell bytecode optimizer that this is a catch
	// block so the code is not removed as unreachable code
	bc->Label((short)beforeCatchLabel);

	// Add the byte code
	LineInstr(bc, node->firstChild->next->tokenPos);
	bc->AddCode(&catchBC);

	// Add the label after catch
	bc->Label((short)afterCatchLabel);

	// The try/catch statement only has return (i.e. no code after
	// the try/catch block will be executed) if both blocks have
	*hasReturn = hasReturnTry && hasReturnCatch;
}

void asCCompiler::CompileIfStatement(asCScriptNode *inode, bool *hasReturn, asCByteCode *bc)
{
	// We will use one label for the if statement
	// and possibly another for the else statement
	int afterLabel = nextLabel++;

	// Compile the expression
	asCExprContext expr(engine);
	int r = CompileAssignment(inode->firstChild, &expr);
	if( r == 0 )
	{
		// Allow value types to be converted to bool using 'bool opImplConv()'
		if( expr.type.dataType.GetTypeInfo() && (expr.type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
			ImplicitConversion(&expr, asCDataType::CreatePrimitive(ttBool, false), inode, asIC_IMPLICIT_CONV);

		if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
			Error(TXT_EXPR_MUST_BE_BOOL, inode->firstChild);
		else
		{
			if( !expr.type.isConstant )
			{
				if( ProcessPropertyGetAccessor(&expr, inode) < 0 )
					return;
				ConvertToVariable(&expr);
				ProcessDeferredParams(&expr);

				// Add a test
				expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
				expr.bc.Instr(asBC_ClrHi);
				expr.bc.InstrDWORD(asBC_JZ, afterLabel);
				ReleaseTemporaryVariable(expr.type, &expr.bc);

				expr.bc.OptimizeLocally(tempVariableOffsets);
				bc->AddCode(&expr.bc);
			}
#if AS_SIZEOF_BOOL == 1
			else if( expr.type.GetConstantB() == 0 )
#else
			else if (expr.type.GetConstantDW() == 0)
#endif
			{
				// Jump to the else case
				bc->InstrINT(asBC_JMP, afterLabel);

				// TODO: Should we warn that the expression will always go to the else?
			}
		}
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
	// Add a variable scope that will be used by CompileBreak/Continue to know where to stop deallocating variables
	AddVariableScope(true, true);

	// We will use three labels for the for loop
	int conditionLabel = nextLabel++;
	int afterLabel = nextLabel++;
	int continueLabel = nextLabel++;
	int insideLabel = nextLabel++;

	continueLabels.PushLast(continueLabel);
	breakLabels.PushLast(afterLabel);

	//---------------------------------------
	// Compile the initialization statement
	asCByteCode initBC(engine);
	LineInstr(&initBC, fnode->firstChild->tokenPos);
	if( fnode->firstChild->nodeType == snDeclaration )
		CompileDeclaration(fnode->firstChild, &initBC);
	else
		CompileExpressionStatement(fnode->firstChild, &initBC);

	//-----------------------------------
	// Compile the condition statement
	asCExprContext expr(engine);
	asCScriptNode *second = fnode->firstChild->next;
	if( second->firstChild )
	{
		int r = CompileAssignment(second->firstChild, &expr);
		if( r >= 0 )
		{
			// Allow value types to be converted to bool using 'bool opImplConv()'
			if( expr.type.dataType.GetTypeInfo() && (expr.type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
				ImplicitConversion(&expr, asCDataType::CreatePrimitive(ttBool, false), second->firstChild, asIC_IMPLICIT_CONV);

			if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
				Error(TXT_EXPR_MUST_BE_BOOL, second);
			else
			{
				if( ProcessPropertyGetAccessor(&expr, second) < 0 )
					return;
				ConvertToVariable(&expr);
				ProcessDeferredParams(&expr);

				// If expression is false exit the loop
				expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
				expr.bc.Instr(asBC_ClrHi);
				expr.bc.InstrDWORD(asBC_JNZ, insideLabel);
				ReleaseTemporaryVariable(expr.type, &expr.bc);

				expr.bc.OptimizeLocally(tempVariableOffsets);

				// Prepend the line instruction for the condition
				asCByteCode tmp(engine);
				LineInstr(&tmp, second->firstChild->tokenPos);
				tmp.AddCode(&expr.bc);
				expr.bc.AddCode(&tmp);
			}
		}
	}

	//---------------------------
	// Compile the increment statement(s)
	asCByteCode nextBC(engine);
	asCScriptNode *cnode = second->next;
	while( cnode && cnode->nodeType == snExpressionStatement && cnode != fnode->lastChild )
	{
		LineInstr(&nextBC, cnode->tokenPos);
		CompileExpressionStatement(cnode, &nextBC);
		cnode = cnode->next;
	}

	//------------------------------
	// Compile loop statement
	bool hasReturn;
	asCByteCode forBC(engine);
	CompileStatement(fnode->lastChild, &hasReturn, &forBC);

	//-------------------------------
	// Join the code pieces
	bc->AddCode(&initBC);
	bc->InstrDWORD(asBC_JMP, conditionLabel);

	bc->Label((short)insideLabel);

	// Add a suspend bytecode inside the loop to guarantee
	// that the application can suspend the execution
	bc->Instr(asBC_SUSPEND);
	bc->InstrPTR(asBC_JitEntry, 0);

	LineInstr(bc, fnode->lastChild->tokenPos);
	bc->AddCode(&forBC);

	bc->Label((short)continueLabel);
	bc->AddCode(&nextBC);

	bc->Label((short)conditionLabel);
	if( expr.bc.GetLastInstr() == -1 )
		// There is no condition, so we just always jump
		bc->InstrDWORD(asBC_JMP, insideLabel);
	else
		bc->AddCode(&expr.bc);

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
	asCExprContext expr(engine);
	int r = CompileAssignment(wnode->firstChild, &expr);
	if( r == 0 )
	{
		// Allow value types to be converted to bool using 'bool opImplConv()'
		if( expr.type.dataType.GetTypeInfo() && (expr.type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
			ImplicitConversion(&expr, asCDataType::CreatePrimitive(ttBool, false), wnode->firstChild, asIC_IMPLICIT_CONV);

		if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
			Error(TXT_EXPR_MUST_BE_BOOL, wnode->firstChild);
		else
		{
			if( ProcessPropertyGetAccessor(&expr, wnode) < 0 )
				return;
			ConvertToVariable(&expr);
			ProcessDeferredParams(&expr);

			// Jump to end of statement if expression is false
			expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
			expr.bc.Instr(asBC_ClrHi);
			expr.bc.InstrDWORD(asBC_JZ, afterLabel);
			ReleaseTemporaryVariable(expr.type, &expr.bc);

			expr.bc.OptimizeLocally(tempVariableOffsets);
			bc->AddCode(&expr.bc);
		}
	}

	// Add a suspend bytecode inside the loop to guarantee
	// that the application can suspend the execution
	bc->Instr(asBC_SUSPEND);
	bc->InstrPTR(asBC_JitEntry, 0);

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
	bc->InstrPTR(asBC_JitEntry, 0);

	// Add a line instruction
	LineInstr(bc, wnode->lastChild->tokenPos);

	// Compile expression
	asCExprContext expr(engine);
	CompileAssignment(wnode->lastChild, &expr);

	// Allow value types to be converted to bool using 'bool opImplConv()'
	if( expr.type.dataType.GetTypeInfo() && (expr.type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
		ImplicitConversion(&expr, asCDataType::CreatePrimitive(ttBool, false), wnode->lastChild, asIC_IMPLICIT_CONV);

	if( !expr.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		Error(TXT_EXPR_MUST_BE_BOOL, wnode->firstChild);
	else
	{
		if( ProcessPropertyGetAccessor(&expr, wnode) < 0 )
			return;
		ConvertToVariable(&expr);
		ProcessDeferredParams(&expr);
		
		// Jump to next iteration if expression is true
		expr.bc.InstrSHORT(asBC_CpyVtoR4, expr.type.stackOffset);
		expr.bc.Instr(asBC_ClrHi);
		expr.bc.InstrDWORD(asBC_JNZ, beforeLabel);
		ReleaseTemporaryVariable(expr.type, &expr.bc);

		expr.bc.OptimizeLocally(tempVariableOffsets);
		bc->AddCode(&expr.bc);
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
		asCExprContext expr(engine);
		CompileAssignment(enode->firstChild, &expr);

		// Must not have unused ambiguous names
		if( expr.IsClassMethod() || expr.IsGlobalFunc() )
			Error(TXT_INVALID_EXPRESSION_AMBIGUOUS_NAME, enode);

		// Must not have unused anonymous functions
		if( expr.IsLambda() )
			Error(TXT_INVALID_EXPRESSION_LAMBDA, enode);

		// If we get here and there is still an unprocessed property
		// accessor, then process it as a get access. Don't call if there is
		// already a compile error, or we might report an error that is not valid
		if( !hasCompileErrors )
			if( ProcessPropertyGetAccessor(&expr, enode) < 0 )
				return;

		// Pop the value from the stack
		if( !expr.type.dataType.IsPrimitive() )
			expr.bc.Instr(asBC_PopPtr);

		// Release temporary variables used by expression
		ReleaseTemporaryVariable(expr.type, &expr.bc);

		ProcessDeferredParams(&expr);

		expr.bc.OptimizeLocally(tempVariableOffsets);
		bc->AddCode(&expr.bc);
	}
}

void asCCompiler::PrepareTemporaryVariable(asCScriptNode *node, asCExprContext *ctx, bool forceOnHeap)
{
	// The input can be either an object or funcdef, either as handle or reference
	asASSERT(ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef());

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
			ctx->bc.Instr(asBC_PopPtr);
			ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			ctx->type.dataType.MakeReference(IsVariableOnHeap(ctx->type.stackOffset));
		}

		return;
	}

	// Allocate temporary variable
	asCDataType dt = ctx->type.dataType;
	dt.MakeReference(false);
	dt.MakeReadOnly(false);

	int offset = AllocateVariable(dt, true, forceOnHeap);

	// Objects stored on the stack are not considered references
	dt.MakeReference(IsVariableOnHeap(offset));

	asCExprValue lvalue;
	lvalue.Set(dt);
	lvalue.isExplicitHandle = ctx->type.isExplicitHandle;
	bool isExplicitHandle = ctx->type.isExplicitHandle;

	bool prevIsTemp = ctx->type.isTemporary;
	int prevStackOffset = ctx->type.stackOffset;

	CompileInitAsCopy(dt, offset, &ctx->bc, ctx, node, false);

	// Release the previous temporary variable if it hasn't already been released
	if( prevIsTemp && tempVariables.Exists(prevStackOffset) )
		ReleaseTemporaryVariable(prevStackOffset, &ctx->bc);

	// Push the reference to the temporary variable on the stack
	ctx->bc.InstrSHORT(asBC_PSF, (short)offset);

	ctx->type.Set(dt);
	ctx->type.isTemporary = true;
	ctx->type.stackOffset = (short)offset;
	ctx->type.isVariable = true;
	ctx->type.isExplicitHandle = isExplicitHandle;
	ctx->type.dataType.MakeReference(IsVariableOnHeap(offset));
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
		asCExprContext expr(engine);
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
			if( !(v->type.IsEqualExceptConst(expr.type.dataType) ||
				  ((expr.type.dataType.IsObject() || expr.type.dataType.IsFuncdef()) &&
				   !expr.type.dataType.IsObjectHandle() &&
				   v->type.IsEqualExceptRefAndConst(expr.type.dataType))) ||
				(!v->type.IsReadOnly() && expr.type.dataType.IsReadOnly()) )
			{
				// Clean up the potential deferred parameters
				ProcessDeferredParams(&expr);
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, expr.type.dataType.Format(outFunc->nameSpace).AddressOf(), v->type.Format(outFunc->nameSpace).AddressOf());
				Error(str, rnode);
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

			// Can't return the reference if could point to a local variable
			if( expr.type.isRefToLocal )
			{
				ProcessDeferredParams(&expr);
				Error(TXT_REF_CANT_BE_TO_LOCAL_VAR, rnode);
				return;
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
				if( !expr.type.dataType.IsObjectHandle() &&
					expr.type.dataType.IsReference() )
					expr.bc.Instr(asBC_RDSPtr);

				expr.bc.Instr(asBC_PopRPtr);
			}

			// There are no temporaries to release so we're done
		}
		else // if( !v->type.IsReference() )
		{
			if( ProcessPropertyGetAccessor(&expr, rnode) < 0 )
				return;

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
					str.Format(TXT_NO_CONVERSION_s_TO_s, expr.type.dataType.Format(outFunc->nameSpace).AddressOf(), v->type.Format(outFunc->nameSpace).AddressOf());
					Error(str, rnode);
					return;
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
			else if( v->type.IsObject() || v->type.IsFuncdef() )
			{
				// Value types are returned on the stack, in a location
				// that has been reserved by the calling function.
				if( outFunc->DoesReturnOnStack() )
				{
					// TODO: runtime optimize: If the return type has a constructor that takes the type of the expression,
					//                         it should be called directly instead of first converting the expression and
					//                         then copy the value.
					if( !v->type.IsEqualExceptRefAndConst(expr.type.dataType) )
					{
						ImplicitConversion(&expr, v->type, rnode->firstChild, asIC_IMPLICIT_CONV);
						if( !v->type.IsEqualExceptRefAndConst(expr.type.dataType) )
						{
							asCString str;
							str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, expr.type.dataType.Format(outFunc->nameSpace).AddressOf(), v->type.Format(outFunc->nameSpace).AddressOf());
							Error(str, rnode->firstChild);
							return;
						}
					}

					int offset = outFunc->objectType ? -AS_PTR_SIZE : 0;
					CompileInitAsCopy(v->type, offset, &expr.bc, &expr, rnode->firstChild, true);

					// Clean up the local variables and process deferred parameters
					DestroyVariables(&expr.bc);
					ProcessDeferredParams(&expr);
				}
				else
				{
					asASSERT( (v->type.GetTypeInfo()->flags & asOBJ_REF) || v->type.IsFuncdef() );

					// Prepare the expression to be loaded into the object
					// register. This will place the reference in local variable
					PrepareArgument(&v->type, &expr, rnode->firstChild, false, 0);

					// Pop the reference to the temporary variable
					expr.bc.Instr(asBC_PopPtr);

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
		}

		expr.bc.OptimizeLocally(tempVariableOffsets);
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
	if( variables == 0 )
	{
		// Out of memory
		return;
	}
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

void asCCompiler::Error(const asCString &msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteError(script->name, msg, r, c);

	hasCompileErrors = true;
}

void asCCompiler::Warning(const asCString &msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteWarning(script->name, msg, r, c);
}

void asCCompiler::Information(const asCString &msg, asCScriptNode *node)
{
	asCString str;

	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	builder->WriteInfo(script->name, msg, r, c, false);
}

void asCCompiler::PrintMatchingFuncs(asCArray<int> &funcs, asCScriptNode *node, asCObjectType *inType)
{
	int r = 0, c = 0;
	asASSERT( node );
	if( node ) script->ConvertPosToRowCol(node->tokenPos, &r, &c);

	for( unsigned int n = 0; n < funcs.GetLength(); n++ )
	{
		asCScriptFunction *func = builder->GetFunctionDescription(funcs[n]);
		if( inType && func->funcType == asFUNC_VIRTUAL )
			func = inType->virtualFunctionTable[func->vfTableIdx];

		builder->WriteInfo(script->name, func->GetDeclaration(true, false, true), r, c, false);

		if (func->objectType && (func->objectType->flags & asOBJ_TEMPLATE))
		{
			// Check for funcdefs in the arguments that may have been generated by the template instance, so these can be shown to user
			for (unsigned int p = 0; p < func->GetParamCount(); p++)
			{
				int typeId = 0;
				func->GetParam(p, &typeId);
				asITypeInfo *ti = engine->GetTypeInfoById(typeId);
				if (ti && (ti->GetFlags() & asOBJ_FUNCDEF))
				{
					asCString msg;
					msg.Format(TXT_WHERE_s_IS_s, ti->GetName(), ti->GetFuncdefSignature()->GetDeclaration());
					builder->WriteInfo(script->name, msg.AddressOf(), r, c, false);
				}
			}
		}
	}
}

int asCCompiler::AllocateVariableNotIn(const asCDataType &type, bool isTemporary, bool forceOnHeap, asCExprContext *ctx)
{
	int l = int(reservedVariables.GetLength());
	ctx->bc.GetVarsUsed(reservedVariables);
	int var = AllocateVariable(type, isTemporary, forceOnHeap);
	reservedVariables.SetLength(l);
	return var;
}

int asCCompiler::AllocateVariable(const asCDataType &type, bool isTemporary, bool forceOnHeap, bool asReference)
{
	asCDataType t(type);
	t.MakeReference(asReference);

	if( t.IsPrimitive() && t.GetSizeOnStackDWords() == 1 )
		t.SetTokenType(ttInt);

	if( t.IsPrimitive() && t.GetSizeOnStackDWords() == 2 )
		t.SetTokenType(ttDouble);

	// Only null handles have the token type unrecognized token
	asASSERT( t.IsObjectHandle() || t.GetTokenType() != ttUnrecognizedToken );

	bool isOnHeap = true;
	if( t.IsPrimitive() ||
		(t.GetTypeInfo() && (t.GetTypeInfo()->GetFlags() & asOBJ_VALUE) && !forceOnHeap && !asReference) )
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

			// Verify that it is not in the list of reserved variables
			bool isUsed = false;
			if( reservedVariables.GetLength() )
				isUsed = reservedVariables.Exists(offset);

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
	{
		// Add offset to the currently allocated temporary variables
		tempVariables.PushLast(offset);

		// Add offset to all known offsets to temporary variables, whether allocated or not
		tempVariableOffsets.PushLast(offset);
	}

	return offset;
}

int asCCompiler::GetVariableOffset(int varIndex)
{
	// Return offset to the last dword on the stack

	// Start at 1 as offset 0 is reserved for the this pointer (or first argument for global functions)
	int varOffset = 1;

	// Skip lower variables
	for( int n = 0; n < varIndex; n++ )
	{
		if( !variableIsOnHeap[n] && variableAllocations[n].IsObject() )
			varOffset += variableAllocations[n].GetSizeInMemoryDWords();
		else
			varOffset += variableAllocations[n].GetSizeOnStackDWords();
	}

	if( varIndex < (int)variableAllocations.GetLength() )
	{
		// For variables larger than 1 dword the returned offset should be to the last dword
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

	// Mark the variable slot available for new allocations
	n = GetVariableSlot(offset);
	if( n != -1 )
	{
		freeVariables.PushLast(n);
		return;
	}

	// We might get here if the variable was implicitly declared
	// because it was used before a formal declaration, in this case
	// the offset is 0x7FFF

	asASSERT(offset == 0x7FFF);
}

void asCCompiler::ReleaseTemporaryVariable(asCExprValue &t, asCByteCode *bc)
{
	if( t.isTemporary )
	{
		ReleaseTemporaryVariable(t.stackOffset, bc);
		t.isTemporary = false;
	}
}

void asCCompiler::ReleaseTemporaryVariable(int offset, asCByteCode *bc)
{
	asASSERT( tempVariables.Exists(offset) );

	if( bc )
	{
		// We need to call the destructor on the true variable type
		int n = GetVariableSlot(offset);
		asASSERT( n >= 0 );
		if( n >= 0 )
		{
			asCDataType dt = variableAllocations[n];
			bool isOnHeap = variableIsOnHeap[n];

			// Call destructor
			CallDestructor(dt, offset, isOnHeap, bc);
		}
	}

	DeallocateVariable(offset);
}

void asCCompiler::Dereference(asCExprContext *ctx, bool generateCode)
{
	if( ctx->type.dataType.IsReference() )
	{
		if( ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef() )
		{
			ctx->type.dataType.MakeReference(false);
			if( generateCode )
				ctx->bc.Instr(asBC_RDSPtr);
		}
		else
		{
			// This should never happen as primitives are treated differently
			asASSERT(false);
		}
	}
}

bool asCCompiler::IsVariableInitialized(asCExprValue *type, asCScriptNode *node)
{
	// No need to check if there is no variable scope
	if( variables == 0 ) return true;

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
	if( v->type.IsObject() || v->type.IsFuncdef() ) return true;

	// Mark as initialized so that the user will not be bothered again
	v->isInitialized = true;

	// Write warning
	asCString str;
	str.Format(TXT_s_NOT_INITIALIZED, (const char *)v->name.AddressOf());
	Warning(str, node);

	return false;
}

void asCCompiler::PrepareOperand(asCExprContext *ctx, asCScriptNode *node)
{
	// Check if the variable is initialized (if it indeed is a variable)
	IsVariableInitialized(&ctx->type, node);

	asCDataType to = ctx->type.dataType;
	to.MakeReference(false);

	ImplicitConversion(ctx, to, node, asIC_IMPLICIT_CONV);

	ProcessDeferredParams(ctx);
}

void asCCompiler::PrepareForAssignment(asCDataType *lvalue, asCExprContext *rctx, asCScriptNode *node, bool toTemporary, asCExprContext *lvalueExpr)
{
	// Reserve the temporary variables used in the lvalue expression so they won't end up being used by the rvalue too
	int l = int(reservedVariables.GetLength());
	if( lvalueExpr ) lvalueExpr->bc.GetVarsUsed(reservedVariables);

	if( ProcessPropertyGetAccessor(rctx, node) < 0 )
		return;

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
		ImplicitConversion(rctx, *lvalue, node, asIC_IMPLICIT_CONV);

		// Check data type
		if( !lvalue->IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lvalue->Format(outFunc->nameSpace).AddressOf());
			Error(str, node);

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
		// First convert to a handle which will do a reference cast
		if( !lvalue->IsObjectHandle() &&
			(lvalue->GetTypeInfo()->flags & asOBJ_SCRIPT_OBJECT) )
			to.MakeHandle(true);

		// Don't allow the implicit conversion to create an object
		ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, !toTemporary);

		if( !lvalue->IsObjectHandle() &&
			(lvalue->GetTypeInfo()->flags & asOBJ_SCRIPT_OBJECT) )
		{
			// Then convert to a reference, which will validate the handle
			to.MakeHandle(false);
			ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true, !toTemporary);
		}

		// Check data type
		if( !lvalue->IsEqualExceptRefAndConst(rctx->type.dataType) )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lvalue->Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
		}
		else
		{
			// If the assignment will be made with the copy behaviour then the rvalue must not be a reference
			asASSERT(!lvalue->IsObject() || !rctx->type.dataType.IsReference());
		}
	}

	// Unreserve variables
	reservedVariables.SetLength(l);
}

bool asCCompiler::IsLValue(asCExprValue &type)
{
	if( !type.isLValue ) return false;
	if( type.dataType.IsReadOnly() ) return false;
	if( !type.dataType.IsObject() && !type.isVariable && !type.dataType.IsReference() ) return false;
	return true;
}

int asCCompiler::PerformAssignment(asCExprValue *lvalue, asCExprValue *rvalue, asCByteCode *bc, asCScriptNode *node)
{
	if( lvalue->dataType.IsReadOnly() )
	{
		Error(TXT_REF_IS_READ_ONLY, node);
		return -1;
	}

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
			return -1;
		}
	}
	else if( !lvalue->isExplicitHandle )
	{
		asCExprContext ctx(engine);
		ctx.type = *lvalue;
		Dereference(&ctx, true);
		*lvalue = ctx.type;
		bc->AddCode(&ctx.bc);

		asSTypeBehaviour *beh = lvalue->dataType.GetBehaviour();
		if( beh && beh->copy && beh->copy != engine->scriptTypeBehaviours.beh.copy )
		{
			asCExprContext res(engine);
			PerformFunctionCall(beh->copy, &res, false, 0, CastToObjectType(lvalue->dataType.GetTypeInfo()));

			bc->AddCode(&res.bc);
			*lvalue = res.type;
		}
		else if( beh && beh->copy == engine->scriptTypeBehaviours.beh.copy )
		{
			// Call the default copy operator for script classes
			// This is done differently because the default copy operator
			// is registered as returning int&, but in reality it returns
			// a reference to the object.
			// TODO: Avoid this special case by implementing a copystub for
			//       script classes that uses the default copy operator
			bc->Call(asBC_CALLSYS, beh->copy, 2*AS_PTR_SIZE);
			bc->Instr(asBC_PshRPtr);
		}
		else
		{
			// Default copy operator
			if( lvalue->dataType.GetSizeInMemoryDWords() == 0 ||
				!(lvalue->dataType.GetTypeInfo()->flags & asOBJ_POD) )
			{
				asCString msg;
				msg.Format(TXT_NO_DEFAULT_COPY_OP_FOR_s, lvalue->dataType.GetTypeInfo()->name.AddressOf());
				Error(msg, node);
				return -1;
			}

			// Copy larger data types from a reference
			// TODO: runtime optimize: COPY should pop both arguments and store the reference in the register.
			bc->InstrSHORT_DW(asBC_COPY, (short)lvalue->dataType.GetSizeInMemoryDWords(), engine->GetTypeIdFromDataType(lvalue->dataType));
		}
	}
	else
	{
		// TODO: The object handle can be stored in a variable as well
		if( !lvalue->dataType.IsReference() )
		{
			Error(TXT_NOT_VALID_REFERENCE, node);
			return -1;
		}

		if( lvalue->dataType.IsFuncdef() )
			bc->InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
		else
			bc->InstrPTR(asBC_REFCPY, lvalue->dataType.GetTypeInfo());

		// Mark variable as initialized
		if( variables )
		{
			sVariable *v = variables->GetVariableByOffset(lvalue->stackOffset);
			if( v ) v->isInitialized = true;
		}
	}

	return 0;
}

bool asCCompiler::CompileRefCast(asCExprContext *ctx, const asCDataType &to, bool isExplicit, asCScriptNode *node, bool generateCode)
{
	bool conversionDone = false;

	asCArray<int> ops;

	// A ref cast must not remove the constness
	bool isConst = ctx->type.dataType.IsObjectConst();

	// Find a suitable opCast or opImplCast method
	asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
	for( asUINT n = 0; ot && n < ot->methods.GetLength(); n++ )
	{
		asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
		if( (isExplicit && func->name == "opCast") ||
			func->name == "opImplCast" )
		{
			// Is the operator for the output type?
			if( func->returnType.GetTypeInfo() != to.GetTypeInfo() )
				continue;

			// Can't call a non-const function on a const object
			if( isConst && !func->IsReadOnly() )
				continue;

			ops.PushLast(func->id);
		}
	}

	// Filter the list by constness to remove const methods if there are matching non-const methods
	FilterConst(ops, !isConst);

	// If there is multiple matches, then pick the most appropriate one
	if (ops.GetLength() > 1)
	{
		// This should only happen if an explicit cast is compiled
		// and the type has both the opCast and opImplCast
		asASSERT(isExplicit);
		asASSERT(ops.GetLength() == 2);

		for (asUINT n = 0; n < ops.GetLength(); n++)
		{
			asCScriptFunction *func = engine->scriptFunctions[ops[n]];
			if (func->name == "opImplCast")
			{
				ops.RemoveIndex(n);
				n--;
			}
		}
	}

	// Should only have one behaviour for each output type
	if( ops.GetLength() == 1 )
	{
		conversionDone = true;
		if( generateCode )
		{
			// TODO: runtime optimize: Instead of producing bytecode for checking if the handle is
			//                         null, we can create a special CALLSYS instruction that checks
			//                         if the object pointer is null and if so sets the object register
			//                         to null directly without executing the function.
			//
			//                         Alternatively I could force the ref cast behaviours be global
			//                         functions with 1 parameter, even though they should still be
			//                         registered with RegisterObjectBehaviour()

			if( (ctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_NOHANDLE))
			{
				// Add code to avoid calling the cast behaviour if the handle is already null,
				// because that will raise a null pointer exception due to the cast behaviour
				// being a class method, and the this pointer cannot be null.

				if (!ctx->type.isVariable)
				{
					Dereference(ctx, true);
					ConvertToVariable(ctx);
				}

				// The reference on the stack will not be used
				ctx->bc.Instr(asBC_PopPtr);

				// TODO: runtime optimize: should have immediate comparison for null pointer
				int offset = AllocateVariable(asCDataType::CreateNullHandle(), true);
				// TODO: runtime optimize: ClrVPtr is not necessary, because the VM should initialize the variable to null anyway (it is currently not done for null pointers though)
				ctx->bc.InstrSHORT(asBC_ClrVPtr, (asWORD)offset);
				ctx->bc.InstrW_W(asBC_CmpPtr, ctx->type.stackOffset, offset);
				DeallocateVariable(offset);

				int afterLabel = nextLabel++;
				ctx->bc.InstrDWORD(asBC_JZ, afterLabel);

				// Call the cast operator
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
				ctx->bc.Instr(asBC_RDSPtr);
				ctx->type.dataType.MakeReference(false);

				asCArray<asCExprContext *> args;
				MakeFunctionCall(ctx, ops[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);
				ctx->bc.Instr(asBC_PopPtr);

				int endLabel = nextLabel++;

				ctx->bc.InstrINT(asBC_JMP, endLabel);
				ctx->bc.Label((short)afterLabel);

				// Make a NULL pointer
				ctx->bc.InstrSHORT(asBC_ClrVPtr, ctx->type.stackOffset);
				ctx->bc.Label((short)endLabel);

				// Push the reference to the handle on the stack
				ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
			}
			else
			{
				// Value types cannot be null, so there is no need to check for this.

				// Likewise for reference types that are registered with asOBJ_NOHANDLE
				// as those are only expected as registered global properties that cannot
				// be modified anyway.

				// Call the cast operator
				asCArray<asCExprContext *> args;
				MakeFunctionCall(ctx, ops[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);
			}
		}
		else
		{
			asCScriptFunction *func = engine->scriptFunctions[ops[0]];
			ctx->type.Set(func->returnType);
		}
	}
	else if( ops.GetLength() == 0 && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCRIPT_OBJECT) && to.IsObjectHandle() )
	{
		// Check for the generic ref cast method: void opCast(?&out)
		// This option only works if the expected type is a handle
		for( asUINT n = 0; ot && n < ot->methods.GetLength(); n++ )
		{
			asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
			if( (isExplicit && func->name == "opCast") ||
				func->name == "opImplCast" )
			{
				// Does the operator take the ?&out parameter?
				if( func->returnType.GetTokenType() != ttVoid ||
					func->parameterTypes.GetLength() != 1 ||
					func->parameterTypes[0].GetTokenType() != ttQuestion ||
					func->inOutFlags[0] != asTM_OUTREF )
					continue;

				ops.PushLast(func->id);
			}
		}

		// Filter the list by constness to remove const methods if there are matching non-const methods
		FilterConst(ops, !isConst);

		// If there is multiple matches, then pick the most appropriate one
		if (ops.GetLength() > 1)
		{
			// This should only happen if an explicit cast is compiled
			// and the type has both the opCast and opImplCast
			asASSERT(isExplicit);
			asASSERT(ops.GetLength() == 2);

			for (asUINT n = 0; n < ops.GetLength(); n++)
			{
				asCScriptFunction *func = engine->scriptFunctions[ops[n]];
				if (func->name == "opImplCast")
				{
					ops.RemoveIndex(n);
					n--;
				}
			}
		}

		if( ops.GetLength() == 1 )
		{
			conversionDone = true;
			if( generateCode )
			{
				int afterLabel = 0;
				bool doNullCheck = false;
				bool releaseTempVariable = false;
				asCExprContext tmp(engine);
				if ((ctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_NOHANDLE))
				{
					tmp.bc.AddCode(&ctx->bc);
					tmp.Merge(ctx);

					// Add code to avoid calling the cast behaviour if the handle is already null,
					// because that will raise a null pointer exception due to the cast behaviour
					// being a class method, and the this pointer cannot be null.
					doNullCheck = true;
					if (!ctx->type.isVariable)
					{
						Dereference(&tmp, true);
						ConvertToVariable(&tmp);
						releaseTempVariable = true;
					}

					// The reference on the stack will not be used
					tmp.bc.Instr(asBC_PopPtr);

					// TODO: runtime optimize: should have immediate comparison for null pointer
					int offset = AllocateVariable(asCDataType::CreateNullHandle(), true);
					// TODO: runtime optimize: ClrVPtr is not necessary, because the VM should initialize the variable to null anyway (it is currently not done for null pointers though)
					tmp.bc.InstrSHORT(asBC_ClrVPtr, (asWORD)offset);
					tmp.bc.InstrW_W(asBC_CmpPtr, tmp.type.stackOffset, offset);
					DeallocateVariable(offset);

					afterLabel = nextLabel++;
					tmp.bc.InstrDWORD(asBC_JZ, afterLabel);

					// Place the object pointer on the stack
					ctx->bc.InstrSHORT(asBC_PSF, (short)tmp.type.stackOffset);
				}

				// Allocate a temporary variable of the requested handle type
				int stackOffset = AllocateVariableNotIn(to, true, false, ctx);

				// Pass the reference of that variable to the function as output parameter
				asCDataType toRef(to);
				toRef.MakeReference(true);
				asCArray<asCExprContext *> args;
				asCExprContext arg(engine);
				arg.bc.InstrSHORT(asBC_PSF, (short)stackOffset);
				// Don't mark the variable as temporary, so it won't be freed too early
				arg.type.SetVariable(toRef, stackOffset, false);
				arg.type.isLValue = true;
				arg.type.isExplicitHandle = true;
				args.PushLast(&arg);

				// Call the behaviour method
				MakeFunctionCall(ctx, ops[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);

				if (doNullCheck)
				{
					// Add the call after the null check
					tmp.bc.AddCode(&ctx->bc);
					ctx->bc.AddCode(&tmp.bc);

					int endLabel = nextLabel++;

					ctx->bc.InstrINT(asBC_JMP, endLabel);
					ctx->bc.Label((short)afterLabel);

					// Make a NULL pointer
					ctx->bc.InstrSHORT(asBC_ClrVPtr, (short)stackOffset);
					ctx->bc.Label((short)endLabel);
				}

				// If a temporary variable was allocated in the tmp to convert
				// the input expression to a variable, it must be released here
				if (releaseTempVariable && tmp.type.isTemporary)
					ReleaseTemporaryVariable(tmp.type.stackOffset, &ctx->bc);

				// Use the reference to the variable as the result of the expression
				// Now we can mark the variable as temporary
				ctx->type.SetVariable(toRef, stackOffset, true);
				ctx->bc.InstrSHORT(asBC_PSF, (short)stackOffset);
			}
			else
			{
				// All casts are legal
				ctx->type.Set(to);
			}
		}
	}

	// If the script object didn't implement a matching opCast or opImplCast
	// then check if the desired type is part of the hierarchy
	if( !conversionDone && (ctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCRIPT_OBJECT) )
	{
		// We need it to be a reference
		if( !ctx->type.dataType.IsReference() )
		{
			asCDataType toRef = ctx->type.dataType;
			toRef.MakeReference(true);
			ImplicitConversion(ctx, toRef, 0, isExplicit ? asIC_EXPLICIT_REF_CAST : asIC_IMPLICIT_CONV, generateCode);
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
			if( CastToObjectType(ctx->type.dataType.GetTypeInfo())->DerivesFrom(to.GetTypeInfo()) )
			{
				conversionDone = true;
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			}
		}

		// A ref cast must not remove the constness
		if( isConst )
			ctx->type.dataType.MakeHandleToConst(true);
	}

	return conversionDone;
}

asUINT asCCompiler::ImplicitConvPrimitiveToPrimitive(asCExprContext *ctx, const asCDataType &toOrig, asCScriptNode *node, EImplicitConv convType, bool generateCode)
{
	asCDataType to = toOrig;
	to.MakeReference(false);
	asASSERT( !ctx->type.dataType.IsReference() );

	// Maybe no conversion is needed
	if( to.IsEqualExceptConst(ctx->type.dataType) )
	{
		// A primitive is const or not
		ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
		return asCC_NO_CONV;
	}

	// Is the conversion an ambiguous enum value?
	if( ctx->enumValue != "" )
	{
		if( to.IsEnumType() )
		{
			// Attempt to resolve an ambiguous enum value
			asCDataType out;
			asDWORD value;
			if( builder->GetEnumValueFromType(CastToEnumType(to.GetTypeInfo()), ctx->enumValue.AddressOf(), out, value) )
			{
				ctx->type.SetConstantDW(out, value);
				ctx->type.dataType.MakeReadOnly(to.IsReadOnly());

				// Reset the enum value since we no longer need it
				ctx->enumValue = "";

				// It wasn't really a conversion. The compiler just resolved the ambiguity (or not)
				return asCC_NO_CONV;
			}
		}

		// The enum value is ambiguous
		if( node && generateCode )
			Error(TXT_FOUND_MULTIPLE_ENUM_VALUES, node);

		// Set a dummy to allow the compiler to try to continue the conversion
		ctx->type.SetDummy();
	}

	// Determine the cost of this conversion
	asUINT cost = asCC_NO_CONV;
	if( (to.IsIntegerType() || to.IsUnsignedType()) && (ctx->type.dataType.IsFloatType() || ctx->type.dataType.IsDoubleType()) )
		cost = asCC_INT_FLOAT_CONV;
	else if ((to.IsFloatType() || to.IsDoubleType()) && (ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsUnsignedType()))
		cost = asCC_INT_FLOAT_CONV;
	else if (ctx->type.dataType.IsEnumType() && to.IsIntegerType() && to.GetSizeInMemoryBytes() == ctx->type.dataType.GetSizeInMemoryBytes() )
		cost = asCC_ENUM_SAME_SIZE_CONV;
	else if (ctx->type.dataType.IsEnumType() && to.IsIntegerType() && to.GetSizeInMemoryBytes() != ctx->type.dataType.GetSizeInMemoryBytes())
		cost = asCC_ENUM_DIFF_SIZE_CONV;
	else if( to.IsUnsignedType() && ctx->type.dataType.IsIntegerType() )
		cost = asCC_SIGNED_CONV;
	else if( to.IsIntegerType() && ctx->type.dataType.IsUnsignedType() )
		cost = asCC_SIGNED_CONV;
	else if( to.GetSizeInMemoryBytes() != ctx->type.dataType.GetSizeInMemoryBytes() )
		cost = asCC_PRIMITIVE_SIZE_CONV;

	// Start by implicitly converting constant values
	if( ctx->type.isConstant )
	{
		ImplicitConversionConstant(ctx, to, generateCode ? node : 0, convType);
		ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
		return cost;
	}

	// Allow implicit conversion between numbers
	if( generateCode )
	{
		// When generating the code the decision has already been made, so we don't bother determining the cost

		// Convert smaller types to 32bit first
		int s = ctx->type.dataType.GetSizeInMemoryBytes();
		if( s < 4 )
		{
			ConvertToTempVariable(ctx);
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

		if( (to.IsIntegerType() && to.GetSizeInMemoryDWords() == 1 && !to.IsEnumType()) ||
			(to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST) )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
				}
				else
				{
					ConvertToTempVariable(ctx);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariable(to, true);
					ctx->bc.InstrW_W(asBC_i64TOi, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_fTOi, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_dTOi, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}

			// Convert to smaller integer if necessary
			s = to.GetSizeInMemoryBytes();
			if( s < 4 )
			{
				ConvertToTempVariable(ctx);
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_iTOb, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_iTOw, ctx->type.stackOffset);
			}
		}
		else if( to.IsIntegerType() && to.GetSizeInMemoryDWords() == 2 )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
				}
				else
				{
					ConvertToTempVariable(ctx);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariable(to, true);
					if( ctx->type.dataType.IsUnsignedType() )
						ctx->bc.InstrW_W(asBC_uTOi64, offset, ctx->type.stackOffset);
					else
						ctx->bc.InstrW_W(asBC_iTOi64, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_fTOi64, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_dTOi64, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
		}
		else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 1  )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
				}
				else
				{
					ConvertToTempVariable(ctx);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariable(to, true);
					ctx->bc.InstrW_W(asBC_i64TOi, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_fTOu, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_dTOu, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}

			// Convert to smaller integer if necessary
			s = to.GetSizeInMemoryBytes();
			if( s < 4 )
			{
				ConvertToTempVariable(ctx);
				if( s == 1 )
					ctx->bc.InstrSHORT(asBC_iTOb, ctx->type.stackOffset);
				else if( s == 2 )
					ctx->bc.InstrSHORT(asBC_iTOw, ctx->type.stackOffset);
			}
		}
		else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 2 )
		{
			if( ctx->type.dataType.IsIntegerType() ||
				ctx->type.dataType.IsUnsignedType() )
			{
				if( ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
				{
					ctx->type.dataType.SetTokenType(to.GetTokenType());
					ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
				}
				else
				{
					ConvertToTempVariable(ctx);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);
					int offset = AllocateVariable(to, true);
					if( ctx->type.dataType.IsUnsignedType() )
						ctx->bc.InstrW_W(asBC_uTOi64, offset, ctx->type.stackOffset);
					else
						ctx->bc.InstrW_W(asBC_iTOi64, offset, ctx->type.stackOffset);
					ctx->type.SetVariable(to, offset, true);
				}
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_fTOu64, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_dTOu64, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());

				if( convType != asIC_EXPLICIT_VAL_CAST )
					Warning(TXT_FLOAT_CONV_TO_INT_CAUSE_TRUNC, node);
			}
		}
		else if( to.IsFloatType() )
		{
			if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_iTOf, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			}
			else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_i64TOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_uTOf, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_u64TOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsDoubleType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_dTOf, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
		}
		else if( to.IsDoubleType() )
		{
			if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_iTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsIntegerType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_i64TOd, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_uTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
			else if( ctx->type.dataType.IsUnsignedType() && ctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				ConvertToTempVariable(ctx);
				ctx->bc.InstrSHORT(asBC_u64TOd, ctx->type.stackOffset);
				ctx->type.dataType.SetTokenType(to.GetTokenType());
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			}
			else if( ctx->type.dataType.IsFloatType() )
			{
				ConvertToTempVariable(ctx);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);
				int offset = AllocateVariable(to, true);
				ctx->bc.InstrW_W(asBC_fTOd, offset, ctx->type.stackOffset);
				ctx->type.SetVariable(to, offset, true);
			}
		}
	}
	else
	{
		if( ((to.IsIntegerType() && !to.IsEnumType()) || to.IsUnsignedType() ||
			 to.IsFloatType()   || to.IsDoubleType() ||
			 (to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST)) &&
			(ctx->type.dataType.IsIntegerType() || ctx->type.dataType.IsUnsignedType() ||
			 ctx->type.dataType.IsFloatType()   || ctx->type.dataType.IsDoubleType()) )
		{
			ctx->type.dataType.SetTokenType(to.GetTokenType());
			ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
		}
	}

	// Primitive types on the stack, can be const or non-const
	ctx->type.dataType.MakeReadOnly(to.IsReadOnly());
	return cost;
}

asUINT asCCompiler::ImplicitConvLambdaToFunc(asCExprContext *ctx, const asCDataType &to, asCScriptNode * /*node*/, EImplicitConv /*convType*/, bool generateCode)
{
	asASSERT( to.IsFuncdef() && ctx->IsLambda() );

	asCScriptFunction *funcDef = CastToFuncdefType(to.GetTypeInfo())->funcdef;

	// Check that the lambda has the correct amount of arguments
	asUINT count = 0;
	asCScriptNode *argNode = ctx->exprNode->firstChild;
	while( argNode->nodeType != snStatementBlock )
	{
		// Check if the specified parameter types match the funcdef
		if (argNode->nodeType == snDataType)
		{
			asCDataType dt = builder->CreateDataTypeFromNode(argNode, script, outFunc->nameSpace, false, outFunc->objectType);
			asETypeModifiers inOutFlag;
			dt = builder->ModifyDataTypeFromNode(dt, argNode->next, script, &inOutFlag, 0);

			if (count >= funcDef->parameterTypes.GetLength() ||
				funcDef->parameterTypes[count] != dt ||
				funcDef->inOutFlags[count] != inOutFlag)
				return asCC_NO_CONV;

			argNode = argNode->next;
		}

		if( argNode->nodeType == snIdentifier )
			count++;
		argNode = argNode->next;
	}

	if (funcDef->parameterTypes.GetLength() != count)
		return asCC_NO_CONV;

	asASSERT(argNode->nodeType == snStatementBlock);

	// The Lambda can be used as this funcdef
	ctx->type.dataType = to;

	if( generateCode )
	{
		// Build a unique name for the anonymous function
		asCString name;
		if( m_globalVar )
			name.Format("$%s$%d", m_globalVar->name.AddressOf(), numLambdas++);
		else
			name.Format("$%s$%d", outFunc->GetDeclaration(), numLambdas++);

		// Register the lambda with the builder for later compilation
		asCScriptFunction *func = builder->RegisterLambda(ctx->exprNode, script, funcDef, name, outFunc->nameSpace, outFunc->IsShared());
		asASSERT( func == 0 || funcDef->IsSignatureExceptNameEqual(func) );
		ctx->bc.InstrPTR(asBC_FuncPtr, func);

		// Clear the expression node as it is no longer valid
		ctx->exprNode = 0;
	}

	return asCC_CONST_CONV;
}

asUINT asCCompiler::ImplicitConversion(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode, bool allowObjectConstruct)
{
	asASSERT( ctx->type.dataType.GetTokenType() != ttUnrecognizedToken ||
		      ctx->type.dataType.IsNullHandle() ||
		      ctx->IsAnonymousInitList() );

	if( to.IsFuncdef() && ctx->IsLambda() )
		return ImplicitConvLambdaToFunc(ctx, to, node, convType, generateCode);

	if (ctx->IsAnonymousInitList())
	{
		if (to.GetBehaviour() && to.GetBehaviour()->listFactory)
		{
			if (generateCode)
				CompileAnonymousInitList(ctx->exprNode, ctx, to);
			else
				ctx->type.dataType = to;
		}
		return asCC_NO_CONV;
	}

	// No conversion from void to any other type
	if( ctx->type.dataType.GetTokenType() == ttVoid )
		return asCC_NO_CONV;

	// No conversion from class method to any type (it requires delegate)
	if( ctx->IsClassMethod() )
		return asCC_NO_CONV;

	// Do we want a var type?
	if( to.GetTokenType() == ttQuestion )
	{
		// Any type can be converted to a var type, but only when not generating code
		asASSERT( !generateCode );

		ctx->type.dataType = to;

		return asCC_VARIABLE_CONV;
	}
	// Do we want a primitive?
	else if( to.IsPrimitive() )
	{
		if( !ctx->type.dataType.IsPrimitive() )
			return ImplicitConvObjectToPrimitive(ctx, to, node, convType, generateCode);
		else
			return ImplicitConvPrimitiveToPrimitive(ctx, to, node, convType, generateCode);
	}
	else // The target is a complex type
	{
		if( ctx->type.dataType.IsPrimitive() )
			return ImplicitConvPrimitiveToObject(ctx, to, node, convType, generateCode, allowObjectConstruct);
		else if( ctx->type.IsNullConstant() || ctx->type.dataType.GetTypeInfo() )
			return ImplicitConvObjectToObject(ctx, to, node, convType, generateCode, allowObjectConstruct);
	}

	return asCC_NO_CONV;
}

asUINT asCCompiler::ImplicitConvObjectToPrimitive(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode)
{
	if( ctx->type.isExplicitHandle )
	{
		// An explicit handle cannot be converted to a primitive
		if( convType != asIC_IMPLICIT_CONV && node )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
		}
		return asCC_NO_CONV;
	}

	// Find matching value cast behaviours
	// Here we're only interested in those that convert the type to a primitive type
	asCArray<int> funcs;
	asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
	if( ot == 0 )
	{
		if( convType != asIC_IMPLICIT_CONV && node )
		{
			asCString str;
			str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
		}
		return asCC_NO_CONV;
	}


	if( convType == asIC_EXPLICIT_VAL_CAST )
	{
		for( unsigned int n = 0; n < ot->methods.GetLength(); n++ )
		{
			// accept both implicit and explicit cast
			asCScriptFunction *mthd = engine->scriptFunctions[ot->methods[n]];
			if( (mthd->name == "opConv" || mthd->name == "opImplConv") &&
				mthd->parameterTypes.GetLength() == 0 &&
				mthd->returnType.IsPrimitive() )
				funcs.PushLast(ot->methods[n]);
		}
	}
	else
	{
		for( unsigned int n = 0; n < ot->methods.GetLength(); n++ )
		{
			// accept only implicit cast
			asCScriptFunction *mthd = engine->scriptFunctions[ot->methods[n]];
			if( mthd->name == "opImplConv" &&
				mthd->parameterTypes.GetLength() == 0 &&
				mthd->returnType.IsPrimitive() )
				funcs.PushLast(ot->methods[n]);
		}
	}

	FilterConst(funcs, !ctx->type.dataType.IsReadOnly());

	int funcId = 0;
	if( to.IsMathType() )
	{
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
					if( descr->returnType.IsEqualExceptRefAndConst(target) )
					{
						funcId = funcs[n];
						break;
					}
				}
			}
		}
	}
	else
	{
		// Only accept the exact conversion for non-math types

		// Find the matching cast operator
		for( unsigned int n = 0; n < funcs.GetLength(); n++ )
		{
			asCScriptFunction *descr = builder->GetFunctionDescription(funcs[n]);
			if( descr->returnType.IsEqualExceptRefAndConst(to) )
			{
				funcId = funcs[n];
				break;
			}
		}
	}

	// Did we find a suitable function?
	if( funcId != 0 )
	{
		asCScriptFunction *descr = builder->GetFunctionDescription(funcId);
		if( generateCode )
		{
			Dereference(ctx, true);
			PerformFunctionCall(funcId, ctx);
		}
		else
			ctx->type.Set(descr->returnType);

		// Allow one more implicit conversion to another primitive type
		return asCC_OBJ_TO_PRIMITIVE_CONV + ImplicitConversion(ctx, to, node, convType, generateCode, false);
	}

	// TODO: clean-up: This part is similar to what is in ImplicitConvObjectValue
	// If no direct conversion is found we should look for the generic form 'void opConv(?&out)'
	funcs.SetLength(0);
	for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
	{
		asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
		if( ((convType == asIC_EXPLICIT_VAL_CAST) && func->name == "opConv") ||
			func->name == "opImplConv" )
		{
			// Does the operator take the ?&out parameter?
			if( func->returnType != asCDataType::CreatePrimitive(ttVoid, false) ||
				func->parameterTypes.GetLength() != 1 ||
				func->parameterTypes[0].GetTokenType() != ttQuestion ||
				func->inOutFlags[0] != asTM_OUTREF )
				continue;

			funcs.PushLast(ot->methods[n]);
		}
	}

	FilterConst(funcs, !ctx->type.dataType.IsReadOnly());

	// If there are multiple valid value casts, then we must choose the most appropriate one
	if (funcs.GetLength() > 1)
	{
		// This should only happen in case of explicit value cast and
		// the application has registered both opImplConv and opConv
		asASSERT(convType == asIC_EXPLICIT_VAL_CAST);
		asASSERT(funcs.GetLength() == 2);

		for (asUINT n = 0; n < funcs.GetLength(); n++)
		{
			asCScriptFunction *func = engine->scriptFunctions[funcs[n]];
			if (func->name == "opImplConv")
			{
				funcs.RemoveIndex(n);
				n--;
			}
		}
	}

	if( funcs.GetLength() == 1 )
	{
		if( generateCode )
		{
			// Allocate a temporary variable of the requested type
			int stackOffset = AllocateVariableNotIn(to, true, false, ctx);
			CallDefaultConstructor(to, stackOffset, IsVariableOnHeap(stackOffset), &ctx->bc, node);

			// Pass the reference of that variable to the function as output parameter
			asCDataType toRef(to);
			toRef.MakeReference(true);
			toRef.MakeReadOnly(false);
			asCArray<asCExprContext *> args;
			asCExprContext arg(engine);
			// Don't mark the variable as temporary, so it won't be freed too early
			arg.type.SetVariable(toRef, stackOffset, false);
			arg.type.isLValue = true;
			arg.exprNode = node;
			args.PushLast(&arg);

			// Call the behaviour method
			MakeFunctionCall(ctx, funcs[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);

			// Use the reference to the variable as the result of the expression
			// Now we can mark the variable as temporary
			toRef.MakeReference(false);
			ctx->type.SetVariable(toRef, stackOffset, true);
		}
		else
			ctx->type.Set(to);

		return asCC_OBJ_TO_PRIMITIVE_CONV;
	}

	if( convType != asIC_IMPLICIT_CONV && node )
	{
		asCString str;
		str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
	}

	return asCC_NO_CONV;
}


asUINT asCCompiler::ImplicitConvObjectRef(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode)
{
	// Convert null to any object type handle, but not to a non-handle type
	if( ctx->type.IsNullConstant() && ctx->methodName == "" )
	{
		if( to.IsObjectHandle() )
		{
			ctx->type.dataType = to;
			return asCC_REF_CONV;
		}
		return asCC_NO_CONV;
	}

	asASSERT(ctx->type.dataType.GetTypeInfo() || ctx->methodName != "");

	// First attempt to convert the base type without instantiating another instance
	if( to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() && ctx->methodName == "" )
	{
		// If the to type is an interface and the from type implements it, then we can convert it immediately
		if( ctx->type.dataType.GetTypeInfo()->Implements(to.GetTypeInfo()) )
		{
			ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			return asCC_REF_CONV;
		}
		// If the to type is a class and the from type derives from it, then we can convert it immediately
		else if( ctx->type.dataType.GetTypeInfo()->DerivesFrom(to.GetTypeInfo()) )
		{
			ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
			return asCC_REF_CONV;
		}
		// If the types are not equal yet, then we may still be able to find a reference cast
		else if( ctx->type.dataType.GetTypeInfo() != to.GetTypeInfo() )
		{
			// We may still be able to find an implicit ref cast behaviour
			CompileRefCast(ctx, to, convType == asIC_EXPLICIT_REF_CAST, node, generateCode);

			// Was the conversion done?
			if( ctx->type.dataType.GetTypeInfo() == to.GetTypeInfo() )
				return asCC_REF_CONV;
		}
	}

	// Convert matching function types
	if( to.IsFuncdef() )
	{
		// If the input expression is already a funcdef, check if it can be converted
		if( ctx->type.dataType.IsFuncdef() &&
			to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() )
		{
			asCScriptFunction *toFunc = CastToFuncdefType(to.GetTypeInfo())->funcdef;
			asCScriptFunction *fromFunc = CastToFuncdefType(ctx->type.dataType.GetTypeInfo())->funcdef;
			if( toFunc->IsSignatureExceptNameEqual(fromFunc) )
			{
				ctx->type.dataType.SetTypeInfo(to.GetTypeInfo());
				return asCC_REF_CONV;
			}
		}

		// If the input expression is a deferred function ref, check if there is a matching func
		if( ctx->methodName != "" )
		{
			// Determine the namespace
			asSNameSpace *ns = 0;
			asCString name = "";
			int pos = ctx->methodName.FindLast("::");
			if( pos >= 0 )
			{
				asCString nsName = ctx->methodName.SubString(0, pos+2);
				// Trim off the last ::
				if( nsName.GetLength() > 2 )
					nsName.SetLength(nsName.GetLength()-2);
				ns = DetermineNameSpace(nsName);
				name = ctx->methodName.SubString(pos+2);
			}
			else
			{
				DetermineNameSpace("");
				name = ctx->methodName;
			}

			asCArray<int> funcs;
			if( ns )
				builder->GetFunctionDescriptions(name.AddressOf(), funcs, ns);

			// Check if any of the functions have perfect match
			asCScriptFunction *toFunc = CastToFuncdefType(to.GetTypeInfo())->funcdef;
			for( asUINT n = 0; n < funcs.GetLength(); n++ )
			{
				asCScriptFunction *func = builder->GetFunctionDescription(funcs[n]);
				if( toFunc->IsSignatureExceptNameEqual(func) )
				{
					if( generateCode )
					{
						ctx->bc.InstrPTR(asBC_FuncPtr, func);

						// Make sure the identified function is shared if we're compiling a shared function
						if( !func->IsShared() && outFunc->IsShared() )
						{
							asCString msg;
							msg.Format(TXT_SHARED_CANNOT_CALL_NON_SHARED_FUNC_s, func->GetDeclaration());
							Error(msg, node);
						}
					}

					ctx->type.dataType = asCDataType::CreateType(to.GetTypeInfo(), false);
					return asCC_REF_CONV;
				}
			}
		}
	}

	return asCC_NO_CONV;
}

asUINT asCCompiler::ImplicitConvObjectValue(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode)
{
	asUINT cost = asCC_NO_CONV;

	// If the base type is still different, and we are allowed to instance
	// another object then we can try an implicit value cast
	if( to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() )
	{
		// TODO: Implement support for implicit constructor/factory
		asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
		if( ot == 0 )
			return cost;

		asCArray<int> funcs;
		if( convType == asIC_EXPLICIT_VAL_CAST )
		{
			for( unsigned int n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];

				// accept both implicit and explicit cast
				if( (func->name == "opConv" ||
					 func->name == "opImplConv") &&
					func->returnType.GetTypeInfo() == to.GetTypeInfo() &&
					func->parameterTypes.GetLength() == 0 )
					funcs.PushLast(ot->methods[n]);
			}
		}
		else
		{
			for( unsigned int n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];

				// accept only implicit cast
				if( func->name == "opImplConv" &&
					func->returnType.GetTypeInfo() == to.GetTypeInfo() &&
					func->parameterTypes.GetLength() == 0 )
					funcs.PushLast(ot->methods[n]);
			}
		}

		FilterConst(funcs, !ctx->type.dataType.IsReadOnly());

		// If there are multiple valid value casts, then we must choose the most appropriate one
		if (funcs.GetLength() > 1)
		{
			// This should only happen in case of explicit value cast and
			// the application has registered both opImplConv and opConv
			asASSERT(convType == asIC_EXPLICIT_VAL_CAST);
			asASSERT(funcs.GetLength() == 2);

			for (asUINT n = 0; n < funcs.GetLength(); n++)
			{
				asCScriptFunction *func = engine->scriptFunctions[funcs[n]];
				if (func->name == "opImplConv")
				{
					funcs.RemoveIndex(n);
					n--;
				}
			}
		}

		if( funcs.GetLength() == 1 )
		{
			asCScriptFunction *f = builder->GetFunctionDescription(funcs[0]);
			if( generateCode )
			{
				Dereference(ctx, true);

				bool useVariable = false;
				int  stackOffset = 0;

				if( f->DoesReturnOnStack() )
				{
					useVariable = true;
					stackOffset = AllocateVariable(f->returnType, true);

					// Push the pointer to the pre-allocated space for the return value
					ctx->bc.InstrSHORT(asBC_PSF, short(stackOffset));

					// The object pointer is already on the stack, but should be the top
					// one, so we need to swap the pointers in order to get the correct
					ctx->bc.Instr(asBC_SwapPtr);
				}

				PerformFunctionCall(funcs[0], ctx, false, 0, 0, useVariable, stackOffset);
			}
			else
				ctx->type.Set(f->returnType);

			cost = asCC_TO_OBJECT_CONV;
		}
		else
		{
			// TODO: cleanup: This part is similar to the second half of ImplicitConvObjectToPrimitive
			// Look for a value cast with variable type
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
				if( ((convType == asIC_EXPLICIT_VAL_CAST) && func->name == "opConv") ||
					func->name == "opImplConv" )
				{
					// Does the operator take the ?&out parameter?
					if( func->returnType != asCDataType::CreatePrimitive(ttVoid, false) ||
						func->parameterTypes.GetLength() != 1 ||
						func->parameterTypes[0].GetTokenType() != ttQuestion ||
						func->inOutFlags[0] != asTM_OUTREF )
						continue;

					funcs.PushLast(ot->methods[n]);
				}
			}

			FilterConst(funcs, !ctx->type.dataType.IsReadOnly());

			// If there are multiple valid value casts, then we must choose the most appropriate one
			if (funcs.GetLength() > 1)
			{
				// This should only happen in case of explicit value cast and
				// the application has registered both opImplConv and opConv
				asASSERT(convType == asIC_EXPLICIT_VAL_CAST);
				asASSERT(funcs.GetLength() == 2);

				for (asUINT n = 0; n < funcs.GetLength(); n++)
				{
					asCScriptFunction *func = engine->scriptFunctions[funcs[n]];
					if (func->name == "opImplConv")
					{
						funcs.RemoveIndex(n);
						n--;
					}
				}
			}

			if( funcs.GetLength() == 1 )
			{
				cost = asCC_TO_OBJECT_CONV;
				if( generateCode )
				{
					// Allocate a temporary variable of the requested type
					int stackOffset = AllocateVariableNotIn(to, true, false, ctx);
					CallDefaultConstructor(to, stackOffset, IsVariableOnHeap(stackOffset), &ctx->bc, node);

					// Pass the reference of that variable to the function as output parameter
					asCDataType toRef(to);
					toRef.MakeReference(false);
					asCExprContext arg(engine);
					arg.bc.InstrSHORT(asBC_PSF, (short)stackOffset);

					// If this an object on the heap, the pointer must be dereferenced
					if( IsVariableOnHeap(stackOffset) )
						arg.bc.Instr(asBC_RDSPtr);

					// Don't mark the variable as temporary, so it won't be freed too early
					arg.type.SetVariable(toRef, stackOffset, false);
					arg.type.isLValue = true;
					arg.exprNode = node;

					// Mark the argument as clean, so that MakeFunctionCall knows it
					// doesn't have to make a copy of it in order to protect the value
					arg.isCleanArg = true;

					// Call the behaviour method
					asCArray<asCExprContext *> args;
					args.PushLast(&arg);
					MakeFunctionCall(ctx, funcs[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);

					// Use the reference to the variable as the result of the expression
					// Now we can mark the variable as temporary
					ctx->type.SetVariable(toRef, stackOffset, true);
					ctx->bc.InstrSHORT(asBC_PSF, (short)stackOffset);
				}
				else
				{
					// All casts are legal
					ctx->type.Set(to);
				}
			}
			else if( CastToObjectType(to.GetTypeInfo()) )
			{
				// If no opConv/opImplConv methods were found on the object, then try to find a conversion constructor on the target type
				if( to.GetTypeInfo()->flags & asOBJ_REF )
					funcs = CastToObjectType(to.GetTypeInfo())->beh.factories;
				else
					funcs = CastToObjectType(to.GetTypeInfo())->beh.constructors;

				// If not explicit cast, remove any explicit conversion constructors
				for (asUINT n = 0; n < funcs.GetLength(); n++)
				{
					asCScriptFunction *f = engine->scriptFunctions[funcs[n]];
					if( f == 0 || f->parameterTypes.GetLength() != 1 || (convType != asIC_EXPLICIT_VAL_CAST && f->IsExplicit()) )
						funcs.RemoveIndex(n--);
				}

				asCArray<asCExprContext *> args;
				args.PushLast(ctx);

				cost = asCC_TO_OBJECT_CONV + MatchFunctions(funcs, args, node, 0, 0, 0, false, true, false);

				// Did we find a matching constructor?
				if (funcs.GetLength() == 1)
				{
					if (generateCode)
					{
						// TODO: This should really reuse the code from CompileConstructCall

						// Allocate the new object
						asCExprValue tempObj;
						asCExprContext e(engine);
						bool onHeap = false;
						if (to.GetTypeInfo()->flags & asOBJ_VALUE)
						{
							tempObj.dataType = to;
							tempObj.dataType.MakeReference(false);
							tempObj.stackOffset = (short)AllocateVariable(tempObj.dataType, true);
							tempObj.dataType.MakeReference(true);
							tempObj.isTemporary = true;
							tempObj.isVariable = true;

							onHeap = IsVariableOnHeap(tempObj.stackOffset);

							// Push the address of the object on the stack
							if (onHeap)
								e.bc.InstrSHORT(asBC_VAR, tempObj.stackOffset);
						}

						PrepareFunctionCall(funcs[0], &e.bc, args);
						MoveArgsToStack(funcs[0], &e.bc, args, false);

						if (to.GetTypeInfo()->flags & asOBJ_VALUE)
						{
							// If the object is allocated on the stack, then call the constructor as a normal function
							if (onHeap)
							{
								int offset = 0;
								asCScriptFunction *descr = builder->GetFunctionDescription(funcs[0]);
								offset = descr->parameterTypes[0].GetSizeOnStackDWords();

								e.bc.InstrWORD(asBC_GETREF, (asWORD)offset);
							}
							else
								e.bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);
						}

						PerformFunctionCall(funcs[0], &e, onHeap, &args, CastToObjectType(tempObj.dataType.GetTypeInfo()));

						if (to.GetTypeInfo()->flags & asOBJ_VALUE)
						{
							// Add tag that the object has been initialized
							e.bc.ObjInfo(tempObj.stackOffset, asOBJ_INIT);

							// The constructor doesn't return anything,
							// so we have to manually inform the type of
							// the return value
							e.type = tempObj;
							if (!onHeap)
								e.type.dataType.MakeReference(false);

							// Push the address of the object on the stack again
							e.bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);
						}

						MergeExprBytecodeAndType(ctx, &e);
					}
					else
					{
						ctx->type.Set(asCDataType::CreateType(to.GetTypeInfo(), false));
					}
				}
			}
		}
	}

	return cost;
}

asUINT asCCompiler::ImplicitConvObjectToObject(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv convType, bool generateCode, bool allowObjectConstruct)
{
	// First try a ref cast
	asUINT cost = ImplicitConvObjectRef(ctx, to, node, convType, generateCode);

	// If the desired type is an asOBJ_ASHANDLE then we'll assume it is allowed to implicitly
	// construct the object through any of the available constructors (except those marked as explicit)
	if( to.GetTypeInfo() && (to.GetTypeInfo()->flags & asOBJ_ASHANDLE) && to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() && allowObjectConstruct )
	{
		asCArray<int> funcs;
		funcs = CastToObjectType(to.GetTypeInfo())->beh.constructors;

		// Don't allow use of explicit constructors/factories in implicit conversions
		if (convType == asIC_IMPLICIT_CONV)
		{
			for (asUINT n = 0; n < funcs.GetLength(); n++)
			{
				asCScriptFunction* desc = builder->GetFunctionDescription(funcs[n]);
				if (desc->IsExplicit())
					funcs.RemoveIndex(n--);
			}
		}

		asCArray<asCExprContext *> args;
		args.PushLast(ctx);

		cost = asCC_TO_OBJECT_CONV + MatchFunctions(funcs, args, node, 0, 0, 0, false, true, false);

		// Did we find a matching constructor?
		if( funcs.GetLength() == 1 )
		{
			if( generateCode )
			{
				// If the ASHANDLE receives a variable type parameter, then we need to
				// make sure the expression is treated as a handle and not as a value
				asCScriptFunction *func = engine->scriptFunctions[funcs[0]];
				if( func->parameterTypes[0].GetTokenType() == ttQuestion )
				{
					if( !ctx->type.isExplicitHandle )
					{
						asCDataType toHandle = ctx->type.dataType;
						toHandle.MakeHandle(true);
						toHandle.MakeReference(true);
						toHandle.MakeHandleToConst(ctx->type.dataType.IsReadOnly());
						ImplicitConversion(ctx, toHandle, node, asIC_IMPLICIT_CONV, true, false);

						asASSERT( ctx->type.dataType.IsObjectHandle() );
					}
					ctx->type.isExplicitHandle = true;
				}

				// TODO: This should really reuse the code from CompileConstructCall

				// Allocate the new object
				asCExprValue tempObj;
				tempObj.dataType = to;
				tempObj.dataType.MakeReference(false);
				tempObj.stackOffset = (short)AllocateVariable(tempObj.dataType, true);
				tempObj.dataType.MakeReference(true);
				tempObj.isTemporary = true;
				tempObj.isVariable = true;

				bool onHeap = IsVariableOnHeap(tempObj.stackOffset);

				// Push the address of the object on the stack
				asCExprContext e(engine);
				if( onHeap )
					e.bc.InstrSHORT(asBC_VAR, tempObj.stackOffset);

				PrepareFunctionCall(funcs[0], &e.bc, args);
				MoveArgsToStack(funcs[0], &e.bc, args, false);

				// If the object is allocated on the stack, then call the constructor as a normal function
				if( onHeap )
				{
					int offset = 0;
					asCScriptFunction *descr = builder->GetFunctionDescription(funcs[0]);
					offset = descr->parameterTypes[0].GetSizeOnStackDWords();

					e.bc.InstrWORD(asBC_GETREF, (asWORD)offset);
				}
				else
					e.bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);

				PerformFunctionCall(funcs[0], &e, onHeap, &args, CastToObjectType(tempObj.dataType.GetTypeInfo()));

				// Add tag that the object has been initialized
				e.bc.ObjInfo(tempObj.stackOffset, asOBJ_INIT);

				// The constructor doesn't return anything,
				// so we have to manually inform the type of
				// the return value
				e.type = tempObj;
				if( !onHeap )
					e.type.dataType.MakeReference(false);

				// Push the address of the object on the stack again
				e.bc.InstrSHORT(asBC_PSF, tempObj.stackOffset);

				MergeExprBytecodeAndType(ctx, &e);
			}
			else
			{
				ctx->type.Set(asCDataType::CreateType(to.GetTypeInfo(), false));
			}
		}
	}

	// If the base type is still different, and we are allowed to instance
	// another object then we can try an implicit value cast
	if( to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() && allowObjectConstruct )
	{
		// Attempt implicit value cast
		cost = ImplicitConvObjectValue(ctx, to, node, convType, generateCode);
	}

	// If we still haven't converted the base type to the correct type, then there is
	//  no need to continue as it is not possible to do the conversion
	if( to.GetTypeInfo() != ctx->type.dataType.GetTypeInfo() )
		return asCC_NO_CONV;


	if( to.IsObjectHandle() )
	{
		// There is no extra cost in converting to a handle

		// reference to handle -> handle
		// reference           -> handle
		// object              -> handle
		// handle              -> reference to handle
		// reference           -> reference to handle
		// object              -> reference to handle

		if( (!ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsReadOnly() && !to.IsHandleToConst()) ||
			(ctx->type.dataType.IsObjectHandle() && ctx->type.dataType.IsHandleToConst() && !to.IsHandleToConst()) )
		{
			// String literals can be implicitly converted to temporary local variables in order to pass them to functions expecting non-const
			// TODO: NEWSTRING: Should have an engine property to warn or error on this
			if (ctx->type.isConstant && ctx->type.dataType.IsEqualExceptRefAndConst(engine->stringType))
			{
				if (generateCode)
					PrepareTemporaryVariable(node, ctx);
				else
				{
					ctx->type.dataType.MakeReadOnly(false);
					ctx->type.isConstant = false;
				}

				// Add the cost for the copy
				cost += asCC_TO_OBJECT_CONV;
			}
			else if( convType != asIC_IMPLICIT_CONV )
			{
				asASSERT(node);
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
				Error(str, node);
			}
		}

		if( !ctx->type.dataType.IsObjectHandle() )
		{
			// An object type can be directly converted to a handle of the
			// same type by doing a ref copy to a new variable
			if( ctx->type.dataType.SupportHandles() )
			{
				asCDataType dt = ctx->type.dataType;
				dt.MakeHandle(true);
				dt.MakeReference(false);

				if( generateCode )
				{
					// If the expression is already a local variable, then it is not
					// necessary to do a ref copy, as the ref objects on the stack are
					// really handles, only the handles cannot be modified.
					if( ctx->type.isVariable )
					{
						bool isHandleToConst = ctx->type.dataType.IsReadOnly();
						ctx->type.dataType.MakeReadOnly(false);
						ctx->type.dataType.MakeHandle(true);
						ctx->type.dataType.MakeReadOnly(true);
						ctx->type.dataType.MakeHandleToConst(isHandleToConst);

						if( to.IsReference() && !ctx->type.dataType.IsReference() )
						{
							ctx->bc.Instr(asBC_PopPtr);
							ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
							ctx->type.dataType.MakeReference(true);
						}
						else if( ctx->type.dataType.IsReference() )
						{
							ctx->bc.Instr(asBC_RDSPtr);
							ctx->type.dataType.MakeReference(false);
						}
					}
					else
					{
						int offset = AllocateVariable(dt, true);

						if( ctx->type.dataType.IsReference() )
							ctx->bc.Instr(asBC_RDSPtr);
						ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
						if (dt.IsFuncdef())
							ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
						else
							ctx->bc.InstrPTR(asBC_REFCPY, dt.GetTypeInfo());
						ctx->bc.Instr(asBC_PopPtr);
						ctx->bc.InstrSHORT(asBC_PSF, (short)offset);

						ReleaseTemporaryVariable(ctx->type, &ctx->bc);

						if( to.IsReference() )
							dt.MakeReference(true);
						else
							ctx->bc.Instr(asBC_RDSPtr);

						ctx->type.SetVariable(dt, offset, true);
					}
				}
				else
					ctx->type.dataType = dt;

				// When this conversion is done the expression is no longer an lvalue
				ctx->type.isLValue = false;
			}
		}

		if( ctx->type.dataType.IsObjectHandle() )
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
				asASSERT( ctx->type.dataType.IsObjectHandle() );

				// If the input type is a handle, then a simple ref copy is enough
				bool isExplicitHandle = ctx->type.isExplicitHandle;
				ctx->type.isExplicitHandle = ctx->type.dataType.IsObjectHandle();

				// If the input type is read-only we'll need to temporarily
				// remove this constness, otherwise the assignment will fail
				bool typeIsReadOnly = ctx->type.dataType.IsReadOnly();
				ctx->type.dataType.MakeReadOnly(false);

				// If the object already is a temporary variable, then the copy
				// doesn't have to be made as it is already a unique object
				PrepareTemporaryVariable(node, ctx);

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
	else // if( !to.IsObjectHandle() )
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
				{
					if( ctx->type.dataType.IsReference() )
					{
						// The pointer on the stack refers to the handle
						ctx->bc.Instr(asBC_ChkRefS);
					}
					else
					{
						// The pointer on the stack refers to the object
						ctx->bc.Instr(asBC_CHKREF);
					}
				}

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
						PrepareTemporaryVariable(node, ctx);
					}

					// In case the object was already in a temporary variable, then the function
					// didn't really do anything so we need to remove the constness here
					ctx->type.dataType.MakeReadOnly(false);

					// Add the cost for the copy
					cost += asCC_TO_OBJECT_CONV;
				}
			}

			if( ctx->type.dataType.IsReference() )
			{
				// This may look strange, but a value type allocated on the stack is already
				// correct, so nothing should be done other than remove the mark as reference.
				// For types allocated on the heap, it is necessary to dereference the pointer
				// that is currently on the stack
				if( IsVariableOnHeap(ctx->type.stackOffset) )
					Dereference(ctx, generateCode);
				else
					ctx->type.dataType.MakeReference(false);
			}

			// A non-const object can be converted to a const object directly
			if( !ctx->type.dataType.IsReadOnly() && to.IsReadOnly() )
			{
				ctx->type.dataType.MakeReadOnly(true);
			}
		}
		else // if( to.IsReference() )
		{
			// reference to handle -> reference
			// handle              -> reference
			// object              -> reference

			if( ctx->type.dataType.IsReference() )
			{
				if( ctx->type.isExplicitHandle && ctx->type.dataType.GetTypeInfo() && (ctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE) )
				{
					// ASHANDLE objects are really value types, so explicit handle can be removed
					ctx->type.isExplicitHandle = false;
					ctx->type.dataType.MakeHandle(false);
				}

				// A reference to a handle can be converted to a reference to an object
				// by first reading the address, then verifying that it is not null
				if( !to.IsObjectHandle() && ctx->type.dataType.IsObjectHandle() && !ctx->type.isExplicitHandle )
				{
					ctx->type.dataType.MakeHandle(false);
					if( generateCode )
						ctx->bc.Instr(asBC_ChkRefS);
				}

				// A reference to a non-const can be converted to a reference to a const
				if( to.IsReadOnly() )
					ctx->type.dataType.MakeReadOnly(true);
				else if( ctx->type.dataType.IsReadOnly() && allowObjectConstruct )
				{
					// A reference to a const can be converted to a reference to a
					// non-const by copying the object to a temporary variable
					ctx->type.dataType.MakeReadOnly(false);

					if( generateCode )
					{
						// If the object already is a temporary variable, then the copy
						// doesn't have to be made as it is already a unique object
						PrepareTemporaryVariable(node, ctx);
					}

					// Add the cost for the copy
					cost += asCC_TO_OBJECT_CONV;
				}
			}
			else // if( !ctx->type.dataType.IsReference() )
			{
				// A non-reference handle can be converted to a non-handle reference by checking against null handle
				if( ctx->type.dataType.IsObjectHandle() )
				{
					bool readOnly = false;
					if( ctx->type.dataType.IsHandleToConst() )
						readOnly = true;

					if( generateCode )
					{
						if( ctx->type.isVariable )
							ctx->bc.InstrSHORT(asBC_ChkNullV, ctx->type.stackOffset);
						else
							ctx->bc.Instr(asBC_CHKREF);
					}
					ctx->type.dataType.MakeHandle(false);
					ctx->type.dataType.MakeReference(true);

					// Make sure a handle to const isn't converted to non-const reference
					if( readOnly )
						ctx->type.dataType.MakeReadOnly(true);
				}
				else
				{
					// A value type allocated on the stack is differentiated
					// by it not being a reference. But it can be handled as
					// reference by pushing the pointer on the stack
					if( (ctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) &&
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
						PrepareTemporaryVariable(node, ctx);

						ctx->type.dataType.MakeReadOnly(typeIsReadOnly);

						// Add the cost for the copy
						cost += asCC_TO_OBJECT_CONV;
					}

					// This may look strange as the conversion was to make the expression a reference
					// but a value type allocated on the stack is a reference even without the type
					// being marked as such.
					ctx->type.dataType.MakeReference(IsVariableOnHeap(ctx->type.stackOffset));
				}

				if (to.IsReadOnly())
				{
					// This doesn't cost anything
					ctx->type.dataType.MakeReadOnly(true);
				}

				if (!to.IsReadOnly() && ctx->type.dataType.IsReadOnly())
				{
					// A const object can be converted to a non-const object through a copy
					if (allowObjectConstruct || convType == asIC_EXPLICIT_VAL_CAST)
					{
						ctx->type.dataType.MakeReadOnly(false);

						if (generateCode)
						{
							// Make a temporary copy of the object in order to make it non-const
							PrepareTemporaryVariable(node, ctx);
						}

						// Add the cost for the copy
						cost += asCC_TO_OBJECT_CONV;
					}

					// String literals can be implicitly converted to temporary local variables in order to pass them to functions expecting non-const
					// TODO: NEWSTRING: Should have an engine property to warn or error on this
					if (ctx->type.isConstant && ctx->type.dataType.IsEqualExceptRefAndConst(engine->stringType))
					{
						if (generateCode)
							PrepareTemporaryVariable(node, ctx);
						else
						{
							ctx->type.dataType.MakeReadOnly(false);
							ctx->type.isConstant = false;
						}

						// Add the cost for the copy
						cost += asCC_TO_OBJECT_CONV;
					}
				}
			}
		}
	}

	return cost;
}

asUINT asCCompiler::ImplicitConvPrimitiveToObject(asCExprContext *ctx, const asCDataType &to, asCScriptNode *node, EImplicitConv isExplicit, bool generateCode, bool allowObjectConstruct)
{
	asCObjectType *objType = CastToObjectType(to.GetTypeInfo());
	asASSERT( objType || CastToFuncdefType(to.GetTypeInfo()) );
	if( !objType )
		return asCC_NO_CONV;

	asCArray<int> funcs;
	if (objType->flags & asOBJ_VALUE)
	{
		// For value types the object must have a constructor that takes a single primitive argument either by value or as input reference
		for (asUINT n = 0; n < objType->beh.constructors.GetLength(); n++)
		{
			asCScriptFunction *func = engine->scriptFunctions[objType->beh.constructors[n]];
			if (func->parameterTypes.GetLength() == 1 &&
				func->parameterTypes[0].IsPrimitive() &&
				!(func->inOutFlags[0] & asTM_OUTREF) &&
				(isExplicit == asIC_EXPLICIT_VAL_CAST || !func->IsExplicit()) )
			{
				funcs.PushLast(func->id);
			}
		}
	}
	else if (objType->flags & asOBJ_REF)
	{
		// For ref types the object must have a factory that takes a single primitive argument either by value or as input reference
		for (asUINT n = 0; n < objType->beh.factories.GetLength(); n++)
		{
			asCScriptFunction *func = engine->scriptFunctions[objType->beh.factories[n]];
			if (func->parameterTypes.GetLength() == 1 &&
				func->parameterTypes[0].IsPrimitive() &&
				!(func->inOutFlags[0] & asTM_OUTREF) &&
				(isExplicit == asIC_EXPLICIT_VAL_CAST || !func->IsExplicit()))
			{
				funcs.PushLast(func->id);
			}
		}
	}

	if( funcs.GetLength() == 0 )
		return asCC_NO_CONV;

	// Check if it is possible to choose a best match
	asCExprContext arg(engine);
	arg.type = ctx->type;
	arg.exprNode = ctx->exprNode; // Use the same node for compiler messages
	asCArray<asCExprContext*> args;
	args.PushLast(&arg);
	asUINT cost = asCC_TO_OBJECT_CONV + MatchFunctions(funcs, args, 0, 0, 0, objType, false, true, false);
	if( funcs.GetLength() != 1 )
		return asCC_NO_CONV;

	if( !generateCode )
	{
		ctx->type.Set(to);
		return cost;
	}

	// TODO: clean up: This part is similar to CompileConstructCall(). It should be put in a common function

	// Clear the type of ctx, as the type is moved to the arg
	ctx->type.SetDummy();

	// Value types and script types are allocated through the constructor
	asCExprValue tempObj;
	bool onHeap = false;

	if (!(objType->flags & asOBJ_REF))
	{
		tempObj.dataType = to;
		tempObj.stackOffset = (short)AllocateVariable(to, true);
		tempObj.dataType.MakeReference(true);
		tempObj.isTemporary = true;
		tempObj.isVariable = true;

		onHeap = IsVariableOnHeap(tempObj.stackOffset);

		// Push the address of the object on the stack
		if (onHeap)
			ctx->bc.InstrSHORT(asBC_VAR, tempObj.stackOffset);
	}

	PrepareFunctionCall(funcs[0], &ctx->bc, args);
	MoveArgsToStack(funcs[0], &ctx->bc, args, false);

	if( !(objType->flags & asOBJ_REF) )
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

		PerformFunctionCall(funcs[0], ctx, onHeap, &args, CastToObjectType(tempObj.dataType.GetTypeInfo()));

		// Add tag that the object has been initialized
		ctx->bc.ObjInfo(tempObj.stackOffset, asOBJ_INIT);

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

		// Make another pass to make sure the result has the correct handle and reference settings
		ImplicitConversion(ctx, to, node, isExplicit, generateCode, allowObjectConstruct);
	}

	return cost;
}

void asCCompiler::ImplicitConversionConstant(asCExprContext *from, const asCDataType &to, asCScriptNode *node, EImplicitConv convType)
{
	asASSERT(from->type.isConstant);

	// TODO: node should be the node of the value that is
	//       converted (not the operator that provokes the implicit
	//       conversion)

	// If the base type is correct there is no more to do
	if( to.IsEqualExceptRefAndConst(from->type.dataType) ) return;

	// References cannot be constants
	if( from->type.dataType.IsReference() ) return;

	if( (to.IsIntegerType() && to.GetSizeInMemoryDWords() == 1 && !to.IsEnumType()) ||
		(to.IsEnumType() && convType == asIC_EXPLICIT_VAL_CAST) )
	{
		if( from->type.dataType.IsFloatType() ||
			from->type.dataType.IsDoubleType() ||
			from->type.dataType.IsUnsignedType() ||
			from->type.dataType.IsIntegerType() )
		{
			asCDataType targetDt;
			if (to.IsEnumType())
				targetDt = to;
			else
				targetDt = asCDataType::CreatePrimitive(ttInt, true);

			// Transform the value
			// Float constants can be implicitly converted to int
			if( from->type.dataType.IsFloatType() )
			{
				float fc = from->type.GetConstantF();
				int ic = int(fc);

				if( float(ic) != fc )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
				}

				from->type.SetConstantDW(targetDt, ic);
			}
			// Double constants can be implicitly converted to int
			else if( from->type.dataType.IsDoubleType() )
			{
				double fc = from->type.GetConstantD();
				int ic = int(fc);

				if( double(ic) != fc )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
				}

				from->type.SetConstantDW(targetDt, ic);
			}
			else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				// Verify that it is possible to convert to signed without getting negative
				if( from->type.dataType.GetSizeInMemoryBytes() == 4 &&
					int(from->type.GetConstantDW()) < 0 &&
					convType != asIC_EXPLICIT_VAL_CAST &&
					node != 0 )
					Warning(TXT_CHANGE_SIGN, node);

				// Convert to 32bit
				if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
					from->type.SetConstantDW(targetDt, from->type.GetConstantB());
				else if (from->type.dataType.GetSizeInMemoryBytes() == 2)
					from->type.SetConstantDW(targetDt, from->type.GetConstantW());
				else
					from->type.dataType = targetDt;
			}
			else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				if (asQWORD(from->type.GetConstantQW()) >> 31)
					if (convType != asIC_EXPLICIT_VAL_CAST && node) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				// Convert to 32bit
				from->type.SetConstantDW(targetDt, int(from->type.GetConstantQW()));
			}
			else if (from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2)
			{
				if (int(from->type.GetConstantQW()) != asINT64(from->type.GetConstantQW()))
					if (convType != asIC_EXPLICIT_VAL_CAST && node) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				// Convert to 32bit
				from->type.SetConstantDW(targetDt, int(from->type.GetConstantQW()));
			}
			else if (from->type.dataType.IsIntegerType() &&
				from->type.dataType.GetSizeInMemoryBytes() < 4)
			{
				// Convert to 32bit
				if (from->type.dataType.GetSizeInMemoryBytes() == 1)
					from->type.SetConstantDW(targetDt, (asINT8)from->type.GetConstantB());
				else if (from->type.dataType.GetSizeInMemoryBytes() == 2)
					from->type.SetConstantDW(targetDt, (asINT16)from->type.GetConstantW());
			}
			else
			{
				// Only int32 and enums should come here and as these are 32bit
				// already nothing needs to be done except set the target type
				asASSERT((from->type.dataType.GetTokenType() == ttInt ||
					      from->type.dataType.IsEnumType()) &&
					     from->type.dataType.GetSizeInMemoryBytes() == 4);

				from->type.dataType = targetDt;
			}
		}

		// Check if a downsize is necessary
		if( to.IsIntegerType() &&
			from->type.dataType.IsIntegerType() &&
		    from->type.dataType.GetSizeInMemoryBytes() > to.GetSizeInMemoryBytes() )
		{
			// Verify if it is possible
			if( to.GetSizeInMemoryBytes() == 1 )
			{
				if( asINT8(from->type.GetConstantDW()) != int(from->type.GetConstantDW()) )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.SetConstantB(asCDataType::CreatePrimitive(to.GetTokenType(), true), asINT8(from->type.GetConstantDW()));
			}
			else if( to.GetSizeInMemoryBytes() == 2 )
			{
				if( asINT16(from->type.GetConstantDW()) != int(from->type.GetConstantDW()) )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.SetConstantW(asCDataType::CreatePrimitive(to.GetTokenType(), true), asINT16(from->type.GetConstantDW()));
			}
		}
	}
	else if( to.IsIntegerType() && to.GetSizeInMemoryDWords() == 2 )
	{
		// Float constants can be implicitly converted to int
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.GetConstantF();
			asINT64 ic = asINT64(fc);

			if( float(ic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), ic);
		}
		// Double constants can be implicitly converted to int
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.GetConstantD();
			asINT64 ic = asINT64(fc);

			if( double(ic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), ic);
		}
		else if( from->type.dataType.IsUnsignedType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), from->type.GetConstantW());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), from->type.GetConstantDW());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 8 )
			{
				if( asINT64(from->type.GetConstantQW()) < 0 )
				{
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
				}
				from->type.dataType = asCDataType::CreatePrimitive(ttInt64, true);
			}
		}
		else if( from->type.dataType.IsIntegerType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), (asINT8)from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), (asINT16)from->type.GetConstantW());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), (int)from->type.GetConstantDW());
		}
	}
	else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 1 )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.GetConstantF();
			// Some compilers set the value to 0 when converting a negative float to unsigned int.
			// To maintain a consistent behaviour across compilers we convert to int first.
			asUINT uic = asUINT(int(fc));

			if( float(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), uic);

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.GetConstantD();
			// Some compilers set the value to 0 when converting a negative double to unsigned int.
			// To maintain a consistent behaviour across compilers we convert to int first.
			asUINT uic = asUINT(int(fc));

			if( double(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), uic);

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsIntegerType() )
		{
			// Verify that it is possible to convert to unsigned without loosing negative
			if( (from->type.dataType.GetSizeInMemoryBytes() > 4 && asINT64(from->type.GetConstantQW()) < 0) ||
				(from->type.dataType.GetSizeInMemoryBytes() == 4 && int(from->type.GetConstantDW()) < 0) ||
				(from->type.dataType.GetSizeInMemoryBytes() == 2 && asINT16(from->type.GetConstantW()) < 0) ||
				(from->type.dataType.GetSizeInMemoryBytes() == 1 && asINT8(from->type.GetConstantB()) < 0))
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			// Check if any data is lost
			if( from->type.dataType.GetSizeInMemoryBytes() > 4 && (from->type.GetConstantQW() >> 32) != 0 && (from->type.GetConstantQW() >> 32) != 0xFFFFFFFF )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);
			}

			// Convert to 32bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), (asINT8)from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), (asINT16)from->type.GetConstantW());
			else if (from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), (int)from->type.GetConstantDW());
			else
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), (int)(asINT64)from->type.GetConstantQW());

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsUnsignedType() &&
		         from->type.dataType.GetSizeInMemoryBytes() < 4 )
		{
			// Convert to 32bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantDW(asCDataType::CreatePrimitive(ttUInt, true), from->type.GetConstantW());

			// Try once more, in case of a smaller type
			ImplicitConversionConstant(from, to, node, convType);
		}
		else if( from->type.dataType.IsUnsignedType() &&
		         from->type.dataType.GetSizeInMemoryBytes() > to.GetSizeInMemoryBytes() )
		{
			// Verify if it is possible
			if( to.GetSizeInMemoryBytes() == 1 )
			{
				if( (from->type.dataType.GetSizeInMemoryBytes() == 2 && asBYTE(from->type.GetConstantW()) != from->type.GetConstantW()) ||
					(from->type.dataType.GetSizeInMemoryBytes() == 4 && asBYTE(from->type.GetConstantDW()) != from->type.GetConstantDW()) ||
					(from->type.dataType.GetSizeInMemoryBytes() == 8 && asBYTE(from->type.GetConstantQW()) != from->type.GetConstantQW()) )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
					from->type.SetConstantB(asCDataType::CreatePrimitive(to.GetTokenType(), true), asBYTE(from->type.GetConstantW()));
				else if (from->type.dataType.GetSizeInMemoryBytes() == 4)
					from->type.SetConstantB(asCDataType::CreatePrimitive(to.GetTokenType(), true), asBYTE(from->type.GetConstantDW()));
				else if (from->type.dataType.GetSizeInMemoryBytes() == 8)
					from->type.SetConstantB(asCDataType::CreatePrimitive(to.GetTokenType(), true), asBYTE(from->type.GetConstantQW()));
			}
			else if( to.GetSizeInMemoryBytes() == 2 )
			{
				if( (from->type.dataType.GetSizeInMemoryBytes() == 4 && asWORD(from->type.GetConstantDW()) != from->type.GetConstantDW()) ||
					(from->type.dataType.GetSizeInMemoryBytes() == 8 && asWORD(from->type.GetConstantQW()) != from->type.GetConstantQW()) )
					if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				if (from->type.dataType.GetSizeInMemoryBytes() == 4)
					from->type.SetConstantW(asCDataType::CreatePrimitive(to.GetTokenType(), true), asWORD(from->type.GetConstantDW()));
				else if (from->type.dataType.GetSizeInMemoryBytes() == 8)
					from->type.SetConstantW(asCDataType::CreatePrimitive(to.GetTokenType(), true), asWORD(from->type.GetConstantQW()));
			}
			else if (to.GetSizeInMemoryBytes() == 4)
			{
				if( asDWORD(from->type.GetConstantQW()) != from->type.GetConstantQW())
					if (convType != asIC_EXPLICIT_VAL_CAST && node) Warning(TXT_VALUE_TOO_LARGE_FOR_TYPE, node);

				from->type.SetConstantDW(asCDataType::CreatePrimitive(to.GetTokenType(), true), asDWORD(from->type.GetConstantQW()));
			}
		}
	}
	else if( to.IsUnsignedType() && to.GetSizeInMemoryDWords() == 2 )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float fc = from->type.GetConstantF();
			// Convert first to int64 then to uint64 to avoid negative float becoming 0 on gnuc base compilers
			asQWORD uic = asQWORD(asINT64(fc));

#if !defined(_MSC_VER) || _MSC_VER > 1200 // MSVC++ 6
			// MSVC6 doesn't support this conversion
			if( float(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}
#endif

			from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), uic);
		}
		else if( from->type.dataType.IsDoubleType() )
		{
			double fc = from->type.GetConstantD();
			// Convert first to int64 then to uint64 to avoid negative float becoming 0 on gnuc base compilers
			asQWORD uic = asQWORD(asINT64(fc));

#if !defined(_MSC_VER) || _MSC_VER > 1200 // MSVC++ 6
			// MSVC6 doesn't support this conversion
			if( double(uic) != fc )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}
#endif

			from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), uic);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), (asINT64)(asINT8)from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), (asINT64)(asINT16)from->type.GetConstantW());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), (asINT64)(int)from->type.GetConstantDW());

			// Verify that it is possible to convert to unsigned without loosing negative
			if( asINT64(from->type.GetConstantQW()) < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			// Verify that it is possible to convert to unsigned without loosing negative
			if( asINT64(from->type.GetConstantQW()) < 0 )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_CHANGE_SIGN, node);
			}

			from->type.dataType = asCDataType::CreatePrimitive(ttUInt64, true);
		}
		else if( from->type.dataType.IsUnsignedType() )
		{
			// Convert to 64bit
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), from->type.GetConstantB());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), from->type.GetConstantW());
			else if( from->type.dataType.GetSizeInMemoryBytes() == 4 )
				from->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), from->type.GetConstantDW());
		}
	}
	else if( to.IsFloatType() )
	{
		if( from->type.dataType.IsDoubleType() )
		{
			double ic = from->type.GetConstantD();
			float fc = float(ic);

			from->type.SetConstantF(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			int ic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				ic = (asINT8)from->type.GetConstantB();
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				ic = (asINT16)from->type.GetConstantW();
			else
				ic = (int)from->type.GetConstantDW();
			float fc = float(ic);

			if( int(fc) != ic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantF(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			float fc = float(asINT64(from->type.GetConstantQW()));
			if( asINT64(fc) != asINT64(from->type.GetConstantQW()) )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantF(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			unsigned int uic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				uic = from->type.GetConstantB();
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				uic = from->type.GetConstantW();
			else
				uic = from->type.GetConstantDW();
			float fc = float(uic);

			if( (unsigned int)(fc) != uic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantF(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			float fc = float((asINT64)from->type.GetConstantQW());

			if( asQWORD(fc) != from->type.GetConstantQW())
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantF(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
	}
	else if( to.IsDoubleType() )
	{
		if( from->type.dataType.IsFloatType() )
		{
			float ic = from->type.GetConstantF();
			double fc = double(ic);

			from->type.SetConstantD(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			int ic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				ic = (asINT8)from->type.GetConstantB();
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				ic = (asINT16)from->type.GetConstantW();
			else
				ic = (int)from->type.GetConstantDW();
			double fc = double(ic);

			if( int(fc) != ic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantD(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsIntegerType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			double fc = double(asINT64(from->type.GetConstantQW()));

			if( asINT64(fc) != asINT64(from->type.GetConstantQW()) )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantD(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 1 )
		{
			// Must properly convert value in case the from value is smaller
			unsigned int uic;
			if( from->type.dataType.GetSizeInMemoryBytes() == 1 )
				uic = from->type.GetConstantB();
			else if( from->type.dataType.GetSizeInMemoryBytes() == 2 )
				uic = from->type.GetConstantW();
			else
				uic = from->type.GetConstantDW();
			double fc = double(uic);

			if( (unsigned int)(fc) != uic )
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantD(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
		else if( from->type.dataType.IsUnsignedType() && from->type.dataType.GetSizeInMemoryDWords() == 2 )
		{
			double fc = double((asINT64)from->type.GetConstantQW());

			if( asQWORD(fc) != from->type.GetConstantQW())
			{
				if( convType != asIC_EXPLICIT_VAL_CAST && node ) Warning(TXT_NOT_EXACT, node);
			}

			from->type.SetConstantD(asCDataType::CreatePrimitive(to.GetTokenType(), true), fc);
		}
	}
}

int asCCompiler::DoAssignment(asCExprContext *ctx, asCExprContext *lctx, asCExprContext *rctx, asCScriptNode *lexpr, asCScriptNode *rexpr, eTokenType op, asCScriptNode *opNode)
{
	// Don't allow any operators on expressions that take address of class method
	// If methodName is set but the type is not an object, then it is a global function
	if( lctx->methodName != "" || rctx->IsClassMethod() )
	{
		Error(TXT_INVALID_OP_ON_METHOD, opNode);
		return -1;
	}

	// Implicit handle types should always be treated as handles in assignments
	if (lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_IMPLICIT_HANDLE) )
	{
		lctx->type.dataType.MakeHandle(true);
		lctx->type.isExplicitHandle = true;
	}

	// Urho3D: if there is a handle type, and it does not have an overloaded assignment operator, convert to an explicit handle
	// for scripting convenience. (For the Urho3D handle types, value assignment is not supported)
	if (lctx->type.dataType.IsObjectHandle() && !lctx->type.dataType.IsTemplate() && !lctx->type.isExplicitHandle &&
		(!lctx->type.dataType.GetBehaviour() || !lctx->type.dataType.GetBehaviour()->copy))
		lctx->type.isExplicitHandle = true;

	// If the left hand expression is a property accessor, then that should be used
	// to do the assignment instead of the ordinary operator. The exception is when
	// the property accessor is for a handle property, and the operation is a value
	// assignment.
	if( (lctx->property_get || lctx->property_set) &&
		!(lctx->type.dataType.IsObjectHandle() && !lctx->type.isExplicitHandle) )
	{
		if( op != ttAssignment )
		{
			// Generate the code for the compound assignment, i.e. get the value, apply operator, then set the value
			return ProcessPropertyGetSetAccessor(ctx, lctx, rctx, op, opNode);
		}

		// It is not allowed to do a handle assignment on a property
		// accessor that doesn't take a handle in the set accessor.
		if( lctx->property_set && lctx->type.isExplicitHandle )
		{
			// set_opIndex has 2 arguments, where as normal setters have only 1
			asCArray<asCDataType>& parameterTypes =
				builder->GetFunctionDescription(lctx->property_set)->parameterTypes;
			if( !parameterTypes[parameterTypes.GetLength() - 1].IsObjectHandle() )
			{
				// Process the property to free the memory
				ProcessPropertySetAccessor(lctx, rctx, opNode);

				Error(TXT_HANDLE_ASSIGN_ON_NON_HANDLE_PROP, opNode);
				return -1;
			}
		}

		MergeExprBytecodeAndType(ctx, lctx);

		return ProcessPropertySetAccessor(ctx, rctx, opNode);
	}
	else if( lctx->property_get && lctx->type.dataType.IsObjectHandle() && !lctx->type.isExplicitHandle )
	{
		// Get the handle to the object that will be used for the value assignment
		if( ProcessPropertyGetAccessor(lctx, opNode) < 0 )
			return -1;
	}

	if( lctx->type.dataType.IsPrimitive() )
	{
		if( !lctx->type.isLValue )
		{
			Error(TXT_NOT_LVALUE, lexpr);
			return -1;
		}

		if( op != ttAssignment )
		{
			// Compute the operator before the assignment
			asCExprValue lvalue = lctx->type;

			if( lctx->type.isTemporary && !lctx->type.isVariable )
			{
				// The temporary variable must not be freed until the
				// assignment has been performed. lvalue still holds
				// the information about the temporary variable
				lctx->type.isTemporary = false;
			}

			asCExprContext o(engine);
			CompileOperator(opNode, lctx, rctx, &o);
			MergeExprBytecode(rctx, &o);
			rctx->type = o.type;

			// Convert the rvalue to the right type and validate it
			PrepareForAssignment(&lvalue.dataType, rctx, rexpr, false);

			MergeExprBytecode(ctx, rctx);
			lctx->type = lvalue;

			// The lvalue continues the same, either it was a variable, or a reference in the register
		}
		else
		{
			// Convert the rvalue to the right type and validate it
			PrepareForAssignment(&lctx->type.dataType, rctx, rexpr, false, lctx);

			MergeExprBytecode(ctx, rctx);
			MergeExprBytecode(ctx, lctx);
		}

		ReleaseTemporaryVariable(rctx->type, &ctx->bc);

		PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

		ctx->type = lctx->type;
	}
	else if( lctx->type.isExplicitHandle )
	{
		if( !lctx->type.isLValue )
		{
			Error(TXT_NOT_LVALUE, lexpr);
			return -1;
		}

		// Object handles don't have any compound assignment operators
		if( op != ttAssignment )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, lexpr);
			return -1;
		}

		if( lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE) )
		{
			// The object is a value type but that should be treated as a handle

			// Make sure the right hand value is a handle
			if( !rctx->type.isExplicitHandle &&
				!(rctx->type.dataType.GetTypeInfo() && (rctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE)) )
			{
				// Function names can be considered handles already
				if( rctx->methodName == "" )
				{
					asCDataType dt = rctx->type.dataType;
					dt.MakeHandle(true);
					dt.MakeReference(false);

					PrepareArgument(&dt, rctx, rexpr, true, asTM_INREF);
					if( !dt.IsEqualExceptRefAndConst(rctx->type.dataType) )
					{
						asCString str;
						str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
						Error(str, rexpr);
						return -1;
					}
				}

				if (!rctx->type.dataType.IsObjectHandle() && !rctx->type.dataType.SupportHandles())
				{
					Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, rexpr);
					return -1;
				}

				// Mark the right hand expression as explicit handle even if the user didn't do it, otherwise
				// the code for moving the argument to the stack may not know to correctly handle the argument type
				// in case of variable parameter type.
				rctx->type.isExplicitHandle = true;
			}

			if( CompileOverloadedDualOperator(opNode, lctx, rctx, false, ctx, true) )
			{
				// An overloaded assignment operator was found (or a compilation error occured)
				return 0;
			}

			// The object must implement the opAssign method
			asCString msg;
			msg.Format(TXT_NO_APPROPRIATE_OPHNDLASSIGN_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(msg.AddressOf(), opNode);
			return -1;
		}
		else
		{
			asCDataType dt = lctx->type.dataType;
			dt.MakeReference(false);

			PrepareArgument(&dt, rctx, rexpr, false, asTM_INREF , true);
			if( !dt.IsEqualExceptRefAndConst(rctx->type.dataType) )
			{
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
				Error(str, rexpr);
				return -1;
			}

			MergeExprBytecode(ctx, rctx);
			MergeExprBytecode(ctx, lctx);

			if(!rctx->type.isRefSafe)
				ctx->bc.InstrWORD(asBC_GETOBJREF, AS_PTR_SIZE);

			PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

			ReleaseTemporaryVariable(rctx->type, &ctx->bc);

			ctx->type = lctx->type;

			// After the handle assignment the original handle is left on the stack
			ctx->type.dataType.MakeReference(false);
		}
	}
	else // if( lctx->type.dataType.IsObject() )
	{
		// The lvalue reference may be marked as a temporary, if for example
		// it was originated as a handle returned from a function. In such
		// cases it must be possible to assign values to it anyway.
		if( lctx->type.dataType.IsObjectHandle() && !lctx->type.isExplicitHandle )
		{
			// Convert the handle to a object reference
			asCDataType to;
			to = lctx->type.dataType;
			to.MakeHandle(false);
			ImplicitConversion(lctx, to, lexpr, asIC_IMPLICIT_CONV);
			lctx->type.isLValue = true; // Handle may not have been an lvalue, but the dereferenced object is
		}

		// Check for overloaded assignment operator
		if( CompileOverloadedDualOperator(opNode, lctx, rctx, false, ctx) )
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
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, lexpr);
			return -1;
		}

		// If the left hand expression is simple, i.e. without any
		// function calls or allocations of memory, then we can avoid
		// doing a copy of the right hand expression (done by PrepareArgument).
		// Instead the reference to the value can be placed directly on the
		// stack.
		//
		// This optimization should only be done for value types, where
		// the application developer is responsible for making the
		// implementation safe against unwanted destruction of the input
		// reference before the time.
		bool simpleExpr = (lctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) && lctx->bc.IsSimpleExpression();

		// Implicitly convert the rvalue to the type of the lvalue
		bool needConversion = false;
		if( !lctx->type.dataType.IsEqualExceptRefAndConst(rctx->type.dataType) )
			needConversion = true;
		
		if( !simpleExpr || needConversion )
		{
			if( rctx->type.dataType.IsObjectHandle() && !rctx->type.isExplicitHandle && 
			    !lctx->type.dataType.IsObjectHandle() && rctx->type.dataType.GetTypeInfo() == lctx->type.dataType.GetTypeInfo() )
			{
				// Make the conversion from handle to non-handle without creating 
				// a copy of the object (otherwise done by PrepareArgument)
				asCDataType dt = rctx->type.dataType;
				dt.MakeHandle(false);
				ImplicitConversion(rctx, dt, rexpr, asIC_IMPLICIT_CONV);
				needConversion = false;
			}
			
			asCDataType dt = lctx->type.dataType;
			dt.MakeReference(true);
			// A funcdef can be accessed by ref, but only as read-only
			if( dt.IsFuncdef() && !dt.IsObjectHandle() )
				dt.MakeReadOnly(true);
			int r = PrepareArgument(&dt, rctx, rexpr, true, 1, !needConversion);
			if( r < 0 )
				return -1;
			if( !dt.IsEqualExceptRefAndConst(rctx->type.dataType) )
			{
				asCString str;
				str.Format(TXT_CANT_IMPLICITLY_CONVERT_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
				Error(str, rexpr);
				return -1;
			}
		}
		else
		{
			// Process any property accessor first, before placing the final reference on the stack
			if( ProcessPropertyGetAccessor(rctx, rexpr) < 0 )
				return -1;

			if( rctx->type.dataType.IsReference() && (!(rctx->type.isVariable || rctx->type.isTemporary) || IsVariableOnHeap(rctx->type.stackOffset)) )
				rctx->bc.Instr(asBC_RDSPtr);
		}

		MergeExprBytecode(ctx, rctx);
		MergeExprBytecode(ctx, lctx);

		if( !simpleExpr || needConversion )
		{
			if( !rctx->type.isRefSafe && (rctx->type.isVariable || rctx->type.isTemporary) )
			{
				if( !IsVariableOnHeap(rctx->type.stackOffset) )
					// TODO: runtime optimize: Actually the reference can be pushed on the stack directly
					//                         as the value allocated on the stack is guaranteed to be safe.
					//                         The bytecode optimizer should be able to determine this and optimize away the VAR + GETREF
					ctx->bc.InstrWORD(asBC_GETREF, AS_PTR_SIZE);
				else
					ctx->bc.InstrWORD(asBC_GETOBJREF, AS_PTR_SIZE);
			}
		}

		PerformAssignment(&lctx->type, &rctx->type, &ctx->bc, opNode);

		ReleaseTemporaryVariable(rctx->type, &ctx->bc);

		ctx->type = lctx->type;
	}

	return 0;
}

int asCCompiler::CompileAssignment(asCScriptNode *expr, asCExprContext *ctx)
{
	asASSERT(expr->nodeType == snAssignment);

	asCScriptNode *lexpr = expr->firstChild;
	if( lexpr->next )
	{
		// Compile the two expression terms
		asCExprContext lctx(engine), rctx(engine);
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

int asCCompiler::CompileCondition(asCScriptNode *expr, asCExprContext *ctx)
{
	asCExprValue ctype;

	// Compile the conditional expression
	asCScriptNode *cexpr = expr->firstChild;
	if( cexpr->next )
	{
		//-------------------------------
		// Compile the condition
		asCExprContext e(engine);
		int r = CompileExpression(cexpr, &e);
		if( r < 0 )
			e.type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);

		// Allow value types to be converted to bool using 'bool opImplConv()'
		if( e.type.dataType.GetTypeInfo() && (e.type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
			ImplicitConversion(&e, asCDataType::CreatePrimitive(ttBool, false), cexpr, asIC_IMPLICIT_CONV);

		if( r >= 0 && !e.type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		{
			Error(TXT_EXPR_MUST_BE_BOOL, cexpr);
			e.type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
		} 
		ctype = e.type;

		if( ProcessPropertyGetAccessor(&e, cexpr) < 0)
			return -1;

		if( e.type.dataType.IsReference() ) ConvertToVariable(&e);
		ProcessDeferredParams(&e);

		//-------------------------------
		// Compile the left expression
		asCExprContext le(engine);
		int lr = CompileAssignment(cexpr->next, &le);

		// Resolve any function names already
		DetermineSingleFunc(&le, cexpr->next);

		//-------------------------------
		// Compile the right expression
		asCExprContext re(engine);
		int rr = CompileAssignment(cexpr->next->next, &re);
		DetermineSingleFunc(&re, cexpr->next->next);

		if (lr >= 0 && rr >= 0)
		{
			// Don't allow any operators on expressions that take address of class method
			if (le.IsClassMethod() || re.IsClassMethod())
			{
				Error(TXT_INVALID_OP_ON_METHOD, expr);
				return -1;
			}

			if (ProcessPropertyGetAccessor(&le, cexpr->next) < 0)
				return -1;
			if (ProcessPropertyGetAccessor(&re, cexpr->next->next) < 0)
				return -1;

			bool isExplicitHandle = le.type.isExplicitHandle || re.type.isExplicitHandle;

			// Allow an anonymous initialization list to be converted to the type in the other condition
			if (le.IsAnonymousInitList() && re.type.dataType.GetBehaviour() && re.type.dataType.GetBehaviour()->listFactory)
			{
				asCDataType to = re.type.dataType;
				to.MakeReference(false);
				to.MakeReadOnly(false);
				ImplicitConversion(&le, to, cexpr->next, asIC_IMPLICIT_CONV);
			}
			else if (re.IsAnonymousInitList() && le.type.dataType.GetBehaviour() && le.type.dataType.GetBehaviour()->listFactory)
			{
				asCDataType to = le.type.dataType;
				to.MakeReference(false);
				to.MakeReadOnly(false);
				ImplicitConversion(&re, to, cexpr->next->next, asIC_IMPLICIT_CONV);
			}

			if (le.IsAnonymousInitList())
			{
				Error(TXT_CANNOT_RESOLVE_AUTO, cexpr->next);
				return -1;
			}
			else if (re.IsAnonymousInitList())
			{
				Error(TXT_CANNOT_RESOLVE_AUTO, cexpr->next->next);
				return -1;
			}

			// Try to perform an implicit cast to make the two operands of the same type
			// Choose the conversion that is the least costly
			if (le.type.dataType != re.type.dataType)
			{
				asCExprContext tmp(engine);
				tmp.type = le.type;
				tmp.type.dataType.MakeReference(false);
				asUINT costAtoB = ImplicitConversion(&tmp, re.type.dataType, cexpr->next, asIC_IMPLICIT_CONV, false);
				if (!tmp.type.dataType.IsEqualExceptRef(re.type.dataType))
					costAtoB = 0xFFFFFFFF;
				tmp.type = re.type;
				tmp.type.dataType.MakeReference(false);
				asUINT costBtoA = ImplicitConversion(&tmp, le.type.dataType, cexpr->next->next, asIC_IMPLICIT_CONV, false);
				if (!tmp.type.dataType.IsEqualExceptRef(le.type.dataType))
					costBtoA = 0xFFFFFFFF;

				if (costAtoB < costBtoA && costAtoB != 0xFFFFFFFF)
				{
					Dereference(&le, true);
					ImplicitConversion(&le, re.type.dataType, cexpr->next, asIC_IMPLICIT_CONV, true);
				}
				else if (costAtoB > costBtoA && costBtoA != 0xFFFFFFFF)
				{
					Dereference(&re, true);
					ImplicitConversion(&re, le.type.dataType, cexpr->next->next, asIC_IMPLICIT_CONV, true);
				}

				// If the cost for conversion is the same in both directions we have an ambigious situation, 
				// which we do not resolve. In that case the script need to perform an explicit conversion
			}

			// Allow a 0 to be implicitly converted to the other type
			if (le.type.isConstant && le.type.GetConstantData() == 0 && le.type.dataType.IsIntegerType())
			{
				asCDataType to = re.type.dataType;
				to.MakeReference(false);
				to.MakeReadOnly(true);
				ImplicitConversionConstant(&le, to, cexpr->next, asIC_IMPLICIT_CONV);
			}
			else if( re.type.isConstant && re.type.GetConstantData() == 0 && re.type.dataType.IsIntegerType())
			{
				asCDataType to = le.type.dataType;
				to.MakeReference(false);
				to.MakeReadOnly(true);
				ImplicitConversionConstant(&re, to, cexpr->next->next, asIC_IMPLICIT_CONV);
			}

			// Allow expression to be converted to handle if the other is handle
			if (!le.type.dataType.IsObjectHandle() && re.type.dataType.IsObjectHandle() && le.type.dataType.GetTypeInfo() == re.type.dataType.GetTypeInfo() )
			{
				asCDataType dt = le.type.dataType;
				dt.MakeHandle(true);
				ImplicitConversion(&le, dt, cexpr->next, asIC_IMPLICIT_CONV);
			}
			if (!re.type.dataType.IsObjectHandle() && le.type.dataType.IsObjectHandle() && le.type.dataType.GetTypeInfo() == re.type.dataType.GetTypeInfo())
			{
				asCDataType dt = re.type.dataType;
				dt.MakeHandle(true);
				ImplicitConversion(&re, dt, cexpr->next->next, asIC_IMPLICIT_CONV);
			}

			// Allow either case to be converted to const @ if the other is const @
			if( (le.type.dataType.IsHandleToConst() && !le.type.IsNullConstant()) || (re.type.dataType.IsHandleToConst() && !re.type.dataType.IsNullHandle()) )
			{
				le.type.dataType.MakeHandleToConst(true);
				re.type.dataType.MakeHandleToConst(true);
			}

			// Make sure both expressions have the same type
			if (!le.type.dataType.IsEqualExceptRefAndConst(re.type.dataType))
			{
				Error(TXT_BOTH_MUST_BE_SAME, expr);
				return -1;
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

				// Set the type of the result
				ctx->type = le.type;
			}
			else if (le.type.IsNullConstant() && re.type.IsNullConstant())
			{
				// Special case for when both results are 'null'
				// TODO: Other expressions where both results are identical literal constants can probably also be handled this way

				// Put the code for the condition expression on the output
				MergeExprBytecode(ctx, &e);

				// Load the result into the register, but ignore the value since both paths give the same response
				ctx->type = e.type;
				ConvertToVariable(ctx);
				ctx->bc.InstrSHORT(asBC_CpyVtoR4, ctx->type.stackOffset);
				ReleaseTemporaryVariable(ctx->type, &ctx->bc);

				// Return a null constant
				ctx->bc.Instr(asBC_PshNull);
				ctx->type.SetNullConstant();
			}
			else
			{
				// Allow "(a ? b : c) = d;" and "return (a ? b : c);" (where the latter returns the reference)
				//
				// Restrictions for the condition to be used as lvalue:
				//  1. both b and c must be of the same type and be lvalue references
				//  2. neither of the expressions can have any deferred arguments
				//     that would have to be cleaned up after the reference
				//  3. neither expression can be temporary
				//
				// If either expression is local, the resulting lvalue is not valid
				// for return since it is not allowed to return references to local
				// variables.
				//
				// The reference to the local variable must be loaded into the register,
				// the resulting expression must not be considered as a local variable
				// with a stack offset (i.e. it will not be allowed to use asBC_VAR)

				if( le.type.isLValue && re.type.isLValue &&
					le.deferredParams.GetLength() == 0 && re.deferredParams.GetLength() == 0 &&
					!le.type.isTemporary && !re.type.isTemporary &&
					le.type.dataType == re.type.dataType )
				{
					// Put the code for the condition expression on the output
					MergeExprBytecode(ctx, &e);

					// Add the branch decision
					ctx->type = e.type;
					ConvertToVariable(ctx);
					ctx->bc.InstrSHORT(asBC_CpyVtoR4, ctx->type.stackOffset);
					ctx->bc.Instr(asBC_ClrHi);
					ctx->bc.InstrDWORD(asBC_JZ, elseLabel);
					ReleaseTemporaryVariable(ctx->type, &ctx->bc);

					// Start of the left expression
					MergeExprBytecode(ctx, &le);
					if( !le.type.dataType.IsReference() && le.type.isVariable )
					{
						// Load the address of the variable into the register
						ctx->bc.InstrSHORT(asBC_LDV, le.type.stackOffset);
					}

					ctx->bc.InstrINT(asBC_JMP, afterLabel);

					// Start of the right expression
					ctx->bc.Label((short)elseLabel);

					MergeExprBytecode(ctx, &re);
					if( !re.type.dataType.IsReference() && re.type.isVariable )
					{
						// Load the address of the variable into the register
						ctx->bc.InstrSHORT(asBC_LDV, re.type.stackOffset);
					}

					ctx->bc.Label((short)afterLabel);

					// In case the options were to objects, it is necessary to dereference the pointer on
					// the stack so it will point to the actual object, instead of the variable
					if( le.type.dataType.IsReference() && le.type.dataType.IsObject() && !le.type.dataType.IsObjectHandle() )
					{
						asASSERT( re.type.dataType.IsReference() && re.type.dataType.IsObject() && !re.type.dataType.IsObjectHandle() );

						ctx->bc.Instr(asBC_RDSPtr);
					}

					// The result is an lvalue
					ctx->type.isLValue = true;
					ctx->type.dataType = le.type.dataType;
					if( ctx->type.dataType.IsPrimitive() || ctx->type.dataType.IsObjectHandle() )
						ctx->type.dataType.MakeReference(true);
					else
						ctx->type.dataType.MakeReference(false);

					// It can't be a treated as a variable, since we don't know which one was used
					ctx->type.isVariable = false;
					ctx->type.isTemporary = false;

					// Must remember if the reference was to a local variable, since it must not be allowed to be returned
					ctx->type.isRefToLocal = le.type.isVariable || le.type.isRefToLocal || re.type.isVariable || re.type.isRefToLocal;
				}
				else
				{
					// Allocate temporary variable and copy the result to that one
					asCExprValue temp;
					temp = le.type;
					temp.dataType.MakeReference(false);
					temp.dataType.MakeReadOnly(false);

					// Make sure the variable isn't used in any of the expressions,
					// as it would be overwritten which may cause crashes or less visible bugs
					int l = int(reservedVariables.GetLength());
					e.bc.GetVarsUsed(reservedVariables);
					le.bc.GetVarsUsed(reservedVariables);
					re.bc.GetVarsUsed(reservedVariables);
					int offset = AllocateVariable(temp.dataType, true, false);
					reservedVariables.SetLength(l);

					temp.SetVariable(temp.dataType, offset, true);

					// TODO: copy: Use copy constructor if available. See PrepareTemporaryVariable()

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
					asCExprValue rtemp;
					rtemp = temp;
					if( rtemp.dataType.IsObjectHandle() )
						rtemp.isExplicitHandle = true;

					PrepareForAssignment(&rtemp.dataType, &le, cexpr->next, true);
					MergeExprBytecode(ctx, &le);

					if( !rtemp.dataType.IsPrimitive() )
					{
						ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
						rtemp.dataType.MakeReference(IsVariableOnHeap(offset));
					}
					asCExprValue result;
					result = rtemp;
					PerformAssignment(&result, &le.type, &ctx->bc, cexpr->next);
					if( !result.dataType.IsPrimitive() )
						ctx->bc.Instr(asBC_PopPtr); // Pop the original value (always a pointer)

					// Release the old temporary variable
					ReleaseTemporaryVariable(le.type, &ctx->bc);

					// Process any deferred arguments in the expressions as these must not survive until after the condition returns
					ProcessDeferredParams(ctx);

					ctx->bc.InstrINT(asBC_JMP, afterLabel);

					// Start of the right expression
					ctx->bc.Label((short)elseLabel);

					// Copy the result to the same temporary variable
					PrepareForAssignment(&rtemp.dataType, &re, cexpr->next, true);
					MergeExprBytecode(ctx, &re);

					if( !rtemp.dataType.IsPrimitive() )
					{
						ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
						rtemp.dataType.MakeReference(IsVariableOnHeap(offset));
					}
					result = rtemp;
					PerformAssignment(&result, &re.type, &ctx->bc, cexpr->next);
					if( !result.dataType.IsPrimitive() )
						ctx->bc.Instr(asBC_PopPtr); // Pop the original value (always a pointer)

					// Release the old temporary variable
					ReleaseTemporaryVariable(re.type, &ctx->bc);

					// Process any deferred arguments in the expressions as these must not survive until after the condition returns
					ProcessDeferredParams(ctx);

					ctx->bc.Label((short)afterLabel);

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

int asCCompiler::CompileExpression(asCScriptNode *expr, asCExprContext *ctx)
{
	asASSERT(expr->nodeType == snExpression);

	// Convert to polish post fix, i.e: a+b => ab+
	asCArray<asCScriptNode *> postfix;
	ConvertToPostFix(expr, postfix);

	// Compile the postfix formatted expression
	return CompilePostFixExpression(&postfix, ctx);
}

void asCCompiler::ConvertToPostFix(asCScriptNode *expr, asCArray<asCScriptNode *> &postfix)
{
	// The algorithm that I've implemented here is similar to
	// Djikstra's Shunting Yard algorithm, though I didn't know it at the time.
	// ref: http://en.wikipedia.org/wiki/Shunting-yard_algorithm

	// Count the nodes in order to preallocate the buffers
	int count = 0;
	asCScriptNode *node = expr->firstChild;
	while( node )
	{
		count++;
		node = node->next;
	}

	asCArray<asCScriptNode *>  stackA(count);
	asCArray<asCScriptNode *> &stackB = postfix;
	stackB.Allocate(count, false);

	node = expr->firstChild;
	while( node )
	{
		int precedence = GetPrecedence(node);

		while( stackA.GetLength() > 0 &&
			   precedence <= GetPrecedence(stackA[stackA.GetLength()-1]) )
			stackB.PushLast(stackA.PopLast());

		stackA.PushLast(node);

		node = node->next;
	}

	while( stackA.GetLength() > 0 )
		stackB.PushLast(stackA.PopLast());
}

int asCCompiler::CompilePostFixExpression(asCArray<asCScriptNode *> *postfix, asCExprContext *ctx)
{
	// Shouldn't send any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	// Set the context to a dummy type to avoid further
	// errors in case the expression fails to compile
	ctx->type.SetDummy();

	// Evaluate the operands and operators
	asCArray<asCExprContext*> free;
	asCArray<asCExprContext*> expr;
	int ret = 0;
	for( asUINT n = 0; ret == 0 && n < postfix->GetLength(); n++ )
	{
		asCScriptNode *node = (*postfix)[n];
		if( node->nodeType == snExprTerm )
		{
			asCExprContext *e = free.GetLength() ? free.PopLast() : asNEW(asCExprContext)(engine);
			expr.PushLast(e);
			e->exprNode = node;
			ret = CompileExpressionTerm(node, e);
		}
		else
		{
			asCExprContext *r = expr.PopLast();
			asCExprContext *l = expr.PopLast();

			// Now compile the operator
			asCExprContext *e = free.GetLength() ? free.PopLast() : asNEW(asCExprContext)(engine);
			ret = CompileOperator(node, l, r, e);

			expr.PushLast(e);

			// Free the operands
			l->Clear();
			free.PushLast(l);
			r->Clear();
			free.PushLast(r);
		}
	}

	if( ret == 0 )
	{
		asASSERT(expr.GetLength() == 1);

		// The final result should be moved to the output context
		MergeExprBytecodeAndType(ctx, expr[0]);
	}

	// Clean up
	for( asUINT e = 0; e < expr.GetLength(); e++ )
		asDELETE(expr[e], asCExprContext);
	for( asUINT f = 0; f < free.GetLength(); f++ )
		asDELETE(free[f], asCExprContext);

	return ret;
}

int asCCompiler::CompileAnonymousInitList(asCScriptNode *node, asCExprContext *ctx, const asCDataType &dt)
{
	asASSERT(node->nodeType == snInitList);

	// Do not allow constructing non-shared types in shared functions
	if (outFunc->IsShared() &&
		dt.GetTypeInfo() && !dt.GetTypeInfo()->IsShared())
	{
		asCString msg;
		msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, dt.GetTypeInfo()->name.AddressOf());
		Error(msg, node);
	}

	// If this is compiled from a default arg, then use the script code for the default arg
	asCScriptCode *origCode = script;
	if (ctx->origCode)
		script = ctx->origCode;

	// Allocate and initialize the temporary object
	int offset = AllocateVariable(dt, true);
	CompileInitialization(node, &ctx->bc, dt, node, offset, 0, 0);

	// Push the reference to the object on the stack
	ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
	ctx->type.SetVariable(dt, offset, true);
	ctx->type.isLValue = false;

	// If the variable is allocated on the heap we have a reference,
	// otherwise the actual object pointer is pushed on the stack.
	if (IsVariableOnHeap(offset))
		ctx->type.dataType.MakeReference(true);

	// Clear the flag for anonymous initalization list as it is no
	// longer true now that the object has been initialized.
	ctx->isAnonymousInitList = false;
	ctx->origCode = 0;

	script = origCode;

	return 0;
}

int asCCompiler::CompileExpressionTerm(asCScriptNode *node, asCExprContext *ctx)
{
	// Shouldn't send any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	// Check if this is an initialization of a temp object with an initialization list
	if (node->firstChild )
	{
		if (node->firstChild->nodeType == snDataType)
		{
			// Determine the type of the temporary object
			asCDataType dt = builder->CreateDataTypeFromNode(node->firstChild, script, outFunc->nameSpace);

			return CompileAnonymousInitList(node->lastChild, ctx, dt);
		}
		else if (node->firstChild->nodeType == snInitList)
		{
			// As the type is not yet known, the init list will be compiled at a
			// later time when the type can be determined from the destination
			ctx->SetAnonymousInitList(node->firstChild, script);
			return 0;
		}
	}

	// Set the type as a dummy by default, in case of any compiler errors
	ctx->type.SetDummy();

	// Compile the value node
	asCScriptNode *vnode = node->firstChild;
	while( vnode->nodeType != snExprValue )
		vnode = vnode->next;

	asCExprContext v(engine);
	int r = CompileExpressionValue(vnode, &v); 
	if( r < 0 ) 
		return r;

	// Compile post fix operators
	asCScriptNode *pnode = vnode->next;
	while( pnode )
	{
		r = CompileExpressionPostOp(pnode, &v); 
		if( r < 0 ) 
			return r;
		pnode = pnode->next;
	}

	// Compile pre fix operators
	pnode = vnode->prev;
	while( pnode )
	{
		r = CompileExpressionPreOp(pnode, &v); 
		if( r < 0 ) 
			return r;
		pnode = pnode->prev;
	}

	// Return the byte code and final type description
	MergeExprBytecodeAndType(ctx, &v);

	return 0;
}

// returns:
//  SL_LOCALCONST = local constant
//  SL_LOCALVAR   = local variable
//  SL_NOMATCH    = no match
asCCompiler::SYMBOLTYPE asCCompiler::SymbolLookupLocalVar(const asCString &name, asCExprContext *outResult)
{
	sVariable *v = 0;
	if (variables)
		v = variables->GetVariable(name.AddressOf());
	if (v)
	{
		if (v->isPureConstant)
		{
			outResult->type.SetConstantData(v->type, v->constantValue);
			return SL_LOCALCONST;
		}

		outResult->type.SetVariable(v->type, v->stackOffset, false);
		return SL_LOCALVAR;
	}

	return SL_NOMATCH;
}

// returns:
//  SL_CLASSPROPACCESS = class property accessor
//  SL_CLASSPROP       = class property
//  SL_CLASSMETHOD     = class method
//  SL_CLASSTYPE       = class child type
//  SL_NOMATCH         = no match
//  SL_ERROR           = error
asCCompiler::SYMBOLTYPE asCCompiler::SymbolLookupMember(const asCString &name, asCObjectType *objType, asCExprContext *outResult)
{
	// See if there are any matching property accessors
	asCExprContext access(engine);
	access.type.Set(asCDataType::CreateType(objType, false));
	access.type.dataType.MakeReference(true);
	int r = 0;
	// Indexed property access
	asCExprContext dummyArg(engine);
	r = FindPropertyAccessor(name, &access, &dummyArg, 0, 0, true);
	if (r == 0)
	{
		// Normal property access
		r = FindPropertyAccessor(name, &access, 0, 0, true);
	}
	if (r <= -3) return SL_ERROR;
	if (r != 0)
	{
		// The symbol matches getters/setters (though not necessarily a compilable match)
		MergeExprBytecodeAndType(outResult, &access);
		outResult->type.dataType.SetTypeInfo(objType);
		return SL_CLASSPROPACCESS;
	}

	// Look for matching properties
	asCDataType dt;
	dt = asCDataType::CreateType(objType, false);
	asCObjectProperty *prop = builder->GetObjectProperty(dt, name.AddressOf());
	if (prop)
	{
		outResult->type.dataType.SetTypeInfo(objType);
		return SL_CLASSPROP;
	}

	// If it is not a property, it may still be the name of a method
	asCObjectType *ot = objType;
	for (asUINT n = 0; n < ot->methods.GetLength(); n++)
	{
		asCScriptFunction *f = engine->scriptFunctions[ot->methods[n]];
		if (f->name == name &&
			(builder->module->m_accessMask & f->accessMask))
		{
			outResult->type.dataType.SetTypeInfo(objType);
			return SL_CLASSMETHOD;
		}
	}

	// If it is not a method, then it can still be a child type
	for (asUINT n = 0; n < ot->childFuncDefs.GetLength(); n++)
	{
		if (ot->childFuncDefs[n]->name == name)
		{
			outResult->type.dataType.SetTypeInfo(objType);
			return SL_CLASSTYPE;
		}
	}

	return SL_NOMATCH;
}

// The purpose of this function is to find the entity that matches the symbol name respecting the scope and visibility hierarchy
// The 'outResult' will be used to return info on what was identified, but no code will be produced by this function
// input:
//  name         = the name of the symbol to look for
//  scope        = explicit scope informed
//  objType      = used to look for symbols within object type (e.g. when compiling post op), in this case no local or global symbols will be looked up
// returns:
//  SL_NOMATCH          = no matching symbol
//  SL_LOCALCONST       = local constant
//  SL_LOCALVAR         = local variable
//  SL_THISPTR          = this pointer
//  SL_CLASSPROPACCESS  = class property accessor, lookupResult->dataType holds the object type in which the member was found
//  SL_CLASSPROP        = class property, lookupResult->dataType holds the object type in which the member was found
//  SL_CLASSMETHOD      = class method, lookupResult->dataType holds the object type in which the member was found
//  SL_CLASSTYPE        = class child type, lookupResult->dataType holds the object type in which the member was found
//  SL_GLOBALPROPACCESS = global property accessor, lookupResult->symbolNamespace holds the namespace where the symbol was identified
//  SL_GLOBALCONST      = global constant, lookupResult->symbolNamespace holds the namespace where the symbol was identified
//  SL_GLOBALVAR        = global variable, lookupResult->symbolNamespace holds the namespace where the symbol was identified
//  SL_GLOBALFUNC       = global function, lookupResult->symbolNamespace holds the namespace where the symbol was identified
//  SL_GLOBALTYPE       = type, lookupResult->dataType holds the type
//  SL_ENUMVAL          = enum value, lookupResult->dataType holds the enum type, unless ambigious. lookupResult->symbolNamespace holds the namespace where the symbol was identified
//  SL_ERROR            = error
asCCompiler::SYMBOLTYPE asCCompiler::SymbolLookup(const asCString &name, const asCString &scope, asCObjectType *objType, asCExprContext *outResult)
{
	asASSERT(outResult);

	// It is a local variable or parameter?
	// This is not accessible by default arg expressions
	if (!isCompilingDefaultArg && scope == "" && !objType )
	{
		SYMBOLTYPE r = SymbolLookupLocalVar(name, outResult);
		if (r != 0)
			return r;
	}

	// Is it a class member?
	if (scope == "" && ((objType) || (outFunc && outFunc->objectType)))
	{
		// 'this' is not accessible by default arg expressions
		if (name == THIS_TOKEN && !objType && !isCompilingDefaultArg)
		{
			asCDataType dt = asCDataType::CreateType(outFunc->objectType, outFunc->IsReadOnly());

			// The object pointer is located at stack position 0
			outResult->type.SetVariable(dt, 0, false);
			return SL_THISPTR;
		}

		// 'super' is not accessible by default arg expressions
		if (m_isConstructor && name == SUPER_TOKEN && !objType && !isCompilingDefaultArg)
		{
			// If the class is derived from another class, then super can be used to call the base' class constructor
			if (outFunc && outFunc->objectType->derivedFrom)
			{
				outResult->type.dataType.SetTypeInfo(outFunc->objectType->derivedFrom);
				return SL_CLASSMETHOD;
			}
		}

		// Look for members in the type
		// class members are only accessible in default arg expressions as post op '.' 
		if( !isCompilingDefaultArg || (isCompilingDefaultArg && objType) )
		{
			SYMBOLTYPE r = SymbolLookupMember(name, objType ? objType : outFunc->objectType, outResult);
			if (r != 0)
				return r;
		}
	}

	// Recursively search parent namespaces for global entities
	asSNameSpace *currNamespace = DetermineNameSpace("");
	while( !objType && currNamespace )
	{
		asCString currScope = scope;

		// If the scope contains ::identifier, then use the last identifier as the class name and the rest of it as the namespace
		// TODO: child funcdef: A scope can include a template type, e.g. array<ns::type>
		int n = currScope.FindLast("::");
		asCString typeName = n >= 0 ? currScope.SubString(n + 2) : currScope;
		asCString nsName = n >= 0 ? currScope.SubString(0, n) : asCString("");

		// If the scope represents a type that the current class inherits
		// from then that should be used instead of going through the namespaces
		if (nsName == "" && (outFunc && outFunc->objectType))
		{
			asCObjectType *ot = outFunc->objectType;
			while (ot)
			{
				if (ot->name == typeName)
				{
					SYMBOLTYPE r = SymbolLookupMember(name, ot, outResult);
					if (r != 0)
						return r;
				}

				ot = ot->derivedFrom;
			}
		}

		// If the scope starts with :: then search from the global scope
		if (currScope.GetLength() < 2 || currScope[0] != ':')
		{
			if (nsName != "")
			{
				if (currNamespace->name != "")
					nsName = currNamespace->name + "::" + nsName;
			}
			else
				nsName = currNamespace->name;
		}
		else
			nsName = nsName.SubString(2);

		// Get the namespace for this scope
		asSNameSpace *ns = engine->FindNameSpace(nsName.AddressOf());
		if (ns)
		{
			// Is there a type with typeName in the namespace?
			asCTypeInfo *scopeType = builder->GetType(typeName.AddressOf(), ns, 0);

			// Check if the symbol is a member of that type
			if (scopeType)
			{
				// Is it an object type?
				if (CastToObjectType(scopeType))
				{
					SYMBOLTYPE r = SymbolLookupMember(name, CastToObjectType(scopeType), outResult);
					if (r != 0)
						return r;
				}

				// Is it an enum type?
				if (CastToEnumType(scopeType))
				{
					asDWORD value = 0;
					asCDataType dt;
					if (builder->GetEnumValueFromType(CastToEnumType(scopeType), name.AddressOf(), dt, value))
					{
						// an enum value was resolved
						outResult->type.SetConstantDW(dt, value);
						outResult->symbolNamespace = ns;
						return SL_ENUMVAL;
					}
				}
			}
		}

		// Get the namespace for this scope. This may return null if the scope is an enum
		nsName = currScope;

		// If the scope starts with :: then search from the global scope
		if (currScope.GetLength() < 2 || currScope[0] != ':')
		{
			if (nsName != "")
			{
				if (currNamespace->name != "")
					nsName = currNamespace->name + "::" + nsName;
			}
			else
				nsName = currNamespace->name;
		}
		else
			nsName = nsName.SubString(2);

		ns = engine->FindNameSpace(nsName.AddressOf());

		// Is it a global property?
		if (ns)
		{
			// See if there are any matching global property accessors
			asCExprContext access(engine);
			int r = 0;
			// Indexed property access
			asCExprContext dummyArg(engine);
			r = FindPropertyAccessor(name, &access, &dummyArg, 0, ns);
			if (r == 0)
			{
				// Normal property access
				r = FindPropertyAccessor(name, &access, 0, ns);
			}
			if (r <= -3) return SL_ERROR;
			if (r != 0)
			{
				// The symbol matches getters/setters (though not necessarily a compilable match)
				MergeExprBytecodeAndType(outResult, &access);
				outResult->symbolNamespace = ns;
				return SL_GLOBALPROPACCESS;
			}

			// See if there is any matching global property
			bool isCompiled = true;
			bool isPureConstant = false;
			bool isAppProp = false;
			asQWORD constantValue = 0;
			asCGlobalProperty *prop = builder->GetGlobalProperty(name.AddressOf(), ns, &isCompiled, &isPureConstant, &constantValue, &isAppProp);
			if (prop)
			{
				// If the global property is a pure constant
				// we can allow the compiler to optimize it. Pure
				// constants are global constant variables that were
				// initialized by literal constants.
				if (isPureConstant)
				{
					outResult->type.SetConstantData(prop->type, constantValue);
					outResult->symbolNamespace = ns;
					return SL_GLOBALCONST;
				}
				else
				{
					outResult->type.Set(prop->type);
					outResult->symbolNamespace = ns;
					return SL_GLOBALVAR;
				}
			}
		}

		// Is it the name of a global function?
		if (ns)
		{
			asCArray<int> funcs;

			builder->GetFunctionDescriptions(name.AddressOf(), funcs, ns);

			if (funcs.GetLength() > 0)
			{
				// Defer the evaluation of which function until it is actually used
				// Store the namespace and name of the function for later
				outResult->type.SetUndefinedFuncHandle(engine);
				outResult->methodName = ns ? ns->name + "::" + name : name;
				outResult->symbolNamespace = ns;
				return SL_GLOBALFUNC;
			}
		}

		// Check for type names
		if (ns)
		{
			asCTypeInfo *type = builder->GetType(name.AddressOf(), ns, 0);
			if (type)
			{
				outResult->type.dataType = asCDataType::CreateType(type, false);
				return SL_GLOBALTYPE;
			}
		}

		// Is it an enum value?
		if (ns && !engine->ep.requireEnumScope)
		{
			// Look for the enum value without explicitly informing the enum type
			asDWORD value = 0;
			asCDataType dt;
			int e = builder->GetEnumValue(name.AddressOf(), dt, value, ns);
			if (e)
			{
				if (e == 2)
				{
					// Ambiguous enum value: Save the name for resolution later.
					// The ambiguity could be resolved now, but I hesitate
					// to store too much information in the context.
					outResult->enumValue = name.AddressOf();

					// We cannot set a dummy value because it will pass through
					// cleanly as an integer.
					outResult->type.SetConstantDW(asCDataType::CreatePrimitive(ttIdentifier, true), 0);
					outResult->symbolNamespace = ns;
					return SL_ENUMVAL;
				}
				else
				{
					// an enum value was resolved
					outResult->type.SetConstantDW(dt, value);
					outResult->symbolNamespace = ns;
					return SL_ENUMVAL;
				}
			}
		}

		// If the given scope starts with '::' then the search starts from global scope
		if (scope.GetLength() >= 2 && scope[0] == ':')
			break;

		// Move up to parent namespace
		currNamespace = engine->GetParentNameSpace(currNamespace);
	}

	// The name doesn't match any symbol
	return SL_NOMATCH;
}

int asCCompiler::CompileVariableAccess(const asCString &name, const asCString &scope, asCExprContext *ctx, asCScriptNode *errNode, bool isOptional, asCObjectType *objType)
{
	asCExprContext lookupResult(engine);
	SYMBOLTYPE symbolType = SymbolLookup(name, scope, objType, &lookupResult);
	if (symbolType < 0)
	{
		// Give dummy value
		ctx->type.SetDummy();

		return -1;
	}
	if (symbolType == SL_NOMATCH)
	{
		// Give dummy value
		ctx->type.SetDummy();

		if (!isOptional)
		{
			// No matching symbol
			asCString msg;
			asCString smbl;
			if (scope == "::")
				smbl = scope;
			else if (scope != "")
				smbl = scope + "::";
			smbl += name;
			msg.Format(TXT_NO_MATCHING_SYMBOL_s, smbl.AddressOf());
			Error(msg, errNode);
		}
		return -1;
	}

	// It is a local variable or parameter?
	if( symbolType == SL_LOCALCONST || symbolType == SL_LOCALVAR )
	{
		// This is not accessible by default arg expressions
		asASSERT(!isCompilingDefaultArg && scope == "" && !objType && variables);

		sVariable *v = variables->GetVariable(name.AddressOf());
		asASSERT(v);

		if( v->isPureConstant )
			ctx->type.SetConstantData(v->type, v->constantValue);
		else if( v->type.IsPrimitive() )
		{
			if( v->type.IsReference() )
			{
				// Copy the reference into the register
				ctx->bc.InstrSHORT(asBC_PshVPtr, (short)v->stackOffset);
				ctx->bc.Instr(asBC_PopRPtr);
				ctx->type.Set(v->type);
			}
			else
				ctx->type.SetVariable(v->type, v->stackOffset, false);

			// Set as lvalue unless it is a const variable
			if( !v->type.IsReadOnly() )
				ctx->type.isLValue = true;
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
				ctx->bc.Instr(asBC_RDSPtr);

			// Mark the object as safe for access unless it is a handle, as the
			// life time of the object is guaranteed throughout the scope.
			if( !v->type.IsObjectHandle() )
				ctx->type.isRefSafe = true;

			// Set as lvalue unless it is a const variable
			if (!v->type.IsReadOnly())
				ctx->type.isLValue = true;
		}

		return 0;
	}

	// Is it a class member?
	if (symbolType == SL_CLASSPROPACCESS || symbolType == SL_CLASSPROP || symbolType == SL_CLASSMETHOD || symbolType == SL_THISPTR)
	{
		// This is not accessible by default arg expressions
		asASSERT(!isCompilingDefaultArg);

		if (symbolType == SL_THISPTR)
		{
			asASSERT(name == THIS_TOKEN && !objType && scope == "");
			asCDataType dt = asCDataType::CreateType(outFunc->objectType, outFunc->IsReadOnly());

			// The object pointer is located at stack position 0
			ctx->bc.InstrSHORT(asBC_PSF, 0);
			ctx->type.SetVariable(dt, 0, false);
			ctx->type.dataType.MakeReference(true);
			ctx->type.isLValue = true;

			// The 'this' handle is always considered safe (i.e. life time guaranteed)
			ctx->type.isRefSafe = true;

			return 0;
		}

		if (symbolType == SL_CLASSPROPACCESS)
		{
			if (scope != "")
			{
				// Cannot access non-static members like this
				asCString msg;
				msg.Format(TXT_CANNOT_ACCESS_NON_STATIC_MEMBER_s, name.AddressOf());
				Error(msg, errNode);
				return -1;
			}

			// See if there are any matching property accessors
			asCExprContext access(engine);
			if (objType)
				access.type.Set(asCDataType::CreateType(objType, false));
			else
				access.type.Set(asCDataType::CreateType(outFunc->objectType, outFunc->IsReadOnly()));
			access.type.dataType.MakeReference(true);
			int r = 0;
			if (errNode->next && errNode->next->tokenType == ttOpenBracket)
			{
				// This is an index access, check if there is a property accessor that takes an index arg
				asCExprContext dummyArg(engine);
				r = FindPropertyAccessor(name, &access, &dummyArg, errNode, 0, true);
			}
			if (r == 0)
			{
				// Normal property access
				r = FindPropertyAccessor(name, &access, errNode, 0, true);
			}
			if (r < 0) return -1;

			if (access.property_get == 0 && access.property_set == 0)
			{
				// Even though the symbol was identified in SymbolLookup, it doesn't match the arguments
				asCString msg;
				if (errNode->next && errNode->next->tokenType == ttOpenBracket)
					msg.Format(TXT_PROP_ACCESS_s_DOES_NOT_EXPECT_INDEX, name.AddressOf());
				else
					msg.Format(TXT_PROP_ACCESS_s_EXPECTS_INDEX, name.AddressOf());
				Error(msg, errNode);
				return -1;
			}

			if (!objType)
			{
				// Prepare the bytecode for the member access
				// This is only done when accessing through the implicit this pointer
				ctx->bc.InstrSHORT(asBC_PSF, 0);
			}
			MergeExprBytecodeAndType(ctx, &access);

			return 0;
		}

		if (symbolType == SL_CLASSPROP)
		{
			if (scope != "")
			{
				// Cannot access non-static members like this
				asCString msg;
				msg.Format(TXT_CANNOT_ACCESS_NON_STATIC_MEMBER_s, name.AddressOf());
				Error(msg, errNode);
				return -1;
			}

			asCDataType dt;
			if (objType)
				dt = asCDataType::CreateType(objType, false);
			else
				dt = asCDataType::CreateType(outFunc->objectType, false);
			asCObjectProperty *prop = builder->GetObjectProperty(dt, name.AddressOf());
			asASSERT(prop);

			// Is the property access allowed?
			if (prop->isPrivate && prop->isInherited)
			{
				if (engine->ep.privatePropAsProtected)
				{
					// The application is allowing inherited classes to access private properties of the parent
					// class. This option is allowed to provide backwards compatibility with pre-2.30.0 versions
					// as it was how the compiler behaved earlier.
					asCString msg;
					msg.Format(TXT_ACCESSING_PRIVATE_PROP_s, name.AddressOf());
					Warning(msg, errNode);
				}
				else
				{
					asCString msg;
					msg.Format(TXT_INHERITED_PRIVATE_PROP_ACCESS_s, name.AddressOf());
					Error(msg, errNode);
				}
			}

			if (!objType)
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
			ctx->bc.InstrSHORT_DW(asBC_ADDSi, (short)prop->byteOffset, engine->GetTypeIdFromDataType(dt));

			if (prop->type.IsReference())
				ctx->bc.Instr(asBC_RDSPtr);

			// Reference to primitive must be stored in the temp register
			if (prop->type.IsPrimitive())
			{
				// TODO: runtime optimize: The ADD offset command should store the reference in the register directly
				ctx->bc.Instr(asBC_PopRPtr);
			}

			// Set the new type (keeping info about temp variable)
			ctx->type.dataType = prop->type;
			ctx->type.dataType.MakeReference(true);
			ctx->type.isVariable = false;
			ctx->type.isLValue = true;

			if (ctx->type.dataType.IsObject() && !ctx->type.dataType.IsObjectHandle())
			{
				// Objects that are members are not references
				ctx->type.dataType.MakeReference(false);

				// Objects that are members but not handles are safe as long as the parent object is safe
				if (!objType || ctx->type.isRefSafe)
					ctx->type.isRefSafe = true;
			}
			else if (ctx->type.dataType.IsObjectHandle())
			{
				// Objects accessed through handles cannot be considered safe
				// as the handle can be cleared at any time
				ctx->type.isRefSafe = false;
			}

			// If the object reference is const, the property will also be const
			ctx->type.dataType.MakeReadOnly(outFunc->IsReadOnly());

			return 0;
		}

		if (symbolType == SL_CLASSMETHOD)
		{
			if (scope != "")
			{
				// Cannot access non-static members like this
				asCString msg;
				msg.Format(TXT_CANNOT_ACCESS_NON_STATIC_MEMBER_s, name.AddressOf());
				Error(msg, errNode);
				return -1;
			}

#if AS_DEBUG
			// If it is not a property, it may still be the name of a method which can be used to create delegates
			asCObjectType *ot = outFunc->objectType;
			asCScriptFunction *func = 0;
			for (asUINT n = 0; n < ot->methods.GetLength(); n++)
			{
				asCScriptFunction *f = engine->scriptFunctions[ot->methods[n]];
				if (f->name == name &&
					(builder->module->m_accessMask & f->accessMask))
				{
					func = f;
					break;
				}
			}

			asASSERT(func);
#endif
			// An object method was found. Keep the name of the method in the expression, but
			// don't actually modify the bytecode at this point since it is not yet known what
			// the method will be used for, or even what overloaded method should be used.
			ctx->methodName = name;

			// Place the object pointer on the stack, as if the expression was this.func
			if (!objType)
			{
				// The object pointer is located at stack position 0
				// This is only done when accessing through the implicit this pointer
				ctx->bc.InstrSHORT(asBC_PSF, 0);
				ctx->type.SetVariable(asCDataType::CreateType(outFunc->objectType, false), 0, false);
				ctx->type.dataType.MakeReference(true);
				Dereference(ctx, true);
			}

			return 0;
		}
	}

	if (symbolType == SL_GLOBALCONST || symbolType == SL_GLOBALPROPACCESS || symbolType == SL_GLOBALVAR || symbolType == SL_GLOBALFUNC || symbolType == SL_ENUMVAL)
	{
		// Get the namespace from SymbolLookup
		asSNameSpace *ns = lookupResult.symbolNamespace;

		if (symbolType == SL_GLOBALPROPACCESS)
		{
			// See if there are any matching global property accessors
			asCExprContext access(engine);
			int r = 0;
			if (errNode->next && errNode->next->tokenType == ttOpenBracket)
			{
				// This is an index access, check if there is a property accessor that takes an index arg
				asCExprContext dummyArg(engine);
				r = FindPropertyAccessor(name, &access, &dummyArg, errNode, ns);
			}
			if (r == 0)
			{
				// Normal property access
				r = FindPropertyAccessor(name, &access, errNode, ns);
			}
			if (r < 0) return -1;

			if (access.property_get == 0 && access.property_set == 0)
			{
				// Even though the symbol was identified in SymbolLookup, it doesn't match the arguments
				asCString msg;
				if (errNode->next && errNode->next->tokenType == ttOpenBracket)
					msg.Format(TXT_PROP_ACCESS_s_DOES_NOT_EXPECT_INDEX, name.AddressOf());
				else
					msg.Format(TXT_PROP_ACCESS_s_EXPECTS_INDEX, name.AddressOf());
				Error(msg, errNode);
				return -1;
			}

			// Prepare the bytecode for the function call
			MergeExprBytecodeAndType(ctx, &access);

			return 0;
		}

		if (symbolType == SL_GLOBALCONST || symbolType == SL_GLOBALVAR)
		{
			bool isCompiled = true;
			bool isPureConstant = false;
			bool isAppProp = false;
			asQWORD constantValue = 0;
			asCGlobalProperty *prop = builder->GetGlobalProperty(name.AddressOf(), ns, &isCompiled, &isPureConstant, &constantValue, &isAppProp);
			asASSERT(prop);

			// Verify that the global property has been compiled already
			if (!isCompiled)
			{
				asCString str;
				str.Format(TXT_UNINITIALIZED_GLOBAL_VAR_s, prop->name.AddressOf());
				Error(str, errNode);
				return -1;
			}

			// If the global property is a pure constant
			// we can allow the compiler to optimize it. Pure
			// constants are global constant variables that were
			// initialized by literal constants.
			if (isPureConstant)
				ctx->type.SetConstantData(prop->type, constantValue);
			else
			{
				// A shared type must not access global vars, unless they
				// too are shared, e.g. application registered vars
				if (outFunc->IsShared())
				{
					if (!isAppProp)
					{
						asCString str;
						str.Format(TXT_SHARED_CANNOT_ACCESS_NON_SHARED_VAR_s, prop->name.AddressOf());
						Error(str, errNode);

						// Allow the compilation to continue to catch other problems
					}
				}

				ctx->type.Set(prop->type);
				ctx->type.isLValue = true;

				if (ctx->type.dataType.IsPrimitive())
				{
					// Load the address of the variable into the register
					ctx->bc.InstrPTR(asBC_LDG, prop->GetAddressOfValue());

					ctx->type.dataType.MakeReference(true);
				}
				else
				{
					// Push the address of the variable on the stack
					ctx->bc.InstrPTR(asBC_PGA, prop->GetAddressOfValue());

					// If the object is a value type or a non-handle variable to a reference type,
					// then we must validate the existance as it could potentially be accessed
					// before it is initialized.
					// This check is not needed for application registered properties, since they
					// are guaranteed to be valid by the application itself.
					if (!isAppProp &&
						((ctx->type.dataType.GetTypeInfo()->flags & asOBJ_VALUE) ||
							!ctx->type.dataType.IsObjectHandle()))
					{
						ctx->bc.Instr(asBC_ChkRefS);
					}

					// If the address pushed on the stack is to a value type or an object
					// handle, then mark the expression as a reference. Addresses to a reference
					// type aren't marked as references to get correct behaviour
					if ((ctx->type.dataType.GetTypeInfo()->flags & asOBJ_VALUE) ||
						ctx->type.dataType.IsObjectHandle())
					{
						ctx->type.dataType.MakeReference(true);
					}
					else
					{
						asASSERT((ctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && !ctx->type.dataType.IsObjectHandle());

						// It's necessary to dereference the pointer so the pointer on the stack will point to the actual object
						ctx->bc.Instr(asBC_RDSPtr);
					}
				}
			}

			return 0;
		}

		if (symbolType == SL_GLOBALFUNC)
		{
			asCArray<int> funcs;

			builder->GetFunctionDescriptions(name.AddressOf(), funcs, ns);
			asASSERT(funcs.GetLength() > 0);

			if (funcs.GetLength() > 0)
			{
				// Defer the evaluation of which function until it is actually used
				// Store the namespace and name of the function for later
				ctx->type.SetUndefinedFuncHandle(engine);
				ctx->methodName = ns ? ns->name + "::" + name : name;
			}

			return 0;
		}

		if (symbolType == SL_ENUMVAL)
		{
			// The enum type and namespace must be returned from SymbolLookup
			asCDataType dt = lookupResult.type.dataType;
			if (!dt.IsEnumType())
			{
				asASSERT(!engine->ep.requireEnumScope);

				// It is an ambigious enum value. The evaluation needs to be deferred for when the type is known
				ctx->enumValue = name.AddressOf();
				ctx->symbolNamespace = lookupResult.symbolNamespace;

				// We cannot set a dummy value because it will pass through
				// cleanly as an integer.
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttIdentifier, true), 0);
				return 0;
			}

			asDWORD value = 0;
			builder->GetEnumValueFromType(CastToEnumType(lookupResult.type.dataType.GetTypeInfo()), name.AddressOf(), dt, value);

			// Even if the enum type is not shared, and we're compiling a shared object,
			// the use of the values are still allowed, since they are treated as constants.

			// an enum value was resolved
			ctx->type.SetConstantDW(dt, value);
			return 0;
		}
	}

	// The result must have been identified above
	if (symbolType == SL_GLOBALTYPE || symbolType == SL_CLASSTYPE)
	{
		// Give dummy value
		ctx->type.SetDummy();

		// The symbol matches a type
		asCString msg;
		asCString smbl;
		if (scope == "::")
			smbl = scope;
		else if (scope != "")
			smbl = scope + "::";
		smbl += name;
		msg.Format(TXT_EXPR_s_IS_DATA_TYPE, smbl.AddressOf());
		Error(msg, errNode);
		return -1;
	}

	// Should not come here
	asASSERT(false);
	return 0;
}

int asCCompiler::CompileExpressionValue(asCScriptNode *node, asCExprContext *ctx)
{
	// Shouldn't receive any byte code
	asASSERT(ctx->bc.GetLastInstr() == -1);

	asCScriptNode *vnode = node->firstChild;
	ctx->exprNode = vnode;
	if( vnode->nodeType == snVariableAccess )
	{
		// Determine the scope resolution of the variable
		asCString scope = builder->GetScopeFromNode(vnode->firstChild, script, &vnode);

		// Determine the name of the variable
		asASSERT(vnode->nodeType == snIdentifier );
		asCString name(&script->code[vnode->tokenPos], vnode->tokenLength);

		return CompileVariableAccess(name, scope, ctx, node);
	}
	else if( vnode->nodeType == snConstant )
	{
		if( vnode->tokenType == ttIntConstant )
		{
			asCString value(&script->code[vnode->tokenPos], vnode->tokenLength);

			bool overflow = false;
			asQWORD val = asStringScanUInt64(value.AddressOf(), 10, 0, &overflow);

			// Is the number bigger than a 64bit word?
			if (overflow)
			{
				Error(TXT_VALUE_TOO_LARGE_FOR_TYPE, vnode);

				// Set the value to zero to avoid further warnings
				val = 0;
			}

			// Do we need 64 bits?
			// If the 31st bit is set we'll treat the value as a signed 64bit number to avoid
			// incorrect warnings about changing signs if the value is assigned to a 64bit variable
			if( val>>31 )
			{
				// Only if the value uses the last bit of a 64bit word do we consider the number unsigned
				if( val>>63 )
					ctx->type.SetConstantQW(asCDataType::CreatePrimitive(ttUInt64, true), val);
				else
					ctx->type.SetConstantQW(asCDataType::CreatePrimitive(ttInt64, true), val);
			}
			else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), asDWORD(val));
		}
		else if( vnode->tokenType == ttBitsConstant )
		{
			asCString value(&script->code[vnode->tokenPos], vnode->tokenLength);

			// Let the function determine the radix from the prefix 0x = 16, 0d = 10, 0o = 8, or 0b = 2
			bool overflow = false;
			asQWORD val = asStringScanUInt64(value.AddressOf(), 0, 0, &overflow);

			// Is the number bigger than a 64bit word?
			if (overflow)
			{
				Error(TXT_VALUE_TOO_LARGE_FOR_TYPE, vnode);

				// Set the value to zero to avoid further warnings
				val = 0;
			}

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
#ifndef AS_USE_DOUBLE_AS_FLOAT
			// Don't check this if we have double as float, because then the whole token would be scanned (i.e. no f suffix)
			asASSERT(numScanned == vnode->tokenLength - 1);
#endif
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
				if( str.GetLength() && (asBYTE)str[0] > 127 && engine->ep.scanner == 1 )
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
				if(engine->stringFactory == 0 )
				{
					// Error
					Error(TXT_STRINGS_NOT_RECOGNIZED, vnode);

					// Give dummy value
					ctx->type.SetDummy();
					return -1;
				}
				else
				{
					void *strPtr = const_cast<void*>(engine->stringFactory->GetStringConstant(str.AddressOf(), (asUINT)str.GetLength()));
					if (strPtr == 0)
					{
						// TODO: A better message is needed
						Error(TXT_NULL_POINTER_ACCESS, vnode);
						ctx->type.SetDummy();
						return -1;
					}

					// Keep the pointer in the list for clean up at exit
					usedStringConstants.PushLast(strPtr);

					// Push the pointer on the stack. The string factory already guarantees that the
					// string object is valid throughout the lifetime of the script so no need to add
					// reference count or make local copy.
					ctx->bc.InstrPTR(asBC_PGA, strPtr);
					ctx->type.Set(engine->stringType);

					// Mark the string as literal constant so the compiler knows it is allowed
					// to treat it differently than an ordinary constant string variable
					ctx->type.isConstant = true;

					// Mark the reference to the string constant as safe, so the compiler can
					// avoid making unnecessary temporary copies when passing the reference to
					// functions.
					ctx->type.isRefSafe = true;
				}
			}
		}
		else if( vnode->tokenType == ttNull )
		{
			ctx->bc.Instr(asBC_PshNull);
			ctx->type.SetNullConstant();
		}
		else
			asASSERT(false);
	}
	else if( vnode->nodeType == snFunctionCall )
	{
		// Determine the scope resolution
		asCString scope = builder->GetScopeFromNode(vnode->firstChild, script);

		return CompileFunctionCall(vnode, ctx, 0, false, scope);
	}
	else if( vnode->nodeType == snConstructCall )
	{
		return CompileConstructCall(vnode, ctx);
	}
	else if( vnode->nodeType == snAssignment )
	{
		asCExprContext e(engine);
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
		return CompileConversion(vnode, ctx);
	}
	else if( vnode->nodeType == snUndefined && vnode->tokenType == ttVoid )
	{
		// This is a void expression
		ctx->SetVoidExpression();
	}
	else if( vnode->nodeType == snFunction )
	{
		// This is an anonymous function
		// Defer the evaluation of the function until it is known where it
		// will be used, which is where the signature will be defined
		ctx->SetLambda(vnode);
	}
	else
		asASSERT(false);

	return 0;
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

			// Hexadecimal escape sequences will allow the construction of
			// invalid unicode sequences, but the string should also work as
			// a bytearray so we must support this. The code for working with
			// unicode text must be prepared to handle invalid unicode sequences
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
					str.PushLast((asBYTE)val);
				}
				else
				{
#ifndef AS_BIG_ENDIAN
					str.PushLast((asBYTE)val);
					str.PushLast((asBYTE)(val>>8));
#else
					str.PushLast((asBYTE)(val>>8));
					str.PushLast((asBYTE)val);
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
					Warning(msg, node);
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
				if( val == 0xFFFFFFFF )
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
			encodedValue[0] = (asBYTE)val;
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
	bool isMultiline = false;
	int start;
	for( start = 0; start < (int)str.GetLength(); start++ )
	{
		if( str[start] == '\n' )
		{
			isMultiline = true;

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

	// Remove the line after the last line break if it only contains whitespaces
	int end;
	for( end = (int)str.GetLength() - 1; end >= 0; end-- )
	{
		if( str[end] == '\n' )
		{
			// Don't remove the last line break
			end++;
			break;
		}

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
	if (end > start || engine->ep.heredocTrimMode != 2 )
	{
		// if heredocTrimMode == 0 the string shouldn't be trimmed
		// if heredocTrimMode == 1 the string should only be trimmed if it is multiline
		// if heredocTrimMode == 2 the string should always be trimmed
		if (engine->ep.heredocTrimMode == 2 || (isMultiline && engine->ep.heredocTrimMode == 1))
			tmp.Assign(&str[start], end - start);
		else
			tmp = str;
	}

	ProcessStringConstant(tmp, node, false);

	str = tmp;
}

int asCCompiler::CompileConversion(asCScriptNode *node, asCExprContext *ctx)
{
	asCExprContext expr(engine);
	asCDataType to;
	bool anyErrors = false;
	EImplicitConv convType;
	if( node->nodeType == snConstructCall || node->nodeType == snFunctionCall )
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
		else if (node->lastChild->firstChild &&
			node->lastChild->firstChild->nodeType == snNamedArgument)
		{
			Error(TXT_INVALID_USE_OF_NAMED_ARGS, node->lastChild);
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
		to = builder->CreateDataTypeFromNode(node->firstChild, script, outFunc->nameSpace);
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

		// Determine the requested type
		to = builder->CreateDataTypeFromNode(node->firstChild, script, outFunc->nameSpace);

		// If the type support object handles, then use it
		if( to.SupportHandles() )
		{
			to.MakeHandle(true);
			if( expr.type.dataType.IsObjectConst() )
				to.MakeHandleToConst(true);
		}
		else if( !to.IsObjectHandle() )
		{
			// The cast<type> operator can only be used for reference casts
			Error(TXT_ILLEGAL_TARGET_TYPE_FOR_REF_CAST, node->firstChild);
			anyErrors = true;
		}
	}

	// Do not allow casting to non shared type if we're compiling a shared method
	if( outFunc->IsShared() &&
		to.GetTypeInfo() && !to.GetTypeInfo()->IsShared() )
	{
		asCString msg;
		msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, to.GetTypeInfo()->name.AddressOf());
		Error(msg, node);
		anyErrors = true;
	}

	if( anyErrors )
	{
		// Assume that the error can be fixed and allow the compilation to continue
		ctx->type.Set(to);
		return -1;
	}

	if( ProcessPropertyGetAccessor(&expr, node) < 0 )
		return -1;

	// Don't allow any operators on expressions that take address of class method
	if( expr.IsClassMethod() )
	{
		Error(TXT_INVALID_OP_ON_METHOD, node);
		return -1;
	}

	// We don't want a reference for conversion casts
	if( convType == asIC_EXPLICIT_VAL_CAST && expr.type.dataType.IsReference() )
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
		return 0;
	}

	if( to.IsEqualExceptRefAndConst(expr.type.dataType) && to.IsPrimitive() )
	{
		MergeExprBytecode(ctx, &expr);
		ctx->type = expr.type;
		ctx->type.dataType.MakeReadOnly(true);
		return 0;
	}

	// The implicit conversion already does most of the conversions permitted,
	// here we'll only treat those conversions that require an explicit cast.

	bool conversionOK = false;
	if( !expr.type.isConstant && expr.type.dataType != asCDataType::CreatePrimitive(ttVoid, false) )
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
		return 0;

	// Conversion not available
	ctx->type.SetDummy();

	asCString strTo, strFrom;

	strTo = to.Format(outFunc->nameSpace);
	strFrom = expr.type.dataType.Format(outFunc->nameSpace);

	asCString msg;
	msg.Format(TXT_NO_CONVERSION_s_TO_s, strFrom.AddressOf(), strTo.AddressOf());

	Error(msg, node);
	return -1;
}

void asCCompiler::AfterFunctionCall(int funcID, asCArray<asCExprContext*> &args, asCExprContext *ctx, bool deferAll)
{
	// deferAll is set to true if for example the function returns a reference, since in
	// this case the function might be returning a reference to one of the arguments.

	asCScriptFunction *descr = builder->GetFunctionDescription(funcID);

	// Parameters that are sent by reference should be assigned
	// to the evaluated expression if it is an lvalue

	// Evaluate the arguments from last to first
	int n = (int)descr->parameterTypes.GetLength() - 1;
	for( ; n >= 0; n-- )
	{
		// All &out arguments must be deferred, except if the argument is clean, in which case the actual reference was passed in to the function
		// If deferAll is set all objects passed by reference or handle must be deferred
		if( (descr->parameterTypes[n].IsReference() && (descr->inOutFlags[n] & asTM_OUTREF) && !args[n]->isCleanArg) ||
			(descr->parameterTypes[n].IsObject() && deferAll && (descr->parameterTypes[n].IsReference() || descr->parameterTypes[n].IsObjectHandle())) )
		{
			asASSERT( !(descr->parameterTypes[n].IsReference() && (descr->inOutFlags[n] == asTM_OUTREF) && !args[n]->isCleanArg) || args[n]->origExpr );

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

void asCCompiler::ProcessDeferredParams(asCExprContext *ctx)
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
			asCExprContext *expr = outParam.origExpr;
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
				asCExprContext rctx(engine);
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

				asCExprContext o(engine);
				DoAssignment(&o, expr, &rctx, outParam.argNode, outParam.argNode, ttAssignment, outParam.argNode);

				if( !o.type.dataType.IsPrimitive() ) o.bc.Instr(asBC_PopPtr);

				// The assignment may itself have resulted in a new temporary variable, e.g. if
				// the opAssign returns a non-reference. We must release this temporary variable
				// since it won't be used
				ReleaseTemporaryVariable(o.type, &o.bc);

				MergeExprBytecode(ctx, &o);
			}
			else
			{
				// We must still evaluate the expression
				MergeExprBytecode(ctx, expr);
				if( !expr->IsVoidExpression() && (!expr->type.isConstant || expr->type.IsNullConstant()) )
					ctx->bc.Instr(asBC_PopPtr);

				// Give an error, except if the argument is void, null or 0 which indicate the argument is explicitly to be ignored
				if( !expr->IsVoidExpression() && !expr->type.IsNullConstant() &&
					!(expr->type.isConstant && expr->type.dataType.IsPrimitive() && expr->type.GetConstantData() == 0) )
					Error(TXT_ARG_NOT_LVALUE, outParam.argNode);

				ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
			}

			ReleaseTemporaryVariable(expr->type, &ctx->bc);

			// Delete the original expression context
			asDELETE(expr, asCExprContext);
		}
		else // &inout
		{
			if( outParam.argType.isTemporary )
				ReleaseTemporaryVariable(outParam.argType, &ctx->bc);
			else if( !outParam.argType.isVariable )
			{
				if( outParam.argType.dataType.IsObject() &&
					((outParam.argType.dataType.GetBehaviour()->addref &&
					  outParam.argType.dataType.GetBehaviour()->release) ||
					 (outParam.argType.dataType.GetTypeInfo()->flags & asOBJ_NOCOUNT)) )
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


int asCCompiler::CompileConstructCall(asCScriptNode *node, asCExprContext *ctx)
{
	// The first node is a datatype node
	asCString name;
	asCExprValue tempObj;
	bool onHeap = true;
	asCArray<int> funcs;
	bool error = false;

	// It is possible that the name is really a constructor
	asCDataType dt;
	dt = builder->CreateDataTypeFromNode(node->firstChild, script, outFunc->nameSpace, false, outFunc->objectType);
	if( dt.IsPrimitive() )
	{
		// This is a cast to a primitive type
		return CompileConversion(node, ctx);
	}

	if( dt.GetTypeInfo() && (dt.GetTypeInfo()->flags & asOBJ_IMPLICIT_HANDLE) )
	{
		// Types declared as implicit handle must not attempt to construct a handle
		dt.MakeHandle(false);
	}

	// Don't accept syntax like object@(expr)
	if( dt.IsObjectHandle() )
	{
		asCString str;
		str.Format(TXT_CANT_CONSTRUCT_s_USE_REF_CAST, dt.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
		ctx->type.SetDummy();
		return -1;
	}

	// Make sure the desired type can actually be instantiated
	// Delegates are allowed to be created through construct calls,
	// even though they cannot be instantiated as variables
	if( !dt.CanBeInstantiated() && !dt.IsFuncdef() )
	{
		asCString str;
		if( dt.IsAbstractClass() )
			str.Format(TXT_ABSTRACT_CLASS_s_CANNOT_BE_INSTANTIATED, dt.Format(outFunc->nameSpace).AddressOf());
		else if( dt.IsInterface() )
			str.Format(TXT_INTERFACE_s_CANNOT_BE_INSTANTIATED, dt.Format(outFunc->nameSpace).AddressOf());
		else
			// TODO: Improve error message to explain why
			str.Format(TXT_DATA_TYPE_CANT_BE_s, dt.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
		ctx->type.SetDummy();
		return -1;
	}

	// Do not allow constructing non-shared types in shared functions
	if( outFunc->IsShared() &&
		dt.GetTypeInfo() && !dt.GetTypeInfo()->IsShared() )
	{
		asCString msg;
		msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, dt.GetTypeInfo()->name.AddressOf());
		Error(msg, node);
		return -1;
	}

	// Compile the arguments
	asCArray<asCExprContext *> args;
	asCArray<asSNamedArgument> namedArgs;
	asCArray<asCExprValue> temporaryVariables;
	if( CompileArgumentList(node->lastChild, args, namedArgs) >= 0 )
	{
		// Check for a value cast behaviour
		if( args.GetLength() == 1 )
		{
			asCExprContext conv(engine);
			conv.Copy(args[0]);
			asUINT cost = ImplicitConversion(&conv, dt, node->lastChild, asIC_EXPLICIT_VAL_CAST, false);

			// Clean the property_arg in the temporary copy so 
			// it isn't deleted when conv goes out of scope
			conv.property_arg = 0;

			// Don't use this if the cost is 0 because it would mean that nothing
			// is done and the script wants a new value to be constructed
			if( conv.type.dataType.IsEqualExceptRef(dt) && cost > 0 )
			{
				// Make sure the result is a reference, just as if to a local variable
				if( !dt.IsFuncdef() )
					dt.MakeReference(true);

				// Make sure any property accessor is already evaluated
				if( ProcessPropertyGetAccessor(args[0], args[0]->exprNode) < 0 )
					return -1;

				ImplicitConversion(args[0], dt, node->lastChild, asIC_EXPLICIT_VAL_CAST);

				ctx->bc.AddCode(&args[0]->bc);
				ctx->type = args[0]->type;

				asDELETE(args[0], asCExprContext);

				return 0;
			}
		}

		// Check for possible constructor/factory
		name = dt.Format(outFunc->nameSpace);

		asSTypeBehaviour *beh = dt.GetBehaviour();

		if( !(dt.GetTypeInfo()->flags & asOBJ_REF) && !dt.IsFuncdef() )
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
		else if( beh )
			funcs = beh->factories;

		// Special case: Allow calling func(void) with a void expression.
		if( args.GetLength() == 1 && args[0]->type.dataType == asCDataType::CreatePrimitive(ttVoid, false) )
		{
			// Evaluate the expression before the function call
			MergeExprBytecode(ctx, args[0]);
			asDELETE(args[0], asCExprContext);
			args.SetLength(0);
		}

		// Special case: If this is an object constructor and there are no arguments use the default constructor.
		// If none has been registered, just allocate the variable and push it on the stack.
		if( args.GetLength() == 0 )
		{
			beh = tempObj.dataType.GetBehaviour();
			if( beh && beh->construct == 0 && !(dt.GetTypeInfo()->flags & asOBJ_REF) )
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
				return 0;
			}
		}

		// Special case: If this is a construction of a delegate and the expression names an object method
		if( dt.IsFuncdef() && args.GetLength() == 1 && args[0]->methodName != "" )
		{
			// TODO: delegate: It is possible that the argument returns a function pointer already, in which
			//                 case no object delegate will be created, but instead a delegate for a function pointer
			//                 In theory a simple cast would be good in this case, but this is a construct call so it
			//                 is expected that a new object is created.

			dt.MakeHandle(true);
			ctx->type.Set(dt);

			// The delegate must be able to hold on to a reference to the object
			if( !args[0]->type.dataType.SupportHandles() )
			{
				Error(TXT_CANNOT_CREATE_DELEGATE_FOR_NOREF_TYPES, node);
				error = true;
			}
			else
			{
				// Filter the available object methods to find the one that matches the func def
				asCObjectType *type = CastToObjectType(args[0]->type.dataType.GetTypeInfo());
				asCScriptFunction *bestMethod = 0;
				for( asUINT n = 0; n < type->methods.GetLength(); n++ )
				{
					asCScriptFunction *func = engine->scriptFunctions[type->methods[n]];

					if( func->name != args[0]->methodName )
						continue;

					// If the expression is for a const object, then only const methods should be accepted
					if( args[0]->type.dataType.IsReadOnly() && !func->IsReadOnly() )
						continue;

					if( func->IsSignatureExceptNameAndObjectTypeEqual(CastToFuncdefType(dt.GetTypeInfo())->funcdef) )
					{
						bestMethod = func;

						// If the expression is non-const the non-const overloaded method has priority
						if( args[0]->type.dataType.IsReadOnly() == func->IsReadOnly() )
							break;
					}
				}

				if( bestMethod )
				{
					// The object pointer is already on the stack
					MergeExprBytecode(ctx, args[0]);

					// Push the function pointer as an additional argument
					ctx->bc.InstrPTR(asBC_FuncPtr, bestMethod);

					// Call the factory function for the delegate
					asCArray<int> delegateFuncs;
					builder->GetFunctionDescriptions(DELEGATE_FACTORY, delegateFuncs, engine->nameSpaces[0]);
					asASSERT(delegateFuncs.GetLength() == 1 );
					ctx->bc.Call(asBC_CALLSYS , delegateFuncs[0], 2*AS_PTR_SIZE);

					// Store the returned delegate in a temporary variable
					int returnOffset = AllocateVariable(dt, true, false);
					dt.MakeReference(true);
					ctx->type.SetVariable(dt, returnOffset, true);
					ctx->bc.InstrSHORT(asBC_STOREOBJ, (short)returnOffset);

					// Push a reference to the temporary variable on the stack
					ctx->bc.InstrSHORT(asBC_PSF, (short)returnOffset);

					// Clean up arguments
					ReleaseTemporaryVariable(args[0]->type, &ctx->bc);
				}
				else
				{
					asCString msg;
					msg.Format(TXT_NO_MATCHING_SIGNATURES_TO_s, CastToFuncdefType(dt.GetTypeInfo())->funcdef->GetDeclaration());
					Error(msg.AddressOf(), node);
					error = true;
				}
			}

			// Clean-up arg
			asDELETE(args[0], asCExprContext);
			return error ? -1 : 0;
		}

		MatchFunctions(funcs, args, node, name.AddressOf(), &namedArgs, 0, false);

		if( funcs.GetLength() != 1 )
		{
			// The error was reported by MatchFunctions()
			error = true;

			// Dummy value
			ctx->type.SetDummy();
		}
		else
		{
			// TODO: Clean up: Merge this with MakeFunctionCall

			// Add the default values for arguments not explicitly supplied
			int r = CompileDefaultAndNamedArgs(node, args, funcs[0], CastToObjectType(dt.GetTypeInfo()), &namedArgs);

			if( r == asSUCCESS )
			{
				asCByteCode objBC(engine);

				PrepareFunctionCall(funcs[0], &ctx->bc, args);

				MoveArgsToStack(funcs[0], &ctx->bc, args, false);

				if( !(dt.GetTypeInfo()->flags & asOBJ_REF) )
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

					PerformFunctionCall(funcs[0], ctx, onHeap, &args, CastToObjectType(tempObj.dataType.GetTypeInfo()));

					// Add tag that the object has been initialized
					ctx->bc.ObjInfo(tempObj.stackOffset, asOBJ_INIT);

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
			else
				error = true;
		}
	}
	else
	{
		// Failed to compile the argument list, set the result to the dummy type
		ctx->type.SetDummy();
		error = true;
	}

	// Cleanup
	for( asUINT n = 0; n < args.GetLength(); n++ )
		if( args[n] )
		{
			asDELETE(args[n], asCExprContext);
		}
	for( asUINT n = 0; n < namedArgs.GetLength(); n++ )
		if( namedArgs[n].ctx )
		{
			asDELETE(namedArgs[n].ctx, asCExprContext);
		}

	return error ? -1 : 0;
}


int asCCompiler::CompileFunctionCall(asCScriptNode *node, asCExprContext *ctx, asCObjectType *objectType, bool objIsConst, const asCString &scope)
{
	asCExprValue tempObj;
	asCArray<int> funcs;
	int localVar = -1;
	bool initializeMembers = false;
	asCExprContext funcExpr(engine);

	asCScriptNode *nm = node->lastChild->prev;
	asCString name(&script->code[nm->tokenPos], nm->tokenLength);

	// Find the matching entities
	// If objectType is set then this is a post op expression and we shouldn't look for local variables
	asCExprContext lookupResult(engine);
	SYMBOLTYPE symbolType = SymbolLookup(name, scope, objectType, &lookupResult);
	if (symbolType < 0)
		return -1;
	if (symbolType == SL_NOMATCH)
	{
		// No matching symbol
		asCString msg;
		asCString smbl;
		if (scope == "::")
			smbl = scope;
		else if (scope != "")
			smbl = scope + "::";
		smbl += name;
		msg.Format(TXT_NO_MATCHING_SYMBOL_s, smbl.AddressOf());
		Error(msg, node);
		return -1;
	}

	// Is the symbol matching a variable/property?
	if (symbolType == SL_LOCALCONST || symbolType == SL_LOCALVAR ||
		symbolType == SL_THISPTR || symbolType == SL_CLASSPROPACCESS || symbolType == SL_CLASSPROP ||
		symbolType == SL_GLOBALPROPACCESS || symbolType == SL_GLOBALCONST || symbolType == SL_GLOBALVAR || symbolType == SL_ENUMVAL)
	{
		// Variables/properties can be used as functions if they have the opCall
	
		// Compile the variable
		// TODO: Take advantage of the known symbol, so it doesn't have to be looked up again
		localVar = CompileVariableAccess(name, scope, &funcExpr, node, false, objectType);
		if( localVar < 0 )
			return -1;

		if (funcExpr.type.dataType.IsFuncdef())
		{
			funcs.PushLast(CastToFuncdefType(funcExpr.type.dataType.GetTypeInfo())->funcdef->id);
		}
		else if (funcExpr.type.dataType.IsObject())
		{
			// Keep information about temporary variables as deferred expression so it can be properly cleaned up after the call
			if (ctx->type.isTemporary)
			{
				asASSERT(objectType);

				asSDeferredParam deferred;
				deferred.origExpr = 0;
				deferred.argInOutFlags = asTM_INREF;
				deferred.argNode = 0;
				deferred.argType.SetVariable(ctx->type.dataType, ctx->type.stackOffset, true);

				ctx->deferredParams.PushLast(deferred);
			}
			if (funcExpr.property_get == 0)
				Dereference(ctx, true);

			// Add the bytecode for accessing the object on which opCall will be called
			if (ctx->type.dataType.IsObject())
			{
				// Make sure the ProcessPropertyGetAccess knows whether or not to
				// dereference the original object before calling the get accessor
				funcExpr.property_ref = ctx->type.dataType.IsReference();
			}
			MergeExprBytecodeAndType(ctx, &funcExpr);
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;
			Dereference(ctx, true);

			objectType = CastToObjectType(funcExpr.type.dataType.GetTypeInfo());

			// Get the opCall methods from the object type
			if (funcExpr.type.dataType.IsObjectHandle())
				objIsConst = funcExpr.type.dataType.IsHandleToConst();
			else
				objIsConst = funcExpr.type.dataType.IsReadOnly();

			builder->GetObjectMethodDescriptions("opCall", CastToObjectType(funcExpr.type.dataType.GetTypeInfo()), funcs, objIsConst);
		}
		else
		{
			// The variable is not a function or object with opCall
			asCString msg;
			msg.Format(TXT_NOT_A_FUNC_s_IS_TYPE_s, name.AddressOf(), lookupResult.type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(msg, node);
			return -1;
		}
	}

	// Is the symbol matching a class method?
	if (symbolType == SL_CLASSMETHOD)
	{
		// If we're compiling a constructor and the name of the function is super then
		// the constructor of the base class is being called.
		// super cannot be prefixed with a scope operator
		if (scope == "" && m_isConstructor && name == SUPER_TOKEN)
		{
			// If the class is not derived from anyone else, calling super should give an error
			if (outFunc && outFunc->objectType->derivedFrom)
				funcs = outFunc->objectType->derivedFrom->beh.constructors;

			// Must not allow calling base class' constructor multiple times
			if (continueLabels.GetLength() > 0)
			{
				// If a continue label is set we are in a loop
				Error(TXT_CANNOT_CALL_CONSTRUCTOR_IN_LOOPS, node);
			}
			else if (breakLabels.GetLength() > 0)
			{
				// TODO: inheritance: Should eventually allow constructors in switch statements
				// If a break label is set we are either in a loop or a switch statements
				Error(TXT_CANNOT_CALL_CONSTRUCTOR_IN_SWITCH, node);
			}
			else if (m_isConstructorCalled)
			{
				Error(TXT_CANNOT_CALL_CONSTRUCTOR_TWICE, node);
			}
			m_isConstructorCalled = true;

			// We need to initialize the class members, but only after all the deferred arguments have been completed
			initializeMembers = true;
		}
		else
		{
			// The scope can be used to specify the base class
			builder->GetObjectMethodDescriptions(name.AddressOf(), CastToObjectType(lookupResult.type.dataType.GetTypeInfo()), funcs, objIsConst, scope, node, script);
		}

		// If a class method is being called implicitly, then add the this pointer for the call
		if (funcs.GetLength() && !objectType && outFunc->objectType)
		{
			// Verify that the identified function is actually part of the class hierarchy
			if (!outFunc->objectType->DerivesFrom(lookupResult.type.dataType.GetTypeInfo()))
			{
				asCString msg;
				asCString mthd;
				if (scope == "")
					mthd = name;
				else if (scope == "::")
					mthd = scope + name;
				else
					mthd = scope + "::" + name;

				msg.Format(TXT_METHOD_s_NOT_PART_OF_OBJECT_s, mthd.AddressOf(), outFunc->objectType->name.AddressOf());
				Error(msg, node);
				return -1;
			}

			objectType = outFunc->objectType;

			asCDataType dt = asCDataType::CreateType(objectType, false);

			// The object pointer is located at stack position 0
			ctx->bc.InstrSHORT(asBC_PSF, 0);
			ctx->type.SetVariable(dt, 0, false);
			ctx->type.dataType.MakeReference(true);

			Dereference(ctx, true);
		}
		else if (funcs.GetLength() && !objectType && !outFunc->objectType)
		{
			// Cannot call class methods directly without the object
			asCString msg;
			msg.Format(TXT_CANNOT_ACCESS_NON_STATIC_MEMBER_s, name.AddressOf());
			Error(msg, node);
			return -1;
		}
	}

	// Is it a global function?
	if (symbolType == SL_GLOBALFUNC)
	{
		// The symbol lookup identified the namespace to use
		int n = lookupResult.methodName.FindLast("::");
		asSNameSpace *ns = engine->FindNameSpace(lookupResult.methodName.SubString(0, n).AddressOf());

		builder->GetFunctionDescriptions(name.AddressOf(), funcs, ns);
	}

	// Is it a type?
	if (symbolType == SL_CLASSTYPE || symbolType == SL_GLOBALTYPE)
	{
		bool isValid = false;
		asCDataType dt = builder->CreateDataTypeFromNode(node->firstChild, script, outFunc->nameSpace, false, outFunc->objectType, false, &isValid);
		if (isValid)
			return CompileConstructCall(node, ctx);
	}

	// Compile the arguments
	asCArray<asCExprContext *> args;
	asCArray<asSNamedArgument> namedArgs;

	bool isOK = true;
	if( CompileArgumentList(node->lastChild, args, namedArgs) >= 0 )
	{
		// Special case: Allow calling func(void) with an expression that evaluates to no datatype, but isn't exactly 'void'
		if( args.GetLength() == 1 && args[0]->type.IsVoid() && !args[0]->IsVoidExpression() )
		{
			// Evaluate the expression before the function call
			MergeExprBytecode(ctx, args[0]);
			asDELETE(args[0], asCExprContext);
			args.SetLength(0);
		}

		MatchFunctions(funcs, args, node, name.AddressOf(), &namedArgs, objectType, objIsConst, false, true, scope);

		if( funcs.GetLength() != 1 )
		{
			// The error was reported by MatchFunctions()

			// Dummy value
			ctx->type.SetDummy();
			isOK = false;
		}
		else
		{
			// Add the default values for arguments not explicitly supplied
			int r = CompileDefaultAndNamedArgs(node, args, funcs[0], objectType, &namedArgs);

			// TODO: funcdef: Do we have to make sure the handle is stored in a temporary variable, or
			//                is it enough to make sure it is in a local variable?

			// For function pointer we must guarantee that the function is safe, i.e.
			// by first storing the function pointer in a local variable (if it isn't already in one)
			if( r == asSUCCESS )
			{
				asCScriptFunction *func = builder->GetFunctionDescription(funcs[0]);
				if( func->funcType == asFUNC_FUNCDEF )
				{
					if( objectType && funcExpr.property_get <= 0 )
					{
						// Dereference the object pointer to access the member
						Dereference(ctx, true);
					}

					if( funcExpr.property_get > 0 )
					{
						if( ProcessPropertyGetAccessor(&funcExpr, node) < 0 )
							return -1;
						Dereference(&funcExpr, true);
					}
					else
					{
						Dereference(&funcExpr, true);
						ConvertToVariable(&funcExpr);
					}

					// The actual function should be called as if a global function
					objectType = 0;

					// The function call will be made directly from the local variable so the function pointer shouldn't be on the stack
					funcExpr.bc.Instr(asBC_PopPtr);

					asCExprValue tmp = ctx->type;
					MergeExprBytecodeAndType(ctx, &funcExpr);
					ReleaseTemporaryVariable(tmp, &ctx->bc);
				}

				r = MakeFunctionCall(ctx, funcs[0], objectType, args, node, false, 0, funcExpr.type.stackOffset);
				if( r < 0 )
				{
					ctx->type.SetDummy();
					isOK = false;
				}
			}
			else
				isOK = false;
		}
	}
	else
	{
		// Failed to compile the argument list, set the dummy type and continue compilation
		ctx->type.SetDummy();
		isOK = false;
	}

	// Cleanup
	for( asUINT n = 0; n < args.GetLength(); n++ )
		if( args[n] )
		{
			asDELETE(args[n], asCExprContext);
		}
	for( asUINT n = 0; n < namedArgs.GetLength(); n++ )
		if( namedArgs[n].ctx )
		{
			asDELETE(namedArgs[n].ctx, asCExprContext);
		}

	if( initializeMembers )
	{
		asASSERT( m_isConstructor );

		// Need to initialize members here, as they may use the properties of the base class
		// If there are multiple paths that call super(), then there will also be multiple
		// locations with initializations of the members. It is not possible to consolidate
		// these in one place, as the expressions for the initialization are evaluated where
		// they are compiled, which means that they may access different variables depending
		// on the scope where super() is called.
		// Members that don't have an explicit initialization expression will be initialized
		// beginning of the constructor as they are guaranteed not to use at the any
		// members of the base class.
		CompileMemberInitialization(&ctx->bc, false);
	}

	return isOK ? 0 : -1;
}

asSNameSpace *asCCompiler::DetermineNameSpace(const asCString &scope)
{
	asSNameSpace *ns;

	if( scope == "" )
	{
		// When compiling default argument expression the correct namespace is stored in the outFunc even for objects
		if( outFunc->nameSpace->name != "" || isCompilingDefaultArg )
			ns = outFunc->nameSpace;
		else if( outFunc->objectType && outFunc->objectType->nameSpace->name != "" )
			ns = outFunc->objectType->nameSpace;
		else
			ns = engine->nameSpaces[0];
	}
	else if( scope == "::" )
		ns = engine->nameSpaces[0];
	else
		ns = engine->FindNameSpace(scope.AddressOf());

	return ns;
}

int asCCompiler::CompileExpressionPreOp(asCScriptNode *node, asCExprContext *ctx)
{
	int op = node->tokenType;

	// Don't allow any prefix operators except handle on expressions that take address of class method
	if( ctx->IsClassMethod() && op != ttHandle )
	{
		Error(TXT_INVALID_OP_ON_METHOD, node);
		return -1;
	}

	// Don't allow any operators on void expressions
	if( ctx->IsVoidExpression() )
	{
		Error(TXT_VOID_CANT_BE_OPERAND, node);
		return -1;
	}

	IsVariableInitialized(&ctx->type, node);

	if( op == ttHandle )
	{
		if( ctx->methodName != "" )
		{
			// Don't allow taking the handle of a handle
			if( ctx->type.isExplicitHandle )
			{
				Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, node);
				return -1;
			}
		}
		else
		{
			// Don't allow taking handle of a handle, i.e. @@
			if( ctx->type.isExplicitHandle )
			{
				Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, node);
				return -1;
			}

			// @null is allowed even though it is implicit
			if( !ctx->type.IsNullConstant() )
			{
				// Verify that the type allow its handle to be taken
				if( !ctx->type.dataType.SupportHandles() && !ctx->type.dataType.IsObjectHandle() )
				{
					Error(TXT_OBJECT_HANDLE_NOT_SUPPORTED, node);
					return -1;
				}

				// Objects that are not local variables are not references
				// Objects allocated on the stack are also not marked as references
				if( !ctx->type.dataType.IsReference() &&
					!((ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) && !ctx->type.isVariable) &&
					!(ctx->type.isVariable && !IsVariableOnHeap(ctx->type.stackOffset)) )
				{
					Error(TXT_NOT_VALID_REFERENCE, node);
					return -1;
				}

				// Convert the expression to a handle
				if( !ctx->type.dataType.IsObjectHandle() && !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE) )
				{
					asCDataType to = ctx->type.dataType;
					to.MakeHandle(true);
					to.MakeReference(true);
					to.MakeHandleToConst(ctx->type.dataType.IsReadOnly());
					ImplicitConversion(ctx, to, node, asIC_IMPLICIT_CONV, true, false);

					asASSERT( ctx->type.dataType.IsObjectHandle() );
				}
				else if( ctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE )
				{
					// For the ASHANDLE type we'll simply set the expression as a handle
					ctx->type.dataType.MakeHandle(true);
				}
			}
		}

		// Mark the expression as an explicit handle to avoid implicit conversions to non-handle expressions
		ctx->type.isExplicitHandle = true;
	}
	else if( (op == ttMinus || op == ttPlus || op == ttBitNot || op == ttInc || op == ttDec) && ctx->type.dataType.IsObject() )
	{
		// Look for the appropriate method
		// There is no overloadable operator for unary plus
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
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// TODO: If the value isn't const, then first try to find the non const method, and if not found try to find the const method

			// Find the correct method
			bool isConst = ctx->type.dataType.IsObjectConst();
			asCArray<int> funcs;
			asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
				if( func->name == opName &&
					func->parameterTypes.GetLength() == 0 &&
					(!isConst || func->IsReadOnly()) )
				{
					funcs.PushLast(func->id);
				}
			}

			// Did we find the method?
			if( funcs.GetLength() == 1 )
			{
				asCArray<asCExprContext *> args;
				return MakeFunctionCall(ctx, funcs[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);
			}
			else if( funcs.GetLength() == 0 )
			{
				asCString str;
				str = asCString(opName) + "()";
				if( isConst )
					str += " const";
				str.Format(TXT_FUNCTION_s_NOT_FOUND, str.AddressOf());
				Error(str, node);
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
		else if( op == ttPlus )
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			ctx->type.SetDummy();
			return -1;
		}
	}
	else if( op == ttPlus || op == ttMinus )
	{
		// This is only for primitives. Objects are treated in the above block

		// Make sure the type is a math type
		if( !(ctx->type.dataType.IsIntegerType()  ||
			  ctx->type.dataType.IsUnsignedType() ||
			  ctx->type.dataType.IsFloatType()    ||
			  ctx->type.dataType.IsDoubleType()     ) )
		{
			Error(TXT_ILLEGAL_OPERATION, node);
			return -1;
		}


		if( ProcessPropertyGetAccessor(ctx, node) < 0 )
			return -1;

		asCDataType to = ctx->type.dataType;

		if( ctx->type.dataType.IsUnsignedType() )
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

		// Use an explicit conversion in case of constants to avoid unnecessary warning about change of sign
		ImplicitConversion(ctx, to, node, ctx->type.isConstant ? asIC_EXPLICIT_VAL_CAST : asIC_IMPLICIT_CONV);

		if( !ctx->type.isConstant )
		{
			ConvertToTempVariable(ctx);
			asASSERT(!ctx->type.isLValue);

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
				if (ctx->type.dataType.IsIntegerType())
				{
					if (ctx->type.dataType.GetSizeInMemoryBytes() == 4)
						ctx->type.SetConstantDW(-(int)ctx->type.GetConstantDW());
					else if (ctx->type.dataType.GetSizeInMemoryBytes() == 2)
						ctx->type.SetConstantW(-(asINT16)ctx->type.GetConstantW());
					else if (ctx->type.dataType.GetSizeInMemoryBytes() == 1)
						ctx->type.SetConstantB(-(asINT8)ctx->type.GetConstantB());
					else if (ctx->type.dataType.GetSizeInMemoryBytes() == 8)
						ctx->type.SetConstantQW(-(asINT64)ctx->type.GetConstantQW());
				}
				else if( ctx->type.dataType.IsFloatType() )
					ctx->type.SetConstantF(-ctx->type.GetConstantF());
				else if( ctx->type.dataType.IsDoubleType() )
					ctx->type.SetConstantD(-ctx->type.GetConstantD());
				else
				{
					Error(TXT_ILLEGAL_OPERATION, node);
					return -1;
				}

				return 0;
			}
		}
	}
	else if( op == ttNot )
	{
		// Allow value types to be converted to bool using 'bool opImplConv()'
		if( ctx->type.dataType.GetTypeInfo() && (ctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
			ImplicitConversion(ctx, asCDataType::CreatePrimitive(ttBool, false), node, asIC_IMPLICIT_CONV);

		if( ctx->type.dataType.IsEqualExceptRefAndConst(asCDataType::CreatePrimitive(ttBool, true)) )
		{
			if( ctx->type.isConstant )
			{
				#if AS_SIZEOF_BOOL == 1
					ctx->type.SetConstantB(ctx->type.GetConstantB() == 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
				#else
					ctx->type.SetConstantDW(ctx->type.GetConstantDW() == 0 ? VALUE_OF_BOOLEAN_TRUE : 0);
				#endif
				return 0;
			}

			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			ConvertToTempVariable(ctx);
			asASSERT(!ctx->type.isLValue);

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
		if( ProcessPropertyGetAccessor(ctx, node) < 0 )
			return -1;

		asCDataType to = ctx->type.dataType;

		if( ctx->type.dataType.IsIntegerType() )
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
				if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
					ctx->type.SetConstantB(~ctx->type.GetConstantB());
				else if (ctx->type.dataType.GetSizeInMemoryBytes() == 2)
					ctx->type.SetConstantW(~ctx->type.GetConstantW());
				else if (ctx->type.dataType.GetSizeInMemoryBytes() == 4)
					ctx->type.SetConstantDW(~ctx->type.GetConstantDW());
				else
					ctx->type.SetConstantQW(~ctx->type.GetConstantQW());
				return 0;
			}

			ConvertToTempVariable(ctx);
			asASSERT(!ctx->type.isLValue);

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
		if( !ctx->type.isLValue )
		{
			Error(TXT_NOT_LVALUE, node);
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

void asCCompiler::ConvertToReference(asCExprContext *ctx)
{
	if( ctx->type.isVariable && !ctx->type.dataType.IsReference() )
	{
		ctx->bc.InstrSHORT(asBC_LDV, ctx->type.stackOffset);
		ctx->type.dataType.MakeReference(true);
		ctx->type.SetVariable(ctx->type.dataType, ctx->type.stackOffset, ctx->type.isTemporary);
	}
}

int asCCompiler::FindPropertyAccessor(const asCString &name, asCExprContext *ctx, asCScriptNode *node, asSNameSpace *ns, bool isThisAccess)
{
	return FindPropertyAccessor(name, ctx, 0, node, ns, isThisAccess);
}

// Returns:
//   1 = a valid match was found
//   0 = no matching symbols (or feature disabled)
//  -1 = ambiguous getters or setters, i.e. multiple methods match symbol name and signature
//  -2 = mismatching type for getter and setter
//  -3 = processing error, e.g. out of memory
int asCCompiler::FindPropertyAccessor(const asCString &name, asCExprContext *ctx, asCExprContext *arg, asCScriptNode *node, asSNameSpace *ns, bool isThisAccess)
{
	// TODO: With asEP_PROPERTY_ACCESSOR_MODE == 3 this method doesn't need to validate the
	//       getter/setter as it is done at the time of declaration. Should deprecate the other options
	
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
		asASSERT( ns == 0 );

		// Don't look for property accessors in script classes if the script
		// property accessors have been disabled by the application
		if( !(ctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCRIPT_OBJECT) ||
			engine->ep.propertyAccessorMode >= 2 )
		{
			// Check if the object has any methods with the corresponding accessor name(s)
			asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *f = engine->scriptFunctions[ot->methods[n]];
				
				if( engine->ep.propertyAccessorMode == 3 && !f->IsProperty() )
					continue;
				
				// TODO: The type of the parameter should match the argument (unless the arg is a dummy)
				if( f->name == getName && (int)f->parameterTypes.GetLength() == (arg?1:0) )
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
				if( f->name == setName && (int)f->parameterTypes.GetLength() == (arg?2:1) )
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
	}
	else
	{
		asASSERT( ns != 0 );

		// Look for appropriate global functions.
		asCArray<int> funcs;
		asUINT n;
		builder->GetFunctionDescriptions(getName.AddressOf(), funcs, ns);
		for( n = 0; n < funcs.GetLength(); n++ )
		{
			asCScriptFunction *f = builder->GetFunctionDescription(funcs[n]);

			if( engine->ep.propertyAccessorMode == 3 && !f->IsProperty() )
				continue;
			
			// Ignore script functions, if the application has disabled script defined property accessors
			if( engine->ep.propertyAccessorMode == 1 && f->funcType == asFUNC_SCRIPT )
				continue;
			
			// TODO: The type of the parameter should match the argument (unless the arg is a dummy)
			if( (int)f->parameterTypes.GetLength() == (arg?1:0) )
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
		builder->GetFunctionDescriptions(setName.AddressOf(), funcs, ns);
		for( n = 0; n < funcs.GetLength(); n++ )
		{
			asCScriptFunction *f = builder->GetFunctionDescription(funcs[n]);

			if( engine->ep.propertyAccessorMode == 3 && !f->IsProperty() )
				continue;
			
			// Ignore script functions, if the application has disabled script defined property accessors
			if( engine->ep.propertyAccessorMode == 1 && f->funcType == asFUNC_SCRIPT )
				continue;
			
			// TODO: getset: If the parameter is a reference, it must not be an out reference. Should we allow inout ref?
			if( (int)f->parameterTypes.GetLength() == (arg?2:1) )
			{
				if( setId == 0 )
					setId = funcs[n];
				else
				{
					if( multipleSetFuncs.GetLength() == 0 )
						multipleSetFuncs.PushLast(setId);

					multipleSetFuncs.PushLast(funcs[n]);
				}
			}
		}
	}

	bool isConst = ctx->type.dataType.IsObjectConst();

	// Check for multiple matches
	if( multipleGetFuncs.GetLength() > 0 )
	{
		// Filter the list by constness
		FilterConst(multipleGetFuncs, !isConst);

		if( multipleGetFuncs.GetLength() > 1 )
		{
			if (node)
			{
				asCString str;
				str.Format(TXT_MULTIPLE_PROP_GET_ACCESSOR_FOR_s, name.AddressOf());
				Error(str, node);

				PrintMatchingFuncs(multipleGetFuncs, node);
			}

			return -1;
		}
		else
		{
			// The id may have changed
			getId = multipleGetFuncs[0];
		}
	}

	if( multipleSetFuncs.GetLength() > 0 )
	{
		// Filter the list by constness
		FilterConst(multipleSetFuncs, !isConst);

		if( multipleSetFuncs.GetLength() > 1 )
		{
			if (node)
			{
				asCString str;
				str.Format(TXT_MULTIPLE_PROP_SET_ACCESSOR_FOR_s, name.AddressOf());
				Error(str, node);

				PrintMatchingFuncs(multipleSetFuncs, node);
			}

			return -1;
		}
		else
		{
			// The id may have changed
			setId = multipleSetFuncs[0];
		}
	}

	// Check for type compatibility between get and set accessor
	if( getId && setId )
	{
		asCScriptFunction *getFunc = builder->GetFunctionDescription(getId);
		asCScriptFunction *setFunc = builder->GetFunctionDescription(setId);

		// It is permitted for a getter to return a handle and the setter to take a reference
		int idx = (arg?1:0);
		if( !getFunc->returnType.IsEqualExceptRefAndConst(setFunc->parameterTypes[idx]) &&
			!((getFunc->returnType.IsObjectHandle() && !setFunc->parameterTypes[idx].IsObjectHandle()) &&
			  (getFunc->returnType.GetTypeInfo() == setFunc->parameterTypes[idx].GetTypeInfo())) )
		{
			if (node)
			{
				asCString str;
				str.Format(TXT_GET_SET_ACCESSOR_TYPE_MISMATCH_FOR_s, name.AddressOf());
				Error(str, node);

				asCArray<int> funcs;
				funcs.PushLast(getId);
				funcs.PushLast(setId);

				PrintMatchingFuncs(funcs, node);
			}

			return -2;
		}
	}

	// Check if we are within one of the accessors
	int realGetId = getId;
	int realSetId = setId;
	if( outFunc->objectType && isThisAccess )
	{
		// The property accessors would be virtual functions, so we need to find the real implementation
		asCScriptFunction *getFunc = getId ? builder->GetFunctionDescription(getId) : 0;
		if( getFunc &&
			getFunc->funcType == asFUNC_VIRTUAL &&
			outFunc->objectType->DerivesFrom(getFunc->objectType) )
			realGetId = outFunc->objectType->virtualFunctionTable[getFunc->vfTableIdx]->id;
		asCScriptFunction *setFunc = setId ? builder->GetFunctionDescription(setId) : 0;
		if( setFunc &&
			setFunc->funcType == asFUNC_VIRTUAL &&
			outFunc->objectType->DerivesFrom(setFunc->objectType) )
			realSetId = outFunc->objectType->virtualFunctionTable[setFunc->vfTableIdx]->id;
	}

	// Avoid recursive call by not treating this as a property accessor call.
	// This will also allow having the real property with the same name as the accessors.
	if( (isThisAccess || outFunc->objectType == 0) &&
		((realGetId && realGetId == outFunc->id) ||
		 (realSetId && realSetId == outFunc->id)) )
	{
		getId = 0;
		setId = 0;
	}

	if( getId || setId )
	{
		// Property accessors were found, but we don't know which is to be used yet, so
		// we just prepare the bytecode for the method call, and then store the function ids
		// so that the right one can be used when we get there.
		ctx->property_get = getId;
		ctx->property_set = setId;

		bool isRefSafe = ctx->type.isRefSafe;

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
			dt = builder->GetFunctionDescription(setId)->parameterTypes[(arg?1:0)];
		else
			dt = builder->GetFunctionDescription(getId)->returnType;

		// Just change the type, the context must still maintain information
		// about previous variable offset and the indicator of temporary variable.
		int offset = ctx->type.stackOffset;
		bool isTemp = ctx->type.isTemporary;
		ctx->type.Set(dt);
		ctx->type.stackOffset = (short)offset;
		ctx->type.isTemporary = isTemp;
		ctx->exprNode = node;

		// Remember if the object is safe, so the invocation of the property
		// accessor doesn't needlessly make a safe copy of the handle
		ctx->type.isRefSafe = isRefSafe;

		// Store the argument for later use
		if( arg )
		{
			ctx->property_arg = asNEW(asCExprContext)(engine);
			if( ctx->property_arg == 0 )
			{
				// Out of memory
				return -3;
			}

			MergeExprBytecodeAndType(ctx->property_arg, arg);
		}

		return 1;
	}

	// No accessor was found
	return 0;
}

int asCCompiler::ProcessPropertySetAccessor(asCExprContext *ctx, asCExprContext *arg, asCScriptNode *node)
{
	// TODO: A lot of this code is similar to ProcessPropertyGetAccessor. Can we unify them?

	if( !ctx->property_set )
	{
		Error(TXT_PROPERTY_HAS_NO_SET_ACCESSOR, node);
		return -1;
	}

	asCScriptFunction *func = builder->GetFunctionDescription(ctx->property_set);

	// Make sure the arg match the property
	asCArray<int> funcs;
	funcs.PushLast(ctx->property_set);
	asCArray<asCExprContext *> args;
	if( ctx->property_arg )
		args.PushLast(ctx->property_arg);
	args.PushLast(arg);
	MatchFunctions(funcs, args, node, func->GetName(), 0, func->objectType, ctx->property_const);
	if( funcs.GetLength() == 0 )
	{
		// MatchFunctions already reported the error
		if( ctx->property_arg )
		{
			asDELETE(ctx->property_arg, asCExprContext);
			ctx->property_arg = 0;
		}
		return -1;
	}

	if( func->objectType )
	{
		// Setup the context with the original type so the method call gets built correctly
		ctx->type.dataType = asCDataType::CreateType(func->objectType, ctx->property_const);
		if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
		if( ctx->property_ref )	ctx->type.dataType.MakeReference(true);

		// Don't allow the call if the object is read-only and the property accessor is not const
		if( ctx->property_const && !func->IsReadOnly() )
		{
			Error(TXT_NON_CONST_METHOD_ON_CONST_OBJ, node);
			asCArray<int> funcCandidates;
			funcCandidates.PushLast(ctx->property_set);
			PrintMatchingFuncs(funcCandidates, node);
		}
	}

	// Call the accessor
	int r = MakeFunctionCall(ctx, ctx->property_set, func->objectType, args, node);

	ctx->property_get = 0;
	ctx->property_set = 0;
	if( ctx->property_arg )
	{
		asDELETE(ctx->property_arg, asCExprContext);
		ctx->property_arg = 0;
	}

	return r;
}

int asCCompiler::ProcessPropertyGetSetAccessor(asCExprContext *ctx, asCExprContext *lctx, asCExprContext *rctx, eTokenType op, asCScriptNode *errNode)
{
	// TODO: Perhaps it might be interesting to allow the definition of compound setters for better
	//       performance, e.g. set_add_prop, set_mul_prop, etc. With these it would also be possible
	//       to support value types, since it would be a single call

	// Compound assignment for indexed property accessors is not supported yet
	if( lctx->property_arg != 0 )
	{
		// Process the property to free the memory
		ProcessPropertySetAccessor(lctx, rctx, errNode);
		Error(TXT_COMPOUND_ASGN_WITH_IDX_PROP, errNode);
		return -1;
	}

	// Compound assignments require both get and set accessors
	if( lctx->property_set == 0 || lctx->property_get == 0 )
	{
		// Process the property to free the memory
		ProcessPropertySetAccessor(lctx, rctx, errNode);
		Error(TXT_COMPOUND_ASGN_REQUIRE_GET_SET, errNode);
		return -1;
	}

	// Property accessors on value types (or scoped references types) are not supported since
	// it is not possible to guarantee that the object will stay alive between the two calls
	asCScriptFunction *func = engine->scriptFunctions[lctx->property_set];
	if( func->objectType && (func->objectType->flags & (asOBJ_VALUE | asOBJ_SCOPED)) )
	{
		// Process the property to free the memory
		ProcessPropertySetAccessor(lctx, rctx, errNode);
		Error(TXT_COMPOUND_ASGN_ON_VALUE_TYPE, errNode);
		return -1;
	}

	// Translate the compound assignment to the corresponding dual operator
	switch( op )
	{
	case ttAddAssign: op = ttPlus; break;
	case ttSubAssign: op = ttMinus; break;
	case ttMulAssign: op = ttStar; break;
	case ttDivAssign: op = ttSlash; break;
	case ttModAssign: op = ttPercent; break;
	case ttPowAssign: op = ttStarStar; break;

	case ttAndAssign: op = ttAmp; break;
	case ttOrAssign:  op = ttBitOr; break;
	case ttXorAssign: op = ttBitXor; break;

	case ttShiftLeftAssign:   op = ttBitShiftLeft; break;
	case ttShiftRightAAssign: op = ttBitShiftRightArith; break;
	case ttShiftRightLAssign: op = ttBitShiftRight; break;

	default: op = ttUnrecognizedToken; break;
	}

	if( op == ttUnrecognizedToken )
	{
		// Shouldn't happen
		asASSERT(false);

		// Process the property to free the memory
		ProcessPropertySetAccessor(lctx, rctx, errNode);
		return -1;
	}

	asCExprContext before(engine);
	if( func->objectType && (func->objectType->flags & (asOBJ_REF|asOBJ_SCOPED)) == asOBJ_REF )
	{
		// Keep a reference to the object in a local variable
		before.bc.AddCode(&lctx->bc);

		asUINT len = reservedVariables.GetLength();
		rctx->bc.GetVarsUsed(reservedVariables);
		before.bc.GetVarsUsed(reservedVariables);

		asCDataType dt = asCDataType::CreateObjectHandle(func->objectType, false);
		int offset = AllocateVariable(dt, true);

		reservedVariables.SetLength(len);

		before.type.SetVariable(dt, offset, true);

		if( lctx->property_ref )
			before.bc.Instr(asBC_RDSPtr);
		before.bc.InstrSHORT(asBC_PSF, (short)offset);
		before.bc.InstrPTR(asBC_REFCPY, func->objectType);
		before.bc.Instr(asBC_PopPtr);

		if( lctx->type.isTemporary )
		{
			// Add the release of the temporary variable as a deferred expression
			asSDeferredParam deferred;
			deferred.origExpr = 0;
			deferred.argInOutFlags = asTM_INREF;
			deferred.argNode = 0;
			deferred.argType.SetVariable(ctx->type.dataType, lctx->type.stackOffset, true);
			before.deferredParams.PushLast(deferred);
		}

		// Update the left expression to use the local variable
		lctx->bc.InstrSHORT(asBC_PSF, (short)offset);
		lctx->type.stackOffset = (short)offset;
		lctx->property_ref = true;

		// Don't release the temporary variable too early
		lctx->type.isTemporary = false;

		ctx->bc.AddCode(&before.bc);
	}

	// Keep the original information on the property
	asCExprContext llctx(engine);
	llctx.type = lctx->type;
	llctx.property_arg    = lctx->property_arg;
	llctx.property_const  = lctx->property_const;
	llctx.property_get    = lctx->property_get;
	llctx.property_handle = lctx->property_handle;
	llctx.property_ref    = lctx->property_ref;
	llctx.property_set    = lctx->property_set;

	// Compile the dual operator using the get accessor
	CompileOperator(errNode, lctx, rctx, ctx, op, false);

	// If we made a local variable to hold the reference it must be reused
	if( before.type.stackOffset )
		llctx.bc.InstrSHORT(asBC_PSF, before.type.stackOffset);

	// Compile the assignment using the set accessor
	ProcessPropertySetAccessor(&llctx, ctx, errNode);

	MergeExprBytecodeAndType(ctx, &llctx);

	if( before.type.stackOffset )
		ReleaseTemporaryVariable(before.type.stackOffset, &ctx->bc);

	asASSERT( ctx->deferredParams.GetLength() == 0 );
	ctx->deferredParams = before.deferredParams;
	ProcessDeferredParams(ctx);

	return 0;
}

int asCCompiler::ProcessPropertyGetAccessor(asCExprContext *ctx, asCScriptNode *node)
{
	// If no property accessor has been prepared then don't do anything
	if( !ctx->property_get && !ctx->property_set )
		return 0;

	if( !ctx->property_get )
	{
		// Raise error on missing accessor
		Error(TXT_PROPERTY_HAS_NO_GET_ACCESSOR, node);
		return -1;
	}

	asCExprValue objType = ctx->type;
	asCScriptFunction *func = builder->GetFunctionDescription(ctx->property_get);

	// Make sure the arg match the property
	asCArray<int> funcs;
	funcs.PushLast(ctx->property_get);
	asCArray<asCExprContext *> args;
	if( ctx->property_arg )
		args.PushLast(ctx->property_arg);
	MatchFunctions(funcs, args, node, func->GetName(), 0, func->objectType, ctx->property_const);
	if( funcs.GetLength() == 0 )
	{
		// MatchFunctions already reported the error
		if( ctx->property_arg )
		{
			asDELETE(ctx->property_arg, asCExprContext);
			ctx->property_arg = 0;
		}
		return -1;
	}

	if( func->objectType )
	{
		// Setup the context with the original type so the method call gets built correctly
		ctx->type.dataType = asCDataType::CreateType(func->objectType, ctx->property_const);
		if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
		if( ctx->property_ref ) ctx->type.dataType.MakeReference(true);

		// Don't allow the call if the object is read-only and the property accessor is not const
		if( ctx->property_const && !func->IsReadOnly() )
		{
			Error(TXT_NON_CONST_METHOD_ON_CONST_OBJ, node);
			asCArray<int> funcCandidates;
			funcCandidates.PushLast(ctx->property_get);
			PrintMatchingFuncs(funcCandidates, node);
			return -1;
		}
	}

	// The explicit handle flag must be remembered
	bool isExplicitHandle = ctx->type.isExplicitHandle;

	// Call the accessor
	int r = MakeFunctionCall(ctx, ctx->property_get, func->objectType, args, node);
	if( isExplicitHandle )
		ctx->type.isExplicitHandle = true;

	// Clear the property get/set ids
	ctx->property_get = 0;
	ctx->property_set = 0;
	if( ctx->property_arg )
	{
		asDELETE(ctx->property_arg, asCExprContext);
		ctx->property_arg = 0;
	}
	
	return r;
}

int asCCompiler::CompileExpressionPostOp(asCScriptNode *node, asCExprContext *ctx)
{
	// Don't allow any postfix operators on expressions that take address of class method
	if( ctx->IsClassMethod() )
	{
		Error(TXT_INVALID_OP_ON_METHOD, node);
		return -1;
	}

	// Don't allow any operators on void expressions
	if( ctx->IsVoidExpression() )
	{
		Error(TXT_VOID_CANT_BE_OPERAND, node);
		return -1;
	}

	// Check if the variable is initialized (if it indeed is a variable)
	IsVariableInitialized(&ctx->type, node);

	int op = node->tokenType;
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
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// TODO: If the value isn't const, then first try to find the non const method, and if not found try to find the const method

			// Find the correct method
			bool isConst = ctx->type.dataType.IsObjectConst();
			asCArray<int> funcs;
			asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
			for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
				if( func->name == opName &&
					func->parameterTypes.GetLength() == 0 &&
					(!isConst || func->IsReadOnly()) )
				{
					funcs.PushLast(func->id);
				}
			}

			// Did we find the method?
			if( funcs.GetLength() == 1 )
			{
				asCArray<asCExprContext *> args;
				return MakeFunctionCall(ctx, funcs[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node);
			}
			else if( funcs.GetLength() == 0 )
			{
				asCString str;
				str = asCString(opName) + "()";
				if( isConst )
					str += " const";
				str.Format(TXT_FUNCTION_s_NOT_FOUND, str.AddressOf());
				Error(str, node);
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
		if( !ctx->type.isLValue )
		{
			Error(TXT_NOT_LVALUE, node);
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
		asASSERT(!ctx->type.isLValue);

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
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// Get the property name
			asCString name(&script->code[node->firstChild->tokenPos], node->firstChild->tokenLength);

			if( ctx->type.dataType.IsObject() )
			{
				// We need to look for get/set property accessors.
				// If found, the context stores information on the get/set accessors
				// until it is known which is to be used.
				int r = 0;
				if( node->next && node->next->tokenType == ttOpenBracket )
				{
					// The property accessor should take an index arg
					asCExprContext dummyArg(engine);
					r = FindPropertyAccessor(name, ctx, &dummyArg, node, 0);
				}
				if( r == 0 )
					r = FindPropertyAccessor(name, ctx, node, 0);
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

					// The handle may not have been an lvalue, but the dereferenced object is
					ctx->type.isLValue = true;
				}

				bool isConst = ctx->type.dataType.IsObjectConst();

				asCObjectProperty *prop = builder->GetObjectProperty(ctx->type.dataType, name.AddressOf());
				if( prop )
				{
					// Is the property access allowed?
					if( (prop->isPrivate || prop->isProtected) && (!outFunc || outFunc->objectType != ctx->type.dataType.GetTypeInfo()) )
					{
						asCString msg;
						if( prop->isPrivate )
							msg.Format(TXT_PRIVATE_PROP_ACCESS_s, name.AddressOf());
						else
							msg.Format(TXT_PROTECTED_PROP_ACCESS_s, name.AddressOf());
						Error(msg, node);
					}

					// Adjust the pointer for composite member
					// This must always be done even if the offset is 0 because the asCWriter needs the meta data in ADDSi to identify the composite property
					if( prop->compositeOffset || prop->isCompositeIndirect )
						ctx->bc.InstrSHORT_DW(asBC_ADDSi, (short)prop->compositeOffset, engine->GetTypeIdFromDataType(asCDataType::CreateType(ctx->type.dataType.GetTypeInfo(), false)));
					if (prop->isCompositeIndirect)
						ctx->bc.Instr(asBC_RDSPtr);

					// Put the offset on the stack
					// This must always be done even if the offset is 0 so the type info is stored
					ctx->bc.InstrSHORT_DW(asBC_ADDSi, (short)prop->byteOffset, engine->GetTypeIdFromDataType(asCDataType::CreateType(ctx->type.dataType.GetTypeInfo(), false)));

					if( prop->type.IsReference() )
						ctx->bc.Instr(asBC_RDSPtr);

					// Reference to primitive must be stored in the temp register
					if( prop->type.IsPrimitive() )
					{
						ctx->bc.Instr(asBC_PopRPtr);
					}

					// Keep information about temporary variables as deferred expression
					if( ctx->type.isTemporary )
					{
						// Add the release of this reference, as a deferred expression
						asSDeferredParam deferred;
						deferred.origExpr = 0;
						deferred.argInOutFlags = asTM_INREF;
						deferred.argNode = 0;
						deferred.argType.SetVariable(ctx->type.dataType, ctx->type.stackOffset, true);

						ctx->deferredParams.PushLast(deferred);
					}

					// Set the new type and make sure it is not treated as a variable anymore
					ctx->type.dataType = prop->type;
					ctx->type.dataType.MakeReference(true);
					ctx->type.isVariable = false;
					ctx->type.isTemporary = false;

					if( (ctx->type.dataType.IsObject() || ctx->type.dataType.IsFuncdef()) && !ctx->type.dataType.IsObjectHandle() )
					{
						// Objects that are members are not references
						ctx->type.dataType.MakeReference(false);

						// The object is safe (life time guaranteed) if the parent object is also safe
					}
					else if (ctx->type.dataType.IsObjectHandle())
					{
						// A object accessed through a handle cannot be considered safe,
						// as it can be cleared at any time
						ctx->type.isRefSafe = false;
					}

					ctx->type.dataType.MakeReadOnly(isConst ? true : prop->type.IsReadOnly());
				}
				else
				{
					// If the name is not a property, the compiler must check if the name matches
					// a method, which can be used for constructing delegates
					asIScriptFunction *func = 0;
					asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
					for( asUINT n = 0; n < ot->methods.GetLength(); n++ )
					{
						if( engine->scriptFunctions[ot->methods[n]]->name == name )
						{
							func = engine->scriptFunctions[ot->methods[n]];
							break;
						}
					}

					if( func )
					{
						// An object method was found. Keep the name of the method in the expression, but
						// don't actually modify the bytecode at this point since it is not yet known what
						// the method will be used for, or even what overloaded method should be used.
						ctx->methodName = name;
					}
					else
					{
						asCString str;
						str.Format(TXT_s_NOT_MEMBER_OF_s, name.AddressOf(), ctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
						Error(str, node);
						return -1;
					}
				}
			}
			else
			{
				asCString str;
				str.Format(TXT_s_NOT_MEMBER_OF_s, name.AddressOf(), ctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
				Error(str, node);
				return -1;
			}
		}
		else
		{
			// Make sure it is an object we are accessing
			if( !ctx->type.dataType.IsObject() )
			{
				asCString str;
				str.Format(TXT_ILLEGAL_OPERATION_ON_s, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
				Error(str, node);
				return -1;
			}

			// Process the get property accessor
			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;

			// Compile function call
			int r = CompileFunctionCall(node->firstChild, ctx, CastToObjectType(ctx->type.dataType.GetTypeInfo()), ctx->type.dataType.IsObjectConst());
			if( r < 0 ) return r;
		}
	}
	else if( op == ttOpenBracket )
	{
		// If the property access takes an index arg and the argument hasn't been evaluated yet,
		// then we should use that instead of processing it now. If the argument has already been
		// evaluated, then we should process the property accessor as a get access now as the new
		// index operator is on the result of that accessor.
		asCString propertyName;
		asSNameSpace *ns = 0;
		if( ((ctx->property_get && builder->GetFunctionDescription(ctx->property_get)->GetParamCount() == 1) ||
			 (ctx->property_set && builder->GetFunctionDescription(ctx->property_set)->GetParamCount() == 2)) &&
			(ctx->property_arg && ctx->property_arg->type.dataType.GetTokenType() == ttUnrecognizedToken) )
		{
			// Determine the name of the property accessor
			asCScriptFunction *func = 0;
			if( ctx->property_get )
				func = builder->GetFunctionDescription(ctx->property_get);
			else
				func = builder->GetFunctionDescription(ctx->property_set);
			propertyName = func->GetName();
			propertyName = propertyName.SubString(4);

			// Set the original type of the expression so we can re-evaluate the property accessor
			if( func->objectType )
			{
				ctx->type.dataType = asCDataType::CreateType(func->objectType, ctx->property_const);
				if( ctx->property_handle ) ctx->type.dataType.MakeHandle(true);
				if( ctx->property_ref )	ctx->type.dataType.MakeReference(true);
			}
			else
			{
				// Store the namespace where the function is declared
				// so the same function can be found later
				ctx->type.SetDummy();
				ns = func->nameSpace;
			}

			ctx->property_get = ctx->property_set = 0;
			if( ctx->property_arg )
			{
				asDELETE(ctx->property_arg, asCExprContext);
				ctx->property_arg = 0;
			}
		}
		else
		{
			if( !ctx->type.dataType.IsObject() )
			{
				asCString str;
				str.Format(TXT_OBJECT_DOESNT_SUPPORT_INDEX_OP, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
				Error(str, node);
				return -1;
			}

			if( ProcessPropertyGetAccessor(ctx, node) < 0 )
				return -1;
		}

		// Compile the expression
		bool isOK = true;
		asCArray<asCExprContext *> args;
		asCArray<asSNamedArgument> namedArgs;
		asASSERT( node->firstChild->nodeType == snArgList );
		if( CompileArgumentList(node->firstChild, args, namedArgs) >= 0 )
		{
			// Check for the existence of the opIndex method
			bool lookForProperty = true;
			if( propertyName == "" )
			{
				bool isConst = ctx->type.dataType.IsObjectConst();
				asCObjectType *objectType = CastToObjectType(ctx->type.dataType.GetTypeInfo());

				asCArray<int> funcs;
				builder->GetObjectMethodDescriptions("opIndex", objectType, funcs, isConst);
				if( funcs.GetLength() > 0 )
				{
					// Since there are opIndex methods, the compiler should not look for get/set_opIndex accessors
					lookForProperty = false;

					// Determine which of opIndex methods that match
					MatchFunctions(funcs, args, node, "opIndex", 0, objectType, isConst);
					if( funcs.GetLength() != 1 )
					{
						// The error has already been reported by MatchFunctions
						isOK = false;
					}
					else
					{
						// Add the default values for arguments not explicitly supplied
						int r = CompileDefaultAndNamedArgs(node, args, funcs[0], objectType);

						if( r < 0 )
							isOK = false;
						else if( MakeFunctionCall(ctx, funcs[0], objectType, args, node, false, 0, ctx->type.stackOffset) < 0 )
							isOK = false;
					}
				}
			}
			if( lookForProperty && isOK )
			{
				if( args.GetLength() != 1 )
				{
					// TODO: opIndex: Implement support for multiple index arguments in set_opIndex too
					Error(TXT_PROP_ACCESS_WITH_INDEX_ONE_ARG, node);
					isOK = false;
				}
				else
				{
					Dereference(ctx, true);
					asCExprContext lctx(engine);
					MergeExprBytecodeAndType(&lctx, ctx);

					// Check for accessors methods for the opIndex, either as get/set_opIndex or as get/set with the property name
					int r = FindPropertyAccessor(propertyName == "" ? "opIndex" : propertyName.AddressOf(), &lctx, args[0], node, ns);
					if (r == 0)
					{
						asCString str;
						str.Format(TXT_OBJECT_DOESNT_SUPPORT_INDEX_OP, ctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
						Error(str, node);
						isOK = false;
					}
					else if (r < 0)
						isOK = false;

					if (isOK)
						MergeExprBytecodeAndType(ctx, &lctx);
				}
			}
		}
		else
			isOK = false;

		// Cleanup
		for( asUINT n = 0; n < args.GetLength(); n++ )
			if( args[n] )
			{
				asDELETE(args[n], asCExprContext);
			}

		if( !isOK )
			return -1;
	}
	else if( op == ttOpenParanthesis )
	{
		// TODO: Most of this is already done by CompileFunctionCall(). Can we share the code?

		// Make sure the expression is a funcdef or an object that may have opCall methods
		if( !ctx->type.dataType.GetTypeInfo() || (!ctx->type.dataType.IsFuncdef() && !ctx->type.dataType.IsObject()) )
		{
			Error(TXT_EXPR_DOESNT_EVAL_TO_FUNC, node);
			return -1;
		}

		// Compile arguments
		bool isOK = true;
		asCArray<asCExprContext *> args;
		asCArray<asSNamedArgument> namedArgs;
		if( CompileArgumentList(node->lastChild, args, namedArgs) >= 0 )
		{
			// Match arguments with the funcdef
			asCArray<int> funcs;
			if( ctx->type.dataType.IsFuncdef() )
			{
				funcs.PushLast(CastToFuncdefType(ctx->type.dataType.GetTypeInfo())->funcdef->id);
				MatchFunctions(funcs, args, node, ctx->type.dataType.GetTypeInfo()->name.AddressOf(), &namedArgs);
			}
			else
			{
				bool isConst = ctx->type.dataType.IsObjectConst();

				builder->GetObjectMethodDescriptions("opCall", CastToObjectType(ctx->type.dataType.GetTypeInfo()), funcs, isConst);
				MatchFunctions(funcs, args, node, "opCall", &namedArgs, CastToObjectType(ctx->type.dataType.GetTypeInfo()), isConst);
			}

			if( funcs.GetLength() != 1 )
			{
				// The error was reported by MatchFunctions()

				// Dummy value
				ctx->type.SetDummy();
			}
			else
			{
				// Add the default values for arguments not explicitly supplied
				int r = CompileDefaultAndNamedArgs(node, args, funcs[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), &namedArgs);

				// TODO: funcdef: Do we have to make sure the handle is stored in a temporary variable, or
				//                is it enough to make sure it is in a local variable?

				// For function pointer we must guarantee that the function is safe, i.e.
				// by first storing the function pointer in a local variable (if it isn't already in one)
				if( r == asSUCCESS )
				{
					Dereference(ctx, true);
					if( ctx->type.dataType.IsFuncdef() )
					{
						if( !ctx->type.isVariable )
							ConvertToVariable(ctx);

						// Remove the reference from the stack as the asBC_CALLPTR instruction takes the variable as argument
						ctx->bc.Instr(asBC_PopPtr);
					}

					r = MakeFunctionCall(ctx, funcs[0], ctx->type.dataType.IsFuncdef() ? 0 : CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node, false, 0, ctx->type.stackOffset);
					if( r < 0 )
						isOK = false;
				}
				else
					isOK = false;
			}
		}
		else
			ctx->type.SetDummy();

		// Cleanup
		for( asUINT n = 0; n < args.GetLength(); n++ )
			if( args[n] )
			{
				asDELETE(args[n], asCExprContext);
			}
		for( asUINT n = 0; n < namedArgs.GetLength(); n++ )
			if( namedArgs[n].ctx )
			{
				asDELETE(namedArgs[n].ctx, asCExprContext);
			}
			
		if( !isOK )
			return -1;
	}

	return 0;
}

int asCCompiler::GetPrecedence(asCScriptNode *op)
{
	// x ** y
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
	if( tokenType == ttStarStar )
		return 0;

	if( tokenType == ttStar || tokenType == ttSlash || tokenType == ttPercent )
		return -1;

	if( tokenType == ttPlus || tokenType == ttMinus )
		return -2;

	if( tokenType == ttBitShiftLeft ||
		tokenType == ttBitShiftRight ||
		tokenType == ttBitShiftRightArith )
		return -3;

	if( tokenType == ttAmp )
		return -4;

	if( tokenType == ttBitXor )
		return -5;

	if( tokenType == ttBitOr )
		return -6;

	if( tokenType == ttLessThanOrEqual ||
		tokenType == ttLessThan ||
		tokenType == ttGreaterThanOrEqual ||
		tokenType == ttGreaterThan )
		return -7;

	if( tokenType == ttEqual || tokenType == ttNotEqual || tokenType == ttXor || tokenType == ttIs || tokenType == ttNotIs )
		return -8;

	if( tokenType == ttAnd )
		return -9;

	if( tokenType == ttOr )
		return -10;

	// Unknown operator
	asASSERT(false);

	return 0;
}

asUINT asCCompiler::MatchArgument(asCArray<int> &funcs, asCArray<asSOverloadCandidate> &matches, const asCExprContext *argExpr, int paramNum, bool allowObjectConstruct)
{
	matches.SetLength(0);

	for( asUINT n = 0; n < funcs.GetLength(); n++ )
	{
		asCScriptFunction *desc = builder->GetFunctionDescription(funcs[n]);

		// Does the function have arguments enough?
		if( (int)desc->parameterTypes.GetLength() <= paramNum )
			continue;

		int cost = MatchArgument(desc, argExpr, paramNum, allowObjectConstruct);
		if( cost != -1 )
			matches.PushLast(asSOverloadCandidate(funcs[n], asUINT(cost)));
	}

	return (asUINT)matches.GetLength();
}

int asCCompiler::MatchArgument(asCScriptFunction *desc, const asCExprContext *argExpr, int paramNum, bool allowObjectConstruct)
{
	// void expressions can match any out parameter, but nothing else
	if( argExpr->IsVoidExpression() )
	{
		if( desc->inOutFlags[paramNum] == asTM_OUTREF )
			return 0;
		return -1;
	}

	// Anonymous init lists can only match parameters that can be initialized with a list
	if (argExpr->IsAnonymousInitList())
	{
		if( (desc->parameterTypes[paramNum].IsReference() && (desc->inOutFlags[paramNum] & asTM_INREF) == 0) ||
			desc->parameterTypes[paramNum].GetBehaviour() == 0 ||
			desc->parameterTypes[paramNum].GetBehaviour()->listFactory == 0 )
		{
			return -1;
		}
		return 0;
	}

	// Can we make the match by implicit conversion?
	asCExprContext ti(engine);
	ti.type = argExpr->type;
	ti.methodName = argExpr->methodName;
	ti.enumValue = argExpr->enumValue;
	ti.exprNode = argExpr->exprNode;
	if( argExpr->type.dataType.IsPrimitive() )
		ti.type.dataType.MakeReference(false);

	// Don't allow the implicit conversion to make a copy in case the argument is expecting a reference to the true value
	if (desc->parameterTypes[paramNum].IsReference() && desc->inOutFlags[paramNum] == asTM_INOUTREF)
		allowObjectConstruct = false;

	int cost = ImplicitConversion(&ti, desc->parameterTypes[paramNum], 0, asIC_IMPLICIT_CONV, false, allowObjectConstruct);

	// If the function parameter is an inout-reference then it must not be possible to call the
	// function with an incorrect argument type, even though the type can normally be converted.
	if( desc->parameterTypes[paramNum].IsReference() &&
		desc->inOutFlags[paramNum] == asTM_INOUTREF &&
		desc->parameterTypes[paramNum].GetTokenType() != ttQuestion )
	{
		// Observe, that the below checks are only necessary for when unsafe references have been
		// enabled by the application. Without this the &inout reference form wouldn't be allowed
		// for these value types.

		// Don't allow a primitive to be converted to a reference of another primitive type
		if( desc->parameterTypes[paramNum].IsPrimitive() &&
			desc->parameterTypes[paramNum].GetTokenType() != argExpr->type.dataType.GetTokenType() )
		{
			asASSERT( engine->ep.allowUnsafeReferences );
			return -1;
		}

		// Don't allow an enum to be converted to a reference of another enum type
		if( desc->parameterTypes[paramNum].IsEnumType() &&
			desc->parameterTypes[paramNum].GetTypeInfo() != argExpr->type.dataType.GetTypeInfo() )
		{
			asASSERT( engine->ep.allowUnsafeReferences );
			return -1;
		}

		// Don't allow a non-handle expression to be converted to a reference to a handle
		if( desc->parameterTypes[paramNum].IsObjectHandle() &&
			!argExpr->type.dataType.IsObjectHandle() )
		{
			asASSERT( engine->ep.allowUnsafeReferences );
			return -1;
		}

		// Don't allow a value type to be converted
		if( (desc->parameterTypes[paramNum].GetTypeInfo() && (desc->parameterTypes[paramNum].GetTypeInfo()->GetFlags() & asOBJ_VALUE)) &&
			(desc->parameterTypes[paramNum].GetTypeInfo() != argExpr->type.dataType.GetTypeInfo()) )
		{
			asASSERT( engine->ep.allowUnsafeReferences );
			return -1;
		}
	}

	// How well does the argument match the function parameter?
	if( desc->parameterTypes[paramNum].IsEqualExceptRef(ti.type.dataType) )
		return cost;

	// No match is available
	return -1;
}

int asCCompiler::PrepareArgument2(asCExprContext *ctx, asCExprContext *arg, asCDataType *paramType, bool isFunction, int refType, bool isMakingCopy)
{
	// Reference parameters whose value won't be used don't evaluate the expression
	// Clean arguments (i.e. default value) will be passed in directly as there is nothing to protect
	if( paramType->IsReference() && !(refType & asTM_INREF) && !arg->isCleanArg )
	{
		// Store the original bytecode so that it can be reused when processing the deferred output parameter
		asCExprContext *orig = asNEW(asCExprContext)(engine);
		if( orig == 0 )
		{
			// Out of memory
			return -1;
		}
		MergeExprBytecodeAndType(orig, arg);
		arg->origExpr = orig;
	}

	int r = PrepareArgument(paramType, arg, arg->exprNode, isFunction, refType, isMakingCopy);
	if (r < 0)
		return r;

	// arg still holds the original expression for output parameters
	ctx->bc.AddCode(&arg->bc);

	return 0;
}

bool asCCompiler::CompileOverloadedDualOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, bool leftToRight, asCExprContext *ctx, bool isHandle, eTokenType token)
{
	DetermineSingleFunc(lctx, node);
	DetermineSingleFunc(rctx, node);

	ctx->exprNode = node;

	// What type of operator is it?
	if( token == ttUnrecognizedToken )
		token = node->tokenType;
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
		int r = CompileOverloadedDualOperator2(node, "opEquals", lctx, rctx, leftToRight, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
		if( r == 0 )
		{
			// Try again by switching the order of the operands
			r = CompileOverloadedDualOperator2(node, "opEquals", rctx, lctx, !leftToRight, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
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
		int r = CompileOverloadedDualOperator2(node, "opCmp", lctx, rctx, leftToRight, ctx, true, asCDataType::CreatePrimitive(ttInt, false));
		if( r == 0 )
		{
			// Try again by switching the order of the operands
			swappedOrder = true;
			r = CompileOverloadedDualOperator2(node, "opCmp", rctx, lctx, !leftToRight, ctx, true, asCDataType::CreatePrimitive(ttInt, false));
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
			#if AS_SIZEOF_BOOL == 1
				ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
			#else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
			#endif
			return true;
		}
	}

	// The rest of the operators are not commutative, and doesn't require specific return type
	const char *op = 0, *op_r = 0;
	switch( int(token) ) // convert to int to avoid warning in gnuc that not all values are tested
	{
	case ttPlus:               op = "opAdd";  op_r = "opAdd_r";  break;
	case ttMinus:              op = "opSub";  op_r = "opSub_r";  break;
	case ttStar:               op = "opMul";  op_r = "opMul_r";  break;
	case ttSlash:              op = "opDiv";  op_r = "opDiv_r";  break;
	case ttPercent:            op = "opMod";  op_r = "opMod_r";  break;
	case ttStarStar:           op = "opPow";  op_r = "opPow_r";  break;
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
		int r = CompileOverloadedDualOperator2(node, op, lctx, rctx, leftToRight, ctx);
		if( r == 0 )
		{
			// Try again by switching the order of the operands, and using the reversed operator
			r = CompileOverloadedDualOperator2(node, op_r, rctx, lctx, !leftToRight, ctx);
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
	if( isHandle )
	{
		// Only asOBJ_ASHANDLE types can get here
		asASSERT( lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE) );
		asASSERT( token == ttAssignment );

		if( token == ttAssignment )
			op = "opHndlAssign";
	}
	else
	{
		switch( int(token) ) // convert to int to avoid warning in gnuc that not all values are tested
		{
		case ttAssignment:        op = "opAssign";     break;
		case ttAddAssign:         op = "opAddAssign";  break;
		case ttSubAssign:         op = "opSubAssign";  break;
		case ttMulAssign:         op = "opMulAssign";  break;
		case ttDivAssign:         op = "opDivAssign";  break;
		case ttModAssign:         op = "opModAssign";  break;
		case ttPowAssign:         op = "opPowAssign";  break;
		case ttOrAssign:          op = "opOrAssign";   break;
		case ttAndAssign:         op = "opAndAssign";  break;
		case ttXorAssign:         op = "opXorAssign";  break;
		case ttShiftLeftAssign:   op = "opShlAssign";  break;
		case ttShiftRightLAssign: op = "opShrAssign";  break;
		case ttShiftRightAAssign: op = "opUShrAssign"; break;
		}
	}

	if( op )
	{
		if( builder->engine->ep.disallowValueAssignForRefType &&
			lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_REF) && !(lctx->type.dataType.GetTypeInfo()->flags & asOBJ_SCOPED) )
		{
			if( token == ttAssignment )
				Error(TXT_DISALLOW_ASSIGN_ON_REF_TYPE, node);
			else
				Error(TXT_DISALLOW_COMPOUND_ASSIGN_ON_REF_TYPE, node);

			// Set a dummy output
			ctx->type.Set(lctx->type.dataType);
			return true;
		}

		// TODO: Shouldn't accept const lvalue with the assignment operators

		// Find the matching operator method
		int r = CompileOverloadedDualOperator2(node, op, lctx, rctx, false, ctx);
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
int asCCompiler::CompileOverloadedDualOperator2(asCScriptNode *node, const char *methodName, asCExprContext *lctx, asCExprContext *rctx, bool leftToRight, asCExprContext *ctx, bool specificReturn, const asCDataType &returnType)
{
	// Find the matching method
	if( lctx->type.dataType.IsObject() &&
		(!lctx->type.isExplicitHandle ||
		 lctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE) &&
		!lctx->type.IsNullConstant() )
	{
		asUINT n;

		// Is the left value a const?
		bool isConst = lctx->type.dataType.IsObjectConst();

		asCArray<int> funcs;
		asCObjectType *ot = CastToObjectType(lctx->type.dataType.GetTypeInfo());
		asASSERT(ot);
		for( n = 0; ot && n < ot->methods.GetLength(); n++ )
		{
			asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
			asASSERT( func );
			if( func && func->name == methodName &&
				(!specificReturn || func->returnType == returnType) &&
				func->parameterTypes.GetLength() == 1 &&
				(!isConst || func->IsReadOnly()) )
			{
				// Make sure the method is accessible by the module
				if( builder->module->m_accessMask & func->accessMask )
				{
					funcs.PushLast(func->id);
				}
			}
		}

		// Which is the best matching function?
		asCArray<asSOverloadCandidate> tempFuncs;
		MatchArgument(funcs, tempFuncs, rctx, 0);

		// Find the lowest cost operator(s)
		asCArray<int> ops;
		asUINT bestCost = asUINT(-1);
		for( n = 0; n < tempFuncs.GetLength(); ++n )
		{
			asUINT cost = tempFuncs[n].cost;
			if( cost < bestCost )
			{
				ops.SetLength(0);
				bestCost = cost;
			}
			if( cost == bestCost )
				ops.PushLast(tempFuncs[n].funcId);
		}

		// If the object is not const, then we need to prioritize non-const methods
		if( !isConst )
			FilterConst(ops);

		// Did we find an operator?
		if( ops.GetLength() == 1 )
		{
			// Reserve the variables used in the right expression so the new temporary
			// variable allocated for the left operand isn't accidentally overwritten.
			int l = int(reservedVariables.GetLength());
			rctx->bc.GetVarsUsed(reservedVariables);

			// Process the lctx expression as get accessor
			if( ProcessPropertyGetAccessor(lctx, node) < 0 )
				return -1;

			reservedVariables.SetLength(l);

			asCExprContext tmpCtx(engine);
			if (leftToRight)
			{
				// Make sure lctx is in fact a variable. If it is a reference there is no
				// guarantee that the reference will stay alive throughout the evaluation of rctx
				if (!lctx->type.isVariable)
				{
					// Reserve the variables used in the right expression so the new temporary
					// variable allocated for the left operand isn't accidentally overwritten.
					l = int(reservedVariables.GetLength());
					rctx->bc.GetVarsUsed(reservedVariables);

					if (engine->ep.allowUnsafeReferences && lctx->type.dataType.IsObject() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_VALUE))
					{
						// If the application allows unsafe references, then it is not necessary to
						// make a copy of the object, just store the reference as a local variable

						// Allocate a temporary variable as reference to the type
						asCDataType dt = lctx->type.dataType;
						dt.MakeReference(true);
						int offset = AllocateVariable(dt, true, false, true);

						Dereference(lctx, true);

						// Copy the pointer to the temporary variable
						lctx->bc.InstrSHORT(asBC_PSF, (short)offset);
						if (lctx->type.dataType.IsFuncdef())
							lctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
						else
							lctx->bc.InstrPTR(asBC_REFCPY, lctx->type.dataType.GetTypeInfo());

						lctx->type.SetVariable(dt, offset, true);
					}
					else
					{
						if (lctx->type.dataType.SupportHandles())
							lctx->type.dataType.MakeHandle(true);
						PrepareTemporaryVariable(node, lctx);
					}

					reservedVariables.SetLength(l);
				}

				// Move the bytecode for the left operand to a temporary context
				// so we can later make sure this is computed first
				tmpCtx.bc.AddCode(&lctx->bc);
				tmpCtx.bc.Instr(asBC_PopPtr);

				// Add bytecode to push the object pointer computed in the left operand on the stack as the this pointer
				// This will be placed after rctx by MakeFunctionCall below
				lctx->bc.InstrWORD(asBC_PSF, lctx->type.stackOffset);

				// Implicitly dereference handle parameters sent by reference
				sVariable *v = variables->GetVariableByOffset(lctx->type.stackOffset);
				if (v && v->type.IsReference() && (!v->type.IsObject() || v->type.IsObjectHandle()))
					lctx->bc.Instr(asBC_RDSPtr);
			}
			else
			{
				// Make sure the rvalue doesn't have deferred temporary variables that are also used in the lvalue,
				// since that would cause the VM to overwrite the variable while executing the bytecode for the lvalue.
				asCArray<int> usedVars;
				lctx->bc.GetVarsUsed(usedVars);
				asUINT oldReservedVars = reservedVariables.GetLength();
				for (n = 0; n < rctx->deferredParams.GetLength(); n++)
				{
					if (rctx->deferredParams[n].argType.isTemporary &&
						usedVars.Exists(rctx->deferredParams[n].argType.stackOffset))
					{
						if (reservedVariables.GetLength() == oldReservedVars)
							reservedVariables.Concatenate(usedVars);

						// Allocate a new variable for the deferred argument
						int offset = AllocateVariableNotIn(rctx->deferredParams[n].argType.dataType, true, false, rctx);
						int oldVar = rctx->deferredParams[n].argType.stackOffset;
						rctx->deferredParams[n].argType.stackOffset = short(offset);
						rctx->bc.ExchangeVar(oldVar, offset);
						ReleaseTemporaryVariable(oldVar, 0);
					}
				}
				reservedVariables.SetLength(oldReservedVars);
			}

			// Merge the bytecode so that it forms lvalue.methodName(rvalue)
			asCArray<asCExprContext *> args;
			args.PushLast(rctx);
			MergeExprBytecode(ctx, lctx);
			ctx->type = lctx->type;
			if( MakeFunctionCall(ctx, ops[0], CastToObjectType(ctx->type.dataType.GetTypeInfo()), args, node) < 0 )
				return -1;

			// Rearrange the bytecode so the left argument is computed first
			if (leftToRight)
			{
				tmpCtx.bc.AddCode(&ctx->bc);
				ctx->bc.AddCode(&tmpCtx.bc);
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

int asCCompiler::MakeFunctionCall(asCExprContext *ctx, int funcId, asCObjectType *objectType, asCArray<asCExprContext*> &args, asCScriptNode *node, bool useVariable, int stackOffset, int funcPtrVar)
{
	if( objectType )
		Dereference(ctx, true);

	// Store the expression node for error reporting
	if( ctx->exprNode == 0 )
		ctx->exprNode = node;

	asCByteCode objBC(engine);
	objBC.AddCode(&ctx->bc);

	int r = PrepareFunctionCall(funcId, &ctx->bc, args);
	if (r < 0)
		return r;

	// Verify if any of the args variable offsets are used in the other code.
	// If they are exchange the offset for a new one
	asUINT n;
	for( n = 0; n < args.GetLength(); n++ )
	{
		if( args[n]->type.isTemporary && objBC.IsVarUsed(args[n]->type.stackOffset) )
		{
			// Release the current temporary variable
			ReleaseTemporaryVariable(args[n]->type, 0);

			asCDataType dt = args[n]->type.dataType;
			dt.MakeReference(false);

			int l = int(reservedVariables.GetLength());
			objBC.GetVarsUsed(reservedVariables);
			ctx->bc.GetVarsUsed(reservedVariables);
			int newOffset = AllocateVariable(dt, true, IsVariableOnHeap(args[n]->type.stackOffset));
			reservedVariables.SetLength(l);

			asASSERT( IsVariableOnHeap(args[n]->type.stackOffset) == IsVariableOnHeap(newOffset) );

			ctx->bc.ExchangeVar(args[n]->type.stackOffset, newOffset);
			args[n]->type.stackOffset = (short)newOffset;
			args[n]->type.isTemporary = true;
			args[n]->type.isVariable  = true;
		}
	}

	// If the function will return a value type on the stack, then we must allocate space
	// for that here and push the address on the stack as a hidden argument to the function
	asCScriptFunction *func = builder->GetFunctionDescription(funcId);
	if( func->DoesReturnOnStack() )
	{
		asASSERT(!useVariable);

		useVariable = true;
		stackOffset = AllocateVariable(func->returnType, true);
		ctx->bc.InstrSHORT(asBC_PSF, short(stackOffset));
	}

	ctx->bc.AddCode(&objBC);

	MoveArgsToStack(funcId, &ctx->bc, args, objectType ? true : false);

	PerformFunctionCall(funcId, ctx, false, &args, 0, useVariable, stackOffset, funcPtrVar);
	
	return 0;
}

int asCCompiler::CompileOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, asCExprContext *ctx, eTokenType op, bool leftToRight)
{
	// Don't allow any operators on expressions that take address of class method, but allow it on global functions
	if( (lctx->IsClassMethod()) || (rctx->IsClassMethod()) )
	{
		Error(TXT_INVALID_OP_ON_METHOD, node);
		return -1;
	}

	// Don't allow any operators on void expressions
	if( lctx->IsVoidExpression() || rctx->IsVoidExpression() )
	{
		Error(TXT_VOID_CANT_BE_OPERAND, node);
		return -1;
	}

	if( op == ttUnrecognizedToken )
		op = node->tokenType;

	IsVariableInitialized(&lctx->type, node);
	IsVariableInitialized(&rctx->type, node);

	if( lctx->type.isExplicitHandle || rctx->type.isExplicitHandle ||
		lctx->type.IsNullConstant() || rctx->type.IsNullConstant() ||
		op == ttIs || op == ttNotIs )
	{
		CompileOperatorOnHandles(node, lctx, rctx, ctx, op);
		return 0;
	}
	else
	{
		// Compile an overloaded operator for the two operands
		if( CompileOverloadedDualOperator(node, lctx, rctx, leftToRight, ctx, false, op) )
			return 0;

		// If both operands are objects, then we shouldn't continue
		if( lctx->type.dataType.IsObject() && rctx->type.dataType.IsObject() )
		{
			asCString str;
			str.Format(TXT_NO_MATCHING_OP_FOUND_FOR_TYPES_s_AND_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), rctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
			ctx->type.SetDummy();
			return -1;
		}

		// Process the property get accessors (if any)
		if( ProcessPropertyGetAccessor(lctx, node) < 0 )
			return -1;
		if( ProcessPropertyGetAccessor(rctx, node) < 0 )
			return -1;

		// Make sure we have two variables or constants
		if( lctx->type.dataType.IsReference() ) ConvertToVariableNotIn(lctx, rctx);
		if( rctx->type.dataType.IsReference() ) ConvertToVariableNotIn(rctx, lctx);

		// Make sure lctx doesn't end up with a variable used in rctx
		if( lctx->type.isTemporary && rctx->bc.IsVarUsed(lctx->type.stackOffset) )
		{
			int offset = AllocateVariableNotIn(lctx->type.dataType, true, false, rctx);
			rctx->bc.ExchangeVar(lctx->type.stackOffset, offset);
			ReleaseTemporaryVariable(offset, 0);
		}

		// Math operators
		// + - * / % ** += -= *= /= %= **=
		if( op == ttPlus     || op == ttAddAssign ||
			op == ttMinus    || op == ttSubAssign ||
			op == ttStar     || op == ttMulAssign ||
			op == ttSlash    || op == ttDivAssign ||
			op == ttPercent  || op == ttModAssign ||
			op == ttStarStar || op == ttPowAssign )
		{
			CompileMathOperator(node, lctx, rctx, ctx, op);
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
			CompileBitwiseOperator(node, lctx, rctx, ctx, op);
			return 0;
		}

		// Comparison operators
		// == != < > <= >=
		if( op == ttEqual       || op == ttNotEqual           ||
			op == ttLessThan    || op == ttLessThanOrEqual    ||
			op == ttGreaterThan || op == ttGreaterThanOrEqual )
		{
			CompileComparisonOperator(node, lctx, rctx, ctx, op);
			return 0;
		}

		// Boolean operators
		// && || ^^
		if( op == ttAnd || op == ttOr || op == ttXor )
		{
			CompileBooleanOperator(node, lctx, rctx, ctx, op);
			return 0;
		}
	}

	asASSERT(false);
	return -1;
}

void asCCompiler::ConvertToTempVariableNotIn(asCExprContext *ctx, asCExprContext *exclude)
{
	int l = int(reservedVariables.GetLength());
	if( exclude ) exclude->bc.GetVarsUsed(reservedVariables);
	ConvertToTempVariable(ctx);
	reservedVariables.SetLength(l);
}

void asCCompiler::ConvertToTempVariable(asCExprContext *ctx)
{
	// This is only used for primitive types and null handles
	asASSERT( ctx->type.dataType.IsPrimitive() || ctx->type.dataType.IsNullHandle() );

	ConvertToVariable(ctx);
	if( !ctx->type.isTemporary )
	{
		if( ctx->type.dataType.IsPrimitive() )
		{
			// Copy the variable to a temporary variable
			int offset = AllocateVariable(ctx->type.dataType, true);
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

void asCCompiler::ConvertToVariable(asCExprContext *ctx)
{
	// We should never get here while the context is still an unprocessed property accessor
	asASSERT(ctx->property_get == 0 && ctx->property_set == 0);

	int offset;
	if( !ctx->type.isVariable &&
		(ctx->type.dataType.IsObjectHandle() ||
		 (ctx->type.dataType.IsObject() && ctx->type.dataType.SupportHandles())) )
	{
		offset = AllocateVariable(ctx->type.dataType, true);
		if( ctx->type.IsNullConstant() )
		{
			if( ctx->bc.GetLastInstr() == asBC_PshNull )
				ctx->bc.Instr(asBC_PopPtr); // Pop the null constant pushed onto the stack
			ctx->bc.InstrSHORT(asBC_ClrVPtr, (short)offset);
		}
		else
		{
			Dereference(ctx, true);

			// Copy the object handle to a variable
			ctx->bc.InstrSHORT(asBC_PSF, (short)offset);
			if( ctx->type.dataType.IsFuncdef() )
				ctx->bc.InstrPTR(asBC_REFCPY, &engine->functionBehaviours);
			else
				ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());
			ctx->bc.Instr(asBC_PopPtr);
		}

		// As this is an object the reference must be placed on the stack
		ctx->bc.InstrSHORT(asBC_PSF, (short)offset);

		ReleaseTemporaryVariable(ctx->type, &ctx->bc);
		ctx->type.SetVariable(ctx->type.dataType, offset, true);
		ctx->type.dataType.MakeHandle(true);
		ctx->type.dataType.MakeReference(true);
	}
	else if( (!ctx->type.isVariable || ctx->type.dataType.IsReference()) &&
		     ctx->type.dataType.IsPrimitive() )
	{
		if( ctx->type.isConstant )
		{
			offset = AllocateVariable(ctx->type.dataType, true);
			if( ctx->type.dataType.GetSizeInMemoryBytes() == 1 )
				ctx->bc.InstrSHORT_B(asBC_SetV1, (short)offset, ctx->type.GetConstantB());
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 2 )
				ctx->bc.InstrSHORT_W(asBC_SetV2, (short)offset, ctx->type.GetConstantW());
			else if( ctx->type.dataType.GetSizeInMemoryBytes() == 4 )
				ctx->bc.InstrSHORT_DW(asBC_SetV4, (short)offset, ctx->type.GetConstantDW());
			else
				ctx->bc.InstrSHORT_QW(asBC_SetV8, (short)offset, ctx->type.GetConstantQW());

			ctx->type.SetVariable(ctx->type.dataType, offset, true);
			return;
		}
		else
		{
			asASSERT(ctx->type.dataType.IsPrimitive());
			asASSERT(ctx->type.dataType.IsReference());

			ctx->type.dataType.MakeReference(false);
			offset = AllocateVariable(ctx->type.dataType, true);

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

void asCCompiler::ConvertToVariableNotIn(asCExprContext *ctx, asCExprContext *exclude)
{
	int l = int(reservedVariables.GetLength());
	if( exclude ) exclude->bc.GetVarsUsed(reservedVariables);
	ConvertToVariable(ctx);
	reservedVariables.SetLength(l);
}

void asCCompiler::ImplicitConvObjectToBestMathType(asCExprContext *ctx, asCScriptNode *node)
{
	asCArray<int> funcs;
	asCObjectType *ot = CastToObjectType(ctx->type.dataType.GetTypeInfo());
	if( ot )
	{
		for( unsigned int n = 0; n < ot->methods.GetLength(); n++ )
		{
			// Consider only implicit casts
			asCScriptFunction *func = engine->scriptFunctions[ot->methods[n]];
			if( func->name == "opImplConv" &&
				func->returnType.IsPrimitive() &&
				func->parameterTypes.GetLength() == 0 )
				funcs.PushLast(ot->methods[n]);
		}

		// Use the one with the highest precision
		const eTokenType match[10] = {ttDouble, ttFloat, ttInt64, ttUInt64, ttInt, ttUInt, ttInt16, ttUInt16, ttInt8, ttUInt8};
		while( funcs.GetLength() > 1 )
		{
			eTokenType returnType = builder->GetFunctionDescription(funcs[0])->returnType.GetTokenType();
			int value1 = 11, value2 = 11;
			for( asUINT i = 0; i < 10; i++ )
			{
				if( returnType == match[i] )
				{
					value1 = i;
					break;
				}
			}

			for( asUINT n = 1; n < funcs.GetLength(); n++ )
			{
				returnType = builder->GetFunctionDescription(funcs[n])->returnType.GetTokenType();
				for( asUINT i = 0; i < 10; i++ )
				{
					if( returnType == match[i] )
					{
						value2 = i;
						break;
					}
				}

				if( value2 >= value1 )
				{
					// Remove this and continue searching
					funcs.RemoveIndexUnordered(n--);
				}
				else
				{
					// Remove the first, and start over
					funcs.RemoveIndexUnordered(0);
					break;
				}
			}
		}

		// Do the conversion
		if( funcs.GetLength() )
			ImplicitConvObjectToPrimitive(ctx, builder->GetFunctionDescription(funcs[0])->returnType, node, asIC_IMPLICIT_CONV);
	}
}

void asCCompiler::CompileMathOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext  *rctx, asCExprContext *ctx, eTokenType op)
{
	// TODO: If a constant is only using 32bits, then a 32bit operation is preferred

	// TODO: clean up: This initial part is identical to CompileComparisonOperator. Make a common function out of it

	// If either operand is a non-primitive then use the primitive type
	if( !lctx->type.dataType.IsPrimitive() )
	{
		int l = int(reservedVariables.GetLength());
		rctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConvObjectToBestMathType(lctx, node);
		reservedVariables.SetLength(l);
	}
	if( !rctx->type.dataType.IsPrimitive() )
	{
		int l = int(reservedVariables.GetLength());
		lctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConvObjectToBestMathType(rctx, node);
		reservedVariables.SetLength(l);
	}

	// Both types must now be primitives. Implicitly convert them so they match
	asCDataType to;
	if( lctx->type.dataType.IsDoubleType() || rctx->type.dataType.IsDoubleType() )
		to.SetTokenType(ttDouble);
	else if( lctx->type.dataType.IsFloatType() || rctx->type.dataType.IsFloatType() )
		to.SetTokenType(ttFloat);
	else if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 || rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
	{
		// Convert to int64 if both are signed or if one is non-constant and signed
		if( (lctx->type.dataType.IsIntegerType() && !lctx->type.isConstant) ||
			(rctx->type.dataType.IsIntegerType() && !rctx->type.isConstant) )
			to.SetTokenType(ttInt64);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt64);
		else
			to.SetTokenType(ttInt64);
	}
	else
	{
		// Convert to int32 if both are signed or if one is non-constant and signed
		if( (lctx->type.dataType.IsIntegerType() && !lctx->type.isConstant) ||
			(rctx->type.dataType.IsIntegerType() && !rctx->type.isConstant) )
			to.SetTokenType(ttInt);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt);
		else
			to.SetTokenType(ttInt);
	}

	// If doing an operation with double constant and float variable, the constant should be converted to float
	if( (lctx->type.isConstant && lctx->type.dataType.IsDoubleType() && !rctx->type.isConstant && rctx->type.dataType.IsFloatType()) ||
		(rctx->type.isConstant && rctx->type.dataType.IsDoubleType() && !lctx->type.isConstant && lctx->type.dataType.IsFloatType()) )
		to.SetTokenType(ttFloat);

	if( op == ttUnrecognizedToken )
		op = node->tokenType;

	// If integer division is disabled, convert to floating-point
	if( engine->ep.disableIntegerDivision &&
		(op == ttSlash || op == ttDivAssign) &&
		(to.IsIntegerType() || to.IsUnsignedType()) )
	{
		// Use double to avoid losing precision when dividing with 32bit ints
		// For 64bit ints there is unfortunately no greater type so with those
		// there is still a risk of loosing precision
		to.SetTokenType(ttDouble);
	}

	// Do the actual conversion
	int l = int(reservedVariables.GetLength());
	rctx->bc.GetVarsUsed(reservedVariables);
	lctx->bc.GetVarsUsed(reservedVariables);

	if( lctx->type.dataType.IsReference() )
		ConvertToVariable(lctx);
	if( rctx->type.dataType.IsReference() )
		ConvertToVariable(rctx);

	if( to.IsPrimitive() )
	{
		// ttStarStar allows an integer, right-hand operand and a double
		// left-hand operand.
		if( (op == ttStarStar || op == ttPowAssign) &&
			lctx->type.dataType.IsDoubleType() &&
			(rctx->type.dataType.IsIntegerType() ||
			    rctx->type.dataType.IsUnsignedType()) )
		{
			to.SetTokenType(ttInt);
			ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true);
			to.SetTokenType(ttDouble);
		}
		else
		{
			ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true);
			ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true);
		}
	}
	reservedVariables.SetLength(l);

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsIntegerType() &&
		!lctx->type.dataType.IsUnsignedType() &&
		!lctx->type.dataType.IsFloatType() &&
		!lctx->type.dataType.IsDoubleType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_MATH_TYPE, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);

		ctx->type.SetDummy();
		return;
	}

	if( !rctx->type.dataType.IsIntegerType() &&
		!rctx->type.dataType.IsUnsignedType() &&
		!rctx->type.dataType.IsFloatType() &&
		!rctx->type.dataType.IsDoubleType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_MATH_TYPE, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);

		ctx->type.SetDummy();
		return;
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

	// Verify if we are dividing with a constant zero
	if( rctx->type.isConstant &&
		(op == ttSlash   || op == ttDivAssign ||
		 op == ttPercent || op == ttModAssign) &&
		((rctx->type.dataType.GetSizeInMemoryBytes() == 4 && rctx->type.GetConstantDW() == 0) ||
		 (rctx->type.dataType.GetSizeInMemoryBytes() == 8 && rctx->type.GetConstantQW() == 0) ||
		 (rctx->type.dataType.GetSizeInMemoryBytes() == 1 && rctx->type.GetConstantB() == 0) ||
		 (rctx->type.dataType.GetSizeInMemoryBytes() == 2 && rctx->type.GetConstantW() == 0)) )
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
			op == ttModAssign || op == ttPowAssign )
		{
			// Merge the operands in the different order so that they are evaluated correctly
			MergeExprBytecode(ctx, rctx);
			MergeExprBytecode(ctx, lctx);

			// We must not process the deferred parameters yet, as
			// it may overwrite the lvalue kept in the register
		}
		else
		{
			MergeExprBytecode(ctx, lctx);
			MergeExprBytecode(ctx, rctx);

			ProcessDeferredParams(ctx);
		}

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
				else if( op == ttStarStar || op == ttPowAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_POWi;
					else
						instruction = asBC_POWu;
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
				else if( op == ttStarStar || op == ttPowAssign )
				{
					if( lctx->type.dataType.IsIntegerType() )
						instruction = asBC_POWi64;
					else
						instruction = asBC_POWu64;
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
			else if( op == ttStarStar || op == ttPowAssign )
				instruction = asBC_POWf;
		}
		else if( lctx->type.dataType.IsDoubleType() )
		{
			if( rctx->type.dataType.IsIntegerType() )
			{
				asASSERT(rctx->type.dataType.GetSizeInMemoryDWords() == 1);

				if( op == ttStarStar || op == ttPowAssign )
					instruction = asBC_POWdi;
				else
					asASSERT(false);  // Should not be possible
			}
			else
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
				else if( op == ttStarStar || op == ttPowAssign )
					instruction = asBC_POWd;
			}
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
					v = int(lctx->type.GetConstantDW()) + int(rctx->type.GetConstantDW());
				else if( op == ttMinus )
					v = int(lctx->type.GetConstantDW()) - int(rctx->type.GetConstantDW());
				else if( op == ttStar )
					v = int(lctx->type.GetConstantDW()) * int(rctx->type.GetConstantDW());
				else if( op == ttSlash )
				{
					// TODO: Should probably report an error, rather than silently convert the value to 0
					if( rctx->type.GetConstantDW() == 0 || (int(rctx->type.GetConstantDW()) == -1 && lctx->type.GetConstantDW() == 0x80000000) )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = int(lctx->type.GetConstantDW()) / int(rctx->type.GetConstantDW());
						else
							v = lctx->type.GetConstantDW() / rctx->type.GetConstantDW();
				}
				else if( op == ttPercent )
				{
					// TODO: Should probably report an error, rather than silently convert the value to 0
					if( rctx->type.GetConstantDW() == 0 || (int(rctx->type.GetConstantDW()) == -1 && lctx->type.GetConstantDW() == 0x80000000) )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = int(lctx->type.GetConstantDW()) % int(rctx->type.GetConstantDW());
						else
							v = lctx->type.GetConstantDW() % rctx->type.GetConstantDW();
				}
				else if( op == ttStarStar )
				{
					bool isOverflow;
					if( lctx->type.dataType.IsIntegerType() )
						v = as_powi(int(lctx->type.GetConstantDW()), int(rctx->type.GetConstantDW()), isOverflow);
					else
						v = as_powu(lctx->type.GetConstantDW(), rctx->type.GetConstantDW(), isOverflow);

					if( isOverflow )
						Error(TXT_POW_OVERFLOW, node);
				}

				ctx->type.SetConstantDW(lctx->type.dataType, v);

				// If the right value is greater than the left value in a minus operation, then we need to convert the type to int
				if( lctx->type.dataType.GetTokenType() == ttUInt && op == ttMinus && lctx->type.GetConstantDW() < rctx->type.GetConstantDW())
					ctx->type.dataType.SetTokenType(ttInt);
			}
			else
			{
				asQWORD v = 0;
				if( op == ttPlus )
					v = asINT64(lctx->type.GetConstantQW()) + asINT64(rctx->type.GetConstantQW());
				else if( op == ttMinus )
					v = asINT64(lctx->type.GetConstantQW()) - asINT64(rctx->type.GetConstantQW());
				else if( op == ttStar )
					v = asINT64(lctx->type.GetConstantQW()) * asINT64(rctx->type.GetConstantQW());
				else if( op == ttSlash )
				{
					// TODO: Should probably report an error, rather than silently convert the value to 0
					if( rctx->type.GetConstantQW() == 0 || (rctx->type.GetConstantQW() == asQWORD(-1) && lctx->type.GetConstantQW() == (asQWORD(1)<<63)) )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = asINT64(lctx->type.GetConstantQW()) / asINT64(rctx->type.GetConstantQW());
						else
							v = lctx->type.GetConstantQW() / rctx->type.GetConstantQW();
				}
				else if( op == ttPercent )
				{
				    // TODO: Should probably report an error, rather than silently convert the value to 0
					if( rctx->type.GetConstantQW() == 0 || (rctx->type.GetConstantQW() == asQWORD(-1) && lctx->type.GetConstantQW() == (asQWORD(1)<<63)) )
						v = 0;
					else
						if( lctx->type.dataType.IsIntegerType() )
							v = asINT64(lctx->type.GetConstantQW()) % asINT64(rctx->type.GetConstantQW());
						else
							v = lctx->type.GetConstantQW() % rctx->type.GetConstantQW();
				}
				else if( op == ttStarStar )
				{
					bool isOverflow;
					if( lctx->type.dataType.IsIntegerType() )
						v = as_powi64(asINT64(lctx->type.GetConstantQW()), asINT64(rctx->type.GetConstantQW()), isOverflow);
					else
						v = as_powu64(lctx->type.GetConstantQW(), rctx->type.GetConstantQW(), isOverflow);

					if( isOverflow )
						Error(TXT_POW_OVERFLOW, node);
				}

				ctx->type.SetConstantQW(lctx->type.dataType, v);

				// If the right value is greater than the left value in a minus operation, then we need to convert the type to int
				if( lctx->type.dataType.GetTokenType() == ttUInt64 && op == ttMinus && lctx->type.GetConstantQW() < rctx->type.GetConstantQW())
					ctx->type.dataType.SetTokenType(ttInt64);
			}
		}
		else if( lctx->type.dataType.IsFloatType() )
		{
			float v = 0.0f;
			if( op == ttPlus )
				v = lctx->type.GetConstantF() + rctx->type.GetConstantF();
			else if( op == ttMinus )
				v = lctx->type.GetConstantF() - rctx->type.GetConstantF();
			else if( op == ttStar )
				v = lctx->type.GetConstantF() * rctx->type.GetConstantF();
			else if( op == ttSlash )
			{
				if( rctx->type.GetConstantF() == 0 )
					v = 0;
				else
					v = lctx->type.GetConstantF() / rctx->type.GetConstantF();
			}
			else if( op == ttPercent )
			{
				if( rctx->type.GetConstantF() == 0 )
					v = 0;
				else
					v = fmodf(lctx->type.GetConstantF(), rctx->type.GetConstantF());
			}
			else if( op == ttStarStar )
			{
				v = powf(lctx->type.GetConstantF(), rctx->type.GetConstantF());

				if( v == HUGE_VAL )
					Error(TXT_POW_OVERFLOW, node);
			}

			ctx->type.SetConstantF(lctx->type.dataType, v);
		}
		else if( lctx->type.dataType.IsDoubleType() )
		{
			double v = 0.0;
			if( rctx->type.dataType.IsIntegerType() )
			{
				asASSERT(rctx->type.dataType.GetSizeInMemoryDWords() == 1);

				if( op == ttStarStar || op == ttPowAssign )
				{
					v = pow(lctx->type.GetConstantD(), int(rctx->type.GetConstantDW()));
					if( v == HUGE_VAL )
						Error(TXT_POW_OVERFLOW, node);
				}
				else
					asASSERT(false);  // Should not be possible
			}
			else
			{
				if( op == ttPlus )
					v = lctx->type.GetConstantD() + rctx->type.GetConstantD();
				else if( op == ttMinus )
					v = lctx->type.GetConstantD() - rctx->type.GetConstantD();
				else if( op == ttStar )
					v = lctx->type.GetConstantD() * rctx->type.GetConstantD();
				else if( op == ttSlash )
				{
					if( rctx->type.GetConstantD() == 0 )
						v = 0;
					else
						v = lctx->type.GetConstantD() / rctx->type.GetConstantD();
				}
				else if( op == ttPercent )
				{
					if( rctx->type.GetConstantD() == 0 )
						v = 0;
					else
						v = fmod(lctx->type.GetConstantD(), rctx->type.GetConstantD());
				}
				else if( op == ttStarStar )
				{
					v = pow(lctx->type.GetConstantD(), rctx->type.GetConstantD());
					if( v == HUGE_VAL )
						Error(TXT_POW_OVERFLOW, node);
				}
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

void asCCompiler::CompileBitwiseOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, asCExprContext *ctx, eTokenType op)
{
	// TODO: If a constant is only using 32bits, then a 32bit operation is preferred

	if( op == ttUnrecognizedToken )
		op = node->tokenType;
	if( op == ttAmp    || op == ttAndAssign ||
		op == ttBitOr  || op == ttOrAssign  ||
		op == ttBitXor || op == ttXorAssign )
	{
		// Also do not permit float/double to be implicitly converted to integer in this case
		// as the user may think the result is a bitwise operation on the float value but it's not
		if (lctx->type.dataType.IsFloatType() || lctx->type.dataType.IsDoubleType())
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);

			// Set an integer value and allow the compiler to continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), 0);
			return;
		}
		if (rctx->type.dataType.IsFloatType() || rctx->type.dataType.IsDoubleType())
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);

			// Set an integer value and allow the compiler to continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), 0);
			return;
		}

		// Convert left hand operand to integer if it's not already one
		asCDataType to;
		if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 ||
			rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			to.SetTokenType(ttInt64);
		else
			to.SetTokenType(ttInt);

		// Do the actual conversion (keep sign/unsigned if possible)
		int l = int(reservedVariables.GetLength());
		rctx->bc.GetVarsUsed(reservedVariables);
		if( lctx->type.dataType.IsUnsignedType() )
			to.SetTokenType( to.GetSizeOnStackDWords() == 1 ? ttUInt : ttUInt64 );
		else
			to.SetTokenType( to.GetSizeOnStackDWords() == 1 ? ttInt : ttInt64 );
		ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true);
		reservedVariables.SetLength(l);

		// Verify that the conversion was successful
		if( lctx->type.dataType != to )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
		}

		// Convert right hand operand to same size as left hand
		l = int(reservedVariables.GetLength());
		lctx->bc.GetVarsUsed(reservedVariables);
		if( rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType( to.GetSizeOnStackDWords() == 1 ? ttUInt : ttUInt64 );
		else
			to.SetTokenType( to.GetSizeOnStackDWords() == 1 ? ttInt : ttInt64 );
		ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV, true);
		reservedVariables.SetLength(l);
		if( rctx->type.dataType != to )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
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
					v = lctx->type.GetConstantQW() & rctx->type.GetConstantQW();
				else if( op == ttBitOr )
					v = lctx->type.GetConstantQW() | rctx->type.GetConstantQW();
				else if( op == ttBitXor )
					v = lctx->type.GetConstantQW() ^ rctx->type.GetConstantQW();

				// Remember the result
				ctx->type.SetConstantQW(lctx->type.dataType, v);
			}
			else
			{
				asDWORD v = 0;
				if( op == ttAmp )
					v = lctx->type.GetConstantDW() & rctx->type.GetConstantDW();
				else if( op == ttBitOr )
					v = lctx->type.GetConstantDW() | rctx->type.GetConstantDW();
				else if( op == ttBitXor )
					v = lctx->type.GetConstantDW() ^ rctx->type.GetConstantDW();

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
		// Also do not permit float/double to be implicitly converted to integer in this case
		if( lctx->type.dataType.IsObject() || lctx->type.dataType.IsFloatType() || lctx->type.dataType.IsDoubleType() )
		{
			asCString str;
			str.Format(TXT_ILLEGAL_OPERATION_ON_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);

			// Set an integer value and allow the compiler to continue
			ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), 0);
			return;
		}

		// Convert left hand operand to integer if it's not already one
		asCDataType to = lctx->type.dataType;
		if( lctx->type.dataType.IsUnsignedType() &&
			lctx->type.dataType.GetSizeInMemoryBytes() < 4 )
		{
			// Upgrade to 32bit
			to = asCDataType::CreatePrimitive(ttUInt, false);
		}
		else if( !lctx->type.dataType.IsUnsignedType() )
		{
			if (lctx->type.dataType.GetSizeInMemoryDWords() == 2)
				to = asCDataType::CreatePrimitive(ttInt64, false);
			else
				to = asCDataType::CreatePrimitive(ttInt, false);
		}

		// Do the actual conversion
		int l = int(reservedVariables.GetLength());
		rctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV, true);
		reservedVariables.SetLength(l);

		// Verify that the conversion was successful
		if( lctx->type.dataType != to )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
			Error(str, node);
		}

		// Right operand must be 32bit uint
		l = int(reservedVariables.GetLength());
		lctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConversion(rctx, asCDataType::CreatePrimitive(ttUInt, true), node, asIC_IMPLICIT_CONV, true);
		reservedVariables.SetLength(l);
		if( !rctx->type.dataType.IsUnsignedType() )
		{
			asCString str;
			str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), "uint");
			Error(str, node);
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
					v = lctx->type.GetConstantDW() << rctx->type.GetConstantDW();
				else if( op == ttBitShiftRight )
					v = lctx->type.GetConstantDW() >> rctx->type.GetConstantDW();
				else if( op == ttBitShiftRightArith )
					v = int(lctx->type.GetConstantDW()) >> rctx->type.GetConstantDW();

				ctx->type.SetConstantDW(lctx->type.dataType, v);
			}
			else
			{
				asQWORD v = 0;
				if( op == ttBitShiftLeft )
					v = lctx->type.GetConstantQW() << rctx->type.GetConstantDW();
				else if( op == ttBitShiftRight )
					v = lctx->type.GetConstantQW() >> rctx->type.GetConstantDW();
				else if( op == ttBitShiftRightArith )
					v = asINT64(lctx->type.GetConstantQW()) >> rctx->type.GetConstantDW();

				ctx->type.SetConstantQW(lctx->type.dataType, v);
			}
		}
	}
}

void asCCompiler::CompileComparisonOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, asCExprContext *ctx, eTokenType op)
{
	// Both operands must be of the same type

	// If either operand is a non-primitive then first convert them to the best number type
	if( !lctx->type.dataType.IsPrimitive() )
	{
		int l = int(reservedVariables.GetLength());
		rctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConvObjectToBestMathType(lctx, node);
		reservedVariables.SetLength(l);
	}
	if( !rctx->type.dataType.IsPrimitive() )
	{
		int l = int(reservedVariables.GetLength());
		lctx->bc.GetVarsUsed(reservedVariables);
		ImplicitConvObjectToBestMathType(rctx, node);
		reservedVariables.SetLength(l);
	}

	// Implicitly convert the operands to matching types
	asCDataType to;
	if( lctx->type.dataType.IsDoubleType() || rctx->type.dataType.IsDoubleType() )
		to.SetTokenType(ttDouble);
	else if( lctx->type.dataType.IsFloatType() || rctx->type.dataType.IsFloatType() )
		to.SetTokenType(ttFloat);
	else if( lctx->type.dataType.GetSizeInMemoryDWords() == 2 || rctx->type.dataType.GetSizeInMemoryDWords() == 2 )
	{
		// Convert to int64 if both are signed or if one is non-constant and signed
		if( (lctx->type.dataType.IsIntegerType() && !lctx->type.isConstant) ||
			(rctx->type.dataType.IsIntegerType() && !rctx->type.isConstant) )
			to.SetTokenType(ttInt64);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt64);
		else
			to.SetTokenType(ttInt64);
	}
	else
	{
		// Convert to int32 if both are signed or if one is non-constant and signed
		if( (lctx->type.dataType.IsIntegerType() && !lctx->type.isConstant) ||
			(rctx->type.dataType.IsIntegerType() && !rctx->type.isConstant) )
			to.SetTokenType(ttInt);
		else if( lctx->type.dataType.IsUnsignedType() || rctx->type.dataType.IsUnsignedType() )
			to.SetTokenType(ttUInt);
		else if( lctx->type.dataType.IsBooleanType() || rctx->type.dataType.IsBooleanType() )
			to.SetTokenType(ttBool);
		else
			to.SetTokenType(ttInt);
	}

	// If doing an operation with double constant and float variable, the constant should be converted to float
	if( (lctx->type.isConstant && lctx->type.dataType.IsDoubleType() && !rctx->type.isConstant && rctx->type.dataType.IsFloatType()) ||
		(rctx->type.isConstant && rctx->type.dataType.IsDoubleType() && !lctx->type.isConstant && lctx->type.dataType.IsFloatType()) )
		to.SetTokenType(ttFloat);

	asASSERT( to.GetTokenType() != ttUnrecognizedToken );

	// Do we have a mismatch between the sign of the operand?
	bool signMismatch = false;
	for( int n = 0; !signMismatch && n < 2; n++ )
	{
		asCExprContext *opCtx = n ? rctx : lctx;

		if( opCtx->type.dataType.IsUnsignedType() != to.IsUnsignedType() )
		{
			// We have a mismatch, unless the value is a literal constant and the conversion won't affect its value
			signMismatch = true;
			if( opCtx->type.isConstant )
			{
				if( opCtx->type.dataType.GetTokenType() == ttUInt64 || opCtx->type.dataType.GetTokenType() == ttInt64 )
				{
					if( !(opCtx->type.GetConstantQW() & (asQWORD(1)<<63)) )
						signMismatch = false;
				}
				else if(opCtx->type.dataType.GetTokenType() == ttUInt || opCtx->type.dataType.GetTokenType() == ttInt || opCtx->type.dataType.IsEnumType() )
				{
					if( !(opCtx->type.GetConstantDW() & (1<<31)) )
						signMismatch = false;
				}
				else if (opCtx->type.dataType.GetTokenType() == ttUInt16 || opCtx->type.dataType.GetTokenType() == ttInt16)
				{
					if (!(opCtx->type.GetConstantW() & (1 << 15)))
						signMismatch = false;
				}
				else if (opCtx->type.dataType.GetTokenType() == ttUInt8 || opCtx->type.dataType.GetTokenType() == ttInt8)
				{
					if (!(opCtx->type.GetConstantB() & (1 << 7)))
						signMismatch = false;
				}

				// It's not necessary to check for floats or double, because if
				// it was then the types for the conversion will never be unsigned
			}
		}
	}

	// Check for signed/unsigned mismatch
	if( signMismatch )
		Warning(TXT_SIGNED_UNSIGNED_MISMATCH, node);

	// Attempt to resolve ambiguous enumerations
	if( lctx->type.dataType.IsEnumType() && rctx->enumValue != "" )
		ImplicitConversion(rctx, lctx->type.dataType, node, asIC_IMPLICIT_CONV);
	else if( rctx->type.dataType.IsEnumType() && lctx->enumValue != "" )
		ImplicitConversion(lctx, rctx->type.dataType, node, asIC_IMPLICIT_CONV);

	// Do the actual conversion
	int l = int(reservedVariables.GetLength());
	rctx->bc.GetVarsUsed(reservedVariables);

	if( lctx->type.dataType.IsReference() )
		ConvertToVariable(lctx);
	if( rctx->type.dataType.IsReference() )
		ConvertToVariable(rctx);

	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV);
	reservedVariables.SetLength(l);

	// Verify that the conversion was successful
	bool ok = true;
	if( !lctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
		ok = false;
	}

	if( !rctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
		ok = false;
	}

	if( !ok )
	{
		// It wasn't possible to get two valid operands, so we just return
		// a boolean result and let the compiler continue.
#if AS_SIZEOF_BOOL == 1
		ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
#else
		ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
#endif
		return;
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

	if( op == ttUnrecognizedToken )
		op = node->tokenType;

	if( !isConstant )
	{
		if( to.IsBooleanType() )
		{
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
#if AS_SIZEOF_BOOL == 1
				ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), 0);
#else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), 0);
#endif
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
			if( op == ttEqual || op == ttNotEqual )
			{
				asDWORD lv, rv;
				#if AS_SIZEOF_BOOL == 1
					lv = lctx->type.GetConstantB();
					rv = rctx->type.GetConstantB();
				#else
					lv = lctx->type.GetConstantDW();
					rv = rctx->type.GetConstantDW();
				#endif

				// Make sure they are equal if not false
				if (lv != 0) lv = VALUE_OF_BOOLEAN_TRUE;
				if (rv != 0) rv = VALUE_OF_BOOLEAN_TRUE;

				asDWORD v = 0;
				if (op == ttEqual)
					v = (lv == rv) ? VALUE_OF_BOOLEAN_TRUE : 0;
				else if (op == ttNotEqual)
					v = (lv != rv) ? VALUE_OF_BOOLEAN_TRUE : 0;

				#if AS_SIZEOF_BOOL == 1
					ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), (asBYTE)v);
				#else
					ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), v);
				#endif
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
				int v = int(lctx->type.GetConstantDW()) - int(rctx->type.GetConstantDW());
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			{
				asDWORD v1 = lctx->type.GetConstantDW();
				asDWORD v2 = rctx->type.GetConstantDW();
				if( v1 < v2 ) i = -1;
				if( v1 > v2 ) i = 1;
			}
			else if( lctx->type.dataType.IsIntegerType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				asINT64 v = asINT64(lctx->type.GetConstantQW()) - asINT64(rctx->type.GetConstantQW());
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsUnsignedType() && lctx->type.dataType.GetSizeInMemoryDWords() == 2 )
			{
				asQWORD v1 = lctx->type.GetConstantQW();
				asQWORD v2 = rctx->type.GetConstantQW();
				if( v1 < v2 ) i = -1;
				if( v1 > v2 ) i = 1;
			}
			else if( lctx->type.dataType.IsFloatType() )
			{
				float v = lctx->type.GetConstantF() - rctx->type.GetConstantF();
				if( v < 0 ) i = -1;
				if( v > 0 ) i = 1;
			}
			else if( lctx->type.dataType.IsDoubleType() )
			{
				double v = lctx->type.GetConstantD() - rctx->type.GetConstantD();
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

			#if AS_SIZEOF_BOOL == 1
				ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), (asBYTE)i);
			#else
				ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), i);
			#endif
		}
	}
}

void asCCompiler::PushVariableOnStack(asCExprContext *ctx, bool asReference)
{
	// Put the result on the stack
	if( asReference )
	{
		ctx->bc.InstrSHORT(asBC_PSF, ctx->type.stackOffset);
		ctx->type.dataType.MakeReference(true);
	}
	else
	{
		if( ctx->type.dataType.GetSizeInMemoryDWords() == 1 )
			ctx->bc.InstrSHORT(asBC_PshV4, ctx->type.stackOffset);
		else
			ctx->bc.InstrSHORT(asBC_PshV8, ctx->type.stackOffset);
	}
}

void asCCompiler::CompileBooleanOperator(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, asCExprContext *ctx, eTokenType op)
{
	// Both operands must be booleans
	asCDataType to;
	to.SetTokenType(ttBool);

	// Do the actual conversion
	int l = int(reservedVariables.GetLength());
	rctx->bc.GetVarsUsed(reservedVariables);
	lctx->bc.GetVarsUsed(reservedVariables);

	// Allow value types to be converted to bool using 'bool opImplConv()'
	if( lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
		ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV);
	if( rctx->type.dataType.GetTypeInfo() && (rctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_VALUE) )
		ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV);
	reservedVariables.SetLength(l);

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsBooleanType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), "bool");
		Error(str, node);
		// Force the conversion to allow compilation to proceed
		lctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
	}

	if( !rctx->type.dataType.IsBooleanType() )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), "bool");
		Error(str, node);
		// Force the conversion to allow compilation to proceed
		rctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
	}

	bool isConstant = lctx->type.isConstant && rctx->type.isConstant;

	ctx->type.Set(asCDataType::CreatePrimitive(ttBool, true));

	// What kind of operator is it?
	if( op == ttUnrecognizedToken )
		op = node->tokenType;
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
			if( lctx->type.GetConstantB() != 0 ) lctx->type.SetConstantB(VALUE_OF_BOOLEAN_TRUE);
			if( rctx->type.GetConstantB() != 0 ) rctx->type.SetConstantB(VALUE_OF_BOOLEAN_TRUE);

			asBYTE v = 0;
			v = lctx->type.GetConstantB() - rctx->type.GetConstantB();
			if( v != 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;

			ctx->type.isConstant = true;
			ctx->type.SetConstantB(v);
#else
			if( lctx->type.GetConstantDW() != 0 ) lctx->type.SetConstantDW(VALUE_OF_BOOLEAN_TRUE);
			if( rctx->type.GetConstantDW() != 0 ) rctx->type.SetConstantDW(VALUE_OF_BOOLEAN_TRUE);

			asDWORD v = 0;
			v = lctx->type.GetConstantDW() - rctx->type.GetConstantDW();
			if( v != 0 ) v = VALUE_OF_BOOLEAN_TRUE; else v = 0;

			ctx->type.isConstant = true;
			ctx->type.SetConstantDW(v);
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

			ctx->bc.InstrSHORT(asBC_CpyVtoR4, lctx->type.stackOffset);
			ctx->bc.Instr(asBC_ClrHi);
			if( op == ttAnd )
			{
				ctx->bc.InstrDWORD(asBC_JNZ, label1);
				ctx->bc.InstrW_DW(asBC_SetV4, (asWORD)offset, 0);
				ctx->bc.InstrINT(asBC_JMP, label2);
			}
			else if( op == ttOr )
			{
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
				v = lctx->type.GetConstantB() && rctx->type.GetConstantB();
			else if( op == ttOr )
				v = lctx->type.GetConstantB() || rctx->type.GetConstantB();

			// Remember the result
			ctx->type.isConstant = true;
			ctx->type.SetConstantB(v);
#else
			asDWORD v = 0;
			if( op == ttAnd )
				v = lctx->type.GetConstantDW() && rctx->type.GetConstantDW();
			else if( op == ttOr )
				v = lctx->type.GetConstantDW() || rctx->type.GetConstantDW();

			// Remember the result
			ctx->type.isConstant = true;
			ctx->type.SetConstantDW(v);
#endif
		}
	}
}

void asCCompiler::CompileOperatorOnHandles(asCScriptNode *node, asCExprContext *lctx, asCExprContext *rctx, asCExprContext *ctx, eTokenType opToken)
{
	// Process the property accessor as get
	if( ProcessPropertyGetAccessor(lctx, node) < 0 )
		return;
	if( ProcessPropertyGetAccessor(rctx, node) < 0 )
		return;

	DetermineSingleFunc(lctx, node);
	DetermineSingleFunc(rctx, node);

	// Make sure lctx doesn't end up with a variable used in rctx
	if( lctx->type.isTemporary && rctx->bc.IsVarUsed(lctx->type.stackOffset) )
	{
		asCArray<int> vars;
		rctx->bc.GetVarsUsed(vars);
		int offset = AllocateVariable(lctx->type.dataType, true);
		rctx->bc.ExchangeVar(lctx->type.stackOffset, offset);
		ReleaseTemporaryVariable(offset, 0);
	}

	if( opToken == ttUnrecognizedToken )
		opToken = node->tokenType;

	// Warn if not both operands are explicit handles or null handles
	if( (opToken == ttEqual || opToken == ttNotEqual) &&
		((!(lctx->type.isExplicitHandle || lctx->type.IsNullConstant()) && !(lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_IMPLICIT_HANDLE))) ||
		 (!(rctx->type.isExplicitHandle || rctx->type.IsNullConstant()) && !(rctx->type.dataType.GetTypeInfo() && (rctx->type.dataType.GetTypeInfo()->flags & asOBJ_IMPLICIT_HANDLE)))) )
	{
		Warning(TXT_HANDLE_COMPARISON, node);
	}

	// If one of the operands is a value type used as handle, we should look for the opEquals method
	if( ((lctx->type.dataType.GetTypeInfo() && (lctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE)) ||
		 (rctx->type.dataType.GetTypeInfo() && (rctx->type.dataType.GetTypeInfo()->flags & asOBJ_ASHANDLE))) &&
		(opToken == ttEqual || opToken == ttIs ||
		 opToken == ttNotEqual || opToken == ttNotIs) )
	{
		// TODO: Should evaluate which of the two have the best match. If both have equal match, the first version should be used
		// Find the matching opEquals method
		int r = CompileOverloadedDualOperator2(node, "opEquals", lctx, rctx, true, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
		if( r == 0 )
		{
			// Try again by switching the order of the operands
			r = CompileOverloadedDualOperator2(node, "opEquals", rctx, lctx, false, ctx, true, asCDataType::CreatePrimitive(ttBool, false));
		}

		if( r == 1 )
		{
			if( opToken == ttNotEqual || opToken == ttNotIs )
				ctx->bc.InstrSHORT(asBC_NOT, ctx->type.stackOffset);

			// Success, don't continue
			return;
		}
		else if( r == 0 )
		{
			// Couldn't find opEquals method
			Error(TXT_NO_APPROPRIATE_OPEQUALS, node);
		}

		// Compiler error, don't continue
#if AS_SIZEOF_BOOL == 1
		ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
#else
		ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
#endif
		return;
	}


	// Implicitly convert null to the other type
	asCDataType to;
	if( lctx->type.IsNullConstant() )
		to = rctx->type.dataType;
	else if( rctx->type.IsNullConstant() )
		to = lctx->type.dataType;
	else
	{
		// Find a common base type
		asCExprContext tmp(engine);
		tmp.type = rctx->type;
		ImplicitConversion(&tmp, lctx->type.dataType, 0, asIC_IMPLICIT_CONV, false);
		if( tmp.type.dataType.GetTypeInfo() == lctx->type.dataType.GetTypeInfo() )
			to = lctx->type.dataType;
		else
			to = rctx->type.dataType;

		// Assume handle-to-const as it is not possible to convert handle-to-const to handle-to-non-const
		to.MakeHandleToConst(true);
	}

	// Need to pop the value if it is a null constant
	if( lctx->type.IsNullConstant() )
		lctx->bc.Instr(asBC_PopPtr);
	if( rctx->type.IsNullConstant() )
		rctx->bc.Instr(asBC_PopPtr);

	// Convert both sides to explicit handles
	to.MakeHandle(true);
	to.MakeReference(false);

	if( !to.IsObjectHandle() )
	{
		// Compiler error, don't continue
		Error(TXT_OPERANDS_MUST_BE_HANDLES, node);
#if AS_SIZEOF_BOOL == 1
		ctx->type.SetConstantB(asCDataType::CreatePrimitive(ttBool, true), true);
#else
		ctx->type.SetConstantDW(asCDataType::CreatePrimitive(ttBool, true), true);
#endif
		return;
	}

	// Do the conversion
	ImplicitConversion(lctx, to, node, asIC_IMPLICIT_CONV);
	ImplicitConversion(rctx, to, node, asIC_IMPLICIT_CONV);

	// Both operands must be of the same type

	// Verify that the conversion was successful
	if( !lctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, lctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
	}

	if( !rctx->type.dataType.IsEqualExceptConst(to) )
	{
		asCString str;
		str.Format(TXT_NO_CONVERSION_s_TO_s, rctx->type.dataType.Format(outFunc->nameSpace).AddressOf(), to.Format(outFunc->nameSpace).AddressOf());
		Error(str, node);
	}

	// Make sure it really is handles that are being compared
	if( !lctx->type.dataType.IsObjectHandle() )
	{
		Error(TXT_OPERANDS_MUST_BE_HANDLES, node);
	}

	ctx->type.Set(asCDataType::CreatePrimitive(ttBool, true));

	if( opToken == ttEqual || opToken == ttNotEqual || opToken == ttIs || opToken == ttNotIs )
	{
		// Make sure handles received as parameters by reference are copied to a local variable before the
		// asBC_CmpPtr, so we don't end up comparing the reference to the handle instead of the handle itself
		if( lctx->type.isVariable && !lctx->type.isTemporary && lctx->type.stackOffset <= 0 )
			lctx->type.isVariable = false;
		if( rctx->type.isVariable && !rctx->type.isTemporary && rctx->type.stackOffset <= 0 )
			rctx->type.isVariable = false;

		// TODO: runtime optimize: don't do REFCPY if not necessary
		ConvertToVariableNotIn(lctx, rctx);
		ConvertToVariable(rctx);

		// Pop the pointers from the stack as they will not be used
		lctx->bc.Instr(asBC_PopPtr);
		rctx->bc.Instr(asBC_PopPtr);

		MergeExprBytecode(ctx, lctx);
		MergeExprBytecode(ctx, rctx);

		int a = AllocateVariable(ctx->type.dataType, true);
		int b = lctx->type.stackOffset;
		int c = rctx->type.stackOffset;

		ctx->bc.InstrW_W(asBC_CmpPtr, b, c);

		if( opToken == ttEqual || opToken == ttIs )
			ctx->bc.Instr(asBC_TZ);
		else if( opToken == ttNotEqual || opToken == ttNotIs )
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


void asCCompiler::PerformFunctionCall(int funcId, asCExprContext *ctx, bool isConstructor, asCArray<asCExprContext*> *args, asCObjectType *objType, bool useVariable, int varOffset, int funcPtrVar)
{
	asCScriptFunction *descr = builder->GetFunctionDescription(funcId);

	// A shared object may not call non-shared functions
	if( outFunc->IsShared() && !descr->IsShared() )
	{
		asCString msg;
		msg.Format(TXT_SHARED_CANNOT_CALL_NON_SHARED_FUNC_s, descr->GetDeclarationStr().AddressOf());
		Error(msg, ctx->exprNode);
	}

	// Check if the function is private or protected
	if (descr->IsPrivate())
	{
		asCObjectType *type = descr->objectType;
		if (type == 0 && descr->traits.GetTrait(asTRAIT_CONSTRUCTOR))
			type = CastToObjectType(descr->returnType.GetTypeInfo());

		asASSERT(type);

		if( (type != outFunc->GetObjectType()) )
		{
			asCString msg;
			msg.Format(TXT_PRIVATE_METHOD_CALL_s, descr->GetDeclarationStr().AddressOf());
			Error(msg, ctx->exprNode);
		}
	}
	else if (descr->IsProtected())
	{
		asCObjectType *type = descr->objectType;
		if (type == 0 && descr->traits.GetTrait(asTRAIT_CONSTRUCTOR))
			type = CastToObjectType(descr->returnType.GetTypeInfo());

		asASSERT(type);

		if (!(type == outFunc->objectType || (outFunc->objectType && outFunc->objectType->DerivesFrom(type))))
		{
			asCString msg;
			msg.Format(TXT_PROTECTED_METHOD_CALL_s, descr->GetDeclarationStr().AddressOf());
			Error(msg, ctx->exprNode);
		}
	}

	int argSize = descr->GetSpaceNeededForArguments();

	// If we're calling a class method we must make sure the object is guaranteed to stay
	// alive throughout the call by holding on to a reference in a local variable. This must
	// be done for any methods that return references, and any calls on script objects.
	// Application registered objects are assumed to know to keep themselves alive even
	// if the method doesn't return a reference.
	if( !ctx->type.isRefSafe &&
		descr->objectType &&
		(ctx->type.dataType.IsObjectHandle() || ctx->type.dataType.SupportHandles()) &&
		(descr->returnType.IsReference() || (ctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_SCRIPT_OBJECT)) &&
		!(ctx->type.isVariable || ctx->type.isTemporary) &&
		!(ctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_SCOPED) &&
		!(ctx->type.dataType.GetTypeInfo()->GetFlags() & asOBJ_ASHANDLE) )
	{
		// TODO: runtime optimize: Avoid this for global variables, by storing a reference to the global variable once in a
		//                         local variable and then refer to the same for each call. An alias for the global variable
		//                         should be stored in the variable scope so that the compiler can find it. For loops and
		//                         scopes that will always be executed, i.e. non-if scopes the alias should be stored in the
		//                         higher scope to increase the probability of re-use.

		int tempRef = AllocateVariable(ctx->type.dataType, true);
		ctx->bc.InstrSHORT(asBC_PSF, (short)tempRef);
		ctx->bc.InstrPTR(asBC_REFCPY, ctx->type.dataType.GetTypeInfo());

		// Add the release of this reference as a deferred expression
		asSDeferredParam deferred;
		deferred.origExpr = 0;
		deferred.argInOutFlags = asTM_INREF;
		deferred.argNode = 0;
		deferred.argType.SetVariable(ctx->type.dataType, tempRef, true);
		ctx->deferredParams.PushLast(deferred);

		// Forget the current type
		ctx->type.SetDummy();
	}

	// Check if there is a need to add a hidden pointer for when the function returns an object by value
	if( descr->DoesReturnOnStack() && !useVariable )
	{
		useVariable = true;
		varOffset = AllocateVariable(descr->returnType, true);

		// Push the pointer to the pre-allocated space for the return value
		ctx->bc.InstrSHORT(asBC_PSF, short(varOffset));

		if( descr->objectType )
		{
			// The object pointer is already on the stack, but should be the top
			// one, so we need to swap the pointers in order to get the correct
			ctx->bc.Instr(asBC_SwapPtr);
		}
	}

	if( isConstructor )
	{
		// Sometimes the value types are allocated on the heap,
		// which is when this way of constructing them is used.

		asASSERT(useVariable == false);

		if( (objType->flags & asOBJ_TEMPLATE) )
		{
			asASSERT( descr->funcType == asFUNC_SCRIPT );

			// Find the id of the real constructor and not the generated stub
			asUINT id = 0;
			asDWORD *bc = descr->scriptData->byteCode.AddressOf();
			while( bc )
			{
				if( (*(asBYTE*)bc) == asBC_CALLSYS )
				{
					id = asBC_INTARG(bc);
					break;
				}
				bc += asBCTypeSize[asBCInfo[*(asBYTE*)bc].type];
			}

			asASSERT( id );

			ctx->bc.InstrPTR(asBC_OBJTYPE, objType);
			ctx->bc.Alloc(asBC_ALLOC, objType, id, argSize + AS_PTR_SIZE + AS_PTR_SIZE);
		}
		else
			ctx->bc.Alloc(asBC_ALLOC, objType, descr->id, argSize+AS_PTR_SIZE);

		// The instruction has already moved the returned object to the variable
		ctx->type.Set(asCDataType::CreatePrimitive(ttVoid, false));
		ctx->type.isLValue = false;

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, false);

		ProcessDeferredParams(ctx);

		return;
	}
	else
	{
		if( descr->objectType )
			argSize += AS_PTR_SIZE;

		// If the function returns an object by value the address of the location
		// where the value should be stored is passed as an argument too
		if( descr->DoesReturnOnStack() )
			argSize += AS_PTR_SIZE;

		// TODO: runtime optimize: If it is known that a class method cannot be overridden the call
		//                         should be made with asBC_CALL as it is faster. Examples where this
		//                         is known is for example finalled methods where the class doesn't derive
		//                         from any other, or even non-finalled methods but where it is known
		//                         at compile time the true type of the object. The first should be
		//                         quite easy to determine, but the latter will be quite complex and possibly
		//                         not worth it.
		if( descr->funcType == asFUNC_IMPORTED )
			ctx->bc.Call(asBC_CALLBND , descr->id, argSize);
		// TODO: Maybe we need two different byte codes
		else if( descr->funcType == asFUNC_INTERFACE || descr->funcType == asFUNC_VIRTUAL )
			ctx->bc.Call(asBC_CALLINTF, descr->id, argSize);
		else if( descr->funcType == asFUNC_SCRIPT )
			ctx->bc.Call(asBC_CALL    , descr->id, argSize);
		else if( descr->funcType == asFUNC_SYSTEM )
		{
			// Check if we can use the faster asBC_Thiscall1 instruction, i.e. one of
			//    type &obj::func(int)
			//    type &obj::func(uint)
			if( descr->GetObjectType() && descr->returnType.IsReference() &&
				descr->parameterTypes.GetLength() == 1 &&
				(descr->parameterTypes[0].IsIntegerType() || descr->parameterTypes[0].IsUnsignedType()) &&
				descr->parameterTypes[0].GetSizeInMemoryBytes() == 4 &&
				!descr->parameterTypes[0].IsReference() )
				ctx->bc.Call(asBC_Thiscall1, descr->id, argSize);
			else
				ctx->bc.Call(asBC_CALLSYS , descr->id, argSize);
		}
		else if( descr->funcType == asFUNC_FUNCDEF )
			ctx->bc.CallPtr(asBC_CallPtr, funcPtrVar, argSize);
	}

	if( (descr->returnType.IsObject() || descr->returnType.IsFuncdef()) && !descr->returnType.IsReference() )
	{
		int returnOffset = 0;

		asCExprValue tmpExpr = ctx->type;

		if( descr->DoesReturnOnStack() )
		{
			asASSERT( useVariable );

			// The variable was allocated before the function was called
			returnOffset = varOffset;
			ctx->type.SetVariable(descr->returnType, returnOffset, true);

			// The variable was initialized by the function, so we need to mark it as initialized here
			ctx->bc.ObjInfo(varOffset, asOBJ_INIT);
		}
		else
		{
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
				returnOffset = AllocateVariable(descr->returnType, true, !descr->returnType.IsObjectHandle());
				ctx->type.SetVariable(descr->returnType, returnOffset, true);
			}

			// Move the pointer from the object register to the temporary variable
			ctx->bc.InstrSHORT(asBC_STOREOBJ, (short)returnOffset);
		}

		ReleaseTemporaryVariable(tmpExpr, &ctx->bc);

		ctx->type.dataType.MakeReference(IsVariableOnHeap(returnOffset));
		ctx->type.isLValue = false; // It is a reference, but not an lvalue

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
		if( args )
			AfterFunctionCall(funcId, *args, ctx, true);

		// Do not process the output parameters yet, because it
		// might invalidate the returned reference

		// If the context holds a variable that needs cleanup
		// store it as a deferred parameter so it will be cleaned up
		// afterwards.
		if( ctx->type.isTemporary )
		{
			asSDeferredParam defer;
			defer.argNode = 0;
			defer.argType = ctx->type;
			defer.argInOutFlags = asTM_INOUTREF;
			defer.origExpr = 0;
			ctx->deferredParams.PushLast(defer);
		}

		ctx->type.Set(descr->returnType);
		if( !descr->returnType.IsPrimitive() )
		{
			ctx->bc.Instr(asBC_PshRPtr);
			if( descr->returnType.IsObject() &&
				!descr->returnType.IsObjectHandle() )
			{
				// We are getting the pointer to the object
				// not a pointer to a object variable
				ctx->type.dataType.MakeReference(false);
			}
		}

		// A returned reference can be used as lvalue
		ctx->type.isLValue = true;
	}
	else
	{
		asCExprValue tmpExpr = ctx->type;

		if( descr->returnType.GetSizeInMemoryBytes() )
		{
			int offset;
			if (useVariable)
				offset = varOffset;
			else
			{
				// Allocate a temporary variable to hold the value, but make sure
				// the temporary variable isn't used in any of the deferred arguments
				int l = int(reservedVariables.GetLength());
				for (asUINT n = 0; args && n < args->GetLength(); n++)
				{
					asCExprContext *expr = (*args)[n]->origExpr;
					if (expr)
						expr->bc.GetVarsUsed(reservedVariables);
				}
				offset = AllocateVariable(descr->returnType, true);
				reservedVariables.SetLength(l);
			}

			ctx->type.SetVariable(descr->returnType, offset, true);

			// Move the value from the return register to the variable
			if( descr->returnType.GetSizeOnStackDWords() == 1 )
				ctx->bc.InstrSHORT(asBC_CpyRtoV4, (short)offset);
			else if( descr->returnType.GetSizeOnStackDWords() == 2 )
				ctx->bc.InstrSHORT(asBC_CpyRtoV8, (short)offset);
		}
		else
			ctx->type.Set(descr->returnType);

		ReleaseTemporaryVariable(tmpExpr, &ctx->bc);

		ctx->type.isLValue = false;

		// Clean up arguments
		if( args )
			AfterFunctionCall(funcId, *args, ctx, false);

		ProcessDeferredParams(ctx);
	}
}

// This only merges the bytecode, but doesn't modify the type of the final context
void asCCompiler::MergeExprBytecode(asCExprContext *before, asCExprContext *after)
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
void asCCompiler::MergeExprBytecodeAndType(asCExprContext *before, asCExprContext *after)
{
	MergeExprBytecode(before, after);

	before->Merge(after);
}

void asCCompiler::FilterConst(asCArray<int> &funcs, bool removeConst)
{
	if( funcs.GetLength() == 0 ) return;

	// This is only done for object methods
	asCScriptFunction *desc = builder->GetFunctionDescription(funcs[0]);
	if( !desc || desc->objectType == 0 ) return;

	// Check if there are any non-const matches
	asUINT n;
	bool foundNonConst = false;
	for( n = 0; n < funcs.GetLength(); n++ )
	{
		desc = builder->GetFunctionDescription(funcs[n]);
		if( desc && desc->IsReadOnly() != removeConst )
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
			if( desc && desc->IsReadOnly() == removeConst )
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

asCExprValue::asCExprValue()
{
	isTemporary = false;
	stackOffset = 0;
	isConstant = false;
	isVariable = false;
	isExplicitHandle = false;
	qwordValue = 0;
	isLValue = false;
	isRefToLocal = false;
	isRefSafe = false;
}

void asCExprValue::Set(const asCDataType &dt)
{
	dataType = dt;

	isTemporary = false;
	stackOffset = 0;
	isConstant = false;
	isVariable = false;
	isExplicitHandle = false;
	qwordValue = 0;
	isLValue = false;
	isRefToLocal = false;
	isRefSafe = false;
}

void asCExprValue::SetVariable(const asCDataType &in_dt, int in_stackOffset, bool in_isTemporary)
{
	Set(in_dt);

	this->isVariable = true;
	this->isTemporary = in_isTemporary;
	this->stackOffset = (short)in_stackOffset;
}

void asCExprValue::SetConstantQW(const asCDataType &dt, asQWORD value)
{
	Set(dt);

	isConstant = true;
	SetConstantQW(value);
}

void asCExprValue::SetConstantDW(const asCDataType &dt, asDWORD value)
{
	Set(dt);

	isConstant = true;
	SetConstantDW(value);
}

void asCExprValue::SetConstantB(const asCDataType &dt, asBYTE value)
{
	Set(dt);

	isConstant = true;
	SetConstantB(value);
}

void asCExprValue::SetConstantW(const asCDataType &dt, asWORD value)
{
	Set(dt);

	isConstant = true;
	SetConstantW(value);
}

void asCExprValue::SetConstantF(const asCDataType &dt, float value)
{
	Set(dt);

	isConstant = true;
	SetConstantF(value);
}

void asCExprValue::SetConstantD(const asCDataType &dt, double value)
{
	Set(dt);

	isConstant = true;
	SetConstantD(value);
}

void asCExprValue::SetConstantQW(asQWORD value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 8);
	qwordValue = value;
}

void asCExprValue::SetConstantDW(asDWORD value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 4);
	dwordValue = value;
}

void asCExprValue::SetConstantW(asWORD value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 2);
	wordValue = value;
}

void asCExprValue::SetConstantB(asBYTE value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 1);
	byteValue = value;
}

void asCExprValue::SetConstantF(float value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 4);
	floatValue = value;
}

void asCExprValue::SetConstantD(double value)
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 8);
	doubleValue = value;
}

asQWORD asCExprValue::GetConstantQW()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 8);
	return qwordValue;
}

asDWORD asCExprValue::GetConstantDW()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 4);
	return dwordValue;
}

asWORD asCExprValue::GetConstantW()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 2);
	return wordValue;
}

asBYTE asCExprValue::GetConstantB()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 1);
	return byteValue;
}

float asCExprValue::GetConstantF()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 4);
	return floatValue;
}

double asCExprValue::GetConstantD()
{
	asASSERT(dataType.GetSizeInMemoryBytes() == 8);
	return doubleValue;
}

void asCExprValue::SetConstantData(const asCDataType &dt, asQWORD qw)
{
	Set(dt);

	isConstant = true;

	// This code is necessary to guarantee that the code
	// works on both big endian and little endian CPUs.
	if (dataType.GetSizeInMemoryBytes() == 1)
		byteValue = (asBYTE)qw;
	if (dataType.GetSizeInMemoryBytes() == 2)
		wordValue = (asWORD)qw;
	if (dataType.GetSizeInMemoryBytes() == 4)
		dwordValue = (asDWORD)qw;
	else
		qwordValue = qw;
}

asQWORD asCExprValue::GetConstantData()
{
	asQWORD qw = 0;
	// This code is necessary to guarantee that the code
	// works on both big endian and little endian CPUs.
	if (dataType.GetSizeInMemoryBytes() == 1)
		qw = byteValue;
	if (dataType.GetSizeInMemoryBytes() == 2)
		qw = wordValue;
	if (dataType.GetSizeInMemoryBytes() == 4)
		qw = dwordValue;
	else
		qw = qwordValue;
	return qw;
}

void asCExprValue::SetUndefinedFuncHandle(asCScriptEngine *engine)
{
	// This is used for when the expression evaluates to a
	// function, but it is not yet known exactly which. The
	// owner expression will hold the name of the function
	// to determine the exact function when the signature is
	// known.
	Set(asCDataType::CreateObjectHandle(&engine->functionBehaviours, true));
	isConstant = true;
	isExplicitHandle = false;
	qwordValue = 1; // Set to a different value than 0 to differentiate from null constant
	isLValue = false;
}

bool asCExprValue::IsUndefinedFuncHandle() const
{
	if (isConstant == false) return false;
	if (qwordValue == 0) return false;
	if (isLValue) return false;
	if (dataType.GetTypeInfo() == 0) return false;
	if (dataType.GetTypeInfo()->name != "$func") return false;
	if (dataType.IsFuncdef()) return false;

	return true;
}

void asCExprValue::SetNullConstant()
{
	Set(asCDataType::CreateNullHandle());
	isConstant = true;
	isExplicitHandle = false;
	qwordValue = 0;
	isLValue = false;
}

bool asCExprValue::IsNullConstant() const
{
	// We can't check the actual object type, because the null constant may have been cast to another type
	if (isConstant && dataType.IsObjectHandle() && qwordValue == 0)
		return true;

	return false;
}

void asCExprValue::SetVoid()
{
	Set(asCDataType::CreatePrimitive(ttVoid, false));
	isLValue = false;
	isConstant = true;
}

bool asCExprValue::IsVoid() const
{
	if (dataType.GetTokenType() == ttVoid)
		return true;

	return false;
}

void asCExprValue::SetDummy()
{
	SetConstantDW(asCDataType::CreatePrimitive(ttInt, true), 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////

asCExprContext::asCExprContext(asCScriptEngine *engine) : bc(engine)
{
	property_arg = 0;

	Clear();
}

asCExprContext::~asCExprContext()
{
	if (property_arg)
		asDELETE(property_arg, asCExprContext);
}

void asCExprContext::Clear()
{
	bc.ClearAll();
	type.Set(asCDataType());
	deferredParams.SetLength(0);
	if (property_arg)
		asDELETE(property_arg, asCExprContext);
	property_arg = 0;
	exprNode = 0;
	origExpr = 0;
	property_get = 0;
	property_set = 0;
	property_const = false;
	property_handle = false;
	property_ref = false;
	methodName = "";
	enumValue = "";
	symbolNamespace = 0;
	isVoidExpression = false;
	isCleanArg = false;
	isAnonymousInitList = false;
	origCode = 0;
}

bool asCExprContext::IsClassMethod() const
{
	if (type.dataType.GetTypeInfo() == 0) return false;
	if (methodName == "") return false;
	if (type.dataType.GetTypeInfo() == &type.dataType.GetTypeInfo()->engine->functionBehaviours) return false;
	if (isAnonymousInitList) return false;
	return true;
}

bool asCExprContext::IsGlobalFunc() const
{
	if (type.dataType.GetTypeInfo() == 0) return false;
	if (methodName == "") return false;
	if (type.dataType.GetTypeInfo() != &type.dataType.GetTypeInfo()->engine->functionBehaviours) return false;
	if (isAnonymousInitList) return false;
	return true;
}

void asCExprContext::SetLambda(asCScriptNode *funcDecl)
{
	asASSERT(funcDecl && funcDecl->nodeType == snFunction);
	asASSERT(bc.GetLastInstr() == -1);

	Clear();
	type.SetUndefinedFuncHandle(bc.GetEngine());
	exprNode = funcDecl;
}

bool asCExprContext::IsLambda() const
{
	if (type.IsUndefinedFuncHandle() && exprNode && exprNode->nodeType == snFunction)
		return true;

	return false;
}

void asCExprContext::SetVoidExpression()
{
	Clear();
	type.SetVoid();
	isVoidExpression = true;
}

bool asCExprContext::IsVoidExpression() const
{
	if (isVoidExpression && type.IsVoid() && exprNode == 0)
		return true;

	return false;
}

void asCExprContext::SetAnonymousInitList(asCScriptNode *initList, asCScriptCode *script)
{
	Clear();
	exprNode = initList;
	origCode = script;
	isAnonymousInitList = true;
}

bool asCExprContext::IsAnonymousInitList() const
{
	if (isAnonymousInitList && exprNode && exprNode->nodeType == snInitList)
		return true;

	return false;
}

void asCExprContext::Copy(asCExprContext *other)
{
	type                = other->type;
	property_get        = other->property_get;
	property_set        = other->property_set;
	property_const      = other->property_const;
	property_handle     = other->property_handle;
	property_ref        = other->property_ref;
	property_arg        = other->property_arg;
	exprNode            = other->exprNode;
	methodName          = other->methodName;
	enumValue           = other->enumValue;
	isVoidExpression    = other->isVoidExpression;
	isCleanArg          = other->isCleanArg;
	isAnonymousInitList = other->isAnonymousInitList;
	origCode            = other->origCode;

	// Do not copy the origExpr member	
}

void asCExprContext::Merge(asCExprContext *after)
{
	// Overwrite properties with the expression that comes after
	Copy(after);

	// Clean the properties in 'after' that have now moved into 
	// this structure so they are not cleaned up accidentally
	after->property_arg = 0;
}



END_AS_NAMESPACE

#endif // AS_NO_COMPILER



