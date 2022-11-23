// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

namespace Urho3D
{

/// A link between otherwise unconnected regions of the navigation mesh.
class URHO3D_API OffMeshConnection : public Component
{
    URHO3D_OBJECT(OffMeshConnection, Component);

public:
    /// Construct.
    explicit OffMeshConnection(Context* context);
    /// Destruct.
    ~OffMeshConnection() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set endpoint node.
    /// @property
    void SetEndPoint(Node* node);
    /// Set radius.
    /// @property
    void SetRadius(float radius);
    /// Set bidirectional flag. Default true.
    /// @property
    void SetBidirectional(bool enabled);
    /// Set a user assigned mask.
    /// @property
    void SetMask(unsigned newMask);
    /// Sets the assigned area Id for the connection.
    /// @property
    void SetAreaID(unsigned newAreaID);

    /// Return endpoint node.
    /// @property
    Node* GetEndPoint() const;

    /// Return radius.
    /// @property
    float GetRadius() const { return radius_; }

    /// Return whether is bidirectional.
    /// @property
    bool IsBidirectional() const { return bidirectional_; }

    /// Return the user assigned mask.
    /// @property
    unsigned GetMask() const { return mask_; }

    /// Return the user assigned area ID.
    /// @property
    unsigned GetAreaID() const { return areaId_; }

private:
    /// Mark end point dirty.
    void MarkEndPointDirty() { endPointDirty_ = true; }
    /// Endpoint node.
    WeakPtr<Node> endPoint_;
    /// Endpoint node ID.
    unsigned endPointID_;
    /// Radius.
    float radius_;
    /// Bidirectional flag.
    bool bidirectional_;
    /// Endpoint changed flag.
    bool endPointDirty_;
    /// Flags mask to represent properties of this mesh.
    unsigned mask_;
    /// Area id to be used for this off mesh connection's internal poly.
    unsigned areaId_;
};

}
