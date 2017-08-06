#include "ik/chain_tree.h"
#include "ik/effector.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include "ik/solver.h"
#include "ik/solver_FABRIK.h"
#include "ik/solver_2bone.h"
#include "ik/solver_1bone.h"
#include "ik/solver_MSD.h"
#include "ik/solver_jacobian_inverse.h"
#include "ik/solver_jacobian_transpose.h"
#include <string.h>
#include <assert.h>

static int
recursively_get_all_effector_nodes(ik_node_t* node, ordered_vector_t* effector_nodes_list);

/* ------------------------------------------------------------------------- */
ik_solver_t*
ik_solver_create(enum solver_algorithm_e algorithm)
{
    uintptr_t solver_size = 0;
    int (*solver_construct)(ik_solver_t*) = NULL;
    ik_solver_t* solver = NULL;

    /*
     * Determine the correct size and confunction, depending on the
     * selected algorithm.
     */
    switch (algorithm)
    {
    case SOLVER_FABRIK:
        solver_size = sizeof(fabrik_t);
        solver_construct = solver_FABRIK_construct;
        break;

    case SOLVER_TWO_BONE:
        solver_size = sizeof(two_bone_t);
        solver_construct = solver_2bone_construct;
        break;

    case SOLVER_ONE_BONE:
        solver_size = sizeof(one_bone_t);
        solver_construct = solver_1bone_construct;
        break;
        
    case SOLVER_MSD:
        solver_size = sizeof(msd_t);
        solver_construct = solver_MSD_construct;
        break;

    /*
    case SOLVER_JACOBIAN_INVERSE:
    case SOLVER_JACOBIAN_TRANSPOSE:
        break;*/
    }

    if (solver_construct == NULL)
    {
        ik_log_message("Unknown algorithm \"%d\" was specified", algorithm);
        goto alloc_solver_failed;
    }

    /*
     * Allocate the solver, initialise to 0 and initialise the base fields
     * before calling the construct() callback for the specific solver.
     */
    solver = (ik_solver_t*)MALLOC(solver_size);
    if (solver == NULL)
    {
        ik_log_message("Failed to allocate solver: ran out of memory");
        goto alloc_solver_failed;
    }
    memset(solver, 0, solver_size);

    ordered_vector_construct(&solver->effector_nodes_list, sizeof(ik_node_t*));
    chain_tree_construct(&solver->chain_tree);

    /* Now call derived construction */
    if (solver_construct(solver) < 0)
        goto construct_derived_solver_failed;

    /* Derived destruct callback must be set */
    if (solver->destruct == NULL)
    {
        ik_log_message("Derived solvers MUST implement the destruct() callback");
        goto derived_didnt_implement_destruct;
    }

    return solver;

    derived_didnt_implement_destruct :
    construct_derived_solver_failed  : FREE(solver);
    alloc_solver_failed              : return NULL;
}

/* ------------------------------------------------------------------------- */
void
ik_solver_destroy(ik_solver_t* solver)
{
    solver->destruct(solver);

    if (solver->tree)
        ik_node_destroy(solver->tree);

    chain_tree_destruct(&solver->chain_tree);
    ordered_vector_clear_free(&solver->effector_nodes_list);

    FREE(solver);
}

/* ------------------------------------------------------------------------- */
void
ik_solver_set_tree(ik_solver_t* solver, ik_node_t* root)
{
    ik_solver_destroy_tree(solver);
    solver->tree = root;
}

/* ------------------------------------------------------------------------- */
ik_node_t*
ik_solver_unlink_tree(ik_solver_t* solver)
{
    ik_node_t* root = solver->tree;
    if (root == NULL)
        return NULL;
    solver->tree = NULL;

    /*
     * Effectors are owned by the nodes, but we need to release references to
     * them.
     */
    ordered_vector_clear(&solver->effector_nodes_list);

    return root;
}

/* ------------------------------------------------------------------------- */
void
ik_solver_destroy_tree(ik_solver_t* solver)
{
    ik_node_t* root;
    if ((root = ik_solver_unlink_tree(solver)) == NULL)
        return;
    ik_node_destroy(root);
}

