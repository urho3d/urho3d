#include "ik/config.h"
#include "ik/solver.h"

C_HEADER_BEGIN

struct msd_t
{
    SOLVER_DATA_HEAD
};

int
solver_MSD_construct(ik_solver_t* solver);

void
solver_MSD_destruct(ik_solver_t* solver);

int
solver_MSD_solve(ik_solver_t* solver);

C_HEADER_END
