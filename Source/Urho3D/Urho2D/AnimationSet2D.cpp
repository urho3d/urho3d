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

#include "../Urho2D/Animation2D.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../Core/Context.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

AnimationSet2D::AnimationSet2D(Context* context) :
    Resource(context)
{
}

AnimationSet2D::~AnimationSet2D()
{
}

void AnimationSet2D::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimationSet2D>();
}

bool AnimationSet2D::BeginLoad(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    String extension = GetExtension(source.GetName());
    if (extension == ".scml")
        return BeginLoadSpriter(source);

    LOGERROR("Unsupport animation set file: " + source.GetName());

    return false;
}

bool AnimationSet2D::EndLoad()
{
    if (spriterFile_)
        return EndLoadSpriter();

    return false;
}

unsigned AnimationSet2D::GetNumAnimations() const
{
    return animations_.Size();
}

Animation2D* AnimationSet2D::GetAnimation(unsigned index) const
{
    if (index < animations_.Size())
        return animations_[index];
    return 0;
}

Animation2D* AnimationSet2D::GetAnimation(const String& name) const
{
    for (unsigned i = 0; i < animations_.Size(); ++i)
    {
        if (animations_[i]->GetName() == name)
            return animations_[i];
    }
    return 0;
}

Sprite2D* AnimationSet2D::GetSprite(const StringHash& hash) const
{
    HashMap<StringHash, SharedPtr<Sprite2D> >::ConstIterator i = sprites_.Find(hash);
    if (i != sprites_.End())
        return i->second_;
    return 0;
}

bool AnimationSet2D::BeginLoadSpriter(Deserializer &source)
{
    spriterFile_ = new XMLFile(context_);
    if (!spriterFile_->Load(source))
    {
        LOGERROR("Load XML failed " + source.GetName());
        spriterFile_.Reset();
        return false;
    }

    XMLElement rootElem = spriterFile_->GetRoot("spriter_data");
    if (!rootElem)
    {
        LOGERROR("Invalid spriter file " + source.GetName());
        spriterFile_.Reset();
        return false;
    }

    // When async loading, preprocess folders for spritesheet / sprite files and request them for background loading
    if (GetAsyncLoadState() == ASYNC_LOADING)
    {
        if (!LoadSpriterFolders(rootElem))
        {
            spriterFile_.Reset();
            return false;
        }
    }

    return true;
}

bool AnimationSet2D::EndLoadSpriter()
{
    XMLElement rootElem = spriterFile_->GetRoot("spriter_data");
    if (!LoadSpriterFolders(rootElem))
    {
        spriterFile_.Reset();
        return false;
    }

    XMLElement entityElem = rootElem.GetChild("entity");
    if (!entityElem)
    {
        LOGERROR("Could not find entity");
        spriterFile_.Reset();
        return false;
    }

    for (XMLElement animationElem = entityElem.GetChild("animation"); animationElem; animationElem = animationElem.GetNext("animation"))
    {
        if (!LoadSpriterAnimation(animationElem))
        {
            spriterFile_.Reset();
            return false;
        }
    }

    spriterFile_.Reset();
    return true;
}

bool AnimationSet2D::LoadSpriterFolders(const XMLElement& rootElem)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    bool async = GetAsyncLoadState() == ASYNC_LOADING;

    String parentPath = GetParentPath(GetName());
    String spriteSheetFilePathPList = parentPath + GetFileName(GetName()) + ".plist";
    String spriteSheetFilePathXML = parentPath + GetFileName(GetName()) + ".xml";
    SpriteSheet2D* spriteSheet = 0;
    bool hasSpriteSheet = false;

    // When async loading, request the sprite sheet for background loading but do not actually get it
    if (!async)
    {
        spriteSheet = cache->GetResource<SpriteSheet2D>(spriteSheetFilePathPList, false);
        if (!spriteSheet)
            spriteSheet = cache->GetResource<SpriteSheet2D>(spriteSheetFilePathXML, false);
    }
    else
    {
        hasSpriteSheet = cache->Exists(spriteSheetFilePathPList);
        if (hasSpriteSheet)
            cache->BackgroundLoadResource<SpriteSheet2D>(spriteSheetFilePathPList, false, this);
        else
        {
            hasSpriteSheet = cache->Exists(spriteSheetFilePathXML);
            if (hasSpriteSheet)
                cache->BackgroundLoadResource<SpriteSheet2D>(spriteSheetFilePathXML, false, this);
        }
    }

    for (XMLElement folderElem = rootElem.GetChild("folder"); folderElem; folderElem = folderElem.GetNext("folder"))
    {
        unsigned folderId = folderElem.GetUInt("id");

        for (XMLElement fileElem = folderElem.GetChild("file"); fileElem; fileElem = fileElem.GetNext("file"))
        {
            unsigned fileId = fileElem.GetUInt("id");
            String fileName = fileElem.GetAttribute("name");

            // When async loading, request the sprites for background loading but do not actually get them
            if (!async)
            {
                SharedPtr<Sprite2D> sprite;

                if (spriteSheet)
                    sprite = spriteSheet->GetSprite(GetFileName(fileName));
                else
                    sprite = (cache->GetResource<Sprite2D>(parentPath + fileName));

                if (!sprite)
                {
                    LOGERROR("Could not load sprite " + fileName);
                    return false;
                }

                Vector2 hotSpot(0.0f, 1.0f);
                if (fileElem.HasAttribute("pivot_x"))
                    hotSpot.x_ = fileElem.GetFloat("pivot_x");
                if (fileElem.HasAttribute("pivot_y"))
                    hotSpot.y_ = fileElem.GetFloat("pivot_y");

                // If sprite is trimmed, recalculate hot spot
                const IntVector2& offset = sprite->GetOffset();
                if (offset != IntVector2::ZERO)
                {
                    int width = fileElem.GetInt("width");
                    int height = fileElem.GetInt("height");

                    float pivotX = width * hotSpot.x_;
                    float pivotY = height * (1.0f - hotSpot.y_);

                    const IntRect& rectangle = sprite->GetRectangle();
                    hotSpot.x_ = (offset.x_ + pivotX) / rectangle.Width();
                    hotSpot.y_ = 1.0f - (offset.y_ + pivotY) / rectangle.Height();
                }

                sprite->SetHotSpot(hotSpot);

                sprites_[StringHash((folderId << 16) + fileId)] = sprite;
            }
            else if (!hasSpriteSheet)
                cache->BackgroundLoadResource<Sprite2D>(parentPath + fileName, true, this);
        }
    }

    return true;
}

