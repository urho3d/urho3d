//
// Copyright (c) 2008-2016 the Urho3D project.
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

class Context;
class DebugRenderer;
class GravityVector;
class GravityHull;
class GravityMesh;


/*!
 * @brief Provides an interface to query the scene for gravitational data.
 *
 * This class manages all of the gravity probes in the scene. A probe
 * defines a (normalized) gravitational direction and a multiplication factor
 * for a specific location in 3D world space. Multiple probes can be placed
 * in the scene at different locations to change the gravity of physics
 * objects.
 *
 * The final gravitational force is a combination of the global gravitational
 * force (defined by this class) and a resulting interpolated vector from
 * nearby gravity probes.
 */
class URHO3D_API GravityManager : public Component
{
    URHO3D_OBJECT(GravityManager, Component)

public:

    enum Strategy
    {
        TETRAHEDRAL_MESH,
        SHORTEST_DISTANCE,
        DISABLE
    };

    /*!
     * @brief Creates a new gravity component.
     */
    GravityManager(Context* context);

    /*!
     * @brief Destructs the gravity component.
     */
    virtual ~GravityManager();

    /*!
     * @brief Registers this class as an object factory.
     */
    static void RegisterObject(Context* context);

    /*!
     * @brief This is the global gravitational force. It is multiplied with the
     * individual gravity probe forces to yield the final gravitational force.
     * @param[in] acceleration Gravitational constant, in m/s^2.
     */
    void SetGlobalGravity(float acceleration)
            { gravity_ = acceleration; }

    float GetGlobalGravity() const
            { return gravity_; }

    void SetStrategy(Strategy strategy)
            { strategy_ = strategy; }

    /*!
     * @brief Queries all gravity probes and calculates the effective
     * gravitational force at the specified location in world space.
     * @param[in] worldLocation A 3D location in world space.
     * @return Returns the gravitational force at the specified location.
     */
    Vector3 QueryGravity(Vector3 worldLocation);

    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest, Vector3 pos);

private:
    void RebuildTetrahedralMesh();

    /// Triggers a new search for all gravity probe nodes and rebuilds the tetrahedral mesh
    virtual void OnSceneSet(Scene* scene);

    /*!
     * @brief Searches for all gravity probe nodes that are located beneath the
     * specified node and caches them. The specified node is not checked.
     */
    void AddGravityVectorsRecursively(Node* node);

    /*!
     * @brief Searches for all gravity probe nodes that are located on and
     * beneath the specified node.
     */
    void RemoveGravityVectorsRecursively(Node* node);

    void HandleComponentAdded(StringHash eventType, VariantMap& eventData);
    void HandleComponentRemoved(StringHash eventType, VariantMap& eventData);
    void HandleNodeAdded(StringHash eventType, VariantMap& eventData);
    void HandleNodeRemoved(StringHash eventType, VariantMap& eventData);

    PODVector<GravityVector*> gravityVectors_;
    SharedPtr<GravityMesh> gravityMesh_;
    SharedPtr<GravityHull> gravityHull_;

    float gravity_;

    Strategy strategy_;
};

} // namespace Urho3D
