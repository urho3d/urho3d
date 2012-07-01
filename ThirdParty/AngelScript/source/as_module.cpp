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
// as_module.cpp
//
// A class that holds a script module
//

#include "as_config.h"
#include "as_module.h"
#include "as_builder.h"
#include "as_context.h"
#include "as_texts.h"

BEGIN_AS_NAMESPACE

// internal
asCModule::asCModule(const char *name, asCScriptEngine *engine)
{
	this->name     = name;
	this->engine   = engine;

	userData = 0;
	builder = 0;
	isGlobalVarInitialized = false;

	accessMask = 1;
}

// internal
asCModule::~asCModule()
{
	InternalReset();

	if( builder ) 
	{
		asDELETE(builder,asCBuilder);
		builder = 0;
	}

	// Clean the user data
	if( userData && engine->cleanModuleFunc )
		engine->cleanModuleFunc(this);

	// Remove the module from the engine
	if( engine )
	{
		if( engine->lastModule == this )
			engine->lastModule = 0;

		engine->scriptModules.RemoveValue(this);
	}
}

// interface
void *asCModule::SetUserData(void *data)
{
	void *oldData = userData;
	userData = data;
	return oldData;
}

// interface
void *asCModule::GetUserData() const
{
	return userData;
}

// interface
asIScriptEngine *asCModule::GetEngine() const
{
	return engine;
}

// interface
void asCModule::SetName(const char *name)
{
	this->name = name;
}

// interface
const char *asCModule::GetName() const
{
	return name.AddressOf();
}

// interface
int asCModule::SetDefaultNamespace(const char *nameSpace)
{
	// TODO: cleanup: This function is similar to asCScriptEngine::SetDefaultNamespace. Can we reuse the code?
	if( nameSpace == 0 )
		return asINVALID_ARG;

	defaultNamespace = nameSpace;
	if( defaultNamespace != "" )
	{
		// Make sure the namespace is composed of alternating identifier and ::
		size_t pos = 0;
		bool expectIdentifier = true;
		size_t len;
		eTokenType t = ttIdentifier;

		for( ; pos < defaultNamespace.GetLength(); pos += len )
		{
			t = engine->tok.GetToken(defaultNamespace.AddressOf() + pos, defaultNamespace.GetLength() - pos, &len);
			if( (expectIdentifier && t != ttIdentifier) || (!expectIdentifier && t != ttScope) )
				return asINVALID_DECLARATION;

			expectIdentifier = !expectIdentifier;
		}

		// If the namespace ends with :: then strip it off
		if( t == ttScope )
			defaultNamespace.SetLength(defaultNamespace.GetLength()-2);
	}

	return 0;
}

// interface
int asCModule::AddScriptSection(const char *name, const char *code, size_t codeLength, int lineOffset)
{
#ifdef AS_NO_COMPILER
	UNUSED_VAR(name);
	UNUSED_VAR(code);
	UNUSED_VAR(codeLength);
	UNUSED_VAR(lineOffset);
	return asNOT_SUPPORTED;
#else
	if( !builder )
	{
		builder = asNEW(asCBuilder)(engine, this);
		if( builder == 0 )
			return asOUT_OF_MEMORY;
	}

	return builder->AddCode(name, code, (int)codeLength, lineOffset, (int)engine->GetScriptSectionNameIndex(name ? name : ""), engine->ep.copyScriptSections);
#endif
}

// internal
void asCModule::JITCompile()
{
	for (unsigned int i = 0; i < scriptFunctions.GetLength(); i++)
	{
		scriptFunctions[i]->JITCompile();
	}
}

// interface
int asCModule::Build()
{
#ifdef AS_NO_COMPILER
	return asNOT_SUPPORTED;
#else
	// Only one thread may build at one time
	// TODO: It should be possible to have multiple threads perform compilations
	int r = engine->RequestBuild();
	if( r < 0 )
		return r;

	engine->PrepareEngine();
	if( engine->configFailed )
	{
		engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, TXT_INVALID_CONFIGURATION);
		engine->BuildCompleted();
		return asINVALID_CONFIGURATION;
	}

 	InternalReset();

	if( !builder )
	{
		engine->BuildCompleted();
		return asSUCCESS;
	}

	// Compile the script
	r = builder->Build();
	asDELETE(builder,asCBuilder);
	builder = 0;
	
	if( r < 0 )
	{
		// Reset module again
		InternalReset();

		engine->BuildCompleted();
		return r;
	}

    JITCompile();

 	engine->PrepareEngine();
	engine->BuildCompleted();

	// Initialize global variables
	if( r >= 0 && engine->ep.initGlobalVarsAfterBuild )
		r = ResetGlobalVars(0);

	return r;
#endif
}

// interface
int asCModule::ResetGlobalVars(asIScriptContext *ctx)
{
	if( isGlobalVarInitialized ) 
		CallExit();

	return CallInit(ctx);
}

#ifdef AS_DEPRECATED
// Deprecated since 2.24.0 - 2012-05-20
// interface
int asCModule::GetFunctionIdByIndex(asUINT index) const
{
	if( index >= globalFunctions.GetLength() )
		return asNO_FUNCTION;

	return globalFunctions[index]->id;
}
#endif

// interface
asIScriptFunction *asCModule::GetFunctionByIndex(asUINT index) const
{
	if( index >= globalFunctions.GetLength() )
		return 0;

	return globalFunctions[index];
}