// Spriter object type.
enum SpriterObjectType2D
{
    SOT_BONE = 0,
    SOT_SPRITE,
};

// Spriter timeline key.
struct SpriterTimelineKey2D
{
    SpriterTimelineKey2D() : 
        time_(0.0f),
        angle_(0.0f),
        spin_(1),
        scale_(1.0f, 1.0f),
        alpha_(1.0f),
        useHotSpot_(false)
    {
    }

    float time_;
    Vector2 position_;
    float angle_;
    int spin_;
    Vector2 scale_;
    SharedPtr<Sprite2D> sprite_;
    float alpha_;
    bool useHotSpot_;
    Vector2 hotSpot_;
};

// Spriter timeline.
struct SpriterTimeline2D
{
    SpriterTimeline2D() :
        parent_(-1),
        type_(SOT_BONE)
    {
    }

    String name_;
    int parent_;
    SpriterObjectType2D type_;
    Vector<SpriterTimelineKey2D> timelineKeys_;
};

// Spriter reference.
struct SpriterReference2D
{
    SpriterReference2D() :
        type_(SOT_BONE),
        timeline_(-1),
        key_(-1),
        zIndex_(0)
    {
    }

    SpriterObjectType2D type_;
    int timeline_;
    int key_;
    int zIndex_;
};

// Spriter mainline Key.
struct SpriterMainlineKey2D
{
    float time_;
    PODVector<SpriterReference2D> references_;
};

