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
// as_tokenizer.cpp
//
// This class identifies tokens from the script code
//

#include "as_config.h"
#include "as_scriptengine.h"
#include "as_tokenizer.h"
#include "as_tokendef.h"

#if !defined(AS_NO_MEMORY_H)
#include <memory.h>
#endif
#include <string.h> // strcmp()

BEGIN_AS_NAMESPACE

asCTokenizer::asCTokenizer()
{
	engine = 0;

	// Initialize the keyword map
	for( asUINT n = 0; n < numTokenWords; n++ )
	{
		if( (tokenWords[n].word[0] >= 'a' && tokenWords[n].word[0] <= 'z') ||
			(tokenWords[n].word[0] >= 'A' && tokenWords[n].word[0] <= 'Z') )
			alphaKeywordMap.Insert(asCStringPointer(tokenWords[n].word, strlen(tokenWords[n].word)), tokenWords[n].tokenType);
		else
			nonAlphaKeywordMap.Insert(asCStringPointer(tokenWords[n].word, strlen(tokenWords[n].word)), tokenWords[n].tokenType);
	}
}

asCTokenizer::~asCTokenizer()
{
}

// static
const char *asCTokenizer::GetDefinition(int tokenType)
{
	if( tokenType == ttUnrecognizedToken			) return "<unrecognized token>";
	if( tokenType == ttEnd							) return "<end of file>";
	if( tokenType == ttWhiteSpace					) return "<white space>";
	if( tokenType == ttOnelineComment				) return "<one line comment>";
	if( tokenType == ttMultilineComment				) return "<multiple lines comment>";
	if( tokenType == ttIdentifier					) return "<identifier>";
	if( tokenType == ttIntConstant					) return "<integer constant>";
	if( tokenType == ttFloatConstant				) return "<float constant>";
	if( tokenType == ttDoubleConstant				) return "<double constant>";
	if( tokenType == ttStringConstant				) return "<string constant>";
	if( tokenType == ttMultilineStringConstant      ) return "<multiline string constant>";
	if( tokenType == ttNonTerminatedStringConstant	) return "<nonterminated string constant>";
	if( tokenType == ttBitsConstant					) return "<bits constant>";
	if( tokenType == ttHeredocStringConstant		) return "<heredoc string constant>";

	for( asUINT n = 0; n < numTokenWords; n++ )
		if( tokenWords[n].tokenType == tokenType )
			return tokenWords[n].word;

	return 0;
}

eTokenType asCTokenizer::GetToken(const char *source, size_t sourceLength, size_t *tokenLength, asETokenClass *tc) const
{
	asASSERT(source != 0);
	asASSERT(tokenLength != 0);

	eTokenType tokenType;
	size_t     tlen;
	asETokenClass t = ParseToken(source, sourceLength, tlen, tokenType);
	if( tc          ) *tc          = t;
	if( tokenLength ) *tokenLength = tlen;

	return tokenType;
}

asETokenClass asCTokenizer::ParseToken(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	if( IsWhiteSpace(source, sourceLength, tokenLength, tokenType) ) return asTC_WHITESPACE;
	if( IsComment(source, sourceLength, tokenLength, tokenType)    ) return asTC_COMMENT;
	if( IsConstant(source, sourceLength, tokenLength, tokenType)   ) return asTC_VALUE;
	if( IsIdentifier(source, sourceLength, tokenLength, tokenType) ) return asTC_IDENTIFIER;
	if( IsKeyWord(source, sourceLength, tokenLength, tokenType)    ) return asTC_KEYWORD;

	// If none of the above this is an unrecognized token
	// We can find the length of the token by advancing
	// one step and trying to identify a token there
	tokenType   = ttUnrecognizedToken;
	tokenLength = 1;

	return asTC_UNKNOWN;
}

