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

// Modified by Lasse Öörni for Urho3D

//
// as_builder.cpp
//
// This is the class that manages the compilation of the scripts
//


#include "as_config.h"
#include "as_builder.h"
#include "as_parser.h"
#include "as_compiler.h"
#include "as_tokendef.h"
#include "as_string_util.h"
#include "as_outputbuffer.h"
#include "as_texts.h"
#include "as_scriptobject.h"

BEGIN_AS_NAMESPACE

asCBuilder::asCBuilder(asCScriptEngine *engine, asCModule *module)
{
	this->engine = engine;
	this->module = module;
}

asCBuilder::~asCBuilder()
{
#ifndef AS_NO_COMPILER
	asUINT n;

	// Free all functions
	for( n = 0; n < functions.GetLength(); n++ )
	{
		if( functions[n] )
		{
			if( functions[n]->node )
			{
				functions[n]->node->Destroy(engine);
			}

			if( functions[n]->explicitSignature )
			{
				asDELETE(functions[n]->explicitSignature,sExplicitSignature);
			}

			asDELETE(functions[n],sFunctionDescription);
		}

		functions[n] = 0;
	}

	// Free all global variables
	for( n = 0; n < globVariables.GetLength(); n++ )
	{
		if( globVariables[n] )
		{
			if( globVariables[n]->nextNode )
			{
				globVariables[n]->nextNode->Destroy(engine);
			}

			asDELETE(globVariables[n],sGlobalVariableDescription);
			globVariables[n] = 0;
		}
	}

	// Free all the loaded files
	for( n = 0; n < scripts.GetLength(); n++ )
	{
		if( scripts[n] )
		{
			asDELETE(scripts[n],asCScriptCode);
		}

		scripts[n] = 0;
	}

	// Free all class declarations
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		if( classDeclarations[n] )
		{
			if( classDeclarations[n]->node )
			{
				classDeclarations[n]->node->Destroy(engine);
			}

			asDELETE(classDeclarations[n],sClassDeclaration);
			classDeclarations[n] = 0;
		}
	}

	for( n = 0; n < interfaceDeclarations.GetLength(); n++ )
	{
		if( interfaceDeclarations[n] )
		{
			if( interfaceDeclarations[n]->node )
			{
				interfaceDeclarations[n]->node->Destroy(engine);
			}

			asDELETE(interfaceDeclarations[n],sClassDeclaration);
			interfaceDeclarations[n] = 0;
		}
	}

	for( n = 0; n < namedTypeDeclarations.GetLength(); n++ )
	{
		if( namedTypeDeclarations[n] )
		{
			if( namedTypeDeclarations[n]->node )
			{
				namedTypeDeclarations[n]->node->Destroy(engine);
			}

			asDELETE(namedTypeDeclarations[n],sClassDeclaration);
			namedTypeDeclarations[n] = 0;
		}
	}

	for( n = 0; n < funcDefs.GetLength(); n++ )
	{
		if( funcDefs[n] )
		{
			if( funcDefs[n]->node )
				funcDefs[n]->node->Destroy(engine);

			asDELETE(funcDefs[n],sFuncDef);
			funcDefs[n] = 0;
		}
	}

#endif // AS_NO_COMPILER
}

void asCBuilder::Reset()
{
	numErrors = 0;
	numWarnings = 0;
	preMessage.isSet = false;
}

#ifndef AS_NO_COMPILER
int asCBuilder::AddCode(const char *name, const char *code, int codeLength, int lineOffset, int sectionIdx, bool makeCopy)
{
	asCScriptCode *script = asNEW(asCScriptCode);
	if( script == 0 )
		return asOUT_OF_MEMORY;

	int r = script->SetCode(name, code, codeLength, makeCopy);
	script->lineOffset = lineOffset;
	script->idx = sectionIdx;
	scripts.PushLast(script);

	return r;
}

int asCBuilder::Build()
{
	Reset();

	ParseScripts();

	CompileClasses();
	CompileGlobalVariables();
	CompileFunctions();

	// TODO: Attempt to reorder the initialization of global variables so that 
	//       they do not access other uninitialized global variables out-of-order
	//       The builder needs to check for each of the global variable, what functions
	//       that are accessed, and what global variables are access by these functions.

	if( numErrors > 0 )
		return asERROR;

	return asSUCCESS;
}

int asCBuilder::CompileGlobalVar(const char *sectionName, const char *code, int lineOffset)
{
	Reset();

	// Add the string to the script code
	asCScriptCode *script = asNEW(asCScriptCode);
	if( script == 0 )
		return asOUT_OF_MEMORY;

	script->SetCode(sectionName, code, true);
	script->lineOffset = lineOffset;
	scripts.PushLast(script);

	// Parse the string
	asCParser parser(this);
	if( parser.ParseScript(scripts[0]) < 0 )
		return asERROR;

	asCScriptNode *node = parser.GetScriptNode();

	// Make sure there is nothing else than the global variable in the script code
	if( node == 0 ||
		node->firstChild == 0 ||
		node->firstChild != node->lastChild ||
		node->firstChild->nodeType != snGlobalVar )
	{
		WriteError(script->name.AddressOf(), TXT_ONLY_ONE_VARIABLE_ALLOWED, 0, 0);
		return asERROR;
	}

	node = node->firstChild;
	node->DisconnectParent();
	// TODO: namespace: How should we allow informing the namespace? Perhaps the module 
	//                  needs a SetDefaultNamespace() method that can be called before
	RegisterGlobalVar(node, script, "");

	CompileGlobalVariables();

	if( numErrors > 0 )
	{
		// Remove the variable from the module, if it was registered
		if( globVariables.GetLength() > 0 )
		{
			module->RemoveGlobalVar(module->GetGlobalVarCount()-1);
		}

		return asERROR;
	}

	return 0;
}
#endif

int asCBuilder::ValidateDefaultArgs(asCScriptCode *script, asCScriptNode *node, asCScriptFunction *func)
{
	int firstArgWithDefaultValue = -1;
	for( asUINT n = 0; n < func->defaultArgs.GetLength(); n++ )
	{
		if( func->defaultArgs[n] )
			firstArgWithDefaultValue = n;
		else if( firstArgWithDefaultValue >= 0 )
		{
			int r, c;
			script->ConvertPosToRowCol(node->tokenPos, &r, &c);

			asCString str;
			str.Format(TXT_DEF_ARG_MISSING_IN_FUNC_s, func->GetDeclaration());

			WriteError(script->name.AddressOf(), str.AddressOf(), r, c);
			return asINVALID_DECLARATION;
		}
	}

	return 0;
}

#ifndef AS_NO_COMPILER
int asCBuilder::CompileFunction(const char *sectionName, const char *code, int lineOffset, asDWORD compileFlags, asCScriptFunction **outFunc)
{
	asASSERT(outFunc != 0);

	Reset();

	// Add the string to the script code
	asCScriptCode *script = asNEW(asCScriptCode);
	if( script == 0 )
		return asOUT_OF_MEMORY;

	script->SetCode(sectionName, code, true);
	script->lineOffset = lineOffset; 
	scripts.PushLast(script);

	// Parse the string
	asCParser parser(this);
	if( parser.ParseScript(scripts[0]) < 0 )
		return asERROR;

	asCScriptNode *node = parser.GetScriptNode();

	// Make sure there is nothing else than the function in the script code
	if( node == 0 || 
		node->firstChild == 0 || 
		node->firstChild != node->lastChild || 
		node->firstChild->nodeType != snFunction )
	{
		WriteError(script->name.AddressOf(), TXT_ONLY_ONE_FUNCTION_ALLOWED, 0, 0);
		return asERROR;
	}

	// Find the function node
	node = node->firstChild;

	// TODO: namespace: How should we allow informing the namespace? Perhaps the module 
	//                  needs a SetDefaultNamespace() method that can be called before

	// Create the function
	bool isConstructor, isDestructor, isPrivate, isFinal, isOverride, isShared;
	asCScriptFunction *func = asNEW(asCScriptFunction)(engine,module,asFUNC_SCRIPT);
	if( func == 0 )
		return asOUT_OF_MEMORY;

	GetParsedFunctionDetails(node, scripts[0], 0, func->name, func->returnType, func->parameterTypes, func->inOutFlags, func->defaultArgs, func->isReadOnly, isConstructor, isDestructor, isPrivate, isFinal, isOverride, isShared);
	func->id               = engine->GetNextScriptFunctionId();
	func->scriptSectionIdx = engine->GetScriptSectionNameIndex(sectionName ? sectionName : "");

	// Make sure the default args are declared correctly
	int r = ValidateDefaultArgs(script, node, func);
	if( r < 0 )
	{
		func->Release();
		return asERROR;
	}

	// Tell the engine that the function exists already so the compiler can access it
	if( compileFlags & asCOMP_ADD_TO_MODULE )
	{
		int r = CheckNameConflict(func->name.AddressOf(), node, scripts[0], "");
		if( r < 0 )
		{
			func->Release();
			return asERROR;
		}

		module->globalFunctions.PushLast(func);
		func->AddRef();
		module->AddScriptFunction(func);
	}
	else
		engine->SetScriptFunction(func);

	// Fill in the function info for the builder too
	node->DisconnectParent();
	sFunctionDescription *funcDesc = asNEW(sFunctionDescription);
	if( funcDesc == 0 )
	{
		func->Release();
		return asOUT_OF_MEMORY;
	}

	functions.PushLast(funcDesc);
	funcDesc->script            = scripts[0];
	funcDesc->node              = node;
	funcDesc->name              = func->name;
	funcDesc->funcId            = func->id;
	funcDesc->explicitSignature = 0;

	asCCompiler compiler(engine);
	if( compiler.CompileFunction(this, functions[0]->script, 0, functions[0]->node, func) >= 0 )
	{
		// Return the function
		*outFunc = func;
	}
	else
	{
		// If the function was added to the module then remove it again
		if( compileFlags & asCOMP_ADD_TO_MODULE )
		{
			module->globalFunctions.RemoveValue(func);
			module->scriptFunctions.RemoveValue(func);
			func->Release();
			func->Release();
		}

		func->Release();

		return asERROR;
	}

	return asSUCCESS;
}

void asCBuilder::ParseScripts()
{
	asCArray<asCParser*> parsers((int)scripts.GetLength());

	// Parse all the files as if they were one
	asUINT n = 0;
	for( n = 0; n < scripts.GetLength(); n++ )
	{
		asCParser *parser = asNEW(asCParser)(this);
		if( parser != 0 )
		{
			parsers.PushLast(parser);

			// Parse the script file
			parser->ParseScript(scripts[n]);
		}
	}

	if( numErrors == 0 )
	{
		// Find all type declarations
		for( n = 0; n < scripts.GetLength(); n++ )
		{
			asCScriptNode *node = parsers[n]->GetScriptNode();
			RegisterTypesFromScript(node, scripts[n], "");
		}

		// Register the complete function definitions
		for( n = 0; n < funcDefs.GetLength(); n++ )
		{
			CompleteFuncDef(funcDefs[n]);
		}

		// Register script methods found in the interfaces
		for( n = 0; n < interfaceDeclarations.GetLength(); n++ )
		{
			sClassDeclaration *decl = interfaceDeclarations[n];
			asCScriptNode *node = decl->node->firstChild->next;
			while( node )
			{
				asCScriptNode *next = node->next;
				if( node->nodeType == snFunction )
				{
					node->DisconnectParent();
					RegisterScriptFunction(engine->GetNextScriptFunctionId(), node, decl->script, decl->objType, true, false, "", decl->isExistingShared);
				}
				else if( node->nodeType == snVirtualProperty )
				{
					node->DisconnectParent();
					RegisterVirtualProperty(node, decl->script, decl->objType, true, false, "", decl->isExistingShared);
				}

				node = next;
			}
		}

#ifdef AS_DEPRECATED
	// Deprecated since 2.23.0 - 2012-01-30

		// Now the interfaces have been completely established, now we need to determine if
		// the same interface has already been registered before, and if so reuse the interface id.
		// TODO: deprecate this. interfaces should be explicitly marked as shared
		module->ResolveInterfaceIds();
#endif

		// Register script methods found in the structures
		for( n = 0; n < classDeclarations.GetLength(); n++ )
		{
			sClassDeclaration *decl = classDeclarations[n];
			if( decl->isExistingShared ) continue; // TODO: shared: Should really verify that the methods match the original

			asCScriptNode *node = decl->node->firstChild->next;

			// Skip list of classes and interfaces
			while( node && node->nodeType == snIdentifier )
				node = node->next;

			while( node )
			{
				asCScriptNode *next = node->next;
				if( node->nodeType == snFunction )
				{
					node->DisconnectParent();
					RegisterScriptFunction(engine->GetNextScriptFunctionId(), node, decl->script, decl->objType);
				}
				else if( node->nodeType == snVirtualProperty )
				{
					node->DisconnectParent();
					RegisterVirtualProperty(node, decl->script, decl->objType, false, false);
				}

				node = next;
			}

			// Make sure the default factory & constructor exists for classes
			if( decl->objType->beh.construct == engine->scriptTypeBehaviours.beh.construct )
			{
				if( decl->objType->beh.constructors.GetLength() == 1 || engine->ep.alwaysImplDefaultConstruct )
				{
					AddDefaultConstructor(decl->objType, decl->script);
				}
				else
				{
					// As the class has another constructor we shouldn't provide the default constructor
					if( decl->objType->beh.construct )
					{
						engine->scriptFunctions[decl->objType->beh.construct]->Release();
						decl->objType->beh.construct = 0;
						decl->objType->beh.constructors.RemoveIndex(0);
					}
					if( decl->objType->beh.factory )
					{
						engine->scriptFunctions[decl->objType->beh.factory]->Release();
						decl->objType->beh.factory = 0;
						decl->objType->beh.factories.RemoveIndex(0);
					}
					if( decl->objType->beh.copy )
					{
						engine->scriptFunctions[decl->objType->beh.copy]->Release();
						decl->objType->beh.copy = 0;
					}
				}
			}
		}

		// Find other global nodes
		for( n = 0; n < scripts.GetLength(); n++ )
		{
			// Find other global nodes
			asCScriptNode *node = parsers[n]->GetScriptNode();
			RegisterNonTypesFromScript(node, scripts[n], "");
		}
	}

	for( n = 0; n < parsers.GetLength(); n++ )
	{
		asDELETE(parsers[n],asCParser);
	}
}

void asCBuilder::RegisterTypesFromScript(asCScriptNode *node, asCScriptCode *script, const asCString &ns)
{
	asASSERT(node->nodeType == snScript);

	// Find structure definitions first
	node = node->firstChild;
	while( node )
	{
		asCScriptNode *next = node->next;
		if( node->nodeType == snNamespace )
		{
			// Recursively register the entities defined in the namespace
			asCString nsChild;
			nsChild.Assign(&script->code[node->firstChild->tokenPos], node->firstChild->tokenLength);	
			if( ns != "" )
				RegisterTypesFromScript(node->lastChild, script, ns+"::"+nsChild);
			else
				RegisterTypesFromScript(node->lastChild, script, nsChild);
		}
		else
		{
			if( node->nodeType == snClass )
			{
				node->DisconnectParent();
				RegisterClass(node, script, ns);
			}
			else if( node->nodeType == snInterface )
			{
				node->DisconnectParent();
				RegisterInterface(node, script, ns);
			}
			else if( node->nodeType == snEnum )
			{
				node->DisconnectParent();
				RegisterEnum(node, script, ns);
			}
			else if( node->nodeType == snTypedef )
			{
				node->DisconnectParent();
				RegisterTypedef(node, script, ns);
			}
			else if( node->nodeType == snFuncDef )
			{
				node->DisconnectParent();
				RegisterFuncDef(node, script, ns);
			}
		}

		node = next;
	}
}

