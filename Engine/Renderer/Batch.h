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

#ifndef RENDERER_BATCH_H
#define RENDERER_BATCH_H

#include "RendererDefs.h"

class Camera;
class Geometry;
class Light;
class MaterialTechnique;
class MaterialPass;
class PixelShader;
class Renderer;
class VertexShader;
class VolumeNode;

//! Describes a draw call
class Batch
{
public:
    //! Construct with defaults
    Batch() :
        mHasPriority(false),
        mTechnique(0),
        mPass(0),
        mBatchIndex(0),
        mForwardLight(0)
    {
    }
    
    //! Calculate state/distance sorting key
    void calculateSortKey(bool stateHasPriority, bool frontToBack);
    //! Draw
    void draw(Renderer* renderer) const;
    
    //! Scene node
    VolumeNode* mNode;
    //! Camera
    Camera* mCamera;
    //! Geometry
    Geometry* mGeometry;
    //! Scene node batch (geometry within node) index
    unsigned mBatchIndex;
    //! Material technique
    MaterialTechnique* mTechnique;
    //! Material pass
    MaterialPass* mPass;
    //! Vertex shader
    VertexShader* mVertexShader;
    //! Pixel shader
    PixelShader* mPixelShader;
    //! Light in forward rendering
    Light* mForwardLight;
    //! Priority flag
    bool mHasPriority;
    //! Distance from camera
    float mDistance;
    //! Sorting key
    unsigned long long mSortKey;
};

//! Compare sorting keys of two batches
static bool compareBatches(const Batch* lhs, const Batch* rhs)
{
    return lhs->mSortKey > rhs->mSortKey;
}

#endif // RENDERER_BATCH_H
