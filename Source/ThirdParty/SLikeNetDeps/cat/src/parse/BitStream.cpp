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

#include <cat/parse/BitStream.hpp>
#include <cat/io/Logging.hpp>
#include <cat/math/BitMath.hpp>
using namespace cat;

#define BITSTREAM_CLEAR_EXTRANEOUS_BITS

static const int DOUBLE_BYTES = sizeof(double);
static const int DOUBLE_BITS = DOUBLE_BYTES * 8;

static const int FLOAT_BYTES = sizeof(float);
static const int FLOAT_BITS = FLOAT_BYTES * 8;

// minimum size of the buffer before reads will shrink it
static const int SHRINK_MINSIZE = 512;


//// ctors

BitStream::BitStream(u32 bytes, void *vbuffer)
{
    if (vbuffer)
    {
        fixed_buffer = true;
        buffer = (u8*)vbuffer;
        write_offset = bytes * 8;
    }
    else
    {
        fixed_buffer = false;
        buffer = bytes > 0 ? new u8[bytes] : 0;
        write_offset = 0;
    }

    read_underrun = false;
    buffer_bytes = bytes;
    read_offset = 0;
}

BitStream::~BitStream()
{
    if (!fixed_buffer && buffer)
        delete[] buffer;
}


//// miscellaneous

bool BitStream::underrun()
{
    bool b = read_underrun;
    read_underrun = false;
    return b;
}

void BitStream::skip(u32 bits)
{
    read_offset += bits;
    
    if (read_offset > write_offset)
    {
        read_offset = write_offset;
        read_underrun = true;
    }
}


//// shrink and grow

void BitStream::grow(u32 bits)
{
    // no need to grow until the space is used up
    if (write_offset + bits <= buffer_bytes * 8)
        return;

    u32 new_buffer_bytes = 1 << (BSR32(buffer_bytes + CAT_CEIL_UNIT(bits, 8)) + 1);

    u8 *new_buffer = new u8[new_buffer_bytes];
    if (!new_buffer) return;

    // copy old buffer contents to the new buffer
    if (buffer)
    {
        u32 read_start = read_offset / 8;
        u32 read_count = CAT_CEIL_UNIT(write_offset, 8) - read_start;

        memcpy(new_buffer, buffer + read_start, read_count);

        read_offset %= 8;
        write_offset -= read_start * 8;

        // abandon fixed buffer state and go dynamic if needed
        if (fixed_buffer)
            fixed_buffer = false;
        else
            delete[] buffer;
    }

    buffer = new_buffer;
    buffer_bytes = new_buffer_bytes;
}

void BitStream::shrink()
{
    if (!buffer || fixed_buffer ||
        buffer_bytes < SHRINK_MINSIZE ||
        (read_offset + 7) * 2 < buffer_bytes * 8)
    {
        // do not shrink fixed sized buffers
        // do not shrink if the buffer size is under the minimum shrink size
        // do not shrink until the read region is at least half of the total data size
        return;
    }

    u32 new_buffer_bytes = 1 << (BSR32((write_offset - read_offset + (read_offset % 8) + 7) / 8) + 1);

    u8 *new_buffer = new u8[new_buffer_bytes];
    if (!new_buffer) return;

    // copy old buffer contents to the new buffer
    u32 read_start = read_offset / 8;
    u32 read_count = CAT_CEIL_UNIT(write_offset, 8) - read_start;

    memcpy(new_buffer, buffer + read_start, read_count);

    read_offset %= 8;
    write_offset -= read_start * 8;

    delete[] buffer;

    buffer = new_buffer;
    buffer_bytes = new_buffer_bytes;
}


//// insertion

void BitStream::write1(u8 data) // data MUST be 1 or 0
{
    data &= 1;

    grow(1);

    u32 byte_offset = write_offset / 8;
    u32 shift = write_offset % 8;

    if (shift)
        buffer[byte_offset] |= data << shift;
    else
        buffer[byte_offset] = data;

    ++write_offset;
}

