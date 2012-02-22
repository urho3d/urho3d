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
// as_parser.cpp
//
// This class parses the script code and builds a tree for compilation
//



#include "as_config.h"
#include "as_parser.h"
#include "as_tokendef.h"
#include "as_texts.h"

#ifdef _MSC_VER
#pragma warning(disable:4702) // unreachable code
#endif

BEGIN_AS_NAMESPACE

asCParser::asCParser(asCBuilder *builder)
{
	this->builder    = builder;
	this->engine     = builder->engine;

	script			      = 0;
	scriptNode		      = 0;
	checkValidTypes       = false;
	isParsingAppInterface = false;
}

asCParser::~asCParser()
{
	Reset();
}

void asCParser::Reset()
{
	errorWhileParsing     = false;
	isSyntaxError         = false;
	checkValidTypes       = false;
	isParsingAppInterface = false;

	sourcePos = 0;

	if( scriptNode )
	{
		scriptNode->Destroy(engine);
	}

	scriptNode = 0;

	script = 0;
}

asCScriptNode *asCParser::GetScriptNode()
{
	return scriptNode;
}

int asCParser::ParseFunctionDefinition(asCScriptCode *script)
{
	Reset();

	// Set flag that permits ? as datatype for parameters
	isParsingAppInterface = true;

	this->script = script;

	scriptNode = ParseFunctionDefinition();

	// The declaration should end after the definition
	if( !isSyntaxError )
	{
		sToken t;
		GetToken(&t);
		if( t.type != ttEnd )
		{
			Error(ExpectedToken(asCTokenizer::GetDefinition(ttEnd)).AddressOf(), &t);
			return -1;
		}
	}

	if( errorWhileParsing )
		return -1;

	return 0;
}

int asCParser::ParseDataType(asCScriptCode *script, bool isReturnType)
{
	Reset();

	this->script = script;

	scriptNode = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);
		
	scriptNode->AddChildLast(ParseType(true));
	if( isSyntaxError ) return -1;

	if( isReturnType )
	{
		scriptNode->AddChildLast(ParseTypeMod(false));
		if( isSyntaxError ) return -1;
	}

	// The declaration should end after the type
	sToken t;
	GetToken(&t);
	if( t.type != ttEnd )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEnd)).AddressOf(), &t);
		return -1;
	}

	if( errorWhileParsing )
		return -1;

	return 0;
}


// Parse a template declaration: IDENTIFIER '<' 'class'? IDENTIFIER '>'
int asCParser::ParseTemplateDecl(asCScriptCode *script)
{
	Reset();

	this->script = script;
	scriptNode = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined);

	scriptNode->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return -1;

	sToken t;
	GetToken(&t);
	if( t.type != ttLessThan )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttLessThan)).AddressOf(), &t);
		return -1;
	}

	// The class token is optional
	GetToken(&t);
	if( t.type != ttClass )
		RewindTo(&t);

	scriptNode->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return -1;

	GetToken(&t);
	if( t.type != ttGreaterThan )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttGreaterThan)).AddressOf(), &t);
		return -1;
	}

	GetToken(&t);
	if( t.type != ttEnd )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEnd)).AddressOf(), &t);
		return -1;
	}

	if( errorWhileParsing )
		return -1;

	return 0;
}

int asCParser::ParsePropertyDeclaration(asCScriptCode *script)
{
	Reset();

	this->script = script;

	scriptNode = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDeclaration);

	scriptNode->AddChildLast(ParseType(true));
	if( isSyntaxError ) return -1;

	ParseOptionalScope(scriptNode);

	scriptNode->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return -1;

	// The declaration should end after the identifier
	sToken t;
	GetToken(&t);
	if( t.type != ttEnd )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEnd)).AddressOf(), &t);
		return -1;
	}

	return 0;
}

void asCParser::ParseOptionalScope(asCScriptNode *node)
{
	sToken t1, t2;
	GetToken(&t1);
	GetToken(&t2);
	if( t1.type == ttScope )
	{
		RewindTo(&t1);
		node->AddChildLast(ParseToken(ttScope));
		GetToken(&t1);
		GetToken(&t2);
	}
	while( t1.type == ttIdentifier && t2.type == ttScope )
	{
		RewindTo(&t1);
		node->AddChildLast(ParseIdentifier());
		node->AddChildLast(ParseToken(ttScope));
		GetToken(&t1);
		GetToken(&t2);
	}
	RewindTo(&t1);
}

asCScriptNode *asCParser::ParseFunctionDefinition()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFunction);

	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseTypeMod(false));
	if( isSyntaxError ) return node;

	ParseOptionalScope(node);

	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseParameterList());
	if( isSyntaxError ) return node;

	// Parse an optional const after the function definition (used for object methods)
	sToken t1;
	GetToken(&t1);
	RewindTo(&t1);
	if( t1.type == ttConst )
		node->AddChildLast(ParseToken(ttConst));

	return node;
}

asCScriptNode *asCParser::ParseTypeMod(bool isParam)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);

	sToken t;

	// Parse possible & token
	GetToken(&t);
	RewindTo(&t);
	if( t.type == ttAmp )
	{
		node->AddChildLast(ParseToken(ttAmp));
		if( isSyntaxError ) return node;

		if( isParam )
		{
			GetToken(&t);
			RewindTo(&t);

			if( t.type == ttIn || t.type == ttOut || t.type == ttInOut )
			{
				int tokens[3] = {ttIn, ttOut, ttInOut};
				node->AddChildLast(ParseOneOf(tokens, 3));
			}
		}
	}

	// Parse possible + token 
	GetToken(&t);
	RewindTo(&t);
	if( t.type == ttPlus )
	{
		node->AddChildLast(ParseToken(ttPlus));
		if( isSyntaxError ) return node;
	}

	return node;
}

asCScriptNode *asCParser::ParseType(bool allowConst, bool allowVariableType)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);

	sToken t;

	if( allowConst )
	{
		GetToken(&t);
		RewindTo(&t);
		if( t.type == ttConst )
		{
			node->AddChildLast(ParseToken(ttConst));
			if( isSyntaxError ) return node;
		}
	}

	// Parse scope prefix
	ParseOptionalScope(node);

	// Parse the actual type
	node->AddChildLast(ParseDataType(allowVariableType));

	// If the datatype is a template type, then parse the subtype within the < >
	asCScriptNode *type = node->lastChild;
	asCString typeName;
	typeName.Assign(&script->code[type->tokenPos], type->tokenLength);
	if( engine->IsTemplateType(typeName.AddressOf()) )
	{
		GetToken(&t);
		if( t.type != ttLessThan )
		{
			Error(ExpectedToken(asCTokenizer::GetDefinition(ttLessThan)).AddressOf(), &t);
			return node;
		}

		node->AddChildLast(ParseType(true, false));
		if( isSyntaxError ) return node;

		// Accept >> and >>> tokens too. But then force the tokenizer to move 
		// only 1 character ahead (thus splitting the token in two).
		GetToken(&t);
		if( script->code[t.pos] != '>' )
		{
			Error(ExpectedToken(asCTokenizer::GetDefinition(ttGreaterThan)).AddressOf(), &t);
			return node;
		}
		else
		{
			// Break the token so that only the first > is parsed
			sToken t2 = t;
			t2.pos = t.pos + 1;
			RewindTo(&t2);
		}
	}

	// Parse [] and @
	GetToken(&t);
	RewindTo(&t);
	while( t.type == ttOpenBracket || t.type == ttHandle)
	{
		if( t.type == ttOpenBracket )
		{
			node->AddChildLast(ParseToken(ttOpenBracket));
			if( isSyntaxError ) return node;

			GetToken(&t);
			if( t.type != ttCloseBracket )
			{
				Error(ExpectedToken("]").AddressOf(), &t);
				return node;
			}
		}
		else
		{
			node->AddChildLast(ParseToken(ttHandle));
			if( isSyntaxError ) return node;
		}

		GetToken(&t);
		RewindTo(&t);
	}

	return node;
}

asCScriptNode *asCParser::ParseToken(int token)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined);

	sToken t1;

	GetToken(&t1);
	if( t1.type != token )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(token)).AddressOf(), &t1);
		return node;
	}

	node->SetToken(&t1);
	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseOneOf(int *tokens, int count)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined);

	sToken t1;

	GetToken(&t1);
	int n;
	for( n = 0; n < count; n++ )
	{
		if( tokens[n] == t1.type )
			break;
	}
	if( n == count )
	{
		Error(ExpectedOneOf(tokens, count).AddressOf(), &t1);
		return node;
	}

	node->SetToken(&t1);
	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}


