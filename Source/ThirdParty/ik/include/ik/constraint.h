#ifndef IK_CONSTRAINT_H
#define IK_CONSTRAINT_H

#include "ik/config.h"

C_HEADER_BEGIN

typedef void (*ik_constraint_apply_func)(ik_node_t*);

typedef enum ik_constraint_type_e
{
    IK_CONSTRAINT_STIFF,
    IK_CONSTRAINT_HINGE,
    IK_CONSTRAINT_CONE
} ik_constraint_type_e;

struct ik_constraint_t
{
    ik_constraint_type_e type;
    ik_constraint_apply_func apply;
};

/*!
 * @brief Creates a new constraint object. It can be attached to any node in the
 * tree using ik_node_attach_constraint().
 */
IK_PUBLIC_API ik_constraint_t*
ik_constraint_create(ik_constraint_type_e constraint_type);

/*!
 * @brief Sets the type of constraint to enforce.
 * @note The tree must be rebuilt only if you change to or from the "stiff"
 * constraint (IK_CONSTRAINT_STIFF). Switching to any other constraint does not
 * require a rebuild. The reason for this is because the stiff constraint
 * causes the node to be excluded entirely from the chain tree, and determining
 * this requires a rebuild.
 */
IK_PUBLIC_API void
ik_constraint_set(ik_constraint_t* constraint, ik_constraint_type_e constraint_type);

/*!
 * @brief Allows the user to specify a custom callback function for enforcing
 * a constraint.
 */
IK_PUBLIC_API void
ik_constraint_set_custom(ik_constraint_t* constraint, ik_constraint_apply_func callback);

/*!
 * @brief Destroys and frees a constraint object. This should **NOT** be called
 * on constraints that are attached to nodes. Use ik_node_destroy_constraint()
 * instead.
 */
IK_PUBLIC_API void
ik_constraint_destroy(ik_constraint_t* constraint);

C_HEADER_END

#endif /* IK_CONSTRAINT_H */
