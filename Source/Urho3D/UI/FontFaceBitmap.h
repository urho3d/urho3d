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

#include "../UI/FontFace.h"

namespace Urho3D
{

class Image;
class Serializer;

/// Bitmap font face description.
class URHO3D_API FontFaceBitmap : public FontFace
{
public:
    /// Construct.
    explicit FontFaceBitmap(Font* font);
    /// Destruct.
    ~FontFaceBitmap() override;

    /// Load font face.
    bool Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override;
    /// Load from existed font face, pack used glyphs into smallest texture size and smallest number of texture.
    bool Load(FontFace* fontFace, bool usedGlyphs);
    /// Save as a new bitmap font type in XML format. Return true if successful.
    bool Save(Serializer& dest, int pointSize, const String& indentation = "\t");

private:
    /// Convert graphics format to number of components.
    unsigned ConvertFormatToNumComponents(unsigned format);
    /// Save font face texture as image resource.
    SharedPtr<Image> SaveFaceTexture(Texture2D* texture);
    /// Save font face texture as image file.
    bool SaveFaceTexture(Texture2D* texture, const String& fileName);
    /// Blit.
    void Blit(Image* dest, int x, int y, int width, int height, Image* source, int sourceX, int sourceY, int components);
};

}
