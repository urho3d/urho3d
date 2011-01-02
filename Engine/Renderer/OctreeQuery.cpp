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

Intersection PointOctreeQuery::testOctant(const BoundingBox& box, unsigned& mask) const
{
    return box.isInside(mPoint);
}

Intersection PointOctreeQuery::testNode(const BoundingBox& box, unsigned& mask) const
{
    return box.isInside(mPoint);
}

Intersection SphereOctreeQuery::testOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mSphere.isInside(box);
}

Intersection SphereOctreeQuery::testNode(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mSphere.isInsideFast(box);
}

Intersection BoxOctreeQuery::testOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mBox.isInside(box);
}

Intersection BoxOctreeQuery::testNode(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mBox.isInsideFast(box);
}

Intersection FrustumOctreeQuery::testOctant(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mFrustum.isInsideMasked(box, mask);
}

Intersection FrustumOctreeQuery::testNode(const BoundingBox& box, unsigned& mask) const
{
    if (mask == M_MAX_UNSIGNED)
        return INSIDE;
    
    return mFrustum.isInsideFastMasked(box, mask);
}

Intersection OccludedFrustumOctreeQuery::testOctant(const BoundingBox& box, unsigned& mask) const
{
    // First check the frustum
    Intersection frustumRes = INSIDE;
    if (mask != M_MAX_UNSIGNED)
    {
        frustumRes = mFrustum.isInsideMasked(box, mask);
        if (frustumRes == OUTSIDE)
            return OUTSIDE;
    }
    
    // Then check occlusion
    if (mBuffer->isVisible(box))
        return frustumRes;
    else
        return OUTSIDE;
}

Intersection OccludedFrustumOctreeQuery::testNode(const BoundingBox& box, unsigned& mask) const
{
    // First check the frustum
    if (mask != M_MAX_UNSIGNED)
    {
        if (mFrustum.isInsideFastMasked(box, mask) == OUTSIDE)
            return OUTSIDE;
    }
    
    // Then check occlusion
    if (mBuffer->isVisible(box))
        return INSIDE;
    else
        return OUTSIDE;
}
