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

C_HEADER_END

#endif /* VEC3_H */
