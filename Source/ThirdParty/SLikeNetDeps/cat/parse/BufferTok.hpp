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

#ifndef CAT_BUFFER_TOK_HPP
#define CAT_BUFFER_TOK_HPP

#include <cat/Platform.hpp>

namespace cat {


/*
    MyBuf = "   123     5 :  6  "

    BufferTok bt(MyBuf, 256);

    int a, b, c; 
    bt() >> a; // empty delimiter means white space and newlines
    bt(':') >> b >> c;
    if (!bt) // out of buffer space
*/

// Tokenize a buffer
class BufferTok
{
    const char *buffer;
    int len;

    char delimiter;
    bool newline;

    u32 readNext(char *token, u32 tokenBufferSize);

public:
    BufferTok(const char *buffer, int len);

    // Returns true when the buffer is empty
    inline bool operator!() { return len <= 0; }

    // Returns true when the buffer extraction is stuck on a new line
    // Use operator[] to reset this flag
    inline bool onNewline() { return newline; }

    /*
     * operator(char)
     * Set the delimiter character 
     * 
     * This character is used to find the end of the current token
     * Newlines are always a delimiter
     */
    BufferTok &operator()(char ch = 0);

    /*
     * Same as operator(), see above
     * 
     * Also resets the newline() flag, so that data can start being
     * read from the next line.  If newline() wasn't set, it searches
     * for the next line to start reading.
     */
    BufferTok &operator[](char ch);

    /*
     * operator>>
     * Extract a token
     * 
     * Strips whitespace and the end-of-token delimiter
     * Newlines are always a delimiter
     * 
     * After the tokenizer encounters a newline, it will continue
     * returning no results with newline() flag set, until the
     * delimiter is reset with [], so incomplete lines don't wrap.
     */
    BufferTok &operator>>(int &n);
    BufferTok &operator>>(char *n); // buffer must have at least 256 characters
};


} // namespace cat

#endif // CAT_BUFFER_TOK_HPP