// internal
int asCModule::CallInit(asIScriptContext *myCtx)
{
	if( isGlobalVarInitialized ) 
		return asERROR;

	// Each global variable needs to be cleared individually
	asUINT n;
	for( n = 0; n < scriptGlobals.GetLength(); n++ )
	{
		if( scriptGlobals[n] )
		{
			memset(scriptGlobals[n]->GetAddressOfValue(), 0, sizeof(asDWORD)*scriptGlobals[n]->type.GetSizeOnStackDWords());
		}
	}

	// Call the init function for each of the global variables
	asIScriptContext *ctx = myCtx;
	int r = asEXECUTION_FINISHED;
	for( n = 0; n < scriptGlobals.GetLength() && r == asEXECUTION_FINISHED; n++ )
	{
		if( scriptGlobals[n]->GetInitFunc() )
		{
			if( ctx == 0 )
			{
				r = engine->CreateContext(&ctx, true);
				if( r < 0 )
					break;
			}

			r = ctx->Prepare(scriptGlobals[n]->GetInitFunc());
			if( r >= 0 )
			{
				r = ctx->Execute();
				if( r != asEXECUTION_FINISHED )
				{
					asCString msg;
					msg.Format(TXT_FAILED_TO_INITIALIZE_s, scriptGlobals[n]->name.AddressOf());
					asCScriptFunction *func = scriptGlobals[n]->GetInitFunc();

					engine->WriteMessage(func->scriptSectionIdx >= 0 ? engine->scriptSectionNames[func->scriptSectionIdx]->AddressOf() : "",
										 func->GetLineNumber(0) & 0xFFFFF, 
										 func->GetLineNumber(0) >> 20,
										 asMSGTYPE_ERROR,
										 msg.AddressOf());
										 
					if( r == asEXECUTION_EXCEPTION )
					{
						const asIScriptFunction *function = ctx->GetExceptionFunction();

						msg.Format(TXT_EXCEPTION_s_IN_s, ctx->GetExceptionString(), function->GetDeclaration());

						engine->WriteMessage(function->GetScriptSectionName(), 
						                     ctx->GetExceptionLineNumber(), 
											 0,
											 asMSGTYPE_INFORMATION,
											 msg.AddressOf());
					}
				}
			}
		}
	}

	if( ctx && !myCtx )
	{
		ctx->Release();
		ctx = 0;
	}

	// Even if the initialization failed we need to set the 
	// flag that the variables have been initialized, otherwise
	// the module won't free those variables that really were 
	// initialized.
	isGlobalVarInitialized = true;

	if( r != asEXECUTION_FINISHED )
		return asINIT_GLOBAL_VARS_FAILED;

	return asSUCCESS;
}

// internal
void asCModule::CallExit()
{
	if( !isGlobalVarInitialized ) return;

	for( size_t n = 0; n < scriptGlobals.GetLength(); n++ )
	{
		if( scriptGlobals[n]->type.IsObject() )
		{
			void **obj = (void**)scriptGlobals[n]->GetAddressOfValue();
			if( *obj )
			{
				asCObjectType *ot = scriptGlobals[n]->type.GetObjectType();

				if( ot->flags & asOBJ_REF )
				{
					asASSERT( (ot->flags & asOBJ_NOCOUNT) || ot->beh.release );
					if( ot->beh.release )
						engine->CallObjectMethod(*obj, ot->beh.release);
				}
				else
				{
					if( ot->beh.destruct )
						engine->CallObjectMethod(*obj, ot->beh.destruct);

					engine->CallFree(*obj);
				}

				// Set the address to 0 as someone might try to access the variable afterwards
				*obj = 0;
			}
		}
	}

	isGlobalVarInitialized = false;
}

// internal
void asCModule::InternalReset()
{
	CallExit();

	size_t n;

	// Release all global functions
	for( n = 0; n < globalFunctions.GetLength(); n++ )
	{
		if( globalFunctions[n] )
			globalFunctions[n]->Release();
	}
	globalFunctions.SetLength(0);

	// First release all compiled functions
	for( n = 0; n < scriptFunctions.GetLength(); n++ )
	{
		if( scriptFunctions[n] )
		{
			// Remove the module reference in the functions
			scriptFunctions[n]->module = 0;
			scriptFunctions[n]->Release();
		}
	}
	scriptFunctions.SetLength(0);

	// Release the global properties declared in the module
	for( n = 0; n < scriptGlobals.GetLength(); n++ )
		scriptGlobals[n]->Release();
	scriptGlobals.SetLength(0);

	UnbindAllImportedFunctions();

	// Free bind information
	for( n = 0; n < bindInformations.GetLength(); n++ )
	{
		if( bindInformations[n] )
		{
			asUINT id = bindInformations[n]->importedFunctionSignature->id & 0xFFFF;
			engine->importedFunctions[id] = 0;
			engine->freeImportedFunctionIdxs.PushLast(id);

			asDELETE(bindInformations[n]->importedFunctionSignature, asCScriptFunction);
			asDELETE(bindInformations[n], sBindInfo);
		}
	}
	bindInformations.SetLength(0);

	// Free declared types, including classes, typedefs, and enums
	for( n = 0; n < classTypes.GetLength(); n++ )
		classTypes[n]->Release();
	classTypes.SetLength(0);
	for( n = 0; n < enumTypes.GetLength(); n++ )
		enumTypes[n]->Release();
	enumTypes.SetLength(0);
	for( n = 0; n < typeDefs.GetLength(); n++ )
		typeDefs[n]->Release();
	typeDefs.SetLength(0);

	// Free funcdefs
	for( n = 0; n < funcDefs.GetLength(); n++ )
	{
		// TODO: funcdefs: These may be shared between modules, so we can't just remove them
		engine->funcDefs.RemoveValue(funcDefs[n]);
		funcDefs[n]->Release();
	}
	funcDefs.SetLength(0);
}

#ifdef AS_DEPRECATED
// Deprecated since 2.24.0 - 2012-05-20
// interface
int asCModule::GetFunctionIdByName(const char *name) const
{
	// TODO: optimize: Improve linear search
	// Find the function id
	int id = -1;
	for( size_t n = 0; n < globalFunctions.GetLength(); n++ )
	{
		if( globalFunctions[n]->name == name &&
			globalFunctions[n]->nameSpace == defaultNamespace )
		{
			if( id == -1 )
				id = globalFunctions[n]->id;
			else
				return asMULTIPLE_FUNCTIONS;
		}
	}

	if( id == -1 ) return asNO_FUNCTION;

	return id;
}
#endif

// interface
asIScriptFunction *asCModule::GetFunctionByName(const char *name) const
{
	asIScriptFunction *func = 0;
	for( size_t n = 0; n < globalFunctions.GetLength(); n++ )
	{
		if( globalFunctions[n]->name == name &&
			globalFunctions[n]->nameSpace == defaultNamespace )
		{
			if( func == 0 )
				func = globalFunctions[n];
			else
			{
				// Multiple functions with the same name
				return 0;
			}
		}
	}

	return func;
}

