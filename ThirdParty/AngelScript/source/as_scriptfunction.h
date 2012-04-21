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
// as_scriptfunction.h
//
// A container for a compiled script function
//



#ifndef AS_SCRIPTFUNCTION_H
#define AS_SCRIPTFUNCTION_H

#include "as_config.h"
#include "as_string.h"
#include "as_array.h"
#include "as_datatype.h"
#include "as_atomic.h"

BEGIN_AS_NAMESPACE

class asCScriptEngine;
class asCModule;
class asCConfigGroup;
class asCGlobalProperty;

struct asSScriptVariable
{
	asCString   name;
	asCDataType type;
	int         stackOffset;
	asUINT      declaredAtProgramPos;
};

enum asEObjVarInfoOption
{
	asOBJ_UNINIT,
	asOBJ_INIT,
	asBLOCK_BEGIN,
	asBLOCK_END
};

struct asSObjectVariableInfo
{
	asUINT programPos;
	int    variableOffset;
	asUINT option;
};

struct asSSystemFunctionInterface;

// TODO: GetModuleName should be removed. A function won't belong to a specific module anymore
//       as the function can be removed from the module, but still remain alive. For example
//       for dynamically generated functions held by a function pointer.

// TODO: Might be interesting to allow enumeration of accessed global variables, and 
//       also functions/methods that are being called. This could be used to build a 
//       code database with call graphs, etc.

// TODO: runtime optimize: The GC should only be notified of the script function when the last module
//                         removes it from the scope. Must make sure it is only added to the GC once
//                         in case the function is added to another module after the GC already knows 
//                         about the function.

void RegisterScriptFunction(asCScriptEngine *engine);

class asCScriptFunction : public asIScriptFunction
{
public:
	// From asIScriptFunction
	asIScriptEngine     *GetEngine() const;

	// Memory management
	int AddRef() const;
	int Release() const;

	int                  GetId() const;
	asEFuncType          GetFuncType() const;
	const char          *GetModuleName() const;
	asIObjectType       *GetObjectType() const;
	const char          *GetObjectName() const;
	const char          *GetName() const;
	const char          *GetNamespace() const;
	const char          *GetDeclaration(bool includeObjectName = true, bool includeNamespace = false) const;
	const char          *GetScriptSectionName() const;
	const char          *GetConfigGroup() const;
	asDWORD              GetAccessMask() const;
	bool                 IsReadOnly() const;
	bool                 IsPrivate() const;
	bool                 IsFinal() const;
	bool                 IsOverride() const;
	bool                 IsShared() const;

	asUINT               GetParamCount() const;
	int                  GetParamTypeId(asUINT index, asDWORD *flags = 0) const;
	int                  GetReturnTypeId() const;

	// Debug information
	asUINT               GetVarCount() const;
	int                  GetVar(asUINT index, const char **name, int *typeId = 0) const;
	const char *         GetVarDecl(asUINT index) const;
	int                  FindNextLineWithCode(int line) const;

	// For JIT compilation
	asDWORD             *GetByteCode(asUINT *length = 0);

	// User data
	void                *SetUserData(void *userData);
	void                *GetUserData() const;

public:
	//-----------------------------------
	// Internal methods

	asCScriptFunction(asCScriptEngine *engine, asCModule *mod, asEFuncType funcType);
	~asCScriptFunction();

	void      DestroyInternal();

	void      AddVariable(asCString &name, asCDataType &type, int stackOffset);

	int       GetSpaceNeededForArguments();
	int       GetSpaceNeededForReturnValue();
	asCString GetDeclarationStr(bool includeObjectName = true, bool includeNamespace = false) const;
	int       GetLineNumber(int programPosition);
	void      ComputeSignatureId();
	bool      IsSignatureEqual(const asCScriptFunction *func) const;
	bool      IsSignatureExceptNameEqual(const asCScriptFunction *func) const;
	bool      IsSignatureExceptNameEqual(const asCDataType &retType, const asCArray<asCDataType> &paramTypes, const asCArray<asETypeModifiers> &inOutFlags, const asCObjectType *type, bool isReadOnly) const;
	bool      IsSignatureExceptNameAndReturnTypeEqual(const asCArray<asCDataType> &paramTypes, const asCArray<asETypeModifiers> &inOutFlags, const asCObjectType *type, bool isReadOnly) const;

	bool      DoesReturnOnStack() const;

	void      JITCompile();

	void      AddReferences();
	void      ReleaseReferences();


	asCGlobalProperty *GetPropertyByGlobalVarPtr(void *gvarPtr);

	// GC methods
	int  GetRefCount();
	void SetFlag();
	bool GetFlag();
	void EnumReferences(asIScriptEngine *engine);
	void ReleaseAllHandles(asIScriptEngine *engine);

public:
	//-----------------------------------
	// Properties

	mutable asCAtomic            refCount;
	mutable bool                 gcFlag;
	asCScriptEngine             *engine;
	asCModule                   *module;

	void                        *userData;

	// Function signature
	asCString                    name;
	asCDataType                  returnType;
	asCArray<asCDataType>        parameterTypes;
	asCArray<asETypeModifiers>   inOutFlags;
	asCArray<asCString *>        defaultArgs;
	bool                         isReadOnly;
	bool                         isPrivate;
	bool                         isFinal;
	bool                         isOverride;
	asCObjectType               *objectType;
	int                          signatureId;

	int                          id;

	asEFuncType                  funcType;
	asDWORD                      accessMask;
	bool                         isShared;

	// TODO: optimize: The namespace should be stored as an integer id. This  
	//                 will use less space and provide quicker comparisons.
	asCString                    nameSpace;

	// Used by asFUNC_SCRIPT
	asCArray<asDWORD>               byteCode;
	// The stack space needed for the local variables
	asDWORD                         variableSpace;

	// These hold information objects and function pointers, including temporary
	// variables used by exception handler and when saving bytecode
	asCArray<asCObjectType*>        objVariableTypes;
	asCArray<asCScriptFunction*>    funcVariableTypes;
	asCArray<int>	                objVariablePos;
	// The first variables in above array are allocated on the heap, the rest on the stack.
	// This variable shows how many are on the heap.
	asUINT                          objVariablesOnHeap;

	// Holds information on scope for object variables on the stack
	asCArray<asSObjectVariableInfo> objVariableInfo;

	// Holds information on explicitly declared variables
	asCArray<asSScriptVariable*>    variables;        // debug info

	int                             stackNeeded;
	asCArray<int>                   lineNumbers;      // debug info
	int                             scriptSectionIdx; // debug info
	bool                            dontCleanUpOnException;   // Stub functions don't own the object and parameters

	// Used by asFUNC_VIRTUAL
	int                          vfTableIdx;

	// Used by asFUNC_SYSTEM
	asSSystemFunctionInterface  *sysFuncIntf;

    // JIT compiled code of this function
    asJITFunction                jitFunction;
};

END_AS_NAMESPACE

#endif
