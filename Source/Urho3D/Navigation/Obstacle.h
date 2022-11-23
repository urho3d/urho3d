// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Ptr.h"
#include "../Scene/Component.h"

namespace Urho3D
{

class DynamicNavigationMesh;

/// Obstacle for dynamic navigation mesh.
class URHO3D_API Obstacle : public Component
{
    URHO3D_OBJECT(Obstacle, Component);

    friend class DynamicNavigationMesh;

public:
    /// Construct.
    explicit Obstacle(Context* context);
    /// Destruct.
    ~Obstacle() override;

    /// Register Obstacle with engine context.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Update the owning mesh when enabled status has changed.
    void OnSetEnabled() override;

    /// Get the height of this obstacle.
    /// @property
    float GetHeight() const { return height_; }

    /// Set the height of this obstacle.
    /// @property
    void SetHeight(float newHeight);

    /// Get the blocking radius of this obstacle.
    /// @property
    float GetRadius() const { return radius_; }

    /// Set the blocking radius of this obstacle.
    /// @property
    void SetRadius(float newRadius);

    /// Get the internal obstacle ID.
    /// @property{get_obstacleId}
    unsigned GetObstacleID() const { return obstacleId_; }

    /// Render debug information.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;
    /// Simplified rendering of debug information for script usage.
    void DrawDebugGeometry(bool depthTest);

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle scene being assigned, identify our DynamicNavigationMesh.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Handle navigation mesh tile added.
    void HandleNavigationTileAdded(StringHash eventType, VariantMap& eventData);

private:
    /// Radius of this obstacle.
    float radius_;
    /// Height of this obstacle, extends 1/2 height below and 1/2 height above the owning node's position.
    float height_;

    /// Id received from tile cache.
    unsigned obstacleId_;
    /// Pointer to the navigation mesh we belong to.
    WeakPtr<DynamicNavigationMesh> ownerMesh_;
};

}
