#include "ik/solver_MSD.h"

/* ------------------------------------------------------------------------- */
int
solver_MSD_construct(ik_solver_t* solver)
{
    solver->destruct = solver_MSD_destruct;
    solver->solve = solver_MSD_solve;
    
    return 0;
}

/* ------------------------------------------------------------------------- */
void 
solver_MSD_destruct(ik_solver_t* solver)
{
}

/* ------------------------------------------------------------------------- */
int 
solver_MSD_solve(ik_solver_t* solver)
{
    return 0;
}
