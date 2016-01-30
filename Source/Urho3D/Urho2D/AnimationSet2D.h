//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Container/ArrayPtr.h"
#include "../Resource/Resource.h"

#ifdef URHO3D_SPINE
struct spAtlas;
struct spSkeletonData;
struct spAnimationStateData;
#endif

namespace Urho3D
{

namespace Spriter
{
    struct SpriterData;
}

class Sprite2D;
class SpriteSheet2D;

/// Spriter animation set, it includes one or more animations, for more information please refer to http://www.esotericsoftware.com and http://www.brashmonkey.com/spriter.htm.
class URHO3D_API AnimationSet2D : public Resource
{
    URHO3D_OBJECT(AnimationSet2D, Resource);

public:
    /// Construct.
    AnimationSet2D(Context* context);
    /// Destruct.
    virtual ~AnimationSet2D();
    /// Register object factory. 
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();

    /// Get number of animations.
    unsigned GetNumAnimations() const;
    /// Return animation name.
    String GetAnimation(unsigned index) const;
    /// Check has animation.
    bool HasAnimation(const String& animation) const;
    
    /// Return sprite.
    Sprite2D* GetSprite() const;

#ifdef URHO3D_SPINE
    /// Return spine skeleton data.
    spSkeletonData* GetSkeletonData() const { return skeletonData_; }
#endif

    /// Return spriter data.
    Spriter::SpriterData* GetSpriterData() const { return spriterData_; }
    /// Return spriter file sprite.
    Sprite2D* GetSpriterFileSprite(int folderId, int fileId) const;

private:
    /// Return sprite by hash.
    Sprite2D* GetSpriterFileSprite(const StringHash& hash) const;
#ifdef URHO3D_SPINE
    /// Begin load spine.
    bool BeginLoadSpine(Deserializer& source);
    /// Finish load spine.
    bool EndLoadSpine();
#endif
    /// Begin load scml.
    bool BeginLoadSpriter(Deserializer& source);
    /// Finish load scml.
    bool EndLoadSpriter();
    /// Dispose all data.
    void Dispose();
    
    /// Spine sprite.
    SharedPtr<Sprite2D> sprite_;
    
#ifdef URHO3D_SPINE
    /// Spine json data.
    SharedArrayPtr<char> jsonData_;
    /// Spine skeleton data.
    spSkeletonData* skeletonData_;
    /// Spine atlas.
    spAtlas* atlas_;
#endif
    
    /// Spriter data.
    Spriter::SpriterData* spriterData_;
    /// Has sprite sheet.
    bool hasSpriteSheet_;
    /// Sprite sheet file path.
    String spriteSheetFilePath_;
    /// Sprite sheet.
    SharedPtr<SpriteSheet2D> spriteSheet_;
    /// Spriter sprites.
    HashMap<int, SharedPtr<Sprite2D> > spriterFileSprites_;
};

}

