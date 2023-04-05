// htab_lookup_add.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include "private_htab.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    htab_pair_t *return_pair;
    if ((return_pair = htab_find(t, key))) {
        return_pair->value++;
        return return_pair;
    }

    struct htab_item *item_to_add = calloc(1, sizeof(struct htab_item));
    if (!item_to_add) {
        fputs("couldn't allocate memory for item to add", stderr);
        return NULL;
    }

    size_t key_size = strlen(key) + 1;
    char *key_to_add = malloc(key_size);
    if (!key_to_add) {
        fputs("couldn't allocate memory for key in item to add", stderr);
        free(item_to_add);
        return NULL;
    }

    t->size++;

    memcpy(key_to_add, key, key_size);
    struct htab_pair data_to_add = {.key = key_to_add, .value = 1};
    item_to_add->data = data_to_add;

    size_t index = (htab_hash_function(key) % t->arr_size);
    if (!t->arr_ptr[index]) {
        t->arr_ptr[index] = item_to_add;
        return return_pair;
    }
    else {
        item_to_add->next = t->arr_ptr[index];
        t->arr_ptr[index] = item_to_add;
        return return_pair;
    }
}
