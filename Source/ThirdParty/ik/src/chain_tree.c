#include "ik/bst_vector.h"
#include "ik/effector.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include "ik/ordered_vector.h"
#include "ik/solver.h"
#include <assert.h>
#include <stdio.h>

enum node_marking_e
{
    MARK_NONE = 0,
    MARK_SPLIT,
    MARK_SECTION
};

/* ------------------------------------------------------------------------- */
void
chain_tree_construct(chain_tree_t* chain_tree)
{
    ordered_vector_construct(&chain_tree->islands, sizeof(chain_island_t));
}

/* ------------------------------------------------------------------------- */
void
chain_tree_destruct(chain_tree_t* chain_tree)
{
    ORDERED_VECTOR_FOR_EACH(&chain_tree->islands, chain_island_t, island)
        chain_island_destruct(island);
    ORDERED_VECTOR_END_EACH
    ordered_vector_clear_free(&chain_tree->islands);
}

/* ------------------------------------------------------------------------- */
void
chain_island_construct(chain_island_t* chain_tree)
{
    chain_construct(&chain_tree->root_chain);
    ordered_vector_construct(&chain_tree->transform_dependent_nodes, sizeof(ik_node_t*));
}

/* ------------------------------------------------------------------------- */
void
chain_island_destruct(chain_island_t* chain_tree)
{
    ordered_vector_clear_free(&chain_tree->transform_dependent_nodes);
    chain_destruct(&chain_tree->root_chain);
}

/* ------------------------------------------------------------------------- */
chain_t*
chain_create(void)
{
    chain_t* chain = (chain_t*)MALLOC(sizeof *chain);
    if (chain == NULL)
    {
        ik_log_message("Failed to allocate chain: out of memory");
        return NULL;
    }
    chain_construct(chain);
    return chain;
}

/* ------------------------------------------------------------------------- */
void
chain_destroy(chain_t* chain)
{
    chain_destruct(chain);
    FREE(chain);
}

/* ------------------------------------------------------------------------- */
void
chain_construct(chain_t* chain)
{
    ordered_vector_construct(&chain->nodes, sizeof(ik_node_t*));
    ordered_vector_construct(&chain->children, sizeof(chain_t));
}

/* ------------------------------------------------------------------------- */
void
chain_clear_free(chain_t* chain)
{
    chain_destruct(chain); /* does the same thing as de*/
}

/* ------------------------------------------------------------------------- */
void
chain_destruct(chain_t* chain)
{
    ORDERED_VECTOR_FOR_EACH(&chain->children, chain_t, child_chain)
        chain_destruct(child_chain);
    ORDERED_VECTOR_END_EACH
    ordered_vector_clear_free(&chain->children);
    ordered_vector_clear_free(&chain->nodes);
}

/* ------------------------------------------------------------------------- */
static int
count_chains_recursive(chain_t* chain)
{
    int counter = 1;
    ORDERED_VECTOR_FOR_EACH(&chain->children, chain_t, child)
        counter += count_chains_recursive(child);
    ORDERED_VECTOR_END_EACH
    return counter;
}
int
count_chains_exclude_root(chain_tree_t* chain_tree)
{
    int counter = 1;
    ORDERED_VECTOR_FOR_EACH(&chain_tree->islands, chain_island_t, island)
        counter += count_chains_recursive(&island->root_chain);
    ORDERED_VECTOR_END_EACH
    return counter - 1; /* exclude root chain */
}

/* ------------------------------------------------------------------------- */
static int
mark_involved_nodes(ik_solver_t* solver, bstv_t* involved_nodes)
{
    /*
     * Traverse the chain of parents starting at each effector node and ending
     * at the root node of the tree and mark every node on the way. Each
     * effector specifies a maximum chain length, which means it's possible
     * that we won't hit the root node.
     */
    ordered_vector_t* effector_nodes_list = &solver->effector_nodes_list;
    ORDERED_VECTOR_FOR_EACH(effector_nodes_list, ik_node_t*, p_effector_node)

        /*
         * Set up chain length counter. If the chain length is 0 then it is
         * infinitely long. Set the counter to -1 in this case to skip the
         * escape condition.
         */
        int chain_length_counter;
        ik_node_t* node = *p_effector_node;
        assert(node->effector != NULL);
        chain_length_counter = node->effector->chain_length == 0 ? -1 : (int)node->effector->chain_length;

        /*
         * Mark nodes that are at the base of the chain differently, so the
         * chains can be split correctly later. Section markings will overwrite
         * break markings.
         *
         * Additionally, there is a special constraint (IK_CONSTRAINT_STIFF)
         * that restricts all rotations of a node. If this constraint is
         * imposed on a particular node, mark it differently as well so the
         * surrounding nodes can be combined into a single bone properly later.
         *
         * NOTE: The node->constraint field specifies constraints for
         * the *parent* node, not for the current node. However, we will be
         * marking the *current* node, not the parent node.
         */
        for (; node != NULL; node = node->parent)
        {
            enum node_marking_e* current_marking;
            enum node_marking_e marking = MARK_SECTION;
            if (chain_length_counter == 0)
                marking = MARK_SPLIT;

            current_marking = (enum node_marking_e*)bstv_find_ptr(involved_nodes, node->guid);
            if (current_marking == NULL)
            {
                if (bstv_insert(involved_nodes, node->guid, (void*)(intptr_t)marking) < 0)
                {
                    ik_log_message("Ran out of memory while marking involved nodes");
                    return -1;
                }
            }
            else
            {
                if (chain_length_counter != 0)
                    *current_marking = marking;
            }

            if (chain_length_counter-- == 0)
                break;
        }
    ORDERED_VECTOR_END_EACH

    return 0;
}

