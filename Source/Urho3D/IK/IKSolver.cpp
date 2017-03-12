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
#include "../IK/IK.h"
#include "../IK/IKEvents.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../IO/Log.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"

#include <ik/solver.h>
#include <ik/node.h>
#include <ik/effector.h>
#include <ik/log.h>

namespace Urho3D
{

extern const char* IK_CATEGORY;;
extern const char* SUBSYSTEM_CATEGORY;

static void HandleIKLog(const char* msg)
{
    URHO3D_LOGINFOF("[IK] %s", msg);
}
static vec3_t Vec3Urho2IK(const Vector3& urho)
{
    vec3_t ret;
    ret.v.x = urho.x_;
    ret.v.y = urho.y_;
    ret.v.z = urho.z_;
    return ret;
}
static Vector3 Vec3IK2Urho(const vec3_t* ik)
{
    return Vector3(ik->v.x, ik->v.y, ik->v.z);
}
static ik_node_t* CreateIKNode(const Node* node)
{
    ik_node_t* ikNode = ik_node_create(node->GetID());
    ikNode->position = Vec3Urho2IK(node->GetWorldPosition());
    ikNode->user_data = (void*)node;
    return ikNode;
}
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
}
static void ApplyResultCallback(ik_node_t* ikNode, vec3_t position, quat_t rotation)
{
    Node* node = (Node*)ikNode->user_data;
    node->SetWorldPosition(Vec3IK2Urho(&ikNode->solved_position));
    node->SetWorldRotation(Quaternion(
        rotation.q.w,
        rotation.q.x,
        rotation.q.y,
        rotation.q.z
    ));
}

// ----------------------------------------------------------------------------
IKSolver::IKSolver(Context* context) :
    Component(context),
    solver_(NULL),
    solverTreeNeedsRebuild_(false)
{
    context_->RequireIK();
    solver_ = ik_solver_create(SOLVER_FABRIK);
    solver_->apply_result = ApplyResultCallback;
    solver_->build_mode = SOLVER_EXCLUDE_ROOT;
    ik_log_register_listener(HandleIKLog);

    SubscribeToEvent(E_COMPONENTADDED,              URHO3D_HANDLER(IKSolver, HandleComponentAdded));
    SubscribeToEvent(E_COMPONENTREMOVED,            URHO3D_HANDLER(IKSolver, HandleComponentRemoved));
    SubscribeToEvent(E_NODEADDED,                   URHO3D_HANDLER(IKSolver, HandleNodeAdded));
    SubscribeToEvent(E_NODEREMOVED,                 URHO3D_HANDLER(IKSolver, HandleNodeRemoved));
    SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(IKSolver, HandleSceneDrawableUpdateFinished));
}