// interface
asUINT asCModule::GetImportedFunctionCount() const
{
	return (asUINT)bindInformations.GetLength();
}

// interface
int asCModule::GetImportedFunctionIndexByDecl(const char *decl) const
{
	asCBuilder bld(engine, const_cast<asCModule*>(this));

	asCScriptFunction func(engine, const_cast<asCModule*>(this), asFUNC_DUMMY);
	bld.ParseFunctionDeclaration(0, decl, &func, false);

	// TODO: optimize: Improve linear search
	// Search script functions for matching interface
	int id = -1;
	for( asUINT n = 0; n < bindInformations.GetLength(); ++n )
	{
		if( func.name == bindInformations[n]->importedFunctionSignature->name && 
			func.returnType == bindInformations[n]->importedFunctionSignature->returnType &&
			func.parameterTypes.GetLength() == bindInformations[n]->importedFunctionSignature->parameterTypes.GetLength() )
		{
			bool match = true;
			for( asUINT p = 0; p < func.parameterTypes.GetLength(); ++p )
			{
				if( func.parameterTypes[p] != bindInformations[n]->importedFunctionSignature->parameterTypes[p] )
				{
					match = false;
					break;
				}
			}

			if( match )
			{
				if( id == -1 )
					id = n;
				else
					return asMULTIPLE_FUNCTIONS;
			}
		}
	}

	if( id == -1 ) return asNO_FUNCTION;

	return id;
}

// interface
asUINT asCModule::GetFunctionCount() const
{
	return (asUINT)globalFunctions.GetLength();
}

#ifdef AS_DEPRECATED
// Deprecated since 2.24.0 - 2012-05-20
// interface
int asCModule::GetFunctionIdByDecl(const char *decl) const
{
	asCBuilder bld(engine, const_cast<asCModule*>(this));

	asCScriptFunction func(engine, const_cast<asCModule*>(this), asFUNC_DUMMY);
	int r = bld.ParseFunctionDeclaration(0, decl, &func, false);
	if( r < 0 )
		return asINVALID_DECLARATION;

	// Use the defaultNamespace implicitly unless an explicit namespace has been provided
	asCString ns = func.nameSpace == "" ? defaultNamespace : func.nameSpace;

	// TODO: optimize: Improve linear search
	// Search script functions for matching interface
	int id = -1;
	for( size_t n = 0; n < globalFunctions.GetLength(); ++n )
	{
		if( globalFunctions[n]->objectType == 0 && 
			func.name == globalFunctions[n]->name && 
			func.returnType == globalFunctions[n]->returnType &&
			func.parameterTypes.GetLength() == globalFunctions[n]->parameterTypes.GetLength() &&
			ns == globalFunctions[n]->nameSpace )
		{
			bool match = true;
			for( size_t p = 0; p < func.parameterTypes.GetLength(); ++p )
			{
				if( func.parameterTypes[p] != globalFunctions[n]->parameterTypes[p] )
				{
					match = false;
					break;
				}
			}

			if( match )
			{
				if( id == -1 )
					id = globalFunctions[n]->id;
				else
					return asMULTIPLE_FUNCTIONS;
			}
		}
	}

	if( id == -1 ) return asNO_FUNCTION;

	return id;
}
#endif

// interface
asIScriptFunction *asCModule::GetFunctionByDecl(const char *decl) const
{
	asCBuilder bld(engine, const_cast<asCModule*>(this));

	asCScriptFunction func(engine, const_cast<asCModule*>(this), asFUNC_DUMMY);
	int r = bld.ParseFunctionDeclaration(0, decl, &func, false);
	if( r < 0 )
	{
		// Invalid declaration
		// TODO: Write error to message stream
		return 0;
	}

	// Use the defaultNamespace implicitly unless an explicit namespace has been provided
	asCString ns = func.nameSpace == "" ? defaultNamespace : func.nameSpace;

	// TODO: optimize: Improve linear search
	// Search script functions for matching interface
	asIScriptFunction *f = 0;
	for( size_t n = 0; n < globalFunctions.GetLength(); ++n )
	{
		if( globalFunctions[n]->objectType  == 0 && 
			func.name                       == globalFunctions[n]->name && 
			func.returnType                 == globalFunctions[n]->returnType &&
			func.parameterTypes.GetLength() == globalFunctions[n]->parameterTypes.GetLength() &&
			ns                              == globalFunctions[n]->nameSpace )
		{
			bool match = true;
			for( size_t p = 0; p < func.parameterTypes.GetLength(); ++p )
			{
				if( func.parameterTypes[p] != globalFunctions[n]->parameterTypes[p] )
				{
					match = false;
					break;
				}
			}

			if( match )
			{
				if( f == 0 )
					f = globalFunctions[n];
				else
					// Multiple functions
					return 0;
			}
		}
	}

	return f;
}

// interface
asUINT asCModule::GetGlobalVarCount() const
{
	return (asUINT)scriptGlobals.GetLength();
}

// interface
int asCModule::GetGlobalVarIndexByName(const char *name) const
{
	// Find the global var id
	int id = -1;
	for( size_t n = 0; n < scriptGlobals.GetLength(); n++ )
	{
		if( scriptGlobals[n]->name == name &&
			scriptGlobals[n]->nameSpace == defaultNamespace )
		{
			id = (int)n;
			break;
		}
	}

	if( id == -1 ) return asNO_GLOBAL_VAR;

	return id;
}

// interface
int asCModule::RemoveGlobalVar(asUINT index)
{
	if( index >= scriptGlobals.GetLength() )
		return asINVALID_ARG;

	scriptGlobals[index]->Release();
	scriptGlobals.RemoveIndex(index);

	return 0;
}

// interface
int asCModule::GetGlobalVarIndexByDecl(const char *decl) const
{
	asCBuilder bld(engine, const_cast<asCModule*>(this));

	asCString name, nameSpace;
	asCDataType dt;
	bld.ParseVariableDeclaration(decl, defaultNamespace, name, nameSpace, dt);

	// TODO: optimize: Improve linear search
	// Search global variables for a match
	int id = -1;
	for( size_t n = 0; n < scriptGlobals.GetLength(); ++n )
	{
		if( name      == scriptGlobals[n]->name && 
			nameSpace == scriptGlobals[n]->nameSpace &&
			dt        == scriptGlobals[n]->type )
		{
			id = (int)n;
			break;
		}
	}

	if( id == -1 ) return asNO_GLOBAL_VAR;

	return id;
}

