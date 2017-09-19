#include "ik/quat.h"
#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
void
quat_set_identity(ik_real* IK_RESTRICT q)
{
    memset(q, 0, sizeof(ik_real) * 3);
    q[3] = 1;
}

/* ------------------------------------------------------------------------- */
void
quat_add_quat(ik_real* IK_RESTRICT q1, const ik_real* IK_RESTRICT q2)
{
    q1[0] += q2[0];
    q1[1] += q2[1];
    q1[2] += q2[2];
    q1[3] += q2[3];
}

/* ------------------------------------------------------------------------- */
ik_real
quat_mag(const ik_real* IK_RESTRICT q)
{
    return sqrt(q[3]*q[3] + q[2]*q[2] + q[1]*q[1] + q[0]*q[0]);
}

/* ------------------------------------------------------------------------- */
void
quat_conj(ik_real* IK_RESTRICT q)
{
    q[0] = -q[0];
    q[1] = -q[1];
    q[2] = -q[2];
}

/* ------------------------------------------------------------------------- */
void
quat_invert_sign(ik_real* IK_RESTRICT q)
{
    q[0] = -q[0];
    q[1] = -q[1];
    q[2] = -q[2];
    q[3] = -q[3];
}


/* ------------------------------------------------------------------------- */
void
quat_normalise(ik_real* IK_RESTRICT q)
{
    ik_real mag = quat_mag(q);
    if (mag != 0.0)
        mag = 1.0 / mag;
    q[0] *= mag;
    q[1] *= mag;
    q[2] *= mag;
    q[3] *= mag;
}

/* ------------------------------------------------------------------------- */
static void
mul_quat_no_normalise(ik_real* IK_RESTRICT q1, const ik_real* IK_RESTRICT q2)
{
    ik_real v1[3];
    ik_real v2[3];
    memcpy(v1, q1, sizeof(ik_real) * 3);
    memcpy(v2, q2, sizeof(ik_real) * 3);

    vec3_mul_scalar(v1, q2[3]);
    vec3_mul_scalar(v2, q1[3]);
    q1[3] = q1[3]*q2[3] - vec3_dot(q1, q2);
    vec3_cross(q1, q2);
    vec3_add_vec3(q1, v1);
    vec3_add_vec3(q1, v2);
}
void
quat_mul_quat(ik_real* IK_RESTRICT q1, const ik_real* IK_RESTRICT q2)
{
    mul_quat_no_normalise(q1, q2);
    quat_normalise(q1);
}

/* ------------------------------------------------------------------------- */
void
quat_mul_scalar(ik_real* IK_RESTRICT q, ik_real scalar)
{
    q[0] *= scalar;
    q[1] *= scalar;
    q[2] *= scalar;
    q[3] *= scalar;
}

/* ------------------------------------------------------------------------- */
void
quat_div_scalar(ik_real* IK_RESTRICT q, ik_real scalar)
{
    if (scalar == 0.0)
        quat_set_identity(q);
    else
    {
        ik_real rec = 1.0 / scalar;
        q[0] *= rec;
        q[1] *= rec;
        q[2] *= rec;
        q[3] *= rec;
    }
}

/* ------------------------------------------------------------------------- */
ik_real
quat_dot(ik_real* IK_RESTRICT q1, const ik_real* IK_RESTRICT q2)
{
    return q1[0] * q2[0] +
           q1[1] * q2[1] +
           q1[2] * q2[2] +
           q1[3] * q2[3];
}

/* ------------------------------------------------------------------------- */
void
quat_rotate_vec(ik_real* IK_RESTRICT v, const ik_real* IK_RESTRICT q)
{
    /* P' = RPR' */
    quat_t result;
    quat_t conj;
    quat_t point;

    memcpy(point.f, v, sizeof(ik_real) * 3);
    point.q.w = 0.0;

    conj = *(quat_t*)q;
    quat_conj(conj.f);

    result = *(quat_t*)q;
    mul_quat_no_normalise(result.f, point.f);
    mul_quat_no_normalise(result.f, conj.f);
    memcpy(v, result.f, sizeof(ik_real) * 3);
}

/* ------------------------------------------------------------------------- */
void
quat_normalise_sign(ik_real* IK_RESTRICT q1)
{
    quat_t unit = {{0, 0, 0, 1}};
    ik_real dot = quat_dot(q1, unit.f);
    if (dot < 0.0)
        quat_invert_sign(q1);
}
