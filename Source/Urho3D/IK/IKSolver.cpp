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

namespace Urho3D
{

extern const char* IK_CATEGORY;

static bool ChildrenHaveEffector(const Node* node)
{
    if (node->HasComponent<IKEffector>())
        return true;

    const Vector<SharedPtr<Node> >& children = node->GetChildren();
    for (Vector<SharedPtr<Node> >::ConstIterator it = children.Begin(); it != children.End(); ++it)
    {
        if (ChildrenHaveEffector(it->Get()))
            return true;
    }

    return false;
}

// ----------------------------------------------------------------------------
IKSolver::IKSolver(Context* context) :
    Component(context),
    solver_(NULL),
    solverTreeNeedsRebuild_(false),
    updateInitialPose_(false),
    autoSolveEnabled_(true)
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
        (*it)->SetIKEffector(NULL);

    ik_solver_destroy(solver_);
    context_->ReleaseIK();
}

// ----------------------------------------------------------------------------
void IKSolver::RegisterObject(Context* context)
{
    context->RegisterFactory<IKSolver>(IK_CATEGORY);

    static const char* algorithmNames[] = {
        "FABRIK",
        /* not implemented
        "Jacobian Inverse",
        "Jacobian Transpose",*/
        NULL
    };

    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Algorithm", GetAlgorithm, SetAlgorithm, Algorithm, algorithmNames, SOLVER_FABRIK, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Iterations", GetMaximumIterations, SetMaximumIterations, unsigned, 20, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Convergence Tolerance", GetTolerance, SetTolerance, float, 0.001, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Bone Rotations", BoneRotationsEnabled, EnableBoneRotations, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Target Rotation", TargetRotationEnabled, EnableTargetRotation, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Continuous Solving", ContinuousSolvingEnabled, EnableContinuousSolving, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update Pose", UpdatePoseEnabled, EnableUpdatePose, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Solve", AutoSolveEnabled, EnableAutoSolve, bool, true, AM_DEFAULT);
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

    if (solver_ != NULL)
        ik_solver_destroy(solver_);

    switch (algorithm_)
    {
        case FABRIK: solver_ = ik_solver_create(SOLVER_FABRIK); break;
    }

    solver_->flags = SOLVER_CALCULATE_FINAL_ROTATIONS;
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
bool IKSolver::BoneRotationsEnabled() const
{
    return (solver_->flags & SOLVER_CALCULATE_FINAL_ROTATIONS) != 0;
}

// ----------------------------------------------------------------------------
void IKSolver::EnableBoneRotations(bool enable)
{
    solver_->flags &= ~SOLVER_CALCULATE_FINAL_ROTATIONS;
    if (enable)
        solver_->flags |= SOLVER_CALCULATE_FINAL_ROTATIONS;
}

// ----------------------------------------------------------------------------
bool IKSolver::TargetRotationEnabled() const
{
    return (solver_->flags & SOLVER_CALCULATE_TARGET_ROTATIONS) != 0;
}

// ----------------------------------------------------------------------------
void IKSolver::EnableTargetRotation(bool enable)
{
    solver_->flags &= ~SOLVER_CALCULATE_TARGET_ROTATIONS;
    if (enable)
        solver_->flags |= SOLVER_CALCULATE_TARGET_ROTATIONS;
}

// ----------------------------------------------------------------------------
bool IKSolver::ContinuousSolvingEnabled() const
{
    return (solver_->flags & SOLVER_SKIP_RESET) != 0;
}

// ----------------------------------------------------------------------------
void IKSolver::EnableContinuousSolving(bool enable)
{
    solver_->flags &= ~SOLVER_SKIP_RESET;
    if (enable)
        solver_->flags |= SOLVER_SKIP_RESET;
}

// ----------------------------------------------------------------------------
bool IKSolver::UpdatePoseEnabled() const
{
    return updateInitialPose_;
}

// ----------------------------------------------------------------------------
void IKSolver::EnableUpdatePose(bool enable)
{
    updateInitialPose_ = enable;
}

// ----------------------------------------------------------------------------
void IKSolver::MarkSolverTreeDirty()
{
    solverTreeNeedsRebuild_ = true;
}

// ----------------------------------------------------------------------------
bool IKSolver::AutoSolveEnabled() const
{
    return autoSolveEnabled_;
}

// ----------------------------------------------------------------------------
void IKSolver::EnableAutoSolve(bool enable)
{
    if (autoSolveEnabled_ == enable)
        return;

    if (enable)
        SubscribeToEvent(GetScene(), E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(IKSolver, HandleSceneDrawableUpdateFinished));
    else
        UnsubscribeFromEvent(GetScene(), E_SCENEDRAWABLEUPDATEFINISHED);

    autoSolveEnabled_ = enable;
}