void asCBuilder::RegisterNonTypesFromScript(asCScriptNode *node, asCScriptCode *script, const asCString &ns)
{
	node = node->firstChild;
	while( node )
	{
		asCScriptNode *next = node->next;
		if( node->nodeType == snNamespace )
		{
			// Recursively register the entities in the namespace
			asCString nsChild;
			nsChild.Assign(&script->code[node->firstChild->tokenPos], node->firstChild->tokenLength);		
			if( ns != "" )
				RegisterNonTypesFromScript(node->lastChild, script, ns+"::"+nsChild);
			else
				RegisterNonTypesFromScript(node->lastChild, script, nsChild);
		}
		else
		{
			node->DisconnectParent();
			if( node->nodeType == snFunction )
				RegisterScriptFunction(engine->GetNextScriptFunctionId(), node, script, 0, false, true, ns);
			else if( node->nodeType == snGlobalVar )
				RegisterGlobalVar(node, script, ns);
			else if( node->nodeType == snVirtualProperty )
				RegisterVirtualProperty(node, script, 0, false, true, ns);
			else if( node->nodeType == snImport )
				RegisterImportedFunction(module->GetNextImportedFunctionId(), node, script, ns);
			else
			{
				// Unused script node
				int r, c;
				script->ConvertPosToRowCol(node->tokenPos, &r, &c);

				WriteWarning(script->name.AddressOf(), TXT_UNUSED_SCRIPT_NODE, r, c);

				node->Destroy(engine);
			}
		}

		node = next;
	}
}

void asCBuilder::CompileFunctions()
{
	// Compile each function
	for( asUINT n = 0; n < functions.GetLength(); n++ )
	{
		sFunctionDescription *current = functions[n];
		if( current == 0 ) continue;

		asCCompiler compiler(engine);
		asCScriptFunction *func = engine->scriptFunctions[current->funcId];

		if( current->node )
		{
			int r, c;
			current->script->ConvertPosToRowCol(current->node->tokenPos, &r, &c);

			asCString str = func->GetDeclarationStr();
			str.Format(TXT_COMPILING_s, str.AddressOf());
			WriteInfo(current->script->name.AddressOf(), str.AddressOf(), r, c, true);

			compiler.CompileFunction(this, current->script, current->explicitSignature, current->node, func);

			preMessage.isSet = false;
		}
		else if( current->name == current->objType->name )
		{
			asCScriptNode *node = 0;
			for( asUINT n = 0; n < classDeclarations.GetLength(); n++ )
			{
				if( classDeclarations[n]->name == current->name )
				{
					node = classDeclarations[n]->node;
					break;
				}
			}

			int r = 0, c = 0;
			if( node )
				current->script->ConvertPosToRowCol(node->tokenPos, &r, &c);

			asCString str = func->GetDeclarationStr();
			str.Format(TXT_COMPILING_s, str.AddressOf());
			WriteInfo(current->script->name.AddressOf(), str.AddressOf(), r, c, true);

			// This is the default constructor, that is generated
			// automatically if not implemented by the user.
			compiler.CompileDefaultConstructor(this, current->script, node, func);

			preMessage.isSet = false;
		}
		else
		{
			// This is a property accessor, but no implementation was provided for it
			asASSERT( current->explicitSignature );
		}
	}
}
#endif

// Called from module and engine
int asCBuilder::ParseDataType(const char *datatype, asCDataType *result, const asCString &implicitNamespace, bool isReturnType)
{
	Reset();

	asCScriptCode source;
	source.SetCode("", datatype, true);

	asCParser parser(this);
	int r = parser.ParseDataType(&source, isReturnType);
	if( r < 0 )
		return asINVALID_TYPE;

	// Get data type and property name
	asCScriptNode *dataType = parser.GetScriptNode()->firstChild;

	*result = CreateDataTypeFromNode(dataType, &source, implicitNamespace, true);
	if( isReturnType )
		*result = ModifyDataTypeFromNode(*result, dataType->next, &source, 0, 0);

	if( numErrors > 0 )
		return asINVALID_TYPE;

	return asSUCCESS;
}

int asCBuilder::ParseTemplateDecl(const char *decl, asCString *name, asCString *subtypeName)
{
	Reset();

	asCScriptCode source;
	source.SetCode("", decl, true);

	asCParser parser(this);
	int r = parser.ParseTemplateDecl(&source);
	if( r < 0 )
		return asINVALID_TYPE;

	// Get the template name and subtype name
	asCScriptNode *node = parser.GetScriptNode()->firstChild;

	name->Assign(&decl[node->tokenPos], node->tokenLength);
	node = node->next;
	subtypeName->Assign(&decl[node->tokenPos], node->tokenLength);

	// TODO: template: check for name conflicts

	if( numErrors > 0 )
		return asINVALID_DECLARATION;

	return asSUCCESS;
}

int asCBuilder::VerifyProperty(asCDataType *dt, const char *decl, asCString &name, asCDataType &type, const asCString &ns)
{
	Reset();

	if( dt )
	{
		// Verify that the object type exist
		if( dt->GetObjectType() == 0 )
			return asINVALID_OBJECT;
	}

	// Check property declaration and type
	asCScriptCode source;
	source.SetCode(TXT_PROPERTY, decl, true);

	asCParser parser(this);
	int r = parser.ParsePropertyDeclaration(&source);
	if( r < 0 )
		return asINVALID_DECLARATION;

	// Get data type and property name
	asCScriptNode *dataType = parser.GetScriptNode()->firstChild;

	asCScriptNode *nameNode = dataType->next;

	// TODO: namespace: Use correct implicit namespace
	type = CreateDataTypeFromNode(dataType, &source, "");
	name.Assign(&decl[nameNode->tokenPos], nameNode->tokenLength);

	// Validate that the type really can be a registered property
	// We cannot use CanBeInstanciated, as it is allowed to register
	// properties of type that cannot otherwise be instanciated
	if( type.GetFuncDef() && !type.IsObjectHandle() )
	{
		// Function definitions must always be handles
		return asINVALID_DECLARATION;
	}

	// Verify property name
	if( dt )
	{
		if( CheckNameConflictMember(dt->GetObjectType(), name.AddressOf(), nameNode, &source, true) < 0 )
			return asNAME_TAKEN;
	}
	else
	{
		if( CheckNameConflict(name.AddressOf(), nameNode, &source, ns) < 0 )
			return asNAME_TAKEN;
	}

	if( numErrors > 0 )
		return asINVALID_DECLARATION;

	return asSUCCESS;
}

asCObjectProperty *asCBuilder::GetObjectProperty(asCDataType &obj, const char *prop)
{
	asASSERT(obj.GetObjectType() != 0);

	// TODO: optimize: Improve linear search
	asCArray<asCObjectProperty *> &props = obj.GetObjectType()->properties;
	for( asUINT n = 0; n < props.GetLength(); n++ )
	{
		if( props[n]->name == prop )
		{
			if( module->accessMask & props[n]->accessMask )
				return props[n];
			else
				return 0;
		}
	}

	return 0;
}

asCGlobalProperty *asCBuilder::GetGlobalProperty(const char *prop, const asCString &ns, bool *isCompiled, bool *isPureConstant, asQWORD *constantValue, bool *isAppProp)
{
	asUINT n;

	if( isCompiled ) *isCompiled = true;
	if( isPureConstant ) *isPureConstant = false;
	if( isAppProp ) *isAppProp = false;

	// TODO: optimize: Improve linear search
	// Check application registered properties
	asCArray<asCGlobalProperty *> &props = engine->registeredGlobalProps;
	for( n = 0; n < props.GetLength(); ++n )
		if( props[n] && 
			props[n]->name == prop &&
			props[n]->nameSpace == ns )
		{
			if( module )
			{
				// Determine if the module has access to the property
				if( module->accessMask & props[n]->accessMask )
				{
					if( isAppProp ) *isAppProp = true;
					return props[n];
				}
			}
			else
			{
				// We're not compiling a module right now, so it must be a registered global property
				if( isAppProp ) *isAppProp = true;
				return props[n];
			}
		}

#ifndef AS_NO_COMPILER
	// TODO: optimize: Improve linear search
	// Check properties being compiled now
	asCArray<sGlobalVariableDescription *> &gvars = globVariables;
	for( n = 0; n < gvars.GetLength(); ++n )
	{
		if( gvars[n] == 0 ) continue;
		asCGlobalProperty *p = gvars[n]->property;
		if( p && 
			p->name == prop &&
			p->nameSpace == ns )
		{
			if( isCompiled )     *isCompiled     = gvars[n]->isCompiled;
			if( isPureConstant ) *isPureConstant = gvars[n]->isPureConstant;
			if( constantValue  ) *constantValue  = gvars[n]->constantValue;

			return p;
		}
	}
#else
	UNUSED_VAR(constantValue);
#endif

	// TODO: optimize: Improve linear search
	// Check previously compiled global variables
	if( module )
	{
		asCArray<asCGlobalProperty *> &props = module->scriptGlobals;
		for( n = 0; n < props.GetLength(); ++n )
			if( props[n]->name == prop &&
				props[n]->nameSpace == ns )
				return props[n];
	}

	return 0;
}

int asCBuilder::ParseFunctionDeclaration(asCObjectType *objType, const char *decl, asCScriptFunction *func, bool isSystemFunction, asCArray<bool> *paramAutoHandles, bool *returnAutoHandle)
{
	// TODO: Can't we use GetParsedFunctionDetails to do most of what is done in this function?

	Reset();

	asCScriptCode source;
	source.SetCode(TXT_SYSTEM_FUNCTION, decl, true);

	asCParser parser(this);
	int r = parser.ParseFunctionDefinition(&source);
	if( r < 0 )
		return asINVALID_DECLARATION;

	asCScriptNode *node = parser.GetScriptNode();

	// Determine scope
	asCScriptNode *n = node->firstChild->next->next;
	func->nameSpace = GetScopeFromNode(n, &source, &n);

	// Find name
	func->name.Assign(&source.code[n->tokenPos], n->tokenLength);

	// Initialize a script function object for registration
	bool autoHandle;

	// Scoped reference types are allowed to use handle when returned from application functions
	// TODO: namespace: Use correct implicit namespace
	func->returnType = CreateDataTypeFromNode(node->firstChild, &source, "", true, objType);
	func->returnType = ModifyDataTypeFromNode(func->returnType, node->firstChild->next, &source, 0, &autoHandle);
	if( autoHandle && (!func->returnType.IsObjectHandle() || func->returnType.IsReference()) )
			return asINVALID_DECLARATION;
	if( returnAutoHandle ) *returnAutoHandle = autoHandle;

	// Reference types cannot be returned by value from system functions
	if( isSystemFunction &&
		(func->returnType.GetObjectType() &&
		 (func->returnType.GetObjectType()->flags & asOBJ_REF)) &&
        !(func->returnType.IsReference() ||
		  func->returnType.IsObjectHandle()) )
		return asINVALID_DECLARATION;

	// Count number of parameters
	int paramCount = 0;
	n = n->next->firstChild;
	while( n )
	{
		paramCount++;
		n = n->next->next;
		if( n && n->nodeType == snIdentifier )
			n = n->next;

		if( n && n->nodeType == snExpression )
			n = n->next;
	}

	// Preallocate memory
	func->parameterTypes.Allocate(paramCount, false);
	func->inOutFlags.Allocate(paramCount, false);
	func->defaultArgs.Allocate(paramCount, false);
	if( paramAutoHandles ) paramAutoHandles->Allocate(paramCount, false);

	n = node->firstChild->next->next->next->firstChild;
	while( n )
	{
		asETypeModifiers inOutFlags;
		// TODO: namespace: Use correct implicit namespace
		asCDataType type = CreateDataTypeFromNode(n, &source, "", false, objType);
		type = ModifyDataTypeFromNode(type, n->next, &source, &inOutFlags, &autoHandle);

		// Reference types cannot be passed by value to system functions
		if( isSystemFunction &&
			(type.GetObjectType() &&
		     (type.GetObjectType()->flags & asOBJ_REF)) &&
			!(type.IsReference() ||
			  type.IsObjectHandle()) )
			return asINVALID_DECLARATION;

		// Store the parameter type
		func->parameterTypes.PushLast(type);
		func->inOutFlags.PushLast(inOutFlags);

		// Don't permit void parameters
		if( type.GetTokenType() == ttVoid )
			return asINVALID_DECLARATION;

		if( autoHandle && (!type.IsObjectHandle() || type.IsReference()) )
			return asINVALID_DECLARATION;

		if( paramAutoHandles ) paramAutoHandles->PushLast(autoHandle);

		// Make sure that var type parameters are references
		if( type.GetTokenType() == ttQuestion &&
			!type.IsReference() )
			return asINVALID_DECLARATION;

		// Move to next parameter
		n = n->next->next;
		if( n && n->nodeType == snIdentifier )
			n = n->next;

		if( n && n->nodeType == snExpression )
		{
			// Strip out white space and comments to better share the string
			asCString *defaultArgStr = asNEW(asCString);
			if( defaultArgStr )
			{
				*defaultArgStr = GetCleanExpressionString(n, &source);
				func->defaultArgs.PushLast(defaultArgStr);
			}

			n = n->next;
		}
		else
			func->defaultArgs.PushLast(0);
	}

	// Set the read-only flag if const is declared after parameter list
	if( node->lastChild->nodeType == snUndefined && node->lastChild->tokenType == ttConst )
	{
		if( objType == 0 )
			return asINVALID_DECLARATION;
		func->isReadOnly = true;
	}
	else
		func->isReadOnly = false;

	// Make sure the default args are declared correctly
	ValidateDefaultArgs(&source, node, func);

	if( numErrors > 0 || numWarnings > 0 )
		return asINVALID_DECLARATION;

	return 0;
}

int asCBuilder::ParseVariableDeclaration(const char *decl, const asCString &implicitNamespace, asCString &outName, asCString &outNamespace, asCDataType &outDt)
{
	Reset();

	asCScriptCode source;
	source.SetCode(TXT_VARIABLE_DECL, decl, true);

	asCParser parser(this);

	int r = parser.ParsePropertyDeclaration(&source);
	if( r < 0 )
		return asINVALID_DECLARATION;

	asCScriptNode *node = parser.GetScriptNode();

	// Determine the scope from declaration
	asCScriptNode *n = node->firstChild->next;
	asCString scope = GetScopeFromNode(n, &source, &n);
	if( scope == "" )
		outNamespace = implicitNamespace;
	else if( scope == "::" )
		outNamespace = "";
	else
		outNamespace = scope;

	// Find name
	outName.Assign(&source.code[n->tokenPos], n->tokenLength);

	// Initialize a script variable object for registration
	outDt = CreateDataTypeFromNode(node->firstChild, &source, implicitNamespace);

	if( numErrors > 0 || numWarnings > 0 )
		return asINVALID_DECLARATION;

	return 0;
}

int asCBuilder::CheckNameConflictMember(asCObjectType *t, const char *name, asCScriptNode *node, asCScriptCode *code, bool isProperty)
{
	// It's not necessary to check against object types

	// TODO: optimize: Improve linear search
	asCArray<asCObjectProperty *> &props = t->properties;
	for( asUINT n = 0; n < props.GetLength(); n++ )
	{
		if( props[n]->name == name )
		{
			if( code )
			{
				int r, c;
				code->ConvertPosToRowCol(node->tokenPos, &r, &c);

				asCString str;
				str.Format(TXT_NAME_CONFLICT_s_OBJ_PROPERTY, name);
				WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
			}

			return -1;
		}
	}

	// Property names must be checked against method names
	if( isProperty )
	{
		asCArray<int> methods = t->methods;
		for( asUINT n = 0; n < methods.GetLength(); n++ )
		{
			if( engine->scriptFunctions[methods[n]]->name == name )
			{
				if( code )
				{
					int r, c;
					code->ConvertPosToRowCol(node->tokenPos, &r, &c);

					asCString str;
					str.Format(TXT_NAME_CONFLICT_s_METHOD, name);
					WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
				}

				return -1;
			}
		}
	}

	return 0;
}