/* ------------------------------------------------------------------------- */
static int
recursively_build_chain_tree(chain_tree_t* chain_tree,
                             chain_t* chain_current,
                             ik_node_t* node_base,
                             ik_node_t* node_current,
                             bstv_t* involved_nodes)
{
    int marked_children_count;
    ik_node_t* child_node_base = node_base;
    chain_t* child_chain = chain_current;

    /* can remove the mark from the set to speed up future checks */
    enum node_marking_e marking =
        (enum node_marking_e)(intptr_t)bstv_erase(involved_nodes, node_current->guid);

    switch(marking)
    {
        /*
         * If this node was marked as the base of a chain then split the chain
         * at this point by moving the pointer to the base node down the tree
         * to the current node and set the current chain to NULL so a new
         * island is created (this is necessary because all children of this
         * node are necessarily part of an isolated tree).
         */
        case MARK_SPLIT:
            child_node_base = node_current;
            chain_current = NULL;
            break;
        /*
         * If this node is not marked at all, cut off any previous chain but
         * continue (fall through) as if a section was marked. It's possible
         * that there are isolated chains somewhere further down the tree.
         */
        case MARK_NONE:
            node_base = node_current;
            /* falling through on purpose */

        case MARK_SECTION:
            /*
             * If the current node has at least two children marked as sections
             * or if (the current node is an effector node, but only if (the base
             * node is not equal to this node (that is, we need to avoid chains
             * that would have less than 2 nodes), then we must also split the
             * chain at this point.
             */
            marked_children_count = 0;
            BSTV_FOR_EACH(&node_current->children, ik_node_t, child_guid, child)
                if ((enum node_marking_e)(intptr_t)bstv_find(involved_nodes, child_guid) == MARK_SECTION)
                    if (++marked_children_count == 2)
                        break;
            BSTV_END_EACH
            if ((marked_children_count == 2 || node_current->effector != NULL) && node_current != node_base)
            {
                ik_node_t* node;

                if (chain_current == NULL)
                {
                    /*
                     * If this is the first chain in the island, create and
                     * initialise it in the chain tree.
                     */
                    chain_island_t* island = ordered_vector_push_emplace(&chain_tree->islands);
                    if (island == NULL)
                    {
                        ik_log_message("Failed to create chain island: Ran out of memory");
                        return -1;
                    }
                    chain_island_construct(island);
                    child_chain = &island->root_chain;
                }
                else
                {
                    /*
                     * This is not the first chain of the island, so create a
                     * new child chain in the current chain and initialise it.
                     */
                    child_chain = ordered_vector_push_emplace(&chain_current->children);
                    if (child_chain == NULL)
                    {
                        ik_log_message("Failed to create child chain: Ran out of memory");
                        return -1;
                    }
                    chain_construct(child_chain);
                }

                /*
                 * Add pointers to all nodes that are part of this chain into
                 * the chain's list, starting with the end node.
                 */
                for (node = node_current; node != node_base; node = node->parent)
                    ordered_vector_push(&child_chain->nodes, &node);
                ordered_vector_push(&child_chain->nodes, &node_base);

                /*
                 * Update the base node to be this node so deeper chains are built back
                 * to this node
                 */
                child_node_base = node_current;
            }
            break;
    }

    /* Recurse into children of the current node. */
    BSTV_FOR_EACH(&node_current->children, ik_node_t, child_guid, child_node)
        if (recursively_build_chain_tree(
                chain_tree,
                child_chain,
                child_node_base,
                child_node,
                involved_nodes) < 0)
            return -1;
    BSTV_END_EACH

    return 0;
}

