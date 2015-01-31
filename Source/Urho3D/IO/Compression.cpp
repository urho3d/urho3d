//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Container/ArrayPtr.h"
#include "../IO/Compression.h"
#include "../IO/Deserializer.h"
#include "../IO/Serializer.h"
#include "../IO/VectorBuffer.h"

#include <LZ4/lz4.h>
#include <LZ4/lz4hc.h>

namespace Urho3D
{

unsigned EstimateCompressBound(unsigned srcSize)
{
    return LZ4_compressBound(srcSize);
}

unsigned CompressData(void* dest, const void* src, unsigned srcSize)
{
    if (!dest || !src || !srcSize)
        return 0;
    else
        return LZ4_compressHC((const char*)src, (char*)dest, srcSize);
}

unsigned DecompressData(void* dest, const void* src, unsigned destSize)
{
    if (!dest || !src || !destSize)
        return 0;
    else
        return LZ4_decompress_fast((const char*)src, (char*)dest, destSize);
}

bool CompressStream(Serializer& dest, Deserializer& src)
{
    unsigned srcSize = src.GetSize() - src.GetPosition();
    // Prepend the source and dest. data size in the stream so that we know to buffer & uncompress the right amount
    if (!srcSize)
    {
        dest.WriteUInt(0);
        dest.WriteUInt(0);
        return true;
    }
    
    unsigned maxDestSize = LZ4_compressBound(srcSize);
    SharedArrayPtr<unsigned char> srcBuffer(new unsigned char[srcSize]);
    SharedArrayPtr<unsigned char> destBuffer(new unsigned char[maxDestSize]);
    
    if (src.Read(srcBuffer, srcSize) != srcSize)
        return false;
    
    unsigned destSize = LZ4_compressHC((const char*)srcBuffer.Get(), (char*)destBuffer.Get(), srcSize);
    bool success = true;
    success &= dest.WriteUInt(srcSize);
    success &= dest.WriteUInt(destSize);
    success &= dest.Write(destBuffer, destSize) == destSize;
    return success;
}

bool DecompressStream(Serializer& dest, Deserializer& src)
{
    if (src.IsEof())
        return false;
    
    unsigned destSize = src.ReadUInt();
    unsigned srcSize = src.ReadUInt();
    if (!srcSize || !destSize)
        return true; // No data
    
    if (srcSize > src.GetSize())
        return false; // Illegal source (packed data) size reported, possibly not valid data
    
    SharedArrayPtr<unsigned char> srcBuffer(new unsigned char[srcSize]);
    SharedArrayPtr<unsigned char> destBuffer(new unsigned char[destSize]);
    
    if (src.Read(srcBuffer, srcSize) != srcSize)
        return false;
    
    LZ4_decompress_fast((const char*)srcBuffer.Get(), (char*)destBuffer.Get(), destSize);
    return dest.Write(destBuffer, destSize) == destSize;
}

VectorBuffer CompressVectorBuffer(VectorBuffer& src)
{
    VectorBuffer ret;
    src.Seek(0);
    CompressStream(ret, src);
    ret.Seek(0);
    return ret;
}

VectorBuffer DecompressVectorBuffer(VectorBuffer& src)
{
    VectorBuffer ret;
    src.Seek(0);
    DecompressStream(ret, src);
    ret.Seek(0);
    return ret;
}

}
