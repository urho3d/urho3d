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
#include "OctreeQuery.h"
#include "DebugNew.h"

Intersection PointOctreeQuery::TestOctant(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return box.IsInside(point_);
    else
        return INSIDE;
}

Intersection PointOctreeQuery::TestDrawable(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return box.IsInside(point_);
    else
        return INSIDE;
}

Intersection SphereOctreeQuery::TestOctant(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return sphere_.IsInside(box);
    else
        return INSIDE;
}

Intersection SphereOctreeQuery::TestDrawable(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return sphere_.IsInsideFast(box);
    else
        return INSIDE;
}

Intersection BoxOctreeQuery::TestOctant(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return box_.IsInside(box);
    else
        return INSIDE;
}

Intersection BoxOctreeQuery::TestDrawable(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return box_.IsInsideFast(box);
    else
        return INSIDE;
}

Intersection FrustumOctreeQuery::TestOctant(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return frustum_.IsInside(box);
    else
        return INSIDE;
}

Intersection FrustumOctreeQuery::TestDrawable(const BoundingBox& box, bool inside) const
{
    if (!inside)
        return frustum_.IsInsideFast(box);
    else
        return INSIDE;
}