// ----------------------------------------------------------------------------
IKSolver::~IKSolver()
{
    // Destroying the solver tree will destroy the effector objects, so remove
    // any references any of the IKEffector objects could be holding
    for(PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
        (*it)->SetEffector(NULL);

    ik_log_unregister_listener(HandleIKLog);
    ik_solver_destroy(solver_);
    context_->ReleaseIK();
}

// ----------------------------------------------------------------------------
void IKSolver::RegisterObject(Context* context)
{
    context->RegisterFactory<IKSolver>(SUBSYSTEM_CATEGORY);

    static const char* algorithmNames[] = {
        "FABRIK",
        /* not implemented
        "Jacobian Inverse",
        "Jacobian Transpose",*/
        NULL
    };

    URHO3D_ACCESSOR_ATTRIBUTE("Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Algorithm", GetAlgorithm, SetAlgorithm, Algorithm, algorithmNames, SOLVER_FABRIK, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Iterations", GetMaximumIterations, SetMaximumIterations, unsigned, 1000, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Convergence Tolerance", GetTolerance, SetTolerance, float, 0.1f, AM_DEFAULT);
}

// ----------------------------------------------------------------------------
void IKSolver::SetAlgorithm(IKSolver::Algorithm algorithm)
{
    URHO3D_LOGERROR("Failed to set algorithm: Not implemented");
}

// ----------------------------------------------------------------------------
IKSolver::Algorithm IKSolver::GetAlgorithm() const
{
    return FABRIK;
}

// ----------------------------------------------------------------------------
void IKSolver::SetMaximumIterations(unsigned iterations)
{
    solver_->max_iterations = iterations;
}

// ----------------------------------------------------------------------------
unsigned IKSolver::GetMaximumIterations() const
{
    return solver_->max_iterations;
}

// ----------------------------------------------------------------------------
void IKSolver::SetTolerance(float tolerance)
{
    if(tolerance < M_EPSILON)
        tolerance = M_EPSILON;
    solver_->tolerance = tolerance;
}

// ----------------------------------------------------------------------------
float IKSolver::GetTolerance() const
{
    return solver_->tolerance;
}

// ----------------------------------------------------------------------------
void IKSolver::MarkSolverTreeDirty()
{
    solverTreeNeedsRebuild_ = true;
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
    if (scene == NULL)
    {
        ik_solver_destroy_tree(solver_);
    }
    else
    {
        RebuildTree();
    }
}

// ----------------------------------------------------------------------------
void IKSolver::RebuildTree()
{
    Node* scene = GetScene();
    assert(scene != NULL);

    ik_node_t* ikRoot = ik_node_create(scene->GetID());
    ik_solver_set_tree(solver_, ikRoot);

    PODVector<Node*> effectorNodes;
    scene->GetChildrenWithComponent<IKEffector>(effectorNodes, true);
    for(PODVector<Node*>::ConstIterator it = effectorNodes.Begin(); it != effectorNodes.End(); ++it)
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
    if(effector == NULL || effector->GetType() != IKEffector::GetTypeStatic())
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
    effector->SetEffector(ikEffector);           // "weak" reference to effector
    effector->SetSolver(this);
    effectorList_.Push(effector);

    MarkSolverTreeDirty();
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentAdded;
    (void)eventType;

    if(solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    BuildTreeToEffector(node);
}

// ----------------------------------------------------------------------------
void IKSolver::HandleComponentRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentRemoved;
    (void)eventType;

    if(solver_->tree == NULL)
        return;

    // Check if the component that was removed was an IK effector. If not,
    // then it does not concern us.
    IKEffector* effector = static_cast<IKEffector*>(eventData[P_COMPONENT].GetPtr());
    if(effector->GetType() != IKEffector::GetTypeStatic())
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
    ik_node_destroy_effector(ikNode);
    effector->SetEffector(NULL);
    effectorList_.Remove(effector); // TODO RemoveSwap()

    MarkSolverTreeDirty();
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeAdded;
    (void)eventType;

    if(solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    PODVector<Node*> effectorNodes;
    node->GetChildrenWithComponent<IKEffector>(effectorNodes, true);
    for(PODVector<Node*>::ConstIterator it = effectorNodes.Begin(); it != effectorNodes.End(); ++it)
    {
        BuildTreeToEffector(*it);
        effectorList_.Push((*it)->GetComponent<IKEffector>());
    }
}

// ----------------------------------------------------------------------------
void IKSolver::HandleNodeRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeRemoved;
    (void)eventType;

    if(solver_->tree == NULL)
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());

    PODVector<Node*> effectorNodes;
    node->GetChildrenWithComponent<IKEffector>(effectorNodes, true);
    for(PODVector<Node*>::ConstIterator it = effectorNodes.Begin(); it != effectorNodes.End(); ++it)
    {
        effectorList_.Remove((*it)->GetComponent<IKEffector>());
    }

    ik_node_t* ikNode = ik_node_find_child(solver_->tree, node->GetID());
    if(ikNode != NULL)
        ik_node_destroy(ikNode);

    MarkSolverTreeDirty();
}

// ----------------------------------------------------------------------------
void IKSolver::HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData)
{
    URHO3D_PROFILE(SolveIK);

    if (solverTreeNeedsRebuild_)
    {
        ik_solver_rebuild_data(solver_);
        solverTreeNeedsRebuild_ = false;
    }

    for(PODVector<IKEffector*>::ConstIterator it = effectorList_.Begin(); it != effectorList_.End(); ++it)
    {
        (*it)->UpdateTargetNodePosition();
    }

    ik_solver_solve(solver_);
}

} // namespace Urho3D
