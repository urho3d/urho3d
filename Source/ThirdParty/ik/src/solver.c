#include "ik/effector.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include "ik/solver.h"
#include "ik/solver_FABRIK.h"
#include "ik/solver_jacobian_inverse.h"
#include "ik/solver_jacobian_transpose.h"

static int
recursive_get_all_effector_nodes(struct ik_node_t* node, struct ordered_vector_t* effector_nodes_list);

/* ------------------------------------------------------------------------- */
struct ik_solver_t*
ik_solver_create(enum solver_algorithm_e algorithm)
{
    struct ik_solver_t* solver = NULL;

    switch(algorithm)
    {
    case SOLVER_FABRIK:
        solver = (struct ik_solver_t*)solver_FABRIK_create();
        break;

    /*case SOLVER_JACOBIAN_INVERSE:
    case SOLVER_JACOBIAN_TRANSPOSE:
        break;*/
    }

    if(solver == NULL)
        return NULL;

    ordered_vector_construct(&solver->effector_nodes_list, sizeof(struct ik_node_t*));

    return solver;
}

/* ------------------------------------------------------------------------- */
void
ik_solver_destroy(struct ik_solver_t* solver)
{
    if(solver->tree)
        ik_node_destroy(solver->tree);

    ordered_vector_clear_free(&solver->effector_nodes_list);

    solver->destroy(solver);
}

/* ------------------------------------------------------------------------- */
void
ik_solver_set_tree(struct ik_solver_t* solver, struct ik_node_t* root)
{
    ik_solver_destroy_tree(solver);
    solver->tree = root;
}

/* ------------------------------------------------------------------------- */
struct ik_node_t*
ik_solver_unlink_tree(struct ik_solver_t* solver)
{
    struct ik_node_t* root = solver->tree;
    if(root == NULL)
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
ik_solver_destroy_tree(struct ik_solver_t* solver)
{
    struct ik_node_t* root;
    if((root = ik_solver_unlink_tree(solver)) == NULL)
        return;
    ik_node_destroy(root);
}

/* ------------------------------------------------------------------------- */
int
ik_solver_rebuild_data(struct ik_solver_t* solver)
{
    /* If the solver has no tree, then there's nothing to do */
    if(solver->tree == NULL)
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
    if(recursive_get_all_effector_nodes(solver->tree,
                                        &solver->effector_nodes_list) < 0)
    {
        ik_log_message("Ran out of memory while building the effector nodes list");
        return -1;
    }

    return solver->rebuild_data(solver);
}

/* ------------------------------------------------------------------------- */
void
ik_solver_recalculate_segment_lengths(struct ik_solver_t* solver)
{
    solver->recalculate_segment_lengths(solver);
}

/* ------------------------------------------------------------------------- */
int
ik_solver_solve(struct ik_solver_t* solver)
{
    return solver->solve(solver);
}

/* ------------------------------------------------------------------------- */
static void
iterate_tree_recursive(struct ik_solver_t* solver, struct ik_node_t* node)
{
    if(solver->apply_result)
        solver->apply_result(node);

    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        iterate_tree_recursive(solver, child);
    BSTV_END_EACH
}
void
ik_solver_iterate_tree(struct ik_solver_t* solver)
{
    if(solver->tree == NULL)
        return;

    iterate_tree_recursive(solver, solver->tree);
}

/* ------------------------------------------------------------------------- */
static void
reset_solved_data_recursive(struct ik_node_t* node)
{
    node->solved_position = node->position;
    node->solved_rotation = node->rotation;

    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        reset_solved_data_recursive(child);
    BSTV_END_EACH
}
void
ik_solver_reset_solved_data(struct ik_solver_t* solver)
{
    if(solver->tree == NULL)
        return;

    reset_solved_data_recursive(solver->tree);
}

/* ------------------------------------------------------------------------- */
static int
recursive_get_all_effector_nodes(struct ik_node_t* node, struct ordered_vector_t* effector_nodes_list)
{
    if(node->effector != NULL)
        if(ordered_vector_push(effector_nodes_list, &node) < 0)
            return -1;

    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        if(recursive_get_all_effector_nodes(child, effector_nodes_list) < 0)
            return -1;
    BSTV_END_EACH

    return 0;
}
