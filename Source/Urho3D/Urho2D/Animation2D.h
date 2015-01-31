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

#include "../Container/Ptr.h"
#include "../Container/RefCounted.h"
#include "../Math/Vector2.h"

namespace Urho3D
{

class AnimationSet2D;
class Sprite2D;

/// 2D Transform class for spriter animation.
struct Transform2D
{
    /// Construct.
    Transform2D();
    /// Construct from position, angle, scale.
    Transform2D(const Vector2& position, float angle, const Vector2& scale);
    /// Copy-construct from another transform.
    Transform2D(const Transform2D& other);

    /// Assign from another transform.
    Transform2D& operator = (const Transform2D& other);
    /// Multiply a transform.
    Transform2D operator * (const Transform2D& other) const;
    /// Linear interpolation with another transform.
    Transform2D Lerp(const Transform2D& other, float t, int spin) const;

    /// Position.
    Vector2 position_;
    /// Angle.
    float angle_;
    /// Scale.
    Vector2 scale_;
};

/// 2D animation key frame.
struct AnimationKeyFrame2D
{
    /// Construct.
    AnimationKeyFrame2D();
    
    /// Time.
    float time_;

    /// Enabled (2D animation may disable node on fly).
    bool enabled_;
    /// Parent (2D animation may change parent on fly).
    int parent_;
    /// Transform.
    Transform2D transform_;
    /// Spin direction.
    int spin_;

    /// Draw order.
    int zIndex_;
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Alpha.
    float alpha_;
    /// Use hot spot.
    bool useHotSpot_;
    /// Hot spot.
    Vector2 hotSpot_;
};

/// 2D animation track.
struct AnimationTrack2D
{
    /// Name.
    String name_;
    /// Is sprite track.
    bool hasSprite_;
    /// Animation key frames.
    Vector<AnimationKeyFrame2D> keyFrames_;
};

/// 2D Animation.
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
    
    /// Return animation set.
    AnimationSet2D* GetAnimationSet() const;
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return length.
    float GetLength() const { return length_; }
    /// Return looped.
    bool IsLooped() const { return looped_; }
    /// Return number of animation tracks.
    unsigned GetNumTracks() const { return tracks_.Size(); }
    /// Return animation track.
    const AnimationTrack2D& GetTrack(unsigned index) const;

    /// Return all animation tracks (internal use only).
    Vector<AnimationTrack2D>& GetAllTracks() { return tracks_; }

private:
    /// Animation set.
    WeakPtr<AnimationSet2D> animationSet_;
    /// Name.
    String name_;
    /// Length.
    float length_;
    /// Looped.
    bool looped_;
    /// Animation tracks.
    Vector<AnimationTrack2D> tracks_;
};

}