/* ------------------------------------------------------------------------- */
int
rebuild_chain_tree(ik_solver_t* solver)
{
    bstv_t involved_nodes;
    int involved_nodes_count;
#ifdef IK_DOT_OUTPUT
    char buffer[20];
    static int file_name_counter = 0;
#endif

    /* Clear all existing chain trees */
    ORDERED_VECTOR_FOR_EACH(&solver->chain_tree.islands, chain_island_t, island)
        chain_island_destruct(island);
    ORDERED_VECTOR_END_EACH
    ordered_vector_clear_free(&solver->chain_tree.islands);

    /*
     * Build a set of all nodes that are in a direct path with all of the
     * effectors.
     */
    bstv_construct(&involved_nodes);
    if (mark_involved_nodes(solver, &involved_nodes) < 0)
        goto mark_involved_nodes_failed;
    involved_nodes_count = bstv_count(&involved_nodes);

    recursively_build_chain_tree(&solver->chain_tree, NULL, solver->tree, solver->tree, &involved_nodes);

    /* Pre-compute offsets for each node in the chain tree in relation to their
     * parents */
    calculate_segment_lengths(&solver->chain_tree);

    /* DEBUG: Save chain tree to DOT */
#ifdef IK_DOT_OUTPUT
    sprintf(buffer, "tree%d.dot", file_name_counter++);
    dump_to_dot(solver->tree, solver->chain_tree, buffer);
#endif

    ik_log_message("There are %d effector(s) involving %d node(s). %d chain(s) were created",
                   ordered_vector_count(&solver->effector_nodes_list),
                   involved_nodes_count,
                   count_chains_exclude_root(&solver->chain_tree));

    bstv_clear_free(&involved_nodes);

    return 0;

    mark_involved_nodes_failed : bstv_clear_free(&involved_nodes);
    return -1;
}

/* ------------------------------------------------------------------------- */
static void
calculate_segment_lengths_in_island(chain_t* island)
{
    int last_idx = ordered_vector_count(&island->nodes) - 1;
    while (last_idx-- > 0)
    {
        ik_node_t* child_node =
            *(ik_node_t**)ordered_vector_get_element(&island->nodes, last_idx + 0);
        ik_node_t* parent_node =
            *(ik_node_t**)ordered_vector_get_element(&island->nodes, last_idx + 1);

        vec3_t diff = child_node->original_position;
        vec3_sub_vec3(diff.f, parent_node->original_position.f);
        child_node->segment_length = vec3_length(diff.f);
    }

    ORDERED_VECTOR_FOR_EACH(&island->children, chain_t, child)
        calculate_segment_lengths_in_island(child);
    ORDERED_VECTOR_END_EACH
}
void
calculate_segment_lengths(chain_tree_t* chain_tree)
{
    /* TODO: Implement again, take into consideration merged bones */
    ORDERED_VECTOR_FOR_EACH(&chain_tree->islands, chain_island_t, island)
        calculate_segment_lengths_in_island(&island->root_chain);
    ORDERED_VECTOR_END_EACH
}

/* ------------------------------------------------------------------------- */
static void
calculate_global_rotations_of_children(chain_t* chain)
{
    int average_count;
    quat_t average_rotation = {{0, 0, 0, 0}};

    /* Recurse into children chains */
    average_count = 0;
    ORDERED_VECTOR_FOR_EACH(&chain->children, chain_t, child)
        quat_t rotation;
        calculate_global_rotations(child);

        /* Note: All chains that aren't the root chain *MUST* have at least two nodes */
        assert(ordered_vector_count(&child->nodes) >= 2);
        rotation = (*(ik_node_t**)
                ordered_vector_get_element(&child->nodes,
                    ordered_vector_count(&child->nodes) - 1))->rotation;

        /*
         * Averaging quaternions taken from here
         * http://wiki.unity3d.com/index.php/Averaging_Quaternions_and_Vectors
         */
        quat_normalise_sign(rotation.f);
        quat_add_quat(average_rotation.f, rotation.f);
        ++average_count;
    ORDERED_VECTOR_END_EACH

    /*
     * Assuming there was more than 1 child chain and assuming we aren't the
     * root node, then the child chains we just iterated must share the same
     * base node (which is our tip node). Average the accumulated quaternion
     * and set this node's correct solved rotation.
     */
    if (average_count > 0 && ordered_vector_count(&chain->nodes) != 0)
    {
        quat_div_scalar(average_rotation.f, average_count);
        quat_normalise(average_rotation.f);
        (*(ik_node_t**)ordered_vector_get_element(&chain->nodes, 0))
            ->rotation = average_rotation;
    }
}

