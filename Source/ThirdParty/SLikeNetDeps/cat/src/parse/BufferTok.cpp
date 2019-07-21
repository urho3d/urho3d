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

#include <cat/parse/BufferTok.hpp>
using namespace cat;


BufferTok::BufferTok(const char *bufferi, int leni)
{
    buffer = bufferi;
    len = leni;
    delimiter = ' ';
    newline = true;
}

/*
 * operator(char)
 * Set the delimiter character 
 * 
 * This character is used to find the end of the current token
 * Newlines are always a delimiter
 */
BufferTok &BufferTok::operator()(char ch)
{
    delimiter = ch;
    return *this;
}

/*
 * Same as operator(), see above
 * 
 * Also resets the newline() flag, so that data can start being
 * read from the next line.  If newline() wasn't set, it searches
 * for the next line to start reading.
 */
BufferTok &BufferTok::operator[](char ch)
{
    delimiter = ch;
    if (!newline)
    {
        char last = 0;

        while (len)
        {
            ch = *buffer;

            if (ch == '\r' || ch == '\n')
            {
                if (newline && ch != last)
                {
                    ++buffer;
                    --len;
                    break;
                }

                newline = true;
                last = ch;

                ++buffer;
                --len;
            }
            else
            {
                if (newline) break;

                ++buffer;
                --len;
            }
        }
    }
    newline = false;
    return *this;
}

// Read more bytes from the buffer
u32 BufferTok::readNext(char *token, u32 tokenBufferSize)
{
    if (!len || newline)
    {
        *token = 0;
        return 0;
    }

    bool seenNonSpace = false;
    char ch, last = 0;
    u32 copied = 0;

    while (len)
    {
        ch = *buffer;

        if (newline)
        {
            if (ch != last && (ch == '\r' || ch == '\n'))
            {
                ++buffer;
                --len;
            }
            break;
        }

        if (ch == delimiter)
        {
            if (delimiter != ' ' || seenNonSpace)
            {
                ++buffer;
                --len;
                break;
            }
        }

        switch (ch)
        {
        case ' ':
            if (seenNonSpace && last != ' ')
            {
                if (copied < tokenBufferSize-1)
                    token[copied++] = ch;
                last = ch;
            }
            break;
        case '\r':
        case '\n':
            newline = true;
            last = ch;
            break;
        default:
            if ((u8)(ch - '!') < 94)
            {
                seenNonSpace = true;
                if (copied < tokenBufferSize-1)
                    token[copied++] = ch;
                last = ch;
            }
        }

        ++buffer;
        --len;
    }

    if (last == ' ') --copied;

    token[copied] = 0;

    return copied;
}

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
BufferTok &BufferTok::operator>>(int &n)
{
    char work[256];

    u32 copied = readNext(work, sizeof(work));

    n = copied ? atoi(work) : 0;

    return *this;
}

BufferTok &BufferTok::operator>>(char *n)
{
    readNext(n, 256);

    return *this;
}
