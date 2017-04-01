#ifndef QUATERNION_H
#define QUATERNION_H

#include "ik/config.h"
#include "ik/vec3.h"

C_HEADER_BEGIN

typedef union quat_t
{
    struct {
        ik_real x;
        ik_real y;
        ik_real z;
        ik_real w;
    } q;
    struct {
        vec3_t v;
        ik_real w;
    } vw;
    ik_real f[4];
} quat_t;

/*!
 * @brief Sets the quaternion to its identity rotation.
 */
IK_PUBLIC_API void
quat_set_identity(ik_real* q);

/*!
 * @brief Adds the elements from one quaternion to another. Required for
 * averaging multiple quaternions.
 */
IK_PUBLIC_API void
quat_add_quat(ik_real* q1, const ik_real* q2);

/*!
 * @brief Calculates the magnitude of a quaternion.
 */
IK_PUBLIC_API ik_real
quat_mag(const ik_real* q);

/*!
 * @brief Inverts the sign of the vector part of the quaternion (conjugation).
 */
IK_PUBLIC_API void
quat_conj(ik_real* q);

/*!
 * @brief Inverts the sign of all elements (NOT conjugation).
 */
IK_PUBLIC_API void
quat_invert_sign(ik_real* q);

/*!
 * @brief Normalises the quaternion.
 */
IK_PUBLIC_API void
quat_normalise(ik_real* q);

/*!
 * @brief Multiplies two quaternions together.
 */
IK_PUBLIC_API void
quat_mul_quat(ik_real* q1, const ik_real* q2);

/*!
 * @brief Multiplies each component by a constant.
 */
IK_PUBLIC_API void
quat_mul_scalar(ik_real* q, ik_real scalar);

/*!
 * @brief Divides each component by a constant. If the constant is 0 then the
 * result will be a unit quaternion.
 */
IK_PUBLIC_API void
quat_div_scalar(ik_real* q, ik_real scalar);

/*!
 * @brief Calculates the scalar product of two quaternions.
 */
IK_PUBLIC_API ik_real
quat_dot(ik_real* q1, const ik_real* q2);

/*!
 * @brief Rotations a vector by the specified quaternion.
 */
IK_PUBLIC_API void
quat_rotate_vec(ik_real* v, const ik_real* q);

/*!
 * @brief Returns 0 if the two quaternions are "close", i.e. if -q has a
 * similar rotation as q.
 */
IK_PUBLIC_API void
quat_normalise_sign(ik_real* q1);

C_HEADER_END

#endif /* QUATERNION_H */
