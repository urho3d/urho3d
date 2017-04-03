#ifndef MEMORY_H
#define MEMORY_H

#include "ik/config.h"

#if IK_MEMORY_DEBUGGING == ON
#   define MALLOC malloc_wrapper
#   define FREE   free_wrapper
#else
#   include <stdlib.h>
#   define MALLOC malloc
#   define FREE   free
#endif

C_HEADER_BEGIN

/*!
 * @brief Initialises the memory system.
 *
 * In release mode this does nothing. In debug mode it will initialise
 * memory reports and backtraces, if enabled.
 */
IK_PUBLIC_API void
ik_memory_init(void);

/*!
 * @brief De-initialises the memory system.
 *
 * In release mode this does nothing. In debug mode this will output the memory
 * report and print backtraces, if enabled.
 * @return Returns the number of memory leaks.
 */
IK_PUBLIC_API uintptr_t
ik_memory_deinit(void);

#if IK_MEMORY_DEBUGGING == ON
/*!
 * @brief Does the same thing as a normal call to malloc(), but does some
 * additional work to monitor and track down memory leaks.
 */
IK_PUBLIC_API void*
malloc_wrapper(intptr_t size);

/*!
 * @brief Does the same thing as a normal call to fee(), but does some
 * additional work to monitor and track down memory leaks.
 */
IK_PUBLIC_API void
free_wrapper(void* ptr);
#endif /* IK_MEMORY_DEBUGGING */

IK_PUBLIC_API void
mutated_string_and_hex_dump(void* data, intptr_t size_in_bytes);

C_HEADER_END

#endif /* MEMORY_H */
