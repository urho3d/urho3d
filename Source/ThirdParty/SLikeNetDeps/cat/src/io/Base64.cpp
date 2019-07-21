/*
	Copyright (c) 2009 Christopher A. Taylor.  All rights reserved.

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

#include <cat/io/Base64.hpp>
using namespace std;
using namespace cat;


//// Conversion into Base64

static const char TO_BASE64[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};


int cat::GetBase64LengthFromBinaryLength(int bytes)
{
	if (bytes <= 0) return 0;

	return ((bytes + 2) / 3) * 4;
}

int cat::WriteBase64(const void *buffer, int bytes, char *encoded_buffer, int encoded_bytes)
{
	int written_bytes = ((bytes + 2) / 3) * 4;

	if (bytes <= 0 || encoded_bytes < written_bytes)
		return 0;

	const u8 *data = reinterpret_cast<const u8*>( buffer );

	int ii, jj, end;
	for (ii = 0, jj = 0, end = bytes - 2; ii < end; ii += 3, jj += 4)
	{
		encoded_buffer[jj] = TO_BASE64[data[ii] >> 2];
		encoded_buffer[jj+1] = TO_BASE64[((data[ii] << 4) | (data[ii+1] >> 4)) & 0x3f];
		encoded_buffer[jj+2] = TO_BASE64[((data[ii+1] << 2) | (data[ii+2] >> 6)) & 0x3f];
		encoded_buffer[jj+3] = TO_BASE64[data[ii+2] & 0x3f];
	}

	switch (ii - end)
	{
	default:
	case 2: // Nothing to write
		break;

	case 1: // Need to write final 1 byte
		encoded_buffer[jj] = TO_BASE64[data[bytes-1] >> 2];
		encoded_buffer[jj+1] = TO_BASE64[(data[bytes-1] << 4) & 0x3f];
		encoded_buffer[jj+2] = '=';
		encoded_buffer[jj+3] = '=';
		break;

	case 0: // Need to write final 2 bytes
		encoded_buffer[jj] = TO_BASE64[data[bytes-2] >> 2];
		encoded_buffer[jj+1] = TO_BASE64[((data[bytes-2] << 4) | (data[bytes-1] >> 4)) & 0x3f];
		encoded_buffer[jj+2] = TO_BASE64[(data[bytes-1] << 2) & 0x3f];
		encoded_buffer[jj+3] = '=';
		break;
	}

	return written_bytes;
}

// This version writes a C string null-terminator
int cat::WriteBase64Str(const void *buffer, int bytes, char *encoded_buffer, int encoded_bytes)
{
	int written = WriteBase64(buffer, bytes, encoded_buffer, encoded_bytes - 1);

	encoded_buffer[written] = '\0';

	return written;
}

int cat::WriteBase64(const void *buffer, int bytes, ostream &output)
{
	if (bytes <= 0) return 0;

	const u8 *data = reinterpret_cast<const u8*>( buffer );

	int ii, end;
	for (ii = 0, end = bytes - 2; ii < end; ii += 3)
	{
		output << TO_BASE64[data[ii] >> 2];
		output << TO_BASE64[((data[ii] << 4) | (data[ii+1] >> 4)) & 0x3f];
		output << TO_BASE64[((data[ii+1] << 2) | (data[ii+2] >> 6)) & 0x3f];
		output << TO_BASE64[data[ii+2] & 0x3f];
	}

	switch (ii - end)
	{
	default:
	case 2: // Nothing to write
		break;

	case 1: // Need to write final 1 byte
		output << TO_BASE64[data[bytes-1] >> 2];
		output << TO_BASE64[(data[bytes-1] << 4) & 0x3f];
		output << "==";
		break;

	case 0: // Need to write final 2 bytes
		output << TO_BASE64[data[bytes-2] >> 2];
		output << TO_BASE64[((data[bytes-2] << 4) | (data[bytes-1] >> 4)) & 0x3f];
		output << TO_BASE64[(data[bytes-1] << 2) & 0x3f];
		output << '=';
		break;
	}

	return ((bytes + 2) / 3) * 4;
}


//// Conversion from Base64

static const u8 DC = 0;

static const u8 FROM_BASE64[256] = {
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // 0-15
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // 16-31
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, 62, DC, DC, DC, 63, // 32-47
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, DC, DC, DC, DC, DC, DC, // 48-63
	DC, 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11, 12, 13, 14, // 64-79
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, DC, DC, DC, DC, DC, // 80-95
	DC, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, // 96-111
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, DC, DC, DC, DC, DC, // 112-127
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // 128-
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // Extended
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // ASCII
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // Extended
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // ASCII
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // Extended
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, // ASCII
	DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC, DC
};


int cat::GetBinaryLengthFromBase64Length(const char *encoded_buffer, int bytes)
{
	if (bytes <= 0) return 0;

	while (bytes >= 1 && encoded_buffer[bytes-1] == '=')
		--bytes;

	return (bytes * 3) / 4;
}

int cat::ReadBase64(const char *encoded_buffer, int encoded_bytes, void *decoded_buffer, int decoded_bytes)
{
	// Skip '=' characters at the end
	while (encoded_bytes >= 1 && encoded_buffer[encoded_bytes-1] == '=')
		--encoded_bytes;

	if (encoded_bytes <= 0 || decoded_bytes <= 0 ||
		decoded_bytes < (encoded_bytes * 3) / 4)
	{
		return 0;
	}

	const u8 *from = reinterpret_cast<const u8*>( encoded_buffer );
	u8 *to = reinterpret_cast<u8*>( decoded_buffer );

	u8 a, b, c, d;

	int ii, jj, end;
	for (ii = 0, jj = 0, end = encoded_bytes - 3; ii < end; ii += 4, jj += 3)
	{
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];
		c = FROM_BASE64[from[ii+2]];
		d = FROM_BASE64[from[ii+3]];

		to[jj] = (a << 2) | (b >> 4);
		to[jj+1] = (b << 4) | (c >> 2);
		to[jj+2] = (c << 6) | d;
	}

	switch (encoded_bytes & 3)
	{
	case 3: // 3 characters left
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];
		c = FROM_BASE64[from[ii+2]];

		to[jj] = (a << 2) | (b >> 4);
		to[jj+1] = (b << 4) | (c >> 2);
		return jj+2;

	case 2: // 2 characters left
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];

		to[jj] = (a << 2) | (b >> 4);
		return jj+1;
	}

	return jj;
}

int cat::ReadBase64(const char *encoded_buffer, int encoded_bytes, std::ostream &output)
{
	// Skip '=' characters at the end
	while (encoded_bytes >= 1 && encoded_buffer[encoded_bytes-1] == '=')
		--encoded_bytes;

	if (encoded_bytes <= 0) return 0;

	const u8 *from = reinterpret_cast<const u8*>( encoded_buffer );

	u8 a, b, c, d;

	int ii, end;
	for (ii = 0, end = encoded_bytes - 3; ii < end; ii += 4)
	{
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];
		c = FROM_BASE64[from[ii+2]];
		d = FROM_BASE64[from[ii+3]];

		output << (u8)((a << 2) | (b >> 4));
		output << (u8)((b << 4) | (c >> 2));
		output << (u8)((c << 6) | d);
	}

	switch (encoded_bytes & 3)
	{
	case 3: // 3 characters left
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];
		c = FROM_BASE64[from[ii+2]];

		output << (u8)((a << 2) | (b >> 4));
		output << (u8)((b << 4) | (c >> 2));
		break;

	case 2: // 2 characters left
		a = FROM_BASE64[from[ii]];
		b = FROM_BASE64[from[ii+1]];

		output << (u8)((a << 2) | (b >> 4));
		break;
	}

	return (encoded_bytes * 3) / 4;
}
