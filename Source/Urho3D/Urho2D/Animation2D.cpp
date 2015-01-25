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

#include "../Urho2D/Animation2D.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../IO/Log.h"
#include "../Urho2D/Sprite2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

Transform2D::Transform2D() :
    position_(Vector2::ZERO),
    angle_(0.0f),
    scale_(1.0f, 1.0f)
{
}

Transform2D::Transform2D(const Vector2& position, float angle, const Vector2& scale) :
    position_(position), 
    angle_(angle), 
    scale_(scale)
{
}

Transform2D::Transform2D(const Transform2D& other) :
    position_(other.position_), 
    angle_(other.angle_), 
    scale_(other.scale_)
{
}

Transform2D& Transform2D::operator = (const Transform2D& other)
{
    position_ = other.position_; 
    angle_ = other.angle_;
    scale_ = other.scale_;
    return *this;
}

Transform2D Transform2D::operator * (const Transform2D& other) const
{
    float x = scale_.x_ * other.position_.x_;
    float y = scale_.y_ * other.position_.y_;
    float s = Sin(angle_);
    float c = Cos(angle_);

    Vector2 position;
    position.x_ = (x * c) - (y * s);
    position.y_ = (x * s) + (y * c);
    position = position_ + position;

    float angle = angle_ + other.angle_;
    Vector2 scale = scale_ * other.scale_;

    return Transform2D(position, angle, scale);
}

Transform2D Transform2D::Lerp(const Transform2D& other, float t, int spin) const
{
    Transform2D ret;
    ret.position_ = position_.Lerp(other.position_, t);

    if (spin > 0 && angle_ > other.angle_)
        ret.angle_ = Urho3D::Lerp(angle_, other.angle_ + 360.0f, t);
    else if (spin < 0 && angle_ < other.angle_)
        ret.angle_= Urho3D::Lerp(angle_, other.angle_ - 360.0f, t);
    else
        ret.angle_= Urho3D::Lerp(angle_, other.angle_, t);

    ret.scale_ = scale_.Lerp(other.scale_, t);
    return ret;
}

AnimationKeyFrame2D::AnimationKeyFrame2D() : 
    time_(0.0f), 
    enabled_(false),
    parent_(-1),
    spin_(1),
    zIndex_(0),
    alpha_(1.0f),
    useHotSpot_(false)
{
}

Animation2D::Animation2D(AnimationSet2D* animationSet) : 
    animationSet_(animationSet),
    length_(0.0f), 
    looped_(true)
{
}

Animation2D::~Animation2D()
{
}

void Animation2D::SetName(const String& name)
{
    name_ = name;
}

void Animation2D::SetLength(float length)
{
    length_ = Max(0.0f, length);
}

void Animation2D::SetLooped(bool looped)
{
    looped_ = looped;
}

AnimationSet2D* Animation2D::GetAnimationSet() const
{
    return animationSet_;
}

const AnimationTrack2D& Animation2D::GetTrack(unsigned index) const
{
    if (index >= tracks_.Size())
    {
        LOGWARNING("Index out of range");
        index = 0;
    }

    return tracks_[index];
}

}