asCScriptNode *asCParser::ParseDataType(bool allowVariableType)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);

	sToken t1;

	GetToken(&t1);
	if( !IsDataType(t1) && !(allowVariableType && t1.type == ttQuestion) )
	{
		if( t1.type == ttIdentifier )
		{
			asCString errMsg, Identifier;
			Identifier.Assign(&script->code[t1.pos], t1.length);
			errMsg.Format(TXT_IDENTIFIER_s_NOT_DATA_TYPE, Identifier.AddressOf());
			Error(errMsg.AddressOf(), &t1);
		}
		else
			Error(TXT_EXPECTED_DATA_TYPE, &t1);
		return node;
	}

	node->SetToken(&t1);
	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseRealType()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);

	sToken t1;

	GetToken(&t1);
	if( !IsRealType(t1.type) )
	{
		Error(TXT_EXPECTED_DATA_TYPE, &t1);
		return node;
	}

	node->SetToken(&t1);
	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseIdentifier()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snIdentifier);

	sToken t1;

	GetToken(&t1);
	if( t1.type != ttIdentifier )
	{
		Error(TXT_EXPECTED_IDENTIFIER, &t1);
		return node;
	}

	node->SetToken(&t1);
	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseParameterList()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snParameterList);

	sToken t1;
	GetToken(&t1);
	if( t1.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	GetToken(&t1);
	if( t1.type == ttCloseParanthesis )
	{
		node->UpdateSourcePos(t1.pos, t1.length);

		// Statement block is finished
		return node;
	}
	else
	{
		// If the parameter list is just (void) then the void token should be ignored
		if( t1.type == ttVoid )
		{
			sToken t2;
			GetToken(&t2);
			if( t2.type == ttCloseParanthesis )
			{
				node->UpdateSourcePos(t2.pos, t2.length);
				return node;
			}
		}

		RewindTo(&t1);

		for(;;)
		{
			// Parse data type
			node->AddChildLast(ParseType(true, isParsingAppInterface));
			if( isSyntaxError ) return node;

			node->AddChildLast(ParseTypeMod(true));
			if( isSyntaxError ) return node;

			// Parse identifier
			GetToken(&t1);
			if( t1.type == ttIdentifier )
			{
				RewindTo(&t1);

				node->AddChildLast(ParseIdentifier());
				if( isSyntaxError ) return node;

				GetToken(&t1);

				// Parse the expression for the default arg
				if( t1.type == ttAssignment )
				{
					// Do a superficial parsing of the default argument
					// The actual parsing will be done when the argument is compiled for a function call
					node->AddChildLast(SuperficiallyParseExpression());
					if( isSyntaxError ) return node;

					GetToken(&t1);
				}
			}

			// Check if list continues
			if( t1.type == ttCloseParanthesis )
			{
				node->UpdateSourcePos(t1.pos, t1.length);

				return node;
			}
			else if( t1.type == ttListSeparator )
				continue;
			else
			{
				Error(ExpectedTokens(")", ",").AddressOf(), &t1);
				return node;
			}
		}
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::SuperficiallyParseExpression()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExpression);

	// Simply parse everything until the first , or ), whichever comes first. 
	// Keeping in mind that () and {} can group expressions.

	asCString stack;
	sToken t;
	for(;;)
	{
		GetToken(&t);

		if( t.type == ttOpenParanthesis )
			stack += "(";
		else if( t.type == ttCloseParanthesis )
		{
			if( stack == "" )
			{
				// Expression has ended. This token is not part of expression
				RewindTo(&t);
				break;
			}
			else if( stack[stack.GetLength()-1] == '(' )
			{
				// Group has ended
				stack.SetLength(stack.GetLength()-1);
			}
			else
			{
				// Wrong syntax
				RewindTo(&t);
				asCString str;
				str.Format(TXT_UNEXPECTED_TOKEN_s, ")");
				Error(str.AddressOf(), &t);
				return node;
			}
		}
		else if( t.type == ttListSeparator )
		{
			if( stack == "" )
			{
				// Expression has ended. This token is not part of expression
				RewindTo(&t);
				break;
			}
		}
		else if( t.type == ttStartStatementBlock )
			stack += "{";
		else if( t.type == ttEndStatementBlock )
		{
			if( stack == "" || stack[stack.GetLength()-1] != '{' )
			{
				// Wrong syntax
				RewindTo(&t);
				asCString str;
				str.Format(TXT_UNEXPECTED_TOKEN_s, "}");
				Error(str.AddressOf(), &t);
				return node;
			}
			else
			{
				// Group has ended
				stack.SetLength(stack.GetLength()-1);
			}
		}
		else if( t.type == ttEndStatement )
		{
			// Wrong syntax (since we're parsing a default arg expression)
			RewindTo(&t);
			asCString str;
			str.Format(TXT_UNEXPECTED_TOKEN_s, ";");
			Error(str.AddressOf(), &t);
			return node;
		}
		else if( t.type == ttEnd )
		{
			// Wrong syntax
			RewindTo(&t);
			Error(TXT_UNEXPECTED_END_OF_FILE, &t);
			return node;
		}

		// Include the token in the node
		node->UpdateSourcePos(t.pos, t.length);
	}

	return node;
}

void asCParser::GetToken(sToken *token)
{
	size_t sourceLength = script->codeLength;

	do
	{
		if( sourcePos >= sourceLength )
		{
			token->type = ttEnd;
			token->length = 0;
		}
		else
			token->type = engine->tok.GetToken(&script->code[sourcePos], sourceLength - sourcePos, &token->length);

		token->pos = sourcePos;

		// Update state
		sourcePos += token->length;
	}
	// Filter out whitespace and comments
	while( token->type == ttWhiteSpace || 
	       token->type == ttOnelineComment ||
		   token->type == ttMultilineComment );
}

void asCParser::RewindTo(const sToken *token)
{
	sourcePos = token->pos;
}

void asCParser::Error(const char *text, sToken *token)
{
	RewindTo(token);

	isSyntaxError     = true;
	errorWhileParsing = true;

	int row, col;
	script->ConvertPosToRowCol(token->pos, &row, &col);

	if( builder )
		builder->WriteError(script->name.AddressOf(), text, row, col);
}

bool asCParser::IsRealType(int tokenType)
{
	if( tokenType == ttVoid ||
		tokenType == ttInt ||
		tokenType == ttInt8 ||
		tokenType == ttInt16 ||
		tokenType == ttInt64 ||
		tokenType == ttUInt ||
		tokenType == ttUInt8 ||
		tokenType == ttUInt16 ||
		tokenType == ttUInt64 ||
		tokenType == ttFloat ||
		tokenType == ttBool ||
		tokenType == ttDouble )
		return true;

	return false;
}

bool asCParser::IsDataType(const sToken &token)
{
	if( token.type == ttIdentifier )
	{
		if( checkValidTypes )
		{
			// Check if this is a registered type
			asCString str;
			str.Assign(&script->code[token.pos], token.length);
			// TODO: namespace: Should parser really keep track of namespace?
			if( !builder->GetObjectType(str.AddressOf(), "") && !builder->GetFuncDef(str.AddressOf()) )
				return false;
		}
		return true;
	}

	if( IsRealType(token.type) )
		return true;

	return false;
}

asCString asCParser::ExpectedToken(const char *token)
{
	asCString str;

	str.Format(TXT_EXPECTED_s, token);

	return str;
}

asCString asCParser::ExpectedTokens(const char *t1, const char *t2)
{
	asCString str;

	str.Format(TXT_EXPECTED_s_OR_s, t1, t2);

	return str;
}

asCString asCParser::ExpectedOneOf(int *tokens, int count)
{
	asCString str;

	str = TXT_EXPECTED_ONE_OF;
	for( int n = 0; n < count; n++ )
	{
		str += asCTokenizer::GetDefinition(tokens[n]);
		if( n < count-1 )
			str += ", ";
	}

	return str;
}

asCString asCParser::ExpectedOneOf(const char **tokens, int count)
{
	asCString str;

	str = TXT_EXPECTED_ONE_OF;
	for( int n = 0; n < count; n++ )
	{
		str += tokens[n];
		if( n < count-1 )
			str += ", ";
	}

	return str;
}

#ifndef AS_NO_COMPILER
bool asCParser::IdentifierIs(const sToken &t, const char *str)
{
	if( t.type != ttIdentifier ) 
		return false;

	return script->TokenEquals(t.pos, t.length, str);
}

bool asCParser::CheckTemplateType(sToken &t)
{
	// Is this a template type?
	asCString typeName;
	typeName.Assign(&script->code[t.pos], t.length);
	if( engine->IsTemplateType(typeName.AddressOf()) )
	{
		// Expect the sub type within < >
		GetToken(&t);
		if( t.type != ttLessThan )
			return false;

		// Now there must be a data type
		GetToken(&t);
		if( !IsDataType(t) )
			return false;

		if( !CheckTemplateType(t) )
			return false;

		GetToken(&t);

		// Is it a handle or array?
		while( t.type == ttHandle || t.type == ttOpenBracket )
		{
			if( t.type == ttOpenBracket )
			{
				GetToken(&t);
				if( t.type != ttCloseBracket )
					return false;
			}

			GetToken(&t);
		}

		// Accept >> and >>> tokens too. But then force the tokenizer to move 
		// only 1 character ahead (thus splitting the token in two).
		if( script->code[t.pos] != '>' )
			return false;
		else if( t.length != 1 )
		{
			// We need to break the token, so that only the first character is parsed
			sToken t2 = t;
			t2.pos = t.pos + 1;
			RewindTo(&t2);
		}
	}

	return true;
}

