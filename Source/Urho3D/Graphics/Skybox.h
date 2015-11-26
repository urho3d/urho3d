//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Graphics/StaticModel.h"

namespace Urho3D
{

/// Static model component with fixed position in relation to the camera.
class URHO3D_API Skybox : public StaticModel
{
    URHO3D_OBJECT(Skybox, StaticModel);

public:
    /// Construct.
    Skybox(Context* context);
    /// Destruct.
    virtual ~Skybox();
    /// Register object factory. StaticModel must be registered first.
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);

protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();

    /// Custom world transform per camera.
    HashMap<Camera*, Matrix3x4> customWorldTransforms_;
    /// Last frame counter for knowing when to erase the custom world transforms of previous frame.
    unsigned lastFrame_;
};

}
