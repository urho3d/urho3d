#ifndef VEC3_H
#define VEC3_H

#include "ik/config.h"

C_HEADER_BEGIN

typedef union vec3_t
{
    struct {
        ik_real x;
        ik_real y;
        ik_real z;
    } v;
    ik_real f[3];
} vec3_t;

IK_PUBLIC_API void
vec3_set_zero(ik_real* v);

IK_PUBLIC_API void
vec3_add_vec3(ik_real* v1, const ik_real* v2);

IK_PUBLIC_API void
vec3_sub_vec3(ik_real* v1, const ik_real* v2);

IK_PUBLIC_API void
vec3_mul_scalar(ik_real* v1, ik_real scalar);

IK_PUBLIC_API void
vec3_div_scalar(ik_real* v, ik_real scalar);

IK_PUBLIC_API ik_real
vec3_length_squared(const ik_real* v);

IK_PUBLIC_API ik_real
vec3_length(const ik_real* v);

IK_PUBLIC_API void
vec3_normalise(ik_real* v);

IK_PUBLIC_API ik_real
vec3_dot(const ik_real* v1, const ik_real* v2);

IK_PUBLIC_API void
vec3_cross(ik_real* v1, const ik_real* v2);

/*!
 * @brief Calculates the angle between two vectors. If the angle is 0 or 180,
 * the delta rotation is set to identity.
 * @param[out] q A contiguous array of 4 ik_floats representing a quaternion.
 * The result is written to this. Any previous data is overwritten.
 * @param[in] v1 The first vector.
 * @param[in] v2 The second vector.
 */
IK_PUBLIC_API void
vec3_angle(ik_real* q, const ik_real* v1, const ik_real* v2);

C_HEADER_END

#endif /* VEC3_H */