// interface
void *asCModule::GetAddressOfGlobalVar(asUINT index)
{
	if( index >= scriptGlobals.GetLength() )
		return 0;

	// For object variables it's necessary to dereference the pointer to get the address of the value
	if( scriptGlobals[index]->type.IsObject() && 
		!scriptGlobals[index]->type.IsObjectHandle() )
		return *(void**)(scriptGlobals[index]->GetAddressOfValue());

	return (void*)(scriptGlobals[index]->GetAddressOfValue());
}

// interface
const char *asCModule::GetGlobalVarDeclaration(asUINT index, bool includeNamespace) const
{
	if( index >= scriptGlobals.GetLength() )
		return 0;

	asCGlobalProperty *prop = scriptGlobals[index];

	asCString *tempString = &asCThreadManager::GetLocalData()->string;
	*tempString = prop->type.Format();
	*tempString += " ";
	if( includeNamespace )
		*tempString += prop->nameSpace + "::";
	*tempString += prop->name;

	return tempString->AddressOf();
}

// interface
int asCModule::GetGlobalVar(asUINT index, const char **name, const char **nameSpace, int *typeId, bool *isConst) const
{
	if( index >= scriptGlobals.GetLength() )
		return asINVALID_ARG;

	asCGlobalProperty *prop = scriptGlobals[index];

	if( name )
		*name = prop->name.AddressOf();
	if( nameSpace )
		*nameSpace = prop->nameSpace.AddressOf();
	if( typeId )
		*typeId = engine->GetTypeIdFromDataType(prop->type);
	if( isConst )
		*isConst = prop->type.IsReadOnly();

	return asSUCCESS;
}

// interface
asUINT asCModule::GetObjectTypeCount() const
{
	return (asUINT)classTypes.GetLength();
}

// interface 
asIObjectType *asCModule::GetObjectTypeByIndex(asUINT index) const
{
	if( index >= classTypes.GetLength() ) 
		return 0;

	return classTypes[index];
}

// interface
asIObjectType *asCModule::GetObjectTypeByName(const char *name) const
{
	for( asUINT n = 0; n < classTypes.GetLength(); n++ )
	{
		if( classTypes[n] &&
			classTypes[n]->name == name &&
			classTypes[n]->nameSpace == defaultNamespace )
			return classTypes[n];
	}

	return 0;
}

// interface
int asCModule::GetTypeIdByDecl(const char *decl) const
{
	asCDataType dt;
	asCBuilder bld(engine, const_cast<asCModule*>(this));
	int r = bld.ParseDataType(decl, &dt, defaultNamespace);
	if( r < 0 )
		return asINVALID_TYPE;

	return engine->GetTypeIdFromDataType(dt);
}

// interface
asUINT asCModule::GetEnumCount() const
{
	return (asUINT)enumTypes.GetLength();
}

// interface
const char *asCModule::GetEnumByIndex(asUINT index, int *enumTypeId, const char **nameSpace) const
{
	if( index >= enumTypes.GetLength() )
		return 0;

	if( enumTypeId )
		*enumTypeId = GetTypeIdByDecl(enumTypes[index]->name.AddressOf());

	if( nameSpace )
		*nameSpace = enumTypes[index]->name.AddressOf();

	return enumTypes[index]->name.AddressOf();
}

// interface
int asCModule::GetEnumValueCount(int enumTypeId) const
{
	asCDataType dt = engine->GetDataTypeFromTypeId(enumTypeId);
	asCObjectType *t = dt.GetObjectType();
	if( t == 0 || !(t->GetFlags() & asOBJ_ENUM) ) 
		return asINVALID_TYPE;

	return (int)t->enumValues.GetLength();
}

// interface
const char *asCModule::GetEnumValueByIndex(int enumTypeId, asUINT index, int *outValue) const
{
	asCDataType dt = engine->GetDataTypeFromTypeId(enumTypeId);
	asCObjectType *t = dt.GetObjectType();
	if( t == 0 || !(t->GetFlags() & asOBJ_ENUM) ) 
		return 0;

	if( index >= t->enumValues.GetLength() )
		return 0;

	if( outValue )
		*outValue = t->enumValues[index]->value;

	return t->enumValues[index]->name.AddressOf();
}

// interface
asUINT asCModule::GetTypedefCount() const
{
	return (asUINT)typeDefs.GetLength();
}

// interface
const char *asCModule::GetTypedefByIndex(asUINT index, int *typeId, const char **nameSpace) const
{
	if( index >= typeDefs.GetLength() )
		return 0;

	if( typeId )
		*typeId = GetTypeIdByDecl(typeDefs[index]->name.AddressOf());

	if( nameSpace )
		*nameSpace = typeDefs[index]->nameSpace.AddressOf();

	return typeDefs[index]->name.AddressOf();
}


// internal
int asCModule::GetNextImportedFunctionId()
{
	// TODO: multithread: This will break if one thread if freeing a module, while another is being compiled
	if( engine->freeImportedFunctionIdxs.GetLength() )
		return FUNC_IMPORTED | (asUINT)engine->freeImportedFunctionIdxs[engine->freeImportedFunctionIdxs.GetLength()-1];

	return FUNC_IMPORTED | (asUINT)engine->importedFunctions.GetLength();
}

