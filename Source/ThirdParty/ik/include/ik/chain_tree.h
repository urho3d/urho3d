/*!
 * @file chain.h
 * @brief Manages synthesising the user specified tree of nodes (ik_node_t)
 * into a structure more optimal for solvers.
 *
 *
 */
#ifndef IK_CHAIN_H
#define IK_CHAIN_H

#include "ik/config.h"
#include "ik/ordered_vector.h"

C_HEADER_BEGIN

struct chain_t
{
    /*
     * List of ik_node_t* references that belong to this chain.
     * NOTE: The first node in this list is the effector (i.e. the *end* of the
     * chain). The nodes are in reverse.
     */
    ordered_vector_t nodes;
    /* list of chain_t objects */
    ordered_vector_t children;
};

struct chain_island_t
{
    chain_t       root_chain;

    /*
     * List of ik_node_t* objects. This list contains the child nodes of IK
     * effectors, the children of which aren't part of the IK problem but need
     * to be properly updated to match the new transform of the solved tree.
     * TODO Is this implemented yet?
     */
    ordered_vector_t transform_dependent_nodes;
};

struct chain_tree_t
{
    ordered_vector_t islands; /* list of chain_island_t objects */
};

void
chain_tree_construct(chain_tree_t* chain_trees);

void
chain_tree_destruct(chain_tree_t* chain_trees);

void
chain_island_construct(chain_island_t* chain_island);

void
chain_island_destruct(chain_island_t* chain_island);

chain_t*
chain_create(void);

void
chain_destroy(chain_t* chain);

/*!
 * @brief Initialises an allocated chain object.
 */
void
chain_construct(chain_t* chain);

/*!
 * @brief Destroys and frees all members, but does not deallocate the chain
 * object itself.
 */
void
chain_destruct(chain_t* chain);


/*!
 * @brief Clears all children and nodes.
 */
void
chain_clear_free(chain_t* chain);

/*!
 * @brief Breaks down the relevant nodes of the scene graph into a tree of
 * chains. FABRIK can then more efficiently solve each chain individually.
 *
 * A "sub-base joint" is a node in the scene graph where at least two end
 * effector nodes eventually join together. FABRIK only works on single
 * chains of joints at a time. The end position of every sub-base joint is
 * the average of the resulting multiple positions after running FABRIK on
 * each chain. Said average position becomes the new target position for
 * the next chain connected to it.
 *
 * This algorithm finds all sub-base joints and generates chains between
 * base, sub-base joints, and end effectors. These chains are inserted into
 * the chain tree.
 */
int
rebuild_chain_tree(ik_solver_t* solver);

void
calculate_segment_lengths(chain_tree_t* chain_tree);

/*!
 * @brief Counts all of the chains in the tree, excluding the root chain.
 */
int
count_chains_exclude_root(chain_tree_t* chain_tree);

void
calculate_global_rotations(chain_t* chain);

#ifdef IK_DOT_OUTPUT
/*!
 * @brief Dumps the chain tree to DOT format.
 * @param[in] root The root node of the user created tree. This is a parameter
 * because the root chain does not necessarily hold the root node of the tree
 * because the root node doesn't have to be part of the IK problem.
 * @note Doesn't necessarily have to be the root node, it will dump the tree
 * beginning at this node.
 * @param[in] chain Usually the root chain. Doesn't necessarily have to be the
 * root, in which case it will dump beginning at this chain.
 * @param[in] file_name The name of the file to dump to.
 */
void
dump_to_dot(ik_node_t* root, chain_tree_t* chain_tree, const char* file_name);
#endif /* IK_DOT_OUTPUT */

C_HEADER_END

#endif /* IK_CHAIN_H */
