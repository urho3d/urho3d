#include "ik/chain_tree.h"
#include "ik/effector.h"
#include "ik/node.h"
#include "ik/util.h"
#include <assert.h>

typedef struct effector_data_t
{
    ik_real rotation_weight;
    ik_real rotation_weight_decay;
} effector_data_t;

/* ------------------------------------------------------------------------- */
static effector_data_t
calculate_rotation_weight_decays_recursive(chain_t* chain)
{
    int average_count;
    int node_idx, node_count;
    effector_data_t effector_data = {0.0, 0.0};

    /*
     * Find the rotation weight of this chain's last node by averaging the
     * rotation weight of all child chain's first nodes.
     *
     * If there are no child chains, then the first node in the chain must
     * contain an effector. Initialise the weight parameters from said
     * effector.
     *
     * If there are child chains then average the effector data we've
     * accumulated.
     */
    average_count = 0;
    ORDERED_VECTOR_FOR_EACH(&chain->children, chain_t, child)
        effector_data_t child_eff_data =
                calculate_rotation_weight_decays_recursive(child);
        effector_data.rotation_weight += child_eff_data.rotation_weight;
        effector_data.rotation_weight_decay += child_eff_data.rotation_weight_decay;
        ++average_count;
    ORDERED_VECTOR_END_EACH

    if (average_count == 0)
    {
        ik_node_t* effector_node = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, 0);
        ik_effector_t* effector = effector_node->effector;

        effector_data.rotation_weight = effector->rotation_weight;
        effector_data.rotation_weight_decay = effector->rotation_decay;
    }
    else
    {
        ik_real div = 1.0 / average_count;
        effector_data.rotation_weight *= div;
        effector_data.rotation_weight_decay *= div;
    }

    /*
     * With the rotation weight of the last node calculated, we can now iterate
     * the nodes in the chain and set each rotation weight, decaying a little
     * bit every time. Note that we exclude the last node, because it will
     * be handled by the parent chain. If there is no parent chain then the
     * non-recursive caller of this function will set the rotation weight of
     * the root node.
     */
    node_count = ordered_vector_count(&chain->nodes) - 1;
    for (node_idx = 0; node_idx < node_count; ++node_idx)
    {
        ik_node_t* node = *(ik_node_t**)ordered_vector_get_element(&chain->nodes, node_idx);
        node->rotation_weight = effector_data.rotation_weight;
        effector_data.rotation_weight *= effector_data.rotation_weight_decay;
    }

    /* Rotation weight is now equal to that of this chain's base node */
    return effector_data;
}

/* ------------------------------------------------------------------------- */
void
ik_calculate_rotation_weight_decays(chain_tree_t* chain_tree)
{
    /*
     * The recursive version of this function does not set the rotation weight
     * of the first node in every tree that gets passed to it, but it does
     * return the rotation weight that *would have been set* (which gets used
     * recursively to calculate the average rotation weight in the case of
     * multiple child chains).
     *
     * For these reasons we iterate the chain islands and set the first node in
     * each island to the returned rotation weight.
     */
    ORDERED_VECTOR_FOR_EACH(&chain_tree->islands, chain_island_t, island)
        ik_node_t* root_node;
        effector_data_t effector_data = calculate_rotation_weight_decays_recursive(&island->root_chain);
        int last_idx = ordered_vector_count(&island->root_chain.nodes) - 1;
        assert(last_idx > 0);
        root_node = *(ik_node_t**)ordered_vector_get_element(&island->root_chain.nodes, last_idx);
        root_node->rotation_weight = effector_data.rotation_weight;
    ORDERED_VECTOR_END_EACH
}