// internal
int asCModule::AddScriptFunction(int sectionIdx, int id, const char *name, const asCDataType &returnType, asCDataType *params, asETypeModifiers *inOutFlags, asCString **defaultArgs, int paramCount, bool isInterface, asCObjectType *objType, bool isConstMethod, bool isGlobalFunction, bool isPrivate, bool isFinal, bool isOverride, bool isShared, const asCString &ns)
{
	asASSERT(id >= 0);

	// Store the function information
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine, this, isInterface ? asFUNC_INTERFACE : asFUNC_SCRIPT);
	if( func == 0 )
		return asOUT_OF_MEMORY;

	func->name             = name;
	func->nameSpace        = ns;
	func->id               = id;
	func->returnType       = returnType;
	func->scriptSectionIdx = sectionIdx;
	for( int n = 0; n < paramCount; n++ )
	{
		func->parameterTypes.PushLast(params[n]);
		func->inOutFlags.PushLast(inOutFlags[n]);
		func->defaultArgs.PushLast(defaultArgs[n]);
	}
	func->objectType = objType;
	func->isReadOnly = isConstMethod;
	func->isPrivate  = isPrivate;
	func->isFinal    = isFinal;
	func->isOverride = isOverride;
	// All methods of shared objects are also shared
	if( objType && objType->IsShared() )
		isShared = true;
	func->isShared   = isShared;

	// Verify that we are not assigning either the final or override specifier(s) if we are registering a non-member function
	asASSERT( !(!objType && isFinal) );
	asASSERT( !(!objType && isOverride) );

	// The script function's refCount was initialized to 1
	scriptFunctions.PushLast(func);
	engine->SetScriptFunction(func);

	// Compute the signature id
	if( objType )
		func->ComputeSignatureId();

	// Add reference
	if( isGlobalFunction )
	{
		globalFunctions.PushLast(func);
		func->AddRef();
	}

	return 0;
}

// internal 
int asCModule::AddScriptFunction(asCScriptFunction *func)
{
	scriptFunctions.PushLast(func);
	func->AddRef();
	engine->SetScriptFunction(func);

	return 0;
}

// internal
int asCModule::AddImportedFunction(int id, const char *name, const asCDataType &returnType, asCDataType *params, asETypeModifiers *inOutFlags, int paramCount, const asCString &moduleName)
{
	asASSERT(id >= 0);

	// Store the function information
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine, this, asFUNC_IMPORTED);
	if( func == 0 )
		return asOUT_OF_MEMORY;

	func->name       = name;
	func->id         = id;
	func->returnType = returnType;
	for( int n = 0; n < paramCount; n++ )
	{
		func->parameterTypes.PushLast(params[n]);
		func->inOutFlags.PushLast(inOutFlags[n]);
	}
	func->objectType = 0;

	sBindInfo *info = asNEW(sBindInfo);
	if( info == 0 )
		return asOUT_OF_MEMORY;

	info->importedFunctionSignature = func;
	info->boundFunctionId = -1;
	info->importFromModule = moduleName;
	bindInformations.PushLast(info);

	// Add the info to the array in the engine
	if( engine->freeImportedFunctionIdxs.GetLength() )
		engine->importedFunctions[engine->freeImportedFunctionIdxs.PopLast()] = info;
	else
		engine->importedFunctions.PushLast(info);

	return 0;
}

// internal
asCScriptFunction *asCModule::GetImportedFunction(int index) const
{
	return bindInformations[index]->importedFunctionSignature;
}

// interface
int asCModule::BindImportedFunction(asUINT index, asIScriptFunction *func)
{
	// First unbind the old function
	int r = UnbindImportedFunction(index);
	if( r < 0 ) return r;

	// Must verify that the interfaces are equal
	asCScriptFunction *dst = GetImportedFunction(index);
	if( dst == 0 ) return asNO_FUNCTION;

	if( func == 0 )
		return asINVALID_ARG;

	asCScriptFunction *src = engine->GetScriptFunction(func->GetId());
	if( src == 0 ) 
		return asNO_FUNCTION;

	// Verify return type
	if( dst->returnType != src->returnType )
		return asINVALID_INTERFACE;

	if( dst->parameterTypes.GetLength() != src->parameterTypes.GetLength() )
		return asINVALID_INTERFACE;

	for( size_t n = 0; n < dst->parameterTypes.GetLength(); ++n )
	{
		if( dst->parameterTypes[n] != src->parameterTypes[n] )
			return asINVALID_INTERFACE;
	}

	bindInformations[index]->boundFunctionId = src->GetId();
	src->AddRef();

	return asSUCCESS;
}

// interface
int asCModule::UnbindImportedFunction(asUINT index)
{
	if( index >= bindInformations.GetLength() )
		return asINVALID_ARG;

	// Remove reference to old module
	if( bindInformations[index] )
	{
		int oldFuncID = bindInformations[index]->boundFunctionId;
		if( oldFuncID != -1 )
		{
			bindInformations[index]->boundFunctionId = -1;
			engine->scriptFunctions[oldFuncID]->Release();
		}
	}

	return asSUCCESS;
}

// interface
const char *asCModule::GetImportedFunctionDeclaration(asUINT index) const
{
	asCScriptFunction *func = GetImportedFunction(index);
	if( func == 0 ) return 0;

	asCString *tempString = &asCThreadManager::GetLocalData()->string;
	*tempString = func->GetDeclarationStr();

	return tempString->AddressOf();
}

// interface
const char *asCModule::GetImportedFunctionSourceModule(asUINT index) const
{
	if( index >= bindInformations.GetLength() )
		return 0;

	return bindInformations[index]->importFromModule.AddressOf();
}

// inteface
int asCModule::BindAllImportedFunctions()
{
	bool notAllFunctionsWereBound = false;

	// Bind imported functions
	int c = GetImportedFunctionCount();
	for( int n = 0; n < c; ++n )
	{
		asCScriptFunction *importFunc = GetImportedFunction(n);
		if( importFunc == 0 ) return asERROR;

		asCString str = importFunc->GetDeclarationStr();

		// Get module name from where the function should be imported
		const char *moduleName = GetImportedFunctionSourceModule(n);
		if( moduleName == 0 ) return asERROR;

		asCModule *srcMod = engine->GetModule(moduleName, false);
		asIScriptFunction *func = 0;
		if( srcMod )
			func = srcMod->GetFunctionByDecl(str.AddressOf());

		if( func == 0 )
			notAllFunctionsWereBound = true;
		else
		{
			if( BindImportedFunction(n, func) < 0 )
				notAllFunctionsWereBound = true;
		}
	}

	if( notAllFunctionsWereBound )
		return asCANT_BIND_ALL_FUNCTIONS;

	return asSUCCESS;
}