bool asCTokenizer::IsWhiteSpace(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	// Treat UTF8 byte-order-mark (EF BB BF) as whitespace
	if( sourceLength >= 3 && 
		asBYTE(source[0]) == 0xEFu &&
		asBYTE(source[1]) == 0xBBu &&
		asBYTE(source[2]) == 0xBFu )
	{
		tokenType   = ttWhiteSpace;
		tokenLength = 3;
		return true;
	}

	// Group all other white space characters into one
	size_t n;
	int numWsChars = (int)strlen(whiteSpace);
	for( n = 0; n < sourceLength; n++ )
	{
		bool isWhiteSpace = false;
		for( int w = 0; w < numWsChars; w++ )
		{
			if( source[n] == whiteSpace[w] )
			{
				isWhiteSpace = true;
				break;
			}
		}
		if( !isWhiteSpace )	break;
	}

	if( n > 0 )
	{
		tokenType   = ttWhiteSpace;
		tokenLength = n;
		return true;
	}

	return false;
}

bool asCTokenizer::IsComment(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	if( sourceLength < 2 )
		return false;

	if( source[0] != '/' )
		return false;

	if( source[1] == '/' )
	{
		// One-line comment

		// Find the length
		size_t n;
		for( n = 2; n < sourceLength; n++ )
		{
			if( source[n] == '\n' )
				break;
		}

		tokenType   = ttOnelineComment;
		tokenLength = n+1;

		return true;
	}

	if( source[1] == '*' )
	{
		// Multi-line comment

		// Find the length
		size_t n;
		for( n = 2; n < sourceLength-1; )
		{
			if( source[n++] == '*' && source[n] == '/' )
				break;
		}

		tokenType   = ttMultilineComment;
		tokenLength = n+1;

		return true;
	}

	return false;
}

bool asCTokenizer::IsConstant(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	// Starting with number
	if( (source[0] >= '0' && source[0] <= '9') || (source[0] == '.' && sourceLength > 1 && source[1] >= '0' && source[1] <= '9') )
	{
		// Is it a hexadecimal number?
		if( source[0] == '0' && sourceLength > 1 && (source[1] == 'x' || source[1] == 'X') )
		{
			size_t n;
			for( n = 2; n < sourceLength; n++ )
			{
				if( !(source[n] >= '0' && source[n] <= '9') &&
					!(source[n] >= 'a' && source[n] <= 'f') &&
					!(source[n] >= 'A' && source[n] <= 'F') )
					break;
			}

			tokenType   = ttBitsConstant;
			tokenLength = n;
			return true;
		}

		size_t n;
		for( n = 0; n < sourceLength; n++ )
		{
			if( source[n] < '0' || source[n] > '9' )
				break;
		}

		if( n < sourceLength && source[n] == '.' )
		{
			n++;
			for( ; n < sourceLength; n++ )
			{
				if( source[n] < '0' || source[n] > '9' )
					break;
			}

			if( n < sourceLength && (source[n] == 'e' || source[n] == 'E') )
			{
				n++;
				if( n < sourceLength && (source[n] == '-' || source[n] == '+') )
					n++;

				for( ; n < sourceLength; n++ )
				{
					if( source[n] < '0' || source[n] > '9' )
						break;
				}
			}

			if( n < sourceLength && (source[n] == 'f' || source[n] == 'F') )
			{
				tokenType   = ttFloatConstant;
				tokenLength = n + 1;
			}
			else
			{
#ifdef AS_USE_DOUBLE_AS_FLOAT
				tokenType   = ttFloatConstant;
#else
				tokenType   = ttDoubleConstant;
#endif
				tokenLength = n;
			}
			return true;
		}

		tokenType   = ttIntConstant;
		tokenLength = n;
		return true;
	}

	// String constant between double or single quotes
	if( source[0] == '"' || source[0] == '\'' )
	{
		// Is it a normal string constant or a heredoc string constant?
		if( sourceLength >= 6 && source[0] == '"' && source[1] == '"' && source[2] == '"' )
		{
			// Heredoc string constant (spans multiple lines, no escape sequences)

			// Find the length
			size_t n;
			for( n = 3; n < sourceLength-2; n++ )
			{
				if( source[n] == '"' && source[n+1] == '"' && source[n+2] == '"' )
					break;
			}

			tokenType   = ttHeredocStringConstant;
			tokenLength = n+3;
		}
		else
		{
			// Normal string constant
			tokenType = ttStringConstant;
			char quote = source[0];
			bool evenSlashes = true;
			size_t n;
			for( n = 1; n < sourceLength; n++ )
			{
#ifdef AS_DOUBLEBYTE_CHARSET
				// Double-byte characters are only allowed for ASCII
				if( (source[n] & 0x80) && engine->ep.scanner == 0 )
				{
					// This is a leading character in a double byte character, 
					// include both in the string and continue processing.
					n++;
					continue;
				}
#endif

				if( source[n] == '\n' ) 
					tokenType = ttMultilineStringConstant;
				if( source[n] == quote && evenSlashes )
				{
					tokenLength = n+1;
					return true;
				}
				if( source[n] == '\\' ) evenSlashes = !evenSlashes; else evenSlashes = true;
			}

			tokenType   = ttNonTerminatedStringConstant;
			tokenLength = n;
		}

		return true;
	}

	return false;
}

