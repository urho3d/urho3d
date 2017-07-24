#include "ik/config.h"
#include "ik/solver.h"

C_HEADER_BEGIN

struct mss_t
{
    SOLVER_DATA_HEAD
};

int
solver_MSS_construct(ik_solver_t* solver);

void
solver_MSS_destruct(ik_solver_t* solver);

int
solver_MSS_solve(ik_solver_t* solver);

C_HEADER_END
