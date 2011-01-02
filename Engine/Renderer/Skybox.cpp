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
#include "Camera.h"
#include "Skybox.h"

Skybox::Skybox(Octant* octant, const std::string& name) :
    StaticModel(NODE_SKYBOX, octant, name)
{
}

void Skybox::updateDistance(const FrameInfo& frame)
{
    mDistance = 0.0f;
}

void Skybox::overrideTransforms(unsigned batchIndex, Camera& camera, const Matrix4x3** model, const Matrix4x3** view)
{
    static Matrix4x3 overrideView;
    // Follow only the camera rotation, not position
    overrideView.define(Vector3::sZero, camera.getWorldRotation().getInverse(), Vector3::sUnity);
    *view = &overrideView;
}

void Skybox::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    // The skybox is supposed to be visible everywhere, so set a humongous bounding box
    worldBoundingBox.define(-M_LARGE_VALUE, M_LARGE_VALUE);
}
