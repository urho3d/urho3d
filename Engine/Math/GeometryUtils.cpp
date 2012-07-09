//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "GeometryUtils.h"
#include "Plane.h"

inline void ClipEdge(float* output, float* v0, float* v1, float d0, float d1, unsigned components, unsigned blendWeightsComp)
{
    float t = d0 / (d0 - d1);
    
    if (!blendWeightsComp)
    {
       for (unsigned i = 0; i < components; ++i)
            output[i] = v0[i] + t * (v1[i] - v0[i]);
    }
    else
    {
        for (unsigned i = 0; i < blendWeightsComp; ++i)
            output[i] = v0[i] + t * (v1[i] - v0[i]);
        
        // Blend weights / indices can not be easily interpolated, choose the one that is nearer to the split plane
        if (Abs(d0) < Abs(d1))
        {
            for (unsigned i = blendWeightsComp; i < components; ++i)
                output[i] = v0[i];
        }
        else
        {
            for (unsigned i = blendWeightsComp; i < components; ++i)
                output[i] = v1[i];
        }
    }
}

inline void CopyVertex(float* output, float* input, unsigned components)
{
    for (unsigned i = 0; i < components; ++i)
        output[i] = input[i];
}

unsigned ClipPolygon(float* input, float* output, unsigned vertexCount, unsigned vertexSize, const Plane& plane, unsigned blendWeightsOffset, float* clip, unsigned* clipVertexCount)
{
    unsigned components = vertexSize / sizeof(float);
    unsigned blendWeightsComp = blendWeightsOffset / sizeof(float);
    unsigned outVertexCount = 0;
    float* lastVertex = input;
    float lastDistance = 0.0f;
    
    if (clipVertexCount)
        *clipVertexCount = 0;
    
    for (unsigned i = 0; i < vertexCount; ++i)
    {
        float* vertex = input + i * components;
        const Vector3& position = *((Vector3*)vertex);
        float distance = plane.Distance(position);
        if (distance >= 0.0f)
        {
            if (lastDistance < 0.0f)
            {
                ClipEdge(output, lastVertex, vertex, lastDistance, distance, components, blendWeightsComp);
                if (clip && clipVertexCount)
                {
                    CopyVertex(clip, output, components);
                    clip += components;
                    ++(*clipVertexCount);
                }
                output += components;
                ++outVertexCount;
            }
            
            for (unsigned j = 0; j < components; ++j)
                output[j] = vertex[j];
            output += components;
            ++outVertexCount;
        }
        else
        {
            if (lastDistance >= 0.0f && i != 0)
            {
                ClipEdge(output, lastVertex, vertex, lastDistance, distance, components, blendWeightsComp);
                if (clip && clipVertexCount)
                {
                    CopyVertex(clip, output, components);
                    clip += components;
                    ++(*clipVertexCount);
                }
                output += components;
                ++outVertexCount;
            }
        }
        
        lastVertex = vertex;
        lastDistance = distance;
    }
    
    // Recheck the distances of the last and first vertices and add the final clipped vertex if applicable
    {
        float* vertex = input;
        const Vector3& position = *((Vector3*)vertex);
        float distance = plane.Distance(position);
        if ((lastDistance < 0.0f && distance >= 0.0f) || (lastDistance >= 0.0f && distance < 0.0f))
        {
            ClipEdge(output, lastVertex, vertex, lastDistance, distance, components, blendWeightsComp);
            if (clip && clipVertexCount)
            {
                CopyVertex(clip, output, components);
                clip += components;
                ++(*clipVertexCount);
            }
            output += components;
            ++outVertexCount;
        }
    }
    
    return outVertexCount;
}
