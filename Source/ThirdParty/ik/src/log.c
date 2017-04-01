#include "ik/log.h"
#include "ik/memory.h"
#include "ik/ordered_vector.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

static struct log_t
{
    struct ordered_vector_t listeners; /* list of ik_log_cb_func */
    struct ordered_vector_t message_buffer;
}* g_log = NULL;

static void log_stdout_callback(const char* msg)
{
    puts(msg);
}

/* ------------------------------------------------------------------------- */
void
ik_log_init(enum ik_log_e options)
{
    if(g_log != NULL)
        return;

    g_log = (struct log_t*)MALLOC(sizeof *g_log);
    if(g_log == NULL)
        return;

    ordered_vector_construct(&g_log->listeners, sizeof(ik_log_cb_func));
    ordered_vector_construct(&g_log->message_buffer, sizeof(char));

    if(options == IK_LOG_STDOUT)
        ik_log_register_listener(log_stdout_callback);
}

/* ------------------------------------------------------------------------- */
void
ik_log_deinit(void)
{
    if(g_log == NULL)
        return;

    ordered_vector_clear_free(&g_log->message_buffer);
    ordered_vector_clear_free(&g_log->listeners);
    FREE(g_log);
    g_log = NULL;
}

/* ------------------------------------------------------------------------- */
void
ik_log_register_listener(ik_log_cb_func callback)
{
    if(g_log != NULL)
        ordered_vector_push(&g_log->listeners, &callback);
}

/* ------------------------------------------------------------------------- */
void
ik_log_unregister_listener(ik_log_cb_func callback)
{
    if(g_log == NULL)
        return;

    ORDERED_VECTOR_FOR_EACH(&g_log->listeners, ik_log_cb_func, registered_callback)
        if(callback == *registered_callback)
        {
            ordered_vector_erase_element(&g_log->listeners, registered_callback);
            return;
        }
    ORDERED_VECTOR_END_EACH
}

/* ------------------------------------------------------------------------- */
void
ik_log_message(const char* fmt, ...)
{
    va_list va;
    uintptr_t msg_len;

    if(g_log == NULL)
        return;

    va_start(va, fmt);
    msg_len = vsnprintf(NULL, 0, fmt, va);
    va_end(va);

    if(ordered_vector_resize(&g_log->message_buffer, (msg_len + 1) * sizeof(char)) < 0)
        return;
    va_start(va, fmt);
    vsprintf((char*)g_log->message_buffer.data, fmt, va);
    va_end(va);

    ORDERED_VECTOR_FOR_EACH(&g_log->listeners, ik_log_cb_func, callback)
        (*callback)((char*)g_log->message_buffer.data);
    ORDERED_VECTOR_END_EACH
}