int asCBuilder::CheckNameConflict(const char *name, asCScriptNode *node, asCScriptCode *code, const asCString &ns)
{
	// Check against registered object types
	if( engine->GetObjectType(name, ns) != 0 )
	{
		if( code )
		{
			int r, c;
			code->ConvertPosToRowCol(node->tokenPos, &r, &c);
			asCString str;
			str.Format(TXT_NAME_CONFLICT_s_EXTENDED_TYPE, name);
			WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
		}

		return -1;
	}

	// TODO: Must verify global properties in all config groups, whether the module has access or not
	// Check against global properties
	asCGlobalProperty *prop = GetGlobalProperty(name, ns, 0, 0, 0, 0);
	if( prop )
	{
		if( code )
		{
			int r, c;
			code->ConvertPosToRowCol(node->tokenPos, &r, &c);
			asCString str;
			str.Format(TXT_NAME_CONFLICT_s_GLOBAL_PROPERTY, name);
			WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
		}

		return -1;
	}

	// TODO: Property names must be checked against function names

#ifndef AS_NO_COMPILER
	// Check against class types
	asUINT n;
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		if( classDeclarations[n]->name == name &&
			classDeclarations[n]->objType->nameSpace == ns )
		{
			if( code )
			{
				int r, c;
				code->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString str;
				str.Format(TXT_NAME_CONFLICT_s_STRUCT, name);
				WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
			}

			return -1;
		}
	}

	// Check against named types
	for( n = 0; n < namedTypeDeclarations.GetLength(); n++ )
	{
		if( namedTypeDeclarations[n]->name == name &&
			namedTypeDeclarations[n]->objType->nameSpace == ns )
		{
			if( code )
			{
				int r, c;
				code->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString str;
				str.Format(TXT_NAME_CONFLICT_s_IS_NAMED_TYPE, name);
				WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
			}

			return -1;
		}
	}

	// Must check for name conflicts with funcdefs
	for( n = 0; n < funcDefs.GetLength(); n++ )
	{
		if( funcDefs[n]->name == name &&
			module->funcDefs[funcDefs[n]->idx]->nameSpace == ns )
		{
			if( code )
			{
				int r, c;
				code->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString str;
				str.Format(TXT_NAME_CONFLICT_s_IS_FUNCDEF, name);
				WriteError(code->name.AddressOf(), str.AddressOf(), r, c);
			}

			return -1;
		}
	}
#endif

	return 0;
}

#ifndef AS_NO_COMPILER
int asCBuilder::RegisterFuncDef(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	// Find the name
	asASSERT( node->firstChild->nodeType == snDataType );
	asCScriptNode *n = node->firstChild->next->next;
	
	asCString name;
	name.Assign(&file->code[n->tokenPos], n->tokenLength);

	// Check for name conflict with other types
	int r = CheckNameConflict(name.AddressOf(), node, file, ns);
	if( asSUCCESS != r )
	{
		node->Destroy(engine);
		return r;
	}

	// The function definition should be stored as a asCScriptFunction so that the application
	// can use the asIScriptFunction interface to enumerate the return type and parameters

	// The return type and parameter types aren't determined in this function. A second pass is 
	// necessary after all type declarations have been identified.

	sFuncDef *fd = asNEW(sFuncDef);
	if( fd == 0 )
	{
		node->Destroy(engine);
		return asOUT_OF_MEMORY;
	}

	fd->name   = name;
	fd->node   = node;
	fd->script = file;
	fd->idx    = module->AddFuncDef(name.AddressOf(), ns);

	funcDefs.PushLast(fd);

	return 0;
}

void asCBuilder::CompleteFuncDef(sFuncDef *funcDef)
{
	asCDataType                returnType;
	asCArray<asCDataType>      parameterTypes;
	asCArray<asETypeModifiers> inOutFlags;
	asCArray<asCString *>      defaultArgs;
	bool                       isConstMethod;
	bool                       isConstructor;
	bool                       isDestructor;
	bool                       isPrivate;
	bool                       isOverride;
	bool                       isFinal;
	bool                       isShared;

	GetParsedFunctionDetails(funcDef->node, funcDef->script, 0, funcDef->name, returnType, parameterTypes, inOutFlags, defaultArgs, isConstMethod, isConstructor, isDestructor, isPrivate, isOverride, isFinal, isShared);

	asCScriptFunction *func = module->funcDefs[funcDef->idx];
	if( func )
	{
		func->returnType = returnType;
		for( asUINT p = 0; p < parameterTypes.GetLength(); p++ )
		{
			func->parameterTypes.PushLast(parameterTypes[p]);
			func->inOutFlags.PushLast(inOutFlags[p]);

			// Don't copy the default arg expression as it is not allowed for function definitions
		}
	}
}

int asCBuilder::RegisterGlobalVar(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	// Has the application disabled global vars?
	if( engine->ep.disallowGlobalVars )
	{
		int r, c;
		file->ConvertPosToRowCol(node->tokenPos, &r, &c);
		WriteError(file->name.AddressOf(), TXT_GLOBAL_VARS_NOT_ALLOWED, r, c);
	}

	// What data type is it?
	// TODO: namespace: Use correct implicit namespace
	asCDataType type = CreateDataTypeFromNode(node->firstChild, file, "");

	if( !type.CanBeInstanciated() )
	{
		asCString str;
		// TODO: Change to "'type' cannot be declared as variable"
		str.Format(TXT_DATA_TYPE_CANT_BE_s, type.Format().AddressOf());

		int r, c;
		file->ConvertPosToRowCol(node->tokenPos, &r, &c);

		WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
	}

	asCScriptNode *n = node->firstChild->next;

	while( n )
	{
		// Verify that the name isn't taken
		asCString name(&file->code[n->tokenPos], n->tokenLength);
		CheckNameConflict(name.AddressOf(), n, file, ns);

		// Register the global variable
		sGlobalVariableDescription *gvar = asNEW(sGlobalVariableDescription);
		if( gvar == 0 )
		{
			node->Destroy(engine);
			return asOUT_OF_MEMORY;
		}
			
		globVariables.PushLast(gvar);

		gvar->script      = file;
		gvar->name        = name;
		gvar->isCompiled  = false;
		gvar->datatype    = type;
		gvar->isEnumValue = false;

		// TODO: Give error message if wrong
		asASSERT(!gvar->datatype.IsReference());

		gvar->idNode = n;
		gvar->nextNode = 0;
		if( n->next &&
			(n->next->nodeType == snAssignment ||
			 n->next->nodeType == snArgList    ||
			 n->next->nodeType == snInitList     ) )
		{
			gvar->nextNode = n->next;
			n->next->DisconnectParent();
		}

		gvar->property = module->AllocateGlobalProperty(name.AddressOf(), gvar->datatype, ns);
		gvar->index    = gvar->property->id;

		n = n->next;
	}

	node->Destroy(engine);

	return 0;
}

int asCBuilder::RegisterClass(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	asCScriptNode *n = node->firstChild;
	bool isFinal = false;
	bool isShared = false;

	if( n->tokenType == ttIdentifier && file->TokenEquals(n->tokenPos, n->tokenLength, FINAL_TOKEN) )
	{
		isFinal = true;
		n = n->next;
	}

	if( n->tokenType == ttIdentifier && file->TokenEquals(n->tokenPos, n->tokenLength, SHARED_TOKEN) )
	{
		isShared = true;
		n = n->next;

		// Check for final again
		if( n->tokenType == ttIdentifier && file->TokenEquals(n->tokenPos, n->tokenLength, FINAL_TOKEN) )
		{
			isFinal = true;
			n = n->next;
		}
	}

	asCString name(&file->code[n->tokenPos], n->tokenLength);

	int r, c;
	file->ConvertPosToRowCol(n->tokenPos, &r, &c);

	CheckNameConflict(name.AddressOf(), n, file, ns);

	sClassDeclaration *decl = asNEW(sClassDeclaration);
	if( decl == 0 )
		return asOUT_OF_MEMORY;

	classDeclarations.PushLast(decl);
	decl->name             = name;
	decl->script           = file;
	decl->node             = node;

	// If this type is shared and there already exist another shared 
	// type of the same name, then that one should be used instead of
	// creating a new one.
	if( isShared )
	{
		for( asUINT n = 0; n < engine->classTypes.GetLength(); n++ )
		{
			asCObjectType *st = engine->classTypes[n];
			if( st &&
				st->IsShared() &&
				st->name == name &&
				st->nameSpace == ns &&
				!st->IsInterface() )
			{
				// We'll use the existing type
				decl->isExistingShared = true;
				decl->objType          = st;
				module->classTypes.PushLast(st);
				st->AddRef();
				return 0;
			}
		}
	}

	// Create a new object type for this class
	asCObjectType *st = asNEW(asCObjectType)(engine);
	if( st == 0 )
		return asOUT_OF_MEMORY;
	
	st->flags = asOBJ_REF | asOBJ_SCRIPT_OBJECT;

	if( isShared )
		st->flags |= asOBJ_SHARED;

	if( isFinal )
		st->flags |= asOBJ_NOINHERIT;

	if( node->tokenType == ttHandle )
		st->flags |= asOBJ_IMPLICIT_HANDLE;

	st->size      = sizeof(asCScriptObject);
	st->name      = name;
	st->nameSpace = ns;
	module->classTypes.PushLast(st);
	engine->classTypes.PushLast(st);
	st->AddRef();
	decl->objType = st;

	// Add script classes to the GC
	// TODO: runtime optimize: Only add the class to the GC when the module won't use the type anymore
	engine->gc.AddScriptObjectToGC(st, &engine->objectTypeBehaviours);

	// Use the default script class behaviours
	st->beh = engine->scriptTypeBehaviours.beh;

	// TODO: Move this to asCObjectType so that the asCRestore can reuse it
	engine->scriptFunctions[st->beh.addref]->AddRef();
	engine->scriptFunctions[st->beh.release]->AddRef();
	engine->scriptFunctions[st->beh.gcEnumReferences]->AddRef();
	engine->scriptFunctions[st->beh.gcGetFlag]->AddRef();
	engine->scriptFunctions[st->beh.gcGetRefCount]->AddRef();
	engine->scriptFunctions[st->beh.gcReleaseAllReferences]->AddRef();
	engine->scriptFunctions[st->beh.gcSetFlag]->AddRef();
	engine->scriptFunctions[st->beh.copy]->AddRef();
	engine->scriptFunctions[st->beh.factory]->AddRef();
	engine->scriptFunctions[st->beh.construct]->AddRef();
	for( asUINT i = 1; i < st->beh.operators.GetLength(); i += 2 )
		engine->scriptFunctions[st->beh.operators[i]]->AddRef();

	return 0;
}

int asCBuilder::RegisterInterface(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	asCScriptNode *n = node->firstChild;
	asCString name(&file->code[n->tokenPos], n->tokenLength);

	bool isShared = false;
	if( name == SHARED_TOKEN )
	{
		isShared = true;

		n = n->next;
		name.Assign(&file->code[n->tokenPos], n->tokenLength);
	}

	int r, c;
	file->ConvertPosToRowCol(n->tokenPos, &r, &c);

	CheckNameConflict(name.AddressOf(), n, file, ns);

	sClassDeclaration *decl = asNEW(sClassDeclaration);
	if( decl == 0 )
		return asOUT_OF_MEMORY;

	interfaceDeclarations.PushLast(decl);
	decl->name             = name;
	decl->script           = file;
	decl->node             = node;

	// If this type is shared and there already exist another shared 
	// type of the same name, then that one should be used instead of
	// creating a new one.
	if( isShared )
	{
		for( asUINT n = 0; n < engine->classTypes.GetLength(); n++ )
		{
			asCObjectType *st = engine->classTypes[n];
			if( st &&
				st->IsShared() &&
				st->name == name &&
				st->nameSpace == ns &&
				st->IsInterface() )
			{
				// We'll use the existing type
				decl->isExistingShared = true;
				decl->objType          = st;
				module->classTypes.PushLast(st);
				st->AddRef();
				return 0;
			}
		}
	}

	// Register the object type for the interface
	asCObjectType *st = asNEW(asCObjectType)(engine);
	if( st == 0 )
		return asOUT_OF_MEMORY;

	st->flags = asOBJ_REF | asOBJ_SCRIPT_OBJECT;

	if( isShared )
		st->flags |= asOBJ_SHARED;

	st->size = 0; // Cannot be instanciated
	st->name = name;
	st->nameSpace = ns;
	module->classTypes.PushLast(st);
	engine->classTypes.PushLast(st);
	st->AddRef();
	decl->objType = st;

	// Use the default script class behaviours
	st->beh.construct = 0;
	st->beh.addref = engine->scriptTypeBehaviours.beh.addref;
	engine->scriptFunctions[st->beh.addref]->AddRef();
	st->beh.release = engine->scriptTypeBehaviours.beh.release;
	engine->scriptFunctions[st->beh.release]->AddRef();
	st->beh.copy = 0;

	return 0;
}

