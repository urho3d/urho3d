/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CAT_STRINGS_HPP
#define CAT_STRINGS_HPP

/*
	These are ANSI C String function that do not work with UNICODE, UTF-8, etc.
*/

#include <cat/Platform.hpp>

#if defined(CAT_COMPILER_MSVC)
#include <string.h> // _stricmp
#elif defined(CAT_COMPILER_GCC)
#include <strings.h> // strcasecmp
#endif

namespace cat {


// Convert from signed 32-bit number to string (up to 12 bytes including '\0')
int DecToString(s32 x, char *outs);


// iStrEqual(): Returns true if strings match.  Case-insensitive

#if defined(CAT_COMPILER_MSVC)

	CAT_INLINE bool iStrEqual(const char *A, const char *B)
	{
		return _stricmp(A, B) == 0;
	}

#elif defined(CAT_COMPILER_GCC)

	CAT_INLINE bool iStrEqual(const char *A, const char *B)
	{
		return strcasecmp(A, B) == 0;
	}

#else

# define CAT_UNKNOWN_BUILTIN_ISTRCMP
	bool iStrEqual(const char *A, const char *B);

#endif


// Get length of string that has a maximum length (potentially no trailing nul)
u32 GetFixedStrLen(const char *str, u32 max_len);


// Set a fixed string buffer (zero-padded) from a variable-length string,
// both either zero or length-terminated.  Returns length of copied string
u32 SetFixedStr(char *dest, u32 dest_len, const char *src, u32 src_max_len);


// Returns true if buffer contains any non-zero bytes
bool IsZeroFixedBuffer(const void *buffer, u32 bytes);


// Replaces all similar-looking glyphs with a common character
char DesimilarizeCharacter(char ch);

// Replaces all similar-looking glyphs with common characters while copying a string
void CopyDesimilarizeString(const char *from, char *to);

// Replaces all similar-looking glyphs with common characters in a fixed string
u32 DesimilarizeFixedString(char *str, u32 max_len);

// Copies the input string to an output string replacing lowercase letters with their uppercase equivalents
void CopyToUppercaseString(const char *from, char *to);

// Copies the input string to an output string replacing uppercase letters with their lowercase equivalents
void CopyToLowercaseString(const char *from, char *to);


} // namespace cat

#endif // CAT_STRINGS_HPP
