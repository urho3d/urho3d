#ifndef IK_NODE_H
#define IK_NODE_H

#include "ik/config.h"
#include "ik/bst_vector.h"
#include "ik/vec3.h"
#include "ik/quat.h"

C_HEADER_BEGIN

/*!
 * @brief Represents one node in the tree to be solved.
 */
struct ik_node_t
{
    /*!
     * @brief Allows the user of this library to store custom data per node
     * @note Can be set and retrieved directly without issue.
     *
     * This is especially useful in c++ applications which need to store the
     * "this" pointer to their own scene graph nodes. The user data can be
     * accessed in callback functions to make object calls again.
     *
     * For instance:
     * ```cpp
     * // A node in your scene graph
     * MyNode* node = GetMyNode();
     *
     * ik_solver_t* solver = ik_solver_create(SOLVER_FABRIK);
     * ik_node_t* ikNode = ik_node_create(node->GetID());
     * ikNode->user_data = node; // Store pointer to your own node object
     *
     * // ---- elsewhere ------
     * static void ApplyResultsCallback(ik_node_t* ikNode)
     * {
     *     Node* node = (Node*)ikNode->user_data; // Extract your own node object again
     *     node->SetPosition(ikNode->solved_position);
     * }
     * ```
     */
    void* user_data;

    /*!
     * @brief The initial global position (in world space).
     * @note Must be set by the user to get correct results. This value can
     * be set and retrieved at any time.
     * @note The default value is (0, 0, 0).
     */
    vec3_t original_position;

    /*!
     * @brief The initial global rotation (in world space).
     * @note Must be set by the user to get correct results if the solver has
     * angle computations enabled (SOLVER_CALCULATE_FINAL_ANGLES).
     * @note The default value is the identity quaternion.
     */
    quat_t original_rotation;

    /*!
     * @brief After the solver is executed, the solved global (world) position
     * is stored here and can be retrieved.
     */
    vec3_t position;

    /*!
     * @brief After the solver is executed, the solved global (world) rotation
     * is stored here and can be retrieved.
     */
    quat_t rotation;

    /*!
     * @brief Global identifier for this node. The identifier must be unique
     * within the tree, but separate trees may re-use the same IDs again. The
     * ID can later be used to retrieve nodes from the tree again.
     * @note Don't change this if this node has a parent. If you need to change
     * the guid then unlink the node, change it, and re-add it as a child.
     */
    uint32_t guid;

    /*!
     * @brief The end effector object.
     * @note This pointer should not be changed directly. You can however set
     * the target position/rotation of the effector by writing to
     * node->effector->target_position or node->effector->target_rotation.
     * @note May be NULL.
     */
    ik_effector_t* effector;

    ik_constraint_t* constraint;

    ik_real stiffness;
    ik_real rotation_weight;

    /* Private data */
    ik_real segment_length;
    ik_node_t* parent;
    bstv_t children;    /* ik_node_t objects */
};

/*!
 * @brief Creates a new node and returns it. Each node requires a tree-unique
 * ID, which can be used later to search for nodes in the tree.
 */
IK_PUBLIC_API ik_node_t*
ik_node_create(uint32_t guid);

/*!
 * @brief Constructs an already allocated node.
 */
IK_PUBLIC_API void
ik_node_construct(ik_node_t* node, uint32_t guid);

/*!
 * @brief Destructs a node, destroying all children in the process, but does
 * not deallocate the node object itself.
 */
IK_PUBLIC_API void
ik_node_destruct(ik_node_t* node);

/*!
 * @brief Destructs and frees the node, destroying all children in the process.
 * If the node was part of a tree, then it will be removed from its parents.
 * @note You will need to rebuild the solver's tree before solving.
 */
IK_PUBLIC_API void
ik_node_destroy(ik_node_t* node);

/*!
 * @brief Attaches a node as a child to another node. The parent node gains
 * ownership of the child node and is responsible for deallocating it.
 * @note You will need to rebuild the solver's tree before solving.
 */
IK_PUBLIC_API void
ik_node_add_child(ik_node_t* node, ik_node_t* child);

/*!
 * @brief Unlinks a node from the tree, without destroying anything. All
 * children of the unlinked node remain in tact and will no longer be
 * affiliated with the original tree.
 * @note You will need to rebuild the solver's tree before solving.
 */
IK_PUBLIC_API void
ik_node_unlink(ik_node_t* node);

/*!
 * @brief Searches recursively for a node in a tree with the specified global
 * identifier.
 * @return Returns NULL if the node was not found, otherwise the node is
 * returned.
 */
IK_PUBLIC_API ik_node_t*
ik_node_find_child(ik_node_t* node, uint32_t guid);

/*!
 * @brief Attaches an effector object to the node. The node gains ownership
 * of the effector and is responsible for its deallocation. If the node
 * already owns an effector, then it is first destroyed.
 * @note You will need to rebuild the solver's tree before solving.
 */
IK_PUBLIC_API void
ik_node_attach_effector(ik_node_t* node, ik_effector_t* effector);

/*!
 * @brief Removes and destroys the node's effector, if it exists. The field
 * node->effector is set to NULL.
 * @note You will need to rebuild the solver's tree before solving.
 */
IK_PUBLIC_API void
ik_node_destroy_effector(ik_node_t* node);

/*!
 * @brief The constraint is attached to the specified node, but applies to the
 * parent of this node. In other words, if you wish to constraint the rotation
 * of node A then you must attach said constraint to the **child** of node A.
 *
 * Constraints are a bit strange in how they are stored. They don't apply to
 * single nodes, rather, they apply to entire segments (edges connecting nodes).
 * This is not apparent in a single chain of nodes, but becomes apparent if you
 * consider a tree structure.
 *
 *    A   C
 *     \ /
 *      B
 *      |
 *      D
 *
 * If you wanted to constraint the rotation of D, then you would add a
 * constraint to node B. If you wanted to constraint the rotation of the
 * segment B-A then you would add a constraint to node A.
 *
 * @param[in] node The child of the node you wish to constrain.
 * @param[in] constraint The constraint object. The node gains ownership of
 * the constraint and is responsible for its deallocation. If the node already
 * owns a constraint, then it is first destroyed.
 */
IK_PUBLIC_API void
ik_node_attach_constraint(ik_node_t* node, ik_constraint_t* constraint);

/*!
 * @brief Removes and destroys the node's constraint, if it exists. The field
 * node->constraint is set to NULL.
 */
IK_PUBLIC_API void
ik_node_destroy_constraint(ik_node_t* node);

/*!
 * @brief Dumps all nodes recursively to DOT format. You can use graphviz (
 * or other compatible tools) to generate a graphic of the tree.
 */
IK_PUBLIC_API void
ik_node_dump_to_dot(ik_node_t* node, const char* file_name);

IK_PUBLIC_API void
ik_node_global_to_local(ik_node_t* node);

IK_PUBLIC_API void
ik_node_local_to_global(ik_node_t* node);

C_HEADER_END

#endif /* IK_NODE_H */