asCScriptNode *asCParser::ParseCast()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snCast);

	sToken t1;
	GetToken(&t1);
	if( t1.type != ttCast )
	{
		Error(ExpectedToken("cast").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	GetToken(&t1);
	if( t1.type != ttLessThan )
	{
		Error(ExpectedToken("<").AddressOf(), &t1);
		return node;
	}

	// Parse the data type
	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseTypeMod(false));
	if( isSyntaxError ) return node;

	GetToken(&t1);
	if( t1.type != ttGreaterThan )
	{
		Error(ExpectedToken(">").AddressOf(), &t1);
		return node;
	}

	GetToken(&t1);
	if( t1.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t1);
		return node;
	}

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t1);
	if( t1.type != ttCloseParanthesis )
	{
		Error(ExpectedToken(")").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseExprValue()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprValue);

	sToken t1, t2;
	GetToken(&t1);
	GetToken(&t2);
	RewindTo(&t1);

	// TODO: namespace: Datatypes can be defined in namespaces, thus types too must allow scope prefix
	if( IsDataType(t1) && (t2.type == ttOpenParanthesis || 
		                   t2.type == ttLessThan || 
						   t2.type == ttOpenBracket) )
		node->AddChildLast(ParseConstructCall());
	else if( t1.type == ttIdentifier || t1.type == ttScope )
	{
		if( IsFunctionCall() )
			node->AddChildLast(ParseFunctionCall());
		else
			node->AddChildLast(ParseVariableAccess());
	}
	else if( t1.type == ttCast )
		node->AddChildLast(ParseCast());
	else if( IsConstant(t1.type) )
		node->AddChildLast(ParseConstant());
	else if( t1.type == ttOpenParanthesis )
	{
		GetToken(&t1);
		node->UpdateSourcePos(t1.pos, t1.length);

		node->AddChildLast(ParseAssignment());
		if( isSyntaxError ) return node;

		GetToken(&t1);
		if( t1.type != ttCloseParanthesis )
			Error(ExpectedToken(")").AddressOf(), &t1);

		node->UpdateSourcePos(t1.pos, t1.length);
	}
	else
		Error(TXT_EXPECTED_EXPRESSION_VALUE, &t1);

	return node;
}

asCScriptNode *asCParser::ParseConstant()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snConstant);

	sToken t;
	GetToken(&t);
	if( !IsConstant(t.type) )
	{
		Error(TXT_EXPECTED_CONSTANT, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	// We want to gather a list of string constants to concatenate as children
	if( t.type == ttStringConstant || t.type == ttMultilineStringConstant || t.type == ttHeredocStringConstant )
		RewindTo(&t);

	while( t.type == ttStringConstant || t.type == ttMultilineStringConstant || t.type == ttHeredocStringConstant )
	{
		node->AddChildLast(ParseStringConstant());

		GetToken(&t);
		RewindTo(&t);
	}

	return node;
}

asCScriptNode *asCParser::ParseStringConstant()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snConstant);

	sToken t;
	GetToken(&t);
	if( t.type != ttStringConstant && t.type != ttMultilineStringConstant && t.type != ttHeredocStringConstant )
	{
		Error(TXT_EXPECTED_STRING, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseFunctionCall()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFunctionCall);

	// Parse scope prefix
	ParseOptionalScope(node);

	// Parse the function name followed by the argument list
	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseArgList());

	return node;
}

asCScriptNode *asCParser::ParseVariableAccess()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snVariableAccess);

	// Parse scope prefix
	ParseOptionalScope(node);

	// Parse the variable name
	node->AddChildLast(ParseIdentifier());

	return node;
}

asCScriptNode *asCParser::ParseConstructCall()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snConstructCall);

	node->AddChildLast(ParseType(false));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseArgList());

	return node;
}

asCScriptNode *asCParser::ParseArgList()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snArgList);

	sToken t1;
	GetToken(&t1);
	if( t1.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	GetToken(&t1);
	if( t1.type == ttCloseParanthesis )
	{
		node->UpdateSourcePos(t1.pos, t1.length);

		// Statement block is finished
		return node;
	}
	else
	{
		RewindTo(&t1);

		for(;;)
		{
			node->AddChildLast(ParseAssignment());
			if( isSyntaxError ) return node;

			// Check if list continues
			GetToken(&t1);
			if( t1.type == ttCloseParanthesis )
			{
				node->UpdateSourcePos(t1.pos, t1.length);

				return node;
			}
			else if( t1.type == ttListSeparator )
				continue;
			else
			{
				Error(ExpectedTokens(")", ",").AddressOf(), &t1);
				return node;
			}
		}
	}
}

bool asCParser::IsFunctionCall()
{
	sToken s;
	sToken t1, t2;

	GetToken(&s);
	t1 = s;

	// A function call may be prefixed with scope resolution
	if( t1.type == ttScope )
		GetToken(&t1);
	GetToken(&t2);

	while( t1.type == ttIdentifier && t2.type == ttScope )
	{
		GetToken(&t1);
		GetToken(&t2);
	}

	// A function call starts with an identifier followed by an argument list
	if( t1.type != ttIdentifier || IsDataType(t1) )
	{
		RewindTo(&s);
		return false;
	}

	if( t2.type == ttOpenParanthesis )
	{
		RewindTo(&s);
		return true;
	}

	RewindTo(&s);
	return false;
}

asCScriptNode *asCParser::ParseAssignment()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snAssignment);

	node->AddChildLast(ParseCondition());
	if( isSyntaxError ) return node;

	sToken t;
	GetToken(&t);
	RewindTo(&t);

	if( IsAssignOperator(t.type) )
	{
		node->AddChildLast(ParseAssignOperator());
		if( isSyntaxError ) return node;

		node->AddChildLast(ParseAssignment());
		if( isSyntaxError ) return node;
	}

	return node;
}

asCScriptNode *asCParser::ParseCondition()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snCondition);

	node->AddChildLast(ParseExpression());
	if( isSyntaxError ) return node;

	sToken t;
	GetToken(&t);
	if( t.type == ttQuestion )
	{
		node->AddChildLast(ParseAssignment());
		if( isSyntaxError ) return node;

		GetToken(&t);
		if( t.type != ttColon )
		{
			Error(ExpectedToken(":").AddressOf(), &t);
			return node;
		}

		node->AddChildLast(ParseAssignment());
		if( isSyntaxError ) return node;
	}
	else
		RewindTo(&t);

	return node;
}

