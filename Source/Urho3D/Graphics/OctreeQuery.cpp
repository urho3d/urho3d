//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Graphics/OctreeQuery.h"

#include "../DebugNew.h"

namespace Urho3D
{

Intersection PointOctreeQuery::TestOctant(const BoundingBox& box, bool inside)
{
    if (inside)
        return INSIDE;
    else
        return box.IsInside(point_);
}

void PointOctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside)
{
    while (start != end)
    {
        Drawable* drawable = *start++;

        if ((drawable->GetDrawableFlags() & drawableFlags_) && (drawable->GetViewMask() & viewMask_))
        {
            if (inside || drawable->GetWorldBoundingBox().IsInside(point_))
                result_.Push(drawable);
        }
    }
}

Intersection SphereOctreeQuery::TestOctant(const BoundingBox& box, bool inside)
{
    if (inside)
        return INSIDE;
    else
        return sphere_.IsInside(box);
}

void SphereOctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside)
{
    while (start != end)
    {
        Drawable* drawable = *start++;

        if ((drawable->GetDrawableFlags() & drawableFlags_) && (drawable->GetViewMask() & viewMask_))
        {
            if (inside || sphere_.IsInsideFast(drawable->GetWorldBoundingBox()))
                result_.Push(drawable);
        }
    }
}

Intersection BoxOctreeQuery::TestOctant(const BoundingBox& box, bool inside)
{
    if (inside)
        return INSIDE;
    else
        return box_.IsInside(box);
}

void BoxOctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside)
{
    while (start != end)
    {
        Drawable* drawable = *start++;

        if ((drawable->GetDrawableFlags() & drawableFlags_) && (drawable->GetViewMask() & viewMask_))
        {
            if (inside || box_.IsInsideFast(drawable->GetWorldBoundingBox()))
                result_.Push(drawable);
        }
    }
}

Intersection FrustumOctreeQuery::TestOctant(const BoundingBox& box, bool inside)
{
    if (inside)
        return INSIDE;
    else
        return frustum_.IsInside(box);
}

void FrustumOctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside)
{
    while (start != end)
    {
        Drawable* drawable = *start++;

        if ((drawable->GetDrawableFlags() & drawableFlags_) && (drawable->GetViewMask() & viewMask_))
        {
            if (inside || frustum_.IsInsideFast(drawable->GetWorldBoundingBox()))
                result_.Push(drawable);
        }
    }
}


Intersection AllContentOctreeQuery::TestOctant(const BoundingBox& box, bool inside)
{
    return INSIDE;
}

void AllContentOctreeQuery::TestDrawables(Drawable** start, Drawable** end, bool inside)
{
    while (start != end)
    {
        Drawable* drawable = *start++;

        if ((drawable->GetDrawableFlags() & drawableFlags_) && (drawable->GetViewMask() & viewMask_))
            result_.Push(drawable);
    }
}

}