bool AnimationSet2D::LoadSpriterAnimation(const XMLElement& animationElem)
{
    String name = animationElem.GetAttribute("name");
    float length = animationElem.GetFloat("length") * 0.001f;
    bool looped = true;
    if (animationElem.HasAttribute("looping"))
        looped = animationElem.GetBool("looping");

    float highestKeyTime = 0.0f;

    // Load timelines
    Vector<SpriterTimeline2D> timelines;
    for (XMLElement timelineElem = animationElem.GetChild("timeline"); timelineElem; timelineElem = timelineElem.GetNext("timeline"))
    {
        SpriterTimeline2D timeline;
        timeline.name_ = timelineElem.GetAttribute("name");
        if (timelineElem.GetAttribute("object_type") == "bone")
            timeline.type_ = SOT_BONE;
        else
            timeline.type_ = SOT_SPRITE;

        for (XMLElement keyElem = timelineElem.GetChild("key"); keyElem; keyElem = keyElem.GetNext("key"))
        {
            SpriterTimelineKey2D key;
            key.time_ = keyElem.GetFloat("time") * 0.001f;
            if (keyElem.HasAttribute("spin"))
                key.spin_ = keyElem.GetInt("spin");

            XMLElement childElem = keyElem.GetChild();

            key.position_.x_ = childElem.GetFloat("x");
            key.position_.y_ = childElem.GetFloat("y");

            key.angle_ = childElem.GetFloat("angle");

            Vector2 scale(Vector2::ONE);
            if (childElem.HasAttribute("scale_x"))
                key.scale_.x_ = childElem.GetFloat("scale_x");

            if (childElem.HasAttribute("scale_y"))
                key.scale_.y_ = childElem.GetFloat("scale_y");

            if (timeline.type_ == SOT_SPRITE)
            {
                int folder = childElem.GetUInt("folder");
                int file = childElem.GetUInt("file");
                key.sprite_ = GetSprite(StringHash((folder << 16) + file));
                if (!key.sprite_)
                {
                    LOGERROR("Could not find sprite");
                    return false;
                }

                if (childElem.HasAttribute("pivot_x") && childElem.HasAttribute("pivot_y"))
                {
                    key.useHotSpot_ = true;
                    key.hotSpot_.x_ = childElem.GetFloat("pivot_x");
                    key.hotSpot_.y_ = childElem.GetFloat("pivot_y");
                }

                if (childElem.HasAttribute("a"))
                    key.alpha_ = childElem.GetFloat("a");
            }

            timeline.timelineKeys_.Push(key);
        }

        timelines.Push(timeline);
    }

    // Load main line
    Vector<SpriterMainlineKey2D> mainlineKeys;
    XMLElement mainlineElem = animationElem.GetChild("mainline");
    for (XMLElement keyElem = mainlineElem.GetChild("key"); keyElem; keyElem = keyElem.GetNext("key"))
    {
        SpriterMainlineKey2D mainlineKey;
        mainlineKey.time_ = keyElem.GetFloat("time") * 0.001f;

        for (XMLElement refElem = keyElem.GetChild(); refElem; refElem = refElem.GetNext())
        {
            SpriterReference2D ref;
            if (refElem.GetName() == "bone_ref")
                ref.type_ = SOT_BONE;
            else
                ref.type_ = SOT_SPRITE;

            ref.timeline_ = refElem.GetInt("timeline");
            ref.key_ = refElem.GetInt("key");

            if (refElem.HasAttribute("parent"))
            {
                int parent = refElem.GetInt("parent");
                int parentTimeline = mainlineKey.references_[parent].timeline_;
                timelines[ref.timeline_].parent_ = parentTimeline;
            }

            if (refElem.GetName() == "object_ref")
                ref.zIndex_ = refElem.GetInt("z_index");

            mainlineKey.references_.Push(ref);
        }

        mainlineKeys.Push(mainlineKey);
    }
    
    unsigned numTimelines = timelines.Size();
    unsigned numMainlineKeys = mainlineKeys.Size();
    if (numTimelines == 0 || numMainlineKeys == 0)
    {
        LOGERROR("Invalid animation");
        return false;
    }

    // Create animation
    SharedPtr<Animation2D> animation(new Animation2D(this));
    animation->SetName(name);
    animation->SetLength(length);
    animation->SetLooped(looped);

    Vector<AnimationTrack2D>& tracks = animation->GetAllTracks();
    tracks.Resize(numTimelines);

    // Setup animation track key frames
    for (unsigned i = 0; i < numTimelines; ++i)
    {
        SpriterTimeline2D& timeline = timelines[i];
        AnimationTrack2D& track = tracks[i];
        
        track.name_ = timeline.name_;
        track.hasSprite_ = timeline.type_ == SOT_SPRITE;

        unsigned numTimelineKeys = timeline.timelineKeys_.Size();
        tracks[i].keyFrames_.Resize(numTimelineKeys);

        for (unsigned j = 0; j < numTimelineKeys; ++j)
        {
            SpriterTimelineKey2D& timelineKey = timeline.timelineKeys_[j];
            AnimationKeyFrame2D& keyFrame = track.keyFrames_[j];

            keyFrame.time_ = timelineKey.time_;
            highestKeyTime = Max(highestKeyTime, keyFrame.time_);

            // Set disabled
            keyFrame.enabled_ = false;
            keyFrame.parent_ = timeline.parent_;
            keyFrame.transform_ = Transform2D(timelineKey.position_, timelineKey.angle_, timelineKey.scale_);
            keyFrame.spin_ = timelineKey.spin_;

            if (track.hasSprite_)
            {
                keyFrame.sprite_ = timelineKey.sprite_;
                keyFrame.alpha_ = timelineKey.alpha_;
                keyFrame.useHotSpot_ = timelineKey.useHotSpot_;
                if (timelineKey.useHotSpot_)
                    keyFrame.hotSpot_ = timelineKey.hotSpot_;
            }
        }
    }

    // Set animation key frame enabled and set draw order
    for (unsigned i = 0; i < numMainlineKeys; ++i)
    {
        SpriterMainlineKey2D& mainlineKey = mainlineKeys[i];
        PODVector<SpriterReference2D>& references = mainlineKey.references_;
        for (unsigned j = 0; j < references.Size(); ++j)
        {
            SpriterReference2D& ref = references[j];
            AnimationKeyFrame2D& keyFrame = tracks[ref.timeline_].keyFrames_[ref.key_];

            // Set enabled
            keyFrame.enabled_ = true;

            // Set draw order
            keyFrame.zIndex_ = ref.zIndex_;
        }
    }

    // Fix looped animation
    if (looped)
    {
        for (unsigned i = 0; i < numTimelines; ++i)
        {
            Vector<AnimationKeyFrame2D>& keyFrames = tracks[i].keyFrames_;
            if (keyFrames.Front().time_ < 0.01f && !Equals(keyFrames.Back().time_, length))
            {
                AnimationKeyFrame2D keyFrame = keyFrames.Front();
                keyFrame.time_ = length;
                keyFrames.Push(keyFrame);
            }
        }
    }
    else
    {
        // Crop non-looped animation length if longer than the last keyframe
        if (length > highestKeyTime)
            animation->SetLength(highestKeyTime);
    }

    animations_.Push(animation);

    return true;
}

}