asCScriptNode *asCParser::ParseExpression()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExpression);

	node->AddChildLast(ParseExprTerm());
	if( isSyntaxError ) return node;

	for(;;)
	{
		sToken t;
		GetToken(&t);
		RewindTo(&t);

		if( !IsOperator(t.type) )
			return node;

		node->AddChildLast(ParseExprOperator());
		if( isSyntaxError ) return node;

		node->AddChildLast(ParseExprTerm());
		if( isSyntaxError ) return node;
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseExprTerm()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprTerm);

	for(;;)
	{
		sToken t;
		GetToken(&t);
		RewindTo(&t);
		if( !IsPreOperator(t.type) )
			break;

		node->AddChildLast(ParseExprPreOp());
		if( isSyntaxError ) return node;
	}

	node->AddChildLast(ParseExprValue());
	if( isSyntaxError ) return node;

	
	for(;;)
	{
		sToken t;
		GetToken(&t);
		RewindTo(&t);
		if( !IsPostOperator(t.type) )
			return node;

		node->AddChildLast(ParseExprPostOp());
		if( isSyntaxError ) return node;
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseExprPreOp()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprPreOp);

	sToken t;
	GetToken(&t);
	if( !IsPreOperator(t.type) )
	{
		Error(TXT_EXPECTED_PRE_OPERATOR, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseExprPostOp()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprPostOp);

	sToken t;
	GetToken(&t);
	if( !IsPostOperator(t.type) )
	{
		Error(TXT_EXPECTED_POST_OPERATOR, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	if( t.type == ttDot )
	{
		sToken t1, t2;
		GetToken(&t1);
		GetToken(&t2);
		RewindTo(&t1);
		if( t2.type == ttOpenParanthesis )
			node->AddChildLast(ParseFunctionCall());
		else
			node->AddChildLast(ParseIdentifier());
	}
	else if( t.type == ttOpenBracket )
	{
		node->AddChildLast(ParseAssignment());

		GetToken(&t);
		if( t.type != ttCloseBracket )
		{
			Error(ExpectedToken("]").AddressOf(), &t);
			return node;
		}

		node->UpdateSourcePos(t.pos, t.length);
	}

	return node;
}

asCScriptNode *asCParser::ParseExprOperator()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprOperator);

	sToken t;
	GetToken(&t);
	if( !IsOperator(t.type) )
	{
		Error(TXT_EXPECTED_OPERATOR, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseAssignOperator()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExprOperator);

	sToken t;
	GetToken(&t);
	if( !IsAssignOperator(t.type) )
	{
		Error(TXT_EXPECTED_OPERATOR, &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

bool asCParser::IsOperator(int tokenType)
{
	if( tokenType == ttPlus ||
		tokenType == ttMinus ||
		tokenType == ttStar ||
		tokenType == ttSlash ||
		tokenType == ttPercent ||
		tokenType == ttAnd ||
		tokenType == ttOr ||
		tokenType == ttXor ||
		tokenType == ttEqual ||
		tokenType == ttNotEqual ||
		tokenType == ttLessThan ||
		tokenType == ttLessThanOrEqual ||
		tokenType == ttGreaterThan ||
		tokenType == ttGreaterThanOrEqual ||
		tokenType == ttAmp ||
		tokenType == ttBitOr ||
		tokenType == ttBitXor ||
		tokenType == ttBitShiftLeft ||
		tokenType == ttBitShiftRight ||
		tokenType == ttBitShiftRightArith ||
		tokenType == ttIs ||
		tokenType == ttNotIs )
		return true;

	return false;
}

bool asCParser::IsAssignOperator(int tokenType)
{
	if( tokenType == ttAssignment ||
		tokenType == ttAddAssign ||
		tokenType == ttSubAssign ||
		tokenType == ttMulAssign ||
		tokenType == ttDivAssign ||
		tokenType == ttModAssign ||
		tokenType == ttAndAssign ||
		tokenType == ttOrAssign ||
		tokenType == ttXorAssign ||
		tokenType == ttShiftLeftAssign ||
		tokenType == ttShiftRightLAssign ||
		tokenType == ttShiftRightAAssign )
		return true;

	return false;
}

bool asCParser::IsPreOperator(int tokenType)
{
	if( tokenType == ttMinus ||
		tokenType == ttPlus ||
		tokenType == ttNot ||
		tokenType == ttInc ||
		tokenType == ttDec ||
		tokenType == ttBitNot ||
		tokenType == ttHandle )
		return true;
	return false;
}

bool asCParser::IsPostOperator(int tokenType)
{
	if( tokenType == ttInc ||
		tokenType == ttDec ||
		tokenType == ttDot ||
		tokenType == ttOpenBracket )
		return true;
	return false;
}

bool asCParser::IsConstant(int tokenType)
{
	if( tokenType == ttIntConstant ||
		tokenType == ttFloatConstant ||
		tokenType == ttDoubleConstant ||
		tokenType == ttStringConstant ||
		tokenType == ttMultilineStringConstant ||
		tokenType == ttHeredocStringConstant ||
		tokenType == ttTrue ||
		tokenType == ttFalse ||
		tokenType == ttBitsConstant ||
		tokenType == ttNull )
		return true;

	return false;
}

int asCParser::ParseScript(asCScriptCode *script)
{
	Reset();

	this->script = script;

	scriptNode = ParseScript(false);

	if( errorWhileParsing )
		return -1;

	return 0;
}

int asCParser::ParseExpression(asCScriptCode *script)
{
	Reset();

	this->script = script;

	scriptNode = ParseExpression();
	if( errorWhileParsing )
		return -1;

	return 0;
}

asCScriptNode *asCParser::ParseImport()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snImport);

	sToken t;
	GetToken(&t);
	if( t.type != ttImport )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttImport)).AddressOf(), &t);
		return node;
	}

	node->SetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	node->AddChildLast(ParseFunctionDefinition());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttIdentifier )
	{
		Error(ExpectedToken(FROM_TOKEN).AddressOf(), &t);
		return node;
	}

	asCString str;
	str.Assign(&script->code[t.pos], t.length);
	if( str != FROM_TOKEN )
	{
		Error(ExpectedToken(FROM_TOKEN).AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttStringConstant )
	{
		Error(TXT_EXPECTED_STRING, &t);
		return node;
	}

	asCScriptNode *mod = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snConstant);
	node->AddChildLast(mod);

	mod->SetToken(&t);
	mod->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttEndStatement )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEndStatement)).AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseScript(bool inBlock)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snScript);

	// Determine type of node
	sToken t1, t2;

	for(;;)
	{
		while( !isSyntaxError )
		{
			GetToken(&t1);
			GetToken(&t2);
			RewindTo(&t1);

			if( t1.type == ttImport )
				node->AddChildLast(ParseImport());
			else if( t1.type == ttEnum || (IdentifierIs(t1, SHARED_TOKEN) && t2.type == ttEnum) )
				node->AddChildLast(ParseEnumeration());	//	Handle enumerations
			else if( t1.type == ttTypedef )
				node->AddChildLast(ParseTypedef());		//	Handle primitive typedefs
			else if( t1.type == ttClass || 
					 ((IdentifierIs(t1, SHARED_TOKEN) || IdentifierIs(t1, FINAL_TOKEN)) && t2.type == ttClass) || 
					 (IdentifierIs(t1, SHARED_TOKEN) && IdentifierIs(t2, FINAL_TOKEN)) )
				node->AddChildLast(ParseClass());
			else if( t1.type == ttInterface || (t1.type == ttIdentifier && t2.type == ttInterface) )
				node->AddChildLast(ParseInterface());
			else if( t1.type == ttFuncDef )
				node->AddChildLast(ParseFuncDef());
			else if( t1.type == ttConst || IsDataType(t1) )
			{
				if( IsVirtualPropertyDecl() )
					node->AddChildLast(ParseVirtualPropertyDecl(false, false));
				else if( IsVarDecl() )
					node->AddChildLast(ParseGlobalVar());
				else
					node->AddChildLast(ParseFunction());
			}
			else if( t1.type == ttEndStatement )
			{
				// Ignore a semicolon by itself
				GetToken(&t1);
			}
			else if( t1.type == ttNamespace )
				node->AddChildLast(ParseNamespace());
			else if( t1.type == ttEnd )
			{
				if( inBlock )
					Error(ExpectedToken(asCTokenizer::GetDefinition(ttEndStatementBlock)).AddressOf(), &t1);

				return node;
			}
			else if( inBlock && t1.type == ttEndStatementBlock )
				return node;
			else
			{
				asCString str;
				const char *t = asCTokenizer::GetDefinition(t1.type);
				if( t == 0 ) t = "<unknown token>";

				str.Format(TXT_UNEXPECTED_TOKEN_s, t);

				Error(str.AddressOf(), &t1);
			}
		}

		if( isSyntaxError )
		{
			// Search for either ';' or '{' or end
			GetToken(&t1);
			while( t1.type != ttEndStatement && t1.type != ttEnd &&
				   t1.type != ttStartStatementBlock )
				GetToken(&t1);

			if( t1.type == ttStartStatementBlock )
			{
				// Find the end of the block and skip nested blocks
				int level = 1;
				while( level > 0 )
				{
					GetToken(&t1);
					if( t1.type == ttStartStatementBlock ) level++;
					if( t1.type == ttEndStatementBlock ) level--;
					if( t1.type == ttEnd ) break;
				}
			}

			isSyntaxError = false;
		}
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseNamespace()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snNamespace);

	sToken t1;

	GetToken(&t1);
	if( t1.type == ttNamespace )
		node->UpdateSourcePos(t1.pos, t1.length);
	else
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttNamespace)).AddressOf(), &t1);

	// TODO: namespace: Allow declaration of multiple nested namespace with namespace A::B::C { }
	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	GetToken(&t1);
	if( t1.type == ttStartStatementBlock )
		node->UpdateSourcePos(t1.pos, t1.length);
	else
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttStartStatementBlock)).AddressOf(), &t1);

	node->AddChildLast(ParseScript(true));

	if( !isSyntaxError )
	{
		GetToken(&t1);
		if( t1.type == ttEndStatementBlock )
			node->UpdateSourcePos(t1.pos, t1.length);
		else
			Error(ExpectedToken(asCTokenizer::GetDefinition(ttEndStatementBlock)).AddressOf(), &t1);
	}

	return node;
}

int asCParser::ParseStatementBlock(asCScriptCode *script, asCScriptNode *block)
{
	Reset();

	// Tell the parser to validate the identifiers as valid types
	checkValidTypes = true;

	this->script = script;
	sourcePos = block->tokenPos;

	scriptNode = ParseStatementBlock();	

	if( isSyntaxError || errorWhileParsing )
		return -1;

	return 0;
}