void asCBuilder::CompileGlobalVariables()
{
	bool compileSucceeded = true;

	// Store state of compilation (errors, warning, output)
	int currNumErrors   = numErrors;
	int currNumWarnings = numWarnings;

	// Backup the original message stream
	bool                       msgCallback     = engine->msgCallback;
	asSSystemFunctionInterface msgCallbackFunc = engine->msgCallbackFunc;
	void                      *msgCallbackObj  = engine->msgCallbackObj;

	// Set the new temporary message stream
	asCOutputBuffer outBuffer;
	engine->SetMessageCallback(asMETHOD(asCOutputBuffer, Callback), &outBuffer, asCALL_THISCALL);

	asCOutputBuffer finalOutput;
	asCScriptFunction *initFunc = 0;

	asCArray<asCGlobalProperty*> initOrder;

	// We first try to compile all the primitive global variables, and only after that
	// compile the non-primitive global variables. This permits the constructors 
	// for the complex types to use the already initialized variables of primitive 
	// type. Note, we currently don't know which global variables are used in the 
	// constructors, so we cannot guarantee that variables of complex types are 
	// initialized in the correct order, so we won't reorder those.
	bool compilingPrimitives = true;

	// Compile each global variable
	while( compileSucceeded )
	{
		compileSucceeded = false;

		int accumErrors = 0;
		int accumWarnings = 0;

		// Restore state of compilation
		finalOutput.Clear();
		for( asUINT n = 0; n < globVariables.GetLength(); n++ )
		{
			sGlobalVariableDescription *gvar = globVariables[n];
			if( gvar->isCompiled )
				continue;

			asCByteCode init(engine);
			numWarnings = 0;
			numErrors = 0;
			outBuffer.Clear();

			// Skip this for now if we're not compiling complex types yet
			if( compilingPrimitives && !gvar->datatype.IsPrimitive() )
				continue;

			if( gvar->nextNode )
			{
				int r, c;
				gvar->script->ConvertPosToRowCol(gvar->nextNode->tokenPos, &r, &c);
				asCString str = gvar->datatype.Format();
				str += " " + gvar->name;
				str.Format(TXT_COMPILING_s, str.AddressOf());
				WriteInfo(gvar->script->name.AddressOf(), str.AddressOf(), r, c, true);
			}

			if( gvar->isEnumValue )
			{
				int r;
				if( gvar->nextNode )
				{
					asCCompiler comp(engine);
					asCScriptFunction func(engine, module, asFUNC_DUMMY);

					// Temporarily switch the type of the variable to int so it can be compiled properly
					asCDataType saveType;
					saveType = gvar->datatype;
					gvar->datatype = asCDataType::CreatePrimitive(ttInt, true);
					r = comp.CompileGlobalVariable(this, gvar->script, gvar->nextNode, gvar, &func);
					gvar->datatype = saveType;
				}
				else
				{
					r = 0;

					// When there is no assignment the value is the last + 1
					int enumVal = 0;
					if( n > 0 )
					{
						sGlobalVariableDescription *gvar2 = globVariables[n-1];
						if( gvar2->datatype == gvar->datatype )
						{
							// The integer value is stored in the lower bytes
							enumVal = (*(int*)&gvar2->constantValue) + 1;

							if( !gvar2->isCompiled )
							{
								// TODO: Need to get the correct script position
								int row, col;
								gvar->script->ConvertPosToRowCol(0, &row, &col);

								asCString str = gvar->datatype.Format();
								str += " " + gvar->name;
								str.Format(TXT_COMPILING_s, str.AddressOf());
								WriteInfo(gvar->script->name.AddressOf(), str.AddressOf(), row, col, true);

								str.Format(TXT_UNINITIALIZED_GLOBAL_VAR_s, gvar2->name.AddressOf());
								WriteError(gvar->script->name.AddressOf(), str.AddressOf(), row, col);
								r = -1;
							}
						}
					}

					// The integer value is stored in the lower bytes
					*(int*)&gvar->constantValue = enumVal;
				}

				if( r >= 0 )
				{
					// Set the value as compiled
					gvar->isCompiled = true;
					compileSucceeded = true;
				}
			}
			else
			{
				// Compile the global variable
				initFunc = asNEW(asCScriptFunction)(engine, module, asFUNC_DUMMY);
				if( initFunc == 0 )
				{
					// Out of memory
					return;
				}

				asCCompiler comp(engine);
				int r = comp.CompileGlobalVariable(this, gvar->script, gvar->nextNode, gvar, initFunc);
				if( r >= 0 )
				{
					// Compilation succeeded
					gvar->isCompiled = true;
					compileSucceeded = true;
				}
				else
				{
					// Compilation failed
					asDELETE(initFunc, asCScriptFunction);
					initFunc = 0;
				}
			}

			if( gvar->isCompiled )
			{
				// Add warnings for this constant to the total build
				if( numWarnings )
				{
					currNumWarnings += numWarnings;
					if( msgCallback )
						outBuffer.SendToCallback(engine, &msgCallbackFunc, msgCallbackObj);
				}

				// Determine order of variable initializations
				if( gvar->property && !gvar->isEnumValue )
					initOrder.PushLast(gvar->property);

				// Does the function contain more than just a SUSPEND followed by a RET instruction?
				if( initFunc && initFunc->byteCode.GetLength() > 2 )
				{
					// Create the init function for this variable
					initFunc->id = engine->GetNextScriptFunctionId();
					engine->SetScriptFunction(initFunc);

					// Finalize the init function for this variable
					initFunc->funcType = asFUNC_SCRIPT;
					initFunc->returnType = asCDataType::CreatePrimitive(ttVoid, false);
					initFunc->scriptSectionIdx = engine->GetScriptSectionNameIndex(gvar->script->name.AddressOf());

					// Notify the GC of the new script function
					engine->gc.AddScriptObjectToGC(initFunc, &engine->functionBehaviours);

					gvar->property->SetInitFunc(initFunc);

					initFunc->Release();
					initFunc = 0;
				}
				else if( initFunc )
				{
					// Destroy the function as it won't be used
					asDELETE(initFunc, asCScriptFunction);
					initFunc = 0;
				}

				// Convert enums to true enum values, so subsequent compilations can access it as an enum
				if( gvar->isEnumValue )
				{
					asCObjectType *objectType = gvar->datatype.GetObjectType();
					asASSERT(NULL != objectType);

					asSEnumValue *e = asNEW(asSEnumValue);
					if( e == 0 )
					{
						// Out of memory
						numErrors++;
						return;
					}

					e->name = gvar->name;
					e->value = *(int*)&gvar->constantValue;

					objectType->enumValues.PushLast(e);
				}
			}
			else
			{
				// Add output to final output
				finalOutput.Append(outBuffer);
				accumErrors += numErrors;
				accumWarnings += numWarnings;
			}

			preMessage.isSet = false;
		}

		if( !compileSucceeded )
		{
			if( compilingPrimitives )
			{
				// No more primitives could be compiled, so 
				// switch to compiling the complex variables
				compilingPrimitives = false;
				compileSucceeded    = true;
			}
			else
			{
				// No more variables can be compiled
				// Add errors and warnings to total build
				currNumWarnings += accumWarnings;
				currNumErrors   += accumErrors;
				if( msgCallback )
					finalOutput.SendToCallback(engine, &msgCallbackFunc, msgCallbackObj);
			}
		}
	}

	// Restore states
	engine->msgCallback     = msgCallback;
	engine->msgCallbackFunc = msgCallbackFunc;
	engine->msgCallbackObj  = msgCallbackObj;

	numWarnings = currNumWarnings;
	numErrors   = currNumErrors;

	// Set the correct order of initialization
	if( numErrors == 0 )
	{
		// If the length of the arrays are not the same, then this is the compilation 
		// of a single variable, in which case the initialization order of the previous 
		// variables must be preserved.
		if( module->scriptGlobals.GetLength() == initOrder.GetLength() )
			module->scriptGlobals = initOrder;
	}

	// Delete the enum expressions
	for( asUINT n = 0; n < globVariables.GetLength(); n++ )
	{
		sGlobalVariableDescription *gvar = globVariables[n];
		if( gvar->isEnumValue )
		{
			// Destroy the gvar property
			if( gvar->nextNode )
			{
				gvar->nextNode->Destroy(engine);
				gvar->nextNode = 0;
			}
			if( gvar->property )
			{
				asDELETE(gvar->property, asCGlobalProperty);
				gvar->property = 0;
			}

			asDELETE(gvar, sGlobalVariableDescription);
			globVariables[n] = 0;
		}
	}
}

void asCBuilder::CompileClasses()
{
	asUINT n;
	asCArray<sClassDeclaration*> toValidate((int)classDeclarations.GetLength());

	// Determine class inheritances and interfaces
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		sClassDeclaration *decl = classDeclarations[n];
		asCScriptCode *file = decl->script;

		// Find the base class that this class inherits from
		bool multipleInheritance = false;
		asCScriptNode *node = decl->node->firstChild;

		if( decl->objType->IsShared() )
		{
			// Skip the keyword 'shared'
			asASSERT(node->tokenType == ttIdentifier);
			node = node->next;
		}
		if( decl->objType->flags & asOBJ_NOINHERIT )
		{
			// skip the keyword 'final'
			asASSERT(node->tokenType == ttIdentifier);
			node = node->next;
		}

		// Skip the name of the class
		asASSERT(node->tokenType == ttIdentifier);
		node = node->next;

		while( node && node->nodeType == snIdentifier )
		{
			// Get the interface name from the node
			asCString name(&file->code[node->tokenPos], node->tokenLength);

			// Find the object type for the interface
			// TODO: namespace: Use correct namespace
			asCObjectType *objType = GetObjectType(name.AddressOf(), "");

			if( objType == 0 )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString str;
				str.Format(TXT_IDENTIFIER_s_NOT_DATA_TYPE, name.AddressOf());
				WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
			}
			else if( !(objType->flags & asOBJ_SCRIPT_OBJECT) || 
					 objType->flags & asOBJ_NOINHERIT )
			{
				// Either the class is not a script class or interface
				// or the class has been declared as 'final'
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString str;
				str.Format(TXT_CANNOT_INHERIT_FROM_s_FINAL, objType->name.AddressOf());
				WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
			}
			else if( objType->size != 0 )
			{
				// The class inherits from another script class
				if( !decl->isExistingShared && decl->objType->derivedFrom != 0 )
				{
					if( !multipleInheritance )
					{
						int r, c;
						file->ConvertPosToRowCol(node->tokenPos, &r, &c);
						WriteError(file->name.AddressOf(), TXT_CANNOT_INHERIT_FROM_MULTIPLE_CLASSES, r, c);
						multipleInheritance = true;
					}
				}
				else
				{
					// Make sure none of the base classes inherit from this one
					asCObjectType *base = objType;
					bool error = false;
					while( base != 0 )
					{
						if( base == decl->objType )
						{
							int r, c;
							file->ConvertPosToRowCol(node->tokenPos, &r, &c);
							WriteError(file->name.AddressOf(), TXT_CANNOT_INHERIT_FROM_SELF, r, c);
							error = true;
							break;
						}

						base = base->derivedFrom;
					}

					if( !error )
					{
						// A shared type may only inherit from other shared types
						if( (decl->objType->IsShared()) && !(objType->IsShared()) )
						{
							int r, c;
							file->ConvertPosToRowCol(node->tokenPos, &r, &c);
							asCString msg;
							msg.Format(TXT_SHARED_CANNOT_INHERIT_FROM_NON_SHARED_s, objType->name.AddressOf());
							WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
							error = true;
						}
					}

					if( !error )
					{
						if( decl->isExistingShared )
						{
							// Verify that the base class is the same as the original shared type
							if( decl->objType->derivedFrom != objType )
							{
								int r, c;
								file->ConvertPosToRowCol(node->tokenPos, &r, &c);
								WriteError(file->name.AddressOf(), TXT_SHARED_DOESNT_MATCH_ORIGINAL, r, c);
							}
						}
						else
						{
							// Set the base class
							decl->objType->derivedFrom = objType;
							objType->AddRef();
						}
					}
				}
			}
			else
			{
				// The class implements an interface
				if( !decl->isExistingShared && decl->objType->Implements(objType) )
				{
					int r, c;
					file->ConvertPosToRowCol(node->tokenPos, &r, &c);
					asCString msg;
					msg.Format(TXT_INTERFACE_s_ALREADY_IMPLEMENTED, objType->GetName());
					WriteWarning(file->name.AddressOf(), msg.AddressOf(), r, c);
				}
				else
				{
					// A shared type may only implement from shared interfaces
					if( (decl->objType->IsShared()) && !(objType->IsShared()) )
					{
						int r, c;
						file->ConvertPosToRowCol(node->tokenPos, &r, &c);
						asCString msg;
						msg.Format(TXT_SHARED_CANNOT_IMPLEMENT_NON_SHARED_s, objType->name.AddressOf());
						WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
					}
					else
					{
						if( decl->isExistingShared )
						{
							// Verify that the original implements the same interface
							if( !decl->objType->Implements(objType) )
							{
								int r, c;
								file->ConvertPosToRowCol(node->tokenPos, &r, &c);
								WriteError(file->name.AddressOf(), TXT_SHARED_DOESNT_MATCH_ORIGINAL, r, c);
							}
						}
						else
						{
							decl->objType->interfaces.PushLast(objType);
						}
					}
				}
			}

			node = node->next;
		}
	}

	// Order class declarations so that base classes are compiled before derived classes.
	// This will allow the derived classes to copy properties and methods in the next step.
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		sClassDeclaration *decl = classDeclarations[n];
		asCObjectType *derived = decl->objType;
		asCObjectType *base = derived->derivedFrom;

		if( base == 0 ) continue;

		// If the base class is found after the derived class, then move the derived class to the end of the list
		for( asUINT m = n+1; m < classDeclarations.GetLength(); m++ )
		{
			sClassDeclaration *declBase = classDeclarations[m];
			if( base == declBase->objType )
			{
				classDeclarations.RemoveIndex(n);
				classDeclarations.PushLast(decl);

				// Decrease index so that we don't skip an entry
				n--;
				break;
			}
		}
	}

	// Go through each of the classes and register the object type descriptions
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		sClassDeclaration *decl = classDeclarations[n];
		if( decl->isExistingShared )
		{
			// TODO: shared: Should really validate against original

			// Set the declaration as validated already, so that other
			// types that contain this will accept this type
			decl->validState = 1;
			continue;
		}

		// Add all properties and methods from the base class
		if( decl->objType->derivedFrom )
		{
			asCObjectType *baseType = decl->objType->derivedFrom;

			// The derived class inherits all interfaces from the base class
			for( unsigned int n = 0; n < baseType->interfaces.GetLength(); n++ )
			{
				if( !decl->objType->Implements(baseType->interfaces[n]) )
				{
					decl->objType->interfaces.PushLast(baseType->interfaces[n]);
				}
				else
				{
					// Warn if derived class already implements the interface
					int r, c;
					decl->script->ConvertPosToRowCol(decl->node->tokenPos, &r, &c);
					asCString msg;
					msg.Format(TXT_INTERFACE_s_ALREADY_IMPLEMENTED, baseType->interfaces[n]->GetName());
					WriteWarning(decl->script->name.AddressOf(), msg.AddressOf(), r, c);
				}
			}

			// TODO: Need to check for name conflict with new class methods

			// Copy properties from base class to derived class
			for( asUINT p = 0; p < baseType->properties.GetLength(); p++ )
			{
				asCObjectProperty *prop = AddPropertyToClass(decl, baseType->properties[p]->name, baseType->properties[p]->type, baseType->properties[p]->isPrivate);

				// The properties must maintain the same offset
				asASSERT(prop && prop->byteOffset == baseType->properties[p]->byteOffset); UNUSED_VAR(prop);
			}

			// Copy methods from base class to derived class
			for( asUINT m = 0; m < baseType->methods.GetLength(); m++ )
			{
				// If the derived class implements the same method, then don't add the base class' method
				asCScriptFunction *baseFunc = GetFunctionDescription(baseType->methods[m]);
				asCScriptFunction *derivedFunc = 0;
				bool found = false;
				for( asUINT d = 0; d < decl->objType->methods.GetLength(); d++ )
				{
					derivedFunc = GetFunctionDescription(decl->objType->methods[d]);
					if( derivedFunc->IsSignatureEqual(baseFunc) )
					{
						if( baseFunc->IsFinal() )
						{
							int r, c;
							decl->script->ConvertPosToRowCol(decl->node->tokenPos, &r, &c);
							asCString msg;
							msg.Format(TXT_METHOD_CANNOT_OVERRIDE_s, baseFunc->GetDeclaration());
							WriteError(decl->script->name.AddressOf(), msg.AddressOf(), r, c);
						}

						// Move the function from the methods array to the virtualFunctionTable
						decl->objType->methods.RemoveIndex(d);
						decl->objType->virtualFunctionTable.PushLast(derivedFunc);
						found = true;
						break;
					}
				}

				if( !found )
				{
					// Push the base class function on the virtual function table
					decl->objType->virtualFunctionTable.PushLast(baseType->virtualFunctionTable[m]);
					baseType->virtualFunctionTable[m]->AddRef();
				}

				decl->objType->methods.PushLast(baseType->methods[m]);
				engine->scriptFunctions[baseType->methods[m]]->AddRef();
			}
		}

		// Move this class' methods into the virtual function table
		for( asUINT m = 0; m < decl->objType->methods.GetLength(); m++ )
		{
			asCScriptFunction *func = GetFunctionDescription(decl->objType->methods[m]);
			if( func->funcType != asFUNC_VIRTUAL )
			{
				// Move the reference from the method list to the virtual function list
				decl->objType->methods.RemoveIndex(m);
				decl->objType->virtualFunctionTable.PushLast(func);

				// Substitute the function description in the method list for a virtual method
				// Make sure the methods are in the same order as the virtual function table
				decl->objType->methods.PushLast(CreateVirtualFunction(func, (int)decl->objType->virtualFunctionTable.GetLength() - 1));
				m--;
			}
		}

		// Enumerate each of the declared properties
		asCScriptNode *node = decl->node->firstChild->next;
		if( decl->objType->IsShared() )
			node = node->next;
		if( decl->objType->flags & asOBJ_NOINHERIT )
			node = node->next;

		// Skip list of classes and interfaces
		while( node && node->nodeType == snIdentifier )
			node = node->next;

		while( node )
		{
			if( node->nodeType == snDeclaration )
			{
				bool isPrivate = false;
				if( node->firstChild && node->firstChild->tokenType == ttPrivate )
					isPrivate = true;

				asCScriptCode *file = decl->script;
				// TODO: namespace: Use correct implicit namespace
				asCDataType dt = CreateDataTypeFromNode(isPrivate ? node->firstChild->next : node->firstChild, file, "");
				asCString name(&file->code[node->lastChild->tokenPos], node->lastChild->tokenLength);

				if( decl->objType->IsShared() && dt.GetObjectType() && !dt.GetObjectType()->IsShared() )
				{
					int r, c;
					file->ConvertPosToRowCol(node->tokenPos, &r, &c);
					asCString msg;
					msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, dt.GetObjectType()->name.AddressOf());
					WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
				}

				if( dt.IsReadOnly() )
				{
					int r, c;
					file->ConvertPosToRowCol(node->tokenPos, &r, &c);

					WriteError(file->name.AddressOf(), TXT_PROPERTY_CANT_BE_CONST, r, c);
				}

				CheckNameConflictMember(decl->objType, name.AddressOf(), node->lastChild, file, true);

				AddPropertyToClass(decl, name, dt, isPrivate, file, node);
			}
			else
				asASSERT(false);

			node = node->next;
		}

		toValidate.PushLast(decl);
	}

	// TODO: Warn if a method overrides a base method without marking it as 'override'. 
	//       It must be possible to turn off this warning through engine property.

	// TODO: A base class should be able to mark a method as 'abstract'. This will
	//       allow a base class to provide a partial implementation, but still force
	//       derived classes to implement specific methods.

	// Verify that all interface methods are implemented in the classes
	// We do this here so the base class' methods have already been inherited 
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		sClassDeclaration *decl = classDeclarations[n];
		if( decl->isExistingShared ) continue;

		asCArray<bool> overrideValidations(decl->objType->GetMethodCount());
		for( asUINT k = 0; k < decl->objType->methods.GetLength(); k++ )
		{
			overrideValidations.PushLast( !static_cast<asCScriptFunction*>(decl->objType->GetMethodByIndex(k, false))->IsOverride() );
		}

		for( asUINT m = 0; m < decl->objType->interfaces.GetLength(); m++ )
		{
			asCObjectType *objType = decl->objType->interfaces[m];
			for( asUINT i = 0; i < objType->methods.GetLength(); i++ )
			{
				asUINT overrideIndex;
				if( !DoesMethodExist(decl->objType, objType->methods[i], &overrideIndex) )
				{
					int r, c;
					decl->script->ConvertPosToRowCol(decl->node->tokenPos, &r, &c);
					asCString str;
					str.Format(TXT_MISSING_IMPLEMENTATION_OF_s,
						engine->GetFunctionDeclaration(objType->methods[i]).AddressOf());
					WriteError(decl->script->name.AddressOf(), str.AddressOf(), r, c);
				}
				else
					overrideValidations[overrideIndex] = true;
			}
		}

		bool hasBaseClass = decl->objType->derivedFrom != 0;

		for( asUINT j = 0; j < overrideValidations.GetLength(); j++ )
		{
			if( !overrideValidations[j] && (!hasBaseClass || !DoesMethodExist(decl->objType->derivedFrom, decl->objType->methods[j])) )
			{
				int r, c;
				decl->script->ConvertPosToRowCol(decl->node->tokenPos, &r, &c);
				asCString msg;
				msg.Format(TXT_METHOD_s_DOES_NOT_OVERRIDE, decl->objType->GetMethodByIndex(j, false)->GetDeclaration());
				WriteError(decl->script->name.AddressOf(), msg.AddressOf(), r, c);
			}
		}
	}

	// Verify that the declared structures are valid, e.g. that the structure
	// doesn't contain a member of its own type directly or indirectly
	while( toValidate.GetLength() > 0 )
	{
		asUINT numClasses = (asUINT)toValidate.GetLength();

		asCArray<sClassDeclaration*> toValidateNext((int)toValidate.GetLength());
		while( toValidate.GetLength() > 0 )
		{
			sClassDeclaration *decl = toValidate[toValidate.GetLength()-1];
			int validState = 1;
			for( asUINT n = 0; n < decl->objType->properties.GetLength(); n++ )
			{
				// A valid structure is one that uses only primitives or other valid objects
				asCObjectProperty *prop = decl->objType->properties[n];
				asCDataType dt = prop->type;

				if( dt.IsTemplate() )
				{
					asCDataType sub = dt;
					while( sub.IsTemplate() && !sub.IsObjectHandle() )
						sub = sub.GetSubType();

					dt = sub;
				}

				if( dt.IsObject() && !dt.IsObjectHandle() )
				{
					// Find the class declaration
					sClassDeclaration *pdecl = 0;
					for( asUINT p = 0; p < classDeclarations.GetLength(); p++ )
					{
						if( classDeclarations[p]->objType == dt.GetObjectType() )
						{
							pdecl = classDeclarations[p];
							break;
						}
					}

					if( pdecl )
					{
						if( pdecl->objType == decl->objType )
						{
							int r, c;
							decl->script->ConvertPosToRowCol(decl->node->tokenPos, &r, &c);
							WriteError(decl->script->name.AddressOf(), TXT_ILLEGAL_MEMBER_TYPE, r, c);
							validState = 2;
							break;
						}
						else if( pdecl->validState != 1 )
						{
							validState = pdecl->validState;
							break;
						}
					}
				}
			}

			if( validState == 1 )
			{
				decl->validState = 1;
				toValidate.PopLast();
			}
			else if( validState == 2 )
			{
				decl->validState = 2;
				toValidate.PopLast();
			}
			else
			{
				toValidateNext.PushLast(toValidate.PopLast());
			}
		}

		toValidate = toValidateNext;
		toValidateNext.SetLength(0);

		if( numClasses == toValidate.GetLength() )
		{
			int r, c;
			toValidate[0]->script->ConvertPosToRowCol(toValidate[0]->node->tokenPos, &r, &c);
			WriteError(toValidate[0]->script->name.AddressOf(), TXT_ILLEGAL_MEMBER_TYPE, r, c);
			break;
		}
	}

	if( numErrors > 0 ) return;


	// Urho3D: disable garbage collection from script classes
	/*
	// Verify potential circular references
	for( n = 0; n < classDeclarations.GetLength(); n++ )
	{
		sClassDeclaration *decl = classDeclarations[n];
		if( decl->isExistingShared ) continue;
		asCObjectType *ot = decl->objType;

		// Is there some path in which this structure is involved in circular references?
		for( asUINT p = 0; p < ot->properties.GetLength(); p++ )
		{
			asCDataType dt = ot->properties[p]->type;
			if( dt.IsObject() )
			{
				if( dt.IsObjectHandle() )
				{
					// TODO: runtime optimize: If it is known that the handle can't be involved in a circular reference
					//                         then this object doesn't need to be marked as garbage collected. 
					//                         - The application could set a flag when registering the object.
					//                         - The script classes can be marked as final, then the compiler will 
					//                           be able to determine whether the class is garbage collected or not.

					ot->flags |= asOBJ_GC;
					break;
				}
				else if( dt.GetObjectType()->flags & asOBJ_GC )
				{
					// TODO: runtime optimize: Just because the member type is a potential circle doesn't mean that this one is
					//                         Only if the object is of a type that can reference this type, either directly or indirectly

					ot->flags |= asOBJ_GC;
					break;
				}
			}
		}
	}
	*/
}

