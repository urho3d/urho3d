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

#include "../IK/IKSolver.h"
#include "../IK/IKConstraint.h"
#include "../IK/IKEvents.h"
#include "../IK/IKEffector.h"
#include "../IK/IKConverters.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../Scene/SceneEvents.h"

#include <ik/effector.h>
#include <ik/node.h>
#include <ik/solver.h>
#include <ik/util.h>

namespace Urho3D
{

extern const char* IK_CATEGORY;

// ----------------------------------------------------------------------------
IKSolver::IKSolver(Context* context) :
    Component(context),
    solver_(nullptr),
    algorithm_(FABRIK),
    features_(AUTO_SOLVE | JOINT_ROTATIONS | UPDATE_ACTIVE_POSE),
    chainTreesNeedUpdating_(false),
    treeNeedsRebuild(true),
    solverTreeValid_(false)
{
    context_->RequireIK();

    SetAlgorithm(FABRIK);

    SubscribeToEvent(E_COMPONENTADDED,   URHO3D_HANDLER(IKSolver, HandleComponentAdded));
    SubscribeToEvent(E_COMPONENTREMOVED, URHO3D_HANDLER(IKSolver, HandleComponentRemoved));
    SubscribeToEvent(E_NODEADDED,        URHO3D_HANDLER(IKSolver, HandleNodeAdded));
    SubscribeToEvent(E_NODEREMOVED,      URHO3D_HANDLER(IKSolver, HandleNodeRemoved));
}

// ----------------------------------------------------------------------------
IKSolver::~IKSolver()
{
    // Destroying the solver tree will destroy the effector objects, so remove
    // any references any of the IKEffector objects could be holding
    for (PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
        (*it)->SetIKEffectorNode(nullptr);

    ik_solver_destroy(solver_);
    context_->ReleaseIK();
}

// ----------------------------------------------------------------------------
void IKSolver::RegisterObject(Context* context)
{
    context->RegisterFactory<IKSolver>(IK_CATEGORY);

    static const char* algorithmNames[] = {
        "1 Bone",
        "2 Bone",
        "FABRIK",
        /* not implemented,
        "MSD (Mass/Spring/Damper)",
        "Jacobian Inverse",
        "Jacobian Transpose",*/
        nullptr
    };

    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Algorithm", GetAlgorithm, SetAlgorithm, Algorithm, algorithmNames, FABRIK, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Iterations", GetMaximumIterations, SetMaximumIterations, unsigned, 20, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Convergence Tolerance", GetTolerance, SetTolerance, float, 0.001, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Joint Rotations", GetJOINT_ROTATIONS, SetJOINT_ROTATIONS, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Target Rotations", GetTARGET_ROTATIONS, SetTARGET_ROTATIONS, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update Original Pose", GetUPDATE_ORIGINAL_POSE, SetUPDATE_ORIGINAL_POSE, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update Active Pose", GetUPDATE_ACTIVE_POSE, SetUPDATE_ACTIVE_POSE, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Use Original Pose", GetUSE_ORIGINAL_POSE, SetUSE_ORIGINAL_POSE, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Enable Constraints", GetCONSTRAINTS, SetCONSTRAINTS, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Solve", GetAUTO_SOLVE, SetAUTO_SOLVE, bool, true, AM_DEFAULT);
}

// ----------------------------------------------------------------------------
IKSolver::Algorithm IKSolver::GetAlgorithm() const
{
    return algorithm_;
}

// ----------------------------------------------------------------------------
void IKSolver::SetAlgorithm(IKSolver::Algorithm algorithm)
{
    algorithm_ = algorithm;

    /* We need to rebuild the tree so make sure that the scene is in the
     * initial pose when this occurs.*/
    if (node_ != nullptr)
        ApplyOriginalPoseToScene();

    // Initial flags for when there is no solver to destroy
    uint8_t initialFlags = 0;

    // Destroys the tree and the solver
    if (solver_ != nullptr)
    {
        initialFlags = solver_->flags;
        DestroyTree();
        ik_solver_destroy(solver_);
    }

    switch (algorithm_)
    {
        case ONE_BONE : solver_ = ik_solver_create(SOLVER_ONE_BONE); break;
        case TWO_BONE : solver_ = ik_solver_create(SOLVER_TWO_BONE); break;
        case FABRIK   : solver_ = ik_solver_create(SOLVER_FABRIK);   break;
        /*case MSD      : solver_ = ik_solver_create(SOLVER_MSD);      break;*/
    }

    solver_->flags = initialFlags;

    if (node_ != nullptr)
        RebuildTree();
}

// ----------------------------------------------------------------------------
bool IKSolver::GetFeature(Feature feature) const
{
    return (features_ & feature) != 0;
}

// ----------------------------------------------------------------------------
void IKSolver::SetFeature(Feature feature, bool enable)
{
    switch (feature)
    {
        case CONSTRAINTS:
        {
            solver_->flags &= ~SOLVER_ENABLE_CONSTRAINTS;
            if (enable)
                solver_->flags |= SOLVER_ENABLE_CONSTRAINTS;
        } break;

        case TARGET_ROTATIONS:
        {
            solver_->flags &= ~SOLVER_CALCULATE_TARGET_ROTATIONS;
            if (enable)
                solver_->flags |= SOLVER_CALCULATE_TARGET_ROTATIONS;
        } break;

        case AUTO_SOLVE:
        {
            if (((features_ & AUTO_SOLVE) != 0) == enable)
                break;

            if (enable)
                SubscribeToEvent(GetScene(), E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(IKSolver, HandleSceneDrawableUpdateFinished));
            else
                UnsubscribeFromEvent(GetScene(), E_SCENEDRAWABLEUPDATEFINISHED);
        } break;

        default: break;
    }

    features_ &= ~feature;
    if (enable)
        features_ |= feature;
}

// ----------------------------------------------------------------------------
unsigned IKSolver::GetMaximumIterations() const
{
    return solver_->max_iterations;
}

// ----------------------------------------------------------------------------
void IKSolver::SetMaximumIterations(unsigned iterations)
{
    solver_->max_iterations = iterations;
}

// ----------------------------------------------------------------------------
float IKSolver::GetTolerance() const
{
    return solver_->tolerance;
}

// ----------------------------------------------------------------------------
void IKSolver::SetTolerance(float tolerance)
{
    if (tolerance < M_EPSILON)
        tolerance = M_EPSILON;
    solver_->tolerance = tolerance;
}

// ----------------------------------------------------------------------------
ik_node_t* IKSolver::CreateIKNodeFromUrhoNode(const Node* node)
{
    ik_node_t* ikNode = ik_node_create(node->GetID());

    // Set initial position/rotation and pass in Node* as user data for later
    ikNode->original_position = Vec3Urho2IK(node->GetWorldPosition());
    ikNode->original_rotation = QuatUrho2IK(node->GetWorldRotation());
    ikNode->user_data = (void*)node;

    /*
     * If Urho's node has an effector, also create and attach one to the
     * library's node. At this point, the IKEffector component shouldn't be
     * holding a reference to any internal effector. Check this for debugging
     * purposes and log if it does.
     */
    auto* effector = node->GetComponent<IKEffector>();
    if (effector != nullptr)
    {
#ifdef DEBUG
        if (effector->ikEffectorNode_ != nullptr)
            URHO3D_LOGWARNINGF("[ik] IKEffector (attached to node \"%s\") has a reference to a possibly invalid internal effector. Should be NULL.", effector->GetNode()->GetName().CString());
#endif
        ik_effector_t* ikEffector = ik_effector_create();
        ik_node_attach_effector(ikNode, ikEffector); // ownership of effector

        effector->SetIKSolver(this);
        effector->SetIKEffectorNode(ikNode);
    }

    // Exact same deal with the constraint
    auto* constraint = node->GetComponent<IKConstraint>();
    if (constraint != nullptr)
    {
#ifdef DEBUG
        if (constraint->ikConstraintNode_ != nullptr)
            URHO3D_LOGWARNINGF("[ik] IKConstraint (attached to node \"%s\") has a reference to a possibly invalid internal constraint. Should be NULL.", constraint->GetNode()->GetName().CString());
#endif

        constraint->SetIKConstraintNode(ikNode);
    }

    return ikNode;
}

// ----------------------------------------------------------------------------
void IKSolver::DestroyTree()
{
    ik_solver_destroy_tree(solver_);
    effectorList_.Clear();
    constraintList_.Clear();
}

// ----------------------------------------------------------------------------
void IKSolver::RebuildTree()
{
    assert (node_ != nullptr);

    // Destroy current tree and set a new root node
    DestroyTree();
    ik_node_t* ikRoot = CreateIKNodeFromUrhoNode(node_);
    ik_solver_set_tree(solver_, ikRoot);

    /*
     * Collect all effectors and constraints from children, and filter them to
     * make sure they are in our subtree.
     */
    node_->GetComponents<IKEffector>(effectorList_, true);
    node_->GetComponents<IKConstraint>(constraintList_, true);
    for (PODVector<IKEffector*>::Iterator it = effectorList_.Begin(); it != effectorList_.End();)
    {
        if (ComponentIsInOurSubtree(*it))
        {
            BuildTreeToEffector((*it));
            ++it;
        }
        else
        {
            it = effectorList_.Erase(it);
        }
    }
    for (PODVector<IKConstraint*>::Iterator it = constraintList_.Begin(); it != constraintList_.End();)
    {
        if (ComponentIsInOurSubtree(*it))
            ++it;
        else
            it = constraintList_.Erase(it);
    }

    treeNeedsRebuild = false;
    MarkChainsNeedUpdating();
}

// ----------------------------------------------------------------------------
bool IKSolver::BuildTreeToEffector(IKEffector* effector)
{
    /*
     * NOTE: This function makes the assumption that the node the effector is
     * attached to is -- without a doubt -- in our subtree (by using
     * ComponentIsInOurSubtree() first). If this is not the case, the program
     * will abort.
     */

    /*
     * we need to build tree up to the node where this effector was added. Do
     * this by following the chain of parent nodes until we hit a node that
     * exists in the solver's subtree. Then iterate backwards again and add each
     * missing node to the solver's tree.
     */
    const Node* iterNode = effector->GetNode();
    ik_node_t* ikNode;
    PODVector<const Node*> missingNodes;
    while ((ikNode = ik_node_find_child(solver_->tree, iterNode->GetID())) == nullptr)
    {
        missingNodes.Push(iterNode);
        iterNode = iterNode->GetParent();

        // Assert the assumptions made (described in the beginning of this function)
        assert(iterNode != nullptr);
        assert (iterNode->HasComponent<IKSolver>() == false || iterNode == node_);
    }

    while (missingNodes.Size() > 0)
    {
        iterNode = missingNodes.Back();
        missingNodes.Pop();

        ik_node_t* ikChildNode = CreateIKNodeFromUrhoNode(iterNode);
        ik_node_add_child(ikNode, ikChildNode);

        ikNode = ikChildNode;
    }

    return true;
}

// ----------------------------------------------------------------------------
bool IKSolver::ComponentIsInOurSubtree(Component* component) const
{
    const Node* iterNode = component->GetNode();
    while (true)
    {
        // Note part of our subtree
        if (iterNode == nullptr)
            return false;
        // Reached the root node, it's part of our subtree!
        if (iterNode == node_)
            return true;
        // Path to us is being blocked by another solver
        Component* otherSolver = iterNode->GetComponent<IKSolver>();
        if (otherSolver != nullptr && otherSolver != component)
            return false;

        iterNode = iterNode->GetParent();
    }

    return true;
}

// ----------------------------------------------------------------------------
void IKSolver::RebuildChainTrees()
{
    solverTreeValid_ = (ik_solver_rebuild_chain_trees(solver_) == 0);
    ik_calculate_rotation_weight_decays(&solver_->chain_tree);

    chainTreesNeedUpdating_ = false;
}

// ----------------------------------------------------------------------------
void IKSolver::RecalculateSegmentLengths()
{
    ik_solver_recalculate_segment_lengths(solver_);
}

// ----------------------------------------------------------------------------
void IKSolver::CalculateJointRotations()
{
    ik_solver_calculate_joint_rotations(solver_);
}

// ----------------------------------------------------------------------------
void IKSolver::Solve()
{
    URHO3D_PROFILE(IKSolve);

    if (treeNeedsRebuild)
        RebuildTree();

    if (chainTreesNeedUpdating_)
        RebuildChainTrees();

    if (IsSolverTreeValid() == false)
        return;

    if (features_ & UPDATE_ORIGINAL_POSE)
        ApplySceneToOriginalPose();

    if (features_ & UPDATE_ACTIVE_POSE)
        ApplySceneToActivePose();

    if (features_ & USE_ORIGINAL_POSE)
        ApplyOriginalPoseToActivePose();

    for (PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
    {
        (*it)->UpdateTargetNodePosition();
    }

    ik_solver_solve(solver_);

    if (features_ & JOINT_ROTATIONS)
        ik_solver_calculate_joint_rotations(solver_);

    ApplyActivePoseToScene();
}

// ----------------------------------------------------------------------------
static void ApplyInitialPoseToSceneCallback(ik_node_t* ikNode)
{
    auto* node = (Node*)ikNode->user_data;
    node->SetWorldRotation(QuatIK2Urho(&ikNode->original_rotation));
    node->SetWorldPosition(Vec3IK2Urho(&ikNode->original_position));
}
void IKSolver::ApplyOriginalPoseToScene()
{
    ik_solver_iterate_tree(solver_, ApplyInitialPoseToSceneCallback);
}

// ----------------------------------------------------------------------------
static void ApplySceneToInitialPoseCallback(ik_node_t* ikNode)
{
    auto* node = (Node*)ikNode->user_data;
    ikNode->original_rotation = QuatUrho2IK(node->GetWorldRotation());
    ikNode->original_position = Vec3Urho2IK(node->GetWorldPosition());
}
void IKSolver::ApplySceneToOriginalPose()
{
    ik_solver_iterate_tree(solver_, ApplySceneToInitialPoseCallback);
}

// ----------------------------------------------------------------------------
static void ApplyActivePoseToSceneCallback(ik_node_t* ikNode)
{
    auto* node = (Node*)ikNode->user_data;
    node->SetWorldRotation(QuatIK2Urho(&ikNode->rotation));
    node->SetWorldPosition(Vec3IK2Urho(&ikNode->position));
}
void IKSolver::ApplyActivePoseToScene()
{
    ik_solver_iterate_tree(solver_, ApplyActivePoseToSceneCallback);
}

// ----------------------------------------------------------------------------
static void ApplySceneToActivePoseCallback(ik_node_t* ikNode)
{
    auto* node = (Node*)ikNode->user_data;
    ikNode->rotation = QuatUrho2IK(node->GetWorldRotation());
    ikNode->position = Vec3Urho2IK(node->GetWorldPosition());
}
void IKSolver::ApplySceneToActivePose()
{
    ik_solver_iterate_tree(solver_, ApplySceneToActivePoseCallback);
}

// ----------------------------------------------------------------------------
void IKSolver::ApplyOriginalPoseToActivePose()
{
    ik_solver_reset_to_original_pose(solver_);
}

// ----------------------------------------------------------------------------
void IKSolver::MarkChainsNeedUpdating()
{
    chainTreesNeedUpdating_ = true;
}

// ----------------------------------------------------------------------------
void IKSolver::MarkTreeNeedsRebuild()
{
    treeNeedsRebuild = true;
}

// ----------------------------------------------------------------------------
bool IKSolver::IsSolverTreeValid() const
{
    return solverTreeValid_;
}

// ----------------------------------------------------------------------------
/*
 * This next section maintains the internal list of effector nodes. Whenever
 * nodes are deleted or added to the scene, or whenever components are added
 * or removed from nodes, we must check to see which of those nodes are/were
 * IK effector nodes and update our internal list accordingly.
 *
 * Unfortunately, E_COMPONENTREMOVED and E_COMPONENTADDED do not fire when a
 * parent node is removed/added containing child effector nodes, so we must
 * also monitor E_NODEREMOVED AND E_NODEADDED.
 */

// ----------------------------------------------------------------------------
void IKSolver::OnSceneSet(Scene* scene)
{
    if (features_ & AUTO_SOLVE)
        SubscribeToEvent(scene, E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(IKSolver, HandleSceneDrawableUpdateFinished));
}

// ----------------------------------------------------------------------------
void IKSolver::OnNodeSet(Node* node)
{
    ApplyOriginalPoseToScene();
    DestroyTree();

    if (node != nullptr)
        RebuildTree();
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentAdded;
    (void)eventType;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    auto* component = static_cast<Component*>(eventData[P_COMPONENT].GetPtr());

    /*
     * When a solver gets added into the scene, any parent solver's tree will
     * be invalidated. We need to find all parent solvers (by iterating up the
     * tree) and mark them as such.
     */
    if (component->GetType() == IKSolver::GetTypeStatic())
    {
        for (Node* iterNode = node; iterNode != nullptr; iterNode = iterNode->GetParent())
        {
            auto* parentSolver = iterNode->GetComponent<IKSolver>();
            if (parentSolver != nullptr)
                parentSolver->MarkTreeNeedsRebuild();

        }

        return; // No need to continue processing effectors or constraints
    }

    if (solver_->tree == nullptr)
        return;

    /*
     * Update tree if component is an effector and is part of our subtree.
     */
    if (component->GetType() == IKEffector::GetTypeStatic())
    {
        // Not interested in components that won't be part of our
        if (ComponentIsInOurSubtree(component) == false)
            return;

        BuildTreeToEffector(static_cast<IKEffector*>(component));
        effectorList_.Push(static_cast<IKEffector*>(component));
        return;
    }

    if (component->GetType() == IKConstraint::GetTypeStatic())
    {
        if (ComponentIsInOurSubtree(component) == false)
            return;

        constraintList_.Push(static_cast<IKConstraint*>(component));
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentRemoved;

    if (solver_->tree == nullptr)
        return;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    auto* component = static_cast<Component*>(eventData[P_COMPONENT].GetPtr());

    /*
     * When a solver gets added into the scene, any parent solver's tree will
     * be invalidated. We need to find all parent solvers (by iterating up the
     * tree) and mark them as such.
     */
    if (component->GetType() == IKSolver::GetTypeStatic())
    {
        for (Node* iterNode = node; iterNode != nullptr; iterNode = iterNode->GetParent())
        {
            auto* parentSolver = iterNode->GetComponent<IKSolver>();
            if (parentSolver != nullptr)
                parentSolver->MarkTreeNeedsRebuild();

        }

        return; // No need to continue processing effectors or constraints
    }

    // If an effector was removed, the tree will have to be rebuilt.
    if (component->GetType() == IKEffector::GetTypeStatic())
    {
        if (ComponentIsInOurSubtree(component) == false)
            return;

        ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
        assert(ikNode != nullptr);

        ik_node_destroy_effector(ikNode);
        static_cast<IKEffector*>(component)->SetIKEffectorNode(nullptr);
        effectorList_.RemoveSwap(static_cast<IKEffector*>(component));

        ApplyOriginalPoseToScene();
        MarkTreeNeedsRebuild();
        return;
    }

    // Remove the ikNode* reference the IKConstraint was holding
    if (component->GetType() == IKConstraint::GetTypeStatic())
    {
        if (ComponentIsInOurSubtree(component) == false)
            return;

        ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
        assert(ikNode != nullptr);

        static_cast<IKConstraint*>(component)->SetIKConstraintNode(nullptr);
        constraintList_.RemoveSwap(static_cast<IKConstraint*>(component));
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeAdded;

    if (solver_->tree == nullptr)
        return;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    PODVector<IKEffector*> effectors;
    node->GetComponents<IKEffector>(effectors, true);
    for (PODVector<IKEffector*>::ConstIterator it = effectors.Begin(); it != effectors.End(); ++it)
    {
        if (ComponentIsInOurSubtree(*it) == false)
            continue;

        BuildTreeToEffector(*it);
        effectorList_.Push(*it);
    }

    PODVector<IKConstraint*> constraints;
    node->GetComponents<IKConstraint>(constraints, true);
    for (PODVector<IKConstraint*>::ConstIterator it = constraints.Begin(); it != constraints.End(); ++it)
    {
        if (ComponentIsInOurSubtree(*it) == false)
            continue;

        constraintList_.Push(*it);
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeRemoved;

    if (solver_->tree == nullptr)
        return;

    auto* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    // Remove cached IKEffectors from our list
    PODVector<IKEffector*> effectors;
    node->GetComponents<IKEffector>(effectors, true);
    for (PODVector<IKEffector*>::ConstIterator it = effectors.Begin(); it != effectors.End(); ++it)
    {
        (*it)->SetIKEffectorNode(nullptr);
        effectorList_.RemoveSwap(*it);
    }

    PODVector<IKConstraint*> constraints;
    node->GetComponents<IKConstraint>(constraints, true);
    for (PODVector<IKConstraint*>::ConstIterator it = constraints.Begin(); it != constraints.End(); ++it)
    {
        constraintList_.RemoveSwap(*it);
    }

    // Special case, if the node being destroyed is the root node, destroy the
    // solver's tree instead of destroying the single node. Calling
    // ik_node_destroy() on the solver's root node will cause segfaults.
    ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
    if (ikNode != nullptr)
    {
        if (ikNode == solver_->tree)
            ik_solver_destroy_tree(solver_);
        else
            ik_node_destroy(ikNode);

        MarkChainsNeedUpdating();
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
{
    Solve();
}

// ----------------------------------------------------------------------------
void IKSolver::DrawDebugGeometry(bool depthTest)
{
    auto* debug = GetScene()->GetComponent<DebugRenderer>();
    if (debug)
        DrawDebugGeometry(debug, depthTest);
}

// ----------------------------------------------------------------------------
void IKSolver::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    // Draws all scene segments
    for (PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
        (*it)->DrawDebugGeometry(debug, depthTest);

    ORDERED_VECTOR_FOR_EACH(&solver_->effector_nodes_list, ik_node_t*, pnode)
        ik_effector_t* effector = (*pnode)->effector;

        // Calculate average length of all segments so we can determine the radius
        // of the debug spheres to draw
        int chainLength = effector->chain_length == 0 ? -1 : effector->chain_length;
        ik_node_t* a = *pnode;
        ik_node_t* b = a->parent;
        float averageLength = 0.0f;
        unsigned numberOfSegments = 0;
        while (b && chainLength-- != 0)
        {
            vec3_t v = a->original_position;
            vec3_sub_vec3(v.f, b->original_position.f);
            averageLength += vec3_length(v.f);
            ++numberOfSegments;
            a = b;
            b = b->parent;
        }
        averageLength /= numberOfSegments;

        // connect all chained nodes together with lines
        chainLength = effector->chain_length == 0 ? -1 : effector->chain_length;
        a = *pnode;
        b = a->parent;
        debug->AddSphere(
            Sphere(Vec3IK2Urho(&a->original_position), averageLength * 0.1f),
            Color(0, 0, 255),
            depthTest
        );
        debug->AddSphere(
            Sphere(Vec3IK2Urho(&a->position), averageLength * 0.1f),
            Color(255, 128, 0),
            depthTest
        );
        while (b && chainLength-- != 0)
        {
            debug->AddLine(
                Vec3IK2Urho(&a->original_position),
                Vec3IK2Urho(&b->original_position),
                Color(0, 255, 255),
                depthTest
            );
            debug->AddSphere(
                Sphere(Vec3IK2Urho(&b->original_position), averageLength * 0.1f),
                Color(0, 0, 255),
                depthTest
            );
            debug->AddLine(
                Vec3IK2Urho(&a->position),
                Vec3IK2Urho(&b->position),
                Color(255, 0, 0),
                depthTest
            );
            debug->AddSphere(
                Sphere(Vec3IK2Urho(&b->position), averageLength * 0.1f),
                Color(255, 128, 0),
                depthTest
            );
            a = b;
            b = b->parent;
        }
    ORDERED_VECTOR_END_EACH
}

// ----------------------------------------------------------------------------
// Need these wrapper functions flags of GetFeature/SetFeature can be correctly
// exposed to the editor
// ----------------------------------------------------------------------------

#define DEF_FEATURE_GETTER(feature_name) \
bool IKSolver::Get##feature_name() const \
{                                        \
    return GetFeature(feature_name);     \
}

#define DEF_FEATURE_SETTER(feature_name)      \
void IKSolver::Set##feature_name(bool enable) \
{                                             \
    SetFeature(feature_name, enable);         \
}

DEF_FEATURE_GETTER(JOINT_ROTATIONS)
DEF_FEATURE_GETTER(TARGET_ROTATIONS)
DEF_FEATURE_GETTER(UPDATE_ORIGINAL_POSE)
DEF_FEATURE_GETTER(UPDATE_ACTIVE_POSE)
DEF_FEATURE_GETTER(USE_ORIGINAL_POSE)
DEF_FEATURE_GETTER(CONSTRAINTS)
DEF_FEATURE_GETTER(AUTO_SOLVE)

DEF_FEATURE_SETTER(JOINT_ROTATIONS)
DEF_FEATURE_SETTER(TARGET_ROTATIONS)
DEF_FEATURE_SETTER(UPDATE_ORIGINAL_POSE)
DEF_FEATURE_SETTER(UPDATE_ACTIVE_POSE)
DEF_FEATURE_SETTER(USE_ORIGINAL_POSE)
DEF_FEATURE_SETTER(CONSTRAINTS)
DEF_FEATURE_SETTER(AUTO_SOLVE)

} // namespace Urho3D