// interface
int asCModule::UnbindAllImportedFunctions()
{
	asUINT c = GetImportedFunctionCount();
	for( asUINT n = 0; n < c; ++n )
		UnbindImportedFunction(n);

	return asSUCCESS;
}

// internal
asCObjectType *asCModule::GetObjectType(const char *type, const asCString &ns)
{
	size_t n;

	// TODO: optimize: Improve linear search
	for( n = 0; n < classTypes.GetLength(); n++ )
		if( classTypes[n]->name == type &&
			classTypes[n]->nameSpace == ns )
			return classTypes[n];

	for( n = 0; n < enumTypes.GetLength(); n++ )
		if( enumTypes[n]->name == type && 
			enumTypes[n]->nameSpace == ns )
			return enumTypes[n];

	for( n = 0; n < typeDefs.GetLength(); n++ )
		if( typeDefs[n]->name == type && 
			typeDefs[n]->nameSpace == ns )
			return typeDefs[n];

	return 0;
}

// internal
asCGlobalProperty *asCModule::AllocateGlobalProperty(const char *name, const asCDataType &dt, const asCString &ns)
{
	asCGlobalProperty *prop = engine->AllocateGlobalProperty();
	prop->name = name;
	prop->nameSpace = ns;

	// Allocate the memory for this property based on its type
	prop->type = dt;
	prop->AllocateMemory();

	// Store the variable in the module scope (the reference count is already set to 1)
	scriptGlobals.PushLast(prop);

	return prop;
}

#ifdef AS_DEPRECATED
	// Deprecated since 2.23.0 - 2012-01-30

// internal
void asCModule::ResolveInterfaceIds(asCArray<void*> *substitutions)
{
	// For each of the interfaces declared in the script find identical interface in the engine.
	// If an identical interface was found then substitute the current id for the identical interface's id, 
	// then remove this interface declaration. If an interface was modified by the declaration, then 
	// retry the detection of identical interface for it since it may now match another.

	// For an interface to be equal to another the name and methods must match. If the interface
	// references another interface, then that must be checked as well, which can lead to circular references.

	// Example:
	//
	// interface A { void f(B@); }
	// interface B { void f(A@); void f(C@); }
	// interface C { void f(A@); }
	//
	// A1 equals A2 if and only if B1 equals B2
	// B1 equals B2 if and only if A1 equals A2 and C1 equals C2
	// C1 equals C2 if and only if A1 equals A2


	unsigned int i;

	// The interface can only be equal to interfaces declared in other modules. 
	// Interfaces registered by the application will conflict with this one if it has the same name.
	// This means that we only need to look for the interfaces in the engine->classTypes, but not in engine->objectTypes.
	asCArray<sObjectTypePair> equals;
	for( i = 0; i < classTypes.GetLength(); i++ )
	{
		asCObjectType *intf1 = classTypes[i];
		if( !intf1->IsInterface() )
			continue;

		// The interface may have been determined to be equal to another already
		bool found = false;
		for( unsigned int e = 0; e < equals.GetLength(); e++ )
		{
			if( equals[e].a == intf1 )
			{
				found = true;
				break;
			}
		}
		
		if( found )
			continue;

		for( unsigned int n = 0; n < engine->classTypes.GetLength(); n++ )
		{
			// Don't compare against self
			if( engine->classTypes[n] == intf1 )
				continue;
	
			asCObjectType *intf2 = engine->classTypes[n];

			// Assume the interface are equal, then validate this
			sObjectTypePair pair = {intf1,intf2};
			equals.PushLast(pair);

			if( AreInterfacesEqual(intf1, intf2, equals) )
				break;
			
			// Since they are not equal, remove them from the list again
			equals.PopLast();
		}
	}

	// For each of the interfaces that have been found to be equal we need to 
	// remove the new declaration and instead have the module use the existing one.
	for( i = 0; i < equals.GetLength(); i++ )
	{
		// Substitute the old object type from the module's class types
		unsigned int c;
		for( c = 0; c < classTypes.GetLength(); c++ )
		{
			if( classTypes[c] == equals[i].a )
			{
				if( substitutions )
				{
					substitutions->PushLast(equals[i].a);
					substitutions->PushLast(equals[i].b);
				}

				classTypes[c] = equals[i].b;
				equals[i].b->AddRef();
				break;
			}
		}

		// Remove the old object type from the engine's class types
		engine->classTypes.RemoveValue(equals[i].a);

		// Only interfaces in the module are using the type so far
		for( c = 0; c < classTypes.GetLength(); c++ )
		{
			if( classTypes[c]->IsInterface() )
			{
				asCObjectType *intf = classTypes[c];
				for( asUINT m = 0; m < intf->GetMethodCount(); m++ )
				{
					asCScriptFunction *func = engine->GetScriptFunction(intf->methods[m]);
					if( func )
					{
						// Check if it is the same type
						if( func->returnType.GetObjectType() == equals[i].a )
							func->returnType.SetObjectType(equals[i].b);
						// Look for template instances that uses the interface as subtype
						else if( func->returnType.IsTemplate() && 
							     func->returnType.GetSubType().GetObjectType() == equals[i].a )
						{
							// Find the originating template type
							asCObjectType *templ = 0;
							for( asUINT t = 0; t < engine->registeredObjTypes.GetLength(); t++ )
								if( (engine->registeredObjTypes[t]->flags & asOBJ_TEMPLATE) &&
									engine->registeredObjTypes[t]->name == func->returnType.GetObjectType()->name &&
									!engine->templateInstanceTypes.Exists(engine->registeredObjTypes[t]) )
								{
									templ = engine->registeredObjTypes[t];
									break;
								}

							asASSERT( templ );
							
							asCDataType subType = func->returnType.GetSubType();
							subType.SetObjectType(equals[i].b);
							func->returnType.SetObjectType(engine->GetTemplateInstanceType(templ, subType));
						}

						for( asUINT p = 0; p < func->GetParamCount(); p++ )
						{
							// Check if it is the same type
							if( func->parameterTypes[p].GetObjectType() == equals[i].a )
								func->parameterTypes[p].SetObjectType(equals[i].b);
							// Look for template instances that uses the interface as subtype
							else if( func->parameterTypes[p].IsTemplate() &&
								     func->parameterTypes[p].GetSubType().GetObjectType() == equals[i].a )
							{
								// Find the originating template type
								asCObjectType *templ = 0;
								for( asUINT t = 0; t < engine->registeredObjTypes.GetLength(); t++ )
									if( (engine->registeredObjTypes[t]->flags & asOBJ_TEMPLATE) &&
										engine->registeredObjTypes[t]->name == func->parameterTypes[p].GetObjectType()->name &&
									    !engine->templateInstanceTypes.Exists(engine->registeredObjTypes[t]) )
									{
										templ = engine->registeredObjTypes[t];
										break;
									}

								asASSERT( templ );

								asCDataType subType = func->parameterTypes[p].GetSubType();
								subType.SetObjectType(equals[i].b);
								func->parameterTypes[p].SetObjectType(engine->GetTemplateInstanceType(templ, subType));
							}
						}
					}
				}
			}
		}

		// Substitute all interface methods in the module. Delete all methods for the old interface
		for( unsigned int m = 0; m < equals[i].a->methods.GetLength(); m++ )
		{
			for( c = 0; c < scriptFunctions.GetLength(); c++ )
			{
				if( scriptFunctions[c]->id == equals[i].a->methods[m] )
				{
					if( substitutions )
						substitutions->PushLast(scriptFunctions[c]);

					scriptFunctions[c]->Release();

					scriptFunctions[c] = engine->GetScriptFunction(equals[i].b->methods[m]);
					scriptFunctions[c]->AddRef();

					if( substitutions )
						substitutions->PushLast(scriptFunctions[c]);
				}
			}
		}

		// If there was a template instance, it needs to be removed first
		for( asUINT n = 0; n < engine->templateTypes.GetLength(); n++ )
		{
			if( engine->templateTypes[n]->templateSubType.GetObjectType() == equals[i].a )
			{
				// The use of the template has already been exchanged above
				engine->RemoveTemplateInstanceType(engine->templateTypes[n]);
				n--;
			}
		}

		// Deallocate the object type
		asDELETE(equals[i].a, asCObjectType);
	}
}

