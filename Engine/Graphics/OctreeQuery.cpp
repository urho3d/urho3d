//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "DebugNew.h"

Intersection PointOctreeQuery::TestOctant(const BoundingBox& box, unsigned& mask) const
{
    return box.IsInside(point_);
}

Intersection PointOctreeQuery::TestDrawable(const BoundingBox& box, unsigned& mask) const
{
    return box.IsInside(point_);
}

Intersection SphereOctreeQuery::TestOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return sphere_.IsInside(box);
}

Intersection SphereOctreeQuery::TestDrawable(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return sphere_.IsInsideFast(box);
}

Intersection BoxOctreeQuery::TestOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return box_.IsInside(box);
}

Intersection BoxOctreeQuery::TestDrawable(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return box_.IsInsideFast(box);
}

Intersection FrustumOctreeQuery::TestOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return frustum_.IsInsideMasked(box, mask);
}

Intersection FrustumOctreeQuery::TestDrawable(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return frustum_.IsInsideFastMasked(box, mask);
}

Intersection OccludedFrustumOctreeQuery::TestOctant(const BoundingBox& box, unsigned& mask) const
{
    // First check the frustum
    Intersection frustumRes = INSIDE;
    if (mask != M_MAX_UNSIGNED)
    {
        frustumRes = frustum_.IsInsideMasked(box, mask);
        if (frustumRes == OUTSIDE)
            return OUTSIDE;
    }
    
    // Then check occlusion
    if (buffer_->IsVisible(box))
        return frustumRes;
    else
        return OUTSIDE;
}

Intersection OccludedFrustumOctreeQuery::TestDrawable(const BoundingBox& box, unsigned& mask) const
{
    // First check the frustum
    if (mask != M_MAX_UNSIGNED)
    {
        if (frustum_.IsInsideFastMasked(box, mask) == OUTSIDE)
            return OUTSIDE;
    }
    
    // Then check occlusion
    if (buffer_->IsVisible(box))
        return INSIDE;
    else
        return OUTSIDE;
}
