// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    explicit Skybox(Context* context);
    /// Destruct.
    ~Skybox() override;
    /// Register object factory. StaticModel must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;

protected:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;

    /// Custom world transform per camera.
    HashMap<Camera*, Matrix3x4> customWorldTransforms_;
    /// Last frame counter for knowing when to erase the custom world transforms of previous frame.
    unsigned lastFrame_;
};

}
