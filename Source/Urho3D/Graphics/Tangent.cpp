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

#include "../Graphics/Tangent.h"
#include "../Math/Vector4.h"

namespace Urho3D
{

inline unsigned GetIndex(void*& indexPointer, unsigned indexSize)
{
    if (indexSize == sizeof(unsigned short))
    {
        unsigned short*& p = (unsigned short*&)indexPointer;
        return *p++;
    }
    else
    {
        unsigned*& p = (unsigned*&)indexPointer;
        return *p++;
    }
}

void GenerateTangents(void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart,
    unsigned indexCount, unsigned normalOffset, unsigned texCoordOffset, unsigned tangentOffset)
{
    // Tangent generation from
    // http://www.terathon.com/code/tangent.html
    unsigned minVertex = M_MAX_UNSIGNED;
    unsigned maxVertex = 0;
    unsigned char* vertices = (unsigned char*)vertexData;
    
    void* indexPointer = const_cast<void*>(indexData);
    for (unsigned i = indexStart; i < indexStart + indexCount; ++i)
    {
        unsigned v = GetIndex(indexPointer, indexSize);
        if (v < minVertex)
            minVertex = v;
        if (v > maxVertex)
            maxVertex = v;
    }
    
    unsigned vertexCount = maxVertex + 1;
    Vector3 *tan1 = new Vector3[vertexCount * 2];
    Vector3 *tan2 = tan1 + vertexCount;
    memset(tan1, 0, sizeof(Vector3) * vertexCount * 2);
    
    indexPointer = const_cast<void*>(indexData);
    for (unsigned i = indexStart; i < indexStart + indexCount; i += 3)
    {
        unsigned i1 = GetIndex(indexPointer, indexSize);
        unsigned i2 = GetIndex(indexPointer, indexSize);
        unsigned i3 = GetIndex(indexPointer, indexSize);
        
        const Vector3& v1 = *((Vector3*)(vertices + i1 * vertexSize));
        const Vector3& v2 = *((Vector3*)(vertices + i2 * vertexSize));
        const Vector3& v3 = *((Vector3*)(vertices + i3 * vertexSize));
        
        const Vector2& w1 = *((Vector2*)(vertices + i1 * vertexSize + texCoordOffset));
        const Vector2& w2 = *((Vector2*)(vertices + i2 * vertexSize + texCoordOffset));
        const Vector2& w3 = *((Vector2*)(vertices + i3 * vertexSize + texCoordOffset));
        
        float x1 = v2.x_ - v1.x_;
        float x2 = v3.x_ - v1.x_;
        float y1 = v2.y_ - v1.y_;
        float y2 = v3.y_ - v1.y_;
        float z1 = v2.z_ - v1.z_;
        float z2 = v3.z_ - v1.z_;
        
        float s1 = w2.x_ - w1.x_;
        float s2 = w3.x_ - w1.x_;
        float t1 = w2.y_ - w1.y_;
        float t2 = w3.y_ - w1.y_;
        
        float r = 1.0f / (s1 * t2 - s2 * t1);
        Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                (t2 * z1 - t1 * z2) * r);
        Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                (s1 * z2 - s2 * z1) * r);
        
        tan1[i1] += sdir;
        tan1[i2] += sdir;
        tan1[i3] += sdir;
        
        tan2[i1] += tdir;
        tan2[i2] += tdir;
        tan2[i3] += tdir;
    }
    
    for (unsigned i = minVertex; i <= maxVertex; i++)
    {
        const Vector3& n = *((Vector3*)(vertices + i * vertexSize + normalOffset));
        const Vector3& t = tan1[i];
        Vector3 xyz;
        float w;
        
        // Gram-Schmidt orthogonalize
        xyz = (t - n * n.DotProduct(t)).Normalized();
        
        // Calculate handedness
        w = n.CrossProduct(t).DotProduct(tan2[i]) < 0.0f ? -1.0f : 1.0f;
        
        Vector4& tangent = *((Vector4*)(vertices + i * vertexSize + tangentOffset));
        tangent = Vector4(xyz, w);
    }
    
    delete[] tan1;
}

}
