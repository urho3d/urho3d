#include "ik/constraint.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include <string.h>
#include <assert.h>

static void
apply_stiff(ik_node_t* node);
static void
apply_hinge(ik_node_t* node);
static void
apply_cone(ik_node_t* node);

/* ------------------------------------------------------------------------- */
ik_constraint_t*
ik_constraint_create(ik_constraint_type_e constraint_type)
{
    ik_constraint_t* constraint = (ik_constraint_t*)MALLOC(sizeof *constraint);
    if (constraint == NULL)
    {
        ik_log_message("Failed to allocate constraint: Out of memory");
        return NULL;
    }

    memset(constraint, 0, sizeof *constraint);
    ik_constraint_set(constraint, constraint_type);

    return constraint;
}

/* ------------------------------------------------------------------------- */
void
ik_constraint_set(ik_constraint_t* constraint, ik_constraint_type_e constraint_type)
{
    switch (constraint_type)
    {
        case IK_CONSTRAINT_STIFF:
            constraint->apply = apply_stiff;
            break;

        case IK_CONSTRAINT_HINGE:
            constraint->apply = apply_hinge;
            break;

        case IK_CONSTRAINT_CONE:
            constraint->apply = apply_cone;
            break;
    }
    
    constraint->type = constraint_type;
}

/* ------------------------------------------------------------------------- */
void
ik_constraint_set_custom(ik_constraint_t* constraint, ik_constraint_apply_func callback)
{
    constraint->apply = callback;
}

/* ------------------------------------------------------------------------- */
void
ik_constraint_destroy(ik_constraint_t* constraint)
{
    FREE(constraint);
}

/* ------------------------------------------------------------------------- */
/* Constraint implementations (static) */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
static void
apply_stiff(ik_node_t* node)
{
    /*
     * The stiff constraint should never actually be reached, because joints
     * that have a stiff constraint will be excluded from the chain tree
     * entirely. This function exists solely to debug the chain tree.
     */
    assert(1);
}

/* ------------------------------------------------------------------------- */
static void
apply_hinge(ik_node_t* node)
{
}

/* ------------------------------------------------------------------------- */
static void
apply_cone(ik_node_t* node)
{
}
