//
// Copyright (c) 2008-2020 the Urho3D project.
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
