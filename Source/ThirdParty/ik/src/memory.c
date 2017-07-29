#include "ik/memory.h"
#include "ik/bst_vector.h"
#include "ik/backtrace.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BACKTRACE_OMIT_COUNT 2

#ifdef IK_MEMORY_DEBUGGING
static uintptr_t g_allocations = 0;
static uintptr_t d_deg_allocations = 0;
static uintptr_t g_ignore_bstv_malloc = 0;
static bstv_t report;

typedef struct report_info_t
{
    uintptr_t location;
    uintptr_t size;
#   ifdef IK_MEMORY_BACKTRACE
    int backtrace_size;
    char** backtrace;
#   endif
} report_info_t;

/* ------------------------------------------------------------------------- */
void
ik_memory_init(void)
{
    g_allocations = 0;
    d_deg_allocations = 0;

    /*
     * Init bst vector of report objects and force it to allocate by adding
     * and removing one item. This fixes a bug where the number of memory leaks
     * would be wrong in the case of MALLOC() never being called.
     */
    g_ignore_bstv_malloc = 1;
        bstv_construct(&report);
        bstv_insert(&report, 0, NULL); bstv_erase(&report, 0);
    g_ignore_bstv_malloc = 0;
}

/* ------------------------------------------------------------------------- */
void*
malloc_wrapper(intptr_t size)
{
    void* p = NULL;
    report_info_t* info = NULL;

    /* breaking from this will clean up and return NULL */
    for (;;)
    {
        /* allocate */
        p = malloc(size);
        if (p)
            ++g_allocations;
        else
            break;

        /*
        * Record allocation info. Call to bstv may allocate memory,
        * so set flag to ignore the call to malloc() when inserting.
        */
        if (!g_ignore_bstv_malloc)
        {
            g_ignore_bstv_malloc = 1;
            info = (report_info_t*)malloc(sizeof(report_info_t));
            if (!info)
            {
                fprintf(stderr, "[memory] ERROR: malloc() for report_info_t failed"
                    " -- not enough memory.\n");
                g_ignore_bstv_malloc = 0;
                break;
            }

            /* record the location and size of the allocation */
            info->location = (uintptr_t)p;
            info->size = size;

            /* if (enabled, generate a backtrace so we know where memory leaks
            * occurred */
#   ifdef IK_MEMORY_BACKTRACE
            if (!(info->backtrace = get_backtrace(&info->backtrace_size)))
                fprintf(stderr, "[memory] WARNING: Failed to generate backtrace\n");
#   endif

            /* insert into bstv */
            if (bstv_insert(&report, (uintptr_t)p, info) == 1)
            {
                fprintf(stderr,
                "[memory] WARNING: Hash collision occurred when inserting\n"
                "into memory report bstv. On 64-bit systems the pointers are\n"
                "rounded down to 32-bit unsigned integers, so even though\n"
                "it's rare, collisions can happen.\n\n"
                "The matching call to FREE() will generate a warning saying\n"
                "something is being freed that was never allocated. This is to\n"
                "be expected and can be ignored.\n");
#   ifdef IK_MEMORY_BACKTRACE
                {
                    char** bt;
                    int bt_size, i;
                    if ((bt = get_backtrace(&bt_size)))
                    {
                        printf("  backtrace to where malloc() was called:\n");
                        for (i = 0; i < bt_size; ++i)
                            printf("      %s\n", bt[i]);
                        printf("  -----------------------------------------\n");
                        free(bt);
                    }
                    else
                        fprintf(stderr, "[memory] WARNING: Failed to generate backtrace\n");
                }
#   endif
            }
            g_ignore_bstv_malloc = 0;
        }

        /* success */
        return p;
    }

    /* failure */
    if (p)
    {
        free(p);
        --g_allocations;
    }

    if (info)
    {
#   ifdef IK_MEMORY_BACKTRACE
        if (info->backtrace)
            free(info->backtrace);
#   endif
        free(info);
    }

    return NULL;
}

