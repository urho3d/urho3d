#ifndef IK_LOG_H
#define IK_LOG_H

#include "ik/config.h"

C_HEADER_BEGIN

typedef void (*ik_log_cb_func)(const char*);

typedef enum ik_log_e
{
    IK_LOG_NONE,
    IK_LOG_STDOUT
} ik_log_e;

IK_PUBLIC_API void
ik_log_init(ik_log_e options);

IK_PUBLIC_API void
ik_log_deinit(void);

IK_PUBLIC_API void
ik_log_register_listener(ik_log_cb_func callback);

IK_PUBLIC_API void
ik_log_unregister_listener(ik_log_cb_func callback);

IK_PUBLIC_API void
ik_log_message(const char* fmt, ...);

C_HEADER_END

#endif /* IK_LOG_H */
