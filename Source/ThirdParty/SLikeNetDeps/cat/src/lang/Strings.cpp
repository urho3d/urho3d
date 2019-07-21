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

#include <cat/lang/Strings.hpp>
#include <cctype> // tolower
using namespace cat;

// Convert from signed 32-bit number to string (up to 12 bytes including '\0')
int cat::DecToString(s32 x, char *outs)
{
	char *out = outs;

	if (x < 0)
	{
		*out++ = '-';
		x = -x;
	}

	// max = 4294967295
	u32 r, d, n = (u32)x;

	r = (n >= 1000000000) ? 9 : (n >= 100000000) ? 8 : (n >= 10000000) ? 7 : 
		(n >= 1000000) ? 6 : (n >= 100000) ? 5 : (n >= 10000) ? 4 : 
		(n >= 1000) ? 3 : (n >= 100) ? 2 : (n >= 10) ? 1 : 0;

	switch (r)
	{
	case 9:
		d = n / 1000000000;
		n %= 1000000000;
		*out++ = '0' + (char)d;
	case 8:
		d = n / 100000000;
		n %= 100000000;
		*out++ = '0' + (char)d;
	case 7:
		d = n / 10000000;
		n %= 10000000;
		*out++ = '0' + (char)d;
	case 6:
		d = n / 1000000;
		n %= 1000000;
		*out++ = '0' + (char)d;
	case 5:
		d = n / 100000;
		n %= 100000;
		*out++ = '0' + (char)d;
	case 4:
		d = n / 10000;
		n %= 10000;
		*out++ = '0' + (char)d;
	case 3:
		d = n / 1000;
		n %= 1000;
		*out++ = '0' + (char)d;
	case 2:
		d = n / 100;
		n %= 100;
		*out++ = '0' + (char)d;
	case 1:
		d = n / 10;
		n %= 10;
		*out++ = '0' + (char)d;
	default:
		*out++ = '0' + (char)n;
	}

	return (int)(out - outs);
}

#if defined(CAT_UNKNOWN_BUILTIN_ISTRCMP)

bool cat::iStrEqual(const char *A, const char *B)
{
	// Forever,
	for (;;)
	{
		// Grab next character from each string
		char a = *A++;
		char b = *B++;

		// Convert to lower case if needed
		if (a >= 'A' && a <= 'Z') a += 'a' - 'Z';
		if (b >= 'A' && b <= 'Z') b += 'a' - 'Z';

		// If characters do not match, return false
		if (a != b) return false;

		// If both characters are '\0', we have reached
		// the end and no characters were different
		if (a == '\0') return true;
	}
}

#endif // CAT_UNKNOWN_BUILTIN_ISTRCMP


// Get length of string that has a maximum length (potentially no trailing nul)
u32 cat::GetFixedStrLen(const char *str, u32 max_len)
{
	for (u32 ii = 0; ii < max_len; ++ii)
		if (str[ii] == '\0')
			return ii;

	return max_len;
}


// Set a fixed string buffer (zero-padded) from a variable-length string,
// both either zero or length-terminated.  Returns length of copied string
u32 cat::SetFixedStr(char *dest, u32 dest_len, const char *src, u32 src_max_len)
{
	u32 ii;

	// Copy characters until source or destination buffer ends or encounter null
	for (ii = 0; ii < dest_len && ii < src_max_len; ++ii)
	{
		char ch = src[ii];

		if (ch == '\0')
			break;

		dest[ii] = ch;
	}

	u32 copied = ii;

	// Pad destination with null bytes
	// NOTE: Does not guarantee the destination is null-terminated
	for (; ii < dest_len; ++ii)
	{
		dest[ii] = '\0';
	}

	return copied;
}


// Returns true if buffer contains any non-zero bytes
bool cat::IsZeroFixedBuffer(const void *vbuffer, u32 bytes)
{
	const u8 *buffer = reinterpret_cast<const u8*>( vbuffer );

	for (u32 ii = 0; ii < bytes; ++ii)
		if (buffer[ii]) return false;

	return true;
}


// Replaces all similar-looking glyphs with a common character
char cat::DesimilarizeCharacter(char ch)
{
	ch = (char)std::toupper(ch);

	switch (ch)
	{
	case 'I':
	case 'L':
	case '1':
	case '|':
		return 'I';

	case 'O':
	case '0':
		return 'O';

	case 'T':
	case '+':
		return 'T';

	case '`':
	case '\'':
	case '"':
		return '`';

	case '8':
	case 'B':
		return 'B';

	case '.':
	case ',':
		return '.';

	case '6':
	case 'G':
		return 'G';

	case '2':
	case 'Z':
		return 'Z';

	case '~':
	case '-':
		return '~';

	case '\\':
	case '/':
		return '/';

	case ':':
	case ';':
		return ';';

	case 'N':
	case 'M':
		return 'N';
	}

	return ch;
}

// Replaces all similar-looking glyphs with common characters while copying a string
void cat::CopyDesimilarizeString(const char *from, char *to)
{
	char ch;

	while ((ch = *from++)) *to++ = DesimilarizeCharacter(ch);

	*to = '\0';
}

// Replaces all similar-looking glyphs with common characters in a fixed string
u32 cat::DesimilarizeFixedString(char *str, u32 max_len)
{
	for (u32 ii = 0; ii < max_len; ++ii)
	{
		if (str[ii] == '\0')
			return ii;

		str[ii] = DesimilarizeCharacter(str[ii]);
	}

	return max_len;
}

// Copies the input string to an output string replacing lowercase letters with their uppercase equivalents
void cat::CopyToUppercaseString(const char *from, char *to)
{
	char ch;

	while ((ch = *from++)) *to++ = (char)std::toupper(ch);

	*to = '\0';
}

// Copies the input string to an output string replacing uppercase letters with their lowercase equivalents
void cat::CopyToLowercaseString(const char *from, char *to)
{
	char ch;

	while ((ch = *from++)) *to++ = (char)std::tolower(ch);

	*to = '\0';
}