asCScriptNode *asCParser::ParseEnumeration()
{
	asCScriptNode *ident;
	asCScriptNode *dataType;

	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snEnum);

	sToken	token;

	// Optional 'shared' token
	GetToken(&token);
	if( IdentifierIs(token, SHARED_TOKEN) )
	{	
		RewindTo(&token);
		node->AddChildLast(ParseIdentifier());
		if( isSyntaxError ) return node;

		GetToken(&token);
	}

	// Check for enum
	if( token.type != ttEnum )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEnum)).AddressOf(), &token);
		return node;
	}

	node->SetToken(&token);
	node->UpdateSourcePos(token.pos, token.length);

	// Get the identifier
	GetToken(&token);
	if(ttIdentifier != token.type) 
	{
		Error(TXT_EXPECTED_IDENTIFIER, &token);
		return node;
	}

	dataType = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDataType);
	node->AddChildLast(dataType);

	ident = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snIdentifier);
	ident->SetToken(&token);
	ident->UpdateSourcePos(token.pos, token.length);
	dataType->AddChildLast(ident);

	// check for the start of the declaration block
	GetToken(&token);
	if( token.type != ttStartStatementBlock ) 
	{
		RewindTo(&token);
		Error(ExpectedToken(asCTokenizer::GetDefinition(token.type)).AddressOf(), &token);
		return node;
	}

	while(ttEnd != token.type) 
	{
		GetToken(&token);

		if( ttEndStatementBlock == token.type ) 
		{
			RewindTo(&token);
			break;
		}

		if(ttIdentifier != token.type) 
		{
			Error(TXT_EXPECTED_IDENTIFIER, &token);
			return node;
		}

		//	Add the enum element
		ident = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snIdentifier);
		ident->SetToken(&token);
		ident->UpdateSourcePos(token.pos, token.length);
		node->AddChildLast(ident);

		GetToken(&token);

		if( token.type == ttAssignment )
		{
			asCScriptNode	*tmp;

			RewindTo(&token);

			tmp = SuperficiallyParseGlobalVarInit();

			node->AddChildLast(tmp);
			if( isSyntaxError ) return node;
			GetToken(&token);
		}

		if(ttListSeparator != token.type) 
		{
			RewindTo(&token);
			break;
		}
	}

	//	check for the end of the declaration block
	GetToken(&token);
	if( token.type != ttEndStatementBlock ) 
	{
		RewindTo(&token);
		Error(ExpectedToken(asCTokenizer::GetDefinition(token.type)).AddressOf(), &token);
		return node;
	}

	//	Parse the declarations
	return node;
}

bool asCParser::IsVarDecl()
{
	// Set start point so that we can rewind
	sToken t;
	GetToken(&t);
	RewindTo(&t);

	// A class property decl can be preceded by 'private' 
	sToken t1;
	GetToken(&t1);
	if( t1.type != ttPrivate )
		RewindTo(&t1);

	// A variable decl can start with a const
	GetToken(&t1);
	if( t1.type == ttConst )
		GetToken(&t1);

	// The type may be initiated with the scope operator
	if( t1.type == ttScope )
		GetToken(&t1);

	// The type may be preceeded with a multilevel scope
	sToken t2;
	GetToken(&t2);
	while( t1.type == ttIdentifier && t2.type == ttScope )
	{
		GetToken(&t1);
		GetToken(&t2);
	}
	RewindTo(&t2);

	// We don't validate if the identifier is an actual declared type at this moment
	// as it may wrongly identify the statement as a non-declaration if the user typed
	// the name incorrectly. The real type is validated in ParseDeclaration where a
	// proper error message can be given.
	if( !IsRealType(t1.type) && t1.type != ttIdentifier )
	{
		RewindTo(&t);
		return false;
	}

	if( !CheckTemplateType(t1) )
	{
		RewindTo(&t);
		return false;
	}

	// Object handles can be interleaved with the array brackets
	GetToken(&t2);
	while( t2.type == ttHandle || t2.type == ttOpenBracket )
	{
		if( t2.type == ttOpenBracket )
		{
			GetToken(&t2);
			if( t2.type != ttCloseBracket )
			{
				RewindTo(&t);
				return false;
			}
		}

		GetToken(&t2);
	}

	if( t2.type != ttIdentifier )
	{
		RewindTo(&t);
		return false;
	}

	GetToken(&t2);
	if( t2.type == ttEndStatement || t2.type == ttAssignment || t2.type == ttListSeparator )
	{
		RewindTo(&t);
		return true;
	}
	if( t2.type == ttOpenParanthesis ) 
	{	
		// If the closing paranthesis is followed by a statement 
		// block or end-of-file, then treat it as a function. 
		while( t2.type != ttCloseParanthesis && t2.type != ttEnd )
			GetToken(&t2);

		if( t2.type == ttEnd ) 
			return false;
		else
		{
			GetToken(&t1);
			RewindTo(&t);
			if( t1.type == ttStartStatementBlock || t1.type == ttEnd )
				return false;
		}

		RewindTo(&t);

		return true;
	}

	RewindTo(&t);
	return false;
}

bool asCParser::IsVirtualPropertyDecl()
{
	// Set start point so that we can rewind
	sToken t;
	GetToken(&t);
	RewindTo(&t);

	// A class property decl can be preceded by 'private' 
	sToken t1;
	GetToken(&t1);
	if( t1.type != ttPrivate )
		RewindTo(&t1);

	// A variable decl can start with a const
	GetToken(&t1);
	if( t1.type == ttConst )
		GetToken(&t1);

	// We don't validate if the identifier is an actual declared type at this moment
	// as it may wrongly identify the statement as a non-declaration if the user typed
	// the name incorrectly. The real type is validated in ParseDeclaration where a
	// proper error message can be given.
	if( !IsRealType(t1.type) && t1.type != ttIdentifier )
	{
		RewindTo(&t);
		return false;
	}

	if( !CheckTemplateType(t1) )
	{
		RewindTo(&t);
		return false;
	}

	// Object handles can be interleaved with the array brackets
	sToken t2;
	GetToken(&t2);
	while( t2.type == ttHandle || t2.type == ttOpenBracket )
	{
		if( t2.type == ttOpenBracket )
		{
			GetToken(&t2);
			if( t2.type != ttCloseBracket )
			{
				RewindTo(&t);
				return false;
			}
		}

		GetToken(&t2);
	}

	if( t2.type != ttIdentifier )
	{
		RewindTo(&t);
		return false;
	}

	GetToken(&t2);
	if( t2.type == ttStartStatementBlock )
	{
		RewindTo(&t);
		return true;
	}

	RewindTo(&t);
	return false;
}

bool asCParser::IsFuncDecl(bool isMethod)
{
	// Set start point so that we can rewind
	sToken t;
	GetToken(&t);
	RewindTo(&t);

	// A class method decl can be preceded by 'private' 
	if( isMethod )
	{
		sToken t1;
		GetToken(&t1);
		if( t1.type != ttPrivate )
			RewindTo(&t1);
	}

	// A class constructor starts with identifier followed by parenthesis
	// A class destructor starts with the ~ token
	if( isMethod )
	{
		sToken t1, t2;
		GetToken(&t1);
		GetToken(&t2);
		RewindTo(&t1);
		if( (t1.type == ttIdentifier && t2.type == ttOpenParanthesis) || t1.type == ttBitNot )
		{
			RewindTo(&t);
			return true;
		}
	}

	// A function decl can start with a const
	sToken t1;
	GetToken(&t1);
	if( t1.type == ttConst )
		GetToken(&t1);

	if( !IsDataType(t1) )
	{
		RewindTo(&t);
		return false;
	}

	if( !CheckTemplateType(t1) )
	{
		RewindTo(&t);
		return false;
	}

	// Object handles can be interleaved with the array brackets
	sToken t2;
	GetToken(&t2);
	while( t2.type == ttHandle || t2.type == ttOpenBracket )
	{
		if( t2.type == ttOpenBracket )
		{
			GetToken(&t2);
			if( t2.type != ttCloseBracket )
			{
				RewindTo(&t);
				return false;
			}
		}

		GetToken(&t2);
	}

	// There can be an ampersand if the function returns a reference
	if( t2.type == ttAmp )
	{
		RewindTo(&t);
		return true;
	}

	if( t2.type != ttIdentifier )
	{
		RewindTo(&t);
		return false;
	}

	GetToken(&t2);
	if( t2.type == ttOpenParanthesis ) 
	{	
		// If the closing paranthesis is not followed by a  
		// statement block then it is not a function. 
		while( t2.type != ttCloseParanthesis && t2.type != ttEnd )
			GetToken(&t2);

		if( t2.type == ttEnd ) 
			return false;
		else
		{
			if( isMethod )
			{
				// A class method can have a 'const' token after the parameter list
				GetToken(&t1);
				if( t1.type != ttConst )
					RewindTo(&t1);
				
				// A class method may also have any number of additional inheritance behavior specifiers
				for( ; ; )
				{
					GetToken(&t2);
					if( !IdentifierIs(t2, FINAL_TOKEN) && !IdentifierIs(t2, OVERRIDE_TOKEN) )
					{
						RewindTo(&t2);
						break;
					}
				}
			}

			GetToken(&t1);
			RewindTo(&t);
			if( t1.type == ttStartStatementBlock )
				return true;
		}

		RewindTo(&t);
		return false;
	}

	RewindTo(&t);
	return false;
}

