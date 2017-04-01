#include "ik/effector.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

/* ------------------------------------------------------------------------- */
struct ik_node_t*
ik_node_create(uint32_t guid)
{
    struct ik_node_t* node = (struct ik_node_t*)MALLOC(sizeof *node);
    if(node == NULL)
        return NULL;

    ik_node_construct(node, guid);
    return node;
}

/* ------------------------------------------------------------------------- */
void
ik_node_construct(struct ik_node_t* node, uint32_t guid)
{
    memset(node, 0, sizeof *node);
    bstv_construct(&node->children);
    quat_set_identity(node->rotation.f);
    quat_set_identity(node->solved_rotation.f);
    node->guid = guid;
}

/* ------------------------------------------------------------------------- */
static void
ik_node_destroy_recursive(struct ik_node_t* node);
static void
ik_node_destruct_recursive(struct ik_node_t* node)
{
    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        ik_node_destroy_recursive(child);
    BSTV_END_EACH

    if(node->effector)
        ik_effector_destroy(node->effector);

    bstv_clear_free(&node->children);
}
void
ik_node_destruct(struct ik_node_t* node)
{
    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        ik_node_destroy_recursive(child);
    BSTV_END_EACH

    if(node->effector)
        ik_effector_destroy(node->effector);

    ik_node_unlink(node);
    bstv_clear_free(&node->children);
}

/* ------------------------------------------------------------------------- */
static void
ik_node_destroy_recursive(struct ik_node_t* node)
{
    ik_node_destruct_recursive(node);
    FREE(node);
}
void
ik_node_destroy(struct ik_node_t* node)
{
    ik_node_destruct(node);
    FREE(node);
}

/* ------------------------------------------------------------------------- */
void
ik_node_add_child(struct ik_node_t* node, struct ik_node_t* child)
{
    child->parent = node;
    bstv_insert(&node->children, child->guid, child);
}

/* ------------------------------------------------------------------------- */
void
ik_node_unlink(struct ik_node_t* node)
{
    if(node->parent == NULL)
        return;

    bstv_erase(&node->parent->children, node->guid);
    node->parent = NULL;
}

/* ------------------------------------------------------------------------- */
struct ik_node_t*
ik_node_find_child(struct ik_node_t* node, uint32_t guid)
{
    struct ik_node_t* found = bstv_find(&node->children, guid);
    if(found != NULL)
        return found;

    if(node->guid == guid)
        return node;

    BSTV_FOR_EACH(&node->children, struct ik_node_t, child_guid, child)
        found = ik_node_find_child(child, guid);
        if(found != NULL)
            return found;
    BSTV_END_EACH

    return NULL;
}

/* ------------------------------------------------------------------------- */
void
ik_node_attach_effector(struct ik_node_t* node, struct ik_effector_t* effector)
{
    node->effector = effector;
}

/* ------------------------------------------------------------------------- */
void
ik_node_destroy_effector(struct ik_node_t* node)
{
    if(node->effector == NULL)
        return;
    ik_effector_destroy(node->effector);
    node->effector = NULL;
}

/* ------------------------------------------------------------------------- */
static void
recursively_dump_dot(FILE* fp, struct ik_node_t* node)
{
    if(node->effector != NULL)
        fprintf(fp, "    %d [color=\"1.0 0.5 1.0\"];\n", node->guid);

    BSTV_FOR_EACH(&node->children, struct ik_node_t, guid, child)
        fprintf(fp, "    %d -- %d;\n", node->guid, guid);
        recursively_dump_dot(fp, child);
    BSTV_END_EACH
}

/* ------------------------------------------------------------------------- */
void
ik_node_dump_to_dot(struct ik_node_t* node, const char* file_name)
{
    FILE* fp = fopen(file_name, "w");
    if(fp == NULL)
    {
        ik_log_message("Failed to open file %s", file_name);
        return;
    }

    fprintf(fp, "graph graphname {\n");
    recursively_dump_dot(fp, node);
    fprintf(fp, "}\n");

    fclose(fp);
}
