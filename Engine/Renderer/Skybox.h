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

#ifndef RENDERER_SKYBOX_H
#define RENDERER_SKYBOX_H

#include "StaticModel.h"

//! A static model scene node with fixed transform in relation to the camera
class Skybox : public StaticModel
{
    DEFINE_TYPE(Skybox);
    
public:
    //! Construct with octree pointer and name
    Skybox(Octant* octant = 0, const std::string& name = std::string());
    
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Override model and view transforms for rendering
    virtual void overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view);
    
protected:
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
};

#endif // RENDERER_SKYBOX_H
