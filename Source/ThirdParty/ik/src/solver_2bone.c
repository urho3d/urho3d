#include "ik/effector.h"
#include "ik/node.h"
#include "ik/log.h"
#include "ik/solver_2bone.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>

/* ------------------------------------------------------------------------- */
int
solver_2bone_construct(ik_solver_t* solver)
{
    two_bone_t* two_bone = (two_bone_t*)solver;

    /* set up derived functions */
    two_bone->destruct = solver_2bone_destruct;
    two_bone->post_chain_build = solver_2bone_post_chain_build;
    two_bone->solve = solver_2bone_solve;

    return 0;
}

/* ------------------------------------------------------------------------- */
void
solver_2bone_destruct(ik_solver_t* solver)
{
}

/* ------------------------------------------------------------------------- */
int
solver_2bone_post_chain_build(ik_solver_t* solver)
{
    /*
     * We need to assert that there really are only chains of length 1 and no
     * sub chains.
     */
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        if (ordered_vector_count(&island->root_chain.nodes) != 3) /* 3 nodes = 2 bones */
        {
            ik_log_message("ERROR: Your tree has chains that are longer or shorter than 2 bones. Are you sure you selected the correct solver algorithm?");
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
solver_2bone_solve(ik_solver_t* solver)
{
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        ik_node_t* node_tip;
        ik_node_t* node_mid;
        ik_node_t* node_base;
        vec3_t to_target;
        ik_real a, b, c, aa, bb, cc;

        assert(ordered_vector_count(&island->root_chain.nodes) > 2);
        node_tip = *(ik_node_t**)ordered_vector_get_element(&island->root_chain.nodes, 0);
        node_mid = *(ik_node_t**)ordered_vector_get_element(&island->root_chain.nodes, 1);
        node_base = *(ik_node_t**)ordered_vector_get_element(&island->root_chain.nodes, 2);

        assert(node_tip->effector != NULL);
        to_target = node_tip->effector->target_position;
        vec3_sub_vec3(to_target.f, node_base->position.f);

        /*
         * Form a triangle from the two segment lengths so we can calculate the
         * angles. Here's some visual help.
         *
         *   target *--.__  a
         *           \     --.___ (unknown position, needs solving)
         *            \      _-
         *           c \   _-
         *              \-    b
         *            base
         *
         */
        a = node_tip->segment_length;
        b = node_mid->segment_length;
        aa = a*a;
        bb = b*b;
        cc = vec3_length_squared(to_target.f);
        c = sqrt(cc);

        /* check if in reach */
        if (c < a + b)
        {
            /* Cosine law to get base angle (alpha) */
            quat_t alpha_rotation;
            ik_real alpha = acos((bb + cc - aa) / (2.0 * node_mid->segment_length * sqrt(cc)));
            ik_real cos_a = cos(alpha * 0.5);
            ik_real sin_a = sin(alpha * 0.5);

            /* Cross product of both segment vectors defines axis of rotation */
            alpha_rotation.vw.v = node_tip->position;
            vec3_sub_vec3(alpha_rotation.f, node_mid->position.f);  /* top segment */
            vec3_sub_vec3(node_mid->position.f, node_base->position.f);  /* bottom segment */
            vec3_cross(alpha_rotation.f, node_mid->position.f);

            /*
             * Set up quaternion describing the rotation of alpha. Need to
             * normalise vec3 component of quaternion so rotation is correct.
             */
            vec3_normalise(alpha_rotation.f);
            vec3_mul_scalar(alpha_rotation.f, sin_a);
            alpha_rotation.q.w = cos_a;

            /* Rotate side c and scale to length of side b to get the unknown position */
            node_mid->position = to_target;
            vec3_normalise(node_mid->position.f);
            vec3_mul_scalar(node_mid->position.f, node_mid->segment_length);
            quat_rotate_vec(node_mid->position.f, alpha_rotation.f);
            vec3_add_vec3(node_mid->position.f, node_base->position.f);

            node_tip->position = node_tip->effector->target_position;
        }
        else
        {
            /* Just point both segments at target */
            vec3_normalise(to_target.f);
            node_mid->position = to_target;
            node_tip->position = to_target;
            vec3_mul_scalar(node_mid->position.f, node_mid->segment_length);
            vec3_mul_scalar(node_tip->position.f, node_tip->segment_length);
            vec3_add_vec3(node_mid->position.f, node_base->position.f);
            vec3_add_vec3(node_tip->position.f, node_mid->position.f);
        }
    ORDERED_VECTOR_END_EACH

    return 0;
}
