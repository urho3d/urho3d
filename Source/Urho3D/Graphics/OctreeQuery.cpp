// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
