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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "Skybox.h"

OBJECTTYPESTATIC(Skybox);

Skybox::Skybox(Context* context) :
    StaticModel(context)
{
}

Skybox::~Skybox()
{
}

void Skybox::RegisterObject(Context* context)
{
    context->RegisterFactory<Skybox>();
    context->CopyBaseAttributes<StaticModel, Skybox>();
}

void Skybox::UpdateDistance(const FrameInfo& frame)
{
    distance_ = 0.0f;
}

void Skybox::GetBatch(const FrameInfo& frame, unsigned batchIndex, Batch& batch)
{
    // Follow only the camera rotation, not position
    Matrix3x4 customView(Vector3::ZERO, frame.camera_->GetWorldRotation().Inverse(), Vector3::UNITY);
    customWorldTransform_ = customView * GetWorldTransform();
    
    batch.geometry_ = geometries_[batchIndex][lodLevels_[batchIndex]];
    batch.worldTransform_ = &customWorldTransform_;
    batch.overrideView_ = true;
    batch.material_ = materials_[batchIndex];
}

void Skybox::OnWorldBoundingBoxUpdate()
{
    // The skybox is supposed to be visible everywhere, so set a humongous bounding box
    worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
}
