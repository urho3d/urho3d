#include "ik/chain_tree.h"
#include "ik/effector.h"
#include "ik/log.h"
#include "ik/node.h"
#include "ik/solver_1bone.h"
#include <stddef.h>
#include <assert.h>

/* ------------------------------------------------------------------------- */
int
solver_1bone_construct(ik_solver_t* solver)
{
    one_bone_t* one_bone = (one_bone_t*)solver;

    /* set up derived functions */
    one_bone->destruct = solver_1bone_destruct;
    one_bone->post_chain_build = solver_1bone_post_chain_build;
    one_bone->solve = solver_1bone_solve;

    return 0;
}

/* ------------------------------------------------------------------------- */
void
solver_1bone_destruct(ik_solver_t* solver)
{
}

/* ------------------------------------------------------------------------- */
int
solver_1bone_post_chain_build(ik_solver_t* solver)
{
    /*
     * We need to assert that there really are only chains of length 1 and no
     * sub chains.
     */
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        if (ordered_vector_count(&island->root_chain.nodes) != 2) /* 2 nodes = 1 bone */
        {
            ik_log_message("ERROR: Your tree has chains that are longer than 1 bone. Are you sure you selected the correct solver algorithm?");
            return -1;
        }
        if (ordered_vector_count(&island->root_chain.children) > 0)
        {
            ik_log_message("ERROR: Your tree has child chains. This solver does not support arbitrary trees. You will need to switch to another algorithm (e.g. FABRIK)");
            return -1;
        }
    ORDERED_VECTOR_END_EACH

    return 0;
}

/* ------------------------------------------------------------------------- */
int
solver_1bone_solve(ik_solver_t* solver)
{
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        ik_node_t* node_tip;
        ik_node_t* node_base;
        chain_t* root_chain = &island->root_chain;

        assert(ordered_vector_count(&root_chain->nodes) > 1);
        node_tip = *(ik_node_t**)ordered_vector_get_element(&root_chain->nodes, 0);
        node_base = *(ik_node_t**)ordered_vector_get_element(&root_chain->nodes, 1);

        assert(node_tip->effector != NULL);
        node_tip->position = node_tip->effector->target_position;

        vec3_sub_vec3(node_tip->position.f, node_base->position.f);
        vec3_normalise(node_tip->position.f);
        vec3_mul_scalar(node_tip->position.f, node_tip->segment_length);
        vec3_add_vec3(node_tip->position.f, node_base->position.f);
    ORDERED_VECTOR_END_EACH

    return 0;
}
