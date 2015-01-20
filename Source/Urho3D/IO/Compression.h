//
// Copyright (c) 2008-2014 the Urho3D project.
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

#pragma once

namespace Urho3D
{

class Deserializer;
class Serializer;
class VectorBuffer;

/// Estimate and return worst case LZ4 compressed output size in bytes for given input size.
URHO3D_API unsigned EstimateCompressBound(unsigned srcSize);
/// Compress data using the LZ4 algorithm and return the compressed data size. The needed destination buffer worst-case size is given by EstimateCompressBound().
URHO3D_API unsigned CompressData(void* dest, const void* src, unsigned srcSize);
/// Uncompress data using the LZ4 algorithm. The uncompressed data size must be known. Return the number of compressed data bytes consumed.
URHO3D_API unsigned DecompressData(void* dest, const void* src, unsigned destSize);
/// Compress a source stream (from current position to the end) to the destination stream using the LZ4 algorithm. Return true on success.
URHO3D_API bool CompressStream(Serializer& dest, Deserializer& src);
/// Decompress a compressed source stream produced using CompressStream() to the destination stream. Return true on success.
URHO3D_API bool DecompressStream(Serializer& dest, Deserializer& src);
/// Compress a VectorBuffer using the LZ4 algorithm and return the compressed result buffer.
URHO3D_API VectorBuffer CompressVectorBuffer(VectorBuffer& src);
/// Decompress a VectorBuffer produced using CompressVectorBuffer().
URHO3D_API VectorBuffer DecompressVectorBuffer(VectorBuffer& src);

}