int asCBuilder::CreateVirtualFunction(asCScriptFunction *func, int idx)
{
	asCScriptFunction *vf = asNEW(asCScriptFunction)(engine, module, asFUNC_VIRTUAL);
	if( vf == 0 )
		return asOUT_OF_MEMORY;

	vf->funcType         = asFUNC_VIRTUAL;
	vf->name             = func->name;
	vf->returnType       = func->returnType;
	vf->parameterTypes   = func->parameterTypes;
	vf->inOutFlags       = func->inOutFlags;
	vf->id               = engine->GetNextScriptFunctionId();
	vf->scriptSectionIdx = func->scriptSectionIdx;
	vf->isReadOnly       = func->isReadOnly;
	vf->objectType       = func->objectType;
	vf->signatureId      = func->signatureId;
	vf->isPrivate        = func->isPrivate;
	vf->isFinal          = func->isFinal;
	vf->isOverride       = func->isOverride;
	vf->vfTableIdx       = idx;
	vf->defaultArgs      = func->defaultArgs;

	// Copy the default arg strings to avoid multiple deletes on the same object
	for( asUINT n = 0; n < vf->defaultArgs.GetLength(); n++ )
		if( vf->defaultArgs[n] )
			vf->defaultArgs[n] = asNEW(asCString)(*vf->defaultArgs[n]);

	module->AddScriptFunction(vf);

	// Add a dummy to the builder so that it doesn't mix up function ids
	functions.PushLast(0);

	return vf->id;
}

asCObjectProperty *asCBuilder::AddPropertyToClass(sClassDeclaration *decl, const asCString &name, const asCDataType &dt, bool isPrivate, asCScriptCode *file, asCScriptNode *node)
{
	if( !dt.CanBeInstanciated() )
	{
		if( file && node )
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);
			asCString str;
			str.Format(TXT_DATA_TYPE_CANT_BE_s, dt.Format().AddressOf());
			WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
		}
		return 0;
	}

	return decl->objType->AddPropertyToClass(name, dt, isPrivate);
}

bool asCBuilder::DoesMethodExist(asCObjectType *objType, int methodId, asUINT *methodIndex)
{
	asCScriptFunction *method = GetFunctionDescription(methodId);

	for( asUINT n = 0; n < objType->methods.GetLength(); n++ )
	{
		asCScriptFunction *m = GetFunctionDescription(objType->methods[n]);

		if( m->name           != method->name           ) continue;
		if( m->returnType     != method->returnType     ) continue;
		if( m->isReadOnly     != method->isReadOnly     ) continue;
		if( m->parameterTypes != method->parameterTypes ) continue;
		if( m->inOutFlags     != method->inOutFlags     ) continue;

		if( methodIndex )
			*methodIndex = n;

		return true;
	}

	return false;
}

void asCBuilder::AddDefaultConstructor(asCObjectType *objType, asCScriptCode *file)
{
	int funcId = engine->GetNextScriptFunctionId();

	asCDataType returnType = asCDataType::CreatePrimitive(ttVoid, false);
	asCArray<asCDataType> parameterTypes;
	asCArray<asETypeModifiers> inOutFlags;
	asCArray<asCString *> defaultArgs;

	// Add the script function
	module->AddScriptFunction(file->idx, funcId, objType->name.AddressOf(), returnType, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), false, objType);

	// Set it as default constructor
	if( objType->beh.construct )
		engine->scriptFunctions[objType->beh.construct]->Release();
	objType->beh.construct = funcId;
	objType->beh.constructors[0] = funcId;
	engine->scriptFunctions[funcId]->AddRef();

	// The bytecode for the default constructor will be generated
	// only after the potential inheritance has been established
	sFunctionDescription *func = asNEW(sFunctionDescription);
	if( func == 0 )
	{
		// Out of memory
		return;
	}

	functions.PushLast(func);

	func->script            = file;
	func->node              = 0;
	func->name              = objType->name;
	func->objType           = objType;
	func->funcId            = funcId;
	func->explicitSignature = 0;

	// Add a default factory as well
	funcId = engine->GetNextScriptFunctionId();
	if( objType->beh.factory )
		engine->scriptFunctions[objType->beh.factory]->Release();
	objType->beh.factory = funcId;
	objType->beh.factories[0] = funcId;
	returnType = asCDataType::CreateObjectHandle(objType, false);
	module->AddScriptFunction(file->idx, funcId, objType->name.AddressOf(), returnType, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), false);
	functions.PushLast(0);
	asCCompiler compiler(engine);
	compiler.CompileFactory(this, file, engine->scriptFunctions[funcId]);
	engine->scriptFunctions[funcId]->AddRef();

	// If the object is shared, then the factory must also be marked as shared
	if( objType->flags & asOBJ_SHARED )
		engine->scriptFunctions[funcId]->isShared = true;
}

int asCBuilder::RegisterEnum(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	// Is it a shared enum?
	bool isShared = false;
	asCObjectType *existingSharedType = 0;
	asCScriptNode *tmp = node->firstChild;
	if( tmp->nodeType == snIdentifier && file->TokenEquals(tmp->tokenPos, tmp->tokenLength, SHARED_TOKEN) )
	{
		isShared = true;
		tmp = tmp->next;
	}

	// Grab the name of the enumeration
	asCString name;
	asASSERT(snDataType == tmp->nodeType);
	asASSERT(snIdentifier == tmp->firstChild->nodeType);
	name.Assign(&file->code[tmp->firstChild->tokenPos], tmp->firstChild->tokenLength);

	if( isShared )
	{
		// Look for a pre-existing shared enum with the same signature
		for( asUINT n = 0; n < engine->classTypes.GetLength(); n++ )
		{
			asCObjectType *o = engine->classTypes[n];
			if( o &&
				o->IsShared() &&
				(o->flags & asOBJ_ENUM) &&
				o->name == name &&
				o->nameSpace == ns )
			{
				existingSharedType = o;
				break;
			}
		}
	}

	// Check the name and add the enum
	int r = CheckNameConflict(name.AddressOf(), tmp->firstChild, file, ns);
	if( asSUCCESS == r )
	{
		asCObjectType *st;

		if( existingSharedType )
			st = existingSharedType;
		else
		{
			st = asNEW(asCObjectType)(engine);
			if( st == 0 )
				return asOUT_OF_MEMORY;

			st->flags     = asOBJ_ENUM;
			if( isShared )
				st->flags |= asOBJ_SHARED;
			st->size      = 4;
			st->name      = name;
			st->nameSpace = ns;
		}
		module->enumTypes.PushLast(st);
		st->AddRef();

		// TODO: cleanup: Should the enum type really be stored in the engine->classTypes? 
		//                http://www.gamedev.net/topic/616912-c-header-file-shared-with-scripts/page__gopid__4895940
		if( !existingSharedType )
			engine->classTypes.PushLast(st);

		// Store the location of this declaration for reference in name collisions
		sClassDeclaration *decl = asNEW(sClassDeclaration);
		if( decl == 0 )
			return asOUT_OF_MEMORY;

		decl->name             = name;
		decl->script           = file;
		decl->objType          = st;
		namedTypeDeclarations.PushLast(decl);

		asCDataType type = CreateDataTypeFromNode(tmp, file, ns);
		asASSERT(!type.IsReference());
		
		// Register the enum values
		tmp = tmp->next;
		while( tmp )
		{
			asASSERT(snIdentifier == tmp->nodeType);

			asCString name(&file->code[tmp->tokenPos], tmp->tokenLength);

			if( existingSharedType )
			{
				// If this is a pre-existent shared enum, then just double check 
				// that the value is already defined in the original declaration
				bool found = false;
				for( size_t n = 0; n < st->enumValues.GetLength(); n++ )
					if( st->enumValues[n]->name == name )
					{
						found = true;
						break;
					}

				if( !found )
				{
					int r, c;
					file->ConvertPosToRowCol(tmp->tokenPos, &r, &c);
					WriteError(file->name.AddressOf(), TXT_SHARED_DOESNT_MATCH_ORIGINAL, r, c);
					break;
				}

				tmp = tmp->next;
				if( tmp && tmp->nodeType == snAssignment )
					tmp = tmp->next;
				continue;
			}
			else
			{
				// Check for name conflict errors with other values in the enum
				r = 0;
				for( size_t n = globVariables.GetLength(); n-- > 0; )
				{
					sGlobalVariableDescription *gvar = globVariables[n];
					if( gvar->datatype != type )
						break;

					if( gvar->name == name &&
						gvar->property->nameSpace == ns )
					{
						r = asNAME_TAKEN;
						break;
					}
				}
				if( asSUCCESS != r )
				{
					int r, c;
					file->ConvertPosToRowCol(tmp->tokenPos, &r, &c);

					asCString str;
					str.Format(TXT_NAME_CONFLICT_s_ALREADY_USED, name.AddressOf());
					WriteError(file->name.AddressOf(), str.AddressOf(), r, c);

					tmp = tmp->next;
					if( tmp && tmp->nodeType == snAssignment )
						tmp = tmp->next;
					continue;
				}

				// Check for assignment
				asCScriptNode *asnNode = tmp->next;
				if( asnNode && snAssignment == asnNode->nodeType )
					asnNode->DisconnectParent();
				else
					asnNode = 0;

				// Create the global variable description so the enum value can be evaluated
				sGlobalVariableDescription *gvar = asNEW(sGlobalVariableDescription);
				if( gvar == 0 )
					return asOUT_OF_MEMORY;

				globVariables.PushLast(gvar);

				gvar->script		  = file;
				gvar->idNode          = 0;
				gvar->nextNode		  = asnNode;
				gvar->name			  = name;
				gvar->datatype		  = type;
				// No need to allocate space on the global memory stack since the values are stored in the asCObjectType
				gvar->index			  = 0;
				gvar->isCompiled	  = false;
				gvar->isPureConstant  = true;
				gvar->isEnumValue     = true;
				gvar->constantValue   = 0xdeadbeef;

				// Allocate dummy property so we can compile the value. 
				// This will be removed later on so we don't add it to the engine.
				gvar->property            = asNEW(asCGlobalProperty);
				if( gvar->property == 0 )
					return asOUT_OF_MEMORY;

				gvar->property->name      = name;
				gvar->property->nameSpace = ns;
				gvar->property->type      = gvar->datatype;
				gvar->property->id        = 0;

				tmp = tmp->next;
			}
		}
	}

	node->Destroy(engine);

	return r;
}

