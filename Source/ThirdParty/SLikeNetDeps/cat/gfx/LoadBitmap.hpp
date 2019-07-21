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

#ifndef LOAD_BITMAP_HPP
#define LOAD_BITMAP_HPP

#include <cat/Platform.hpp>

namespace cat {


/*
	LoadBitmap() loads a memory-mapped bitmap or a file from disk into RGBA format,
	meaning the first byte of every pixel is Red, then Green, Blue, and Alpha.
	The output data is useful for creating an OpenGL texture using GL_RGBA format.
	The output width and height will be powers of two.

	Parameters:
		file, bytes : Memory-mapped file pointer and number of bytes in the file
		path : Alternatively, the path to the file to load
		width, height : The dimensions of the loaded file, in pixels

	Returns: Zero on error, or a pointer to the rasterized RGBA pixels.

	Free the allocated memory using Aligned::Delete(a);
*/
void *LoadBitmap(void *file, u32 bytes, u32 &width, u32 &height);
void *LoadBitmap(const char *path, u32 &width, u32 &height);


class BMPTokenizer
{
	u8 trans_red, trans_green, trans_blue;

	bool requirePOTS; // Require Power-of-Two Size

	void rasterizeImage(u8 *image);
	void onImage(u32 *image, u32 newWidth, u32 newHeight);

public:
	BMPTokenizer();
	~BMPTokenizer();

public:
	bool LoadFile(const char *path);
};


} // namespace cat

#endif // LOAD_BITMAP_HPP
