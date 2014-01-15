//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Node.h"
#include "Skybox.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

Skybox::Skybox(Context* context) :
    StaticModel(context),
    lastFrame_(0)
{
}

Skybox::~Skybox()
{
}

void Skybox::RegisterObject(Context* context)
{
    context->RegisterFactory<Skybox>(GEOMETRY_CATEGORY);

    COPY_BASE_ATTRIBUTES(Skybox, StaticModel);
}

void Skybox::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not record a raycast result for a skybox, as it would block all other results
}

void Skybox::UpdateBatches(const FrameInfo& frame)
{
    distance_ = 0.0f;

    if (frame.frameNumber_ != lastFrame_)
    {
        customWorldTransforms_.Clear();
        lastFrame_ = frame.frameNumber_;
    }

    // Follow only the camera rotation, not position
    Matrix3x4 customView(Vector3::ZERO, frame.camera_->GetNode()->GetWorldRotation().Inverse(), Vector3::ONE);
    HashMap<Camera*, Matrix3x4>::Iterator it = customWorldTransforms_.Insert(MakePair(frame.camera_, customView *
        node_->GetWorldTransform()));

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].worldTransform_ = &it->second_;
        batches_[i].distance_ = 0.0f;
        batches_[i].overrideView_ = true;
    }
}

void Skybox::OnWorldBoundingBoxUpdate()
{
    // The skybox is supposed to be visible everywhere, so set a humongous bounding box
    worldBoundingBox_.Define(-M_LARGE_VALUE, M_LARGE_VALUE);
}

}
