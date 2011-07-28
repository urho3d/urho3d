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
#include "Ray.h"

Vector3 Ray::Project(const Vector3& point) const
{
    Vector3 offset = point - origin_;
    return origin_ + offset.DotProduct(direction_) * direction_;
}

float Ray::Distance(const Vector3& v0, const Vector3& v1, const Vector3& v2) const
{
    // Based on Fast, Minimum Storage Ray/Triangle Intersection by Möller & Trumbore
    // http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
    // Calculate edge vectors
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;
    
    // Calculate determinant & check backfacing
    Vector3 p = direction_.CrossProduct(edge2);
    float det = edge1.DotProduct(p);
    if (det >= M_EPSILON)
    {
        // Calculate u & v parameters and test
        Vector3 t = origin_ - v0;
        float u = t.DotProduct(p);
        if (u >= 0.0f && u <= det)
        {
            Vector3 q = t.CrossProduct(edge1);
            float v = direction_.DotProduct(q);
            if (v >= 0.0f && u + v <= det)
            {
                // There is an intersection, so calculate distance
                return edge2.DotProduct(q) / det;
            }
        }
    }
    
    return M_INFINITY;
}

float Ray::Distance(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) const
{
    float nearest = M_INFINITY;
    const unsigned char* vertices = (const unsigned char*)vertexData;
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = (const unsigned short*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            const Vector3& v0 = *((const Vector3*)(&vertices[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertices[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertices[indices[i + 2] * vertexSize]));
            nearest = Min(nearest, Distance(v0, v1, v2));
        }
    }
    // 32-bit indices
    else
    {
        const unsigned* indices = (const unsigned*)indexData;
        
        for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
        {
            const Vector3& v0 = *((const Vector3*)(&vertices[indices[i] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&vertices[indices[i + 1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&vertices[indices[i + 2] * vertexSize]));
            nearest = Min(nearest, Distance(v0, v1, v2));
        }
    }
    
    return nearest;
}