asCScriptNode *asCParser::ParseFuncDef()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFuncDef);

	sToken t1;
	GetToken(&t1);
	if( t1.type != ttFuncDef )
	{
		Error(asCTokenizer::GetDefinition(ttFuncDef), &t1);
		return node;
	}

	node->SetToken(&t1);

	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseTypeMod(false));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseParameterList());
	if( isSyntaxError ) return node;

	GetToken(&t1);
	if( t1.type != ttEndStatement )
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(ttEndStatement)).AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseFunction(bool isMethod)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFunction);

	sToken t1,t2;
	GetToken(&t1);
	GetToken(&t2);
	RewindTo(&t1);

	// A class method can start with private
	if( isMethod && t1.type == ttPrivate )
	{
		node->AddChildLast(ParseToken(ttPrivate));
		if( isSyntaxError ) return node;
	}

	// A global function can be marked as shared
	if( !isMethod && IdentifierIs(t1, SHARED_TOKEN) )
	{
		node->AddChildLast(ParseIdentifier());
		if( isSyntaxError ) return node;
	}

	// If it is a global function, or a method, except constructor and destructor, then the return type is parsed
	if( !isMethod || (t1.type != ttBitNot && t2.type != ttOpenParanthesis) )
	{
		node->AddChildLast(ParseType(true));
		if( isSyntaxError ) return node;

		node->AddChildLast(ParseTypeMod(false));
		if( isSyntaxError ) return node;
	}

	// If this is a class destructor then it starts with ~, and no return type is declared
	if( isMethod && t1.type == ttBitNot )
	{
		node->AddChildLast(ParseToken(ttBitNot));
		if( isSyntaxError ) return node;
	}

	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseParameterList());
	if( isSyntaxError ) return node;

	if( isMethod )
	{
		GetToken(&t1);
		RewindTo(&t1);

		// Is the method a const?
		if( t1.type == ttConst )
			node->AddChildLast(ParseToken(ttConst));

		ParseMethodOverrideBehaviors(node);
		if( isSyntaxError ) return node;
	}

	// We should just find the end of the statement block here. The statements 
	// will be parsed on request by the compiler once it starts the compilation.
	node->AddChildLast(SuperficiallyParseStatementBlock());

	return node;
}

asCScriptNode *asCParser::ParseInterfaceMethod()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFunction);

	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseTypeMod(false));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseParameterList());
	if( isSyntaxError ) return node;

	// Parse an optional const after the method definition
	sToken t1;
	GetToken(&t1);
	RewindTo(&t1);
	if( t1.type == ttConst )
		node->AddChildLast(ParseToken(ttConst));

	GetToken(&t1);
	if( t1.type != ttEndStatement )
	{
		Error(ExpectedToken(";").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseVirtualPropertyDecl(bool isMethod, bool isInterface)
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snVirtualProperty);

	sToken t1,t2;
	GetToken(&t1);
	GetToken(&t2);
	RewindTo(&t1);

	// A class method can start with private
	if( isMethod && t1.type == ttPrivate )
	{
		node->AddChildLast(ParseToken(ttPrivate));
		if( isSyntaxError ) return node;
	}

	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseTypeMod(false));
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseIdentifier());
	if( isSyntaxError ) return node;

	GetToken(&t1);
	if( t1.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t1);
		return node;
	}

	for(;;)
	{
		GetToken(&t1);
		asCScriptNode *accessorNode = 0;

		if( IdentifierIs(t1, GET_TOKEN) || IdentifierIs(t1, SET_TOKEN) )
		{
			accessorNode = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snVirtualProperty);
			node->AddChildLast(accessorNode);

			RewindTo(&t1);
			accessorNode->AddChildLast(ParseIdentifier());
			
			if( isMethod )
			{
				GetToken(&t1);
				RewindTo(&t1);
				if( t1.type == ttConst )
					accessorNode->AddChildLast(ParseToken(ttConst));

				if( !isInterface )
				{
					ParseMethodOverrideBehaviors(accessorNode);
					if( isSyntaxError ) return node;
				}
			}

			if( !isInterface )
			{
				GetToken(&t1);
				if( t1.type == ttStartStatementBlock )
				{
					RewindTo(&t1);
					accessorNode->AddChildLast(SuperficiallyParseStatementBlock());
					if( isSyntaxError ) return node;
				}
				else if( t1.type != ttEndStatement )
				{
					Error(ExpectedTokens(";", "{").AddressOf(), &t1);
					return node;
				}
			}
			else
			{
				GetToken(&t1);
				if( t1.type != ttEndStatement )
				{
					Error(ExpectedToken(";").AddressOf(), &t1);
					return node;
				}
			}
		}
		else if( t1.type == ttEndStatementBlock )
		{
			break;
		}
		else
		{
			const char *tokens[] = { GET_TOKEN, SET_TOKEN, asCTokenizer::GetDefinition(ttEndStatementBlock) };
			Error(ExpectedOneOf(tokens, 3).AddressOf(), &t1);
			return node;
		}
	}

	return node;
}

asCScriptNode *asCParser::ParseInterface()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snInterface);

	sToken t;
	GetToken(&t);

	// Allow keyword 'shared' before 'interface'
	if( t.type == ttIdentifier )
	{
		asCString str;
		str.Assign(&script->code[t.pos], t.length);
		if( str != SHARED_TOKEN )
		{
			Error(ExpectedToken(SHARED_TOKEN).AddressOf(), &t);
			return node;
		}

		RewindTo(&t);
		node->AddChildLast(ParseIdentifier());
		GetToken(&t);
	}

	if( t.type != ttInterface )
	{
		Error(ExpectedToken("interface").AddressOf(), &t);
		return node;
	}

	node->SetToken(&t);

	node->AddChildLast(ParseIdentifier());

	GetToken(&t);
	if( t.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t);
		return node;
	}

	// Parse interface methods
	GetToken(&t);
	RewindTo(&t);
	while( t.type != ttEndStatementBlock && t.type != ttEnd )
	{
		if( IsVirtualPropertyDecl() )
		{
			node->AddChildLast(ParseVirtualPropertyDecl(true, true));
		}
		else
		{
			// Parse the method signature
			node->AddChildLast(ParseInterfaceMethod());
		}

		if( isSyntaxError ) return node;
		
		GetToken(&t);
		RewindTo(&t);
	}

	GetToken(&t);
	if( t.type != ttEndStatementBlock )
	{
		Error(ExpectedToken("}").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseClass()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snClass);

	sToken t;
	GetToken(&t);

	// Allow the keyword 'shared' before 'class'
	if( IdentifierIs(t, SHARED_TOKEN) )
	{
		RewindTo(&t);
		node->AddChildLast(ParseIdentifier());
		GetToken(&t);
	}

	if( IdentifierIs(t, FINAL_TOKEN) )
	{
		RewindTo(&t);
		node->AddChildLast(ParseIdentifier());
		GetToken(&t);
	}

	if( t.type != ttClass )
	{
		Error(ExpectedToken("class").AddressOf(), &t);
		return node;
	}

	node->SetToken(&t);

	if( engine->ep.allowImplicitHandleTypes )
	{
		// Parse 'implicit handle class' construct
		GetToken(&t);
		
		if ( t.type == ttHandle )
			node->SetToken(&t);
		else
			RewindTo(&t);
	}

	node->AddChildLast(ParseIdentifier());

	GetToken(&t);

	// Optional list of interfaces that are being implemented and classes that are being inherited
	if( t.type == ttColon )
	{
		node->AddChildLast(ParseIdentifier());
		GetToken(&t);
		while( t.type == ttListSeparator )
		{
			node->AddChildLast(ParseIdentifier());
			GetToken(&t);
		}
	}

	if( t.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t);
		return node;
	}

	// Parse properties
	GetToken(&t);
	RewindTo(&t);
	while( t.type != ttEndStatementBlock && t.type != ttEnd )
	{
		// Is it a property or a method?
		if( IsFuncDecl(true) )
		{
			// Parse the method
			node->AddChildLast(ParseFunction(true));
		}
		else if( IsVirtualPropertyDecl() )
		{
			node->AddChildLast(ParseVirtualPropertyDecl(true, false));
		}
		else if( IsVarDecl() )
		{
			// Parse a property declaration
			asCScriptNode *prop = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDeclaration);
			node->AddChildLast(prop);

			// A variable declaration can be preceded by 'private'
			if( t.type == ttPrivate )
				prop->AddChildLast(ParseToken(ttPrivate));

			prop->AddChildLast(ParseType(true));
			if( isSyntaxError ) return node;

			prop->AddChildLast(ParseIdentifier());
			if( isSyntaxError ) return node;

			GetToken(&t);
			if( t.type != ttEndStatement )
			{
				Error(ExpectedToken(";").AddressOf(), &t);
				return node;
			}
			prop->UpdateSourcePos(t.pos, t.length);
		}
		else
		{
			Error(TXT_EXPECTED_METHOD_OR_PROPERTY, &t);
			return node;
		}

		GetToken(&t);
		RewindTo(&t);
	}

	GetToken(&t);
	if( t.type != ttEndStatementBlock )
	{
		Error(ExpectedToken("}").AddressOf(), &t);
		return node;
	}
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseGlobalVar()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snGlobalVar);

	// Parse data type
	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	sToken t;

	for(;;)
	{
		// Parse identifier
		node->AddChildLast(ParseIdentifier());
		if( isSyntaxError ) return node;

		// Only superficially parse the initialization info for the variable
		GetToken(&t);
		RewindTo(&t);
		if( t.type == ttAssignment || t.type == ttOpenParanthesis )
		{
			node->AddChildLast(SuperficiallyParseGlobalVarInit());
			if( isSyntaxError ) return node;
		}

		// continue if list separator, else terminate with end statement
		GetToken(&t);
		if( t.type == ttListSeparator )
			continue;
		else if( t.type == ttEndStatement )
		{
			node->UpdateSourcePos(t.pos, t.length);

			return node;
		}
		else
		{
			Error(ExpectedTokens(",", ";").AddressOf(), &t);
			return node;
		}
	}
	UNREACHABLE_RETURN;
}