int asCBuilder::RegisterTypedef(asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	// Get the native data type
	asCScriptNode *tmp = node->firstChild;
	asASSERT(NULL != tmp && snDataType == tmp->nodeType);
	asCDataType dataType;
	dataType.CreatePrimitive(tmp->tokenType, false);
	dataType.SetTokenType(tmp->tokenType);
	tmp = tmp->next;

	// Grab the name of the typedef
	asASSERT(NULL != tmp && NULL == tmp->next);
	asCString name;
	name.Assign(&file->code[tmp->tokenPos], tmp->tokenLength);

	// If the name is not already in use add it
 	int r = CheckNameConflict(name.AddressOf(), tmp, file, ns);

	asCObjectType *st = 0;
	if( asSUCCESS == r )
	{
		// Create the new type
		st = asNEW(asCObjectType)(engine);
		if( st == 0 )
			r = asOUT_OF_MEMORY;
	}

	if( asSUCCESS == r )
	{
		st->flags           = asOBJ_TYPEDEF;
		st->size            = dataType.GetSizeInMemoryBytes();
		st->name            = name;
		st->nameSpace       = ns;
		st->templateSubType = dataType;

		st->AddRef();

		module->typeDefs.PushLast(st);
		engine->classTypes.PushLast(st);

		// Store the location of this declaration for reference in name collisions
		sClassDeclaration *decl = asNEW(sClassDeclaration);
		if( decl == 0 )
			r = asOUT_OF_MEMORY;
		else
		{
			decl->name             = name;
			decl->script           = file;
			decl->objType          = st;
			namedTypeDeclarations.PushLast(decl);
		}
	}

	node->Destroy(engine);

	return r;
}

void asCBuilder::GetParsedFunctionDetails(asCScriptNode *node, asCScriptCode *file, asCObjectType *objType, asCString &name, asCDataType &returnType, asCArray<asCDataType> &parameterTypes, asCArray<asETypeModifiers> &inOutFlags, asCArray<asCString *> &defaultArgs, bool &isConstMethod, bool &isConstructor, bool &isDestructor, bool &isPrivate, bool &isOverride, bool &isFinal, bool &isShared)
{
	node = node->firstChild;

	// Is the function a private class method?
	isPrivate = false;
	if( node->tokenType == ttPrivate )
	{
		isPrivate = true;
		node = node->next;
	}

	// Is the function shared?
	isShared = false;
	if( node->tokenType == ttIdentifier && file->TokenEquals(node->tokenPos, node->tokenLength, SHARED_TOKEN) )
	{
		isShared = true;
		node = node->next;
	}

	// Find the name
	isConstructor = false;
	isDestructor = false;
	asCScriptNode *n = 0;
	if( node->nodeType == snDataType )
		n = node->next->next;
	else
	{
		// If the first node is a ~ token, then we know it is a destructor
		if( node->tokenType == ttBitNot )
		{
			n = node->next;
			isDestructor = true;
		}
		else
		{
			n = node;
			isConstructor = true;
		}
	}
	name.Assign(&file->code[n->tokenPos], n->tokenLength);

	// Initialize a script function object for registration
	if( !isConstructor && !isDestructor )
	{
		// TODO: namespace: Use correct implicit namespace
		returnType = CreateDataTypeFromNode(node, file, "");
		returnType = ModifyDataTypeFromNode(returnType, node->next, file, 0, 0);
	}
	else
		returnType = asCDataType::CreatePrimitive(ttVoid, false);

	isConstMethod = false;
	isFinal = false;
	isOverride = false;

	if( objType && n->next->next )
	{
		asCScriptNode *decorator = n->next->next;

		// Is this a const method?
		if( decorator->tokenType == ttConst )
		{
			isConstMethod = true;
			decorator = decorator->next;
		}

		while( decorator )
		{
			if( decorator->tokenType == ttIdentifier && file->TokenEquals(decorator->tokenPos, decorator->tokenLength, FINAL_TOKEN) )
				isFinal = true;
			else if( decorator->tokenType == ttIdentifier && file->TokenEquals(decorator->tokenPos, decorator->tokenLength, OVERRIDE_TOKEN) )
				isOverride = true;

			decorator = decorator->next;
		}
	}

	// Count the number of parameters
	int count = 0;
	asCScriptNode *c = n->next->firstChild;
	while( c )
	{
		count++;
		c = c->next->next;
		if( c && c->nodeType == snIdentifier )
			c = c->next;
		if( c && c->nodeType == snExpression )
			c = c->next;
	}

	// Get the parameter types
	parameterTypes.Allocate(count, false);
	inOutFlags.Allocate(count, false);
	defaultArgs.Allocate(count, false);
	n = n->next->firstChild;
	while( n )
	{
		asETypeModifiers inOutFlag;
		// TODO: namespace: Use correct implicit namespace
		asCDataType type = CreateDataTypeFromNode(n, file, "");
		type = ModifyDataTypeFromNode(type, n->next, file, &inOutFlag, 0);

		// Store the parameter type
		parameterTypes.PushLast(type);
		inOutFlags.PushLast(inOutFlag);

		// Move to next parameter
		n = n->next->next;
		if( n && n->nodeType == snIdentifier )
			n = n->next;
		
		if( n && n->nodeType == snExpression )
		{
			// Strip out white space and comments to better share the string
			asCString *defaultArgStr = asNEW(asCString);
			if( defaultArgStr )
				*defaultArgStr = GetCleanExpressionString(n, file);
			defaultArgs.PushLast(defaultArgStr);

			n = n->next;
		}
		else
			defaultArgs.PushLast(0);
	}
}
#endif

asCString asCBuilder::GetCleanExpressionString(asCScriptNode *node, asCScriptCode *file)
{
	asASSERT(node && node->nodeType == snExpression);

	asCString str;
	str.Assign(file->code + node->tokenPos, node->tokenLength);

	asCString cleanStr;
	for( asUINT n = 0; n < str.GetLength(); )
	{
		int len;
		asETokenClass tok = engine->ParseToken(str.AddressOf() + n, str.GetLength() - n, &len);
		if( tok != asTC_COMMENT && tok != asTC_WHITESPACE )
		{
			if( cleanStr.GetLength() ) cleanStr += " ";
			cleanStr.Concatenate(str.AddressOf() + n, len);
		}
		n += len;
	}

	return cleanStr;
}

#ifndef AS_NO_COMPILER
int asCBuilder::RegisterScriptFunction(int funcId, asCScriptNode *node, asCScriptCode *file, asCObjectType *objType, bool isInterface, bool isGlobalFunction, const asCString &ns, bool isExistingShared)
{
	asCString                  name;
	asCDataType                returnType;
	asCArray<asCDataType>      parameterTypes;
	asCArray<asETypeModifiers> inOutFlags;
	asCArray<asCString *>      defaultArgs;
	bool                       isConstMethod;
	bool                       isOverride;
	bool                       isFinal;
	bool                       isConstructor;
	bool                       isDestructor;
	bool                       isPrivate;
	bool                       isShared;

	GetParsedFunctionDetails(node, file, objType, name, returnType, parameterTypes, inOutFlags, defaultArgs, isConstMethod, isConstructor, isDestructor, isPrivate, isOverride, isFinal, isShared);

	if( isExistingShared ) 
	{
		asASSERT( objType );

		// Should validate that the function really exists in the class/interface
		bool found = false;
		if( isConstructor || isDestructor )
		{
			// TODO: shared: Should check the existance of these too
			found = true;
		}
		else
		{
			for( asUINT n = 0; n < objType->methods.GetLength(); n++ )
			{
				asCScriptFunction *func = engine->scriptFunctions[objType->methods[n]];
				if( func->name == name &&
					func->IsSignatureExceptNameEqual(returnType, parameterTypes, inOutFlags, objType, isConstMethod) )
				{
					found = true;
					break;
				}
			}
		}

		if( !found )
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);
			WriteError(file->name.AddressOf(), TXT_SHARED_DOESNT_MATCH_ORIGINAL, r, c);
		}

		node->Destroy(engine);
		return 0;
	}

	// Check for name conflicts
	if( !isConstructor && !isDestructor )
	{
		if( objType )
		{
			CheckNameConflictMember(objType, name.AddressOf(), node, file, false);

			if( name == objType->name )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);
				WriteError(file->name.AddressOf(), TXT_METHOD_CANT_HAVE_NAME_OF_CLASS, r, c);
			}
		}
		else
		{
			CheckNameConflict(name.AddressOf(), node, file, ns);
		}
	}
	else
	{
		// Verify that the name of the constructor/destructor is the same as the class
		if( name != objType->name )
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);
			WriteError(file->name.AddressOf(), TXT_CONSTRUCTOR_NAME_ERROR, r, c);
		}

		if( isDestructor )
			name = "~" + name;
	}

	isExistingShared = false;
	if( !isInterface )
	{
		sFunctionDescription *func = asNEW(sFunctionDescription);
		if( func == 0 )
			return asOUT_OF_MEMORY;

		functions.PushLast(func);

		func->script            = file;
		func->node              = node;
		func->name              = name;
		func->objType           = objType;
		func->funcId            = funcId;
		func->explicitSignature = 0;
		func->isExistingShared  = false;

		if( isShared )
		{
			// Look for a pre-existing shared function with the same signature
			for( asUINT n = 0; n < engine->scriptFunctions.GetLength(); n++ )
			{
				asCScriptFunction *f = engine->scriptFunctions[n];
				if( f &&
					f->isShared &&
					f->name == name &&
					f->nameSpace == ns &&
					f->IsSignatureExceptNameEqual(returnType, parameterTypes, inOutFlags, 0, false) )
				{
					funcId           = func->funcId           = f->id;
					isExistingShared = func->isExistingShared = true;
					break;
				}
			}
		}
	}

	// Destructors may not have any parameters
	if( isDestructor && parameterTypes.GetLength() > 0 )
	{
		int r, c;
		file->ConvertPosToRowCol(node->tokenPos, &r, &c);

		WriteError(file->name.AddressOf(), TXT_DESTRUCTOR_MAY_NOT_HAVE_PARM, r, c);
	}

	// If a function, class, or interface is shared then only shared types may be used in the signature
	if( (objType && objType->IsShared()) || isShared )
	{
		asCObjectType *ot = returnType.GetObjectType();
		if( ot && !ot->IsShared() )
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);
			asCString msg;
			msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, ot->name.AddressOf());
			WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
		}
		
		for( asUINT p = 0; p < parameterTypes.GetLength(); ++p )
		{
			asCObjectType *ot = parameterTypes[p].GetObjectType();
			if( ot && !ot->IsShared() )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString msg;
				msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, ot->name.AddressOf());
				WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
			}
		}
	}

	// Check that the same function hasn't been registered already in the namespace
	asCArray<int> funcs;
	GetFunctionDescriptions(name.AddressOf(), funcs, ns);
	if( funcs.GetLength() )
	{
		for( asUINT n = 0; n < funcs.GetLength(); ++n )
		{
			asCScriptFunction *func = GetFunctionDescription(funcs[n]);
			if( func->IsSignatureExceptNameAndReturnTypeEqual(parameterTypes, inOutFlags, objType, isConstMethod) )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);

				WriteError(file->name.AddressOf(), TXT_FUNCTION_ALREADY_EXIST, r, c);
				break;
			}
		}
	}

	// Register the function
	if( isExistingShared )
	{
		asCScriptFunction *f = engine->scriptFunctions[funcId];
		module->AddScriptFunction(f);
		module->globalFunctions.PushLast(f);
		f->AddRef();
	}
	else
	{
		module->AddScriptFunction(file->idx, funcId, name.AddressOf(), returnType, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), isInterface, objType, isConstMethod, isGlobalFunction, isPrivate, isFinal, isOverride, isShared, ns);
	}

	// Make sure the default args are declared correctly
	ValidateDefaultArgs(file, node, engine->scriptFunctions[funcId]);

	if( objType )
	{
		engine->scriptFunctions[funcId]->AddRef();
		if( isConstructor )
		{
			int factoryId = engine->GetNextScriptFunctionId();
			if( parameterTypes.GetLength() == 0 )
			{
				// Overload the default constructor
				engine->scriptFunctions[objType->beh.construct]->Release();
				objType->beh.construct = funcId;
				objType->beh.constructors[0] = funcId;

				// Register the default factory as well
				engine->scriptFunctions[objType->beh.factory]->Release();
				objType->beh.factory = factoryId;
				objType->beh.factories[0] = factoryId;
			}
			else
			{
				objType->beh.constructors.PushLast(funcId);

				// Register the factory as well
				objType->beh.factories.PushLast(factoryId);
			}

			// We must copy the default arg strings to avoid deleting the same object multiple times
			for( asUINT n = 0; n < defaultArgs.GetLength(); n++ )
				if( defaultArgs[n] )
					defaultArgs[n] = asNEW(asCString)(*defaultArgs[n]);

			asCDataType dt = asCDataType::CreateObjectHandle(objType, false);
			module->AddScriptFunction(file->idx, factoryId, name.AddressOf(), dt, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), false);

			// If the object is shared, then the factory must also be marked as shared
			if( objType->flags & asOBJ_SHARED )
				engine->scriptFunctions[factoryId]->isShared = true;

			// Add a dummy function to the builder so that it doesn't mix up the fund Ids
			functions.PushLast(0);

			// Compile the factory immediately
			asCCompiler compiler(engine);
			compiler.CompileFactory(this, file, engine->scriptFunctions[factoryId]);
			engine->scriptFunctions[factoryId]->AddRef();
		}
		else if( isDestructor )
			objType->beh.destruct = funcId;
		else
			objType->methods.PushLast(funcId);
	}

	// We need to delete the node already if this is an interface method
	if( isInterface && node )
	{
		node->Destroy(engine);
	}

	return 0;
}

