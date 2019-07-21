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

#ifndef CAT_BUFFER_STREAM_HPP
#define CAT_BUFFER_STREAM_HPP

#include <cat/Platform.hpp>
#include <cat/port/EndianNeutral.hpp>

namespace cat {


/*
	BufferStream

	Extremely light-weight wrapper for a buffer data insertion and extraction.

	Performs automatic endian conversion into and out of the buffer (sometimes).

	Performs no checking for buffer overruns.
	This class does not add any security to your code; it just makes it shorter.
	Use at your peril.
*/
class BufferStream
{
protected:
	u8 *_buffer;

public:
	CAT_INLINE BufferStream(u8 *buffer) { _buffer = buffer; }
	CAT_INLINE BufferStream &operator=(u8 *buffer) { _buffer = buffer; }

	CAT_INLINE u32 GetOffset(void *buffer) { return (u32)(_buffer - reinterpret_cast<u8*>( buffer )); }

public:
	// Auto-cast to u8* or char*
	CAT_INLINE operator u8*() { return _buffer; }
	CAT_INLINE char *c_str() { return reinterpret_cast<char*>( _buffer ); }

	CAT_INLINE BufferStream &operator++() { _buffer++; return *this; }
	CAT_INLINE BufferStream &operator+=(int skip_bytes) { _buffer += skip_bytes; return *this; }

public:
	// Insertion
	CAT_INLINE BufferStream &operator<<(s8 data) { *_buffer++ = (u8)data; return *this; }
	CAT_INLINE BufferStream &operator<<(s16 data) { *(u16*)_buffer = getLE16((u16)data); _buffer += 2; return *this; }
	CAT_INLINE BufferStream &operator<<(s32 data) { *(u32*)_buffer = getLE32((u32)data); _buffer += 4; return *this; }
	CAT_INLINE BufferStream &operator<<(s64 data) { *(u64*)_buffer = getLE64((u64)data); _buffer += 8; return *this; }

	CAT_INLINE BufferStream &operator<<(u8 data) { *_buffer++ = data; return *this; }
	CAT_INLINE BufferStream &operator<<(u16 data) { *(u16*)_buffer = getLE16(data); _buffer += 2; return *this; }
	CAT_INLINE BufferStream &operator<<(u32 data) { *(u32*)_buffer = getLE32(data); _buffer += 4; return *this; }
	CAT_INLINE BufferStream &operator<<(u64 data) { *(u64*)_buffer = getLE64(data); _buffer += 8; return *this; }

	CAT_INLINE void write(const void *data, u32 bytes)
	{
		memcpy(_buffer, data, bytes);
		_buffer += bytes;
	}

	template<class T>
	CAT_INLINE BufferStream &operator<<(const T &data) { write(&data, sizeof(T)); return *this; }

public:
	// Extraction
	CAT_INLINE BufferStream &operator>>(s8 &data) { data = (s8)*_buffer++; return *this; }
	CAT_INLINE BufferStream &operator>>(s16 &data) { data = (s16)getLE16(*(u16*)_buffer); _buffer += 2; return *this; }
	CAT_INLINE BufferStream &operator>>(s32 &data) { data = (s32)getLE32(*(u32*)_buffer); _buffer += 4; return *this; }
	CAT_INLINE BufferStream &operator>>(s64 &data) { data = (s64)getLE64(*(u64*)_buffer); _buffer += 8; return *this; }

	CAT_INLINE BufferStream &operator>>(u8 &data) { data = *_buffer++; return *this; }
	CAT_INLINE BufferStream &operator>>(u16 &data) { data = getLE16(*(u16*)_buffer); _buffer += 2; return *this; }
	CAT_INLINE BufferStream &operator>>(u32 &data) { data = getLE32(*(u32*)_buffer); _buffer += 4; return *this; }
	CAT_INLINE BufferStream &operator>>(u64 &data) { data = getLE64(*(u64*)_buffer); _buffer += 8; return *this; }

	CAT_INLINE void read(void *data, u32 bytes)
	{
		memcpy(data, _buffer, bytes);
		_buffer += bytes;
	}

	template<class T>
	CAT_INLINE BufferStream &operator>>(T &data) { read(&data, sizeof(T)); return *this; }
};


} // namespace cat

#endif // CAT_BUFFER_STREAM_HPP
