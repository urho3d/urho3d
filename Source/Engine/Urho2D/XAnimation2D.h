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

class Sprite2D;
class XAnimationSet2D;

/// Object reference.
struct ObjectRef
{
    /// Construct.
    ObjectRef();

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
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Position.
    Vector2 position_;
    /// Pivot (hot spot).
    Vector2 pivot_;
    /// Scale.
    Vector2 scale_;
    /// Spin direction.
    int spin_;
    /// Angle.
    float angle_;
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
    /// Object keys.
    Vector<ObjectKey> objectKeys_;
};

/// Spriter animation. for more information please refer to http://www.brashmonkey.com/spriter.htm.
class URHO3D_API XAnimation2D : public RefCounted
{
public:
    /// Construct.
    XAnimation2D(XAnimationSet2D* animationSet);
    /// Destruct
    virtual ~XAnimation2D();

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
    XAnimationSet2D* GetAnimationSet() const;
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return length.
    float GetLength() const { return length_; }
    /// Return looped.
    bool IsLooped() const { return looped_; }
    /// Return all mainline keys.
    const Vector<MainlineKey>& GetMainlineKeys() const { return mainlineKeys_; }
    /// Return all timelines.
    const Vector<Timeline>& GetTimelines() const { return timelines_; }

private:
    /// Animation set.
    WeakPtr<XAnimationSet2D> animationSet_;
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