bool asCTokenizer::IsIdentifier(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	// Starting with letter or underscore
	if( (source[0] >= 'a' && source[0] <= 'z') ||
		(source[0] >= 'A' && source[0] <= 'Z') ||
		source[0] == '_' )
	{
		tokenType   = ttIdentifier;
		tokenLength = 1;

		for( size_t n = 1; n < sourceLength; n++ )
		{
			if( (source[n] >= 'a' && source[n] <= 'z') ||
				(source[n] >= 'A' && source[n] <= 'Z') ||
				(source[n] >= '0' && source[n] <= '9') ||
				source[n] == '_' )
				tokenLength++;
			else
				break;
		}

		// Make sure the identifier isn't a reserved keyword
		if( alphaKeywordMap.MoveTo(0, asCStringPointer(source, tokenLength)) )
			return false;

		return true;
	}

	return false;
}

bool asCTokenizer::IsKeyWord(const char *source, size_t sourceLength, size_t &tokenLength, eTokenType &tokenType) const
{
	// TODO: optimize: This can probably be optimized further with a specialized algorithm
	//                 As most keywords are shorter, then we should start from the shortest
	//                 to the longest. Only for some of the keywords is it necessary to look
	//                 for a longer part, e.g. ! and !is.
	//
	//                 We can use a map that separates the tokens based on the first character.
	//                 The highest number of possible tokens would then be 11 for the letter 'i'.

	// Choose the best map
	const asCMap<asCStringPointer,eTokenType> *map;
	int maxLength;

	if( (source[0] >= 'a' && source[0] <= 'z') ||
		(source[0] >= 'A' && source[0] <= 'Z') )
	{
		map = &alphaKeywordMap;
		// 'interface' is the longest alpha keyword
		maxLength = sourceLength > 9 ? 9 : int(sourceLength);
	}
	else
	{
		map = &nonAlphaKeywordMap;
		// '>>>=' is the longest non-alpha keyword
		maxLength = sourceLength > 4 ? 4 : int(sourceLength);
	}

	// Find the longest keyword that matches the start of the source string
	while( maxLength > 0 )
	{
		asSMapNode<asCStringPointer, eTokenType> *cursor;
		if( map->MoveTo(&cursor, asCStringPointer(source, maxLength)) )
		{
			// Tokens that end with a character that can be part of an 
			// identifier require an extra verification to guarantee that 
			// we don't split an identifier token, e.g. the "!is" token 
			// and the tokens "!" and "isTrue" in the "!isTrue" expression.
			if( maxLength < int(sourceLength) &&
				((source[maxLength-1] >= 'a' && source[maxLength-1] <= 'z') ||
				 (source[maxLength-1] >= 'A' && source[maxLength-1] <= 'Z')) &&
				((source[maxLength] >= 'a' && source[maxLength] <= 'z') ||
				 (source[maxLength] >= 'A' && source[maxLength] <= 'Z') ||
				 (source[maxLength] >= '0' && source[maxLength] <= '9') ||
				 (source[maxLength] == '_')) )
			{
				// The token doesn't really match, even though 
				// the start of the source matches the token
				maxLength--;
				continue;
			}

			tokenType   = cursor->value;
			tokenLength = maxLength;
			return true;
		}
		maxLength--;
	}

	return false;	
}

END_AS_NAMESPACE

