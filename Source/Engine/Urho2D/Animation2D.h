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

#include "Ptr.h"
#include "RefCounted.h"
#include "Vector2.h"

namespace Urho3D
{

class AnimationSet2D;
class Sprite2D;

/// Object type.
enum ObjectType2D
{
    /// Bone.
    OT_BONE = 0,
    /// Sprite.
    OT_SPRITE,
};

/// Reference.
struct Reference2D
{
    /// Construct.
    Reference2D();

    /// Object type.
    ObjectType2D type_;
    /// Parent.
    int parent_;
    /// Timeline.
    int timeline_;
    /// Key index.
    int key_;
    /// Z index (draw order).
    int zIndex_;
};

/// Mainline Key.
struct MainlineKey2D
{
public:
    /// Construct.
    MainlineKey2D();

    /// Return reference by timeline.
    const Reference2D* GetReference(int timeline) const;
    /// Return timeline by id.
    unsigned GetTimeline(int id) const;

    /// Time.
    float time_;
    /// References.
    Vector<Reference2D> references_;
};

/// Timeline key.
struct TimelineKey2D
{
    /// Construct.
    TimelineKey2D();

    /// Time.
    float time_;
    /// Spin direction.
    int spin_;

    /// Position.
    Vector2 position_;
    /// Angle.
    float angle_;
    /// Scale.
    Vector2 scale_;

    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Hot spot (pivot).
    Vector2 hotSpot_;
    /// Alpha.
    float alpha_;
};

/// Timeline.
struct Timeline2D
{
    /// Construct.
    Timeline2D();

    /// Name.
    String name_;
    /// Object type.
    ObjectType2D type_;
    /// Object keys.
    Vector<TimelineKey2D> timelineKeys_;
};

/// Spriter animation. for more information please refer to http://www.brashmonkey.com/spriter.htm.
class URHO3D_API Animation2D : public RefCounted
{
public:
    /// Construct.
    Animation2D(AnimationSet2D* animationSet);
    /// Destruct
    virtual ~Animation2D();

    /// Set name.
    void SetName(const String& name);
    /// Set length.
    void SetLength(float length);
    /// Set looped.
    void SetLooped(bool looped);
    /// Add mainline key.
    void AddMainlineKey(const MainlineKey2D& mainlineKey);
    /// Add timeline.
    void AddTimeline(const Timeline2D& timeline);

    /// Return animation set.
    AnimationSet2D* GetAnimationSet() const;
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return length.
    float GetLength() const { return length_; }
    /// Return looped.
    bool IsLooped() const { return looped_; }
    /// Return all mainline keys.
    const Vector<MainlineKey2D>& GetMainlineKeys() const { return mainlineKeys_; }
    /// Return number of timelines.
    unsigned GetNumTimelines() const { return timelines_.Size();}
    /// Return timeline by index.
    const Timeline2D& GetTimeline(unsigned index) const { return timelines_[index]; }

private:
    /// Animation set.
    WeakPtr<AnimationSet2D> animationSet_;
    /// Name.
    String name_;
    /// Length.
    float length_;
    /// Looped.
    bool looped_;
    /// All mainline Keys.
    Vector<MainlineKey2D> mainlineKeys_;
    /// All timelines.
    Vector<Timeline2D> timelines_;
};

}