int asCParser::ParseGlobalVarInit(asCScriptCode *script, asCScriptNode *init)
{
	Reset();

	// Tell the parser to validate the identifiers as valid types
	checkValidTypes = true;

	this->script = script;
	sourcePos = init->tokenPos;

	// If next token is assignment, parse expression
	sToken t;
	GetToken(&t);
	if( t.type == ttAssignment )
	{
		GetToken(&t);
		RewindTo(&t);
		if( t.type == ttStartStatementBlock )
			scriptNode = ParseInitList();
		else
			scriptNode = ParseAssignment();
	}
	else if( t.type == ttOpenParanthesis ) 
	{
		RewindTo(&t);
		scriptNode = ParseArgList();
	}
	else
	{
		int tokens[] = {ttAssignment, ttOpenParanthesis};
		Error(ExpectedOneOf(tokens, 2).AddressOf(), &t);
	}

	if( isSyntaxError || errorWhileParsing )
		return -1;

	return 0;
}

asCScriptNode *asCParser::SuperficiallyParseGlobalVarInit()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snAssignment);

	sToken t;
	GetToken(&t);
	node->UpdateSourcePos(t.pos, t.length);

	if( t.type == ttAssignment )
	{
		GetToken(&t);
		if( t.type == ttStartStatementBlock )
		{
			// Find the end of the initialization list
			int indent = 1;
			while( indent )
			{
				GetToken(&t);
				if( t.type == ttStartStatementBlock )
					indent++;
				else if( t.type == ttEndStatementBlock )
					indent--;
				else if( t.type == ttEnd )
				{
					Error(TXT_UNEXPECTED_END_OF_FILE, &t);
					break;
				}
			}
		}
		else
		{
			// Find the end of the expression
			int indent = 0;
			while( indent || (t.type != ttListSeparator && t.type != ttEndStatement && t.type != ttEndStatementBlock) )
			{
				if( t.type == ttOpenParanthesis )
					indent++;
				else if( t.type == ttCloseParanthesis )
					indent--;
				else if( t.type == ttEnd )
				{
					Error(TXT_UNEXPECTED_END_OF_FILE, &t);
					break;
				}
				GetToken(&t);
			}

			// Rewind so that the next token read is the list separator, end statement, or end statement block
			RewindTo(&t);
		}
	}
	else if( t.type == ttOpenParanthesis )
	{
		// Find the end of the argument list
		int indent = 1;
		while( indent )
		{
			GetToken(&t);
			if( t.type == ttOpenParanthesis )
				indent++;
			else if( t.type == ttCloseParanthesis )
				indent--;
			else if( t.type == ttEnd )
			{
				Error(TXT_UNEXPECTED_END_OF_FILE, &t);
				break;
			}
		}
	}
	else
	{
		int tokens[] = {ttAssignment, ttOpenParanthesis};
		Error(ExpectedOneOf(tokens, 2).AddressOf(), &t);
	}

	return node;
}

asCScriptNode *asCParser::SuperficiallyParseStatementBlock()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snStatementBlock);

	// This function will only superficially parse the statement block in order to find the end of it
	sToken t1;

	GetToken(&t1);
	if( t1.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	int level = 1;
	while( level > 0 && !isSyntaxError )
	{
		GetToken(&t1);
		if( t1.type == ttEndStatementBlock )
			level--;
		else if( t1.type == ttStartStatementBlock )
			level++;
		else if( t1.type == ttEnd )
			Error(TXT_UNEXPECTED_END_OF_FILE, &t1);
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	return node;
}

asCScriptNode *asCParser::ParseStatementBlock()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snStatementBlock);

	sToken t1;

	GetToken(&t1);
	if( t1.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	for(;;)
	{
		while( !isSyntaxError )
		{
			GetToken(&t1);
			if( t1.type == ttEndStatementBlock )
			{
				node->UpdateSourcePos(t1.pos, t1.length);

				// Statement block is finished
				return node;
			}
			else
			{
				RewindTo(&t1);

				if( IsVarDecl() )
					node->AddChildLast(ParseDeclaration());
				else
					node->AddChildLast(ParseStatement());
			}
		}

		if( isSyntaxError )
		{
			// Search for either ';', '{', '}', or end
			GetToken(&t1);
			while( t1.type != ttEndStatement && t1.type != ttEnd &&
				   t1.type != ttStartStatementBlock && t1.type != ttEndStatementBlock )
			{
				GetToken(&t1);
			}

			// Skip this statement block
			if( t1.type == ttStartStatementBlock )
			{
				// Find the end of the block and skip nested blocks
				int level = 1;
				while( level > 0 )
				{
					GetToken(&t1);
					if( t1.type == ttStartStatementBlock ) level++;
					if( t1.type == ttEndStatementBlock ) level--;
					if( t1.type == ttEnd ) break;
				}
			}
			else if( t1.type == ttEndStatementBlock )
			{
				RewindTo(&t1);
			}
			else if( t1.type == ttEnd )
			{
				Error(TXT_UNEXPECTED_END_OF_FILE, &t1);
				return node;
			}

			isSyntaxError = false;
		}
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseInitList()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snInitList);

	sToken t1;

	GetToken(&t1);
	if( t1.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t1);
		return node;
	}

	node->UpdateSourcePos(t1.pos, t1.length);

	GetToken(&t1);
	if( t1.type == ttEndStatementBlock )
	{
		node->UpdateSourcePos(t1.pos, t1.length);

		// Statement block is finished
		return node;
	}
	else
	{
		RewindTo(&t1);
		for(;;)
		{
			GetToken(&t1);
			if( t1.type == ttListSeparator )
			{
				// No expression 
				node->AddChildLast(new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined));

				GetToken(&t1);
				if( t1.type == ttEndStatementBlock )
				{
					// No expression
					node->AddChildLast(new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined));
					node->UpdateSourcePos(t1.pos, t1.length);
					return node;
				}
				RewindTo(&t1);
			}
			else if( t1.type == ttEndStatementBlock )
			{
				// No expression 
				node->AddChildLast(new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snUndefined));

				node->UpdateSourcePos(t1.pos, t1.length);

				// Statement block is finished
				return node;
			}
			else if( t1.type == ttStartStatementBlock )
			{
				RewindTo(&t1);
				node->AddChildLast(ParseInitList());
				if( isSyntaxError ) return node;

				GetToken(&t1);
				if( t1.type == ttListSeparator )
					continue;
				else if( t1.type == ttEndStatementBlock )
				{
					node->UpdateSourcePos(t1.pos, t1.length);

					// Statement block is finished
					return node;
				}
				else
				{
					Error(ExpectedTokens("}", ",").AddressOf(), &t1);
					return node;
				}
			}
			else
			{
				RewindTo(&t1);
				node->AddChildLast(ParseAssignment());
				if( isSyntaxError ) return node;


				GetToken(&t1);
				if( t1.type == ttListSeparator )
					continue;
				else if( t1.type == ttEndStatementBlock )
				{
					node->UpdateSourcePos(t1.pos, t1.length);

					// Statement block is finished
					return node;
				}
				else
				{
					Error(ExpectedTokens("}", ",").AddressOf(), &t1);
					return node;
				}
			}
		}
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseDeclaration()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDeclaration);

	// Parse data type
	node->AddChildLast(ParseType(true));
	if( isSyntaxError ) return node;

	sToken t;

	for(;;)
	{
		// Parse identifier
		node->AddChildLast(ParseIdentifier());
		if( isSyntaxError ) return node;

		// If next token is assignment, parse expression
		GetToken(&t);
		if( t.type == ttOpenParanthesis )
		{
			RewindTo(&t);
			node->AddChildLast(ParseArgList());
			if( isSyntaxError ) return node;
		}
		else if( t.type == ttAssignment )
		{
			GetToken(&t);
			RewindTo(&t);
			if( t.type == ttStartStatementBlock )
			{
				node->AddChildLast(ParseInitList());
				if( isSyntaxError ) return node;
			}
			else
			{
				node->AddChildLast(ParseAssignment());
				if( isSyntaxError ) return node;
			}
		}
		else
			RewindTo(&t);

		// continue if list separator, else terminate with end statement
		GetToken(&t);
		if( t.type == ttListSeparator )
			continue;
		else if( t.type == ttEndStatement )
		{
			node->UpdateSourcePos(t.pos, t.length);

			return node;
		}
		else
		{
			Error(ExpectedTokens(",", ";").AddressOf(), &t);
			return node;
		}
	}
	UNREACHABLE_RETURN;
}

