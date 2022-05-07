// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

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
