//
// Copyright (c) 2008-2020 the Urho3D project.
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
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set endpoint node.
    void SetEndPoint(Node* node);
    /// Set radius.
    void SetRadius(float radius);
    /// Set bidirectional flag. Default true.
    void SetBidirectional(bool enabled);
    /// Set a user assigned mask
    void SetMask(unsigned newMask);
    /// Sets the assigned area Id for the connection
    void SetAreaID(unsigned newAreaID);

    /// Return endpoint node.
    Node* GetEndPoint() const;

    /// Return radius.
    float GetRadius() const { return radius_; }

    /// Return whether is bidirectional.
    bool IsBidirectional() const { return bidirectional_; }

    /// Return the user assigned mask
    unsigned GetMask() const { return mask_; }

    /// Return the user assigned area ID
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
    /// Flags mask to represent properties of this mesh
    unsigned mask_;
    /// Area id to be used for this off mesh connection's internal poly
    unsigned areaId_;
};

}
