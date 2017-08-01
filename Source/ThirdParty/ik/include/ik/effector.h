#ifndef EFFECTOR_H
#define EFFECTOR_H

#include "ik/config.h"
#include "ik/vec3.h"
#include "ik/quat.h"

C_HEADER_BEGIN

typedef enum effector_flags_e
{
    /*!
     * @brief Causes intermediary weight values to rotate the target around the
     * chain's root instead of linearly interpolating the target. Can be more
     * appealing if the solved tree diverges a lot from the original tree
     * during weight transitions.
     */
    EFFECTOR_WEIGHT_NLERP            = 0x01
} effector_flgs_e;

/*!
 * @brief Specifies how a chain of nodes should be solved. The effector can
 * be attached to any node in a tree using ik_node_attach_effector(). The
 * effector specifies the target position and rotation of that node, as well
 * as how much influence the solver has on the tree (weight) and how many
 * child nodes are affected (chain_length).
 */
struct ik_effector_t
{
    /*!
     * @brief Can be set at any point, and should be updated whenever you have
     * a new target position to solve for. Specifies the global (world)
     * position where the node it is attached to should head for.
     * @note Default value is (0, 0, 0).
     */
    vec3_t   target_position;

    /*!
     * @brief Can be set at any point, and should be updated whenever you have
     * a new target rotation to solve for. Specifies the global (world)
     * rotation where the node it is attached to should head for.
     * @note Default value is the identity quaternion.
     */
    quat_t   target_rotation;

    /*!
     * @brief Specifies how much influence the solver has on the chain of
     * nodes. A value of 0.0 will cause the solver to completely ignore the
     * chain, while a value of 1.0 will cause the solver to try to place the
     * target node directly at target_position/target_rotation.
     *
     * This is useful for blending the solver in and out. For instance, if you
     * wanted to ground the legs of an animated character, you would want the
     * solver to do nothing during the time when the foot is in the air
     * (weight=0.0) and be fully active when the foot is on the ground
     * (weight=1.0).
     */
    ik_real  weight;

    ik_real rotation_weight;
    ik_real rotation_decay;

    /*!
     * @brief Specifies how many parent nodes should be affected. A value of
     * 0 means all of the parents, including the root node.
     * @note Changing the chain length requires the solver tree to be rebuilt
     * with ik_solver_rebuild_tree().
     */
    uint16_t chain_length;

    /*!
     * @brief Various behavioural settings. Check the enum effector_flags_e for
     * more information.
     */
    uint8_t flags;
};

/*!
 * @brief Creates a new effector object. It can be attached to any node in the
 * tree using ik_node_attach_effector().
 */
IK_PUBLIC_API ik_effector_t*
ik_effector_create(void);

/*!
 * @brief Constructs a previously allocated effector object.
 */
IK_PUBLIC_API void
ik_effector_construct(ik_effector_t* effector);

/*!
 * @brief Destroys and frees an effector object. This should **NOT** be called
 * on effectors that are attached to nodes. Use ik_node_destroy_effector()
 * instead.
 */
IK_PUBLIC_API void
ik_effector_destroy(ik_effector_t* effector);

C_HEADER_END

#endif /* EFFECTOR_H */
