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

struct ik_solver_t;
struct ik_node_t;

namespace Urho3D
{
class AnimationState;
class IKConstraint;
class IKEffector;

/*!
 * @brief Marks the root or "beginning" of an IK chain or multiple IK chains.
 * The solving algorithm can be set along with other solver related parameters.
 * The IK problem is solved starting from the node this component is attached
 * to and ending at all nodes that have an IKEffector component attached.
 */
class URHO3D_API IKSolver : public Component
{
    URHO3D_OBJECT(IKSolver, Component)

public:

    enum Algorithm
    {
        FABRIK
        /* not implemented yet
        JACOBIAN_INVERSE,
        JACOBIAN_TRANSPOSE*/
    };

    /// Construct an IK root component.
    IKSolver(Context* context);
    /// Default destructor.
    virtual ~IKSolver();
    /// Registers this class to the context.
    static void RegisterObject(Context* context);

    /// Returns the active algorithm
    Algorithm GetAlgorithm() const;

    /*!
     * @brief Selects the solver algorithm. Default is FABRIK.
     *
     * The currently supported solvers are listed below.
     *   + **FABRIK**: This is a fairly new and highly efficient inverse
     *     kinematic solving algorithm. It requires the least iterations to
     *     reach its goal, it does not suffer from singularities (nearly no
     *     violent snapping about), and it always converges.
     */
    void SetAlgorithm(Algorithm algorithm);

    /// Returns the configured maximum number of iterations.
    unsigned GetMaximumIterations() const;

    /*!
     * @brief Sets the maximum number of iterations the solver is allowed to
     * perform before applying the result.
     *
     * Depending on the algorithm, you may want higher or lower values.
     * FABRIK looks decent after only 10 iterations, whereas Jacobian based
     * methods often require more than a 100.
     *
     * The default value is 20.
     *
     * @note Most algorithms have a convergence criteria at which the solver
     * will stop iterating, so most of the time the maximum number of
     * iterations isn't even reached.
     *
     * @param[in] iterations Number of iterations. Must be greater than 0. Higher
     * values yield more accurate results, but at the cost of performance.
     */
    void SetMaximumIterations(unsigned iterations);

    /// Returns the configured tolerance.
    float GetTolerance() const;

    /*!
     * @brief Sets the distance at which the effector is "close enough" to the
     * target node, at which point the algorithm will stop iterating.
     *
     * @param tolerance The distance to set. Smaller values yield more accurate
     * results, but at the cost of more iterations. Generally you'll want to
     * specify a number that is about 1/100th to 1/1000th of the total size of
     * the IK chain, e.g. if your human character has a leg that is 1 Urho3D
     * unit long, a good starting tolerance would be 0.01.
     */
    void SetTolerance(float tolerance);

    /// Whether or not rotations should be calculated.
    bool BoneRotationsEnabled() const;

    /*!
     * @brief When enabled, final joint rotations are calculated as a post
     * processing step. If you are using IK on a model with skinning, you will
     * want to enable this or it will look wrong. If you disable this, then
     * you will get a slight performance boost (less calculations are required)
     * but only the node positions are updated. This can be useful for scene
     * IK (perhaps a chain of platforms, where each platform should retain its
     * initial world rotation?)
     */
    void EnableBoneRotations(bool enable);

    /// Whether or not target rotation is enabled
    bool TargetRotationEnabled() const;

    /*!
     * @brief When enabled, the effector will try to match the target's
     * rotation as well as the effectors position. When disabled, the target
     * node will reach the effector with any rotation necessary.
     *
     * If the target position goes out of range of the effector then the
     * rotation will no longer be matched. The chain will try to reach out to
     * reach the target position, even if it means rotating towards it.
     */
    void EnableTargetRotation(bool enable);

    /// Whether or not continuous solving is enabled or not.
    bool ContinuousSolvingEnabled() const;

