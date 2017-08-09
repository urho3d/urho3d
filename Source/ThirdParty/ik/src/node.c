#include "ik/constraint.h"
#include "ik/effector.h"
#include "ik/log.h"
#include "ik/memory.h"
#include "ik/node.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

/* ------------------------------------------------------------------------- */
ik_node_t*
ik_node_create(uint32_t guid)
{
    ik_node_t* node = (ik_node_t*)MALLOC(sizeof *node);
    if (node == NULL)
        return NULL;

    ik_node_construct(node, guid);
    return node;
}

/* ------------------------------------------------------------------------- */
void
ik_node_construct(ik_node_t* node, uint32_t guid)
{
    memset(node, 0, sizeof *node);
    bstv_construct(&node->children);
    quat_set_identity(node->original_rotation.f);
    quat_set_identity(node->rotation.f);
    node->guid = guid;
}

/* ------------------------------------------------------------------------- */
static void
ik_node_destroy_recursive(ik_node_t* node);
static void
ik_node_destruct_recursive(ik_node_t* node)
{
    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        ik_node_destroy_recursive(child);
    BSTV_END_EACH

    if (node->effector)
        ik_effector_destroy(node->effector);
    if (node->constraint)
        ik_constraint_destroy(node->constraint);

    bstv_clear_free(&node->children);
}
void
ik_node_destruct(ik_node_t* node)
{
    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        ik_node_destroy_recursive(child);
    BSTV_END_EACH

    if (node->effector)
        ik_effector_destroy(node->effector);
    if (node->constraint)
        ik_constraint_destroy(node->constraint);

    ik_node_unlink(node);
    bstv_clear_free(&node->children);
}

/* ------------------------------------------------------------------------- */
static void
ik_node_destroy_recursive(ik_node_t* node)
{
    ik_node_destruct_recursive(node);
    FREE(node);
}
void
ik_node_destroy(ik_node_t* node)
{
    ik_node_destruct(node);
    FREE(node);
}

/* ------------------------------------------------------------------------- */
void
ik_node_add_child(ik_node_t* node, ik_node_t* child)
{
    child->parent = node;
    bstv_insert(&node->children, child->guid, child);
}

/* ------------------------------------------------------------------------- */
void
ik_node_unlink(ik_node_t* node)
{
    if (node->parent == NULL)
        return;

    bstv_erase(&node->parent->children, node->guid);
    node->parent = NULL;
}

/* ------------------------------------------------------------------------- */
ik_node_t*
ik_node_find_child(ik_node_t* node, uint32_t guid)
{
    ik_node_t* found = bstv_find(&node->children, guid);
    if (found != NULL)
        return found;

    if (node->guid == guid)
        return node;

    BSTV_FOR_EACH(&node->children, ik_node_t, child_guid, child)
        found = ik_node_find_child(child, guid);
        if (found != NULL)
            return found;
    BSTV_END_EACH

    return NULL;
}

/* ------------------------------------------------------------------------- */
void
ik_node_attach_effector(ik_node_t* node, ik_effector_t* effector)
{
    if (node->effector != NULL)
        ik_effector_destroy(node->effector);

    node->effector = effector;
}

/* ------------------------------------------------------------------------- */
void
ik_node_destroy_effector(ik_node_t* node)
{
    if (node->effector == NULL)
        return;
    ik_effector_destroy(node->effector);
    node->effector = NULL;
}

/* ------------------------------------------------------------------------- */
void
ik_node_attach_constraint(ik_node_t* node, ik_constraint_t* constraint)
{
    if (node->constraint != NULL)
        ik_constraint_destroy(node->constraint);

    node->constraint = constraint;
}

/* ------------------------------------------------------------------------- */
void
ik_node_destroy_constraint(ik_node_t* node)
{
    if (node->constraint == NULL)
        return;
    ik_constraint_destroy(node->constraint);
    node->constraint = NULL;
}

/* ------------------------------------------------------------------------- */
static void
recursively_dump_dot(FILE* fp, ik_node_t* node)
{
    if (node->effector != NULL)
        fprintf(fp, "    %d [color=\"1.0 0.5 1.0\"];\n", node->guid);

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        fprintf(fp, "    %d -- %d;\n", node->guid, guid);
        recursively_dump_dot(fp, child);
    BSTV_END_EACH
}

/* ------------------------------------------------------------------------- */
void
ik_node_dump_to_dot(ik_node_t* node, const char* file_name)
{
    FILE* fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        ik_log_message("Failed to open file %s", file_name);
        return;
    }

    fprintf(fp, "graph graphname {\n");
    recursively_dump_dot(fp, node);
    fprintf(fp, "}\n");

    fclose(fp);
}

/* ------------------------------------------------------------------------- */
static void
local_to_global_recursive(ik_node_t* node, vec3_t acc_pos, quat_t acc_rot)
{
    vec3_t position;
    quat_t rotation;

    quat_rotate_vec(node->position.f, acc_rot.f);
    position = node->position;
    vec3_add_vec3(node->position.f, acc_pos.f);
    vec3_add_vec3(acc_pos.f, position.f);

    rotation = node->rotation;
    quat_mul_quat(node->rotation.f, acc_rot.f);
    quat_mul_quat(acc_rot.f, rotation.f);

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        local_to_global_recursive(child, acc_pos, acc_rot);
    BSTV_END_EACH
}
void
ik_node_local_to_global(ik_node_t* node)
{
    vec3_t acc_pos = {{0, 0, 0}};
    quat_t acc_rot = {{0, 0, 0, 1}};
    local_to_global_recursive(node, acc_pos, acc_rot);
}

/* ------------------------------------------------------------------------- */
static void
global_to_local_recursive(ik_node_t* node, vec3_t acc_pos, quat_t acc_rot)
{
    quat_t inv_rotation = acc_rot;
    quat_conj(inv_rotation.f);
    quat_mul_quat(node->rotation.f, inv_rotation.f);
    quat_mul_quat(acc_rot.f, node->rotation.f);

    vec3_sub_vec3(node->position.f, acc_pos.f);
    vec3_add_vec3(acc_pos.f, node->position.f);
    quat_rotate_vec(node->position.f, inv_rotation.f);

    BSTV_FOR_EACH(&node->children, ik_node_t, guid, child)
        global_to_local_recursive(child, acc_pos, acc_rot);
    BSTV_END_EACH
}
void
ik_node_global_to_local(ik_node_t* node)
{
    vec3_t acc_pos = {{0, 0, 0}};
    quat_t acc_rot = {{0, 0, 0, 1}};
    global_to_local_recursive(node, acc_pos, acc_rot);
}
