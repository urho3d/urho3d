#ifndef LIGHTSHIP_UTIL_BACKTRACE_H
#define LIGHTSHIP_UTIL_BACKTRACE_H

#define BACKTRACE_SIZE 64

#include "ik/config.h"

C_HEADER_BEGIN

/*!
 * @brief Generates a backtrace.
 * @param[in] size The maximum number of frames to walk.
 * @return Returns an array of char* arrays.
 * @note The returned array must be freed manually with FREE(returned_array).
 */
IK_PUBLIC_API char**
get_backtrace(int* size);

C_HEADER_END

#endif /* LIGHTSHIP_UTIL_BACKTRACE_H */