int asCBuilder::RegisterScriptFunctionWithSignature(int funcId, asCScriptNode *node, asCScriptCode *file, asCString &name, sExplicitSignature *signature, asCObjectType *objType, bool isInterface, bool isGlobalFunction, bool isPrivate, bool isConst, bool isFinal, bool isOverride, bool treatAsProperty, const asCString &ns)
{
	bool isConstructor = false;
	bool isDestructor = false;
	asCArray<asCDataType> &parameterTypes = signature->argTypes;
	asCArray<asETypeModifiers> &inOutFlags = signature->argModifiers;
	asCArray<asCString *> defaultArgs = signature->defaultArgs;

	if( objType && asCDataType::CreatePrimitive(ttVoid, false) == signature->returnType )
	{
		if( 0 == name.Compare( objType->name ) )
			isConstructor = true;
		else if( 0 == name.Compare( "~" + objType->name ) )
			isDestructor = true;
	}

	// Check for name conflicts
	if( !isConstructor && !isDestructor )
	{
		if( objType )
			CheckNameConflictMember(objType, name.AddressOf(), node, file, treatAsProperty);
		else
			CheckNameConflict(name.AddressOf(), node, file, ns);
	}

	if( isInterface )
	{
		asASSERT(!isFinal);
		asASSERT(!isOverride);
	}
	else
	{
		sFunctionDescription *func = asNEW(sFunctionDescription);
		if( func == 0 )
			return asOUT_OF_MEMORY;

		functions.PushLast(func);

		func->script            = file;
		func->node              = node;
		func->name              = name;
		func->objType           = objType;
		func->funcId            = funcId;
		func->explicitSignature = signature;
	}

	// Destructors may not have any parameters
	if( isDestructor && parameterTypes.GetLength() > 0 )
	{
		int r, c;
		file->ConvertPosToRowCol(node->tokenPos, &r, &c);

		WriteError(file->name.AddressOf(), TXT_DESTRUCTOR_MAY_NOT_HAVE_PARM, r, c);
	}

	// If class or interface is shared, then only shared types may be used in the method signature
	if( objType && (objType->flags & asOBJ_SHARED) )
	{
		asCObjectType *ot = signature->returnType.GetObjectType();
		if( ot && (ot->flags & asOBJ_SCRIPT_OBJECT) && !(ot->flags & asOBJ_SHARED) )
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);
			asCString msg;
			msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, ot->name.AddressOf());
			WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
		}

		for( asUINT p = 0; p < parameterTypes.GetLength(); ++p )
		{
			asCObjectType *ot = parameterTypes[p].GetObjectType();
			if( ot && (ot->flags & asOBJ_SCRIPT_OBJECT) && !(ot->flags & asOBJ_SHARED) )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);
				asCString msg;
				msg.Format(TXT_SHARED_CANNOT_USE_NON_SHARED_TYPE_s, ot->name.AddressOf());
				WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
			}
		}
	}

	// TODO: Much of this can probably be reduced by using the IsSignatureEqual method
	// Check that the same function hasn't been registered already
	asCArray<int> funcs;
	GetFunctionDescriptions(name.AddressOf(), funcs, ns);
	if( funcs.GetLength() )
	{
		for( asUINT n = 0; n < funcs.GetLength(); ++n )
		{
			asCScriptFunction *func = GetFunctionDescription(funcs[n]);

			if( parameterTypes.GetLength() == func->parameterTypes.GetLength() )
			{
				bool match = true;
				if( func->objectType != objType )
				{
					match = false;
					break;
				}

				for( asUINT p = 0; p < parameterTypes.GetLength(); ++p )
				{
					if( parameterTypes[p] != func->parameterTypes[p] )
					{
						match = false;
						break;
					}
				}

				if( match )
				{
					int r, c;
					file->ConvertPosToRowCol(node->tokenPos, &r, &c);

					WriteError(file->name.AddressOf(), TXT_FUNCTION_ALREADY_EXIST, r, c);
					break;
				}
			}
		}
	}

	// Register the function
	module->AddScriptFunction(file->idx, funcId, name.AddressOf(), signature->returnType, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), isInterface, objType, isConst, isGlobalFunction, isPrivate, isFinal, isOverride);

	// Make sure the default args are declared correctly
	ValidateDefaultArgs(file, node, engine->scriptFunctions[funcId]);

	if( objType )
	{
		engine->scriptFunctions[funcId]->AddRef();
		if( isConstructor )
		{
			int factoryId = engine->GetNextScriptFunctionId();
			if( parameterTypes.GetLength() == 0 )
			{
				// Overload the default constructor
				engine->scriptFunctions[objType->beh.construct]->Release();
				objType->beh.construct = funcId;
				objType->beh.constructors[0] = funcId;

				// Register the default factory as well
				engine->scriptFunctions[objType->beh.factory]->Release();
				objType->beh.factory = factoryId;
				objType->beh.factories[0] = factoryId;
			}
			else
			{
				objType->beh.constructors.PushLast(funcId);

				// Register the factory as well
				objType->beh.factories.PushLast(factoryId);
			}

			// We must copy the default arg strings to avoid deleting the same object multiple times
			for( asUINT n = 0; n < defaultArgs.GetLength(); n++ )
				if( defaultArgs[n] )
					defaultArgs[n] = asNEW(asCString)(*defaultArgs[n]);

			asCDataType dt = asCDataType::CreateObjectHandle(objType, false);
			module->AddScriptFunction(file->idx, factoryId, name.AddressOf(), dt, parameterTypes.AddressOf(), inOutFlags.AddressOf(), defaultArgs.AddressOf(), (asUINT)parameterTypes.GetLength(), false);

			// Add a dummy function to the builder so that it doesn't mix up the fund Ids
			functions.PushLast(0);

			// Compile the factory immediately
			asCCompiler compiler(engine);
			compiler.CompileFactory(this, file, engine->scriptFunctions[factoryId]);
			engine->scriptFunctions[factoryId]->AddRef();
		}
		else if( isDestructor )
			objType->beh.destruct = funcId;
		else
			objType->methods.PushLast(funcId);
	}

	// We need to delete the node already if this is an interface method
	if( isInterface && node )
	{
		node->Destroy(engine);
	}

	return 0;
}

int asCBuilder::RegisterVirtualProperty(asCScriptNode *node, asCScriptCode *file, asCObjectType *objType, bool isInterface, bool isGlobalFunction, const asCString &ns, bool isExistingShared)
{
	if( isExistingShared ) 
	{
		// TODO: shared: Should validate that the function really exists in the class/interface
		node->Destroy(engine);
		return 0;
	}

	if( engine->ep.propertyAccessorMode != 2 )
	{
		int r, c;
		file->ConvertPosToRowCol(node->tokenPos, &r, &c);
		WriteError(file->name.AddressOf(), TXT_PROPERTY_ACCESSOR_DISABLED, r, c);
		node->Destroy(engine);
		return 0;
	}

	bool isPrivate = false;
	asCString emulatedName;
	asCDataType emulatedType;
	
	asCScriptNode *mainNode = node;
	node = node->firstChild;

	if( !isGlobalFunction && node->tokenType == ttPrivate )
	{
		isPrivate = true;
		node = node->next;
	}

	// TODO: namespace: Use correct implicit namespace
	emulatedType = CreateDataTypeFromNode(node, file, "");
	emulatedType = ModifyDataTypeFromNode(emulatedType, node->next, file, 0, 0);
	node = node->next->next;

	emulatedName.Assign(&file->code[node->tokenPos], node->tokenLength);
	node = node->next;

	while( node )
	{
		asCScriptNode *next           = node->next;
		asCScriptNode *funcNode       = 0;
		sExplicitSignature *signature = 0;
		bool success                  = false;
		bool isConst                  = false;
		bool isFinal                  = false;
		bool isOverride               = false;

		asCString name;

		// TODO: getset: Allow private for individual property accessors
		// TODO: getset: If the accessor uses its own name, then the property should be automatically declared

		if( node->firstChild->nodeType == snIdentifier && file->TokenEquals(node->firstChild->tokenPos, node->firstChild->tokenLength, GET_TOKEN) )
		{
			funcNode  = node->firstChild->next;

			if( funcNode && funcNode->tokenType == ttConst )
			{
				isConst = true;
				funcNode = funcNode->next;
			}

			while( funcNode && funcNode->nodeType != snStatementBlock )
			{
				if( funcNode->tokenType == ttIdentifier && file->TokenEquals(funcNode->tokenPos, funcNode->tokenLength, FINAL_TOKEN) )
					isFinal = true;
				else if( funcNode->tokenType == ttIdentifier && file->TokenEquals(funcNode->tokenPos, funcNode->tokenLength, OVERRIDE_TOKEN) )
					isOverride = true;

				funcNode = funcNode->next;
			}

			if( funcNode )
				funcNode->DisconnectParent();

			if( funcNode == 0 && (objType == 0 || !objType->IsInterface()) )
			{
				// TODO: getset: If no implementation is supplied the builder should provide an automatically generated implementation
				//               The compiler needs to be able to handle the different types, primitive, value type, and handle
				//               The code is also different for global property accessors
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);

				WriteError(file->name.AddressOf(), TXT_PROPERTY_ACCESSOR_MUST_BE_IMPLEMENTED, r, c);
			}

			signature = asNEW(sExplicitSignature);
			if( signature == 0 )
				return asOUT_OF_MEMORY;
			
			signature->returnType = emulatedType;

			name    = "get_" + emulatedName;
			success = true;
		}
		else if( node->firstChild->nodeType == snIdentifier && file->TokenEquals(node->firstChild->tokenPos, node->firstChild->tokenLength, SET_TOKEN) )
		{
			funcNode  = node->firstChild->next;

			if( funcNode && funcNode->tokenType == ttConst )
			{
				isConst = true;
				funcNode = funcNode->next;
			}

			while( funcNode && funcNode->nodeType != snStatementBlock )
			{
				if( funcNode->tokenType == ttIdentifier && file->TokenEquals(funcNode->tokenPos, funcNode->tokenLength, FINAL_TOKEN) )
					isFinal = true;
				else if( funcNode->tokenType == ttIdentifier && file->TokenEquals(funcNode->tokenPos, funcNode->tokenLength, OVERRIDE_TOKEN) )
					isOverride = true;

				funcNode = funcNode->next;
			}

			if( funcNode )
				funcNode->DisconnectParent();

			if( funcNode == 0 && (objType == 0 || !objType->IsInterface()) )
			{
				int r, c;
				file->ConvertPosToRowCol(node->tokenPos, &r, &c);

				WriteError(file->name.AddressOf(), TXT_PROPERTY_ACCESSOR_MUST_BE_IMPLEMENTED, r, c);
			}

			signature = asNEW(sExplicitSignature)(1);
			if( signature == 0 )
				return asOUT_OF_MEMORY;

			signature->returnType = asCDataType::CreatePrimitive(ttVoid, false);

			signature->argModifiers.PushLast(asTM_NONE);
			signature->argNames.PushLast("value");
			signature->argTypes.PushLast(emulatedType);
			signature->defaultArgs.PushLast(0);

			name    = "set_" + emulatedName;
			success = true;
		}
		else
		{
			int r, c;
			file->ConvertPosToRowCol(node->tokenPos, &r, &c);

			WriteError(file->name.AddressOf(), TXT_UNRECOGNIZED_VIRTUAL_PROPERTY_NODE, r, c);
		}

		if( success )
			RegisterScriptFunctionWithSignature(engine->GetNextScriptFunctionId(), funcNode, file, name, signature, objType, isInterface, isGlobalFunction, isPrivate, isConst, isFinal, isOverride, true, ns);

		node = next;
	};

	mainNode->Destroy(engine);

	return 0;
}

int asCBuilder::RegisterImportedFunction(int importID, asCScriptNode *node, asCScriptCode *file, const asCString &ns)
{
	// Find name
	asCScriptNode *f = node->firstChild;
	asCScriptNode *n = f->firstChild->next->next;

	// Check for name conflicts
	asCString name(&file->code[n->tokenPos], n->tokenLength);
	CheckNameConflict(name.AddressOf(), n, file, ns);

	// Initialize a script function object for registration
	asCDataType returnType;
	// TODO: namespace: Use correct implicit namespace
	returnType = CreateDataTypeFromNode(f->firstChild, file, "");
	returnType = ModifyDataTypeFromNode(returnType, f->firstChild->next, file, 0, 0);

	// Count the parameters
	int count = 0;
	asCScriptNode *c = n->next->firstChild;
	while( c )
	{
		count++;
		c = c->next->next;
		if( c && c->nodeType == snIdentifier )
			c = c->next;
	}

	asCArray<asCDataType> parameterTypes(count);
	asCArray<asETypeModifiers> inOutFlags(count);
	n = n->next->firstChild;
	while( n )
	{
		asETypeModifiers inOutFlag;
		// TODO: namespace: Use correct implicit namespace
		asCDataType type = CreateDataTypeFromNode(n, file, "");
		type = ModifyDataTypeFromNode(type, n->next, file, &inOutFlag, 0);

		// Store the parameter type
		parameterTypes.PushLast(type);
		inOutFlags.PushLast(inOutFlag);

		if( type.GetTokenType() == ttVoid )
		{
			int r, c;
			file->ConvertPosToRowCol(n->tokenPos, &r, &c);
			asCString str;
			str.Format(TXT_PARAMETER_CANT_BE_s, type.Format().AddressOf());
			WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
			break;
		}

		// Move to next parameter
		n = n->next->next;
		if( n && n->nodeType == snIdentifier )
			n = n->next;
	}

	// Check that the same function hasn't been registered already
	asCArray<int> funcs;
	GetFunctionDescriptions(name.AddressOf(), funcs, ns);
	if( funcs.GetLength() )
	{
		for( asUINT n = 0; n < funcs.GetLength(); ++n )
		{
			asCScriptFunction *func = GetFunctionDescription(funcs[n]);

			if( parameterTypes.GetLength() == func->parameterTypes.GetLength() )
			{
				bool match = true;
				for( asUINT p = 0; p < parameterTypes.GetLength(); ++p )
				{
					if( parameterTypes[p] != func->parameterTypes[p] )
					{
						match = false;
						break;
					}
				}

				if( match )
				{
					int r, c;
					file->ConvertPosToRowCol(node->tokenPos, &r, &c);

					WriteError(file->name.AddressOf(), TXT_FUNCTION_ALREADY_EXIST, r, c);
					break;
				}
			}
		}
	}

	// Read the module name as well
	n = node->firstChild->next;
	asCString moduleName;
	moduleName.Assign(&file->code[n->tokenPos+1], n->tokenLength-2);

	node->Destroy(engine);

	// Register the function
	// TODO: namespace: Store namespace
	module->AddImportedFunction(importID, name.AddressOf(), returnType, parameterTypes.AddressOf(), inOutFlags.AddressOf(), (asUINT)parameterTypes.GetLength(), moduleName);

	return 0;
}
#endif

asCScriptFunction *asCBuilder::GetFunctionDescription(int id)
{
	// TODO: import: This should be improved when the imported functions are removed
	// Get the description from the engine
	if( (id & 0xFFFF0000) == 0 )
		return engine->scriptFunctions[id];
	else
		return engine->importedFunctions[id & 0xFFFF]->importedFunctionSignature;
}

void asCBuilder::GetFunctionDescriptions(const char *name, asCArray<int> &funcs, const asCString &ns)
{
	// TODO: optimize: Improve linear searches in GetFunctionDescriptions
	//                 A large part of the compilation time seems to be spent in this function
	//                 I need to have a map with all global functions so that it will be
	//                 quicker to find them by name. The key should be the function name, and 
	//                 the value a list with all the functions using that name

	asUINT n;
	for( n = 0; n < module->scriptFunctions.GetLength(); n++ )
	{
		asCScriptFunction *f = module->scriptFunctions[n];
		if( f->name == name &&
			f->nameSpace == ns && 
			f->objectType == 0 )
			funcs.PushLast(f->id);
	}

	for( n = 0; n < module->bindInformations.GetLength(); n++ )
	{
		if( module->bindInformations[n]->importedFunctionSignature->name == name )
			funcs.PushLast(module->bindInformations[n]->importedFunctionSignature->id);
	}

	for( n = 0; n < engine->registeredGlobalFuncs.GetLength(); n++ )
	{
		asCScriptFunction *f = engine->registeredGlobalFuncs[n];
		if( f &&
			f->funcType == asFUNC_SYSTEM &&
			f->objectType == 0 &&
			f->nameSpace == ns &&
			f->name == name )
		{
			// Verify if the module has access to the function
			if( module->accessMask & f->accessMask )
			{
				funcs.PushLast(f->id);
			}
		}
	}
}