// ----------------------------------------------------------------------------
static void ApplySolvedDataCallback(ik_node_t* ikNode)
{
    Node* node = (Node*)ikNode->user_data;
    node->SetWorldRotation(QuatIK2Urho(&ikNode->solved_rotation));
    node->SetWorldPosition(Vec3IK2Urho(&ikNode->solved_position));
}
void IKSolver::Solve()
{
    URHO3D_PROFILE(IKSolve);

    if (solverTreeNeedsRebuild_)
    {
        ik_solver_rebuild_data(solver_);
        solverTreeNeedsRebuild_ = false;
    }

    if (updateInitialPose_)
        UpdateInitialPose();

    for (PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
    {
        (*it)->UpdateTargetNodePosition();
    }

    solver_->apply_result = ApplySolvedDataCallback;
    ik_solver_solve(solver_);
}

// ----------------------------------------------------------------------------
static void ApplyInitialDataCallback(ik_node_t* ikNode)
{
    Node* node = (Node*)ikNode->user_data;
    node->SetWorldRotation(QuatIK2Urho(&ikNode->rotation));
    node->SetWorldPosition(Vec3IK2Urho(&ikNode->position));
}
void IKSolver::ResetToInitialPose()
{
    solver_->apply_result = ApplyInitialDataCallback;
    ik_solver_iterate_tree(solver_);
}

// ----------------------------------------------------------------------------
static void UpdateInitialPoseCallback(ik_node_t* ikNode)
{
    Node* node = (Node*)ikNode->user_data;
    ikNode->rotation = QuatUrho2IK(node->GetWorldRotation());
    ikNode->position = Vec3Urho2IK(node->GetWorldPosition());
}
void IKSolver::UpdateInitialPose()
{
    solver_->apply_result = UpdateInitialPoseCallback;
    ik_solver_iterate_tree(solver_);
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
    if (autoSolveEnabled_)
        SubscribeToEvent(scene, E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(IKSolver, HandleSceneDrawableUpdateFinished));
}

// ----------------------------------------------------------------------------
void IKSolver::OnNodeSet(Node* node)
{
    ResetToInitialPose();
    DestroyTree();

    if (node != NULL)
        RebuildTree();
}

// ----------------------------------------------------------------------------
ik_node_t* IKSolver::CreateIKNode(const Node* node)
{
    ik_node_t* ikNode = ik_node_create(node->GetID());

    // Set initial position/rotation and pass in Node* as user data for later
    ikNode->position = Vec3Urho2IK(node->GetWorldPosition());
    ikNode->rotation = QuatUrho2IK(node->GetWorldRotation());
    ikNode->user_data = (void*)node;

    // If the node has a constraint, it needs access to the ikNode
    IKConstraint* constraint = node->GetComponent<IKConstraint>();
    if (constraint != NULL)
        constraint->SetIKNode(ikNode);

    return ikNode;
}

// ----------------------------------------------------------------------------
void IKSolver::DestroyTree()
{
    ik_solver_destroy_tree(solver_);
    effectorList_.Clear();
}

// ----------------------------------------------------------------------------
void IKSolver::RebuildTree()
{
    assert(node_ != NULL);

    ik_node_t* ikRoot = CreateIKNode(node_);
    ik_solver_set_tree(solver_, ikRoot);

    PODVector<Node*> effectorNodes;
    node_->GetChildrenWithComponent<IKEffector>(effectorNodes, true);
    for (PODVector<Node*>::ConstIterator it = effectorNodes.Begin(); it != effectorNodes.End(); ++it)
    {
        BuildTreeToEffector(*it);
    }
}

// ----------------------------------------------------------------------------
void IKSolver::BuildTreeToEffector(const Node* node)
{
    // Check if the component that was added is an IK effector. If not, then it
    // does not concern us.
    IKEffector* effector = static_cast<IKEffector*>(node->GetComponent<IKEffector>());
    if (effector == NULL || effector->GetType() != IKEffector::GetTypeStatic())
        return;

    // May need to build tree up to the node where this effector was added. Do
    // this by following the chain of parent nodes until we hit a node that
    // exists in the solver's tree. Then iterate backwards again and add each
    // missing node to the solver's tree.
    PODVector<const Node*> missingNodes;
    const Node* iterNode = node;
    ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
    while (ikNode == NULL)
    {
        missingNodes.Push(iterNode);
        iterNode = iterNode->GetParent();
        ikNode = ik_node_find_child(solver_->tree, iterNode->GetID());
    }
    while (missingNodes.Size() > 0)
    {
        iterNode = missingNodes.Back();
        missingNodes.Pop();
        ik_node_t* ikChildNode = CreateIKNode(iterNode);
        ik_node_add_child(ikNode, ikChildNode);
        ikNode = ikChildNode;
    }

    // The tip of the tree is the effector. The solver library has ownership of
    // the effector object, but our IKEffector object also needs to know about
    // it.
    ik_effector_t* ikEffector = ik_effector_create();
    ik_node_attach_effector(ikNode, ikEffector); // ownership of effector
    effector->SetIKEffector(ikEffector);           // "weak" reference to effector
    effector->SetIKSolver(this);
    effectorList_.Push(effector);

    MarkSolverTreeDirty();
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentAdded;
    (void)eventType;

    if (solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    BuildTreeToEffector(node);
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentRemoved;

    if (solver_->tree == NULL)
        return;

    // If an effector was removed, the tree will have to be rebuilt.
    Component* component = static_cast<Component*>(eventData[P_COMPONENT].GetPtr());
    if (component->GetType() == IKEffector::GetTypeStatic())
    {
        IKEffector* effector = static_cast<IKEffector*>(component);
        Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
        ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
        assert(ikNode != NULL);
        ik_node_destroy_effector(ikNode);
        effector->SetIKEffector(NULL);
        effectorList_.RemoveSwap(effector);

        ResetToInitialPose();
        MarkSolverTreeDirty();
    }

    // Remove the ikNode* reference the IKConstraint was holding
    if (component->GetType() == IKConstraint::GetTypeStatic())
    {
        IKConstraint* constraint = static_cast<IKConstraint*>(component);
        constraint->SetIKNode(NULL);  // NOTE: Should restore default settings to the node
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeAdded;

    if (solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    PODVector<Node*> nodes;
    node->GetChildrenWithComponent<IKEffector>(nodes, true);
    for (PODVector<Node*>::ConstIterator it = nodes.Begin(); it != nodes.End(); ++it)
    {
        BuildTreeToEffector(*it);
        effectorList_.Push((*it)->GetComponent<IKEffector>());
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeRemoved;

    if (solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    // Remove cached IKEffectors from our list
    PODVector<Node*> nodes;
    node->GetChildrenWithComponent<IKEffector>(nodes, true);
    for (PODVector<Node*>::ConstIterator it = nodes.Begin(); it != nodes.End(); ++it)
    {
        IKEffector* effector = (*it)->GetComponent<IKEffector>();
        effector->SetIKEffector(NULL);
        effectorList_.RemoveSwap(effector);
    }

    // Special case, if the node being destroyed is the root node, destroy the
    // solver's tree instead of destroying the single node. Calling
    // ik_node_destroy() on the solver's root node will cause segfaults.
    ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
    if (ikNode != NULL)
    {
        if (ikNode == solver_->tree)
            ik_solver_destroy_tree(solver_);
        else
            ik_node_destroy(ikNode);

        MarkSolverTreeDirty();
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
    DebugRenderer* debug = GetScene()->GetComponent<DebugRenderer>();
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
            vec3_t v = a->position;
            vec3_sub_vec3(v.f, b->position.f);
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
            Sphere(Vec3IK2Urho(&a->position), averageLength * 0.1f),
            Color(0, 0, 255),
            depthTest
        );
        debug->AddSphere(
            Sphere(Vec3IK2Urho(&a->solved_position), averageLength * 0.1f),
            Color(255, 128, 0),
            depthTest
        );
        while (b && chainLength-- != 0)
        {
            debug->AddLine(
                Vec3IK2Urho(&a->position),
                Vec3IK2Urho(&b->position),
                Color(0, 255, 255),
                depthTest
            );
            debug->AddSphere(
                Sphere(Vec3IK2Urho(&b->position), averageLength * 0.1f),
                Color(0, 0, 255),
                depthTest
            );
            debug->AddLine(
                Vec3IK2Urho(&a->solved_position),
                Vec3IK2Urho(&b->solved_position),
                Color(255, 0, 0),
                depthTest
            );
            debug->AddSphere(
                Sphere(Vec3IK2Urho(&b->solved_position), averageLength * 0.1f),
                Color(255, 128, 0),
                depthTest
            );
            a = b;
            b = b->parent;
        }
    ORDERED_VECTOR_END_EACH
}

} // namespace Urho3D