/* ------------------------------------------------------------------------- */
void
free_wrapper(void* ptr)
{
    /* find matching allocation and remove from bstv */
    if (!g_ignore_bstv_malloc)
    {
        report_info_t* info = (report_info_t*)bstv_erase(&report, (uintptr_t)ptr);
        if (info)
        {
#   ifdef IK_MEMORY_BACKTRACE
            if (info->backtrace)
                free(info->backtrace);
            else
                fprintf(stderr, "[memory] WARNING: free(): Allocation didn't "
                    "have a backtrace (it was NULL)\n");
#   endif
            free(info);
        }
        else
        {
#   ifdef IK_MEMORY_BACKTRACE
            char** bt;
            int bt_size, i;
            fprintf(stderr, "  -----------------------------------------\n");
#   endif
            fprintf(stderr, "  WARNING: Freeing something that was never allocated\n");
#   ifdef IK_MEMORY_BACKTRACE
            if ((bt = get_backtrace(&bt_size)))
            {
                fprintf(stderr, "  backtrace to where free() was called:\n");
                for (i = 0; i < bt_size; ++i)
                    fprintf(stderr, "      %s\n", bt[i]);
                fprintf(stderr, "  -----------------------------------------\n");
                free(bt);
            }
            else
                fprintf(stderr, "[memory] WARNING: Failed to generate backtrace\n");
#   endif
        }
    }

    if (ptr)
    {
        ++d_deg_allocations;
        free(ptr);
    }
    else
        fprintf(stderr, "Warning: free(NULL)\n");
}

/* ------------------------------------------------------------------------- */
uintptr_t
ik_memory_deinit(void)
{
    uintptr_t leaks;

    --g_allocations; /* this is the single allocation still held by the report vector */

    printf("=========================================\n");
    printf("Inverse Kinematics Memory Report\n");
    printf("=========================================\n");

    /* report details on any g_allocations that were not de-allocated */
    if (report.vector.count != 0)
    {
        BSTV_FOR_EACH(&report, report_info_t, key, info)

            printf("  un-freed memory at %p, size %p\n", (void*)info->location, (void*)info->size);
            mutated_string_and_hex_dump((void*)info->location, info->size);

#   ifdef IK_MEMORY_BACKTRACE
            printf("  Backtrace to where malloc() was called:\n");
            {
                intptr_t i;
                for (i = BACKTRACE_OMIT_COUNT; i < info->backtrace_size; ++i)
                    printf("      %s\n", info->backtrace[i]);
            }
            free(info->backtrace); /* this was allocated when malloc() was called */
            printf("  -----------------------------------------\n");
#   endif
            free(info);

        BSTV_END_EACH

        printf("=========================================\n");
    }

    /* overall report */
    leaks = (g_allocations > d_deg_allocations ? g_allocations - d_deg_allocations : d_deg_allocations - g_allocations);
    printf("allocations: %lu\n", g_allocations);
    printf("deallocations: %lu\n", d_deg_allocations);
    printf("memory leaks: %lu\n", leaks);
    printf("=========================================\n");

    ++g_allocations; /* this is the single allocation still held by the report vector */
    g_ignore_bstv_malloc = 1;
    bstv_clear_free(&report);

    return leaks;
}

#else /* IK_MEMORY_DEBUGGING */

void ik_memory_init(void) {}
uintptr_t ik_memory_deinit(void) { return 0; }

#endif /* IK_MEMORY_DEBUGGING */

/* ------------------------------------------------------------------------- */
void
mutated_string_and_hex_dump(void* data, intptr_t length_in_bytes)
{
    char* dump;
    intptr_t i;

    /* allocate and copy data into new buffer */
    if (!(dump = malloc(length_in_bytes + 1)))
    {
        fprintf(stderr, "[memory] WARNING: Failed to malloc() space for dump\n");
        return;
    }
    memcpy(dump, data, length_in_bytes);
    dump[length_in_bytes] = '\0';

    /* mutate null terminators into dots */
    for (i = 0; i != length_in_bytes; ++i)
        if (dump[i] == '\0')
            dump[i] = '.';

    /* dump */
    printf("  mutated string dump: %s\n", dump);
    printf("  hex dump: ");
    for (i = 0; i != length_in_bytes; ++i)
        printf(" %02x", (unsigned char)dump[i]);
    printf("\n");

    free(dump);
}