void asCBuilder::GetObjectMethodDescriptions(const char *name, asCObjectType *objectType, asCArray<int> &methods, bool objIsConst, const asCString &scope)
{
	if( scope != "" )
	{
		// Find the base class with the specified scope
		while( objectType && objectType->name != scope )
			objectType = objectType->derivedFrom;

		// If the scope is not any of the base classes, then return no methods
		if( objectType == 0 )
			return;
	}

	// TODO: optimize: Improve linear search
	if( objIsConst )
	{
		// Only add const methods to the list
		for( asUINT n = 0; n < objectType->methods.GetLength(); n++ )
		{
			if( engine->scriptFunctions[objectType->methods[n]]->name == name &&
				engine->scriptFunctions[objectType->methods[n]]->isReadOnly )
			{
				// When the scope is defined the returned methods should be the true methods, not the virtual method stubs
				if( scope == "" )
					methods.PushLast(engine->scriptFunctions[objectType->methods[n]]->id);
				else
				{
					asCScriptFunction *virtFunc = engine->scriptFunctions[objectType->methods[n]];
					asCScriptFunction *realFunc = objectType->virtualFunctionTable[virtFunc->vfTableIdx];
					methods.PushLast(realFunc->id);
				}
			}
		}
	}
	else
	{
		// TODO: Prefer non-const over const
		for( asUINT n = 0; n < objectType->methods.GetLength(); n++ )
		{
			if( engine->scriptFunctions[objectType->methods[n]]->name == name )
			{
				// When the scope is defined the returned methods should be the true methods, not the virtual method stubs
				if( scope == "" )
					methods.PushLast(engine->scriptFunctions[objectType->methods[n]]->id);
				else
				{
					asCScriptFunction *virtFunc = engine->scriptFunctions[objectType->methods[n]];
					asCScriptFunction *realFunc = objectType->virtualFunctionTable[virtFunc->vfTableIdx];
					methods.PushLast(realFunc->id);
				}
			}
		}
	}
}

void asCBuilder::WriteInfo(const char *scriptname, const char *message, int r, int c, bool pre)
{
	// Need to store the pre message in a structure
	if( pre )
	{
		preMessage.isSet = true;
		preMessage.c = c;
		preMessage.r = r;
		preMessage.message = message;
	}
	else
	{
		preMessage.isSet = false;
		engine->WriteMessage(scriptname, r, c, asMSGTYPE_INFORMATION, message);
	}
}

void asCBuilder::WriteError(const char *scriptname, const char *message, int r, int c)
{
	numErrors++;

	// Need to pass the preMessage first
	if( preMessage.isSet )
		WriteInfo(scriptname, preMessage.message.AddressOf(), preMessage.r, preMessage.c, false);

	engine->WriteMessage(scriptname, r, c, asMSGTYPE_ERROR, message);
}

void asCBuilder::WriteWarning(const char *scriptname, const char *message, int r, int c)
{
	numWarnings++;

	// Need to pass the preMessage first
	if( preMessage.isSet )
		WriteInfo(scriptname, preMessage.message.AddressOf(), preMessage.r, preMessage.c, false);

	engine->WriteMessage(scriptname, r, c, asMSGTYPE_WARNING, message);
}

asCString asCBuilder::GetScopeFromNode(asCScriptNode *node, asCScriptCode *script, asCScriptNode **next)
{
	asCString scope;
	asCScriptNode *sn = node;
	if( sn->tokenType == ttScope )
	{
		scope = "::";
		sn = sn->next;
	}

	while( sn && sn->next && sn->next->tokenType == ttScope )
	{
		asCString tmp;
		tmp.Assign(&script->code[sn->tokenPos], sn->tokenLength);
		if( scope != "" && scope != "::" )
			scope += "::";
		scope += tmp;
		sn = sn->next->next;
	}

	if( next )
		*next = sn;

	return scope;
}

asCDataType asCBuilder::CreateDataTypeFromNode(asCScriptNode *node, asCScriptCode *file, const asCString &implicitNamespace, bool acceptHandleForScope, asCObjectType *currentType)
{
	asASSERT(node->nodeType == snDataType);

	asCDataType dt;

	asCScriptNode *n = node->firstChild;

	bool isConst = false;
	bool isImplicitHandle = false;
	if( n->tokenType == ttConst )
	{
		isConst = true;
		n = n->next;
	}

	// Determine namespace
	asCString scope = GetScopeFromNode(n, file, &n);
	if( scope == "" ) scope = implicitNamespace;

	if( n->tokenType == ttIdentifier )
	{
		asCString str;
		str.Assign(&file->code[n->tokenPos], n->tokenLength);

		asCObjectType *ot = 0;

		// If this is for a template type, then we must first determine if the 
		// identifier matches any of the template subtypes
		// TODO: template: it should be possible to have more than one subtypes
		if( currentType && (currentType->flags & asOBJ_TEMPLATE) && str == currentType->templateSubType.GetObjectType()->name )
			ot = currentType->templateSubType.GetObjectType();

		if( ot == 0 )
			ot = GetObjectType(str.AddressOf(), scope);
		if( ot == 0 && !module && currentType )
			ot = GetObjectTypeFromTypesKnownByObject(str.AddressOf(), currentType);
	
		if( ot )
		{
			if( ot->flags & asOBJ_IMPLICIT_HANDLE )
				isImplicitHandle = true;

			// Make sure the module has access to the object type
			if( !module || (module->accessMask & ot->accessMask) )
			{
				if(asOBJ_TYPEDEF == (ot->flags & asOBJ_TYPEDEF))
				{
					// TODO: typedef: A typedef should be considered different from the original type (though with implicit conversions between the two)
					// Create primitive data type based on object flags
					dt = ot->templateSubType;
					dt.MakeReadOnly(isConst);
				}
				else
				{
					if( ot->flags & asOBJ_TEMPLATE )
					{
						n = n->next;
						
						// Check if the subtype is a type or the template's subtype
						// if it is the template's subtype then this is the actual template type,
						// orderwise it is a template instance.
						// Only do this for application registered interface, as the 
						// scripts cannot implement templates.
						// TODO: namespace: Use correct implicit namespace
						asCDataType subType = CreateDataTypeFromNode(n, file, "", false, module ? 0 : ot);
						if( subType.GetObjectType() != ot->templateSubType.GetObjectType() )
						{
							// This is a template instance
							// Need to find the correct object type
							asCObjectType *otInstance = engine->GetTemplateInstanceType(ot, subType);

							if( !otInstance )
							{
								asCString msg;
								msg.Format(TXT_CANNOT_INSTANCIATE_TEMPLATE_s_WITH_s, ot->name.AddressOf(), subType.Format().AddressOf());
								int r, c;
								file->ConvertPosToRowCol(n->tokenPos, &r, &c);
								WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);
							}

							ot = otInstance;
						}
					}

					// Create object data type
					if( ot )
						dt = asCDataType::CreateObject(ot, isConst);
					else
						dt = asCDataType::CreatePrimitive(ttInt, isConst);
				}
			}
			else
			{
				asCString msg;
				msg.Format(TXT_TYPE_s_NOT_AVAILABLE_FOR_MODULE, (const char *)str.AddressOf());

				int r, c;
				file->ConvertPosToRowCol(n->tokenPos, &r, &c);

				WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);

				dt.SetTokenType(ttInt);
			}
		}
		else if( ot == 0 )
		{
			// It can still be a function definition
			asCScriptFunction *funcdef = GetFuncDef(str.AddressOf());

			if( funcdef )
			{
				dt = asCDataType::CreateFuncDef(funcdef);
			}
			else if( funcdef == 0 )
			{
				asCString msg;
				msg.Format(TXT_IDENTIFIER_s_NOT_DATA_TYPE, (const char *)str.AddressOf());

				int r, c;
				file->ConvertPosToRowCol(n->tokenPos, &r, &c);

				WriteError(file->name.AddressOf(), msg.AddressOf(), r, c);

				dt = asCDataType::CreatePrimitive(ttInt, isConst);
				return dt;
			}
		}
	}
	else
	{
		// Create primitive data type
		dt = asCDataType::CreatePrimitive(n->tokenType, isConst);
	}

	// Determine array dimensions and object handles
	n = n->next;
	while( n && (n->tokenType == ttOpenBracket || n->tokenType == ttHandle) )
	{
		if( n->tokenType == ttOpenBracket )
		{
			// Make sure the sub type can be instanciated
			if( !dt.CanBeInstanciated() )
			{
				int r, c;
				file->ConvertPosToRowCol(n->tokenPos, &r, &c);

				asCString str;
				// TODO: Change to "Array sub type cannot be 'type'"
				str.Format(TXT_DATA_TYPE_CANT_BE_s, dt.Format().AddressOf());

				WriteError(file->name.AddressOf(), str.AddressOf(), r, c);
			}

			// Make the type an array (or multidimensional array)
			if( dt.MakeArray(engine) < 0 )
			{
				int r, c;
				file->ConvertPosToRowCol(n->tokenPos, &r, &c);
				WriteError(file->name.AddressOf(), TXT_NO_DEFAULT_ARRAY_TYPE, r, c);
				break;
			}
		}
		else
		{
			// Make the type a handle
			if( dt.MakeHandle(true, acceptHandleForScope) < 0 )
			{
				int r, c;
				file->ConvertPosToRowCol(n->tokenPos, &r, &c);
				WriteError(file->name.AddressOf(), TXT_OBJECT_HANDLE_NOT_SUPPORTED, r, c);
				break;
			}
		}
		n = n->next;
	}

	if( isImplicitHandle )
	{
		// Make the type a handle
		if( dt.MakeHandle(true, acceptHandleForScope) < 0 )
		{
			int r, c;
			file->ConvertPosToRowCol(n->tokenPos, &r, &c);
			WriteError(file->name.AddressOf(), TXT_OBJECT_HANDLE_NOT_SUPPORTED, r, c);
		}
	}

	return dt;
}

asCDataType asCBuilder::ModifyDataTypeFromNode(const asCDataType &type, asCScriptNode *node, asCScriptCode *file, asETypeModifiers *inOutFlags, bool *autoHandle)
{
	asCDataType dt = type;

	if( inOutFlags ) *inOutFlags = asTM_NONE;

	// Is the argument sent by reference?
	asCScriptNode *n = node->firstChild;
	if( n && n->tokenType == ttAmp )
	{
		dt.MakeReference(true);
		n = n->next;

		if( n )
		{
			if( inOutFlags )
			{
				if( n->tokenType == ttIn )
					*inOutFlags = asTM_INREF;
				else if( n->tokenType == ttOut )
					*inOutFlags = asTM_OUTREF;
				else if( n->tokenType == ttInOut )
					*inOutFlags = asTM_INOUTREF;
				else
					asASSERT(false);
			}

			n = n->next;
		}
		else
		{
			if( inOutFlags )
				*inOutFlags = asTM_INOUTREF; // ttInOut
		}

		if( !engine->ep.allowUnsafeReferences &&
			inOutFlags && *inOutFlags == asTM_INOUTREF )
		{
			// Verify that the base type support &inout parameter types
			if( !dt.IsObject() || dt.IsObjectHandle() || !((dt.GetObjectType()->flags & asOBJ_NOCOUNT) || (dt.GetObjectType()->beh.addref && dt.GetObjectType()->beh.release)) )
			{
				int r, c;
				file->ConvertPosToRowCol(node->firstChild->tokenPos, &r, &c);
				WriteError(file->name.AddressOf(), TXT_ONLY_OBJECTS_MAY_USE_REF_INOUT, r, c);
			}
		}
	}

	if( autoHandle ) *autoHandle = false;

	if( n && n->tokenType == ttPlus )
	{
		// Autohandles are not supported for types with NOCOUNT
		if( dt.GetObjectType()->flags & asOBJ_NOCOUNT )
		{
			int r, c;
			file->ConvertPosToRowCol(node->firstChild->tokenPos, &r, &c);
			WriteError(file->name.AddressOf(), TXT_AUTOHANDLE_CANNOT_BE_USED_FOR_NOCOUNT, r, c);
		}

		if( autoHandle ) *autoHandle = true;
	}

	return dt;
}

asCObjectType *asCBuilder::GetObjectType(const char *type, const asCString &ns)
{
	asCObjectType *ot = engine->GetObjectType(type, ns);
	if( !ot && module )
		ot = module->GetObjectType(type, ns);

	return ot;
}

// This function will return true if there are any types in the engine or module 
// with the given name. The namespace is ignored in this verification.
bool asCBuilder::DoesTypeExist(const char *type)
{
	asUINT n;

	// TODO: optimize: Improve linear searches

	// Check if it is a registered type
	for( n = 0; n < engine->objectTypes.GetLength(); n++ )
		if( engine->objectTypes[n] &&
			engine->objectTypes[n]->name == type ) // TODO: template: Should we check the subtype in case of template instances?
			return true;

	for( n = 0; n < engine->registeredFuncDefs.GetLength(); n++ )
		if( engine->registeredFuncDefs[n]->name == type )
			return true;

	// Check if it is a script type
	if( module )
	{
		for( n = 0; n < module->classTypes.GetLength(); n++ )
			if( module->classTypes[n]->name == type )
				return true;

		for( n = 0; n < module->enumTypes.GetLength(); n++ )
			if( module->enumTypes[n]->name == type )
				return true;

		for( n = 0; n < module->typeDefs.GetLength(); n++ )
			if( module->typeDefs[n]->name == type )
				return true;

		for( asUINT n = 0; n < module->funcDefs.GetLength(); n++ )
			if( module->funcDefs[n]->name == type )
				return true;
	}

	return false;
}

asCObjectType *asCBuilder::GetObjectTypeFromTypesKnownByObject(const char *type, asCObjectType *currentType)
{
	if( currentType->name == type )
		return currentType;

	asUINT n;

	for( n = 0; n < currentType->properties.GetLength(); n++ )
		if( currentType->properties[n]->type.GetObjectType() && 
			currentType->properties[n]->type.GetObjectType()->name == type )
			return currentType->properties[n]->type.GetObjectType();

	for( n = 0; n < currentType->methods.GetLength(); n++ )
	{
		asCScriptFunction *func = engine->scriptFunctions[currentType->methods[n]];
		if( func->returnType.GetObjectType() &&
			func->returnType.GetObjectType()->name == type )
			return func->returnType.GetObjectType();

		for( asUINT f = 0; f < func->parameterTypes.GetLength(); f++ )
			if( func->parameterTypes[f].GetObjectType() &&
				func->parameterTypes[f].GetObjectType()->name == type )
				return func->parameterTypes[f].GetObjectType();
	}

	return 0;
}

asCScriptFunction *asCBuilder::GetFuncDef(const char *type)
{
	for( asUINT n = 0; n < engine->registeredFuncDefs.GetLength(); n++ )
		// TODO: access: Only return the definitions that the module has access to
		if( engine->registeredFuncDefs[n]->name == type )
			return engine->registeredFuncDefs[n];

	if( module )
	{
		for( asUINT n = 0; n < module->funcDefs.GetLength(); n++ )
			if( module->funcDefs[n]->name == type )
				return module->funcDefs[n];
	}

	return 0;
}

#ifndef AS_NO_COMPILER

int asCBuilder::GetEnumValueFromObjectType(asCObjectType *objType, const char *name, asCDataType &outDt, asDWORD &outValue)
{
	if( !objType || !(objType->flags & asOBJ_ENUM) )
		return 0;

	for( asUINT n = 0; n < objType->enumValues.GetLength(); ++n )
	{
		if( objType->enumValues[n]->name == name )
		{
			outDt = asCDataType::CreateObject(objType, true);
			outValue = objType->enumValues[n]->value;
			return 1;
		}
	}

	return 0;
}

int asCBuilder::GetEnumValue(const char *name, asCDataType &outDt, asDWORD &outValue, const asCString &ns)
{
	bool found = false;

	// Search all available enum types
	asUINT t;
	for( t = 0; t < engine->objectTypes.GetLength(); t++ )
	{
		asCObjectType *ot = engine->objectTypes[t];
		if( ns != ot->nameSpace ) continue;

		if( GetEnumValueFromObjectType( ot, name, outDt, outValue ) )
		{
			if( !found )
			{
				found = true;
			}
			else
			{
				// Found more than one value in different enum types
				return 2;
			}
		}
	}

	for( t = 0; t < module->enumTypes.GetLength(); t++ )
	{
		asCObjectType *ot = module->enumTypes[t];
		if( ns != ot->nameSpace ) continue;

		if( GetEnumValueFromObjectType( ot, name, outDt, outValue ) )
		{
			if( !found )
			{
				found = true;
			}
			else
			{
				// Found more than one value in different enum types
				return 2;
			}
		}
	}

	if( found )
		return 1;

	// Didn't find any value
	return 0;
}

#endif // AS_NO_COMPILER

END_AS_NAMESPACE