/* ------------------------------------------------------------------------- */
static void
calculate_delta_rotation_of_each_segment(chain_t* chain)
{
    int node_idx;

    /*
     * Calculate all of the delta angles of the joints. The resulting delta (!)
     * angles will be written to node->rotation
     */
    node_idx = ordered_vector_count(&chain->nodes) - 1;
    while (node_idx-- > 0)
    {
        ik_node_t* child_node  = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, node_idx + 0);
        ik_node_t* parent_node = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, node_idx + 1);

        /* calculate vectors for original and solved segments */
        vec3_t segment_original = child_node->original_position;
        vec3_t segment_solved   = child_node->position;
        vec3_sub_vec3(segment_original.f, parent_node->original_position.f);
        vec3_sub_vec3(segment_solved.f, parent_node->position.f);

        vec3_angle(parent_node->rotation.f, segment_original.f, segment_solved.f);
    }
}

/* ------------------------------------------------------------------------- */
void
calculate_global_rotations(chain_t* chain)
{
    int node_idx;

    /*
     * Calculates the "global" (world) angles of each joint and writes them to
     * each node->rotation slot.
     *
     * The angle between the original and solved segments are calculated using
     * standard vector math (dot product). The axis of rotation is calculated
     * with the cross product. From this data, a quaternion is constructed,
     * describing this delta rotation. Finally, in order to make the rotations
     * global instead of relative, the delta rotation is multiplied with
     * node->original_rotation, which should be a quaternion describing the
     * node's global rotation in the unsolved tree.
     *
     * The rotation of the base joint in the chain is returned so it can be
     * averaged by parent chains.
     */

    calculate_global_rotations_of_children(chain);
    calculate_delta_rotation_of_each_segment(chain);

    /*
     * At this point, all nodes have calculated their delta angles *except* for
     * the end effector nodes, which remain untouched. It makes sense to copy
     * the delta rotation of the parent node into the effector node by default.
     */
    node_idx = ordered_vector_count(&chain->nodes);
    if (node_idx > 1)
    {
        ik_node_t* effector_node  = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, 0);
        ik_node_t* parent_node = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, 1);
        effector_node->rotation.q = parent_node->rotation.q;
    }

    /*
     * Finally, apply initial global rotations to calculated delta rotations to
     * obtain the solved global rotations.
     */
    ORDERED_VECTOR_FOR_EACH(&chain->nodes, ik_node_t*, pnode)
        ik_node_t* node = *pnode;
        quat_mul_quat(node->rotation.f, node->original_rotation.f);
    ORDERED_VECTOR_END_EACH
}

/* ------------------------------------------------------------------------- */
#ifdef IK_DOT_OUTPUT
static void
dump_chain(ik_chain_t* chain, FILE* fp)
{
    int last_idx = ordered_vector_count(&chain->nodes) - 1;
    if (last_idx > 0)
    {
        fprintf(fp, "    %d [shape=record];\n",
            (*(ik_node_t**)ordered_vector_get_element(&chain->nodes, 0))->guid);
        fprintf(fp, "    %d [shape=record];\n",
            (*(ik_node_t**)ordered_vector_get_element(&chain->nodes, last_idx))->guid);
    }

    while (last_idx-- > 0)
    {
        fprintf(fp, "    %d -- %d [color=\"1.0 0.5 1.0\"];\n",
            (*(ik_node_t**)ordered_vector_get_element(&chain->nodes, last_idx + 0))->guid,
            (*(ik_node_t**)ordered_vector_get_element(&chain->nodes, last_idx + 1))->guid);
    }

    ORDERED_VECTOR_FOR_EACH(&chain->children, ik_chain_t, child)
        dump_chain(child, fp);
    ORDERED_VECTOR_END_EACH
}
static void
dump_node(ik_node_t* node, FILE* fp)
{
    if (node->effector != NULL)
        fprintf(fp, "    %d [color=\"0.6 0.5 1.0\"];\n", node->guid);
    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        fprintf(fp, "    %d -- %d;\n", node->guid, guid);
        dump_node(child, fp);
    BSTV_END_EACH
}
void
dump_to_dot(ik_node_t* node, ik_chain_t* chain, const char* file_name)
{
    FILE* fp = fopen(file_name, "w");
    if (fp == NULL)
        return;

    fprintf(fp, "graph chain_tree {\n");
    dump_node(node, fp);
    dump_chain(chain, fp);
    fprintf(fp, "}\n");

    fclose(fp);
}
#endif
