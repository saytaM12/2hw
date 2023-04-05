// htab_find.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "private_htab.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item *curr_item = t->arr_ptr[index];
    while (curr_item) {
        if (strcmp(curr_item->data.key, key) == 0) {
            return &(curr_item->data);
        }

        curr_item = curr_item->next;
    }
    return NULL;
}
