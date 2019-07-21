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

#ifndef CAT_BASE64_HPP
#define CAT_BASE64_HPP

#include <cat/Platform.hpp>
#include <ostream>

namespace cat {


// Write buffer to output stream in Base64 encoding
int GetBase64LengthFromBinaryLength(int bytes);

// Returns number of bytes written, or 0 for error
int WriteBase64(const void *buffer, int bytes, char *encoded_buffer, int encoded_bytes);
int WriteBase64Str(const void *buffer, int bytes, char *encoded_buffer, int encoded_bytes); // This version writes a null-terminator
int WriteBase64(const void *buffer, int bytes, std::ostream &output);

// Read buffer in Base64 encoding
int GetBinaryLengthFromBase64Length(const char *encoded_buffer, int bytes);

// Returns number of bytes read, or 0 for error
int ReadBase64(const char *encoded_buffer, int encoded_bytes, void *decoded_buffer, int decoded_bytes);
int ReadBase64(const char *encoded_buffer, int encoded_bytes, std::ostream &output);


} // namespace cat

#endif // CAT_BASE64_HPP
