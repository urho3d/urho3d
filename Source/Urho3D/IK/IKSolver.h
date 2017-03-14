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

#include "../IK/IKEffector.h"
#include "../Scene/Component.h"

struct ik_solver_t;
struct ik_node_t;

namespace Urho3D
{
class AnimationState;

/*!
 * @brief Marks the root or "beginning" of an IK chain or multiple IK chains.
 * The solving algorithm can be set along with other solver related parameters.
 * The IK problem is solved starting from the node this component is attached
 * to and ending at all nodes that have an IKEffector component attached.
 */
class IKSolver : public Component
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
     * The default value is 50.
     *
     * @note Most algorithms have a convergence criteria at which the solver
     * will stop iterating, so most of the time the maximum number of
     * iterations isn't even reached.
     *
     * @param iterations Number of iterations. Must be greater than 0. Higher
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

    bool DoCalculateFinalAngles() const;
    void SetCalculateFinalAngles(bool enable);

    bool DoSkipReset() const;
    void SetSkipReset(bool enable);

    /// Causes the solver tree to be rebuilt before solving the next time.
    void MarkSolverTreeDirty();

    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

private:
    virtual void OnNodeSet(Node* scene);
    /// Causes the entire tree to be rebuilt
    void RebuildTree();
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
};

} // namespace Urho3D