asCScriptNode *asCParser::ParseStatement()
{
	sToken t1;

	GetToken(&t1);
	RewindTo(&t1);

	if( t1.type == ttIf )
		return ParseIf();
	else if( t1.type == ttFor )
		return ParseFor();
	else if( t1.type == ttWhile )
		return ParseWhile();
	else if( t1.type == ttReturn )
		return ParseReturn();
	else if( t1.type == ttStartStatementBlock )
		return ParseStatementBlock();
	else if( t1.type == ttBreak )
		return ParseBreak();
	else if( t1.type == ttContinue )
		return ParseContinue();
	else if( t1.type == ttDo )
		return ParseDoWhile();
	else if( t1.type == ttSwitch )
		return ParseSwitch();
	else
		return ParseExpressionStatement();
}

asCScriptNode *asCParser::ParseExpressionStatement()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExpressionStatement);

	sToken t;
	GetToken(&t);
	if( t.type == ttEndStatement )
	{
		node->UpdateSourcePos(t.pos, t.length);

		return node;
	}

	RewindTo(&t);

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttEndStatement )
	{
		Error(ExpectedToken(";").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseSwitch()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snSwitch);

	sToken t;
	GetToken(&t);
	if( t.type != ttSwitch )
	{
		Error(ExpectedToken("switch").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttCloseParanthesis )
	{
		Error(ExpectedToken(")").AddressOf(), &t);
		return node;
	}

	GetToken(&t);
	if( t.type != ttStartStatementBlock )
	{
		Error(ExpectedToken("{").AddressOf(), &t);
		return node;
	}
	
	while( !isSyntaxError )
	{
		GetToken(&t);
		
		if( t.type == ttEndStatementBlock || t.type == ttDefault)
			break;

		RewindTo(&t);

		if( t.type != ttCase )
		{
			Error(ExpectedToken("case").AddressOf(), &t);
			return node;
		}

		node->AddChildLast(ParseCase());
		if( isSyntaxError ) return node;
	}

	if( t.type == ttDefault)
	{
		RewindTo(&t);

		node->AddChildLast(ParseCase());
		if( isSyntaxError ) return node;

		GetToken(&t);
	}

	if( t.type != ttEndStatementBlock )
	{
		Error(ExpectedToken("}").AddressOf(), &t);
		return node;
	}

	return node;
}

asCScriptNode *asCParser::ParseCase()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snCase);

	sToken t;
	GetToken(&t);
	if( t.type != ttCase && t.type != ttDefault )
	{
		Error(ExpectedTokens("case", "default").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	if(t.type == ttCase)
	{
		node->AddChildLast(ParseExpression());
	}

	GetToken(&t);
	if( t.type != ttColon )
	{
		Error(ExpectedToken(":").AddressOf(), &t);
		return node;
	}

	// Parse statements until we find either of }, case, default, and break
	GetToken(&t);
	RewindTo(&t);
	while( t.type != ttCase && 
		   t.type != ttDefault && 
		   t.type != ttEndStatementBlock && 
		   t.type != ttBreak )
	{
		if( IsVarDecl() )
			// Variable declarations are not allowed, but we parse it anyway to give a good error message
			node->AddChildLast(ParseDeclaration());
		else
			node->AddChildLast(ParseStatement());
		if( isSyntaxError ) return node;

		GetToken(&t);
		RewindTo(&t);
	}

	// If the case was ended with a break statement, add it to the node
	if( t.type == ttBreak )
		node->AddChildLast(ParseBreak());

	return node;
}

asCScriptNode *asCParser::ParseIf()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snIf);

	sToken t;
	GetToken(&t);
	if( t.type != ttIf )
	{
		Error(ExpectedToken("if").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttCloseParanthesis )
	{
		Error(ExpectedToken(")").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseStatement());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttElse )
	{
		// No else statement return already
		RewindTo(&t);
		return node;
	}

	node->AddChildLast(ParseStatement());

	return node;
}

asCScriptNode *asCParser::ParseFor()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snFor);

	sToken t;
	GetToken(&t);
	if( t.type != ttFor )
	{
		Error(ExpectedToken("for").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t);
		return node;
	}

	if( IsVarDecl() )
		node->AddChildLast(ParseDeclaration());
	else
		node->AddChildLast(ParseExpressionStatement());
	if( isSyntaxError ) return node;

	node->AddChildLast(ParseExpressionStatement());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttCloseParanthesis )
	{
		RewindTo(&t);

		asCScriptNode *n = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snExpressionStatement);
		node->AddChildLast(n);
		n->AddChildLast(ParseAssignment());
		if( isSyntaxError ) return node;

		GetToken(&t);
		if( t.type != ttCloseParanthesis )
		{
			Error(ExpectedToken(")").AddressOf(), &t);
			return node;
		}
	}

	node->AddChildLast(ParseStatement());
	
	return node;
}

asCScriptNode *asCParser::ParseWhile()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snWhile);

	sToken t;
	GetToken(&t);
	if( t.type != ttWhile )
	{
		Error(ExpectedToken("while").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttCloseParanthesis )
	{
		Error(ExpectedToken(")").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseStatement());

	return node;
}

asCScriptNode *asCParser::ParseDoWhile()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snDoWhile);

	sToken t;
	GetToken(&t);
	if( t.type != ttDo )
	{
		Error(ExpectedToken("do").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	node->AddChildLast(ParseStatement());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttWhile )
	{
		Error(ExpectedToken("while").AddressOf(), &t);
		return node;
	}

	GetToken(&t);
	if( t.type != ttOpenParanthesis )
	{
		Error(ExpectedToken("(").AddressOf(), &t);
		return node;
	}

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttCloseParanthesis )
	{
		Error(ExpectedToken(")").AddressOf(), &t);
		return node;
	}

	GetToken(&t);
	if( t.type != ttEndStatement )
	{
		Error(ExpectedToken(";").AddressOf(), &t);
		return node;
	}
	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseReturn()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snReturn);

	sToken t;
	GetToken(&t);
	if( t.type != ttReturn )
	{
		Error(ExpectedToken("return").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type == ttEndStatement )
	{
		node->UpdateSourcePos(t.pos, t.length);
		return node;
	}

	RewindTo(&t);

	node->AddChildLast(ParseAssignment());
	if( isSyntaxError ) return node;

	GetToken(&t);
	if( t.type != ttEndStatement )
	{
		Error(ExpectedToken(";").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseBreak()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snBreak);

	sToken t;
	GetToken(&t);
	if( t.type != ttBreak )
	{
		Error(ExpectedToken("break").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttEndStatement )
		Error(ExpectedToken(";").AddressOf(), &t);

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

asCScriptNode *asCParser::ParseContinue()
{
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snContinue);

	sToken t;
	GetToken(&t);
	if( t.type != ttContinue )
	{
		Error(ExpectedToken("continue").AddressOf(), &t);
		return node;
	}

	node->UpdateSourcePos(t.pos, t.length);

	GetToken(&t);
	if( t.type != ttEndStatement )
		Error(ExpectedToken(";").AddressOf(), &t);

	node->UpdateSourcePos(t.pos, t.length);

	return node;
}

// TODO: typedef: Typedefs should accept complex types as well
asCScriptNode *asCParser::ParseTypedef()
{
	// Create the typedef node
	asCScriptNode *node = new(engine->memoryMgr.AllocScriptNode()) asCScriptNode(snTypedef);

	sToken	token;

	GetToken(&token);
	if( token.type != ttTypedef)
	{
		Error(ExpectedToken(asCTokenizer::GetDefinition(token.type)).AddressOf(), &token);
		return node;
	}
	
	node->SetToken(&token);
	node->UpdateSourcePos(token.pos, token.length);

	// Parse the base type
	GetToken(&token);
	RewindTo(&token);

	// Make sure it is a primitive type (except ttVoid)
	if( !IsRealType(token.type) || token.type == ttVoid )
	{
		asCString str;
		str.Format(TXT_UNEXPECTED_TOKEN_s, asCTokenizer::GetDefinition(token.type));
		Error(str.AddressOf(), &token);
		return node;
	}

	node->AddChildLast(ParseRealType());
	node->AddChildLast(ParseIdentifier());

	// Check for the end of the typedef
	GetToken(&token);
	if( token.type != ttEndStatement ) 
	{
		RewindTo(&token);
		Error(ExpectedToken(asCTokenizer::GetDefinition(token.type)).AddressOf(), &token);
	}

	return node;
}

void asCParser::ParseMethodOverrideBehaviors(asCScriptNode *funcNode)
{
	sToken t1;

	for( ; ; )
	{
		GetToken(&t1);
		RewindTo(&t1);

		if( IdentifierIs(t1, FINAL_TOKEN) || IdentifierIs(t1, OVERRIDE_TOKEN) )
			funcNode->AddChildLast(ParseIdentifier());
		else
			break;
	}
}
#endif

END_AS_NAMESPACE

