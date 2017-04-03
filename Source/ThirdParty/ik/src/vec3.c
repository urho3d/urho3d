#include "ik/vec3.h"
#include <string.h>
#include <math.h>

/* ------------------------------------------------------------------------- */
void
vec3_set_zero(ik_real* v)
{
    memset(v, 0, sizeof *v);
}

/* ------------------------------------------------------------------------- */
void
vec3_add_vec3(ik_real* v1, const ik_real* v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}

/* ------------------------------------------------------------------------- */
void
vec3_sub_vec3(ik_real* v1, const ik_real* v2)
{
    v1[0] -= v2[0];
    v1[1] -= v2[1];
    v1[2] -= v2[2];
}

/* ------------------------------------------------------------------------- */
void
vec3_mul_scalar(ik_real* v, ik_real scalar)
{
    v[0] *= scalar;
    v[1] *= scalar;
    v[2] *= scalar;
}

/* ------------------------------------------------------------------------- */
void
vec3_div_scalar(ik_real* v, ik_real scalar)
{
    v[0] /= scalar;
    v[1] /= scalar;
    v[2] /= scalar;
}

/* ------------------------------------------------------------------------- */
ik_real
vec3_length_squared(const ik_real* v)
{
    return vec3_dot(v, v);
}

/* ------------------------------------------------------------------------- */
ik_real
vec3_length(const ik_real* v)
{
    return sqrt(vec3_length_squared(v));
}

/* ------------------------------------------------------------------------- */
void
vec3_normalise(ik_real* v)
{
    ik_real length = vec3_length(v);
    if(length != 0.0)
        length = 1.0 / length;
    v[0] *= length;
    v[1] *= length;
    v[2] *= length;
}

/* ------------------------------------------------------------------------- */
ik_real
vec3_dot(const ik_real* v1, const ik_real* v2)
{
    return v1[0] * v2[0] +
           v1[1] * v2[1] +
           v1[2] * v2[2];
}

/* ------------------------------------------------------------------------- */
void
vec3_cross(ik_real* v1, const ik_real* v2)
{
    ik_real v1x = v1[1] * v2[2] - v2[1] * v1[2];
    ik_real v1z = v1[0] * v2[1] - v2[0] * v1[1];
    v1[1]       = v1[2] * v2[0] - v2[2] * v1[0];
    v1[0] = v1x;
    v1[2] = v1z;
}
