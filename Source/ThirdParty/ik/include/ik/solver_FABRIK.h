#ifndef IK_SOLVER_FABRIK_H
#define IK_SOLVER_FABRIK_H

#include "ik/config.h"
#include "ik/ordered_vector.h"
#include "ik/solver.h"

C_HEADER_BEGIN

struct fabrik_t
{
    SOLVER_DATA_HEAD
};

int
solver_FABRIK_construct(ik_solver_t* solver);

void
solver_FABRIK_destruct(ik_solver_t* solver);

int
solver_FABRIK_solve(ik_solver_t* solver);

C_HEADER_END

#endif /* IK_SOLVER_FABRIK_H */