// internal
bool asCModule::AreInterfacesEqual(asCObjectType *a, asCObjectType *b, asCArray<sObjectTypePair> &equals)
{
	// An interface is considered equal to another if the following criterias apply:
	//
	// - The interface names are equal
	// - The number of methods is equal
	// - All the methods are equal
	// - The order of the methods is equal
	// - If a method returns or takes an interface by handle or reference, both interfaces must be equal


	// ------------
	// TODO: Study the possiblity of allowing interfaces where methods are declared in different orders to
	// be considered equal. The compiler and VM can handle this, but it complicates the comparison of interfaces
	// where multiple methods take different interfaces as parameters (or return values). Example:
	// 
	// interface A
	// {
	//    void f(B, C);
	//    void f(B);
	//    void f(C);
	// }
	//
	// If 'void f(B)' in module A is compared against 'void f(C)' in module B, then the code will assume
	// interface B in module A equals interface C in module B. Thus 'void f(B, C)' in module A won't match
	// 'void f(C, B)' in module B.
	// ------------


	// Are both interfaces?
	if( !a->IsInterface() || !b->IsInterface() )
		return false;

	// Are the names equal?
	if( a->name != b->name )
		return false;

	// Are the namespaces equal?
	if( a->nameSpace != b->nameSpace )
		return false;

	// Are the number of methods equal?
	if( a->methods.GetLength() != b->methods.GetLength() )
		return false;

	// Keep the number of equals in the list so we can restore it later if necessary
	int prevEquals = (int)equals.GetLength();

	// Are the methods equal to each other?
	bool match = true;
	for( unsigned int n = 0; n < a->methods.GetLength(); n++ )
	{
		match = false;

		asCScriptFunction *funcA = (asCScriptFunction*)engine->GetFunctionById(a->methods[n]);
		asCScriptFunction *funcB = (asCScriptFunction*)engine->GetFunctionById(b->methods[n]);

		// funcB can be null if the module that created the interface has been  
		// discarded but the type has not yet been released by the engine.
		if( funcB == 0 )
			break;

		// The methods must have the same name and the same number of parameters
		if( funcA->name != funcB->name ||
			funcA->parameterTypes.GetLength() != funcB->parameterTypes.GetLength() )
			break;
		
		// The return types must be equal. If the return type is an interface the interfaces must match.
		if( !AreTypesEqual(funcA->returnType, funcB->returnType, equals) )
			break;

		match = true;
		for( unsigned int p = 0; p < funcA->parameterTypes.GetLength(); p++ )
		{
			if( !AreTypesEqual(funcA->parameterTypes[p], funcB->parameterTypes[p], equals) ||
				funcA->inOutFlags[p] != funcB->inOutFlags[p] )
			{
				match = false;
				break;
			}
		}

		if( !match )
			break;
	}

	// For each of the new interfaces that we're assuming to be equal, we need to validate this
	if( match )
	{
		for( unsigned int n = prevEquals; n < equals.GetLength(); n++ )
		{
			if( !AreInterfacesEqual(equals[n].a, equals[n].b, equals) )
			{
				match = false;
				break;
			}
		}
	}

	if( !match )
	{
		// The interfaces doesn't match. 
		// Restore the list of previous equals before we go on, so  
		// the caller can continue comparing with another interface
		equals.SetLength(prevEquals);
	}

	return match;
}

// internal
bool asCModule::AreTypesEqual(const asCDataType &a, const asCDataType &b, asCArray<sObjectTypePair> &equals)
{
	if( !a.IsEqualExceptInterfaceType(b) )
		return false;

	asCObjectType *ai = a.GetObjectType();
	asCObjectType *bi = b.GetObjectType();

	if( ai && (ai->flags & asOBJ_TEMPLATE) )
	{
		ai = ai->templateSubType.GetObjectType();
		bi = bi->templateSubType.GetObjectType();
	}

	if( ai && ai->IsInterface() )
	{
		// If the interface is in the equals list, then the pair must match the pair in the list
		bool found = false;
		unsigned int e;
		for( e = 0; e < equals.GetLength(); e++ )
		{
			if( equals[e].a == ai )
			{
				found = true;
				break;
			}
		}

		if( found )
		{
			// Do the pairs match?
			if( equals[e].b != bi )
				return false;
		}
		else
		{
			// Assume they are equal from now on
			sObjectTypePair pair = {ai, bi};
			equals.PushLast(pair);
		}
	}

	return true;
}

