// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Resource/Resource.h"

#include <memory>

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
    explicit AnimationSet2D(Context* context);
    /// Destruct.
    ~AnimationSet2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;

    /// Get number of animations.
    /// @property
    unsigned GetNumAnimations() const;
    /// Return animation name.
    String GetAnimation(unsigned index) const;
    /// Check has animation.
    bool HasAnimation(const String& animationName) const;

    /// Return sprite.
    Sprite2D* GetSprite() const;

#ifdef URHO3D_SPINE
    /// Return spine skeleton data.
    spSkeletonData* GetSkeletonData() const { return skeletonData_; }
#endif

    /// Return spriter data.
    Spriter::SpriterData* GetSpriterData() const { return spriterData_.get(); }
    
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
    std::unique_ptr<Spriter::SpriterData> spriterData_;
    
    /// Has sprite sheet.
    bool hasSpriteSheet_;
    
    /// Sprite sheet file path.
    String spriteSheetFilePath_;
    
    /// Sprite sheet.
    SharedPtr<SpriteSheet2D> spriteSheet_;
    
    /// Spriter sprites.
    HashMap<unsigned, SharedPtr<Sprite2D> > spriterFileSprites_;
};

}

