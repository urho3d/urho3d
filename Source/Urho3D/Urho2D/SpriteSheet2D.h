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

#pragma once

#include "../Resource/Resource.h"

namespace Urho3D
{

class PListFile;
class Sprite2D;
class Texture2D;
class XMLFile;

/// Sprite sheet.
class URHO3D_API SpriteSheet2D : public Resource
{
    OBJECT(SpriteSheet2D);

public:
    /// Construct.
    SpriteSheet2D(Context* context);
    /// Destruct.
    virtual ~SpriteSheet2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();

    /// Return texture.
    Texture2D* GetTexture() const { return texture_; }
    /// Return sprite.
    Sprite2D* GetSprite(const String& name) const;
    /// Define sprite.
    void DefineSprite(const String& name, const IntRect& rectangle, const Vector2& hotSpot = Vector2(0.5f, 0.5f), const IntVector2& offset = IntVector2::ZERO);

    /// Return sprite mapping.
    const HashMap<String, SharedPtr<Sprite2D> >& GetSpriteMapping() const { return spriteMapping_; }

private:
    /// Begin load from PList file.
    bool BeginLoadFromPListFile(Deserializer& source);
    /// End load from PList file.
    bool EndLoadFromPListFile();
    /// Begin load from XML file.
    bool BeginLoadFromXMLFile(Deserializer& source);
    /// End load from XML file.
    bool EndLoadFromXMLFile();

    /// Texture.
    SharedPtr<Texture2D> texture_;
    /// Sprite mapping.
    HashMap<String, SharedPtr<Sprite2D> > spriteMapping_;
    /// PList file used while loading.
    SharedPtr<PListFile> loadPListFile_;
    /// XML file used while loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// Texture name used while loading.
    String loadTextureName_;
};

}
