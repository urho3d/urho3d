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
// as_builder.h
//
// This is the class that manages the compilation of the scripts
//


#ifndef AS_BUILDER_H
#define AS_BUILDER_H

#include "as_config.h"
#include "as_scriptengine.h"
#include "as_module.h"
#include "as_array.h"
#include "as_scriptcode.h"
#include "as_scriptnode.h"
#include "as_datatype.h"
#include "as_property.h"

BEGIN_AS_NAMESPACE

#ifndef AS_NO_COMPILER

struct sExplicitSignature
{
	sExplicitSignature(int argCount = 0) : argTypes(argCount), argModifiers(argCount), argNames(argCount), defaultArgs(argCount) {}

	asCDataType returnType;
	asCArray<asCDataType> argTypes;
	asCArray<asETypeModifiers> argModifiers;
	asCArray<asCString> argNames;
	asCArray<asCString *> defaultArgs;
};

struct sFunctionDescription
{
	asCScriptCode *script;
	asCScriptNode *node;
	asCString name;
	asCObjectType *objType;
	sExplicitSignature *explicitSignature;
	int funcId;
	bool isExistingShared;
};

struct sGlobalVariableDescription
{
	asCScriptCode *script;
	asCScriptNode *idNode;
	asCScriptNode *nextNode;
	asCString name;
	asCGlobalProperty *property;
	asCDataType datatype;
	int index;
	bool isCompiled;
	bool isPureConstant;
	bool isEnumValue;
	asQWORD constantValue;
};

struct sClassDeclaration
{
	sClassDeclaration() {script = 0; node = 0; validState = 0; objType = 0; isExistingShared = false; isFinal = false;}

	asCScriptCode *script;
	asCScriptNode *node;
	asCString name;
	int validState;
	asCObjectType *objType;
	bool isExistingShared;
	bool isFinal;
};

struct sFuncDef
{
	asCScriptCode *script;
	asCScriptNode *node;
	asCString name;
	int idx;
};

#endif // AS_NO_COMPILER

class asCBuilder
{
public:
	asCBuilder(asCScriptEngine *engine, asCModule *module);
	~asCBuilder();

	// These methods are used by the application interface
	int VerifyProperty(asCDataType *dt, const char *decl, asCString &outName, asCDataType &outType, const asCString &ns);
	int ParseDataType(const char *datatype, asCDataType *result, const asCString &implicitNamespace, bool isReturnType = false);
	int ParseTemplateDecl(const char *decl, asCString *name, asCString *subtypeName);
	int ParseFunctionDeclaration(asCObjectType *type, const char *decl, asCScriptFunction *func, bool isSystemFunction, asCArray<bool> *paramAutoHandles = 0, bool *returnAutoHandle = 0);
	int ParseVariableDeclaration(const char *decl, const asCString &implicitNamespace, asCString &outName, asCString &outNamespace, asCDataType &outDt);
	int CheckNameConflict(const char *name, asCScriptNode *node, asCScriptCode *code, const asCString &ns);
	int CheckNameConflictMember(asCObjectType *type, const char *name, asCScriptNode *node, asCScriptCode *code, bool isProperty);

#ifndef AS_NO_COMPILER
	int AddCode(const char *name, const char *code, int codeLength, int lineOffset, int sectionIdx, bool makeCopy);
	int Build();

	int CompileFunction(const char *sectionName, const char *code, int lineOffset, asDWORD compileFlags, asCScriptFunction **outFunc);
	int CompileGlobalVar(const char *sectionName, const char *code, int lineOffset);
#endif

protected:
	friend class asCModule;
	friend class asCParser;

	void               Reset();

	void               WriteInfo(const char *scriptname, const char *msg, int r, int c, bool preMessage);
	void               WriteError(const char *scriptname, const char *msg, int r, int c);
	void               WriteWarning(const char *scriptname, const char *msg, int r, int c);

	asCObjectProperty *GetObjectProperty(asCDataType &obj, const char *prop);
	asCGlobalProperty *GetGlobalProperty(const char *prop, const asCString &ns, bool *isCompiled, bool *isPureConstant, asQWORD *constantValue, bool *isAppProp);

	asCScriptFunction *GetFunctionDescription(int funcId);
	void               GetFunctionDescriptions(const char *name, asCArray<int> &funcs, const asCString &ns);
	void               GetObjectMethodDescriptions(const char *name, asCObjectType *objectType, asCArray<int> &methods, bool objIsConst, const asCString &scope = "");