/* ------------------------------------------------------------------------- */
int
ik_solver_rebuild_chain_trees(ik_solver_t* solver)
{
    /* If the solver has no tree, then there's nothing to do */
    if (solver->tree == NULL)
    {
        ik_log_message("No tree to work with. Did you forget to set the tree with ik_solver_set_tree()?");
        return -1;
    }

    /*
     * Traverse the entire tree and generate a list of the effectors. This
     * makes the process of building the chain list for FABRIK much easier.
     */
    ik_log_message("Rebuilding effector nodes list");
    ordered_vector_clear(&solver->effector_nodes_list);
    if (recursively_get_all_effector_nodes(solver->tree, &solver->effector_nodes_list) < 0)
    {
        ik_log_message("Ran out of memory while building the effector nodes list");
        return -1;
    }

    /* now build the chain tree */
    if (rebuild_chain_tree(solver) < 0)
        return -1;

    if (solver->post_chain_build != NULL)
        return solver->post_chain_build(solver);

    return 0;
}

/* ------------------------------------------------------------------------- */
void
ik_solver_recalculate_segment_lengths(ik_solver_t* solver)
{
    calculate_segment_lengths(&solver->chain_tree);
}

/* ------------------------------------------------------------------------- */
int
ik_solver_solve(ik_solver_t* solver)
{
    return solver->solve(solver);
}

/* ------------------------------------------------------------------------- */
void
ik_solver_calculate_joint_rotations(ik_solver_t* solver)
{
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        calculate_global_rotations(&island->root_chain);
    ORDERED_VECTOR_END_EACH
}

/* ------------------------------------------------------------------------- */
static void
iterate_tree_recursive(ik_node_t* node,
                       ik_solver_iterate_node_cb_func callback)
{
    callback(node);

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        iterate_tree_recursive(child, callback);
    BSTV_END_EACH
}
void
ik_solver_iterate_tree(ik_solver_t* solver,
                       ik_solver_iterate_node_cb_func callback)
{
    if (solver->tree == NULL)
    {
        ik_log_message("Warning: Tried iterating the tree, but no tree was set");
        return;
    }

    iterate_tree_recursive(solver->tree, callback);
}

/* ------------------------------------------------------------------------- */
static void
iterate_chain_tree_recursive(chain_t* chain,
                             ik_solver_iterate_node_cb_func callback)
{
    /*
     * Iterate the chain tree breadth first. Note that we exclude the base node
     * in each chain, because otherwise the same node would be passed to the
     * callback multiple times. The base node is shared by the parent chain's
     * effector as well as with other chains in the same depth.
     */
    int idx = ordered_vector_count(&chain->nodes);
    assert(idx > 0); // chains must have at least 2 nodes in them
    while (idx--)
    {
        callback(*(ik_node_t**)ordered_vector_get_element(&chain->nodes, idx));
    }

    ORDERED_VECTOR_FOR_EACH(&chain->children, chain_t, child)
        iterate_chain_tree_recursive(child, callback);
    ORDERED_VECTOR_END_EACH
}
void ik_solver_iterate_chain_tree(ik_solver_t* solver,
                                  ik_solver_iterate_node_cb_func callback)
{
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        /*
         * The root node is excluded by the recursive function, so we must
         * do the callback here
         */
        int idx = ordered_vector_count(&island->root_chain.nodes) - 1;
        ik_node_t* root = *(ik_node_t**)ordered_vector_get_element(&island->root_chain.nodes, idx);
        callback(root);

        iterate_chain_tree_recursive(&island->root_chain, callback);
    ORDERED_VECTOR_END_EACH
}

/* ------------------------------------------------------------------------- */
static void
reset_active_pose_recursive(ik_node_t* node)
{
    node->position = node->original_position;
    node->rotation = node->original_rotation;

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        reset_active_pose_recursive(child);
    BSTV_END_EACH
}
void
ik_solver_reset_to_original_pose(ik_solver_t* solver)
{
    if (solver->tree == NULL)
        return;

    reset_active_pose_recursive(solver->tree);
}

/* ------------------------------------------------------------------------- */
static int
recursively_get_all_effector_nodes(ik_node_t* node, ordered_vector_t* effector_nodes_list)
{
    if (node->effector != NULL)
        if (ordered_vector_push(effector_nodes_list, &node) < 0)
            return -1;

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        if (recursively_get_all_effector_nodes(child, effector_nodes_list) < 0)
            return -1;
    BSTV_END_EACH

    return 0;
}
