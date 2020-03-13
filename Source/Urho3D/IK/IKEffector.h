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
#include "../Scene/Scene.h"

using ik_node_t = struct ik_node_t;

namespace Urho3D
{

class Context;
class IKSolver;

class URHO3D_API IKEffector : public Component
{
    URHO3D_OBJECT(IKEffector, Component)

public:

    enum Feature
    {

        /*!
         * If you set the effector weight (see SetWeight()) to a value in
         * between 0 and 1, the default behaviour is to linearly interpolate
         * the effector's target position. If the solved tree and the initial
         * tree are far apart, this can look very strange, especially if you
         * are controlling limbs on a character that are designed to rotation.
         * Enabling this causes a rotational based interpolation (nlerp) around
         * the chain's base node and makes transitions look much more natural.
         */
        WEIGHT_NLERP = 0x01,

        /*!
         * By default the end effector node will retain its global orientation,
         * even after solving. By enabling this feature, the node will instead
         * "rotate with" its parent node.
         */
        INHERIT_PARENT_ROTATION = 0x02
    };

    /// Constructs a new IK effector.
    explicit IKEffector(Context* context);

    /// Destructs he IK effector.
    ~IKEffector() override;

    /// Registers this class as an object factory.
    static void RegisterObject(Context* context);

    /// Test if a certain feature is enabled (see IKEffector::Feature).
    bool GetFeature(Feature feature) const;
    /// Enable or disable a certain feature (see IKEffector::Feature).
    void SetFeature(Feature feature, bool enable);

    /// Retrieves the node that is being used as a target. Can be NULL.
    Node* GetTargetNode() const;

    /*!
     * @brief The position of the target node provides the target position of
     * the effector node.
     *
     * The IK chain is solved such that the node to which this component is
     * attached to will try to move to the position of the target node.
     * @param targetNode A scene node that acts as a target. Specifying NULL
     * will erase the target and cause the solver to ignore this chain.
     * @note You will get very strange behaviour if you specify a target node
     * that is part the IK chain being solved for (circular dependency). Don't
     * do that.
     */
    void SetTargetNode(Node* targetNode);

    /*!
     * @brief Retrieves the name of the target node. The node doesn't
     * necessarily have to exist in the scene graph.
     */
    const String& GetTargetName() const;

    /*!
     * @brief Sets the name of the target node. The node doesn't necessarily
     * have to exist in the scene graph. When a node is created that matches
     * this name, it is selected as the target.
     * @note This clears the existing target node.
     */
    void SetTargetName(const String& nodeName);

    /// Returns the current target position in world space.
    const Vector3& GetTargetPosition() const;
    /// Sets the current target position. If the effector has a target node then this will have no effect.
    void SetTargetPosition(const Vector3& targetPosition);

    /// Gets the current target rotation in world space.
    const Quaternion& GetTargetRotation() const;
    /// Sets the current target rotation. If the effector has a target node then this will have no effect.
    void SetTargetRotation(const Quaternion& targetRotation);

    /// Required for the editor, get the target rotation in euler angles.
    Vector3 GetTargetRotationEuler() const;
    /// Required for the editor, sets the target rotation in euler angles.
    void SetTargetRotationEuler(const Vector3& targetRotation);

    /// Returns the number of segments that will be affected by this effector. 0 Means all nodes between this effector and the next IKSolver.
    unsigned GetChainLength() const;
    /// Sets the number of segments that will be affected. 0 Means all nodes between this effector and the next IKSolver.
    void SetChainLength(unsigned chainLength);

    /// How strongly the effector affects the solution.
    float GetWeight() const;

    /*!
     * @brief Sets how much influence the effector has on the solution.
     *
     * You can use this value to smoothly transition between a solved pose and
     * an initial pose  For instance, lifting a foot off of the ground or
     * letting go of an object.
     */
    void SetWeight(float weight);

    /// How strongly the target node's rotation influences the solution.
    float GetRotationWeight() const;

    /*!
     * @brief Sets how much influence the target rotation should have on the
     * solution. A value of 1 means to match the target rotation exactly, if
     * possible. A value of 0 means to not match it at all.
     * @note The solver must have target rotation enabled for this to have
     * any effect. See IKSolver::Feature::TARGET_ROTATIONS.
     */
    void SetRotationWeight(float weight);

    /// Retrieves the rotation decay factor. See SetRotationDecay() for info.
    float GetRotationDecay() const;

    /*!
     * @brief A factor with which to control the target rotation influence of
     * the next segments down the chain.
     *
     * For example, if this is set to 0.5 and the rotation weight is set to
     * 1.0, then the first segment will match the target rotation exactly, the
     * next segment will match it only 50%, the next segment 25%, the next
     * 12.5%, etc. This parameter makes long chains look more natural when
     * matching a target rotation.
     */
    void SetRotationDecay(float decay);

    void DrawDebugGeometry(bool depthTest);
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

private:
    friend class IKSolver;

    /// Intended to be used only by IKSolver.
    void SetIKSolver(IKSolver* solver);
    /// Intended to be used only by IKSolver.
    void SetIKEffectorNode(ik_node_t* effectorNode);
    /// Intended to be used by IKSolver. Copies the positions/rotations of the target node into the effector.
    void UpdateTargetNodePosition();

public:
    /// Need these wrapper functions flags of GetFeature/SetFeature can be correctly exposed to the editor and to AngelScript and lua.
    bool GetWEIGHT_NLERP() const;
    bool GetINHERIT_PARENT_ROTATION() const;
    void SetWEIGHT_NLERP(bool enable);
    void SetINHERIT_PARENT_ROTATION(bool enable);

private:
    WeakPtr<Node> targetNode_;
    WeakPtr<IKSolver> solver_;
    ik_node_t* ikEffectorNode_;

    String targetName_;
    Vector3 targetPosition_;
    Quaternion targetRotation_;
    unsigned chainLength_;
    float weight_;
    float rotationWeight_;
    float rotationDecay_;
    unsigned features_;
};

} // namespace Urho3D