void BitStream::writeBits(u32 data, int bits)
{
    grow(bits);

    u32 byte_offset = write_offset / 8;
    u32 shift = write_offset % 8;
    u32 remaining_bits = bits;

    if (shift)
    {
        buffer[byte_offset] |= data << shift;
        data = (unsigned)data >> (8 - shift);
        remaining_bits -= 8 - shift;
        ++byte_offset;
    }

    switch ((remaining_bits + 7) / 8)
    {
    case 4:
        *(u32*)(buffer + byte_offset) = data;
        break;
    case 3:
        buffer[byte_offset + 2] = (u8)(data >> 16);
    case 2:
        *(u16*)(buffer + byte_offset) = (u16)data;
        break;
    case 1:
        buffer[byte_offset] = (u8)data;
        break;
    }

    write_offset += bits;
}

void BitStream::writeBytes(const void *vdata, u32 byte_count)
{
    grow(byte_count * 8);

    u32 byte_offset = write_offset / 8;
    u32 shift = write_offset % 8;

    if (shift)
    {
        u8 *data = (u8*)vdata;
        u8 *out = buffer + byte_offset;
        u32 remaining = byte_count;
        u8 next = data[0];

        *out++ |= next << shift;

        while (remaining >= 5)
        {
            next = data[4];
            *(u32*)out = (*(u32*)data >> (8 - shift)) | (next << (shift + 24));
            out += 4;
            data += 4;
            remaining -= 4;
        }

        while (remaining >= 2)
        {
            u8 last = next;
            next = data[1];
            *out++ = (last >> (8 - shift)) | (next << shift);
            ++data;
            --remaining;
        }

        if (remaining > 0)
        {
            *out = next >> (8 - shift);
        }
    }
    else
    {
        memcpy(buffer + byte_offset, vdata, byte_count);
    }

    write_offset += byte_count * 8;
}


//// extraction

u8 BitStream::read1()
{
    if (read_offset + 1 > write_offset)
    {
        read_underrun = true;
        return 0;
    }

    u32 byte_offset = read_offset / 8;
    u32 shift = read_offset % 8;

    u8 data = (buffer[byte_offset] >> shift) & 1;

    ++read_offset;

    return data;
}

u32 BitStream::readBits(u32 bits)
{
    if (read_offset + bits > write_offset)
    {
        read_underrun = true;
        return 0;
    }

    u32 byte_offset = read_offset / 8;
    u32 shift = read_offset % 8;
    u32 data;

    switch ((shift + bits + 7) / 8)
    {
    case 5:
        data = (buffer[byte_offset + 4] << (32 - shift)) | (*(u32*)(buffer + byte_offset) >> shift);
        break;
    case 4:
        data = *(u32*)(buffer + byte_offset) >> shift;
        break;
    case 3:
        data = ((buffer[byte_offset + 2] << 16) | *(u16*)(buffer + byte_offset)) >> shift;
        break;
    case 2:
        data = *(u16*)(buffer + byte_offset) >> shift;
        break;
    case 1:
        data = buffer[byte_offset] >> shift;
        break;
    }

    read_offset += bits;

    // clear high garbage bits
    shift = 32 - bits;
    data <<= shift;
    data >>= shift;

    return data;
}

void BitStream::readBytes(void *vdata, u32 byte_count)
{
    if (read_offset + byte_count * 8 > write_offset)
    {
        read_underrun = true;
        return;
    }

    u32 byte_offset = read_offset / 8;
    u32 shift = read_offset % 8;

    if (shift)
    {
        u8 *out = (u8*)vdata;
        u8 *in = buffer + byte_offset;
        u32 remaining = byte_count;
        u8 next;

        if (remaining >= 5)
        {
            do {
                next = in[4];
                *(u32*)out = (*(u32*)in >> shift) | (next << (32 - shift));
                out += 4;
                in += 4;
                remaining -= 4;
            } while (remaining >= 5);
        }
        else
        {
            next = in[0];
        }

        next = in[0];
        while (remaining > 0)
        {
            u8 last = next;
            next = in[1];
            out[0] = (last >> shift) | (next << (8 - shift));
            ++out;
            ++in;
            --remaining;
        }
    }
    else
    {
        memcpy(vdata, buffer + byte_offset, byte_count);
    }

    read_offset += byte_count * 8;
}
