// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Resource/Image.h"

namespace Urho3D
{

/// Decompress a DXT compressed image to RGBA.
URHO3D_API void
    DecompressImageDXT(unsigned char* rgba, const void* blocks, int width, int height, int depth, CompressedFormat format);
/// Decompress an ETC1/ETC2 compressed image to RGBA.
URHO3D_API void DecompressImageETC(unsigned char* dstImage, const void* blocks, int width, int height, bool hasAlpha);
/// Decompress a PVRTC compressed image to RGBA.
URHO3D_API void DecompressImagePVRTC(unsigned char* rgba, const void* blocks, int width, int height, CompressedFormat format);
/// Flip a compressed block vertically.
URHO3D_API void FlipBlockVertical(unsigned char* dest, const unsigned char* src, CompressedFormat format);
/// Flip a compressed block horizontally.
URHO3D_API void FlipBlockHorizontal(unsigned char* dest, const unsigned char* src, CompressedFormat format);

}