#endif // AS_DEPRECATED

// interface
int asCModule::SaveByteCode(asIBinaryStream *out) const
{
#ifdef AS_NO_COMPILER
	UNUSED_VAR(out);
	return asNOT_SUPPORTED;
#else
	if( out == 0 ) return asINVALID_ARG;

	asCWriter write(const_cast<asCModule*>(this), out, engine);
	return write.Write();
#endif
}

// interface
int asCModule::LoadByteCode(asIBinaryStream *in)
{
	if( in == 0 ) return asINVALID_ARG;

	// Only permit loading bytecode if no other thread is currently compiling
	// TODO: It should be possible to have multiple threads perform compilations
	int r = engine->RequestBuild();
	if( r < 0 )
		return r;

	asCReader read(this, in, engine);
	r = read.Read();

    JITCompile();

	engine->BuildCompleted();

	return r;
}

// interface
int asCModule::CompileGlobalVar(const char *sectionName, const char *code, int lineOffset)
{
#ifdef AS_NO_COMPILER
	UNUSED_VAR(sectionName);
	UNUSED_VAR(code);
	UNUSED_VAR(lineOffset);
	return asNOT_SUPPORTED;
#else
	// Validate arguments
	if( code == 0 )
		return asINVALID_ARG;

	// Only one thread may build at one time
	// TODO: It should be possible to have multiple threads perform compilations
	int r = engine->RequestBuild();
	if( r < 0 )
		return r;

	// Prepare the engine
	engine->PrepareEngine();
	if( engine->configFailed )
	{
		engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, TXT_INVALID_CONFIGURATION);
		engine->BuildCompleted();
		return asINVALID_CONFIGURATION;
	}

	// Compile the global variable and add it to the module scope
	asCBuilder builder(engine, this);
	asCString str = code;
	// TODO: namespace: Add the global var to the default namespace
	r = builder.CompileGlobalVar(sectionName, str.AddressOf(), lineOffset);

	engine->BuildCompleted();

	// Initialize the variable
	if( r >= 0 && engine->ep.initGlobalVarsAfterBuild )
	{
		// Clear the memory 
		asCGlobalProperty *prop = scriptGlobals[scriptGlobals.GetLength()-1];
		memset(prop->GetAddressOfValue(), 0, sizeof(asDWORD)*prop->type.GetSizeOnStackDWords());

		if( prop->GetInitFunc() )
		{
			// Call the init function for the global variable
			asIScriptContext *ctx = 0;
			int r = engine->CreateContext(&ctx, true);
			if( r < 0 )
				return r;

			r = ctx->Prepare(prop->GetInitFunc());
			if( r >= 0 )
				r = ctx->Execute();

			ctx->Release();
		}
	}

	return r;
#endif
}

// interface
int asCModule::CompileFunction(const char *sectionName, const char *code, int lineOffset, asDWORD compileFlags, asIScriptFunction **outFunc)
{
#ifdef AS_NO_COMPILER
	UNUSED_VAR(sectionName);
	UNUSED_VAR(code);
	UNUSED_VAR(lineOffset);
	UNUSED_VAR(compileFlags);
	UNUSED_VAR(outFunc);
	return asNOT_SUPPORTED;
#else
	asASSERT(outFunc == 0 || *outFunc == 0);

	// Validate arguments
	if( code == 0 || 
		(compileFlags != 0 && compileFlags != asCOMP_ADD_TO_MODULE) )
		return asINVALID_ARG;

	// Only one thread may build at one time
	// TODO: It should be possible to have multiple threads perform compilations
	int r = engine->RequestBuild();
	if( r < 0 )
		return r;

	// Prepare the engine
	engine->PrepareEngine();
	if( engine->configFailed )
	{
		engine->WriteMessage("", 0, 0, asMSGTYPE_ERROR, TXT_INVALID_CONFIGURATION);
		engine->BuildCompleted();
		return asINVALID_CONFIGURATION;
	}

	// Compile the single function
	asCBuilder builder(engine, this);
	asCString str = code;
	asCScriptFunction *func = 0;
	// TODO: namespace: Add the function to the default namespace
	r = builder.CompileFunction(sectionName, str.AddressOf(), lineOffset, compileFlags, &func);

	engine->BuildCompleted();

	if( r >= 0 && outFunc )
	{
		// Return the function to the caller
		*outFunc = func;
		func->AddRef();
	}

	// Release our reference to the function
	if( func )
		func->Release();

	return r;
#endif
}

#ifdef AS_DEPRECATED
// Deprecated since 2.24.0 - 2012-05-20
// interface
int asCModule::RemoveFunction(int funcId)
{
	if( funcId >= 0 && funcId < (int)engine->scriptFunctions.GetLength() )
		return RemoveFunction(engine->scriptFunctions[funcId]);

	return asNO_FUNCTION;
}
#endif

// interface
int asCModule::RemoveFunction(asIScriptFunction *func)
{
	// Find the global function
	asCScriptFunction *f = static_cast<asCScriptFunction*>(func);
	int idx = globalFunctions.IndexOf(f);
	if( idx >= 0 )
	{
		globalFunctions.RemoveIndex(idx);
		f->Release();
		scriptFunctions.RemoveValue(f);
		f->Release();
		return 0;
	}

	return asNO_FUNCTION;
}

// internal
int asCModule::AddFuncDef(const char *name, const asCString &ns)
{
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine, 0, asFUNC_FUNCDEF);
	if( func == 0 )
		return asOUT_OF_MEMORY;

	func->name      = name;
	func->nameSpace = ns;

	funcDefs.PushLast(func);

	engine->funcDefs.PushLast(func);
	func->id = engine->GetNextScriptFunctionId();
	engine->SetScriptFunction(func);

	return (int)funcDefs.GetLength()-1;
}

// interface
asDWORD asCModule::SetAccessMask(asDWORD mask)
{
	asDWORD old = accessMask;
	accessMask = mask;
	return old;
}

END_AS_NAMESPACE

