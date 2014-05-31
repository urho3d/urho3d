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

#include "Precompiled.h"
#include "Sprite2D.h"
#include "XAnimation2D.h"
#include "XAnimationSet2D.h"

#include "DebugNew.h"

namespace Urho3D
{

ObjectRef::ObjectRef() : 
    timeline_(0),
    key_(0),
    zIndex_(0)
{
}

MainlineKey::MainlineKey() :
    time_(0)
{
}

const ObjectRef* MainlineKey::GetObjectRef(int timeline) const
{
    for (unsigned i = 0; i < objectRefs_.Size(); ++i)
    {
        if (timeline == objectRefs_[i].timeline_)
            return &objectRefs_[i];
    }
    return 0;
}

ObjectKey::ObjectKey() :
    time_(0.0f),
    pivot_(0.0f, 1.0f),
    scale_(Vector2::ONE), 
    spin_(1),
    alpha_(1.0f)
{
}

Timeline::Timeline()
{
}

XAnimation2D::XAnimation2D(XAnimationSet2D* animationSet) : 
    animationSet_(animationSet),
    length_(0.0f), 
    looped_(true)
{
}

XAnimation2D::~XAnimation2D()
{
}

void XAnimation2D::SetName(const String& name)
{
    name_ = name;
}

void XAnimation2D::SetLength(float length)
{
    length_ = Max(0.0f, length);
}

void XAnimation2D::SetLooped(bool looped)
{
    looped_ = looped;
}

void XAnimation2D::AddMainlineKey(const MainlineKey& mainlineKey)
{
    mainlineKeys_.Push(mainlineKey);
}

void XAnimation2D::AddTimeline(const Timeline& timeline)
{
    timelines_.Push(timeline);
}

XAnimationSet2D* XAnimation2D::GetAnimationSet() const
{
    return animationSet_;
}

}
