#include "ik/solver_MSS.h"

/* ------------------------------------------------------------------------- */
int
solver_MSS_construct(ik_solver_t* solver)
{
    solver->destruct = solver_MSS_destruct;
    solver->solve = solver_MSS_solve;
    
    return 0;
}

/* ------------------------------------------------------------------------- */
void 
solver_MSS_destruct(ik_solver_t* solver)
{
}

/* ------------------------------------------------------------------------- */
int 
solver_MSS_solve(ik_solver_t* solver)
{
    return 0;
}