    /*!
     * @brief When enabled, the solver will refrain from applying the initial
     * pose before solving. The result is that it will use the previously
     * solved tree as a basis for the new calculation instead of using the
     * initial tree. This can be useful if you want to simulate chains or
     * something similar. When disabled, the solver will use the initial
     * positions/rotations which where set when the solver was first created.
     *
     * If you call UpdateInitialPose() then the initial tree will be matched to
     * the current nodes in the scene graph.
     *
     * If you call ResetToInitialPose() then you will do the opposite of
     * UpdateInitialPose() -- the initial pose is applied back to the scene
     * graph.
     *
     * If you enable pose updating with EnableUpdatePose(), then the initial
     * tree will automatically be matched to the current nodes in the scene
     * graph.
     */
    void EnableContinuousSolving(bool enable);

    /// Whether or not the initial pose is updated for every solution
    bool UpdatePoseEnabled() const;

    /*!
     * @brief When enabled, the current Urho3D node positions and rotations in
     * the scene graph will be copied into the solver's initial tree right
     * before solving. This should generally be enabled for animated models
     * so the solver refers to the current frame of animation rather than to
     * the animation's initial pose.
     *
     * When disabled, the initial pose will remain unmodified. The initial pose
     * is set when the solver is first created. You can manually update the
     * initial pose at any time by calling UpdateInitialPose().
     */
    void EnableUpdatePose(bool enable);

    /// Whether or not the solver should be invoked automatically
    bool AutoSolveEnabled() const;

    /*!
     * @brief Mostly exists because of the editor. When enabled, the solver
     * will be invoked automatically for you. If you need to do additional
     * calculations before being able to set the effector target data, you will
     * want to disable this and call Solve() manually.
     */
    void EnableAutoSolve(bool enable);

    /*!
     * @brief Invokes the solver. The solution is applied back to the scene
     * graph automatically.
     * @note You will want to register to E_SCENEDRAWABLEUPDATEFINISHED and
     * call this method there. This is right after the animations have been
     * applied.
     */
    void Solve();

    /*!
     * @brief Causes the initial tree to be applied back to Urho3D's scene
     * graph. This is what gets called when continuous solving is disabled.
     */
    void ResetToInitialPose();

    /*!
     * @brief Causes the current scene graph data to be copied into the solvers
     * initial pose. This should generally be called before solving if you
     * are using IK on an animated model. If you don't update the initial pose,
     * then the result will be a "continuous solution", where the solver will
     * use the previously calculated tree as a basis for the new solution.
     */
    void UpdateInitialPose();

    /// Causes the solver tree to be rebuilt before solving the next time.
    void MarkSolverTreeDirty();

    void DrawDebugGeometry(bool depthTest);
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

private:
    /// Subscribe to drawable update finished event here
    virtual void OnSceneSet(Scene* scene);
    /// Destroys and creates the tree
    virtual void OnNodeSet(Node* scene);

    /// Creates the ik library node and sets the current rotation/position and user data correctly.
    ik_node_t* CreateIKNode(const Node* node);

    /// Destroys the solver's tree
    void DestroyTree();
    /// Builds the solver's tree to match the scene graph's tree. If a tree already exists, it is first destroyed
    void RebuildTree();
    /// Builds a chain of nodes up to the specified node and adds an effector. Thus, the specified node must have an IKEffector attached.
    void BuildTreeToEffector(const Node* node);

    void HandleComponentAdded(StringHash eventType, VariantMap& eventData);
    void HandleComponentRemoved(StringHash eventType, VariantMap& eventData);
    void HandleNodeAdded(StringHash eventType, VariantMap& eventData);
    void HandleNodeRemoved(StringHash eventType, VariantMap& eventData);
    /// Invokes the IK solver
    void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);

    PODVector<IKEffector*> effectorList_;
    ik_solver_t* solver_;
    Algorithm algorithm_;
    bool solverTreeNeedsRebuild_;
    bool updateInitialPose_;
    bool autoSolveEnabled_;
};

} // namespace Urho3D
