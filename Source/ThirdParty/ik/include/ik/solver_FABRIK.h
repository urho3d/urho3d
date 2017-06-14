#ifndef IK_SOLVER_FABRIK_H
#define IK_SOLVER_FABRIK_H

#include "ik/config.h"
#include "ik/ordered_vector.h"
#include "ik/solver.h"

C_HEADER_BEGIN

struct chain_t
{
    struct ordered_vector_t nodes;    /* list of node_t* references */
    struct ordered_vector_t children; /* list of chain_t objects */
};

struct fabrik_t
{
    SOLVER_DATA_HEAD
    struct chain_t* chain_tree;
};

struct ik_solver_t*
solver_FABRIK_create(void);

void
solver_FABRIK_destroy(struct ik_solver_t* solver);

int
solver_FABRIK_rebuild_data(struct ik_solver_t* solver);

void
solver_FABRIK_recalculate_segment_lengths(struct ik_solver_t* solver);

int
solver_FABRIK_solve(struct ik_solver_t* solver);

C_HEADER_END

#endif /* IK_SOLVER_FABRIK_H */
