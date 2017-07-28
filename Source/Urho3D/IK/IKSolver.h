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
        ONE_BONE = 0,
        TWO_BONE,
        FABRIK
        /* not implemented yet
        MSD,
        JACOBIAN_INVERSE,
        JACOBIAN_TRANSPOSE*/
    };

    enum Feature
    {
        /*!
         * @brief Should be enabled if your model uses skinning or if you are
         * generally interested in correct joint rotations. Has a minor
         * performance impact.
         *
         * When enabled, final joint rotations are calculated as a post
         * processing step. If you are using IK on a model with skinning, you will
         * want to enable this or it will look wrong. If you disable this, then
         * you will get a slight performance boost (less calculations are required)
         * but only the node positions are updated. This can be useful for scene
         * IK (perhaps a chain of platforms, where each platform should retain its
         * initial world rotation?)
         */
        JOINT_ROTATIONS = 0x01,

        /*!
         * @brief When enabled, the effector will try to match the target's
         * rotation as well as the effectors position. When disabled, the target
         * node will reach the effector with any rotation necessary.
         *
         * If the target position goes out of range of the effector then the
         * rotation will no longer be matched. The chain will try to reach out to
         * reach the target position, even if it means rotating towards it.
         */
        TARGET_ROTATIONS = 0x02,

        /*!
         * When the solver is first initialized, it will copy the positions
         * and rotations of the current Urho3D scene graph into an internal
         * structure. This is referred to as the "original pose" and will by
         * default never change for the duration of the solver's life cycle.
         * When the solver is destroyed, the original pose is applied back to
         * Urho3D's scene graph so the nodes are restored to whatever they were
         * before the solver was created.
         *
         * By enabling UPDATE_ORIGINAL_POSE, the original pose will be updated
         * right before solving to reflect the current Urho3D scene graph. As
         * a consequence, there will no longer be an original pose to restore
         * when the solver is destroyed.
         *
         * When disabled, the original pose will remain unmodified. The original
         * pose is set when the solver is first created. You can manually update the
         * original pose at any time by calling UpdateInitialPose().
         */
        UPDATE_ORIGINAL_POSE = 0x04,

        /*!
         * @brief Should be enabled if you are using IK on an animated model,
         * along with disabling USE_ORIGINAL_POSE.
         *
         * The "active pose" has two purposes: The solver uses it as the
         * initial tree to derive a solution from, and at the same time uses it
         * to store the solution into. Thus, the typical solving process is:
         *   1) The active pose needs to be updated to reflect a preferred
         *      initial condition (such as the current frame of animation)
         *   2) Call Solve()
         *   3) The active pose now holds the solution, so it must be applied
         *      back to the Urho3D scene graph.
         *
         * When enabled, the active pose is updated right before solving to
         * reflect the current state of the Urho3D scene graph.
         *
         * When disabled, the active pose will simply remain as it was since
         * the last time Solve() was called.
         *
         * @note This option conflicts with USE_ORIGINAL_POSE. Make sure to
         * disable USE_ORIGINAL_POSE if you enable this feature.
         */
        UPDATE_ACTIVE_POSE = 0x08,

        /*!
         * @brief Choose between using the original pose or the active pose as
         * a basis for a solution.
         *
         * When enabled, the solver will copy the original pose
         * (see UPDATE_ORIGINAL_POSE) into the active pose before solving (and
         * thus use the original pose as a basis for a solution).
         *
         * @note This option conflicts with UPDATE_ACTIVE_POSE. If you enable
         * this feature, make sure to disable UPDATE_ACTIVE_POSE.
         *
         * If both UPDATE_ACTIVE_POSE and USE_ORIGINAL_POSE are disabled, then
         * the solver will use the previously solved tree as a basis for the new
         * calculation. The result is a more "continuous" solution that unfolds
         * over time. This can be useful if you want to simulate chains or
         * something similar.
         */
        USE_ORIGINAL_POSE = 0x10,

        /*!
         * Due to the somewhat unfortunate performance impacts, the solver
         * does not enable constraints by default. Enabling constraints causes
         * the solver's tree to be written to and from Urho3D's scene graph every
         * iteration, while calling ApplyConstraints(). Disabling constraints means
         * ApplyConstraints() is never called.
         */
        CONSTRAINTS = 0x20,

        /*!
         * Mostly exists because of the editor. When enabled, the solver
         * will be invoked automatically for you. If you need to do additional
         * calculations before being able to set the effector target data, you will
         * want to disable this and call Solve() manually.
         */
        AUTO_SOLVE = 0x40
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
     * @brief Selects the solver algorithm. Default is FABRIK. Note that this
     * may not be the most efficient algorithm available. The specialized
     * solvers will be a lot faster.
     *
     * The currently supported solvers are listed below.
     *   + **FABRIK**: This is a fairly new and highly efficient inverse
     *     kinematic solving algorithm. It requires the least iterations to
     *     reach its goal, it does not suffer from singularities (nearly no
     *     violent snapping about), and it always converges.
     *   + **2 Bone**: A specialized solver optimized for 2 bone problems (such
     *     as a human leg)
     *   + **1 Bone**: A specialized solver optimized for 1 bone problems (such
     *     as a look-at target, e.g. eyes or a head)
     */
    void SetAlgorithm(Algorithm algorithm);

    bool GetFeature(Feature feature) const;
    void SetFeature(Feature feature, bool enable);

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

    /*!
     * @brief Updates the solver's internal data structures, which is required
     * whenever the tree is modified in any way (e.g. adding or removing nodes,
     * adding or removing effectors, etc.).
     * @note This gets called  automatically for you in Solve().
     */
    void RebuildData();

    /*!
     * @brief Unusual, but if you have a tree with translational motions such
     * that the distances between nodes changes (perhaps a slider?), you can
     * call this to recalculate the segment lengths after assigning new
     * positions to the nodes.
     * @note This function gets called by RebuildData() and by extension in
     * Solve().
     */
    void RecalculateSegmentLengths();

    /*!
     * @brief Skinned models require joint rotations to be calculated so
     * skinning works correctly. This is automatically enabled by default with
     * the feature flag JOINT_ROTATIONS.
     */
    void CalculateJointRotations();

    /*!
     * @brief Invokes the solver. The solution is applied back to the scene
     * graph automatically.
     * @note By default this is called automatically for you if the feature
     * flag AUTO_SOLVE is set. For more complex IK problems you can disable
     * that flag and call Solve() in response to E_SCENEDRAWABLEUPDATEFINISHED.
     * This is right after the animations have been applied.
     */
    void Solve();

    /*!
     * @brief Causes the initial tree to be applied back to Urho3D's scene
     * graph. This is what gets called when continuous solving is disabled.
     */
    void ApplyOriginalPoseToScene();

    /*!
     * @brief Causes the current scene graph data to be copied into the solvers
     * initial pose. This should generally be called before solving if you
     * are using IK on an animated model. If you don't update the initial pose,
     * then the result will be a "continuous solution", where the solver will
     * use the previously calculated tree as a basis for the new solution.
     *
     * @note This is
     */
    void ApplySceneToOriginalPose();
    void ApplyActivePoseToScene();
    void ApplySceneToActivePose();
    void ApplyOriginalPoseToActivePose();

    void DrawDebugGeometry(bool depthTest);
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

private:
    friend class IKEffector;

    /// Causes the solver tree to be rebuilt before solving the next time. Intended to be used by IKEffector.
    void MarkSolverTreeDirty();
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

    /// Need these wrapper functions flags of GetFeature/SetFeature can be correctly exposed to the editor
    bool GetFeature_JOINT_ROTATIONS() const;
    bool GetFeature_TARGET_ROTATIONS() const;
    bool GetFeature_UPDATE_ORIGINAL_POSE() const;
    bool GetFeature_UPDATE_ACTIVE_POSE() const;
    bool GetFeature_USE_ORIGINAL_POSE() const;
    bool GetFeature_CONSTRAINTS() const;
    bool GetFeature_AUTO_SOLVE() const;

    void SetFeature_JOINT_ROTATIONS(bool enable);
    void SetFeature_TARGET_ROTATIONS(bool enable);
    void SetFeature_UPDATE_ORIGINAL_POSE(bool enable);
    void SetFeature_UPDATE_ACTIVE_POSE(bool enable);
    void SetFeature_USE_ORIGINAL_POSE(bool enable);
    void SetFeature_CONSTRAINTS(bool enable);
    void SetFeature_AUTO_SOLVE(bool enable);

    PODVector<IKEffector*> effectorList_;
    PODVector<IKConstraint*> constraintList_;
    ik_solver_t* solver_;
    Algorithm algorithm_;
    unsigned features_;
    bool solverTreeNeedsRebuild_;
};

} // namespace Urho3D
