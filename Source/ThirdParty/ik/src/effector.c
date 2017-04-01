#include "ik/effector.h"
#include "ik/memory.h"
#include "ik/node.h"
#include <string.h>

/* ------------------------------------------------------------------------- */
struct ik_effector_t*
ik_effector_create(void)
{
    struct ik_effector_t* effector = (struct ik_effector_t*)MALLOC(sizeof *effector);
    if(effector == NULL)
        return NULL;

    ik_effector_construct(effector);
    return effector;
}

/* ------------------------------------------------------------------------- */
void
ik_effector_construct(struct ik_effector_t* effector)
{
    memset(effector, 0, sizeof *effector);
    quat_set_identity(effector->target_rotation.f);
    effector->weight = 0;
    effector->rotation_weight = 1.0;
    effector->rotation_decay = 0.25;
}

/* ------------------------------------------------------------------------- */
void
ik_effector_destroy(struct ik_effector_t* effector)
{
    FREE(effector);
}

/* ------------------------------------------------------------------------- */
void
effector_attach(struct ik_effector_t* effector, struct ik_node_t* node)
{
    if(node->effector != NULL)
        ik_effector_destroy(node->effector);

    node->effector = effector;
}
