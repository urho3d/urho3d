#include "ik/bst_vector.h"
#include "ik/memory.h"
#include <assert.h>
#include <string.h>

const uint32_t BST_VECTOR_INVALID_HASH = (uint32_t)-1;

/* ------------------------------------------------------------------------- */
struct bstv_t*
bstv_create(void)
{
    struct bstv_t* bstv;
    if(!(bstv = (struct bstv_t*)MALLOC(sizeof *bstv)))
        return NULL;
    bstv_construct(bstv);
    return bstv;
}

/* ------------------------------------------------------------------------- */
void
bstv_construct(struct bstv_t* bstv)
{
    assert(bstv);
    ordered_vector_construct(&bstv->vector, sizeof(struct bstv_hash_value_t));
}

/* ------------------------------------------------------------------------- */
void
bstv_destroy(struct bstv_t* bstv)
{
    assert(bstv);
    bstv_clear_free(bstv);
    FREE(bstv);
}

/* ------------------------------------------------------------------------- */
/* algorithm taken from GNU GCC stdlibc++'s lower_bound function, line 2121 in stl_algo.h */
/* https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02014.html */
static struct bstv_hash_value_t*
bstv_find_lower_bound(const struct bstv_t* bstv, uint32_t hash)
{
    uint32_t half;
    struct bstv_hash_value_t* middle;
    struct bstv_hash_value_t* data;
    uint32_t len;

    assert(bstv);

    data = (struct bstv_hash_value_t*)bstv->vector.data;
    len = bstv->vector.count;

    /* if the vector has no data, return NULL */
    if(!len)
        return NULL;

    while(len > 0)
    {
        half = len >> 1;
        middle = data + half;
        if(middle->hash < hash)
        {
            data = middle;
            ++data;
            len = len - half - 1;
        }
        else
            len = half;
    }

    /* if "data" is pointing outside of the valid elements in the vector, also return NULL */
    if((intptr_t)data >= (intptr_t)bstv->vector.data + (intptr_t)bstv->vector.count * (intptr_t)bstv->vector.element_size)
        return NULL;
    else
        return data;
}

/* ------------------------------------------------------------------------- */
int
bstv_insert(struct bstv_t* bstv, uint32_t hash, void* value)
{
    struct bstv_hash_value_t* emplaced_data;
    struct bstv_hash_value_t* lower_bound;

    assert(bstv);

    /* don't insert reserved hashes */
    if(hash == BST_VECTOR_INVALID_HASH)
        return -1;

    /* lookup location in bstv to insert */
    lower_bound = bstv_find_lower_bound(bstv, hash);
    if(lower_bound && lower_bound->hash == hash)
        return 1;

    /* either push back or insert, depending on whether there is already data
     * in the bstv */
    if(!lower_bound)
        emplaced_data = (struct bstv_hash_value_t*)ordered_vector_push_emplace(&bstv->vector);
    else
        emplaced_data = ordered_vector_insert_emplace(&bstv->vector,
                          lower_bound - (struct bstv_hash_value_t*)bstv->vector.data);

    if(!emplaced_data)
        return -1;

    memset(emplaced_data, 0, sizeof *emplaced_data);
    emplaced_data->hash = hash;
    emplaced_data->value = value;

    return 0;
}

/* ------------------------------------------------------------------------- */
void
bstv_set(struct bstv_t* bstv, uint32_t hash, void* value)
{
    struct bstv_hash_value_t* data;

    assert(bstv);

    data = bstv_find_lower_bound(bstv, hash);
    if(data && data->hash == hash)
        data->value = value;
}

/* ------------------------------------------------------------------------- */
void*
bstv_find(const struct bstv_t* bstv, uint32_t hash)
{
    void** result = bstv_find_ptr(bstv, hash);
    return result == NULL ? NULL : *result;
}

/* ------------------------------------------------------------------------- */
void**
bstv_find_ptr(const struct bstv_t* bstv, uint32_t hash)
{
    struct bstv_hash_value_t* data;

    assert(bstv);

    data = bstv_find_lower_bound(bstv, hash);
    if(!data || data->hash != hash)
        return NULL;
    return &data->value;
}

/* ------------------------------------------------------------------------- */
uint32_t
bstv_find_element(const struct bstv_t* bstv, const void* value)
{
    assert(bstv);

    ORDERED_VECTOR_FOR_EACH(&bstv->vector, struct bstv_hash_value_t, kv)
        if(kv->value == value)
            return kv->hash;
    ORDERED_VECTOR_END_EACH
    return BST_VECTOR_INVALID_HASH;
}

/* ------------------------------------------------------------------------- */
void*
bstv_get_any_element(const struct bstv_t* bstv)
{
    struct bstv_hash_value_t* kv;
    assert(bstv);
    kv = (struct bstv_hash_value_t*)ordered_vector_back(&bstv->vector);
    if(kv)
        return kv->value;
    return NULL;
}

/* ------------------------------------------------------------------------- */
int
bstv_hash_exists(struct bstv_t* bstv, uint32_t hash)
{
    struct bstv_hash_value_t* data;

    assert(bstv);

    data = bstv_find_lower_bound(bstv, hash);
    if(data && data->hash == hash)
        return 0;
    return -1;
}

/* ------------------------------------------------------------------------- */
uint32_t
bstv_find_unused_hash(struct bstv_t* bstv)
{
    uint32_t i = 0;

    assert(bstv);

    BSTV_FOR_EACH(bstv, void, key, value)
        if(i != key)
            break;
        ++i;
    BSTV_END_EACH
    return i;
}

/* ------------------------------------------------------------------------- */
void*
bstv_erase(struct bstv_t* bstv, uint32_t hash)
{
    void* value;
    struct bstv_hash_value_t* data;

    assert(bstv);

    data = bstv_find_lower_bound(bstv, hash);
    if(!data || data->hash != hash)
        return NULL;

    value = data->value;
    ordered_vector_erase_element(&bstv->vector, (DATA_POINTER_TYPE*)data);
    return value;
}

/* ------------------------------------------------------------------------- */
void*
bstv_erase_element(struct bstv_t* bstv, void* value)
{
    void* data;
    uint32_t hash;

    assert(bstv);

    hash = bstv_find_element(bstv, value);
    if(hash == BST_VECTOR_INVALID_HASH)
        return NULL;

    data = bstv_find_lower_bound(bstv, hash);
    ordered_vector_erase_element(&bstv->vector, (DATA_POINTER_TYPE*)data);

    return value;
}

/* ------------------------------------------------------------------------- */
void
bstv_clear(struct bstv_t* bstv)
{
    assert(bstv);
    ordered_vector_clear(&bstv->vector);
}

/* ------------------------------------------------------------------------- */
void bstv_clear_free(struct bstv_t* bstv)
{
    assert(bstv);
    ordered_vector_clear_free(&bstv->vector);
}
