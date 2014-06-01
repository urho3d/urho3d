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

/// Object reference.
struct ObjectRef
{
    /// Construct.
    ObjectRef();
    
    /// Is bone.
    bool isBone_;
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
struct MainlineKey
{
public:
    /// Construct.
    MainlineKey();

    /// Time.
    float time_;
    /// Object references.
    Vector<ObjectRef> objectRefs_;
    /// Return object reference by timeline.
    const ObjectRef* GetObjectRef(int timeline) const;
};

/// Object key.
struct ObjectKey
{
    /// Construct.
    ObjectKey();

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
struct Timeline
{
    /// Construct.
    Timeline();

    /// Name.
    String name_;
    /// Is sprite.
    bool isSprite_;
    /// Object keys.
    Vector<ObjectKey> objectKeys_;
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
    void AddMainlineKey(const MainlineKey& mainlineKey);
    /// Add timeline.
    void AddTimeline(const Timeline& timeline);

    /// Return animation set.
    AnimationSet2D* GetAnimationSet() const;
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return length.
    float GetLength() const { return length_; }
    /// Return looped.
    bool IsLooped() const { return looped_; }
    /// Return all mainline keys.
    const Vector<MainlineKey>& GetMainlineKeys() const { return mainlineKeys_; }
    /// Return number of timelines.
    unsigned GetNumTimelines() const { return timelines_.Size();}
    /// Return timeline by index.
    const Timeline& GetTimeline(unsigned index) const { return timelines_[index]; }
    /// Return all timelines.
    const Vector<Timeline>& GetTimelines() const { return timelines_; }

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
    Vector<MainlineKey> mainlineKeys_;
    /// All timelines.
    Vector<Timeline> timelines_;
};

}