	int                ValidateDefaultArgs(asCScriptCode *script, asCScriptNode *node, asCScriptFunction *func);
	asCString          GetCleanExpressionString(asCScriptNode *n, asCScriptCode *file);

	asCString          GetScopeFromNode(asCScriptNode *n, asCScriptCode *script, asCScriptNode **next = 0);

	asCObjectType     *GetObjectType(const char *type, const asCString &ns);
	asCScriptFunction *GetFuncDef(const char *type);
	asCObjectType     *GetObjectTypeFromTypesKnownByObject(const char *type, asCObjectType *currentType);
	asCDataType        CreateDataTypeFromNode(asCScriptNode *node, asCScriptCode *file, const asCString &implicitNamespace, bool acceptHandleForScope = false, asCObjectType *currentType = 0);
	asCDataType        ModifyDataTypeFromNode(const asCDataType &type, asCScriptNode *node, asCScriptCode *file, asETypeModifiers *inOutFlag, bool *autoHandle);

	struct preMessage_t
	{
		bool isSet;
		asCString message;
		int r;
		int c;
	} preMessage;

	int numErrors;
	int numWarnings;

	asCScriptEngine *engine;
	asCModule       *module;

#ifndef AS_NO_COMPILER
protected:
	friend class asCCompiler;

	int                RegisterScriptFunction(int funcID, asCScriptNode *node, asCScriptCode *file, asCObjectType *object = 0, bool isInterface = false, bool isGlobalFunction = false, const asCString &ns = "", bool isExistingShared = false);
	int                RegisterScriptFunctionWithSignature(int funcID, asCScriptNode *node, asCScriptCode *file, asCString &name, sExplicitSignature *signature, asCObjectType *object = 0, bool isInterface = false, bool isGlobalFunction = false, bool isPrivate = false, bool isConst = false, bool isFinal = false, bool isOverride = false, bool treatAsProperty = false, const asCString &ns = "");
	int                RegisterVirtualProperty(asCScriptNode *node, asCScriptCode *file, asCObjectType *object = 0, bool isInterface = false, bool isGlobalFunction = false, const asCString &ns = "", bool isExistingShared = false);
	int                RegisterImportedFunction(int funcID, asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterGlobalVar(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterClass(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterInterface(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterEnum(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterTypedef(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	int                RegisterFuncDef(asCScriptNode *node, asCScriptCode *file, const asCString &ns);
	void               CompleteFuncDef(sFuncDef *funcDef);
	void               CompileClasses();
	void               GetParsedFunctionDetails(asCScriptNode *node, asCScriptCode *file, asCObjectType *objType, asCString &name, asCDataType &returnType, asCArray<asCDataType> &parameterTypes, asCArray<asETypeModifiers> &inOutFlags, asCArray<asCString *> &defaultArgs, bool &isConstMethod, bool &isConstructor, bool &isDestructor, bool &isPrivate, bool &isOverride, bool &isFinal, bool &isShared);
	bool               DoesMethodExist(asCObjectType *objType, int methodId, asUINT *methodIndex = 0);
	void               AddDefaultConstructor(asCObjectType *objType, asCScriptCode *file);
	asCObjectProperty *AddPropertyToClass(sClassDeclaration *c, const asCString &name, const asCDataType &type, bool isPrivate, asCScriptCode *file = 0, asCScriptNode *node = 0);
	int                CreateVirtualFunction(asCScriptFunction *func, int idx);
	void               ParseScripts();
	void               RegisterTypesFromScript(asCScriptNode *node, asCScriptCode *script, const asCString &ns);
	void               RegisterNonTypesFromScript(asCScriptNode *node, asCScriptCode *script, const asCString &ns);
	void               CompileFunctions();
	void               CompileGlobalVariables();
	int                GetEnumValueFromObjectType(asCObjectType *objType, const char *name, asCDataType &outDt, asDWORD &outValue);
	int                GetEnumValue(const char *name, asCDataType &outDt, asDWORD &outValue, const asCString &ns);

	asCArray<asCScriptCode *>              scripts;
	asCArray<sFunctionDescription *>       functions;
	asCArray<sGlobalVariableDescription *> globVariables;
	asCArray<sClassDeclaration *>          classDeclarations;
	asCArray<sClassDeclaration *>          interfaceDeclarations;
	asCArray<sClassDeclaration *>          namedTypeDeclarations;
	asCArray<sFuncDef *>                   funcDefs;
#endif
};

END_AS_NAMESPACE

#endif
