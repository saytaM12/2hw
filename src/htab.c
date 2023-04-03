#include <stdio.h>
#include "htab.h"

struct htab_item {
    struct htab_pair data;
    struct htab_item* next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item** arr_ptr;
};

size_t htab_hash_function(htab_key_t str) {
    unsigned h = 0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

htab_t *htab_init(const size_t n) {
    htab_t *t = malloc(sizeof(htab_t));
    if (!t) {
        fputs("couldn't allocate memory for hash tab", stderr);
        return NULL;
    }

    t->arr_ptr = malloc(n * sizeof(struct htab_item*));
    if (!t->arr_ptr) {
        fputs("couldn't allocate memory for array of pointers", stderr);
        free(t);
        return NULL;
    }

    t->size = 0;
    t->arr_size = n;

    return t;
}

size_t htab_size(const htab_t *t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item* curr_item = t->arr_ptr[index];
    while (curr_item->next != NULL) {
        if (strcmp(curr_item->data.key, key) == 0) {
            return &(curr_item->data);
        }

        curr_item = curr_item->next;
    }
    return NULL;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    htab_pair_t *return_pair;
    if (return_pair = htab_find(t, key)) {
        return_pair->value++;
        return return_pair;
    }

    struct htab_item *item_to_add = malloc(sizeof(struct htab_item));
    if (!item_to_add) {
        fputs("couldn't allocate memory for item to add", stderr);
        return NULL;
    }
    struct htab_pair data_to_add = {.key = malloc(sizeof(key)), .value = 1};
    if (!data_to_add.key) {
        fputs("couldn't allocate memory for key in item to add", stderr);
        free(item_to_add);
        return NULL;
    }
    data_to_add.key = key;
    item_to_add->data = data_to_add;

    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item* curr_item = t->arr_ptr[index];
    while (curr_item->next != NULL) {
        curr_item = curr_item->next;
    }

    curr_item->next = item_to_add;
}

bool htab_erase(htab_t *t, htab_key_t key) {
}

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
}

void htab_clear(htab_t *t) {
}

void htab_free(htab_t *t) {
}

void htab_statistics(const htab_t *t) {
}
